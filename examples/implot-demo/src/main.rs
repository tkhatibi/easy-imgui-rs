use std::os::raw::{c_int, c_void};

use easy_imgui_window::{
    AppHandler, Application, Args, EventResult,
    easy_imgui::{self as imgui, lbl},
    easy_imgui_sys::{self as sys},
    winit,
};
use winit::{event::WindowEvent, event_loop::EventLoop};

fn main() {
    // env_logger::Builder::new()
    //     .filter_level(log::LevelFilter::Debug)
    //     .parse_default_env()
    //     .init();

    let event_loop = EventLoop::with_user_event().build().unwrap();

    let mut main = AppHandler::<App>::new(&event_loop, ());
    main.imgui_builder().set_docking(true);
    main.attributes().title = String::from("Example");

    match event_loop.run_app(&mut main) {
        Err(e) => println!("{e:#?}"),
        _ => println!("Ok"),
    }
}

struct App;

// static KARLA_TTF: &[u8] = include_bytes!("Karla-Regular.ttf");

impl Application for App {
    type UserEvent = ();
    type Data = ();
    fn new(args: Args<Self>) -> App {
        // Dear ImGui by default uses "imgui.ini", but easy_imgui sets it to None.
        let imgui = args.window.renderer().imgui();
        imgui.set_ini_file_name(Some("imgui.ini"));
        let font_atlas = imgui.io_mut().font_atlas_mut();
        font_atlas.add_font(imgui::FontInfo::default_font());
        // font_atlas.add_font(imgui::FontInfo::new(KARLA_TTF).set_name("karla"));
        //imgui.style_mut().FontSizeBase = 16.0;
        App
    }
    fn window_event(&mut self, args: Args<Self>, _event: WindowEvent, res: EventResult) {
        if res.window_closed {
            args.event_loop.exit();
        }
    }
}

unsafe extern "C" fn bar_getter(idx: c_int, user_data: *mut c_void) -> sys::ImPlotPoint {
    // reinterpret user_data as pointer to f64
    let vals = user_data as *const f64;

    // now do the pointer arithmetic + deref in its own unsafe block
    let y = unsafe { *vals.add(idx as usize) };

    // x = index, y = array value
    sys::ImPlotPoint { x: idx as f64, y }
}

impl imgui::UiBuilder for App {
    fn do_ui(&mut self, ui: &imgui::Ui<Self>) {
        ui.dock_space_over_viewport(0, ui.get_main_viewport(), imgui::DockNodeFlags::None);
        ui.show_demo_window(None);
        ui.show_implot_demo_window(None);

        let mut bar_data = Vec::new();
        for i in 0..10 {
            bar_data.push(i + 1);
        }

        let mut bar_data = vec![1.0_f64, 2.5, 0.3, 4.2];
        let labels = std::ffi::CString::new("My Bars").unwrap();

        // we need a *mut c_void, so get a mutable pointer to our Vec’s buffer
        let user_data = bar_data.as_mut_ptr() as *mut c_void;
        let count = bar_data.len() as core::ffi::c_int;
        let width = 0.8_f64;

        ui.window_config(lbl("Hello World!")).with(|| {
            ui.text("This is some useful text."); // Display some text (you can use a format strings too)
            unsafe {
                if sys::ImPlot_BeginPlot(
                    std::ffi::CString::new("Plot").unwrap().as_ptr(),
                    &sys::ImVec2 { x: -1.0, y: 0.0 },
                    0,
                ) {
                    sys::ImPlot_PlotBarsG(
                        labels.as_ptr(),
                        Some(bar_getter),
                        user_data,
                        count,
                        width,
                        0,
                    );
                    sys::ImPlot_EndPlot();
                }
            }
        });
    }
}

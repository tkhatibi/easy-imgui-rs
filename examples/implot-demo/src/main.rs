use easy_imgui_window::{
    AppHandler, Application, Args, EventResult,
    easy_imgui::{
        self as imgui, PlotBarsFlags, PlotFlags, PlotLineFlags, WithImPlot, im_vec2, lbl,
        plot_line_u16,
    },
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
        args.window.ping_user_input();

        if res.window_closed {
            args.event_loop.exit();
        }
    }
}

impl imgui::UiBuilder for App {
    fn do_ui(&mut self, ui: &imgui::Ui<Self>) {
        ui.dock_space_over_viewport(0, ui.get_main_viewport(), imgui::DockNodeFlags::None);
        ui.show_demo_window(None);
        ui.show_implot_demo_window(None);

        ui.window_config(lbl("Hello World!")).with(|| {
            ui.text("This is some useful text.");

            let points = vec![
                im_vec2(1.0, 10.0),
                im_vec2(2.0, 20.0),
                im_vec2(3.0, 50.0),
                im_vec2(4.0, 80.0),
                im_vec2(5.0, 60.0),
                im_vec2(6.0, 90.0),
                im_vec2(7.0, 70.0),
                im_vec2(8.0, 80.0),
            ];
            let values = vec![12u16, 14, 15, 14, 17, 18, 16, 17, 16, 20, 25, 27];

            ui.plot("plot")
                .size(im_vec2(-1.0, 0.0))
                .flags(PlotFlags::NoMenus | PlotFlags::NoLegend)
                .with(|plot| {
                    plot.bars("My Bars")
                        .bar_size(0.8)
                        .flags(PlotBarsFlags::Horizontal)
                        .with(&points);

                    plot_line_u16("My values", &values, 1.0, 0.0, PlotLineFlags::Loop, 0); // I don't even know what is stride
                });
        });
    }
}

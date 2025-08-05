struct ImGuiContext;
thread_local ImGuiContext *MyImGuiTLS;

#include "imgui.cpp"
#include "imgui_demo.cpp"
#include "imgui_draw.cpp"
#include "imgui_tables.cpp"
#include "imgui_widgets.cpp"

#ifdef IMGUI_ENABLE_FREETYPE
    #include "misc/freetype/imgui_freetype.cpp"
#endif

#ifdef IMGUI_ENABLE_IMPLOT
    #include "implot.cpp"
    #include "implot_demo.cpp"
    #include "implot_items.cpp"
    #include "implot_wrappers.h"
#endif

#ifdef _MSC_VER
    #include "hack_msvc.cpp"
#endif

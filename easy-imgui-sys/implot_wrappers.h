#include "implot.h"

#ifdef __cplusplus
extern "C" {
#endif

// Wrapper macro to generate functions for each supported type
#define DEFINE_PLOT_WRAPPERS(TYPE, NAME) \
    /* PlotLine overloads */ \
    void ImPlot_PlotLine_##NAME(const char* label_id, const TYPE* values, int count, double xscale = 1, double xstart = 0, ImPlotLineFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotLine<TYPE>(label_id, values, count, xscale, xstart, flags, offset, stride); \
    } \
    void ImPlot_PlotLine_##NAME##_XY(const char* label_id, const TYPE* xs, const TYPE* ys, int count, ImPlotLineFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotLine<TYPE>(label_id, xs, ys, count, flags, offset, stride); \
    } \
    /* PlotScatter overloads */ \
    void ImPlot_PlotScatter_##NAME(const char* label_id, const TYPE* values, int count, double xscale = 1, double xstart = 0, ImPlotScatterFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotScatter<TYPE>(label_id, values, count, xscale, xstart, flags, offset, stride); \
    } \
    void ImPlot_PlotScatter_##NAME##_XY(const char* label_id, const TYPE* xs, const TYPE* ys, int count, ImPlotScatterFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotScatter<TYPE>(label_id, xs, ys, count, flags, offset, stride); \
    } \
    /* PlotStairs overloads */ \
    void ImPlot_PlotStairs_##NAME(const char* label_id, const TYPE* values, int count, double xscale = 1, double xstart = 0, ImPlotStairsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotStairs<TYPE>(label_id, values, count, xscale, xstart, flags, offset, stride); \
    } \
    void ImPlot_PlotStairs_##NAME##_XY(const char* label_id, const TYPE* xs, const TYPE* ys, int count, ImPlotStairsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotStairs<TYPE>(label_id, xs, ys, count, flags, offset, stride); \
    } \
    /* PlotShaded overloads */ \
    void ImPlot_PlotShaded_##NAME(const char* label_id, const TYPE* values, int count, double yref = 0, double xscale = 1, double xstart = 0, ImPlotShadedFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotShaded<TYPE>(label_id, values, count, yref, xscale, xstart, flags, offset, stride); \
    } \
    void ImPlot_PlotShaded_##NAME##_XY(const char* label_id, const TYPE* xs, const TYPE* ys, int count, double yref = 0, ImPlotShadedFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotShaded<TYPE>(label_id, xs, ys, count, yref, flags, offset, stride); \
    } \
    void ImPlot_PlotShaded_##NAME##_XY2(const char* label_id, const TYPE* xs, const TYPE* ys1, const TYPE* ys2, int count, ImPlotShadedFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotShaded<TYPE>(label_id, xs, ys1, ys2, count, flags, offset, stride); \
    } \
    /* PlotBars overloads */ \
    void ImPlot_PlotBars_##NAME(const char* label_id, const TYPE* values, int count, double bar_size = 0.67, double shift = 0, ImPlotBarsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotBars<TYPE>(label_id, values, count, bar_size, shift, flags, offset, stride); \
    } \
    void ImPlot_PlotBars_##NAME##_XY(const char* label_id, const TYPE* xs, const TYPE* ys, int count, double bar_size, ImPlotBarsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotBars<TYPE>(label_id, xs, ys, count, bar_size, flags, offset, stride); \
    } \
    /* PlotBarGroups */ \
    void ImPlot_PlotBarGroups_##NAME(const char* const label_ids[], const TYPE* values, int item_count, int group_count, double group_size = 0.67, double shift = 0, ImPlotBarGroupsFlags flags = 0) { \
        ImPlot::PlotBarGroups<TYPE>(label_ids, values, item_count, group_count, group_size, shift, flags); \
    } \
    /* PlotErrorBars overloads */ \
    void ImPlot_PlotErrorBars_##NAME(const char* label_id, const TYPE* xs, const TYPE* ys, const TYPE* err, int count, ImPlotErrorBarsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotErrorBars<TYPE>(label_id, xs, ys, err, count, flags, offset, stride); \
    } \
    void ImPlot_PlotErrorBars_##NAME##_Binary(const char* label_id, const TYPE* xs, const TYPE* ys, const TYPE* neg, const TYPE* pos, int count, ImPlotErrorBarsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotErrorBars<TYPE>(label_id, xs, ys, neg, pos, count, flags, offset, stride); \
    } \
    /* PlotStems overloads */ \
    void ImPlot_PlotStems_##NAME(const char* label_id, const TYPE* values, int count, double ref = 0, double scale = 1, double start = 0, ImPlotStemsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotStems<TYPE>(label_id, values, count, ref, scale, start, flags, offset, stride); \
    } \
    void ImPlot_PlotStems_##NAME##_XY(const char* label_id, const TYPE* xs, const TYPE* ys, int count, double ref = 0, ImPlotStemsFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotStems<TYPE>(label_id, xs, ys, count, ref, flags, offset, stride); \
    } \
    /* PlotInfLines */ \
    void ImPlot_PlotInfLines_##NAME(const char* label_id, const TYPE* values, int count, ImPlotInfLinesFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotInfLines<TYPE>(label_id, values, count, flags, offset, stride); \
    } \
    /* PlotPieChart overloads */ \
    void ImPlot_PlotPieChart_##NAME(const char* const label_ids[], const TYPE* values, int count, double x, double y, double radius, ImPlotFormatter fmt, void* fmt_data = nullptr, double angle0 = 90, ImPlotPieChartFlags flags = 0) { \
        ImPlot::PlotPieChart<TYPE>(label_ids, values, count, x, y, radius, fmt, fmt_data, angle0, flags); \
    } \
    void ImPlot_PlotPieChart_##NAME##_Simple(const char* const label_ids[], const TYPE* values, int count, double x, double y, double radius, const char* label_fmt = "%.1f", double angle0 = 90, ImPlotPieChartFlags flags = 0) { \
        ImPlot::PlotPieChart<TYPE>(label_ids, values, count, x, y, radius, label_fmt, angle0, flags); \
    } \
    /* PlotHeatmap */ \
    void ImPlot_PlotHeatmap_##NAME(const char* label_id, const TYPE* values, int rows, int cols, double scale_min = 0, double scale_max = 0, const char* label_fmt = "%.1f", const ImPlotPoint& bounds_min = ImPlotPoint(0,0), const ImPlotPoint& bounds_max = ImPlotPoint(1,1), ImPlotHeatmapFlags flags = 0) { \
        ImPlot::PlotHeatmap<TYPE>(label_id, values, rows, cols, scale_min, scale_max, label_fmt, bounds_min, bounds_max, flags); \
    } \
    /* PlotHistogram */ \
    double ImPlot_PlotHistogram_##NAME(const char* label_id, const TYPE* values, int count, int bins = ImPlotBin_Sturges, double bar_scale = 1.0, ImPlotRange range = ImPlotRange(), ImPlotHistogramFlags flags = 0) { \
        return ImPlot::PlotHistogram<TYPE>(label_id, values, count, bins, bar_scale, range, flags); \
    } \
    double ImPlot_PlotHistogram2D_##NAME(const char* label_id, const TYPE* xs, const TYPE* ys, int count, int x_bins = ImPlotBin_Sturges, int y_bins = ImPlotBin_Sturges, ImPlotRect range = ImPlotRect(), ImPlotHistogramFlags flags = 0) { \
        return ImPlot::PlotHistogram2D<TYPE>(label_id, xs, ys, count, x_bins, y_bins, range, flags); \
    } \
    /* PlotDigital */ \
    void ImPlot_PlotDigital_##NAME(const char* label_id, const TYPE* xs, const TYPE* ys, int count, ImPlotDigitalFlags flags = 0, int offset = 0, int stride = sizeof(TYPE)) { \
        ImPlot::PlotDigital<TYPE>(label_id, xs, ys, count, flags, offset, stride); \
    }

// Implot converts all types to double before plotting.
// So there is no need to wrap all the types.
// Rust can convert other types to double (f64),
// before passing them to implot.

// DEFINE_PLOT_WRAPPERS(ImS8, ImS8)
// DEFINE_PLOT_WRAPPERS(ImU8, ImU8)
// DEFINE_PLOT_WRAPPERS(ImS16, ImS16)
// DEFINE_PLOT_WRAPPERS(ImU16, ImU16)
// DEFINE_PLOT_WRAPPERS(ImS32, ImS32)
// DEFINE_PLOT_WRAPPERS(ImU32, ImU32)
// DEFINE_PLOT_WRAPPERS(ImS64, ImS64)
// DEFINE_PLOT_WRAPPERS(ImU64, ImU64)
// DEFINE_PLOT_WRAPPERS(float, Float)
DEFINE_PLOT_WRAPPERS(double, Double)

#undef DEFINE_PLOT_WRAPPERS

#ifdef __cplusplus
}
#endif

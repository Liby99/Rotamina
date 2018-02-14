#include "viewer/component/ChannelEditor.h"

using namespace rotamina;

ChannelEditor::ChannelEditor(Widget *parent) : Widget(parent) {}

void ChannelEditor::draw(NVGcontext * ctx) {
    Widget::draw(ctx);
    drawAxis(ctx, 0, 10, -3, 3);
    drawKeyframe(ctx, 0.5, 0.5, false);
    nvgEndFrame(ctx);
}

void ChannelEditor::drawXAxis(NVGcontext * ctx, float perc, NVGcolor color) {
    nvgBeginPath(ctx);
    nvgRect(ctx, padding, mSize[1] * perc + offset + padding, mSize[0], 1);
    nvgFillColor(ctx, color);
    nvgFill(ctx);
}

void ChannelEditor::drawYAxis(NVGcontext * ctx, float perc, NVGcolor color) {
    nvgBeginPath(ctx);
    nvgRect(ctx, mSize[0] * perc + padding, offset + padding, 1, mSize[1]);
    nvgFillColor(ctx, color);
    nvgFill(ctx);
}

void ChannelEditor::drawXAxisText(NVGcontext * ctx, float perc, float f) {
    nvgFontSize(ctx, 16.0f);
    nvgFontFace(ctx, "sans-bold");
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgFillColor(ctx, nvgRGB(120, 120, 120));
    nvgText(ctx, mSize[0] * perc + 5 + padding, offset + padding + mSize[1] * 0.95, std::to_string(f).c_str(), NULL);
}

void ChannelEditor::drawYAxisText(NVGcontext * ctx, float perc, float f) {
    nvgFontSize(ctx, 16.0f);
    nvgFontFace(ctx, "sans-bold");
    nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
    nvgFillColor(ctx, nvgRGB(120, 120, 120));
    nvgText(ctx, mSize[0] * 0.1 + padding - 5, offset + padding + mSize[1] * perc - 5, std::to_string(f).c_str(), NULL);
}

void ChannelEditor::drawAxis(NVGcontext * ctx, float xmin, float xmax, float ymin, float ymax) {

    drawXAxis(ctx, 0.1, nvgRGB(100, 100, 100));
    drawXAxis(ctx, 0.3, nvgRGB(100, 100, 100));
    drawXAxis(ctx, 0.5, nvgRGB(150, 150, 150));
    drawXAxis(ctx, 0.7, nvgRGB(100, 100, 100));
    drawXAxis(ctx, 0.9, nvgRGB(100, 100, 100));

    drawXAxisText(ctx, 0.1, xmin);
    drawXAxisText(ctx, 0.3, xmin + (xmax - xmin) / 4);
    drawXAxisText(ctx, 0.5, xmin + (xmax - xmin) / 2);
    drawXAxisText(ctx, 0.7, xmin + (xmax - xmin) * 3 / 4);
    drawXAxisText(ctx, 0.9, xmax);

    drawYAxis(ctx, 0.1, nvgRGB(150, 150, 150));
    drawYAxis(ctx, 0.3, nvgRGB(100, 100, 100));
    drawYAxis(ctx, 0.5, nvgRGB(100, 100, 100));
    drawYAxis(ctx, 0.7, nvgRGB(100, 100, 100));
    drawYAxis(ctx, 0.9, nvgRGB(150, 150, 150));

    drawYAxisText(ctx, 0.9, ymin);
    drawYAxisText(ctx, 0.7, ymin + (ymax - ymin) / 4);
    drawYAxisText(ctx, 0.5, ymin + (ymax - ymin) / 2);
    drawYAxisText(ctx, 0.3, ymin + (ymax - ymin) * 3 / 4);
    drawYAxisText(ctx, 0.1, ymax);
}

void ChannelEditor::drawKeyframeBox(NVGcontext * ctx, float xp, float yp, bool selected) {
    nvgBeginPath(ctx);
    nvgRect(ctx, mSize[0] * xp + padding - 4, mSize[1] * yp + offset + padding - 4, 8, 8);
    nvgFillColor(ctx, nvgRGB(200, 200, 200));
    nvgFill(ctx);
}

void ChannelEditor::drawKeyframeHandlebar(NVGcontext * ctx, float xp, float yp, float xoff, float yoff) {
    nvgBeginPath(ctx);
    nvgMoveTo(ctx, mSize[0] * xp + padding, mSize[1] * yp + offset + padding);
    nvgLineTo(ctx, mSize[0] * xp + padding + xoff, mSize[1] * yp + offset + padding + yoff);
    nvgStrokeColor(ctx, nvgRGB(200, 200, 200));
    nvgStroke(ctx);

    nvgBeginPath(ctx);
    nvgCircle(ctx, mSize[0] * xp + padding + xoff, mSize[1] * yp + offset + padding + yoff, 3);
    nvgFillColor(ctx, nvgRGB(200, 200, 200));
    nvgFill(ctx);
}

void ChannelEditor::drawKeyframe(NVGcontext * ctx, float xp, float yp, bool selected) {
    drawKeyframeBox(ctx, xp, yp, false);
    drawKeyframeHandlebar(ctx, xp, yp, -50, -50);
    drawKeyframeHandlebar(ctx, xp, yp, 50, 50);
}
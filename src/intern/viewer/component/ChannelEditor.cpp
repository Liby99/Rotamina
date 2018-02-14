#include "viewer/component/ChannelEditor.h"

using namespace rotamina;

ChannelEditor::ChannelEditor(Widget *parent) : Widget(parent), channel(nullptr) {}

void ChannelEditor::setChannel(Channel * c) {
    this->channel = c;
}

void ChannelEditor::draw(NVGcontext * ctx) {
    Widget::draw(ctx);
    if (channel && channel->getKeyframeAmount()) {

        // First Draw the axis based on the keyframe
        if (channel->getKeyframeAmount() == 1) {
            Keyframe & k = channel->getKeyframe(0);
            float t = k.getTime();
            float v = k.getValue();
            drawAxis(ctx, t - 1, t + 1, v - 1, v + 1);
        }
        else {
            Keyframe & k0 = channel->getKeyframe(0);
            float vmin = k0.getValue(), vmax = k0.getValue();
            for (int i = 0; i < channel->getKeyframeAmount(); i++) {
                float v = channel->getKeyframe(i).getValue();
                if (v > vmax) vmax = v;
                if (v < vmin) vmin = v;
            }
            drawAxis(ctx, k0.getTime(), channel->getLastKeyframe().getTime(), vmin, vmax);
        }

        // Then draw the keyframes
        for (int i = 0; i < channel->getKeyframeAmount(); i++) {
            drawKeyframe(ctx, channel->getKeyframe(i));
        }

        // Finally draw the curve
        drawCurve(ctx);
    }
    else {
        drawAxis(ctx, -1, 1, -1, 1);
    }
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

    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;

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

void ChannelEditor::drawKeyframe(NVGcontext * ctx, Keyframe & k) {

    float xp = (k.getTime() - xmin) / (xmax - xmin) * 0.8 + 0.1;
    float yp = (k.getValue() - ymin) / (ymax - ymin) * 0.8 + 0.1;

    drawKeyframeBox(ctx, xp, yp, false);

    Eigen::Vector2f lh = { -1, -k.getInTangent() / ((ymax - ymin) / (mSize[1] / 8)) * ((xmax - xmin) / (mSize[0] / 8)) };
    Eigen::Vector2f rh = { 1, k.getOutTangent() / ((ymax - ymin) / (mSize[1] / 8)) * ((xmax - xmin) / (mSize[0] / 8)) };
    lh.normalize();
    rh.normalize();

    drawKeyframeHandlebar(ctx, xp, yp, lh[0] * 30, lh[1] * 30);
    drawKeyframeHandlebar(ctx, xp, yp, rh[0] * 30, rh[1] * 30);
}

void ChannelEditor::drawCurve(NVGcontext *ctx) {
    nvgBeginPath(ctx);
    float u = (xmax - xmin) / 8;
    float v = (ymax - ymin) / 8;
    float startx = xmin - u;
    float starty = channel->evaluate(startx);
    float dur = u * 10;
    float basey = ymin - v;
    float rangey = v * 10;
    nvgMoveTo(ctx, startx, starty);
    for (int i = 0; i < 200; i++) {
        float t = startx + i / 200.0f * dur;
        float y = channel->evaluate(t);
        int px = (t - startx) / dur * mSize[0] + padding;
        int py = (y - basey) / rangey * mSize[1] + offset + padding;
        nvgLineTo(ctx, px, py);
    }
    nvgStrokeColor(ctx, nvgRGB(200, 200, 200));
    nvgStroke(ctx);
}
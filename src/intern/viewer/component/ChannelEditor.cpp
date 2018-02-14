#include "viewer/component/ChannelEditor.h"

using namespace rotamina;

ChannelEditor::ChannelEditor(Widget *parent) : Widget(parent), channel(nullptr), currKeyframe(nullptr) {}

void ChannelEditor::setChannel(Channel * c) {
    this->currKeyframe = nullptr;
    this->channel = c;
}

Channel * ChannelEditor::getChannel() {
    return this->channel;
}

void ChannelEditor::setLinear() {
    if (currKeyframe) {
        currKeyframe->setInTangent(Keyframe::Tangent::Linear);
        currKeyframe->setOutTangent(Keyframe::Tangent::Linear);
    }
}

void ChannelEditor::setFlat() {
    if (currKeyframe) {
        currKeyframe->setInTangent(Keyframe::Tangent::Flat);
        currKeyframe->setOutTangent(Keyframe::Tangent::Flat);
    }
}

void ChannelEditor::setSmooth() {
    if (currKeyframe) {
        currKeyframe->setInTangent(Keyframe::Tangent::Smooth);
        currKeyframe->setOutTangent(Keyframe::Tangent::Smooth);
    }
}

void ChannelEditor::removeKeyframe() {
    if (currKeyframe) {
        channel->removeKeyframe(*currKeyframe);
        currKeyframe = nullptr;
        draggingKeyframe = nullptr;
    }
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

        // Then draw the curve
        drawCurve(ctx);

        // Finally draw the keyframes
        for (int i = 0; i < channel->getKeyframeAmount(); i++) {
            drawKeyframe(ctx, channel->getKeyframe(i));
        }
    }
    else {
        drawAxis(ctx, -1, 1, -1, 1);
    }
    nvgEndFrame(ctx);
}

bool ChannelEditor::mouseButtonEvent(const nanogui::Vector2i & p, int button, bool down, int modifiers) {
    if (channel) {
        for (int i = 0; i < channel->getKeyframeAmount(); i++) {
            Keyframe & k = channel->getKeyframe(i);
            float xp = (k.getTime() - xmin) / (xmax - xmin) * 0.8 + 0.1;
            float yp = (k.getValue() - ymin) / (ymax - ymin) * 0.8 + 0.1;
            int x = mSize[0] * xp + padding;
            int y = mSize[1] * (1 - yp) + offset + padding;
            float dist = sqrt(pow(x - p[0], 2) + pow(y - p[1], 2));
            if (dist < 7) {
                currKeyframe = &k;
                if (down) {
                    draggingKeyframe = &k;
                }
                else {
                    draggingKeyframe = nullptr;
                }
                return true;
            }

            Eigen::Vector2f lh = { -1, k.getInTangent() / ((ymax - ymin) / (mSize[1] / 8)) * ((xmax - xmin) / (mSize[0] / 8)) };
            Eigen::Vector2f rh = { 1, -k.getOutTangent() / ((ymax - ymin) / (mSize[1] / 8)) * ((xmax - xmin) / (mSize[0] / 8)) };
            lh.normalize();
            rh.normalize();

            float lxoff = lh[0] * 30, lyoff = lh[1] * 30, rxoff = rh[0] * 30, ryoff = rh[1] * 30;
            int lx = x + lxoff;
            int ly = y + lyoff;
            dist = sqrt(pow(lx - p[0], 2) + pow(ly - p[1], 2));
            if (dist < 5) {
                currKeyframe = &k;
                return true;
            }

            int rx = x + rxoff;
            int ry = y + ryoff;
            dist = sqrt(pow(rx - p[0], 2) + pow(ry - p[1], 2));
            if (dist < 5) {
                currKeyframe = &k;
                return true;
            }
        }

        if (down) {
            float xp = float(p[0] - padding) / float(mSize[0]);
            float yp = 1 - float(p[1] - padding - offset) / float(mSize[1]);
            float t = (xp - 0.1) / 0.8 * (xmax - xmin) + xmin;
            float v = (yp - 0.1) / 0.8 * (ymax - ymin) + ymin;
            channel->addKeyframe(t, v);
            return true;
        }
    }
    return false;
}

bool ChannelEditor::mouseDragEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) {
    if (draggingKeyframe) {
        float xp = float(rel[0]) / float(mSize[0]);
        float yp = float(rel[1]) / float(mSize[1]);
        float dt = xp / 0.8 * (xmax - xmin);
        float dv = yp / 0.8 * (ymax - ymin);
        float nt = draggingKeyframe->getTime() + dt;
        float nv = draggingKeyframe->getValue() - dv;
        if (draggingKeyframe->hasNext()) {
            nt = std::min(nt, draggingKeyframe->getNext().getTime() - 0.01f);
        }
        if (draggingKeyframe->hasPrev()) {
            nt = std::max(nt, draggingKeyframe->getPrev().getTime() + 0.01f);
        }
        draggingKeyframe->setTime(nt);
        draggingKeyframe->setValue(nv);
        return true;
    }
    return false;
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
    auto c = selected ? nvgRGB(255, 255, 0) : nvgRGB(200, 200, 200);
    nvgBeginPath(ctx);
    nvgRect(ctx, mSize[0] * xp + padding - 4, mSize[1] * (1 - yp) + offset + padding - 4, 8, 8);
    nvgFillColor(ctx, c);
    nvgFill(ctx);
}

void ChannelEditor::drawKeyframeHandlebar(NVGcontext * ctx, float xp, float yp, float xoff, float yoff, bool selected) {
    auto c = selected ? nvgRGB(255, 255, 0) : nvgRGB(200, 200, 200);
    nvgBeginPath(ctx);
    nvgMoveTo(ctx, mSize[0] * xp + padding, mSize[1] * (1 - yp) + offset + padding);
    nvgLineTo(ctx, mSize[0] * xp + padding + xoff, mSize[1] * (1 - yp) + offset + padding + yoff);
    nvgStrokeColor(ctx, c);
    nvgStroke(ctx);

    nvgBeginPath(ctx);
    nvgCircle(ctx, mSize[0] * xp + padding + xoff, mSize[1] * (1 - yp) + offset + padding + yoff, 3);
    nvgFillColor(ctx, c);
    nvgFill(ctx);
}

void ChannelEditor::drawKeyframe(NVGcontext * ctx, Keyframe & k) {

    float xp = (k.getTime() - xmin) / (xmax - xmin) * 0.8 + 0.1;
    float yp = (k.getValue() - ymin) / (ymax - ymin) * 0.8 + 0.1;

    drawKeyframeBox(ctx, xp, yp, currKeyframe == &k);

    Eigen::Vector2f lh = { -1, k.getInTangent() / ((ymax - ymin) / (mSize[1] / 8)) * ((xmax - xmin) / (mSize[0] / 8)) };
    Eigen::Vector2f rh = { 1, -k.getOutTangent() / ((ymax - ymin) / (mSize[1] / 8)) * ((xmax - xmin) / (mSize[0] / 8)) };
    lh.normalize();
    rh.normalize();

    drawKeyframeHandlebar(ctx, xp, yp, lh[0] * 30, lh[1] * 30, currKeyframe == &k);
    drawKeyframeHandlebar(ctx, xp, yp, rh[0] * 30, rh[1] * 30, currKeyframe == &k);
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
        int py = (1 - (y - basey) / rangey) * mSize[1] + offset + padding;
        nvgLineTo(ctx, px, py);
    }
    nvgStrokeColor(ctx, nvgRGB(200, 200, 200));
    nvgStroke(ctx);
}
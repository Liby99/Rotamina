#include "viewer/component/ChannelEditor.h"

using namespace rotamina;

ChannelEditor::ChannelEditor(Widget *parent) :
    Widget(parent), channel(nullptr), currTime(0),
    currKeyframe(nullptr), draggingKeyframe(nullptr),
    draggingInHandle(false), draggingOutHandle(false) {}

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

void ChannelEditor::setCurrTime(float t) {
    this->currTime = t;
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
        
        //
        drawCurrTime(ctx);
    }
    else {
        drawAxis(ctx, -1, 1, -1, 1);
    }
    nvgEndFrame(ctx);
}

bool ChannelEditor::mouseButtonEvent(const nanogui::Vector2i & p, int button, bool down, int modifiers) {
    if (channel) {
        for (int i = 0; i < channel->getKeyframeAmount(); i++) {
            
            // Cache the keyframe
            Keyframe & k = channel->getKeyframe(i);
            float ratio = ((ymax - ymin) / mSize[1]) / ((xmax - xmin) / mSize[0]);
            
            // Check if the mouse touch the keyframe box
            float xp = (k.getTime() - xmin) / (xmax - xmin) * 0.8 + 0.1;
            float yp = (k.getValue() - ymin) / (ymax - ymin) * 0.8 + 0.1;
            int x = mSize[0] * xp + padding;
            int y = mSize[1] * (1 - yp) + offset + padding;
            float dist = sqrt(pow(x - p[0], 2) + pow(y - p[1], 2));
            if (dist < 8) {
                currKeyframe = &k;
                if (down) {
                    draggingKeyframe = &k;
                    draggingInHandle = false;
                    draggingOutHandle = false;
                }
                else {
                    draggingKeyframe = nullptr;
                }
                return true;
            }
            
            // Check if the mouse touches the left handle
            Eigen::Vector2f lh = { -1, k.getInTangent() / ratio };
            lh.normalize();
            float lxoff = lh[0] * 30, lyoff = lh[1] * 30;
            int lx = x + lxoff;
            int ly = y + lyoff;
            dist = sqrt(pow(lx - p[0], 2) + pow(ly - p[1], 2));
            if (dist < 6) {
                currKeyframe = &k;
                if (down) {
                    draggingKeyframe = &k;
                    draggingInHandle = true;
                    draggingOutHandle = false;
                }
                else {
                    draggingKeyframe = nullptr;
                    draggingInHandle = false;
                }
                return true;
            }
            
            // Check if the mouse touches the right handle
            Eigen::Vector2f rh = { 1, -k.getOutTangent() / ratio };
            rh.normalize();
            float rxoff = rh[0] * 30, ryoff = rh[1] * 30;
            int rx = x + rxoff;
            int ry = y + ryoff;
            dist = sqrt(pow(rx - p[0], 2) + pow(ry - p[1], 2));
            if (dist < 6) {
                currKeyframe = &k;
                if (down) {
                    draggingKeyframe = &k;
                    draggingOutHandle = true;
                    draggingInHandle = false;
                }
                else {
                    draggingKeyframe = nullptr;
                    draggingOutHandle = false;
                }
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

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

float ChannelEditor::getNewSlope(Eigen::Vector2f handle, const Eigen::Vector2i & rel) {
    handle.normalize();
    handle *= 30;
    handle[0] += rel[0];
    handle[1] += rel[1];
    if (abs(handle[0]) <= 0.5) {
        handle[0] = sgn(handle[0]) * 0.5;
    }
    handle.normalize();
    handle /= abs(handle[0]);
    return handle[1];
}

bool ChannelEditor::mouseDragEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) {
    if (draggingKeyframe) {
        float ratio = ((ymax - ymin) / mSize[1]) / ((xmax - xmin) / mSize[0]);
        if (draggingInHandle) {
            draggingKeyframe->setConsistent(false);
            draggingKeyframe->setInTangent(getNewSlope({ -1, draggingKeyframe->getInTangent() / ratio }, rel) * ratio);
        }
        else if (draggingOutHandle) {
            draggingKeyframe->setConsistent(false);
            draggingKeyframe->setOutTangent(-getNewSlope({ 1, -draggingKeyframe->getOutTangent() / ratio }, rel) * ratio);
        }
        else {
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
    
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << f;
    std::string s = stream.str();
    
    nvgFontSize(ctx, 16.0f);
    nvgFontFace(ctx, "sans-bold");
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgFillColor(ctx, nvgRGB(120, 120, 120));
    nvgText(ctx, mSize[0] * perc + 5 + padding, offset + padding + mSize[1] * 0.95, s.c_str(), NULL);
}

void ChannelEditor::drawYAxisText(NVGcontext * ctx, float perc, float f) {
    
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << f;
    std::string s = stream.str();
    
    nvgFontSize(ctx, 16.0f);
    nvgFontFace(ctx, "sans-bold");
    nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
    nvgFillColor(ctx, nvgRGB(120, 120, 120));
    nvgText(ctx, mSize[0] * 0.1 + padding - 5, offset + padding + mSize[1] * perc - 5, s.c_str(), NULL);
}

void ChannelEditor::drawAxis(NVGcontext * ctx, float xmin, float xmax, float ymin, float ymax) {

    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
    
    drawXAxis(ctx, 0.1, nvgRGB(150, 150, 150));
    drawXAxis(ctx, 0.3, nvgRGB(60, 60, 60));
    drawXAxis(ctx, 0.5, nvgRGB(60, 60, 60));
    drawXAxis(ctx, 0.7, nvgRGB(60, 60, 60));
    drawXAxis(ctx, 0.9, nvgRGB(150, 150, 150));

    // drawXAxisText(ctx, 0.1, xmin);
    // drawXAxisText(ctx, 0.3, xmin + (xmax - xmin) / 4);
    // drawXAxisText(ctx, 0.5, xmin + (xmax - xmin) / 2);
    // drawXAxisText(ctx, 0.7, xmin + (xmax - xmin) * 3 / 4);
    // drawXAxisText(ctx, 0.9, xmax);
    
    float expectWidth = 100;
    int amount = floor(mSize[0] * 0.8 / expectWidth);
    float step = 0.8 / amount;
    drawYAxis(ctx, 0.1, nvgRGB(150, 150, 150));
    drawXAxisText(ctx, 0.1, xmin);
    for (float x = 0.1 + step; x <= 0.9 - step; x += step) {
        drawYAxis(ctx, x, nvgRGB(60, 60, 60));
        drawXAxisText(ctx, x, xmin + (x - 0.1) / 0.8 * (xmax - xmin));
    }
    drawYAxis(ctx, 0.9, nvgRGB(150, 150, 150));
    drawXAxisText(ctx, 0.9, xmax);

    // drawYAxis(ctx, 0.1, nvgRGB(150, 150, 150));
    // drawYAxis(ctx, 0.3, nvgRGB(60, 60, 60));
    // drawYAxis(ctx, 0.5, nvgRGB(60, 60, 60));
    // drawYAxis(ctx, 0.7, nvgRGB(60, 60, 60));
    // drawYAxis(ctx, 0.9, nvgRGB(150, 150, 150));

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

void ChannelEditor::drawCurrTime(NVGcontext * ctx) {
    float d = xmax - xmin, t = fmod(currTime - xmin, d), xp = t / (xmax - xmin) * 0.8 + 0.1;
    drawYAxis(ctx, xp, nvgRGB(200, 30, 0));
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

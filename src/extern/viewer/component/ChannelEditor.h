#ifndef CHANNEL_EDITOR_H
#define CHANNEL_EDITOR_H

#include <iomanip>
#include <sstream>
#include <nanogui/nanogui.h>
#include "animation/Channel.h"

namespace rotamina {
    class ChannelEditor : public nanogui::Widget {
    protected:
        int padding = 5;
        int offset = 30;
        float xmin, xmax, ymin, ymax, currTime;
        Channel * channel;
        Keyframe * currKeyframe;
        Keyframe * draggingKeyframe;
        bool draggingInHandle;
        bool draggingOutHandle;
    public:
        ChannelEditor(Widget * parent);
        void setChannel(Channel *);
        Channel * getChannel();
        void setLinear();
        void setFlat();
        void setSmooth();
        void removeKeyframe();
        void setCurrTime(float);
        virtual void draw(NVGcontext * ctx) override;
        virtual bool mouseButtonEvent(const nanogui::Vector2i &p, int button, bool down, int modifiers) override;
        virtual bool mouseDragEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) override;
    protected:
        float getNewSlope(Eigen::Vector2f handle, const Eigen::Vector2i & rel);
        void drawXAxis(NVGcontext * ctx, float perc, NVGcolor color);
        void drawYAxis(NVGcontext * ctx, float perc, NVGcolor color);
        void drawXAxisText(NVGcontext * ctx, float perc, float f);
        void drawYAxisText(NVGcontext * ctx, float perc, float f);
        void drawAxis(NVGcontext * ctx, float xmin, float xmax, float ymin, float ymax);
        void drawKeyframeBox(NVGcontext * ctx, float xp, float yp, bool selected);
        void drawKeyframeHandlebar(NVGcontext * ctx, float xp, float yp, float xoff, float yoff, bool selected);
        void drawKeyframe(NVGcontext * ctx, Keyframe &);
        void drawCurrTime(NVGcontext *);
        void drawCurve(NVGcontext * ctx);
    };
}

#endif

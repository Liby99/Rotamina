#ifndef CHANNEL_EDITOR_H
#define CHANNEL_EDITOR_H

#include <nanogui/nanogui.h>
#include "animation/Channel.h"

namespace rotamina {
    class ChannelEditor : public nanogui::Widget {
        protected:
            int padding = 5;
            int offset = 30;
            Channel * channel;
        public:
            ChannelEditor(Widget * parent);
            virtual void draw(NVGcontext * ctx) override;
        protected:
            void drawXAxis(NVGcontext * ctx, float perc, NVGcolor color);
            void drawYAxis(NVGcontext * ctx, float perc, NVGcolor color);
            void drawXAxisText(NVGcontext * ctx, float perc, float f);
            void drawYAxisText(NVGcontext * ctx, float perc, float f);
            void drawAxis(NVGcontext * ctx, float xmin, float xmax, float ymin, float ymax);
            void drawKeyframeBox(NVGcontext * ctx, float xp, float yp, bool selected);
            void drawKeyframeHandlebar(NVGcontext * ctx, float xp, float yp, float xoff, float yoff);
            void drawKeyframe(NVGcontext * ctx, float xp, float yp, bool selected);
    };
}

#endif

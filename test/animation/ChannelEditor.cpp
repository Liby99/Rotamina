#include "animation/Channel.h"
#include <nanogui/nanogui.h>

using namespace rotamina;

class ChannelEditor : public nanogui::Widget {
public:
    
    bool fontsLoaded;
    
    int padding = 5;
    int offset = 30;
    
    Channel * channel;
    
    ChannelEditor(nanogui::Widget * parent, Channel & c) : Widget(parent), fontsLoaded(false) {
        channel = &c;
        mSize = nanogui::Vector2i(250, 250);
    }
    
    int loadFonts(NVGcontext * ctx) {
        int font;
        font = nvgCreateFont(ctx, "sans", "./res/rotamina/fonts/Roboto-Regular.ttf");
        if (font == -1) {
            printf("Could not add font regular.\n");
            return -1;
        }
        font = nvgCreateFont(ctx, "sans-bold", "./res/rotamina/fonts/Roboto-Bold.ttf");
        if (font == -1) {
            printf("Could not add font bold.\n");
            return -1;
        }
        return 0;
    }
    
    void drawXAxis(NVGcontext * ctx, float perc, NVGcolor color) {
        nvgBeginPath(ctx);
        nvgRect(ctx, padding, mSize[1] * perc + offset + padding, mSize[0], 1);
        nvgFillColor(ctx, color);
        nvgFill(ctx);
    }
    
    void drawYAxis(NVGcontext * ctx, float perc, NVGcolor color) {
        nvgBeginPath(ctx);
        nvgRect(ctx, mSize[0] * perc + padding, offset + padding, 1, mSize[1]);
        nvgFillColor(ctx, color);
        nvgFill(ctx);
    }
    
    void drawXAxisText(NVGcontext * ctx, float perc, float f) {
        nvgFontSize(ctx, 16.0f);
        nvgFontFace(ctx, "sans-bold");
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgFillColor(ctx, nvgRGB(120, 120, 120));
        nvgText(ctx, mSize[0] * perc + 5 + padding, offset + padding + mSize[1] * 0.95, std::to_string(f).c_str(), NULL);
    }
    
    void drawYAxisText(NVGcontext * ctx, float perc, float f) {
        nvgFontSize(ctx, 16.0f);
        nvgFontFace(ctx, "sans-bold");
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
        nvgFillColor(ctx, nvgRGB(120, 120, 120));
        nvgText(ctx, mSize[0] * 0.1 + padding - 5, offset + padding + mSize[1] * perc - 5, std::to_string(f).c_str(), NULL);
    }
    
    void drawAxis(NVGcontext * ctx, float xmin, float xmax, float ymin, float ymax) {
        
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
    
    void drawKeyframeBox(NVGcontext * ctx, float xp, float yp, bool selected) {
        nvgBeginPath(ctx);
        nvgRect(ctx, mSize[0] * xp + padding - 4, mSize[1] * yp + offset + padding - 4, 8, 8);
        nvgFillColor(ctx, nvgRGB(200, 200, 200));
        nvgFill(ctx);
    }
    
    void drawKeyframeHandlebar(NVGcontext * ctx, float xp, float yp, float xoff, float yoff) {
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
    
    void drawKeyframe(NVGcontext * ctx, float xp, float yp, bool selected) {
        drawKeyframeBox(ctx, xp, yp, false);
        drawKeyframeHandlebar(ctx, xp, yp, -50, -50);
        drawKeyframeHandlebar(ctx, xp, yp, 50, 50);
    }
    
    virtual void draw(NVGcontext * ctx) override {
        Widget::draw(ctx);
        
        if (!fontsLoaded) {
            loadFonts(ctx);
            fontsLoaded = true;
        }
        
        drawAxis(ctx, 0, 10, -3, 3);
        
        drawKeyframe(ctx, 0.5, 0.5, false);
        
        nvgEndFrame(ctx);
    }
};

class ChannelViewer : public nanogui::Screen {
public:
    
    Channel * channel;
    
    nanogui::Window * channelEditorWindow;
    ChannelEditor * channelEditor;
    
    ChannelViewer(int w, int h, Channel & c, std::string name) : nanogui::Screen(Eigen::Vector2i(w, h), name, false) {
        
        this->channel = &c;
        
        using namespace nanogui;
        
        setBackground({ 30, 30, 30, 255 });
        
        channelEditorWindow = new Window(this, "Channel Editor");
        channelEditorWindow->setLayout(new GroupLayout(5));
        
        channelEditor = new ChannelEditor(channelEditorWindow, c);
        channelEditor->setSize({ w - 10, 300 });
        
        performLayout();
    }
};

int main() {
    nanogui::init();
    
    Channel c;
    
    // Initiate Viewer
    ChannelViewer viewer = ChannelViewer(1600, 960, c, "Channel Viewer");
    viewer.drawAll();
    viewer.setVisible(true);
    
    nanogui::mainloop();
    nanogui::shutdown();
}

#include <iostream>
#include "viewer/CharAnimViewer.h"

using namespace rotamina;

const int CharAnimViewer::SKELETON_VIEWER_WIDTH = 300;
const int CharAnimViewer::JOINT_VIEWER_WIDTH= 300;
const int CharAnimViewer::CHANNEL_EDITOR_HEIGHT = 300;

CharAnimViewer::CharAnimViewer(int w, int h, std::string n, CharacterAnimator & ca) : AnimationViewer(w, h, n, ca) {

    // First initiate the object to draw
    this->characterAnimator = &ca;

    // Then initialize the UI
    using namespace nanogui;

    // First reset the parent windows
    {
        int centerWidth = w - SKELETON_VIEWER_WIDTH - JOINT_VIEWER_WIDTH;
        sceneViewer->setPosition({ SKELETON_VIEWER_WIDTH, sceneViewer->position()[1] });
        scene->setHeight(scene->getHeight() - CHANNEL_EDITOR_HEIGHT - 2 * PADDING);
        scene->setWidth(centerWidth - 2 * PADDING);
        animationControlWindow->setPosition({ SKELETON_VIEWER_WIDTH, animationControlWindow->position()[1] - CHANNEL_EDITOR_HEIGHT });
        animationControlWindow->setFixedWidth(centerWidth);
    }

    // Then setup the skeleton viewer
    {
        int height = h - CHANNEL_EDITOR_HEIGHT;
        skeletonViewer = new Window(this, "Skeleton Viewer");
        skeletonViewer->setFixedSize({ SKELETON_VIEWER_WIDTH, height });
        skeletonViewer->setPosition({ 0, 0 });
        skeletonViewer->setLayout(new GroupLayout(0));
        VScrollPanel * scrollPanel = new VScrollPanel(skeletonViewer);
        scrollPanel->setFixedSize({ SKELETON_VIEWER_WIDTH, height - HEADER_HEIGHT });
        Widget * outer = new Widget(scrollPanel);
        outer->setLayout(new GroupLayout(10));

        Animation & a = ca.getAnimation();
        Character & c = ca.getCharacter();
        Skeleton & s = c.getSkeleton();

        Widget * positionLabel = new Widget(outer);
        positionLabel->setLayout(new GridLayout(Orientation::Horizontal, 1, Alignment::Fill, 0, 5));
        new Label(positionLabel, "Position");

        Widget * positionBtns = new Widget(outer);
        positionBtns->setLayout(new GridLayout(Orientation::Horizontal, 3, Alignment::Fill, 0, 5));
        for (int i = 0; i < 3; i++) {
            Button * posBtn = new Button(positionBtns, std::string(1, char('X' + i)));
            posBtn->setFlags(Button::RadioButton);
            posBtn->setFontSize(14);
            dofButtonGroup.push_back(posBtn);
            Channel * c = &a.getChannel(i);
            posBtn->setCallback([this, c] () {
                this->showChannel(c);
            });
        }

        Widget * jointList = new Widget(outer);
        jointList->setLayout(new GridLayout(Orientation::Horizontal, 2, Alignment::Fill, 0, 5));

        new Label(jointList, "Joint");
        new Label(jointList, "DOFs");

        int counter = 3;
        for (int i = 0; i < s.jointAmount(); i++) {
            Joint * j = &(s.getJoint(i));
            Button * btn = new Button(jointList, j->getName());
            btn->setCallback([this, j] () {
                this->showJoint(j);
            });
            jointButtonGroup.push_back(btn);
            btn->setFlags(Button::RadioButton);
            btn->setFontSize(14);
            auto dofs = j->getDOFs();
            Widget * dofBtns = new Widget(jointList);
            dofBtns->setLayout(new GridLayout(Orientation::Horizontal, dofs.size(), Alignment::Fill));
            for (auto p : dofs) {
                Button * dofBtn = new Button(dofBtns, p.first);
                dofBtn->setFlags(Button::RadioButton);
                dofBtn->setFontSize(14);
                dofButtonGroup.push_back(dofBtn);
                Channel * c = &(a.getChannel(counter));
                dofBtn->setCallback([this, c, btn] () {
                    this->push(btn);
                    this->showChannel(c);
                });
                counter++;
            }
        }
        for (Button * btn : jointButtonGroup) {
            btn->setButtonGroup(jointButtonGroup);
        }
        for (Button * btn : dofButtonGroup) {
            btn->setButtonGroup(dofButtonGroup);
        }
    }

    // Finally setup the joint viewer
    {
        jointViewer = new Window(this, "Joint Viewer");
        jointViewer->setFixedSize({ JOINT_VIEWER_WIDTH, h - CHANNEL_EDITOR_HEIGHT });
        jointViewer->setPosition({ w - JOINT_VIEWER_WIDTH, 0 });

        jointViewer->setLayout(new GroupLayout());
        showJoint(&ca.getCharacter().getSkeleton().getRoot());
    }

    // Then setup the channel editor
    {
        channelEditorWindow = new Window(this, "Channel Editor");
        channelEditorWindow->setFixedSize({ w, CHANNEL_EDITOR_HEIGHT });
        channelEditorWindow->setPosition({ 0, h - CHANNEL_EDITOR_HEIGHT });
        channelEditorWindow->setLayout(new GroupLayout(15));
        
        int cw = w - 2 * PADDING;
        int iw = cw / 3 - 20;
        
        editor = new ChannelEditor(channelEditorWindow);
        editor->setSize({ cw, CHANNEL_EDITOR_HEIGHT - HEADER_HEIGHT - 45 - 2 * PADDING });
        
        Widget * channelControl = new Widget(channelEditorWindow);
        channelControl->setLayout(new GridLayout(Orientation::Horizontal, 3, Alignment::Fill));
        channelControl->setFixedWidth(cw);
        
        Widget * left = new Widget(channelControl);
        left->setLayout(new GridLayout(Orientation::Horizontal, 1, Alignment::Minimum));
        left->setFixedWidth(iw);
        
        Widget * leftChannelControl = new Widget(left);
        leftChannelControl->setLayout(new BoxLayout(Orientation::Horizontal, Alignment::Fill));
        Button * inConstant = new Button(leftChannelControl, "Constant");
        inConstant->setFlags(Button::RadioButton);
        inConstant->setFontSize(14);
        Button * inLinear = new Button(leftChannelControl, "Linear");
        inLinear->setFlags(Button::RadioButton);
        inLinear->setFontSize(14);
        Button * inCycle = new Button(leftChannelControl, "Cycle");
        inCycle->setFlags(Button::RadioButton);
        inCycle->setFontSize(14);
        Button * inCycleOffset = new Button(leftChannelControl, "Cycle Offset");
        inCycleOffset->setFlags(Button::RadioButton);
        inCycleOffset->setFontSize(14);
        Button * inBounce = new Button(leftChannelControl, "Bounce");
        inBounce->setFlags(Button::RadioButton);
        inBounce->setFontSize(14);
        
        inConstant->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setInExtrapolation(Channel::Extrapolation::Constant);
            }
        });
        inLinear->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setInExtrapolation(Channel::Extrapolation::Linear);
            }
        });
        inCycle->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setInExtrapolation(Channel::Extrapolation::Cycle);
            }
        });
        inCycleOffset->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setInExtrapolation(Channel::Extrapolation::CycleOffset);
            }
        });
        inBounce->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setInExtrapolation(Channel::Extrapolation::Bounce);
            }
        });

        Widget * middle = new Widget(channelControl);
        middle->setLayout(new GridLayout(Orientation::Horizontal, 1, Alignment::Middle));
        middle->setFixedWidth(iw);

        Widget * middleKeyframeControl = new Widget(middle);
        middleKeyframeControl->setLayout(new BoxLayout(Orientation::Horizontal, Alignment::Fill));
        Button * keyFlat = new Button(middleKeyframeControl, "Flat");
        keyFlat->setFontSize(14);
        keyFlat->setCallback([this] () {
            editor->setFlat();
        });
        Button * keyLinear = new Button(middleKeyframeControl, "Linear");
        keyLinear->setFontSize(14);
        keyLinear->setCallback([this] () {
            editor->setLinear();
        });
        Button * keySmooth = new Button(middleKeyframeControl, "Smooth");
        keySmooth->setFontSize(14);
        keySmooth->setCallback([this] () {
            editor->setSmooth();
        });
        
        // Button * keyConsistent = new Button(middleKeyframeControl, "Is Consistent");
        // keyConsistent->setFlags(Button::ToggleButton);
        // keyConsistent->setFontSize(14);
        // keyConsistent->setChangeCallback([this] (bool b) {
        //     editor->setConsistent(b);
        // });
        
        Button * keyRemove = new Button(middleKeyframeControl, "Remove");
        keyRemove->setBackgroundColor(Color(200, 0, 0, 100));
        keyRemove->setFontSize(14);
        keyRemove->setCallback([this] () {
            editor->removeKeyframe();
        });

        Widget * right = new Widget(channelControl);
        right->setLayout(new GridLayout(Orientation::Horizontal, 1, Alignment::Maximum));
        right->setFixedWidth(iw);

        Widget * rightChannelControl = new Widget(right);
        rightChannelControl->setLayout(new BoxLayout(Orientation::Horizontal, Alignment::Fill));
        Button * outConstant = new Button(rightChannelControl, "Constant");
        outConstant->setFlags(Button::RadioButton);
        outConstant->setFontSize(14);
        Button * outLinear = new Button(rightChannelControl, "Linear");
        outLinear->setFlags(Button::RadioButton);
        outLinear->setFontSize(14);
        Button * outCycle = new Button(rightChannelControl, "Cycle");
        outCycle->setFlags(Button::RadioButton);
        outCycle->setFontSize(14);
        Button * outCycleOffset = new Button(rightChannelControl, "Cycle Offset");
        outCycleOffset->setFlags(Button::RadioButton);
        outCycleOffset->setFontSize(14);
        Button * outBounce = new Button(rightChannelControl, "Bounce");
        outBounce->setFlags(Button::RadioButton);
        outBounce->setFontSize(14);

        outConstant->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setOutExtrapolation(Channel::Extrapolation::Constant);
            }
        });
        outLinear->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setOutExtrapolation(Channel::Extrapolation::Linear);
            }
        });
        outCycle->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setOutExtrapolation(Channel::Extrapolation::Cycle);
            }
        });
        outCycleOffset->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setOutExtrapolation(Channel::Extrapolation::CycleOffset);
            }
        });
        outBounce->setCallback([this] () {
            if (this->editor->getChannel()) {
                this->editor->getChannel()->setOutExtrapolation(Channel::Extrapolation::Bounce);
            }
        });
    }

    performLayout();
}

void CharAnimViewer::displayCallback() {
    AnimationViewer::displayCallback();
    showJoint(currJoint);
    editor->setCurrTime(characterAnimator->duration());
}

void CharAnimViewer::push(nanogui::Button * btn) {
    for (auto b : btn->buttonGroup()) {
        b->setPushed(false);
    }
    btn->setPushed(true);
    btn->callback()();
}

void CharAnimViewer::showChannel(Channel * c) {
    editor->setChannel(c);
    for (int i = 0; i < 5; i++) {
        nanogui::Button * inButton = (nanogui::Button *) channelEditorWindow->childAt(1)->childAt(0)->childAt(0)->childAt(i);
        nanogui::Button * outButton = (nanogui::Button *) channelEditorWindow->childAt(1)->childAt(2)->childAt(0)->childAt(i);
        if (i == c->getInExtrapolation()) inButton->setPushed(true);
        else inButton->setPushed(false);
        if (i == c->getOutExtrapolation()) outButton->setPushed(true);
        else outButton->setPushed(false);
    }
}

void CharAnimViewer::clearJointInfo() {
    int count = jointViewer->childCount();
    for (int i = 0; i < count; i++) {
        jointViewer->removeChild(0);
    }
    performLayout();
}

void CharAnimViewer::showJoint(Joint * joint) {

    currJoint = joint;

    clearJointInfo();

    using namespace nanogui;

    // Title and Joint Type
    Label * l = new Label(jointViewer, joint->getName());
    l->setFontSize(24);
    l->setFont("sans-bold");
    l = new Label(jointViewer, "Type: " + joint->getJointType());
    l->setFontSize(18);

    // DOFS
    auto dofs = joint->getDOFs();
    l = new Label(jointViewer, "Degrees of Freedom (" + std::to_string(dofs.size()) + ")");
    l->setFontSize(18);
    if (dofs.size() > 0) {
        Widget * w = new Widget(jointViewer);
        GridLayout * layout = new GridLayout(Orientation::Horizontal, 2, Alignment::Maximum, 0, 5);
        layout->setMargin(5);
        layout->setColAlignment({ Alignment::Maximum, Alignment::Fill });
        layout->setSpacing(0, 10);
        w->setLayout(layout);
        for (auto dp : dofs) {
            DOF * dof = dp.second;
            new Label(w, dp.first + " :", "sans-bold");
            new Label(w, std::to_string(dof->getValue()) + " rad");
        }
    }

    // Variables
    auto vars = joint->getVars();
    l = new Label(jointViewer, "Variables (" + std::to_string(vars.size()) + ")");
    l->setFontSize(18);
    if (vars.size() > 0) {
        Widget * w = new Widget(jointViewer);
        GridLayout * layout = new GridLayout(Orientation::Horizontal, 2, Alignment::Maximum, 0, 5);
        layout->setMargin(5);
        layout->setColAlignment({ Alignment::Maximum, Alignment::Fill });
        layout->setSpacing(0, 10);
        w->setLayout(layout);
        for (auto var : vars) {
            l = new Label(w, var.first + " :", "sans-bold");
            l = new Label(w, var.second);
            l->setFixedWidth(200);
        }
    }

    performLayout();
}

#include "animation/AnimationParser.h"

using namespace rotamina;

void AnimationParser::load(Animation & a, const std::string & f) {
    
    // Open the file
    Tokenizer t;
    t.open(f.c_str());
    
    t.findToken("animation");
    loadAnimation(a, t);
    
    // Close the file
    t.close();
}

void AnimationParser::loadAnimation(Animation & a, Tokenizer & t) {
    char temp[BUF_SIZE];
    t.findToken("{");
    int channelIndex = -1, channelAmount = -1;
    while (!t.isEOF()) {
        t.getToken(temp);
        if (!strcmp(temp, "range")) {
            a.setStartTime(t.getFloat());
            a.setEndTime(t.getFloat());
        }
        else if (!strcmp(temp, "numchannels")) {
            channelAmount = t.getInt();
            a.initiateChannels(channelAmount);
        }
        else if (!strcmp(temp, "channel")) {
            if (channelAmount == -1) {
                throw std::invalid_argument("Error parsing the animation. Parsing channel before amount is specified");
            }
            else {
                channelIndex++;
                loadChannel(a.getChannel(channelIndex), t);
            }
        }
        else if (!strcmp(temp, "}")) {
            return;
        }
    }
}

void AnimationParser::loadChannel(Channel & c, Tokenizer & t) {
    char temp[BUF_SIZE];
    t.findToken("{");
    while (!t.isEOF()) {
        t.getToken(temp);
        if (!strcmp(temp, "extrapolate")) {
            c.setInExtrapolation(getExtrapolation(t));
            c.setOutExtrapolation(getExtrapolation(t));
        }
        else if (!strcmp(temp, "keys")) {
            int keyAmount = t.getInt();
            c.initiateKeyframes(keyAmount);
            t.findToken("{");
            for (int i = 0; i < keyAmount; i++) {
                loadKeyframe(c.getKeyframe(i), t);
            }
            t.findToken("}");
        }
        else if (!strcmp(temp, "}")) {
            return;
        }
    }
}

void AnimationParser::loadKeyframe(Keyframe & k, Tokenizer & t) {
    
    // First set time and value
    k.setTime(t.getFloat());
    k.setValue(t.getFloat());
    
    // Then set consistent to false
    k.setConsistent(false);
    
    // Get the tangents
    Keyframe::Tangent tIn, tOut;
    float sIn, sOut;
    if (getTangent(t, tIn, sIn)) k.setInTangent(tIn);
    else k.setInTangent(sIn);
    if (getTangent(t, tOut, sOut)) k.setOutTangent(tOut);
    else k.setOutTangent(sOut);
    
    // Finally check if they are actually consistent
    if (tIn == tOut) {
        if (tIn == Keyframe::Tangent::Custom) {
            k.setConsistent(sIn == sOut);
        }
        else {
            k.setConsistent(true);
        }
    }
    else {
        k.setConsistent(false);
    }
}

bool AnimationParser::getTangent(Tokenizer & t, Keyframe::Tangent & tang, float & slope) {
    char temp[BUF_SIZE];
    t.getToken(temp);
    if (!strcmp(temp, "flat")) {
        tang = Keyframe::Tangent::Flat;
        return true;
    }
    else if (!strcmp(temp, "linear")) {
        tang = Keyframe::Tangent::Linear;
        return true;
    }
    else if (!strcmp(temp, "smooth")) {
        tang = Keyframe::Tangent::Smooth;
        return true;
    }
    else {
        slope = float(atof(temp));
        tang = Keyframe::Tangent::Custom;
        return false;
    }
}

Channel::Extrapolation AnimationParser::getExtrapolation(Tokenizer & t) {
    char temp[BUF_SIZE];
    t.getToken(temp);
    if (!strcmp(temp, "constant")) {
        return Channel::Extrapolation::Constant;
    }
    else if (!strcmp(temp, "linear")) {
        return Channel::Extrapolation::Linear;
    }
    else if (!strcmp(temp, "cycle")) {
        return Channel::Extrapolation::Cycle;
    }
    else if (!strcmp(temp, "cycle_offset")) {
        return Channel::Extrapolation::CycleOffset;
    }
    else if (!strcmp(temp, "bounce")) {
        return Channel::Extrapolation::Bounce;
    }
    else {
        throw std::invalid_argument("Error parsing the animation. Cannot read extrapolation [" + std::string(temp) + "]");
    }
}

#ifndef CHARACTER_H
#define CHARACTER_H

#include "object/skeleton/Skeleton.h"
#include "object/skin/Skin.h"

namespace rotamina {
    class Character : public Object {
        protected:
            bool showSkinFlag;
            Skeleton skeleton;
            Skin skin;
        public:
            
            Character();
            
            Skeleton & getSkeleton();
            Skin & getSkin();
            
            bool isShowingSkin();
            void setShowSkin();
            void setShowSkeleton();
            
            virtual void update();
            virtual void drawSkin(Shader &);
            virtual void drawSkeleton(Shader &);
            virtual void draw(Shader &);
    };
}

#endif
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
            
            bool isShowingSkin();
            void setShowSkin();
            void setShowSkeleton();
            
            virtual Skeleton & getSkeleton();
            virtual Skin & getSkin();
            
            virtual void update();
            virtual void drawSkin(Shader &);
            virtual void drawSkeleton(Shader &);
            virtual void draw(Shader &);
    };
}

#endif

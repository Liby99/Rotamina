#ifndef CHARACTER_H
#define CHARACTER_H

#include "object/skeleton/Skeleton.h"
#include "object/skin/Skin.h"

namespace rotamina {
    class Character : public Object {
        private:
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
            
            void update();
            void draw(Shader &);
    };
}

#endif

#ifndef __SceneTrans__MenuScene
#define __SceneTrans__MenuScene

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
 
    CREATE_FUNC(MenuScene);


};
#endif // _SceneTrans__MenuScene



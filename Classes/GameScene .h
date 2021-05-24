#ifndef __SceneTrans__GameScene
#define __SceneTrans__GameScene

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
 
    CREATE_FUNC(GameScene);


};

#endif // _SceneTrans__GameScene

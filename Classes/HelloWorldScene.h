#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
 
    CREATE_FUNC(HelloWorld);

    void Scene0(Ref* pSender);
    void Scene1(Ref* pSender);
    void Scene2(Ref* pSender);
	void GameScene(Ref* pSender);
	void MenuScene(Ref* pSender);
  
};

#endif // __HELLOWORLD_SCENE_H__

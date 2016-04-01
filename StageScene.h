#ifndef __SceneTran1_StageScene__
#define __SceneTran1_StageScene__

#include "cocos2d.h"
#include "HelloWorldScene.h"

class StageScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(StageScene);
			
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	~StageScene(void);
	
	void doClose(Ref* pSender);

};

#endif //__SceneTran1_StageScene__

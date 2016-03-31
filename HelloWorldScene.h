#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);
	char str[100] = { 0 };
	int status = 0;
	cocos2d::Size winSize;
	cocos2d::Vec2 itemPosition;
	cocos2d::Vec2 monsterPosition;
	cocos2d::Vec2 heroPosition;
	cocos2d::Sprite* hero;
	cocos2d::Vector<cocos2d::Sprite*> itemV;
	cocos2d::Sprite* item;
	cocos2d::Sprite* monster;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* items;
	cocos2d::TMXLayer* metainfo;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames2;

	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void createHero();
	void setViewpointCenter(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);
};

#endif // __HELLOWORLD_SCENE_H__

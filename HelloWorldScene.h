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
	int status = 0;	//현재 영웅 아이템 보유상태
	int fight = 0;	//몬스터 충돌시 비교 카운트
	int stage = 0;
	//Position
	cocos2d::Size winSize;
	cocos2d::Vec2 itemPosition;
	cocos2d::Vec2 curItemPosition;
	cocos2d::Vec2 monsterPosition;
	cocos2d::Vec2 heroPosition;
	
	//Hero
	cocos2d::Sprite* hero;
	
	//Item, Monster Create
	cocos2d::Vector<cocos2d::Sprite*> itemV;
	cocos2d::Sprite* itemSprite1;
	cocos2d::Sprite* itemSprite2;
	cocos2d::Sprite* itemSprite3;
	cocos2d::Sprite* itemSprite4;
	cocos2d::Sprite* itemSprite5;
	cocos2d::Sprite* monsterSprite1;
	cocos2d::Sprite* monsterSprite2;
	cocos2d::Sprite* monsterSprite3;
	
	//Tile
	cocos2d::TMXTiledMap* tmap;
	
	cocos2d::TMXTiledMap* tmap2;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* items;
	cocos2d::TMXLayer* metainfo;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames2;


	//TouchEvent
	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	//Function
	void createHero();
	void createMonster(int i);
	void fadeRemove(int i);
	void setViewpointCenter(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);
	void changeStage(int i);
	void doChangeScene(Ref* pSender);

};

#endif // __HELLOWORLD_SCENE_H__

#include "HelloWorldScene.h"
#include "StageScene.h"

using namespace cocos2d;

Scene* StageScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StageScene::create();
	scene->addChild(layer);

	return scene;
}

bool StageScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	auto tmap = TMXTiledMap::create("TileMaps/holygrail_stage1.tmx");

	auto background = tmap->getLayer("Background");
	auto metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(true);
	this->addChild(tmap, 0, 11);; // z-order를 -1로 지정하면 화면이 나오지 않는다.
}

void StageScene::onEnter()
{
	Layer::onEnter();

	log("StageScene :: onEnter");
}
void StageScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	log("StageScene :: onEnterTransitionDidFinish");
}
void StageScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();

	log("StageScene :: onExitTransitionDidStart");
}
void StageScene::onExit()
{
	Layer::onExit();

	log("StageScene :: onExit");
}
StageScene::~StageScene()
{
	log("StageScene::dealloc");
}
void StageScene::doClose(Ref* pSender)
{
	// Director::getInstace()->popScene();
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////

	winSize = Director::getInstance()->getWinSize();

	//타일맵 읽어 오기
	tmap= TMXTiledMap::create("TileMaps/holygrail_tutorial.tmx");
	tmap1= TMXTiledMap::create("TileMaps/holygrail_stage1.tmx");
	//tmap2 = TMXTiledMap::create("TileMaps/holygrail_tutorial.tmx");
	
	background = tmap->getLayer("Background");
	//items = tmap->getLayer("Items");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(true);
	this->addChild(tmap, 0, 11);; // z-order를 -1로 지정하면 화면이 나오지 않는다.

	//오브젝트 읽어 오기
	auto objects = tmap->getObjectGroup("Objects");
	//------------------------------------------------------------------------
	//영웅 생성
	ValueMap spawnPoint = objects->getObject("SpawnPoint");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	heroPosition = Vec2(x, y);
	log("Hero Create Check : x.%f y.%f", heroPosition.x, heroPosition.y);
	this->createHero();

	//아이템, 몬스터 생성

	//현재 습득한 아이템
	ValueMap curitemPoint = objects->getObject("CurrentItem");
	int cx = curitemPoint["x"].asInt();
	int cy = curitemPoint["y"].asInt();
	curItemPosition = Vec2(cx, cy);

	//Sprite 사용 Item 생성
	//#item1
	ValueMap itemPoint = objects->getObject("Sword");
	int ix = itemPoint["x"].asInt();
	int iy = itemPoint["y"].asInt();
	itemPosition = Vec2(ix, iy);
	itemSprite1 = Sprite::createWithSpriteFrameName("W_Sword001.png");
	itemSprite1->setPosition(itemPosition);
	this->addChild(itemSprite1);


	//#item2
	itemPoint = objects->getObject("Sword2");
	ix = itemPoint["x"].asInt();
	iy = itemPoint["y"].asInt();
	itemPosition = Vec2(ix, iy);
	itemSprite2 = Sprite::createWithSpriteFrameName("W_Sword015.png");
	itemSprite2->setPosition(itemPosition);
	this->addChild(itemSprite2);


	//#item3
	itemPoint = objects->getObject("Key");
	ix = itemPoint["x"].asInt();
	iy = itemPoint["y"].asInt();
	itemPosition = Vec2(ix, iy);
	itemSprite3 = Sprite::createWithSpriteFrameName("I_Key02.png");
	itemSprite3->setPosition(itemPosition);
	this->addChild(itemSprite3);

	//#item4
	itemPoint = objects->getObject("Chest");
	ix = itemPoint["x"].asInt();
	iy = itemPoint["y"].asInt();
	itemPosition = Vec2(ix, iy);
	itemSprite4 = Sprite::createWithSpriteFrameName("I_Chest01.png");
	itemSprite4->setPosition(itemPosition);
	this->addChild(itemSprite4);

	//#item5	Vector(itemV) 사용 Item 생성
	itemPoint = objects->getObject("Mace");
	ix = itemPoint["x"].asInt();
	iy = itemPoint["y"].asInt();
	itemPosition = Vec2(ix, iy);
	itemV.pushBack(Sprite::createWithSpriteFrameName("W_Mace008.png"));
	itemV.at(0)->setPosition(itemPosition);
	this->addChild(itemV.at(0));

	//------------------------------------------------------------------------

	//Sprite 사용 Monster 생성
	ValueMap monsterPoint = objects->getObject("Wolf");
	int mx = monsterPoint["x"].asInt();
	int my = monsterPoint["y"].asInt();
	monsterPosition = Vec2(mx, my);
	this->createMonster(1);

	monsterPoint = objects->getObject("Jelly");
	mx = monsterPoint["x"].asInt();
	my = monsterPoint["y"].asInt();
	monsterPosition = Vec2(mx, my);
	this->createMonster(2);

	monsterPoint = objects->getObject("Demon");
	mx = monsterPoint["x"].asInt();
	my = monsterPoint["y"].asInt();
	monsterPosition = Vec2(mx, my);
	this->createMonster(3);

	return true;
}

//애니메이션 생성
//Hero---------------------------------------------------------------------
void HelloWorld::createHero()
{
	//움직이는 캐릭터 넣기 시작

	//캐릭터 읽어 오기
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/Holygrail.plist");
	//auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");

	for (int i = 4; i < 7; i++) {
		sprintf(str, "Hero%02d.png", i);

		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	//스프라이트 생성 및 초기화
	hero = Sprite::createWithSpriteFrameName("Hero01.png");
	hero->setPosition(heroPosition);
	this->addChild(hero);

	//영웅의 방향을 바꿔준다.
	hero->setFlippedX(true);

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	//auto rep = RepeatForever::create(animate);
	hero->runAction(animate);

}

//Monster---------------------------------------------------------------------
void HelloWorld::createMonster(int i)
{

	int div = i;
	log("Monster");
	//움직이는 캐릭터 넣기 시작

	//캐릭터 읽어 오기
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/Holygrail.plist");
	//auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");
	animFrames2.clear();
	for (int i = 1; i < 4; i++) {

		if (div == 1)
			sprintf(str, "Wolf%d.png", i);
		else if (div == 2)
			sprintf(str, "Jelly%d.png", i);
		else if (div == 3)
			sprintf(str, "Demon%d.png", i);

		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames2.pushBack(frame);
		log("Monster FOR");
	}

	auto animation = Animation::createWithSpriteFrames(animFrames2, 0.1f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);

	//스프라이트 생성 및 초기화
	log("Monster Sprite before");
	if (div == 1) {
		monsterSprite1 = Sprite::createWithSpriteFrameName("Wolf1.png");
		monsterSprite1->setPosition(monsterPosition);
		this->addChild(monsterSprite1);
		monsterSprite1->runAction(rep);
	}
	else if (div == 2) {
		monsterSprite2 = Sprite::createWithSpriteFrameName("Jelly1.png");
		monsterSprite2->setPosition(monsterPosition);
		this->addChild(monsterSprite2);
		monsterSprite2->runAction(rep);
	}
	else if (div == 3) {
		monsterSprite3 = Sprite::createWithSpriteFrameName("Demon1.png");
		monsterSprite3->setPosition(monsterPosition);
		this->addChild(monsterSprite3);
		monsterSprite3->runAction(rep);
	}

}
void HelloWorld::onEnter()
{
	Layer::onEnter();

	//싱글 터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = hero->getPosition();
	Vec2 diff = touchPoint - playerPos;
	
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			animFrames.clear();
			for (int i = 4; i < 7; i++) {
				sprintf(str, "Hero%02d.png", i);

				SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
				animFrames.pushBack(frame);
			}
			auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
			auto animate = Animate::create(animation);
			hero->runAction(animate);
			playerPos.x += tmap->getTileSize().width;

			//영웅의 방향을 바꿔준다.
			//hero->setFlippedX(true);
		}
		else {
			animFrames.clear();
			for (int i = 7; i < 10; i++) {
				sprintf(str, "Hero%02d.png", i);

				SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
				animFrames.pushBack(frame);
			}
			auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
			auto animate = Animate::create(animation);
			hero->runAction(animate);
			playerPos.x -= tmap->getTileSize().width;

			//영웅의 방향을 바꿔준다.
			//hero->setFlippedX(false);
		}
	}
	else {
		if (diff.y > 0) {
			animFrames.clear();
			for (int i = 10; i < 13; i++) {
				sprintf(str, "Hero%02d.png", i);

				SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
				animFrames.pushBack(frame);
			}
			auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
			auto animate = Animate::create(animation);
			hero->runAction(animate);
			playerPos.y += tmap->getTileSize().height;
		}
		else {
			animFrames.clear();
			for (int i = 1; i < 4; i++) {
				sprintf(str, "Hero%02d.png", i);

				SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
				animFrames.pushBack(frame);
			}
			auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
			auto animate = Animate::create(animation);
			hero->runAction(animate);
			playerPos.y -= tmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) &&
		playerPos.y <= (tmap->getMapSize().height * tmap->getTileSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		//hero->setPosition(playerPos);
		log("캐릭터 이동 ! playerPos.x : %f ,playerPos.y : %f", playerPos.x, playerPos.y);
		this->setPlayerPosition(playerPos);
	}
	//영웅의 위치에 맞춰 화면 위치 조정
	this->setViewpointCenter(hero->getPosition());
}

void HelloWorld::setViewpointCenter(Vec2 position)
{
	//파라미터로 들어오는 위치에 맞춰 화면을 움직인다.
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

//현재 탭으로 선택된 타일의 위치를 가져온다.
Vec2 HelloWorld::tileCoordForPosition(Vec2 position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height - position.y)
		/ tmap->getTileSize().height);
	return Vec2(x, y);
}

void HelloWorld::setPlayerPosition(Vec2 position)
{
	//탭된 위치 구하기
	Vec2 tileCoord = this->tileCoordForPosition(position);

	//현재 위치의 Tile GID 구하기
	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

	if (tileGid)
	{
		//타일맵에서 GID에 해당하는 부분의 속성 읽어 오기
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			//Item--------------------------------------------------------------------
			std::string item1 = properties.asValueMap()["Items"].asString();

			if (item1 == "Sword" && status == 0) {
				itemSprite1->setPosition(curItemPosition);
				this->metainfo->removeTileAt(tileCoord);

				log("검 획득");
				status = 1;
			}
			else  if (item1 == "Sword2" && status == 0) {
				itemSprite2->setPosition(curItemPosition);
				this->metainfo->removeTileAt(tileCoord);
				//removeChild(itemSprite2);
				log("성검 획득");
				status = 3;
			}
			else if (item1 == "Key" && status == 0) {
				itemSprite3->setPosition(curItemPosition);
				this->metainfo->removeTileAt(tileCoord);
				log("열쇠 획득\n 상자를 열 수 있습니다!");
				status = 20;
			}
			else if (item1 == "Chest" && status == 20) {
				this->metainfo->removeTileAt(tileCoord);
				removeChild(itemSprite4);
				removeChild(itemSprite3);
				log("상자 오픈!\n 다음 스테이지로~");
				status = 99;

				stage++;

			}
			else if (item1 == "Chest" && status != 20) {
				log("상자를 열기위해서는 열쇠가 필요합니다!");
				return;
			}

			//Vector로 생성한 item
			else if (item1 == "Mace" && status == 0) {
				itemV.at(0)->setPosition(curItemPosition);
				this->metainfo->removeTileAt(tileCoord);

				status = 2;
				log("메이스 획득 %d", status);

			}
			else if (item1 != "" && status != 0)
			{
				log("무기를 더 습득 할 수 없습니다.");
				return;
			}

			//Monster----------------------------------------------------------
			std::string monster1 = properties.asValueMap()["Monster"].asString();

			if (monster1 == "Wolf" && status == 1) {
				this->metainfo->removeTileAt(tileCoord);
				fadeRemove(1);
				log("늑대 처치");
				status = 0;
			}
			else if (monster1 == "Wolf" && status != 1)
			{
				//hero->setPosition(heroPosition);	스폰 위치로 초기화
				log("뭔가 뾰족한게 필요해..\n늑대는 '검'으로 공격 할 수 있습니다.");
				return;
			}
			if (monster1 == "Jelly" && status == 2) {
				this->metainfo->removeTileAt(tileCoord);
				fadeRemove(2);
				log("젤리 처치");
				status = 0;
			}
			else if (monster1 == "Jelly" && status != 2)
			{
				//hero->setPosition(heroPosition);
				log("뭔가 내려칠게 필요해..\n젤리는 '메이스'로 공격 할 수 있습니다.");
				return;
			}
			if (monster1 == "Demon" && status == 3) {
				this->metainfo->removeTileAt(tileCoord);
				fadeRemove(3);
				log("악마 처치");
				status = 0;
			}
			else if (monster1 == "Demon" && status != 3)
			{
				//hero->setPosition(heroPosition);
				log("뭔가 신성한 무기가 필요해..\n악마는 '성검'으로 공격 할 수 있습니다.");
				return;
			}
		}
	}
	Vec2 action = Vec2(position.x, position.y);
	
	auto heroAction = MoveTo::create(0.3, position);
	if(hero->numberOfRunningActions()<=2){
		hero->runAction(heroAction);
		
	}else{
		log("!1 ACTION");
	}
	//hero->setPosition(position);
}


void HelloWorld::changeStage(int i) {
	
}

void HelloWorld::fadeRemove(int i) {
	auto fOutAction = FadeOut::create(0.3);

	if (i == 1)
	{
		monsterSprite1->runAction(fOutAction);
		removeChild(itemSprite1);

		if (monsterSprite1->numberOfRunningActions() == 0) {
			removeChild(monsterSprite1);
		}

	}
	else if (i == 2)
	{
		monsterSprite2->runAction(fOutAction);
		removeChild(itemV.at(0));

		if (monsterSprite2->numberOfRunningActions() == 0) {
			removeChild(monsterSprite2);
		}
	}
	else if (i == 3)
	{
		monsterSprite3->runAction(fOutAction);
		removeChild(itemSprite2);

		if (monsterSprite3->numberOfRunningActions() == 0) {
			removeChild(monsterSprite3);
		}
	}
	
}
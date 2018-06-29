#include "StartScene.h"
#include "GameScene.h"
#include "global.h"
USING_NS_CC;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point visiblePos = Point(visibleSize.width / 2, visibleSize.height / 2);

	
	auto layerColorBG = LayerColor::create(Color4B(199, 237, 233, 200));
	this->addChild(layerColorBG);


	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	auto menuItemStart = MenuItemFont::create("4*4", CC_CALLBACK_1(StartScene::onfour, this));


	auto menu = Menu::create(menuItemStart, NULL);
	addChild(menu);
	menu->setPosition(Point(visiblePos.x, visiblePos.y + 200));



	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	menuItemStart = MenuItemFont::create("5*5", CC_CALLBACK_1(StartScene::onfive, this));


    menu = Menu::create(menuItemStart, NULL);
	addChild(menu);
	menu->setPosition(Point(visiblePos.x, visiblePos.y + 100));



	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	menuItemStart = MenuItemFont::create("6*6", CC_CALLBACK_1(StartScene::onsix, this));


	menu = Menu::create(menuItemStart, NULL);
	addChild(menu);
	menu->setPosition(Point(visiblePos.x, visiblePos.y ));



	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	menuItemStart = MenuItemFont::create("7*7", CC_CALLBACK_1(StartScene::onseven, this));


	menu = Menu::create(menuItemStart, NULL);
	addChild(menu);
	menu->setPosition(Point(visiblePos.x, visiblePos.y - 100));
	
	
	auto cardNumberTitle = Label::createWithSystemFont("row * col", "Consolas", 50);
	cardNumberTitle->setPosition(Point(200, visibleSize.height - 100));
	addChild(cardNumberTitle);


	StartScene::change(row, col);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(StartScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	touchListener->setSwallowTouches(true);
	

	return true;
}

int StartScene::change(int &row, int &col)
{
	if (&StartScene::onfour)
	{
		row = 4;
		col = 4;
	}

	
	if (&StartScene::onfive)
	{
		row = 5;
		col = 5;

	}
	if (&StartScene::onsix)
	{
		row = 6;
		col = 6;
	}
	if (&StartScene::onseven)
	{
		row = 7;
		col = 7;
	}
	return row, col;
}


void StartScene::onfour(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
	Director::getInstance()->resume();
	
}

void StartScene::onfive(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
	Director::getInstance()->resume();

}

void StartScene::onsix(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
	Director::getInstance()->resume();
}

void StartScene::onseven(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
	Director::getInstance()->resume();
}

bool StartScene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void StartScene::onTouchMoved(Touch* touch, Event* event)
{
}

void StartScene::onTouchEnded(Touch* touch, Event* event)
{
}



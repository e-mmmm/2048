//
//  PopLayer.cpp
//  2048
//
//  Created by ZeroYang on 5/8/14.
//
//

#include "PopLayer.h"
#include "StartScene.h"
#include "global.h"


PopLayer* PopLayer::create(const Color4B& color)
{
	PopLayer *pRet = new PopLayer();
	if (pRet && pRet->initWithColor(color))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool PopLayer::initWithColor(const Color4B& color)
{
	if (!LayerColor::initWithColor(color)) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Point centerPos = Point(winSize.width / 2, winSize.height / 2);

	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);

	auto menuItemContinue = MenuItemFont::create("CONTINUE", CC_CALLBACK_1(PopLayer::onContinue, this));
	auto menuItemRestart = MenuItemFont::create("RESTART", CC_CALLBACK_1(PopLayer::onRestart, this));
	


	auto menu = Menu::create(menuItemContinue, menuItemRestart,NULL);
	menu->alignItemsVertically();
	addChild(menu);
	menu->setPosition(centerPos);
	PopLayer::change(row, col);

	//设置触摸事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PopLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PopLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PopLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	touchListener->setSwallowTouches(true);

	return true;
}

int PopLayer::change(int &row, int &col)
{
	if (&PopLayer::onRestart) {
		row = 5;
		col = 5;
	};

	return row, col;
}

void PopLayer::onRestart(Ref* pSender)
{
	
	Director::getInstance()->replaceScene(StartScene::createScene());
	Director::getInstance()->resume();
}



void PopLayer::onContinue(Ref* pSender)
{
	removeFromParent();
	Director::getInstance()->resume();
}

bool PopLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void PopLayer::onTouchMoved(Touch* touch, Event* event)
{
}

void PopLayer::onTouchEnded(Touch* touch, Event* event)
{
}
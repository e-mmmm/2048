#include "GameScene.h"
#include "CardSprite.h"
#include "Recognizer.h"
#include "GameOverLayer.h"
#include "HighScore.h"
#include "PopLayer.h"
#include "global.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameScene::~GameScene()
{
	delete recognizer;

	
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Point origin = Director::getInstance()->getVisibleOrigin();

	
	auto layerColorBG = LayerColor::create(Color4B(199, 237, 233, 200));
	this->addChild(layerColorBG);


	//pause
	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	auto menuItemPause = MenuItemFont::create("C/R", CC_CALLBACK_1(GameScene::onPause, this));


	auto menu = Menu::create(menuItemPause, NULL);
	addChild(menu);
	menu->setPosition(Point(200, visibleSize.height - 200));

	auto cardNumberTitle = Label::createWithSystemFont("Score", "Consolas", 80);
	cardNumberTitle->setPosition(Point(200, visibleSize.height - 100));
	addChild(cardNumberTitle);

	cardNumberTitle = Label::createWithSystemFont("Best", "Consolas", 80);
	cardNumberTitle->setPosition(Point(200, visibleSize.height - 300));
	addChild(cardNumberTitle);

	score = 0;
	cardNumberTTF = Label::createWithSystemFont("0", "Consolas", 70);
	cardNumberTTF->setPosition(Point(400, visibleSize.height - 100));
	addChild(cardNumberTTF);

	char temp[64];
	sprintf(temp, "%d", HighScore::getInstance()->getHighScore());
	highScoreTTF = Label::createWithSystemFont(temp, "Consolas", 70);
	highScoreTTF->setPosition(Point(400, visibleSize.height - 300));
	addChild(highScoreTTF);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	
	createCardSprite(visibleSize);
	if (UserDefault::getInstance()->getBoolForKey("history")) {
		resumeStatus();
	}
	else
	{
		createCardNumber(false);
		createCardNumber(false);
	}

	recognizer = new SimpleRecognizer();

	return true;
}

void GameScene::onPause(Ref* pSender)
{
	PopLayer *poplayer = PopLayer::create(Color4B(0, 0, 0, 180));
	getParent()->addChild(poplayer);
	Director::getInstance()->pause();
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	Point beginPoint = touch->getLocation();
	recognizer->beginPoint(beginPoint);
	return true;
}



void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();
	recognizer->movePoint(pos);
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();
	SimpleGestures rtn = recognizer->endPoint(pos);

	switch (rtn) {
	case SimpleGesturesLeft:
		doLeft();
		doCheck();
		setScore(score);
		setHighScore(highscore);
		break;
	case SimpleGesturesRight:
		doRight();
		doCheck();
		setScore(score);
		setHighScore(highscore);
		break;
	case SimpleGesturesUp:
		doUp();
		doCheck();
		setScore(score);
		setHighScore(highscore);
		break;
	case SimpleGesturesDown:
		doDown();
		doCheck();
		setScore(score);
		setHighScore(highscore);
		break;

	case SimpleGesturesNotSupport:
	case SimpleGesturesError:
		log("not support or error touch,use geometricRecognizer!!");
		break;

	default:
		break;
	}
}


void GameScene::createCardSprite(Size size)
{
	cellSize = (size.width - (row)* cellSpace - 40) / (col+1);

	for (int i = 0; i < row ; i++)
	{
		for (int j = 0; j < col; j++)
		{
			CardSprite *card = CardSprite::createCardSprite(0, cellSize, cellSize, getPosition(i, j));
			cardArr[i][j] = card;
			addChild(card);
		}
	}
}

void GameScene::createCardNumber(bool animation)
{

	while (1) {
		int i = CCRANDOM_0_1() * row;        
		int j = CCRANDOM_0_1() * col;

		log("[%d][%d]", i, j);

		if (cardArr[i][j]->getNumber() == 0)
		{

			cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
			if (animation)
			{
				cardArr[i][j]->runNewNumberAction();
			}
			break;
		}

		if (!shouldCreateCardNumber()) {
			break;
		}
	}
}

bool GameScene::shouldCreateCardNumber()
{
	bool isCreate = false;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (0 == cardArr[i][j]->getNumber())
			{
				isCreate = true;
				break;
			}
		}
	}

	return isCreate;
}

bool GameScene::isWin()
{
	bool win = false;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (2048 == cardArr[i][j]->getNumber())
			{
				win = true;
				break;
			}
		}
	}

	return win;
}

bool GameScene::doLeft()
{
	bool isMove = false;
	for (int y = 0; y < col; y++)
	{
		for (int x = 0; x < row; x++)
		{
			for (int x1 = x + 1; x1<row; x1++)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;
						isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						
						score += cardArr[x][y]->getNumber();
						HighScore::getInstance()->setScore(score);
						highscore = HighScore::getInstance()->getHighScore();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

bool GameScene::doRight()
{
	bool isMove = false;
	for (int y = 0; y < col; y++)
	{
		for (int x = row-1; x >= 0; x--)
		{
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						score += cardArr[x][y]->getNumber();
						HighScore::getInstance()->setScore(score);
						highscore = HighScore::getInstance()->getHighScore();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}


bool GameScene::doUp()
{
	bool isMove = false;
	for (int x = 0; x < row; x++)
	{
		for (int y = col-1; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						score += cardArr[x][y]->getNumber();
						HighScore::getInstance()->setScore(score);
						highscore = HighScore::getInstance()->getHighScore();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

bool GameScene::doDown()
{
	
	bool isMove = false;
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y <col; y++)
		{
			for (int y1 = y + 1; y1<col; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						score += cardArr[x][y]->getNumber();
						HighScore::getInstance()->setScore(score);
						highscore = HighScore::getInstance()->getHighScore();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

void GameScene::setScore(int score)
{    
	cardNumberTTF->setString(__String::createWithFormat("%i", score)->getCString());
}

void GameScene::setHighScore(int highscore)
{    
	highScoreTTF->setString(__String::createWithFormat("%i", highscore)->getCString());
}


void GameScene::doCheck()
{
	bool isGameOver = true;

	for (int y = 0; y < col; y++)
	{
		for (int x = 0; x < row; x++)
		{
			if (cardArr[x][y]->getNumber() == 0 ||
				(x<3 && cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber()) ||
				(x>0 && cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber()) ||
				(y<3 && cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()) ||
				(y>0 && cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber()))
			{
				isGameOver = false;
			}
		}
	}

	if (isWin()) {

		successLayer = LayerColor::create(Color4B(0, 0, 0, 180));
		Size winSize = Director::getInstance()->getWinSize();
		Point centerPos = Point(winSize.width / 2, winSize.height / 2);
		auto gameOverTitle = Label::createWithSystemFont("YOU WIN", "Consolas", 80);
		gameOverTitle->setPosition(centerPos);
		successLayer->addChild(gameOverTitle);

		getParent()->addChild(successLayer, 1);

		scheduleOnce(SEL_SCHEDULE(&GameScene::removeSuccessLayer), 2);
		return;
	}

	//isGameOver = true;
	if (isGameOver)
	{
		log("game over");
		UserDefault::getInstance()->setBoolForKey("history", false);

		HighScore::getInstance()->setScore(score);
		GameOverLayer *gameoverLayer = GameOverLayer::create(Color4B(0, 0, 0, 180));
		getParent()->addChild(gameoverLayer, 1);

		Director::getInstance()->pause();
	}
	else
	{
		if (shouldCreateCardNumber()) {
			createCardNumber();

			saveStatus();
		}
	}

}

Point GameScene::getPosition(int i, int j)
{
	float pX = 20 + cellSpace / 2 + i*(cellSize + cellSpace);
	float pY = cellSize / 2 + j*(cellSize + cellSpace);

	return Point(pX, pY);
}


void GameScene::saveStatus()
{
	char temp[10];
	for (int i = 0; i<row; i++) {
		for (int j = 0; j<col; j++)
		{
			sprintf(temp, "%d%d", i, j);
			UserDefault::getInstance()->setIntegerForKey(temp, cardArr[i][j]->getNumber());
		}
	}

	UserDefault::getInstance()->setIntegerForKey("score", score);
	UserDefault::getInstance()->setIntegerForKey("highscore", highscore);

	UserDefault::getInstance()->setBoolForKey("history", true);
}

void GameScene::resumeStatus()
{
	char temp[10];
	for (int i = 0; i<row; i++) {
		for (int j = 0; j<col ; j++)
		{
			sprintf(temp, "%d%d", i, j);
			int number = UserDefault::getInstance()->getIntegerForKey(temp);
			cardArr[i][j]->setNumber(number);
		}
	}

	score = UserDefault::getInstance()->getIntegerForKey("score");
	highscore= UserDefault::getInstance()->getIntegerForKey("highscore");
	setScore(score);

	UserDefault::getInstance()->setBoolForKey("history", false);
}

void GameScene::newNumber(int i, int j, int num)
{

 };

void GameScene::removeSuccessLayer()
{
	successLayer->removeFromParent();
}
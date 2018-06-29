#ifndef ___048__GameScene__

#define ___048__GameScene__



#include "cocos2d.h"
#include "global.h"




class CardSprite;

class SimpleRecognizer;



class GameScene : public cocos2d::Layer

{

public:
	
    static cocos2d::Scene* createScene();
	//int row = 4;
	//int col = 4;


    virtual bool init();

    CREATE_FUNC(GameScene)

    ~GameScene();

    

    //触摸事件监听回调函数

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	 

  //  virtual void onEnter() override;

    

private:

	

    void createCardSprite(cocos2d::Size size);

    void createCardNumber(bool animation = true);
	

    void newNumber(int i, int j, int num);

    void setScore(int score);
	void setHighScore(int highscore);

    void doCheck();

    bool shouldCreateCardNumber();



    bool isWin();

    void removeSuccessLayer();

    

    void saveStatus();

    void resumeStatus();

    

    void onPause(Ref* pSender);



    

    cocos2d::Point getPosition(int i, int j);

    

    /////////////////

    //左滑动

    bool doLeft();

    //右滑动

    bool doRight();

    //上滑动

    bool doUp();

    //下滑动

    bool doDown();



private:

	int firstX, firstY, endX, endY;

    

    int cellSize = 0;

    int cellSpace = 10;

    

    int score;
	int highscore;

    

    cocos2d::Label *cardNumberTTF;
	cocos2d::Label *highScoreTTF;

	


    //储存卡片类

    CardSprite *cardArr[10][10];



    SimpleRecognizer *recognizer;

    

    cocos2d::LayerColor *successLayer;

};



#endif /* defined(___048__GameScene__) */
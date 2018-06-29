#ifndef ___048__Card__
#define ___048__Card__

#include "cocos2d.h"

class CardSprite : public cocos2d::Sprite
{
public:
	static CardSprite* createCardSprite(int number, int wight, int height, cocos2d::Point position);
	virtual bool init();
	CREATE_FUNC(CardSprite)
	~CardSprite();
	int getNumber();
	void setNumber(int num);
	void runNewNumberAction();
private:
	void initCard(int number, int wight, int height, cocos2d::Point position);
private:
	
	int number;

	
	cocos2d::Label *labelCardNumber;

	
	cocos2d::LayerColor *colorBackground;
};

#endif /* defined(___048__Card__) */
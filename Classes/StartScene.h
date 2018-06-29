#ifndef ___048__StartScene__

#define ___048__StartScene__



#include "cocos2d.h"




class StartScene : public cocos2d::Layer

{

public:

	static cocos2d::Scene* createScene();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	

	virtual bool init();
	void onfour(Ref* pSender);
	

	CREATE_FUNC(StartScene)


private:
	
	int change(int &row, int &col);
	void onfive(Ref* pSender);
	void onsix(Ref* pSender);
	void onseven(Ref* pSender);

};


#endif /* defined(___048__StartScene__) */
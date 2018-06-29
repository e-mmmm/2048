#include "CardSprite.h"

USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int number, int wight, int height, Point position)
{
	
	CardSprite *card = new CardSprite();
	if (card && card->init())
	{
		card->autorelease();
		card->initCard(number, wight, height, position);
		return card;
	}
	CC_SAFE_DELETE(card);

	return NULL;
}

CardSprite::~CardSprite()
{

}


bool CardSprite::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void CardSprite::runNewNumberAction()
{
	auto action = ScaleBy::create(0.05, 0.99);
	runAction(Sequence::create(action, action->reverse(), nullptr));
}



int CardSprite::getNumber()

{
	return number;
}




void CardSprite::setNumber(int num)

{
	number = num;

	if (num > 0)

	{
		labelCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
	}

	else
	{
		labelCardNumber->setString("");
	}

	if (num >= 0)
	{
		labelCardNumber->setSystemFontSize(60);
	}

	if (num >= 16)
	{
		labelCardNumber->setSystemFontSize(50);
	}

	if (num >= 128)

	{
		labelCardNumber->setSystemFontSize(30);
	}

	if (num >= 1024)

	{
		labelCardNumber->setSystemFontSize(10);
	}

	if(number == 0){

		colorBackground->setColor(Color3B(225,233,200));

	}

	if (number == 2) {

		colorBackground->setColor(Color3B(167,220,224));

	}

	if (number == 4) {

		colorBackground->setColor(Color3B(38,188,213));

	}

	if (number == 8) {

		colorBackground->setColor(Color3B(175,215,237));

	}

	if (number == 16) {

		colorBackground->setColor(Color3B(147,224,255));

	}

	if (number == 32) {

		colorBackground->setColor(Color3B(92,167,186));

	}

	if (number == 64) {

		colorBackground->setColor(Color3B(20,68,106));

	}

	if (number == 128) {

		colorBackground->setColor(Color3B(3,101,100));

	}

	if (number == 256) {

		colorBackground->setColor(Color3B(3,54,73));

	}

	if (number == 512) {

		colorBackground->setColor(Color3B(3,22,52));

	}

	if (number == 1024) {

		colorBackground->setColor(Color3B(84,115,135));

	}

	if (number == 2048) {

		colorBackground->setColor(Color3B(240,130,90));

	}

	if (number == 4096) {

		colorBackground->setColor(Color3B(240, 160, 120));

	}

	if (number == 8192) {

		colorBackground->setColor(Color3B(240, 230, 110));

	}
}

void CardSprite::initCard(int number, int wight, int height, Point position)

{
	this->number = number;

	colorBackground = LayerColor::create(Color4B(225, 233, 200, 255),wight-15,height-15);
	colorBackground->setPosition(position);


	if (number > 0)
	{
		labelCardNumber = Label::createWithSystemFont(__String::createWithFormat("%i",number)->getCString(),"Consolas",100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2, colorBackground->getContentSize().height/2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}

	else

	{
		labelCardNumber = Label::createWithSystemFont("","Consolas",100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2, colorBackground->getContentSize().height/2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}

    

	this->addChild(colorBackground);

}
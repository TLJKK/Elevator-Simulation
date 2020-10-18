
#include "choose.h"
#include<ui/CocosGUI.h>

#define TAG_TOAST_LABEL 1130
#define TAG_TOAST_LAYER 1131
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;
 
choose::choose()
{
 
}
 
choose::~choose()
{
 
}
 

bool choose::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 180));

	box = ui::Scale9Sprite::create("choose.png");
	cancle_Btn = ui::Button::create("cancleWord.png");
	allAuto_Btn = ui::Button::create("autoWords.png");
	halfAuto_Btn = ui::Button::create("halfWords.png");

	
	auto size = box->getContentSize();
	box->setPosition(viewSize / 2);

	halfAuto_Btn->setPosition((Vec2)viewSize / 2 + Vec2(340, 80));
	allAuto_Btn->setPosition((Vec2)viewSize / 2 + Vec2(355, 0));
	cancle_Btn->setPosition((Vec2)viewSize / 2 + Vec2(415, -80));

	this->setContentSize(viewSize);
	this->addChild(background);
	this->addChild(box);
	this->addChild(cancle_Btn);
	this->addChild(halfAuto_Btn);
	this->addChild(allAuto_Btn);
	//, endGamefunc;
	allAuto_Btn->addClickEventListener([this](Ref* ref)
		{
			if (allAuto != nullptr)
				allAuto();
		});
	halfAuto_Btn->addClickEventListener([this](Ref* ref)
		{
			if (halfAuto != nullptr)
				halfAuto();
		});
	cancle_Btn->addClickEventListener([this](Ref* ref)
		{
			if (cancle != nullptr)
				cancle();
		});

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event* e) {return true; };
	listener->setSwallowTouches(true);
	background->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, background);
   
	return true;
}

//std::function<void()>allAuto;
//std::function<void()>cancle;
//std::function<void()>halfAuto;

void  choose::registerCallback(std::function<void()>allCallback, std::function<void()>
	halfCallback, std::function<void()>cancleCallback)
{
	allAuto = allCallback;
	cancle = cancleCallback;
	halfAuto = halfCallback;
}


void choose::onEnter()
{
	Layer::onEnter();
	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 2.0f, 2.0f)), NULL);
	Sequence* bea = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* cir = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* tx = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	box->runAction(seq);
	allAuto_Btn->runAction(bea);
	halfAuto_Btn->runAction(cir);
	cancle_Btn->runAction(tx);
}
 
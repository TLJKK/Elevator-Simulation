#include "messageBox.h"
#include<ui/CocosGUI.h>

#define TAG_TOAST_LABEL 1130
#define TAG_TOAST_LAYER 1131
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;
 
BDMessageBox::BDMessageBox()
{
 
}
 
BDMessageBox::~BDMessageBox()
{
 
}
 

bool BDMessageBox::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 180));

	box = ui::Scale9Sprite::create("menu.png");
	continue_Btn = ui::Button::create("ali.png");
	end_gameBtn = ui::Button::create("yes.png");

	box->setScale(0.7);
	continue_Btn->setScale(0.8);
	end_gameBtn->setScale(0.8);

	auto size = box->getContentSize();
	box->setPosition(viewSize / 2);
	continue_Btn->setPosition(Vec2(viewSize.width / 2-275, viewSize.height / 2 - 65));
	end_gameBtn->setPosition(Point(viewSize.width / 2 + 255, viewSize.height / 2 - 155));

	this->setContentSize(viewSize);
	this->addChild(background);
	this->addChild(box);
	this->addChild(continue_Btn);
	this->addChild(end_gameBtn);

	//, endGamefunc;
	continue_Btn->addClickEventListener([this](Ref* ref)
		{
			if (continueFunc != nullptr)
				continueFunc();
		});

	end_gameBtn->addClickEventListener([this](Ref* ref)
		{
			if (endGamefunc != nullptr)
				endGamefunc();
		});

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event* e) {return true; };
	listener->setSwallowTouches(true);
	background->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, background);

    label = Label::create("确定退出吗？ali，xyr.", "GameFont.ttf", 30);
	label->setColor(Color3B::BLACK);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE); //锚点在中间
	label->setTag(TAG_TOAST_LABEL);
	label->setPosition(Vec2(size.width / 2 + 30, size.height / 2 + 10));
	addChild(label);

	return true;
}

void  BDMessageBox::registerCallback(std::function<void()>continueCallback, std::function<void()>
	endgameCallback)
{
	continueFunc = continueCallback;
	endGamefunc = endgameCallback;
}

void BDMessageBox::onEnter()
{
	Layer::onEnter();
	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 0.7f, 0.7f)), NULL);
	Sequence* bea = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* cir = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* tx = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	box->runAction(seq);
	continue_Btn->runAction(bea);
	end_gameBtn->runAction(cir);
	label->runAction(tx);
}
 
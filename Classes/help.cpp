
#include "help.h"
#include<ui/CocosGUI.h>

#define TAG_TOAST_LABEL 1130
#define TAG_TOAST_LAYER 1131
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;
 
help::help()
{
 
}
 
help::~help()
{
 
}
 

bool help::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 180));
	box = ui::Scale9Sprite::create("help.png");

	end_gameBtn = ui::Button::create("cancle.png");

	box->setScale(2.0);


	auto size = box->getContentSize();

	box->setPosition(viewSize / 2);

	end_gameBtn->setScale(0.6);
	end_gameBtn->setAnchorPoint(Vec2(0.5, 0.5));
	end_gameBtn->setPosition((Vec2)box->getContentSize() * 2 + box->getBoundingBox().origin
		+ Vec2(-10, -10));

	this->setContentSize(viewSize);
	this->addChild(background);
	this->addChild(box);
	addChild(end_gameBtn);
	
	end_gameBtn->addClickEventListener([this](Ref* ref)
		{
			if (endGamefunc != nullptr)
				endGamefunc();
		});

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event* e) {return true; };
	listener->setSwallowTouches(true);
	background->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, background);

	auto word = Sprite::create("helpblue.png");
	word->setScale(0.25);
	word->setAnchorPoint(Vec2(0, 0));
	word->setPosition(Vec2(20, 25));
	box->addChild(word);
	return true;
}

void  help::registerCallback(std::function<void()>endgameCallback)
{
	endGamefunc = endgameCallback;
}

void help::onEnter()
{
	Layer::onEnter();
	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 2.0f, 2.0f)), NULL);
	Sequence* canc = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 0.6f, 0.6f)), NULL);
	box->runAction(seq);
	end_gameBtn->runAction(canc);
}
 

#include "stopMessage.h"
#include<ui/CocosGUI.h>
#include "Person.h"

#define TAG_TOAST_LABEL 1130
#define TAG_TOAST_LAYER 1131
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;

stopMessageBox::stopMessageBox()
{

}

stopMessageBox::~stopMessageBox()
{

}


bool stopMessageBox::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto viewSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 180));
	box = ui::Scale9Sprite::create("stopface.png");
	continue_Btn = ui::Button::create("continue1.png");
	end_gameBtn = ui::Button::create("mainscene2.png");
	/*box->setScale(0.7);
	continue_Btn->setScale(0.8);
	end_gameBtn->setScale(0.8);*/
	auto size = box->getContentSize();
	box->setPosition(viewSize / 2);
	end_gameBtn->setPosition(Point(viewSize.width / 2, viewSize.height / 2 - 155));
	continue_Btn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 85));
	this->setContentSize(viewSize);
	this->addChild(background);
	this->addChild(box);
	this->addChild(continue_Btn);
	this->addChild(end_gameBtn);
	
	auto _CheckBox = ui::CheckBox::create("checkNo.png", "checkYes.png");

	//设置CheckBox的位置    
	_CheckBox->setPosition((Vec2)viewSize / 2 + Vec2(130, -15));

	//设置CheckBox是否可点击  
	_CheckBox->setTouchEnabled(true);

	//获取checkbox的选中状态
	//selected 值为true 时 checkbox 为选中状态, 为false 则不会
	bool selected = _CheckBox->getSelectedState();

	addChild(_CheckBox);


	//绑定回调函数
	_CheckBox->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == ui::CheckBox::EventType::SELECTED)
				Person::getInstance()->isCancel = true;
			else if (type == ui::CheckBox::EventType::UNSELECTED)
				Person::getInstance()->isCancel = false;
		}
	);


	label = Label::create("取消人物预制人物机制\nPs：全自动模式下由于\n程序逻辑的原因，请勿\n勾选该选项！！！", "GameFont.ttf", 24);
	label->setColor(Color3B::BLUE);
	label->setAnchorPoint(Vec2(0.5, 1)); //锚点在中间
	label->setTag(TAG_TOAST_LABEL);
	label->setPosition(_CheckBox->getPosition() - Vec2(145, -45));
	addChild(label);


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
	return true;
}

void stopMessageBox::registerCallback(std::function<void()>continueCallback, std::function<void()>
	endgameCallback)
{
	continueFunc = continueCallback;
	endGamefunc = endgameCallback;
}


void stopMessageBox::onEnter()
{
	Layer::onEnter();
	Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* bea = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	Sequence* cir = Sequence::create(EaseElasticIn::create(ScaleTo::create(0.0f, 0.0f, 0.0f)),
		EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f)), NULL);
	box->runAction(seq);
	continue_Btn->runAction(bea);
	end_gameBtn->runAction(cir);
}

//void stopMessageBox::SoundEffectMusicVolumeChangeCallBack(Ref* sender, Control::EventType type)
//{
//	/* 设置音效音量 */
//	GlobalMusic.SoundEffect = ((ControlSlider*)sender)->getValue() / 100.0f;
//	userdefault->setFloatForKey("SOUNDEFFECT", GlobalMusic.SoundEffect);
//}


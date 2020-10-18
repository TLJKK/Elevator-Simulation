#include "BgScene.h"
#include "HelloWorldScene.h"
#include "gameOver.h"
#include "messageBox.h"
#include "stopMessage.h"
#include "choose.h"
#include "help.h"
#include "Person.h"

#pragma execution_character_set("utf-8")
USING_NS_CC;


Scene* Bg::create_Scene()
{
	auto scene = Scene::create();

	auto layer = Bg::create();

	scene->addChild(layer);

	return scene;
}

bool Bg::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	Size size = Director::getInstance()->getVisibleSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	CCDirector::getInstance()->setDisplayStats(false);
	initBG();
	/*auto m_emitter1 = ParticleSystemQuad::create("Snow.plist");
	m_emitter1->retain();
	m_emitter1->setPosition(1700, 800);
	m_emitter1->release();
	addChild(m_emitter1, 10);*/
	
	initUI();
	
	return true;
}

void Bg::initUI()
{
	game_Logo = Sprite::create("game_logo.png");
	game_Logo->setScale(0.8f);
	game_Logo->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 160);
	addChild(game_Logo);
	star_Btn = ui::Button::create("play2.png");
	star_Btn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 40));
	addChild(star_Btn);
	star_Btn->setScale(0.45);
	exit_Btn = ui::Button::create("exit.png");
	exit_Btn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 220));
	addChild(exit_Btn);
	schedule(schedule_selector(Bg::timer_hander), 0);

	auto helper = ui::Button::create("helpBtn.png");
	helper->setPosition((Vec2)Director::getInstance()->getVisibleSize() - Vec2(40, 40));
	addChild(helper);
	helper->setScale(0.55);

	helper->addClickEventListener([=](Ref* ref)
		{
			auto helpBox = help::create();
			helpBox->registerCallback([=]() {
				helpBox->removeFromParent();
				});
			this->addChild(helpBox);
			helpBox->to = this;
		});

	star_Btn->addClickEventListener([=](Ref* ref)
		{
			/*virtual void registerCallback(std::function<void()>allCallback, std::function<void()>
				halfCallback, std::function<void()>cancleCallback);*/
			auto chooseBox = choose::create();
			chooseBox->registerCallback(
				[=]()
				{
					Person::getInstance()->changeNum(0);
					auto tran = TransitionZoomFlipAngular::create(2, HelloWorld::createScene());
					Director::getInstance()->replaceScene(tran);
				},
				[=]() {
					Person::getInstance()->changeNum(1);
					auto tran = TransitionZoomFlipAngular::create(2, HelloWorld::createScene());
					Director::getInstance()->replaceScene(tran);
				},
					[=]() {
					chooseBox->removeFromParent();
				});
			this->addChild(chooseBox);
			chooseBox->to = this;
		});
	exit_Btn->addClickEventListener([=](Ref* ref)
		{
			unschedule(schedule_selector(Bg::timer_hander));
			auto pauseBox = BDMessageBox::create();
			pauseBox->registerCallback([=]() {
				pauseBox->to->schedule(schedule_selector(Bg::timer_hander), 0);
				pauseBox->removeFromParent();
				},
				[=]() 
				{
					Director::getInstance()->end();
				});
			this->addChild(pauseBox);
			pauseBox->to = this;
		});
}

void Bg::initBG()
{
	m_bgSprite1 = Sprite::create("1.jpg");
	Size bgSize = m_bgSprite1->getContentSize();
	m_bgSprite1->setPosition(Point(bgSize.width / 2, bgSize.height / 2));
	this->addChild(m_bgSprite1);

	m_bgSprite2 = Sprite::create("2.jpg");
	m_bgSprite2->setPosition(Point(bgSize.width + bgSize.width / 2 - 10, bgSize.height / 2));
	this->addChild(m_bgSprite2);
}
void Bg::timer_hander(float delta)
{
	int posX1 = m_bgSprite1->getPositionX();    //背景地图1的Y坐标
	int posX2 = m_bgSprite2->getPositionX();    //背景地图2的Y坐标

	int iSpeed = 4; //地图滚动速度

	/* 两张地图向左滚动（两张地图是相邻的，所以要一起滚动，否则会出现空隙） */
	posX1 -= iSpeed;
	posX2 -= iSpeed;

	/* 图大小 */
	Size bgSize = m_bgSprite1->getContentSize();

	/* 当第1个地图完全离开屏幕时，第2个地图刚好完全出现在屏幕上，这时候就让第1个地图紧贴在
	 第2个地图后面 */
	if (posX1 <= -bgSize.width / 2) {
		posX1 = bgSize.width + bgSize.width / 2;
	}
	/* 同理，当第2个地图完全离开屏幕时，第1个地图刚好完全出现在屏幕上，这时候就让第2
	 个地图紧贴在第1个地图后面 */
	if (posX2 <= -bgSize.width / 2) {
		posX2 = bgSize.width + bgSize.width / 2;
	}

	m_bgSprite1->setPositionX(posX1);
	m_bgSprite2->setPositionX(posX2);

}

void Bg::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include"HelloWorldScene.h"
#include"Person.h"
#include"spine/spine-cocos2dx.h"
#include<timeapi.h>
#include"Elavator.h"
#include"WorldTime.h"
#include"stopMessage.h"
#include<ui/CocosGUI.h>
#include"messageBox.h"
#include"spine/spine.h"
#include"SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	//CreateTag = 0;
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	CCDirector::getInstance()->setDisplayStats(false);
	
	Person::getInstance()->init();
	Elavator::getInstance()->init();

	timeBegin = WorldTime::getInstance()->getTime();
	timeNow = Label::create("??????", "GameFont.ttf", 22);
	timeNow->setAnchorPoint(Vec2(0.5, 0.5));
	//(1024, 768);
	timeNow->setPosition(Vec2(532, 740));
	addChild(timeNow, 30);

	float scale_now = 0.42;
	float bg_x = 42;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto Sky = Sprite::create("sky.jpg");
	Sky->setAnchorPoint(Vec2(0, 0));
	Sky->setPosition(Vec2(0, 100));
	addChild(Sky);
	auto bg1 = Sprite::create("bg.jpg");
	bg1->setAnchorPoint(Vec2(0, 0));
	bg1->setPosition(Vec2(bg_x, visibleSize.height / 2+150));
	bg1->setScale(scale_now);
	addChild(bg1);
	auto bg2 = Sprite::create("bg2.jpg");
	bg2->setAnchorPoint(Vec2(0, 0));
	bg2->setPosition(Vec2(bg_x, bg1->getPositionY() - bg1->getBoundingBox().size.height));
	bg2->setScale(scale_now);
	addChild(bg2);
	auto bg3 = Sprite::create("bg2.jpg");
	bg3->setAnchorPoint(Vec2(0, 0));
	bg3->setPosition(Vec2(bg_x, bg2->getPositionY() - bg2->getBoundingBox().size.height));
	bg3->setScale(scale_now);
	addChild(bg3);
	auto bg4 = Sprite::create("bg2.jpg");
	bg4->setAnchorPoint(Vec2(0, 0));
	bg4->setPosition(Vec2(bg_x, bg3->getPositionY() - bg3->getBoundingBox().size.height));
	bg4->setScale(scale_now);
	addChild(bg4);
	auto bg5 = Sprite::create("bg2.jpg");
	bg5->setAnchorPoint(Vec2(0, 0));
	bg5->setPosition(Vec2(bg_x, bg4->getPositionY() - bg4->getBoundingBox().size.height));
	bg5->setScale(scale_now);
	addChild(bg5);
	auto Road = Sprite::create("road.png");
	Road->setAnchorPoint(Vec2(0, 0));
	Road->setPosition(Vec2(0, 0));
	Road->setScaleX(0.462);
	Road->setScaleY(0.61);
	addChild(Road);
/////////////////////////////////////模式区分/////////////////////////////////////////////////////
	if (1 == Person::getInstance()->SceneNum)
	{
		
		ui::Button* floor0, * floor1, * floor2, * floor3, * floor4;

		floor0 = ui::Button::create("join0.png");
		floor1 = ui::Button::create("join1.png");
		floor2 = ui::Button::create("join2.png");
		floor3 = ui::Button::create("join3.png");
		floor4 = ui::Button::create("join4.png");

		floor0->setScale(0.5);
		floor0->setPosition(Vec2(980, 60));
		addChild(floor0, 2);
		floor0->addClickEventListener([this](Ref* ref) {
			Person::getInstance()->Prefab(this, 0);
			});

		floor1->setScale(0.5);
		floor1->setPosition(Vec2(990, 60) +
			Vec2(0, bg4->getBoundingBox().size.height + 10));
		addChild(floor1, 2);
		floor1->addClickEventListener([this](Ref* ref) {
			Person::getInstance()->Prefab(this, 1);
			});

		floor2->setScale(0.6);
		floor2->setPosition(Vec2(990, 60) +
			Vec2(0, bg4->getBoundingBox().size.height) * 2);
		addChild(floor2, 2);
		floor2->addClickEventListener([this](Ref* ref) {
			Person::getInstance()->Prefab(this, 2);
			});

		floor3->setScale(0.6);
		floor3->setPosition(Vec2(990, 60) +
			Vec2(0, bg4->getBoundingBox().size.height) * 3);
		addChild(floor3, 2);
		floor3->addClickEventListener([this](Ref* ref) {
			Person::getInstance()->Prefab(this, 3);
			});

		floor4->setScale(0.6);
		floor4->setPosition(Vec2(990, 60) +
			Vec2(0, bg4->getBoundingBox().size.height) * 4
			+ Vec2(0, 10));
		addChild(floor4, 2);
		floor4->addClickEventListener([this](Ref* ref) {
			Person::getInstance()->Prefab(this, 4);
			});
	}
//////////////////////////////////////////////////////////////////////////////////////////
	float* height = Elavator::getInstance()->heigh;
	height[0] = bg5->getPositionY() - 9;
	for (int i = 1; i < 5; i++)
		height[i] = height[i - 1] + bg5->getBoundingBox().size.height;
	for (int i = 0; i < 5; i++)
	{
		Person::getInstance()->ali[i] = new Person::PersonNews;
		Person::getInstance()->ali[i]->skeleton = NULL;
		Person::getInstance()->ali[i]->pre = Person::getInstance()->ali[i]->next = NULL;
		Person::getInstance()->aliTail[i] = Person::getInstance()->ali[i];
		Person::getInstance()->ali[i]->Pos = Vec2(155, height[i] + 25);
	}
	Person::getInstance()->height = height;
	auto Body = Elavator::getInstance()->Body = Sprite::create("Body.png");
	Body->setAnchorPoint(Vec2(0, 0));
	Body->setPosition(Vec2(0, height[1]));
	Body->setScaleY(0.56);
	Body->setScaleX(0.55);
	//addChild(Body);
	//Body->retain();
	

	
	auto LeftDoor = Elavator::getInstance()->LeftDoor = Sprite::create("leftDoor.png");
	LeftDoor->setAnchorPoint(Vec2(0, 0));
	LeftDoor->setPosition(Body->getPosition());//Body->getPosition()Vec2(500, 200)
	LeftDoor->setScale(0.55, 0.28);
	//LeftDoor->retain();

	auto RightDoor = Elavator::getInstance()->RightDoor = Sprite::create("rightDoor.png");
	RightDoor->setAnchorPoint(Vec2(1, 1));
	RightDoor->setPosition(Body->getPosition() + Vec2(LeftDoor->getBoundingBox().size.width*2,
		LeftDoor->getBoundingBox().size.height
		));//Body->getPosition()Vec2(500, 200)
	RightDoor->setScale(0.55, 0.28);// + Vec2(Body->getBoundingBox().size.width, 0)
	///RightDoor->retain();

	Vec2* Pos = Elavator::getInstance()->ElavatorPos;
	Pos[0].x = 20;
	for (int i = 1; i < 4; i++)
		Pos[i] = Pos[i - 1] + Vec2(30, 0); //Body->getPosition();

	
	addChild(Elavator::getInstance()->Body, 1, -2);
	addChild(Elavator::getInstance()->LeftDoor, 10, -2);
	addChild(Elavator::getInstance()->RightDoor, 10, -2);
	///Elavator::getInstance()->num0
	//Sequence* seq = Sequence::create(EaseElasticIn::create(ScaleTo::create(1.5, 0.5)),
	//	EaseElasticOut::create(ScaleTo::create(1.5, 1.0)), NULL);num_0->runAction(Blink::create(2, 2));
	auto num0 = Elavator::getInstance()->Elavator::getInstance()->num0 = Sprite::create("0.png");
	Elavator::getInstance()->recolor = num0->getColor();
	num0->setScale(0.8);
	num0->setPosition(Vec2(70, 60 + bg5->getBoundingBox().size.height * 0));
	addChild(num0);

	auto num1 = Elavator::getInstance()->Elavator::getInstance()->num1 = Sprite::create("1.png");
	num1->setScale(0.8);
	num1->setPosition(Vec2(70, 60 + bg5->getBoundingBox().size.height * 1));
	addChild(num1);

	auto num2 = Elavator::getInstance()->Elavator::getInstance()->num2 = Sprite::create("2.png");
	num2->setScale(0.8);
	num2->setPosition(Vec2(70, 60 + bg5->getBoundingBox().size.height * 2));
	addChild(num2);

	auto num3 = Elavator::getInstance()->Elavator::getInstance()->num3 = Sprite::create("3.png");
	num3->setScale(0.8);
	num3->setPosition(Vec2(70, 60 + bg5->getBoundingBox().size.height * 3));
	addChild(num3);

	auto num4 = Elavator::getInstance()->Elavator::getInstance()->num4 = Sprite::create("4.png");
	num4->setScale(0.8);
	num4->setPosition(Vec2(70, 60 + bg5->getBoundingBox().size.height * 4));
	addChild(num4);

	num0->setColor(Color3B(0, 0, 0));
	num1->setColor(Color3B(0, 0, 0));
	num2->setColor(Color3B(0, 0, 0));
	num3->setColor(Color3B(0, 0, 0));
	num4->setColor(Color3B(0, 0, 0));

	/*ParticleSystem* m_emitter1 = ParticleSystemQuad::create("snow.plist");
	m_emitter1->retain();
	m_emitter1->setPosition(1700, 1450);
	m_emitter1->release();
	addChild(m_emitter1, 20);*/

	

	auto stop_Btn = ui::Button::create("stop1.png");
	stop_Btn->setScale(0.6);
	stop_Btn->setPosition(Point(visibleSize.width - 34, visibleSize.height - 34));
	addChild(stop_Btn, 10);
	stop_Btn->addClickEventListener([=](Ref* ref)
		{
			unschedule(schedule_selector(HelloWorld::TimeHander));
			auto on = stopMessageBox::create();
			WorldTime::getInstance()->DelayBegin = clock();
			on->to = this;
			this->stopAllActions();
			on->registerCallback
			([=]() {
				WorldTime::getInstance()->DelayEnd = clock();
				WorldTime::getInstance()->DelayTime += WorldTime::getInstance()->DelayEnd -
					WorldTime::getInstance()->DelayBegin;
				on->to->resumeSchedulerAndActions();
				on->to->schedule(schedule_selector(HelloWorld::TimeHander), 0);
				on->removeFromParent();
				},
				[=]()
				{
					//on->to->schedule(schedule_selector(HelloWorld::tiemer_hander), 0);
					on->removeFromParent();
					auto tran = TransitionZoomFlipAngular::create(2, Bg::create_Scene());
					Director::getInstance()->replaceScene(tran);
				});
			this->addChild(on, 12);
		});


	Person::getInstance()->Mouse = EventListenerMouse::create();
	Person::getInstance()->Mouse->onMouseMove = [this](Event* event)
	{
		Person::getInstance()->Cur = ((EventMouse*)event)->getLocationInView();
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Person::getInstance()->Mouse,
		this);

	timeNow->setColor(Color3B::RED);
	addChild(Person::getInstance()->box, 30);
	schedule(schedule_selector(HelloWorld::TimeHander, 0));

    return true;
}

void HelloWorld::TimeHander(float dt)
{
	//clock();
	timeNow->setString("模拟进行至第" + Person::getInstance()->anythingToString(
		(WorldTime::getInstance()->getTime() - timeBegin) / CLOCKS_PER_SEC * 1.0) + "秒");
	Elavator::getInstance()->UpdataWithScene();
	Person::getInstance()->UpdataWithScene(this);
	Elavator::getInstance()->Proj();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


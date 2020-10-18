#include "Person.h"
#include<ctime>
#include<cmath>
#include "Elavator.h"
#include<Windows.h>
#include<sstream>
#include<string>
#include "WorldTime.h"
#include "messageBox.h"
USING_NS_CC;

Person* Person::_instance = nullptr;

Person* Person::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)Person;

		//_instance->init();
	}
	return _instance;
}

bool Person::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	NoOne = 0;
	CreateTag = 0;
	leave = new PersonNews;
	leave->next = leave->pre = NULL;
	leaveTail = leave;
	Elava = new PersonNews;
	Elava->skeleton = NULL;
	Elava->pre = Elava->next = NULL;
	ElavaTail = Elava;
	ElavaNum = 0;
	isCancel = false;
	auto viewSize = Director::getInstance()->getVisibleSize();

	box = Sprite::create("PersonNews.png");

	box->setPosition(viewSize / 2);

	box->setAnchorPoint(Vec2(1, 0));


	label1 = Label::create("进入系统时间：", "GameFont.ttf", 20);
	label1->setColor(Color3B::BLUE);
	label1->setAnchorPoint(Vec2(1, 0.5)); //锚点在中间
	label1->setTag(TAG_TOAST_LABEL);
	/* - Vec2(box->getBoundingBox().size.width,
		-box->getBoundingBox().size.height)*/
	box->addChild(label1);

	label2 = Label::create("放弃乘坐电梯：", "GameFont.ttf", 20);
	label2->setColor(Color3B::BLUE);
	label2->setAnchorPoint(Vec2(1, 0.5)); //锚点在中间
	label2->setTag(TAG_TOAST_LABEL);
	/* - Vec2(box->getBoundingBox().size.width,
		-box->getBoundingBox().size.height)*/
	box->addChild(label2);

	label3 = Label::create("距下一个人来：", "GameFont.ttf", 20);
	label3->setColor(Color3B::BLUE);
	label3->setAnchorPoint(Vec2(1, 0.5)); //锚点在中间
	label3->setTag(TAG_TOAST_LABEL);
	/* - Vec2(box->getBoundingBox().size.width,
		-box->getBoundingBox().size.height)*/
	box->addChild(label3);

	label4 = Label::create("该人物来自：", "GameFont.ttf", 20);
	label4->setColor(Color3B::BLUE);
	label4->setAnchorPoint(Vec2(1, 0.5)); //锚点在中间
	label4->setTag(TAG_TOAST_LABEL);
	/* - Vec2(box->getBoundingBox().size.width,
		-box->getBoundingBox().size.height)*/
	box->addChild(label4);

	label5 = Label::create("人物目标楼层：", "GameFont.ttf", 20);
	label5->setColor(Color3B::BLUE);
	label5->setAnchorPoint(Vec2(1, 0.5)); //锚点在中间
	label5->setTag(TAG_TOAST_LABEL);
	box->addChild(label5);

	label11 = Label::create("?????", "GameFont.ttf", 20);
	label11->setColor(Color3B::BLUE);
	label11->setAnchorPoint(Vec2(0, 0.5));
	label11->setTag(TAG_TOAST_LABEL);
	box->addChild(label11);

	label22 = Label::create("?????", "GameFont.ttf", 20);
	label22->setColor(Color3B::BLUE);
	label22->setAnchorPoint(Vec2(0, 0.5));
	label22->setTag(TAG_TOAST_LABEL);
	box->addChild(label22);

	label33 = Label::create("?????", "GameFont.ttf", 20);
	label33->setColor(Color3B::BLUE);
	label33->setAnchorPoint(Vec2(0, 0.5));
	label33->setTag(TAG_TOAST_LABEL);
	box->addChild(label33);

	label44 = Label::create("?????", "GameFont.ttf", 20);
	label44->setColor(Color3B::BLUE);
	label44->setAnchorPoint(Vec2(0, 0.5));
	label44->setTag(TAG_TOAST_LABEL);
	box->addChild(label44);

	label55 = Label::create("?????", "GameFont.ttf", 20);
	label55->setColor(Color3B::BLUE);
	label55->setAnchorPoint(Vec2(0, 0.5));
	label55->setTag(TAG_TOAST_LABEL);
	box->addChild(label55);

	box->setScaleX(0.7);
	box->setScaleY(0.8);

	label1->setPosition(Vec2(150, 140));
	label2->setPosition(Vec2(150, 110));
	label3->setPosition(Vec2(150, 80));
	label4->setPosition(Vec2(150, 50));
	label5->setPosition(Vec2(150, 20));

	label11->setPosition(Vec2(150, 140));
	label22->setPosition(Vec2(150, 110));
	label33->setPosition(Vec2(150, 80));
	label44->setPosition(Vec2(150, 50));
	label55->setPosition(Vec2(150, 20));

	box->setPosition(Vec2(-1000, -1000));

	WindowsTo = nullptr;

	return true;
}


void Person::BDUpdata(Person::PersonNews* PN)
{
//	std::string
	label11->setString("第" + anythingToString(PN->Born / CLOCKS_PER_SEC * 1.0) + "秒");
	label22->setString("剩余"+anythingToString(PN->GiveUpTime
		- (WorldTime::getInstance()->getTime() - PN->Born) / CLOCKS_PER_SEC * 1.0) + "秒");
	label33->setString(anythingToString(PN->NextPerson
		- (WorldTime::getInstance()->getTime() - PN->Born) / CLOCKS_PER_SEC * 1.0) + "秒");
	label44->setString("第" + anythingToString(PN->inFloor) + "层");
	label55->setString("第" + anythingToString(PN->OutFloor) + "层");
	
}

void Person::changeNum(int sk)
{
	this->SceneNum = sk;
}

void Person::UpdataWithScene(Node* SimulateScene)
{
	if (!SceneNum)
	{
		srand(time(NULL));
		if (NoOne < 100 && 4 == rand() % 10 || !NoOne)
		{
			Prefab(SimulateScene);
			NoOne++;
		}
	}

	if (WindowsTo != nullptr && WindowsTo && WindowsTo->skeleton != nullptr &&
		!WindowsTo->skeleton->getBoundingBox().containsPoint(Cur))
		box->setPosition(Vec2(-1000, -1000)), WindowsTo = nullptr;
		
	auto ElavatorPerson =Elava->next;
	while (ElavatorPerson)
	{
		if (ElavatorPerson->NextPerson - (WorldTime::getInstance()->getTime() - ElavatorPerson->Born) / CLOCKS_PER_SEC * 1.0 < 0)
		{
			/*SimulateScene->removeChildByTag(now->Tag);*/
			if (!ElavatorPerson->NxtCome)
			{
				ElavatorPerson->NxtCome = true;
				Prefab(SimulateScene);
			}
		}
		ElavatorPerson = ElavatorPerson->next;//程序突然卡死没有报任何错，不怕程序报错，就怕程序错了还不报，
		//吓死我了。。。。。。。。。。。。。。。
	}


	for (int i = 0; i < 5; i++)
	{
		
		PersonNews* now = ali[i]->next;
		if (!now)continue;
		while (now)
		{
			if (now->skeleton->getBoundingBox().containsPoint(Cur))
			{
				WindowsTo = now;
				box->setPosition(now->skeleton->getPosition() + Vec2(120, 100));
				BDUpdata(now);
			}

			//director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Mouse, this);


			//ske->runAction(MoveTo::create(2.0f, Vec2(aliTail[floor]->Pos + Vec2(55, 0))));
			now->Pos = now->pre->Pos + Vec2(55, 0);
			if (now->skeleton->getPositionX() <= now->Pos.x)
			{
				if (!now->NowAnimation)
					now->skeleton->addAnimation(0, "idle", true), now->NowAnimation = 1;
				if (0 == now->UDdirection)Elavator::getInstance()->CallUp[now->inFloor] = 1;
				else Elavator::getInstance()->CallDown[now->inFloor] = 1;
			}
			else
			{
				now->skeleton->setPosition(now->skeleton->getPosition() - Vec2(2, 0));
				if (now->NowAnimation)
					now->skeleton->addAnimation(0, "walk", true), now->NowAnimation = 0;
			}
				

			if (now->NextPerson - (WorldTime::getInstance()->getTime() - now->Born) / CLOCKS_PER_SEC * 1.0 < 0)
			{
				/*SimulateScene->removeChildByTag(now->Tag);*/
				if (!now->NxtCome)
				{
					now->NxtCome = true;
					Prefab(SimulateScene);
				}
			}

			bool isLeave = false;
			if (now->GiveUpTime - (WorldTime::getInstance()->getTime() - now->Born) / CLOCKS_PER_SEC * 1.0 < 0
				&& Elavator::getInstance()->FloorNow != now->inFloor)
			{
				//SimulateScene->removeChildByTag(now->Tag);
				if (now->next)now->pre->next = now->next, now->next->pre = now->pre;
				else aliTail[i] = now->pre, now->pre->next = nullptr;
				auto angry = now;
				now = now->next;
				angry->pre = angry->next = nullptr;
				leaveTail->next = angry;
				angry->pre = leaveTail;
				leaveTail = angry;
				isLeave = true;
				angry->skeleton->getSkeleton()->flipX = 0;
				angry->skeleton->addAnimation(0, "walk", true);
				angry->skeleton->removeChildByTag(1);
				angry->skeleton->runAction(MoveTo::create(15.0f, Vec2(angry->skeleton->getPosition() + Vec2(1300, 0))));
			}
			if (!isLeave)now = now->next;
		}
	}

	auto leavePerson = leave->next;
	while (leavePerson)
	{

		if (leavePerson->NextPerson - (WorldTime::getInstance()->getTime() - leavePerson->Born) / CLOCKS_PER_SEC * 1.0 < 0)
		{
			/*SimulateScene->removeChildByTag(now->Tag);*/
			if (!leavePerson->NxtCome)
			{
				leavePerson->NxtCome = true;
				Prefab(SimulateScene);
			}
		}

		bool isDelete = false;
		if (leavePerson->skeleton->getPositionX() > 1200)
		{
			isDelete = true;
			SimulateScene->removeChildByTag(leavePerson->Tag);
			if (leavePerson->next)
			{
				leavePerson->pre->next = leavePerson->next;
				leavePerson->next->pre = leavePerson->pre;
				auto del = leavePerson;
				leavePerson = leavePerson->next;
				delete del;
			}
			else
			{
				leavePerson->pre->next = NULL;
				delete leavePerson;
				leavePerson = NULL;
			}
		}
		if (!isDelete)leavePerson = leavePerson->next;
	}
	//if (now.NextPerson - (WorldTime::getInstance()->getTime() - now.Born) / CLOCKS_PER_SEC < 0)	
}

Person::PersonNews* Person::Prefab(Node* SimulateScene)
{
	srand(time(NULL));
	int floor = rand() % 5;
	return Prefab(SimulateScene, floor);
}
//, int floor
Person::PersonNews* Person::Prefab(Node* SimulateScene, int floorNow)
{
	srand(time(NULL));
	int floor = floorNow;
	auto ske = spine::SkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas", 0.30f);
	ske->addAnimation(0, "walk", true);
	ske->setPosition(aliTail[floor]->Pos + Vec2(1100, 0));
	/*ske->runAction(MoveTo::create(2.0f, Vec2(aliTail[floor]->Pos + Vec2(55, 0))));*/
	ske->getSkeleton()->flipX = -1;
	num++;
	SimulateScene->addChild(ske, 1, ++CreateTag);

	PersonNews* now = new PersonNews;
	now->id = 1;
	now->skeleton = ske;
	now->NextPerson = 30.0 + rand() % 20;
	now->Born = WorldTime::getInstance()->getTime();
	now->GiveUpTime = 50.0 + rand() % 35;
	now->inFloor = floor;
	now->NowAnimation = 0;
	int go = -1;
	while (1) { go = rand() % 5; if (go != floor)break; }
	now->OutFloor = go;
	now->Tag = CreateTag;
	now->NxtCome = false;
	now->pre = now->next = nullptr;
	if (go > floor)
	{
		auto front = Sprite::create("up.png");
		front->runAction(RepeatForever::create(Blink::create(2.0, 1)));
		front->setPosition(Vec2(0, 100));
		front->setScale(0.3);
		ske->addChild(front, 10, 1);
		now->UDdirection = 0;//,Elavator::getInstance()->CallUp[floor] = 1
	}
	else
	{
		auto front = Sprite::create("down.png");
		front->runAction(RepeatForever::create(Blink::create(2.0, 1)));
		front->setPosition(Vec2(2, 0));
		front->setScale(0.7);
		ske->addChild(front, 10, 1);
		now->UDdirection = 1;//, Elavator::getInstance()->CallDown[floor] = 1
	}
	aliTail[floor]->next = now, now->pre = aliTail[floor];
	now->Pos = aliTail[floor]->Pos + Vec2(55, 0);
	aliTail[floor] = now;
	if (isCancel)
		now->NextPerson = 999999999.0f;
	return now;
}


//ui::CheckBox::ccCheckBoxCallback Person::checkBoxCallback(cocos2d::Ref* ref, ui::CheckBox::EventType type)
//{
//	switch (type)
//	{
//	case cocos2d::ui::CheckBox::EventType::SELECTED:
//		Person::getInstance()->isCancel = true;
//		break;
//	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
//		Person::getInstance()->isCancel = false;
//		break;
//	default:
//		break;
//	}
//}

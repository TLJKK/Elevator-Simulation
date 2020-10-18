#pragma once
#include <cocos2d.h>
#include<spine/spine-cocos2dx.h>
#include<vector>
#include "HelloWorldScene.h"
#include<spine/spine.h>
#include<string>
#include<ui/CocosGUI.h>
#include<iostream>
USING_NS_CC;

class Person :public Sprite
{
public:
	//ui::Button* floor0, * floor1, * floor2, * floor3, * floor4; //push to the HW Scene at auto release
	typedef struct kk
	{
		spine::SkeletonAnimation* skeleton;
		clock_t Born;
		int inFloor, OutFloor, Tag;
		float NextPerson, GiveUpTime;
		bool isGiveUp, NxtCome;
		int id;// 0 boy 1 dragon
		int NowAnimation;//0 walk 1 idle
		int AnimationState;//0 idle 1 walk 
		int LRdirection, UDdirection; // -1 left 1 right 0 Up 1 Down
		struct kk* next, * pre;
		Vec2 Pos;

	}PersonNews;
	enum State { M1 = 1, M2, M3, M4, M5, M6 };
	float* height;
	int NoOne;
	int test = 0;
	CREATE_FUNC(Person);
	virtual bool init();
	PersonNews* ali[5], * aliTail[5];//在各楼层之中 0 up 1 down
	PersonNews* Elava, * ElavaTail;//在电梯里面
	PersonNews* leave, * leaveTail;
	int ElavaNum;
	float MoveSpeed;
	void UpdataWithScene(Node* SimulateScene);
	int CreateTag;
	PersonNews* Prefab(Node* SimulateScene);
	PersonNews* Prefab(Node* SimulateScene, int floorNow);
	static Person* getInstance();
	void BDUpdata(PersonNews* PN);
	PersonNews* WindowsTo;
	Sprite* box;
	Label* label1, * label2, * label3, * label4, * label5;
	Label* label11, * label22, * label33, * label44, * label55;
	Vec2 Cur;
	//ui::CheckBox::ccCheckBoxCallback checkBoxCallback(cocos2d::Ref* ref, ui::CheckBox::EventType type);
	bool isCancel;
	cocos2d::EventListenerMouse* Mouse;
	template<class T>
	std::string anythingToString(T anything)
	{
		std::stringstream ss;
		ss << anything;
		std::string ans;
		ss >> ans;
		return ans;
	};
	void changeNum(int sk);
	int SceneNum;//0 自动 1 半自动
private:
	static Person* _instance;
	

	int num = 0;
};


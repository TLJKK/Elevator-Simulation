#pragma once
#include<cocos2d.h>
#include<queue>
#include "Person.h"
USING_NS_CC;

class Elavator :public Sprite
{
public:
	struct tmpPlan
	{
		clock_t Born;
		float Sustain;
		int Destination;
		tmpPlan* next, * pre;
	};
	struct Moving
	{
		clock_t Born;
		float Sustain;
		bool leagal;
	};
	CREATE_FUNC(Elavator);
	Color3B recolor;
	Sprite* num0, * num1, * num2, * num3, * num4, * num5;
	virtual bool init();
	static Elavator* getInstance();
	float heigh[5];
	Vec2 ElavatorPos[4];
	bool CallUp[5], CallDown[5], CallCar[5], comein;
	float floorHeight[5];
	int StateForMove;//0 idle 1 up 2 down
	int StateForE;
	int StateReal;
	int FloorNow;//电梯现在的层数
	int CallE6;
	bool D1, D2, D3;
	int BlinkOr[5];
	enum E { E1 = 1, E2, E3, E4, E5, E6, E7, E8, E9 };
	enum Move { idle, up, down };
	enum Status { Opening = 1, Opened, Closing, Closed, Waiting, Down_Moving, Up_Moving, Decelerate, Accelerate };
	void UpdataWithScene();
	void Proj();
	void Controler(int Caller);
	void openDoor();
	void closeDoor();
	void E1Func();
	void E2Func(); 
	void E3Func(); 
	void E4Func(); 
	void E5Func(); 
	void E6Func(int Caller); 
	void E7Func();
	void E8Func(); 
	void E9Func();
	Person* PersonInstance;//单例
	Sprite* Body, * LeftDoor, * RightDoor;
private:
	
	static Elavator* _instance;
	tmpPlan* _plan;
	struct Moving MoveThread, DoorThread, ToE1Thread, ToE2Thread, ToE3Thread, ToE4Thread, ToE5Thread;
	struct Moving ToE6Thread, ToE7Thread, ToE8Thread, ToE9Thread, ToD1Thread, test;
};

//DI ——值为0，除非人们正在进入和离开电梯；
//D2 ——值为0，如果电梯已经在某层停候30Ot以上；
//D3 ——值为0，除非电梯门正开着又无人迸出电梯；
//State ——电梯的当前状态(GoingUp，GoingDOWEl，Idle)。

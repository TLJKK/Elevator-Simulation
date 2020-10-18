#include "Elavator.h"
#include "WorldTime.h"
#include<cmath>
Elavator* Elavator::_instance = nullptr;

Elavator* Elavator::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)Elavator;
		//_instance->init();
	}
	return _instance;
}

bool Elavator::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	test.Born = WorldTime::getInstance()->getTime();
	test.leagal = true;
	test.Sustain = 15.0f;

	MoveThread.leagal = DoorThread.leagal = ToE1Thread.leagal = ToE2Thread.leagal = ToE3Thread.leagal
		= ToE4Thread.leagal = ToE5Thread.leagal = ToE6Thread.leagal = ToE7Thread.leagal = ToE8Thread.leagal
		= ToE9Thread.leagal = ToD1Thread.leagal = 0;
	
	PersonInstance = Person::getInstance();
	_plan = new tmpPlan;
	comein = false;
	FloorNow = 1;
	D1 = D2 = D3 = 0;
	StateForMove = idle;
	StateForE = E1;
	StateReal = Waiting;
	for (int i = 0; i < 5; i++)
		CallUp[i] = CallDown[i] = CallCar[i] = BlinkOr[i] = 0;

	return true;
}

void Elavator::UpdataWithScene()
{
	if (test.leagal)
		if (test.Sustain - (WorldTime::getInstance()->getTime() - test.Born) / CLOCKS_PER_SEC * 1.0 < 0)
			test.leagal = false;

	for (int i = 0; i < 5; i++)
	{
		if (CallCar[i]&& !BlinkOr[i])
		{
			switch (i)
			{
			case 0:num0->setColor(recolor); num0->runAction(Blink::create(2, 2)); break;
			case 1:num1->setColor(recolor); num1->runAction(Blink::create(2, 2)); break;
			case 2:num2->setColor(recolor); num2->runAction(Blink::create(2, 2)); break;
			case 3:num3->setColor(recolor); num3->runAction(Blink::create(2, 2)); break;
			case 4:num4->setColor(recolor); num4->runAction(Blink::create(2, 2)); break;
			default:break;
			}
			BlinkOr[i] = 1;
		}
		if (!CallCar[i] && BlinkOr[i])
		{
			switch (i)
			{
			case 0:num0->setColor(Color3B(0, 0, 0)); break;
			case 1:num1->setColor(Color3B(0, 0, 0)); break;
			case 2:num2->setColor(Color3B(0, 0, 0)); break;
			case 3:num3->setColor(Color3B(0, 0, 0)); break;
			case 4:num4->setColor(Color3B(0, 0, 0)); break;
			default:break;
			}
			BlinkOr[i] = 0;
		}
	}

	for (int i = 0; i < 4; i++)
		ElavatorPos[i].y = Body->getPositionY() + 25;
	//	Pos[0] = Body->getPosition() + Vec2(20, height[0] + 25);
	auto ElavatorPerson = Person::getInstance()->Elava->next;
	int num = 0;
	while (ElavatorPerson)
	{
		if (fabs(ElavatorPerson->skeleton->getPositionX() - ElavatorPos[num].x) >= 0.0 &&
			fabs(ElavatorPerson->skeleton->getPositionX() - ElavatorPos[num].x) <= 4.0)
		{
			if (!ElavatorPerson->NowAnimation)
				ElavatorPerson->skeleton->addAnimation(0, "idle", true), ElavatorPerson->NowAnimation = 1;
			ElavatorPerson->skeleton->getSkeleton()->flipX = 0;
		}
		else
		{
			if (ElavatorPerson->NowAnimation)
				ElavatorPerson->skeleton->addAnimation(0, "walk", true), ElavatorPerson->NowAnimation = 0;
			int whi = ElavatorPerson->skeleton->getPositionX() > ElavatorPos[num].x ? -1 : 1;
			if (whi < 0)ElavatorPerson->skeleton->getSkeleton()->flipX = -1;
			else ElavatorPerson->skeleton->getSkeleton()->flipX = 0;
			ElavatorPerson->skeleton->setPositionX(ElavatorPerson->skeleton->getPositionX() + 2 * whi);
		}

		if (ElavatorPerson->skeleton->getPositionY() != ElavatorPos[num].y)
		{
			ElavatorPerson->skeleton->setPositionY(ElavatorPos[num].y);
		}
		num++;
		ElavatorPerson = ElavatorPerson->next;
	}
}

void Elavator::Proj()
{
	if (MoveThread.leagal)
		if (MoveThread.Sustain - (WorldTime::getInstance()->getTime() - MoveThread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
			MoveThread.leagal = false, StateReal = Waiting;

	if (DoorThread.leagal)
		if (DoorThread.Sustain - (WorldTime::getInstance()->getTime() - DoorThread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
			DoorThread.leagal = false, StateReal = Waiting;

	if (StateReal == Up_Moving)return;
	if (StateReal == Down_Moving)return;
	if (StateReal == Opening)return;
	if (StateReal == Closing)return;


	if (E5 == StateForE)E5Func();
	else if (E2 == StateForE)E2Func();
	else if (E3 == StateForE)E3Func();
	else if (E4 == StateForE)E4Func();
	else if (E6 == StateForE)E6Func(CallE6);
	else if (E7 == StateForE)E7Func();
	else if (E8 == StateForE)E8Func();
	else if (E1 == StateForE)E1Func();

	if (ToE9Thread.leagal)
	{
		if (1 == FloorNow)ToE9Thread.leagal = false;
		if (ToE9Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE9Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
			E9Func();
	}

	return;
}

void Elavator::Controler(int Caller)
{
	if (idle != StateForMove)return;
	if (CallUp[FloorNow] || CallDown[FloorNow] || CallCar[FloorNow])
	{
		//_plan.push(tmpPlan{ WorldTime::getInstance()->getTime(),2.0f,E3 });
		ToE3Thread.Born = WorldTime::getInstance()->getTime();
		ToE3Thread.leagal = true;
		ToE3Thread.Sustain = 2.0f;
		//ToE3Thread
		StateForE = E3;
		return;
	}//should open the door

	int hasButton = false, to = -1;
	for (int i = 0; i < 5; i++)
		if (CallCar[i]) { to = i; hasButton = 1; break; }
		else if (CallDown[i]) { to = i; hasButton = 1; break; }
		else if (CallUp[i]) { to = i; hasButton = 1; break; }

	if (!hasButton)
		if (E9 == Caller) { CallCar[1] = true; ToE9Thread.leagal = false; return; }
		else return;

	if (to > FloorNow)StateForMove = up;
	else if (to < FloorNow)StateForMove = down;

	if (E1 == Caller && FloorNow != to)
	{
		StateForE = E6;
		ToE6Thread.Born = WorldTime::getInstance()->getTime();
		ToE6Thread.leagal = true;
		ToE6Thread.Sustain = 2.0f;
		CallE6 = 0;
	}

}

void Elavator::E1Func()
{
	Controler(E1);
}

void Elavator::E2Func()
{
	/*[要改变状态 ? ] 如果电梯处于GoingUp(或GoingDown〉状态，
	但该方向的楼层却无人等待，则要看反方向楼层是否有人等候，
	而决定置State为GoingDown(或GoingUp〉还是Idle。*/

	if (ToE2Thread.leagal)
	{
		if (ToE2Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE2Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
		{
			ToE2Thread.leagal = false; 
		}
		return;
	}

	if (!ToE2Thread.leagal)
	{
		bool conti = true;

		if (up == StateForMove)
		{
			for (int i = FloorNow + 1; i < 5; i++)
				if (CallCar[i] || CallUp[i] || CallDown[i])break;
				else if (i == 4)conti = false;
			if (FloorNow == 4)conti = false;
			if (!conti)
				for (int i = FloorNow - 1; i >= 0; i--)
					if (CallCar[i] || CallUp[i] || CallDown[i]) { StateForMove = down; conti = true; break; }
		}
		else if (down == StateForMove)
		{
			for (int i = FloorNow - 1; i >= 0; i--)
				if (CallCar[i] || CallUp[i] || CallDown[i])break;
				else if (i == 0)conti = false;
			if (FloorNow == 0)conti = false;
			if (!conti)
				for (int i = FloorNow + 1; i < 5; i++)
					if (CallCar[i] || CallUp[i] || CallDown[i]) { StateForMove = up; conti = true; break; }
		}

		if (!conti)StateForMove = idle;

		CallE6 = E2;
		StateForE = E6;
		ToE6Thread.Born = WorldTime::getInstance()->getTime();
		ToE6Thread.leagal = true;
		ToE6Thread.Sustain = 0.2f;
		closeDoor();
		return;
	}

}

void Elavator::E3Func()
{
	//DI ——值为0，除非人们正在进入和离开电梯；
	//D2 ——值为0，如果电梯已经在某层停候30Ot以上；
	//D3 ——值为0，除非电梯门正开着又无人迸出电梯；
	//State ——电梯的当前状态(GoingUp，GoingDOWEl，Idle)。
	//_plan.push(tmpPlan{ WorldTime::getInstance()->getTime(),
		//30.0f,E9 });
	//_plan.push(tmpPlan{ WorldTime::getInstance()->getTime(),
		//7.6f,E5 });
	if (ToE3Thread.leagal)
	{
		if (ToE3Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE2Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
		{
			ToE3Thread.leagal = false;
			DoorThread.Born = WorldTime::getInstance()->getTime();
			DoorThread.leagal = true;
			DoorThread.Sustain = 2.0f;
			openDoor();
			StateReal = Opening;
		}
		return;
	}
	
	D1 = D2 = true;

	ToE9Thread.Born = WorldTime::getInstance()->getTime();
	ToE9Thread.leagal = true;
	ToE9Thread.Sustain = 30.0f;

	ToE5Thread.Born = WorldTime::getInstance()->getTime();
	ToE5Thread.leagal = true;
	ToE5Thread.Sustain = 4.6f;

	StateForE = E4;
}

void Elavator::E4Func()
{
	ToE9Thread.Born = WorldTime::getInstance()->getTime();
	ToE9Thread.leagal = true;
	ToE9Thread.Sustain = 30.0f;
	//ToE4Thread
	if (ToE4Thread.leagal)
	{
		if (ToE4Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE4Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
			ToE4Thread.leagal = false;
		return;
	}


	D1 = 1;
	auto PersonNow = PersonInstance->Elava->next;
	while (PersonNow)
	{
		bool to = true;
		if (PersonNow->OutFloor == FloorNow)
		{
			if (!PersonNow->next)
			{
				PersonInstance->ElavaTail = PersonNow->pre;
				PersonNow->pre->next = nullptr;
				PersonNow->pre = PersonNow->next = nullptr;
				PersonInstance->leaveTail->next = PersonNow;
				PersonNow->pre = PersonInstance->leaveTail;
				PersonInstance->leaveTail = PersonNow;
				PersonNow = PersonNow->next;
			}
			else
			{
				PersonNow->pre->next = PersonNow->next;
				PersonNow->next->pre = PersonNow->pre;
				auto kj = PersonNow;
				PersonNow = PersonNow->next;
				kj->pre = kj->next = nullptr;
				PersonInstance->leaveTail->next = kj;
				kj->pre = PersonInstance->leaveTail;
				PersonInstance->leaveTail = kj;
			}
			//if (0 == PersonInstance->leaveTail->id)
			PersonInstance->leaveTail->skeleton->addAnimation(0, "walk", true);
			PersonInstance->leaveTail->skeleton->runAction(MoveTo::create(8.0f, Vec2(
				1800, PersonInstance->leaveTail->skeleton->getPositionY())));
			//PersonInstance->leaveTail->skeleton->getSkeleton()->flipX = 1;//反转
			to = false;
			PersonInstance->ElavaNum--;
			StateForE = E4;
			ToE4Thread.Born = WorldTime::getInstance()->getTime();
			ToE4Thread.leagal = true;
			ToE4Thread.Sustain = 2.5f;
			return;
		}
		if (to)PersonNow = PersonNow->next;
	}


	if (PersonInstance->ElavaNum >= 4)
	{
		StateForE = E5;
		return;
	}

	if (idle == StateForMove)
	{
		auto per = PersonInstance->ali[FloorNow]->next;
		while (per)
		{
			
			if (per->Pos.x >= per->skeleton->getPositionX())//1 == per->UDdirection
			{
				PersonInstance->ElavaNum++;
				per->skeleton->removeChildByTag(1);
				CallCar[per->OutFloor] = 1;
				//////////////////////////////////////////////
				//per->skeleton->runAction(MoveTo::create(2.5f, ElavatorPos[PersonInstance->ElavaNum]));
				if (!per->next)
				{
					PersonInstance->aliTail[FloorNow] = per->pre;
					per->pre->next = nullptr;
					per->pre = per->next = nullptr;
					PersonInstance->ElavaTail->next = per;
					per->pre = PersonInstance->ElavaTail;
					PersonInstance->ElavaTail = per;
				}
				else
				{
					per->pre->next = per->next;
					per->next->pre = per->pre;
					per->pre = per->next = nullptr;
					PersonInstance->ElavaTail->next = per;
					per->pre = PersonInstance->ElavaTail;
					PersonInstance->ElavaTail = per;
				}
				StateForE = E4;
				ToE4Thread.Born = WorldTime::getInstance()->getTime();
				ToE4Thread.leagal = true;
				ToE4Thread.Sustain = 2.5f;
				return;
			}
			per = per->next;
		}
	}

	if (up == StateForMove)
	{
		bool hsaPeople = false;
		auto per = PersonInstance->ali[FloorNow]->next;
		while(per)
		{
			if (0 == per->UDdirection && per->Pos.x >= per->skeleton->getPositionX())
			{
				PersonInstance->ElavaNum++;
				per->skeleton->removeChildByTag(1);
				CallCar[per->OutFloor] = 1;
				//per->skeleton->runAction(MoveTo::create(0.2f, PersonInstance->ElavaTail->Pos + Vec2(0, 30)));
				if (!per->next)
				{
					PersonInstance->aliTail[FloorNow] = per->pre;
					per->pre->next = nullptr;
					per->pre = per->next = nullptr;
					PersonInstance->ElavaTail->next = per;
					per->pre = PersonInstance->ElavaTail;
					PersonInstance->ElavaTail = per;
				}
				else
				{
					per->pre->next = per->next;
					per->next->pre = per->pre;
					per->pre = per->next = nullptr;
					PersonInstance->ElavaTail->next = per;
					per->pre = PersonInstance->ElavaTail;
					PersonInstance->ElavaTail = per;
				}
				StateForE = E4;
				ToE4Thread.Born = WorldTime::getInstance()->getTime();
				ToE4Thread.leagal = true;
				ToE4Thread.Sustain = 2.5f;
				return;
			}
			per = per->next;
		}
		if (!PersonInstance->ElavaNum && PersonInstance->ali[FloorNow]->next &&
			PersonInstance->ali[FloorNow]->next->Pos.x - PersonInstance->ali[FloorNow]->next->skeleton->getPositionX() >= 0)
		{
			StateForMove = down;
			return;
		}
	}

	if (down == StateForMove)
	{
		auto per = PersonInstance->ali[FloorNow]->next;
		while(per)
		{
			//fabs(per->Pos.x-per->skeleton->getPositionX())>=0&& fabs(per->Pos.x - per->skeleton->getPositionX())<=4
			if (1 == per->UDdirection && per->Pos.x >= per->skeleton->getPositionX())
			{
				PersonInstance->ElavaNum++;
				CallCar[per->OutFloor] = 1;
				per->skeleton->removeChildByTag(1);
				//per->skeleton->runAction(MoveTo::create(0.2f, PersonInstance->ElavaTail->Pos + Vec2(0, 30)));
				if (!per->next)
				{
					PersonInstance->aliTail[FloorNow] = per->pre;
					per->pre->next = nullptr;
					per->pre = per->next = nullptr;
					PersonInstance->ElavaTail->next = per;
					per->pre = PersonInstance->ElavaTail;
					PersonInstance->ElavaTail = per;
				}
				else
				{
					per->pre->next = per->next;
					per->next->pre = per->pre;
					per->pre = per->next = nullptr;
					PersonInstance->ElavaTail->next = per;
					per->pre = PersonInstance->ElavaTail;
					PersonInstance->ElavaTail = per;
				}
				StateForE = E4;
				ToE4Thread.Born = WorldTime::getInstance()->getTime();
				ToE4Thread.leagal = true;
				ToE4Thread.Sustain = 2.5f;
				return;
			}
			per = per->next;
		}
		if (!PersonInstance->ElavaNum && PersonInstance->ali[FloorNow]->next &&
			PersonInstance->ali[FloorNow]->next->Pos.x - PersonInstance->ali[FloorNow]->next->skeleton->getPositionX() >= 0)
		{
			StateForMove = up;
			return;
		}
	}
	StateForE = E5;
	return;
}

void Elavator::E5Func()
{
	ToE9Thread.Born = WorldTime::getInstance()->getTime();
	ToE9Thread.leagal = true;
	ToE9Thread.Sustain = 30.0f;

	D3 = 1;

	if(ToE5Thread.leagal)
	{
		if (ToE5Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE5Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
			ToE5Thread.leagal = false;
		return;
	}

	if (PersonInstance->ElavaNum >= 4)
	{
		D1 = D3 = false;
		StateForE = E2;
		ToE2Thread.Born = WorldTime::getInstance()->getTime();
		ToE2Thread.leagal = true;
		ToE2Thread.Sustain = 0.2f;
		return;
	}

	if (D1)
	{
		if (down == StateForMove)
		{
			auto per = PersonInstance->ali[FloorNow]->next;
			bool go = false;
			while (per)
			{
				if (1 == per->UDdirection) { go = true; break; }
				per = per->next;
			}
			if (go)
			{
				StateForE = E4;
				ToE5Thread.Born = WorldTime::getInstance()->getTime();
				ToE5Thread.leagal = true;
				ToE5Thread.Sustain = 4.0f;
				return;
			}
		}
		else if (up == StateForMove)
		{
			auto per = PersonInstance->ali[FloorNow]->next;
			bool go = false;
			while (per)
			{
				if (0 == per->UDdirection) { go = true; break; }
				per = per->next;
			}
			if (go)
			{
				StateForE = E4;
				ToE5Thread.Born = WorldTime::getInstance()->getTime();
				ToE5Thread.leagal = true;
				ToE5Thread.Sustain = 4.0f;
				return;
			}
		}
		else
		{
			auto per = PersonInstance->ali[FloorNow]->next;
			bool go = false;
			if(per)go = true;
			if (go)
			{
				StateForE = E4;
				ToE5Thread.Born = WorldTime::getInstance()->getTime();
				ToE5Thread.leagal = true;
				ToE5Thread.Sustain = 4.0f;
				return;
			}
		}
		D1 = 0;
	}

	////////////////////////////////////////////D3 = 0;////////////////////////////////////////////////////////////////////
	StateForE = E2;
	ToE2Thread.Born = WorldTime::getInstance()->getTime();
	ToE2Thread.leagal = true;
	ToE2Thread.Sustain = 0.2f;
	return;
}

void Elavator::E6Func(int Caller)
{
	if (E2 == Caller)
	{
		if (down == StateForMove && D3)
		{
			auto per = PersonInstance->ali[FloorNow]->next;
			bool go = false;
			while (per)
			{
				if (1 == per->UDdirection) { go = true; break; }
				per = per->next;
			}
			if (go)
			{
				StateForE = E3;
				ToE3Thread.Born = WorldTime::getInstance()->getTime();
				ToE3Thread.leagal = true;
				ToE3Thread.Sustain = 4.0f;
				return;
			}
		}
		else if (up == StateForMove && D3)
		{
			auto per = PersonInstance->ali[FloorNow]->next;
			bool go = false;
			while (per)
			{
				if (0 == per->UDdirection) { go = true; break; }
				per = per->next;
			}
			if (go)
			{
				StateForE = E3;
				ToE3Thread.Born = WorldTime::getInstance()->getTime();
				ToE3Thread.leagal = true;
				ToE3Thread.Sustain = 2.0f;
				return;
			}
		}
		if (idle == StateForMove && D3)
		{
			auto per = PersonInstance->ali[FloorNow]->next;
			bool go = false;
			if(per)go = true;
			if (go)
			{
				StateForE = E3;
				ToE3Thread.Born = WorldTime::getInstance()->getTime();
				ToE3Thread.leagal = true;
				ToE3Thread.Sustain = 2.0f;
				return;
			}
		}
		
		if (ToE6Thread.leagal)
		{
			if (ToE6Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE6Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
			{
				D3 = 0;
				ToE6Thread.leagal = false;
			}
			return;
		}
	}
	else 
	{
		if (ToE6Thread.leagal)
		{
			if (ToE6Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE6Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
				ToE6Thread.leagal = false;
			return;
		}
	}

	CallCar[FloorNow] = false;
	if (up == StateForMove)CallUp[FloorNow] = false;
	else if (down == StateForMove)CallDown[FloorNow] = false;
	else CallUp[FloorNow] = CallDown[FloorNow] = false;

	Controler(E6);

	if (idle == StateForMove) 
	{
		ToE1Thread.Born = WorldTime::getInstance()->getTime();
		ToE1Thread.leagal = true;
		ToE1Thread.Sustain = 0.2f; 
		StateForE = E1;
		return;
	}
	if (D2)ToE9Thread.leagal = false;

	if (up == StateForMove)
	{
		/*ToE7Thread.Born = WorldTime::getInstance()->getTime(); 
		ToE7Thread.leagal = true;
		ToE7Thread.Sustain = 0.2f;
		StateForE = E7;*/
		ToE7Thread.Born = WorldTime::getInstance()->getTime();
		ToE7Thread.leagal = true;
		ToE7Thread.Sustain = 1.5f;
		StateForE = E7;
	}

	if (down == StateForMove)
	{
		/*ToE8Thread.Born = WorldTime::getInstance()->getTime();
		ToE8Thread.leagal = true;
		ToE8Thread.Sustain = 0.2f;
		StateForE = E8;*/
		ToE8Thread.Born = WorldTime::getInstance()->getTime();
		ToE8Thread.leagal = true;
		ToE8Thread.Sustain = 1.5f;
		StateForE = E8;
	}

}

void Elavator::E7Func()
{
	//ToE7Thread
	if (ToE7Thread.leagal)
	{
		if (ToE7Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE7Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
		{
			FloorNow++;
			ToE7Thread.leagal = false;
			StateReal = Up_Moving;
			MoveThread.Born = WorldTime::getInstance()->getTime();
			MoveThread.leagal = true;
			Body->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
			LeftDoor->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
			RightDoor->runAction(MoveTo::create(2.0f, Vec2(0 + RightDoor->getBoundingBox().size.width * 2,
				heigh[FloorNow] + RightDoor->getBoundingBox().size.height)));
			MoveThread.Sustain = 1.1f;
			return;
		}
		else return;
	}
	


	//if((4==FloorNow||CallDown[FloorNow])&&)
	
	int flag = false;
	for (int i = FloorNow + 1; i < 5; i++)
		if (CallUp[i] || CallDown[i] || CallCar[i])break;
		else if (4 == i)flag = true;

	bool reser = false;
	for (int i = FloorNow + 1; i < 5; i++)
		if (CallUp[i] || CallDown[i] || CallCar[i])break;
		else if (4 == i)reser = true;

	if (4 == FloorNow)flag = true;

	if (CallCar[FloorNow] == 1 || CallUp[FloorNow] == 1 ||((
		4 == FloorNow || CallDown[FloorNow]) && flag))//|| ((FloorNow == 1 || CallDown[FloorNow] == 1) && flag)
	{
		if (reser == FloorNow)StateForMove = down;
		StateForE = E3;
		ToE3Thread.leagal = true;
		ToE3Thread.Sustain = 0.4f;
		ToE3Thread.Born = WorldTime::getInstance()->getTime();
		return;
	}
	//ToE7Thread.leagal = false;
	//StateReal = Up_Moving;ToE7Thread.Born = WorldTime::getInstance()->getTime();
	FloorNow++;
	StateReal = Up_Moving;
	MoveThread.Born = WorldTime::getInstance()->getTime();
	MoveThread.leagal = true;
	Body->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
	LeftDoor->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
	RightDoor->runAction(MoveTo::create(2.0f, Vec2(0 + RightDoor->getBoundingBox().size.width * 2,
		heigh[FloorNow] + RightDoor->getBoundingBox().size.height)));
	MoveThread.Sustain = 1.1f;
	
	//&&CallUp[j] = CallDown[j] = CallCar[j] = 0对于所有j > Floor
}


void Elavator::E8Func()
{
	//ToE8Thread
	if (ToE8Thread.leagal)
		if (ToE8Thread.Sustain - (WorldTime::getInstance()->getTime() - ToE8Thread.Born) / CLOCKS_PER_SEC * 1.0 < 0)
		{
			FloorNow--;
			ToE8Thread.leagal = false;
			StateReal = Down_Moving;
			MoveThread.Born = WorldTime::getInstance()->getTime();
			MoveThread.leagal = true;
			Body->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
			LeftDoor->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
			RightDoor->runAction(MoveTo::create(2.0f, Vec2(0 + RightDoor->getBoundingBox().size.width * 2,
				heigh[FloorNow] + RightDoor->getBoundingBox().size.height)));
			MoveThread.Sustain = 1.1f;
			return;
		}
		else return;

	int flag = false;
	for (int i = FloorNow - 1; i >= 0; i--)
		if (CallUp[i] || CallDown[i] || CallCar[i])break;
		else if (0 == i)flag = true;

	bool reser = false;
	for (int i = FloorNow - 1; i >= 0; i--)
		if (CallUp[i] || CallDown[i] || CallCar[i])break;
		else if (0 == i)reser = true;

	if (0 == FloorNow)flag = true;
	if (CallCar[FloorNow] == 1 || CallDown[FloorNow] == 1 ||
		((0 == FloorNow || CallUp[FloorNow]) && flag))//|| ((FloorNow == 1 || CallDown[FloorNow] == 1) && flag)
	{
		if (reser)StateForMove = up;
		StateForE = E3;
		ToE3Thread.leagal = true;
		ToE3Thread.Sustain = 0.4f;
		ToE3Thread.Born = WorldTime::getInstance()->getTime();
		return;
	}
	//ToE7Thread.leagal = false;
	//StateReal = Up_Moving;ToE7Thread.Born = WorldTime::getInstance()->getTime();
	FloorNow--;
	StateReal = Down_Moving;
	MoveThread.Born = WorldTime::getInstance()->getTime();
	MoveThread.leagal = true;
	Body->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
	LeftDoor->runAction(MoveTo::create(2.0f, Vec2(0, heigh[FloorNow])));
	RightDoor->runAction(MoveTo::create(2.0f, Vec2(0 + RightDoor->getBoundingBox().size.width * 2,
		heigh[FloorNow] + RightDoor->getBoundingBox().size.height)));
	MoveThread.Sustain = 1.1f;
	
}

void Elavator::E9Func()
{
	D2 = 0;
	Controler(E9);
}

void Elavator::openDoor()
{
	LeftDoor->runAction(ScaleTo::create(2.0f, 0.0f, 0.28f));
	RightDoor->runAction(ScaleTo::create(2.0f, 0.0f, 0.28f));
	//ScaleTo::create(4.0f, 0.0f, 0.28f);
}

void Elavator::closeDoor()
{
	LeftDoor->runAction(ScaleTo::create(2.0f, 0.55f, 0.28f));
	RightDoor->runAction(ScaleTo::create(2.0f, 0.55f, 0.28f));
}
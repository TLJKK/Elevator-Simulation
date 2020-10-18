#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BgScene.h"
using namespace cocos2d;
 
class choose : public cocos2d::Layer
{
public:
	choose();
	~choose();
	virtual bool init();
	CREATE_FUNC(choose);
	ui::Scale9Sprite* box;
	ui::Button* cancle_Btn;
	ui::Button* allAuto_Btn;
	ui::Button* halfAuto_Btn;
	Bg* to;
	virtual void registerCallback(std::function<void()>allCallback, std::function<void()>
		halfCallback, std::function<void()>cancleCallback);
	virtual void onEnter();//show the fault there is less of ';' ,the possible season is the namespace;
protected:
	std::function<void()>allAuto;
	std::function<void()>cancle;
	std::function<void()>halfAuto;
private:
};

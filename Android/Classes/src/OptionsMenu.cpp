#include "OptionsMenu.h"

USING_NS_CC;

Scene* OptionsMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = OptionsMenu::create();

	scene->addChild(layer);

	return scene;
}

bool OptionsMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	muted = false;

	auto menuLabel =
		MenuItemImage::create("OptionsMenuScreen/Menu_Button.png",
		"OptionsMenuScreen/Menu_Button.png");

	auto muteButton =
		MenuItemImage::create("OptionsMenuScreen/mute.png",
		"OptionsMenuScreen/mute.png", 
		CC_CALLBACK_1(OptionsMenu::mutesound,this));
	
	auto mainMenuItem =
		MenuItemImage::create("OptionsMenuScreen/Menu_Button.png",
		"OptionsMenuScreen/Menu_Button.png",
		CC_CALLBACK_1(OptionsMenu::activateMainMenuScene, this));
	
	auto menu = Menu::create(menuLabel, muteButton, mainMenuItem,
		NULL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 6);
	this->addChild(menu);
	return true;
}


void OptionsMenu::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}
void  OptionsMenu::mutesound(cocos2d::Ref *pSender){

	Mute::muted = !Mute::muted;
}
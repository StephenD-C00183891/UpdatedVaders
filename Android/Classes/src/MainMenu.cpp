#include "MainMenu.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}


bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	
	//label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	//Vec2 lablepos = label->getAnchorPoint();
	//this->addChild(label, 1);
//	buttonRight->setPosition(Point(visibleSize.width / 1.05f, visibleSize.height / 13));
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto menuTitle =
		MenuItemImage::create("MainMenuScreen/Game_Title.png",
		"MainMenuScreen/Game_Title.png");
	//menuTitle->setPosition(Point(visibleSize.width/12,visibleSize.height/2));
	auto playItem =
		MenuItemImage::create("MainMenuScreen/Play_Button.png",
		"MainMenuScreen/Play_Button(Click).png",
		CC_CALLBACK_1(MainMenu::activateGameScene, this));

	auto optionsTitle =
		MenuItemImage::create("MainMenuScreen/Options_Menu.png",
		"MainMenuScreen/Options_Menu.png",
	CC_CALLBACK_1(MainMenu::activateOptionsScene, this));



	auto menu = Menu::create(menuTitle, playItem,optionsTitle, NULL);


	
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	//menu->alignItemsHorizontallyWithPadding(visibleSize.width / 2);
	this->addChild(menu);

	return true;
}

void MainMenu::activateGameScene(Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void MainMenu::activateOptionsScene(Ref * pSender){
	auto scene = OptionsMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}
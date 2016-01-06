#include "PauseMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = PauseMenu::create();

	scene->addChild(layer);

	return scene;
}

bool PauseMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto label = Label::createWithSystemFont("Hello World", "Arial", 96);

	//label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	//Vec2 lablepos = label->getAnchorPoint();
	//this->addChild(label, 1);
	auto resumeItem =
		MenuItemImage::create("PauseScreen/Resume_Button.png",
		"PauseScreen/Resume_Button(Click).png",
		CC_CALLBACK_1(PauseMenu::resume, this));
	auto retryItem =
		MenuItemImage::create("PauseScreen/Retry_Button.png",
		"PauseScreen/Retry_Button(Click).png",
		CC_CALLBACK_1(PauseMenu::retry, this));
	auto mainMenuItem =
		MenuItemImage::create("PauseScreen/Menu_Button.png",
		"PauseScreen/Menu_Button(Click).png",
		CC_CALLBACK_1(PauseMenu::activateMainMenuScene, this));
	auto menu = Menu::create(resumeItem, retryItem, mainMenuItem,
		NULL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu);
	return true;
}
void PauseMenu::resume(Ref *pSender)
{
	Director::getInstance()->popScene();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void PauseMenu::activateMainMenuScene(Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto scene = MainMenu::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseMenu::retry(Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto scene = GameOver::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}
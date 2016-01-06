#include "GameOver.h"

USING_NS_CC;

Scene* HighScore::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = HighScore::create();

	scene->addChild(layer);

	return scene;
}


bool HighScore::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < 6; i++)
	{
		m_ScoreBoard.push_back(0);
	}

	auto HighScoreLabel =
		MenuItemImage::create("HighScoreScreen/High_Scores.png", 
		"HighScoreScreen/High_Scores.png");

	auto mainMenuItem =
		MenuItemImage::create("GameOverScreen/Menu_Button.png",
		"GameOverScreen/Menu_Button(Click).png",
		CC_CALLBACK_1(HighScore::activateMainMenuScene, this));
	
	auto menu = Menu::create(HighScoreLabel, mainMenuItem,
		NULL);

	first = Label::createWithTTF("1st: " + std::to_string(m_ScoreBoard[0]), "fonts/Marker Felt.ttf", 20);
	first->setPosition(Point(visibleSize.width / 1.3, visibleSize.height*0.6 / 30));
	this->addChild(first);

	second = Label::createWithTTF("2nd: " + std::to_string(m_ScoreBoard[1]), "fonts/Marker Felt.ttf", 20);
	first->setPosition(Point(visibleSize.width / 1.3, visibleSize.height*0.6 / 30));
	this->addChild(first);

	third = Label::createWithTTF("3rd: " + std::to_string(m_ScoreBoard[2]), "fonts/Marker Felt.ttf", 20);
	first->setPosition(Point(visibleSize.width / 1.3, visibleSize.height*0.6 / 30));
	this->addChild(first);

	fourth = Label::createWithTTF("4th: " + std::to_string(m_ScoreBoard[3]), "fonts/Marker Felt.ttf", 20);
	first->setPosition(Point(visibleSize.width / 1.3, visibleSize.height*0.6 / 30));
	this->addChild(first);

	fifth = Label::createWithTTF("5th: " + std::to_string(m_ScoreBoard[4]), "fonts/Marker Felt.ttf", 20);
	first->setPosition(Point(visibleSize.width / 1.3, visibleSize.height*0.6 / 30));
	this->addChild(first);

	
	
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu);
	return true;
}

void HighScore::fillScoreBoard(int p1Score, int p2Score)
{
	for (int i = 4; i >= 0; i--) {
		if (p1Score > m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = m_ScoreBoard[i];
		}

		if (p1Score <= m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = p1Score;
			break;
		}
		if (p1Score > m_ScoreBoard[0]) {
			m_ScoreBoard[0] = p1Score;
			break;
		}
	}

	for (int i = 4; i >= 0; i--) {
		if (p2Score > m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = m_ScoreBoard[i];
		}
		if (p2Score <= m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = p2Score;
			break;
		}
		if (p2Score > m_ScoreBoard[0]) {
			m_ScoreBoard[0] = p2Score;
			break;
		}
	}

	first->setString(std::to_string(m_ScoreBoard[0]));
	second->setString(std::to_string(m_ScoreBoard[1]));
	third->setString(std::to_string(m_ScoreBoard[2]));
	fourth->setString(std::to_string(m_ScoreBoard[3]));
	fifth->setString(std::to_string(m_ScoreBoard[4]));
}


void HighScore::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	auto backgroundSprite = Sprite::create
		(ptr->m_backgroundTextureFile);
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);
}

void HighScore::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}
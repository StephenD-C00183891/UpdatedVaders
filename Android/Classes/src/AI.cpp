#include "AI.h"

USING_NS_CC;

AI::AI(GameStates & gameState, cocos2d::Layer &layer, int maxAI) :
m_indexOfNextAI(0), m_gameState(gameState)
{
	currentLayer = &layer;
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	//m_aiSprites.reserve(maxAI);
    createAnimatedSprites(m_gameState, maxAI);	
	
}

void AI::update(float dt, float speed)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto move = MoveBy::create(speed, Vec2(visibleSize.width, 0));
	if (m_indexOfNextAI < m_aiSprites.size())
	{
		currentLayer->addChild(m_aiSprites.at(m_indexOfNextAI), 1);
		m_aiSprites.at(m_indexOfNextAI)->runAction(RepeatForever::create(move));
		m_indexOfNextAI++;
	}


	/*for (m_indexOfNextAI; m_indexOfNextAI < m_aiSprites.size() / 2; m_indexOfNextAI++)
	{

	   auto	move = MoveBy::create(speed, Vec2(visibleSize.width, 0));
		if (m_indexOfNextAI < m_aiSprites.size() / 2)
		{
			currentLayer->addChild(m_aiSprites.at(m_indexOfNextAI), 1);
			m_aiSprites.at(m_indexOfNextAI)->runAction(RepeatForever::create(move));
			//m_indexOfNextAI++;
		}
	}
	for (m_indexOfNextAI; m_indexOfNextAI < m_aiSprites.size(); m_indexOfNextAI++)
	 {
	   auto	move2 = MoveBy::create(speed, Vec2(-visibleSize.width, 0));
		if (int i = m_aiSprites.size() / 2 < m_aiSprites.size())
		{
			currentLayer->addChild(m_aiSprites.at(m_indexOfNextAI), 1);
			m_aiSprites.at(m_indexOfNextAI)->runAction(RepeatForever::create(move2));
			//i++;
		}
	}*/



}

cocos2d::Vector<cocos2d::Sprite *> & AI::getAISpriteList()
{
	return m_aiSprites;
}

void AI::createAnimatedSprites(GameStates & m_gameState , int maxAI)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	// load the Sprite Sheet
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_aiPlistFile);
	int frames = ptr->m_aiRows * ptr->m_aiColumns;

	for (int index = 0; index <=  maxAI; index++)
	{
			
		for (int i = 1; i < frames -1; i++)
		{
			m_animFrames.pushBack(spritecache->getSpriteFrameByName("walking" + std::to_string(i) + ".png"));
		}
		// Create the animation out of the frames.
		Animation* animation = Animation::createWithSpriteFrames(m_animFrames, 0.05f);
		Animate* animate = Animate::create(animation);
		// Create a sprite using any one of the SpriteFrames
		// This is so we get a sprite of the correct dimensions.
		auto sprite = Sprite::createWithSpriteFrame(m_animFrames.at(0));
	/*	for (m_indexOfNextAI; m_indexOfNextAI < m_aiSprites.size(); m_indexOfNextAI++)
		{
			if (m_indexOfNextAI < m_aiSprites.size() / 2)
			{
				sprite->setPosition(Vec2(rand() % (-100 - (-800)) + (-800), rand() % (320 - 120) + 120));
			}
			else if (m_indexOfNextAI >= m_aiSprites.size() / 2)
			{
				sprite->setPosition(Vec2(rand() % (1500 - (900)) + (900), rand() % (320 - 120) + 120));
			}
		}*/
		sprite->setPosition(Vec2(rand() % (-100 - (-800)) + (-800), rand() % (320 - 120) + 120));
		sprite->setScale(ptr->m_aiScale);
		// Run and repeat the animation.
		sprite->runAction(RepeatForever::create(animate));
		m_aiSprites.pushBack(sprite);

	}
}



#include "cocos2d.h"
#include "GameData.h"




class Shield : public cocos2d::Sprite
{
private:
	
	cocos2d::Vec2 m_position;
	
	
public:
	Shield();
	cocos2d::Sprite* mySprite;
	static Shield * create(cocos2d::Vec2 position);
	void initOptions(cocos2d::Vec2 position);
	int health;
	void setHealth(int temp);
	int getHealth();
	void Update();

};
#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <memory>
////////////////////////////////////////////////////////////
/// \brief A class that stores gameplay data
/// 
////////////////////////////////////////////////////////////


class GameData {
private:
	//Constructor
	GameData();

	static std::weak_ptr<GameData> m_instance;

	friend std::weak_ptr < GameData >;
	friend std::shared_ptr < GameData >;
public:
	//Get instance of singleton
	static std::shared_ptr<GameData> sharedGameData();

	std::string m_backgroundTextureFile;
	std::string m_textureAtlasImageFile;
	std::string m_textureAtlasPlistFile;
	std::string m_laserPlistFile;
	std::string m_ShieldPlistFile;
	std::string m_shieldImage;
	// Tower base and tower related fields.
	std::string m_player_base_file;
	std::string m_playerplistfile;
	std::string m_towerBaseFile2;
	std::string m_towerGunFile;
	int m_playerWidth;
	int m_playerHeight;
	int m_towerRotationSpeed;
	float m_towerRotationOriginX;
	float m_towerRotationOriginY;
	int m_numberOfPlayers;

	

	// Projectile related fields.
	std::string m_projectileFile;
	float m_projectileCentreX;
	float m_projectileCentreY;
	float m_velocity;

	// AI related fields.
	std::string m_aiImageFile;
	std::string m_aiPlistFile;
	int m_maxNumAI;
	int m_spawnInterval;
	float m_aiScale;
	// AI sprite sheet.
	int m_aiRows;
	int m_aiColumns;
	int m_aiWidth;
	int m_aiHeight;
	// AI Waypoints.

};

#endif
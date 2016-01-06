#include "LevelLoader.h"

////////////////////////////////////////////////////////////
LevelLoader::LevelLoader(std::string const & filename) 
{
	loadJSONData(filename);
	m_document.Parse<0>(m_JSONData.c_str());	
	loadGameData();
}

////////////////////////////////////////////////////////////
void LevelLoader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	auto fileUtils = cocos2d::FileUtils::getInstance();
	// Loads all the data in the file into a std::string.
	m_JSONData = fileUtils->getStringFromFile(filename);
}


////////////////////////////////////////////////////////////
void LevelLoader::loadGameData()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	Value::ConstMemberIterator it1 = m_document["global_settings"].MemberBegin();
	// Get value of "background_texture" 
	ptr->m_backgroundTextureFile = it1->value.GetString();
	// Get value of "texture_atlas_image_file" 
	it1++;
	ptr->m_textureAtlasImageFile = it1->value.GetString();
	// Get value of "texture_atlas_plist_file"
	it1++;
	ptr->m_textureAtlasPlistFile = it1->value.GetString();
	it1++;
	Value const & player = it1->value; 
	assert(player.IsObject());
	// Get the tower properties.
	ptr->m_playerplistfile = player["player_plist_file"].GetString();
	ptr->m_player_base_file = player["player_base_file"].GetString();
	//ptr->m_towerGunFile = tower["tower_gun_file"].GetString();
	ptr->m_playerWidth = player["player_width"].GetInt();
	ptr->m_playerHeight = player["player_height"].GetInt();
	ptr->m_numberOfPlayers = player["number_of_players"].GetInt();

	// The "tower_bases" element is an array.
	
	// Iterate through the array.
	
	// Move to the "projectile" element, which is another object.
	it1++;
	Value const & projectile = it1->value;
	ptr->m_laserPlistFile = projectile["projectileplist_file"].GetString();
	ptr->m_projectileFile = projectile["projectile_file"].GetString();
	// The "projectile_centre" element is an object.	
	Value const & projectileCentre = projectile["projectile_centre"];
	ptr->m_projectileCentreX = projectileCentre["x"].GetInt();
	ptr->m_projectileCentreY = projectileCentre["y"].GetInt();
	// Get the remaining projectile attributes.
	ptr->m_velocity = projectile["velocity"].GetDouble();
	
	// Move to the "ai" element
	it1++;
	Value const & ai = it1->value;
	ptr->m_aiImageFile = ai["ai_image_file"].GetString();
	ptr->m_aiPlistFile = ai["ai_plist_file"].GetString();
	ptr->m_maxNumAI = ai["max_num_ai"].GetInt();
	ptr->m_spawnInterval = ai["ai_spawn_interval"].GetInt();
	ptr->m_aiScale = ai["ai_scale"].GetDouble();
	// The "ai_walking_spritesheet" element is an object.
	Value const & aiWalkingSpriteSheet = ai["ai_walking_spritesheet"];
	ptr->m_aiRows = aiWalkingSpriteSheet["rows"].GetInt();
	ptr->m_aiColumns = aiWalkingSpriteSheet["columns"].GetInt();
	ptr->m_aiWidth = aiWalkingSpriteSheet["width"].GetInt();
	ptr->m_aiHeight = aiWalkingSpriteSheet["height"].GetInt();
	it1++;
	Value const & shield = it1->value;
	ptr->m_ShieldPlistFile = shield["shield_plist_file"].GetString();
	ptr->m_shieldImage = shield["shield_image_file"].GetString();

}

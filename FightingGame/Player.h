#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#define PLAYER_LEVEL_COUNTER 1.65f
#define PLAYER_LEVEL_UP_HP_COUNTER 6.0f
#define PLAYER_LEVEL_UP_MP_COUNTER 7.0f
#define PLAYER_LEVEL_UP_DEF_COUNTER 6.0f

#define DEFAULT_PLAYER_HP 90.0f
#define DEFAULT_PLAYER_MP 85.0f
#define DEFAULT_PLAYER_DEF 8.0f

#define HEAL_HP_POWER 35.0f
#define HEAL_MP_POWER 45.0f

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

#include "CoreFunctions.h"
#include "Attack.h"

using namespace std;
using json = nlohmann::json;

class Player
{
public:
	bool isAlive;

	//--> getters start
	int getLevel();
	float getMaxHP();
	float getCurrHP();
	float getMaxMP();
	float getCurrMP();
	float getMaxDEF();
	float getCurrDEF();
	int getHealthPotions();
	int getManaPotions();
	Attack* getAttack(int i = 0);
	int getAttackListRange();
	//--> getters end

	//--> setters start
	void buildPlayer(json& data);
	void levelUp();
	void recover();
	void addAttack(string name, float damageHP, float damageMP, float damageDEF, float manaCost);
	void addPotions(int healthPotionsAmount = 0, int manaPotionsAmount = 0);
	void takeDamage(float damage = 0);
	void takeDamage(float damageHP = 0, float damageMP = 0, float damageDEF = 0);
	void useMana(float amount = 0);
	void useHealthPotion();
	void useManaPotion();
	//--> setters end

	Player();
	Player(int level, float maxHP, float maxDEF, float maxMP);
	~Player();

private:
	int level;
	float maxHP;
	float currHP;
	float maxMP;
	float currMP;
	float maxDEF;
	float currDEF;
	int healthPotions;
	int manaPotions;

	vector<Attack>* attackList = new vector<Attack> {
		Attack("Kick", 12.0f, 0.0f, 0.0f, 0.0f),
		Attack("Sword Attack", 20.0f, 0.0f, 0.0f, 10.0f),
	};
};

#endif // !__PLAYER_H_INCLUDED__
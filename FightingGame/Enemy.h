#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#define ENEMY_LEVEL_COUNTER 1.46f
#define ENEMY_LEVEL_UP_HP_COUNTER 6.4f
#define ENEMY_LEVEL_UP_MP_COUNTER 7.2f
#define ENEMY_LEVEL_UP_DEF_COUNTER 7.0f

#define DEFAULT_ENEMY_HP 80.0f
#define DEFAULT_ENEMY_MP 80.0f
#define DEFAULT_ENEMY_DEF 4.0f

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

class Enemy
{
private:
	int level;
	float maxHP;
	float currHP;
	float maxDEF;
	float currDEF;
	float maxMP;
	float currMP;
	int healthPotions;
	int manaPotions;

	vector<Attack>* attackList = new vector<Attack>{
		Attack("Kick", 18.0f, 0.0f, 0.0f, 0.0f),
		Attack("Claws Attack", 26.0f, 0.0f, 0.0f, 18.0f),
	};

public:
	bool isAlive;
	Attack currAttack = attackList->at(0);
	Attack prevAttack = currAttack;

	//--> getters start
	int getLevel();
	void levelUp();
	float getMaxHP();
	float getCurrHP();
	float getMaxMP();
	float getCurrMP();
	float getMaxDEF();
	float getCurrDEF();
	int getHealthPotions();
	int getManaPotions();
	Attack* getAttack(int i);
	Attack* getRandAttack();
	int getAttackListRange();
	//--> getters end

	//--> setters start
	void buildEnemy(json& data);
	void recover();
	void addAttack(string name, float damageHP = 0.0f, float damageMP = 0.0f, float damageDEF = 0.0f,float manaCost = 0.0f);
	void useMana(float amount = 0);
	void takeDamage(float damage = 0);
	void takeDamage(float damageHP = 0, float damageMP = 0, float damageDEF = 0);
	void addPotions(int healthPotionsAmount = 0, int manaPotionsAmount = 0);
	void useHealthPotion();
	void useManaPotion();
	//--> setters end

	Enemy();
	Enemy(int level, float maxHP, float maxMP, float maxDEF);
	~Enemy();
};

#endif // !__ENEMY_H_INCLUDED__
#include "Enemy.h"

int Enemy::getLevel()
{
	return Enemy::level;
}
float Enemy::getMaxHP()
{
	return Enemy::maxHP;
}
float Enemy::getCurrHP()
{
	return Enemy::currHP;
}
float Enemy::getMaxMP()
{
	return Enemy::maxMP;
}
float Enemy::getCurrMP()
{
	return Enemy::currMP;
}
float Enemy::getMaxDEF()
{
	return Enemy::maxDEF;
}
float Enemy::getCurrDEF()
{
	return Enemy::currDEF;
}
int Enemy::getHealthPotions()
{
	return Enemy::healthPotions;
}
int Enemy::getManaPotions()
{
	return Enemy::manaPotions;
}
Attack* Enemy::getAttack(int i)
{
	return new Attack(Enemy::attackList->at(i));
}
Attack* Enemy::getRandAttack()
{
	return new Attack(attackList->at(rand() % Enemy::attackList->size()));
}
int Enemy::getAttackListRange()
{
	return Enemy::attackList->size();
}

void Enemy::buildEnemy(json& data)
{
	Enemy::level = data["Enemy"]["level"];
	Enemy::maxHP = data["Enemy"]["maxHP"];
	Enemy::maxMP = data["Enemy"]["maxMP"];
	Enemy::maxDEF = data["Enemy"]["maxDEF"];
	Enemy::healthPotions = data["Enemy"]["healthPotions"];
	Enemy::manaPotions = data["Enemy"]["manaPotions"];
	
	Attack findAttack = Enemy::attackList->at(0);

	for (int i = 0; i < data["Enemy"]["Attacks"].size(); i++)
	{
		try
		{
			findAttack = Enemy::attackList->at(i);
		}
		catch (const std::exception&)
		{
			Enemy::attackList->push_back(Attack(
				data["Enemy"]["Attacks"][i]["name"],
				data["Enemy"]["Attacks"][i]["damageHP"],
				data["Enemy"]["Attacks"][i]["damageMP"],
				data["Enemy"]["Attacks"][i]["damageDEF"],
				data["Enemy"]["Attacks"][i]["manaCost"]));
		}
	}
	
	Enemy::recover();
}
void Enemy::levelUp()
{
	Enemy::level++;

	if (Enemy::level == 2)
	{
		Enemy::addAttack("Sword Attack", 39.0f, 0.0f, 0.0f, 30.0f);
	}
	else if (Enemy::level == 4)
	{
		Enemy::addAttack("Fire Breath", 40.0f, 8.0f, 15.0f, 38.0f);
		Enemy::addPotions(0, 1);
	}
	else if (Enemy::level == 5)
	{
		Enemy::addAttack("Horror Scream", 0.0f, 0.0f, 40.0f, 22.0f);
	}
	else if (Enemy::level == 6)
	{
		Enemy::addAttack("Toxic Breath", 25.0f, 20.0f, 20.0f, 48.0f);
	}
	else if (Enemy::level == 8)
	{
		Enemy::addAttack("Shadow Arrows", 0.0f, 60.0f, 0.0f, 42.0f);
		Enemy::addPotions(0, 1);
	}
	else if (Enemy::level == 9)
	{
		Enemy::addAttack("Meteor Shower", 70.0f, 0.0f, 0.0f, 56.0f);
	}

	Enemy::maxHP += (Enemy::level + ENEMY_LEVEL_COUNTER * ENEMY_LEVEL_UP_HP_COUNTER);
	Enemy::maxMP += (Enemy::level + ENEMY_LEVEL_COUNTER * ENEMY_LEVEL_UP_MP_COUNTER);
	Enemy::maxDEF += (Enemy::level + ENEMY_LEVEL_UP_DEF_COUNTER);

	Enemy::currHP = Enemy::maxHP;
	Enemy::currMP = Enemy::maxMP;
	Enemy::currDEF = Enemy::maxDEF;
}
void Enemy::recover()
{
	Enemy::currHP = Enemy::maxHP;
	Enemy::currMP = Enemy::maxMP;
	Enemy::currDEF = Enemy::maxDEF;
}
void Enemy::addAttack(string name, float damageHP, float damageMP, float damageDEF, float manaCost)
{
	Enemy::attackList->push_back(Attack(name, damageHP, damageMP, damageDEF, manaCost));
}
void Enemy::useMana(float amount)
{
	Enemy::currMP -= amount;
}
void Enemy::takeDamage(float damage)
{
	float trueDamage = damage - ((damage / 10.0f) + (Enemy::currDEF / 10.0f));

	Enemy::currHP -= trueDamage;

	if (Enemy::currHP <= 0.9f)
	{
		Enemy::isAlive = false;
	}
}
void Enemy::takeDamage(float damageHP, float damageMP, float damageDEF)
{
	float trueDamage = damageHP - ((damageHP / 10.0f) + (Enemy::currDEF / 10.0f));

	if (trueDamage >= 0.0f)
	{
		Enemy::currHP -= trueDamage;
	}

	if (Enemy::currHP <= 0.9f)
	{
		Enemy::isAlive = false;
	}

	if (Enemy::currMP > damageMP)
	{
		Enemy::currMP -= damageMP;
	}
	else
	{
		Enemy::currMP = 0;
	}

	if (Enemy::currDEF > damageDEF)
	{
		Enemy::currDEF -= damageDEF;
	}
	else
	{
		Enemy::currDEF = 0;
	}
}
void Enemy::addPotions(int healthPotionsAmount, int manaPotionsAmount)
{
	Enemy::healthPotions += healthPotionsAmount;
	Enemy::manaPotions += manaPotionsAmount;
}

void Enemy::useHealthPotion()
{
	Enemy::healthPotions -= 1;

	if (Enemy::level < 2)
	{
		if (Enemy::maxHP - Enemy::currHP >= HEAL_HP_POWER)
		{
			Enemy::currHP += HEAL_HP_POWER;
		}
	}
	else
	{
		if (Enemy::maxHP - Enemy::currHP >= HEAL_HP_POWER + (Enemy::level * ENEMY_LEVEL_COUNTER))
		{
			Enemy::currHP += HEAL_HP_POWER + (Enemy::level * ENEMY_LEVEL_COUNTER);
		}
	}
}
void Enemy::useManaPotion()
{
	Enemy::manaPotions -= 1;

	if (Enemy::level < 2)
	{
		if (Enemy::maxMP - Enemy::currMP >= HEAL_MP_POWER)
		{
			Enemy::currMP += HEAL_MP_POWER;
		}
	}
	else
	{
		if (Enemy::maxMP - Enemy::currMP >= HEAL_HP_POWER + (Enemy::level * ENEMY_LEVEL_COUNTER))
		{
			Enemy::currMP += HEAL_MP_POWER + (Enemy::level * ENEMY_LEVEL_COUNTER);
		}
	}
}

Enemy::Enemy()
{
	Enemy::isAlive = true;
	Enemy::level = 1;

	Enemy::maxHP = DEFAULT_ENEMY_HP;
	Enemy::maxMP = DEFAULT_ENEMY_MP;
	Enemy::maxDEF = DEFAULT_ENEMY_DEF;

	Enemy::currHP = Enemy::maxHP;
	Enemy::currMP = Enemy::maxMP;
	Enemy::currDEF = Enemy::maxDEF;

	Enemy::healthPotions = 0;
	Enemy::manaPotions = 1;
}
Enemy::Enemy(int level, float maxHP, float maxDEF, float maxMP)
{
	Enemy::isAlive = true;
	Enemy::level = level;

	if (Enemy::level > 1)
	{
		Enemy::maxHP = maxHP + (Enemy::level * ENEMY_LEVEL_COUNTER);
		Enemy::maxMP = maxMP + (Enemy::level * ENEMY_LEVEL_COUNTER);
		Enemy::maxDEF = maxDEF + (Enemy::level * ENEMY_LEVEL_COUNTER);
	}
	else
	{
		Enemy::maxHP = maxHP;
		Enemy::maxMP = maxMP;
		Enemy::maxDEF = maxDEF;
	}

	Enemy::currHP = Enemy::maxHP;
	Enemy::currMP = Enemy::maxMP;
	Enemy::currDEF = Enemy::maxDEF;

	Enemy::healthPotions = 0;
	Enemy::manaPotions = 1;
}
Enemy::~Enemy()
{
	delete Enemy::attackList;
}
#include "Player.h"

//--> getters start
int Player::getLevel()
{
	return Player::level;
}
float Player::getMaxHP()
{
	return Player::maxHP;
}
float Player::getCurrHP()
{
	return Player::currHP;
}
float Player::getMaxMP()
{
	return Player::maxMP;
}
float Player::getCurrMP()
{
	return Player::currMP;
}
float Player::getMaxDEF()
{
	return Player::maxDEF;
}
float Player::getCurrDEF()
{
	return Player::currDEF;
}
int Player::getHealthPotions()
{
	return Player::healthPotions;
}
int Player::getManaPotions()
{
	return Player::manaPotions;
}
Attack* Player::getAttack(int i)
{
	return new Attack(Player::attackList->at(i));
}
int Player::getAttackListRange()
{
	return Player::attackList->size();
}
//--> getters end

//--> setters start
void Player::buildPlayer(json& data)
{
	Player::level = data["Player"]["level"];
	Player::maxHP = data["Player"]["maxHP"];
	Player::maxMP = data["Player"]["maxMP"];
	Player::maxDEF = data["Player"]["maxDEF"];
	Player::healthPotions = data["Player"]["healthPotions"];
	Player::manaPotions = data["Player"]["manaPotions"];

	Attack findAttack = Player::attackList->at(0);

	for (int i = 0; i < data["Player"]["Attacks"].size(); i++)
	{
		try
		{
			findAttack = Player::attackList->at(i);
		}
		catch (const std::exception&)
		{
			Player::attackList->push_back(Attack(
				data["Player"]["Attacks"][i]["name"],
				data["Player"]["Attacks"][i]["damageHP"],
				data["Player"]["Attacks"][i]["damageMP"],
				data["Player"]["Attacks"][i]["damageDEF"],
				data["Player"]["Attacks"][i]["manaCost"]));
		}
	}

	Player::recover();
}
void Player::levelUp()
{
	Player::level++;

	if (Player::level == 2)
	{
		Player::attackList->push_back(Attack("Fire Ball", 42.0f, 14.0f, 0.0f, 45.0f));
		Player::addPotions(0, 1);
	}
	else if (Player::level == 4)
	{
		Player::attackList->push_back(Attack("Thunderbolt", 62.0f, 0.0f, 8.0f, 60.0f));
		Player::addPotions(1, 1);
	}
	else if (Player::level == 6)
	{
		Player::attackList->push_back(Attack("Ice Lance", 28.0f, 6.0f, 12.0f, 30.0f));
		Player::attackList->push_back(Attack("Stone Fist", 20.0f, 0.0f, 32.0f, 30.0f));
		Player::addPotions(1, 1);
	}
	else if (Player::level == 8)
	{
		Player::attackList->push_back(Attack("Shadow Blade", 42.0f, 28.0f, 10.0f, 54.0f));
		Player::addPotions(2, 2);
	}

	Player::maxHP += (Player::level + PLAYER_LEVEL_COUNTER * PLAYER_LEVEL_UP_HP_COUNTER);
	Player::maxMP += (Player::level + PLAYER_LEVEL_COUNTER * PLAYER_LEVEL_UP_MP_COUNTER);
	Player::maxDEF += (Player::level + PLAYER_LEVEL_COUNTER * PLAYER_LEVEL_UP_DEF_COUNTER);

	Player::currHP = Player::maxHP;
	Player::currMP = Player::maxMP;
	Player::currDEF = Player::maxDEF;
}
void Player::recover()
{
	Player::currHP = Player::maxHP;
	Player::currMP = Player::maxMP;
	Player::currDEF = Player::maxDEF;
}
void Player::addAttack(string name, float damageHP, float damageMP, float damageDEF, float manaCost)
{
	Player::attackList->push_back(Attack(name, damageHP, damageMP, damageDEF, manaCost));
}
void Player::addPotions(int healthPotionsAmount, int manaPotionsAmount)
{
	Player::healthPotions += healthPotionsAmount;
	Player::manaPotions += manaPotionsAmount;
}
void Player::useMana(float amount)
{
	Player::currMP -= amount;
}
void Player::useHealthPotion()
{
	Player::healthPotions -= 1;

	if (Player::level < 2)
	{
		if (Player::maxHP - Player::currHP >= HEAL_HP_POWER)
		{
			Player::currHP += HEAL_HP_POWER;
			system("cls");
		}
		else
		{
			cf::showError("you do not need to use this potion");
			cf::getEnter();
		}
	}
	else
	{
		if (Player::maxHP - Player::currHP >= HEAL_HP_POWER + (Player::level * PLAYER_LEVEL_COUNTER))
		{
			Player::currHP += HEAL_HP_POWER + (Player::level * PLAYER_LEVEL_COUNTER);
			system("cls");
		}
		else
		{
			cf::showError("you do not need to use this potion");
			cf::getEnter();
		}
	}
}
void Player::useManaPotion()
{
	Player::manaPotions -= 1;

	if (Player::level < 2)
	{
		if (Player::maxMP - Player::currMP >= HEAL_MP_POWER)
		{
			Player::currMP += HEAL_MP_POWER;
			system("cls");
		}
		else
		{
			cf::showError("you do not need to use this potion");
			cf::getEnter();
		}
	}
	else
	{
		if (Player::maxMP - Player::currMP >= HEAL_MP_POWER + (Player::level * PLAYER_LEVEL_COUNTER))
		{
			Player::currMP += HEAL_MP_POWER + (Player::level * PLAYER_LEVEL_COUNTER);
			system("cls");
		}
		else
		{
			cf::showError("you do not need to use this potion");
			cf::getEnter();
		}
	}
}
void Player::takeDamage(float damage)
{
	float trueDamage = damage - ((damage / 10.0f) + (Player::currDEF / 10.0f));

	if (trueDamage >= 0.0f)
	{
		Player::currHP -= trueDamage;
	}

	if (Player::currHP <= 0.0f)
	{
		Player::isAlive = false;
	}
}
void Player::takeDamage(float damageHP, float damageMP, float damageDEF)
{
	float trueDamageHP = damageHP - ((damageHP / 10.0f) + (Player::currDEF / 10.0f));

	if (trueDamageHP >= 0.0f)
	{
		Player::currHP -= trueDamageHP;
	}

	if (Player::currHP <= 0.0f)
	{
		Player::isAlive = false;
	}

	if (Player::currMP > damageMP)
	{
		Player::currMP -= damageMP;
	}
	else
	{
		Player::currMP = 0;
	}

	if (Player::currDEF > damageDEF)
	{
		Player::currDEF -= damageDEF;
	}
	else
	{
		Player::currDEF = 0;
	}
	
}
//--> setters end

Player::Player()
{
	Player::isAlive = true;
	Player::level = 1;

	Player::maxHP = DEFAULT_PLAYER_HP;
	Player::maxMP = DEFAULT_PLAYER_MP;
	Player::maxDEF = DEFAULT_PLAYER_DEF;

	Player::currHP = Player::maxHP;
	Player::currMP = Player::maxMP;
	Player::currDEF = Player::maxDEF;

	Player::healthPotions = 0;
	Player::manaPotions = 0;
}
Player::Player(int level, float maxHP, float maxMP, float maxDEF)
{
	Player::isAlive = true;
	Player::level = level;

	if (Player::level > 1)
	{
		Player::maxHP = maxHP + (Player::level * PLAYER_LEVEL_COUNTER);
		Player::maxMP = maxMP + (Player::level * PLAYER_LEVEL_COUNTER);
		Player::maxDEF = maxDEF + (Player::level * PLAYER_LEVEL_COUNTER);
	}
	else
	{
		Player::maxHP = maxHP;
		Player::maxMP = maxMP;
		Player::maxDEF = maxDEF;
	}

	Player::currHP = Player::maxHP;
	Player::currMP = Player::maxMP;
	Player::currDEF = Player::maxDEF;

	Player::healthPotions = 0;
	Player::manaPotions = 0;
}
Player::~Player()
{
	delete Player::attackList;
}
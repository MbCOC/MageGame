#include "Attack.h"

Attack::Attack(string name, float damageHP, float damageMP, float damageDEF, float manaCost)
{
	Attack::name = name;
	Attack::damageHP = damageHP;
	Attack::damageMP = damageMP;
	Attack::damageDEF = damageDEF;
	Attack::manaCost = manaCost;
}
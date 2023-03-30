#ifndef __ATTACK_H_INCLUDED__
#define __ATTACK_H_INCLUDED__

#include <iostream>

using namespace std;

class Attack
{
public:
	string name;
	float damageHP;
	float damageMP;
	float damageDEF;
	float manaCost;

	Attack(string name, float damageHP, float damageMP, float damageDEF, float manaCost);
};

#endif // !__ATTACK_H_INCLUDED__
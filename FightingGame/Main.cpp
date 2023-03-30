#include "Main.h"

bool isOpen = true;
Player* player = new Player();
Enemy* enemy = new Enemy();
json saveData;

void initializeSaveData()
{
	// rewrite player's data
	saveData["Player"]["level"] = player->getLevel();
	saveData["Player"]["maxHP"] = player->getMaxHP();
	saveData["Player"]["maxMP"] = player->getMaxMP();
	saveData["Player"]["maxDEF"] = player->getMaxDEF();
	saveData["Player"]["healthPotions"] = player->getHealthPotions();
	saveData["Player"]["manaPotions"] = player->getManaPotions();

	for (int i = 0; i < player->getAttackListRange(); i++)
	{
		saveData["Player"]["Attacks"][i]["name"] = player->getAttack(i)->name;
		saveData["Player"]["Attacks"][i]["damageHP"] = player->getAttack(i)->damageHP;
		saveData["Player"]["Attacks"][i]["damageMP"] = player->getAttack(i)->damageMP;
		saveData["Player"]["Attacks"][i]["damageDEF"] = player->getAttack(i)->damageDEF;
		saveData["Player"]["Attacks"][i]["manaCost"] = player->getAttack(i)->manaCost;
	}

	// rewrite enemy's data
	saveData["Enemy"]["level"] = enemy->getLevel();
	saveData["Enemy"]["maxHP"] = enemy->getMaxHP();
	saveData["Enemy"]["maxMP"] = enemy->getMaxMP();
	saveData["Enemy"]["maxDEF"] = enemy->getMaxDEF();
	saveData["Enemy"]["healthPotions"] = enemy->getHealthPotions();
	saveData["Enemy"]["manaPotions"] = enemy->getManaPotions();

	for (int i = 0; i < player->getAttackListRange(); i++)
	{
		saveData["Enemy"]["Attacks"][i]["name"] = enemy->getAttack(i)->name;
		saveData["Enemy"]["Attacks"][i]["damageHP"] = enemy->getAttack(i)->damageHP;
		saveData["Enemy"]["Attacks"][i]["damageMP"] = enemy->getAttack(i)->damageMP;
		saveData["Enemy"]["Attacks"][i]["damageDEF"] = enemy->getAttack(i)->damageDEF;
		saveData["Enemy"]["Attacks"][i]["manaCost"] = enemy->getAttack(i)->manaCost;
	}

	// save all data
	std::ofstream("data.json") << std::setw(4) << saveData << std::endl;
}
void checkSaveData()
{
	try
	{
		ifstream("data.json") >> saveData;
		player->buildPlayer(saveData);
		enemy->buildEnemy(saveData);
	}
	catch (const std::exception& e)
	{
		initializeSaveData();
	}
}

void drawUI()
{
	cf::showMassage("FIGHTING GAME\n", TEXT_D_YELLOW);
	cf::showMassage("Controls:\t1 - Attack | 2 - Use potion | 0 - Quit\n", TEXT_D_GREEN);

	if (!enemy->isAlive)
	{
		cf::showMassage("\n#----------------------------------------------------#\n", TEXT_L_GRAY);
		cf::showMassage("\n\t\t\tYOU WIN\n", TEXT_L_GREEN);
		cf::showMassage("\n#----------------------------------------------------#\n\n", TEXT_L_GRAY);
	}
	else if (!player->isAlive)
	{
		cf::showMassage("\n#----------------------------------------------------#\n", TEXT_L_GRAY);
		cf::showMassage("\n\t\t\tYOU LOSE\n", TEXT_D_RED);
		cf::showMassage("\n#----------------------------------------------------#\n\n", TEXT_L_GRAY);
	}
	else
	{
		cf::showMassage("\n#----------------------------------------------------#\n", TEXT_L_GRAY);
		cf::showMassage("\t\t\tENEMY\n", TEXT_D_RED);

		cf::setTextColor(TEXT_YELLOW);
		cout << "\tLevel: " << enemy->getLevel();
		cf::setTextColor(TEXT_L_RED);
		cout << "\n\tHP: " << enemy->getCurrHP() << '/' << enemy->getMaxHP();
		cf::setTextColor(TEXT_L_BLUE);
		cout << "\tMP: " << enemy->getCurrMP() << '/' << enemy->getMaxMP();
		cf::setTextColor(TEXT_L_GRAY);
		cout << "\tDEF: " << enemy->getCurrDEF();
		cf::setTextColor(TEXT_L_CYAN);
		cout << "\n\tHealth potions: " << enemy->getHealthPotions();
		cout << "\tMana Potions: " << enemy->getManaPotions();

		cf::showMassage("\n\n\n\n\n\t\t\tPLAYER\n", TEXT_D_GREEN);
		cf::setTextColor(TEXT_YELLOW);
		cout << "\tLevel: " << player->getLevel();
		cf::setTextColor(TEXT_L_RED);
		cout << "\n\tHP: " << player->getCurrHP() << '/' << player->getMaxHP();
		cf::setTextColor(TEXT_L_BLUE);
		cout << "\tMP: " << player->getCurrMP() << '/' << player->getMaxMP();
		cf::setTextColor(TEXT_L_GRAY);
		cout << "\tDEF: " << player->getCurrDEF();
		cf::showMassage("\n#----------------------------------------------------#\n\n", TEXT_L_GRAY);
	}
}
void enemyAttack()
{
	if (enemy->getLevel() < 2)
	{
		player->takeDamage(enemy->currAttack.damageHP, enemy->currAttack.damageMP, enemy->currAttack.damageDEF);
	}
	else
	{
		player->takeDamage(enemy->currAttack.damageHP + (enemy->getLevel() * ENEMY_LEVEL_COUNTER),
			enemy->currAttack.damageMP, enemy->currAttack.damageDEF);
	}

	enemy->useMana(enemy->currAttack.manaCost);

	std::system("cls");
	drawUI();
	cf::showMassage(enemy->currAttack.name + '!', TEXT_D_RED);
}

void showAttacks()
{
	for (int i = 0; i < player->getAttackListRange(); i++)
	{
		cf::setTextColor(TEXT_L_GRAY);
		cout << i + 1 << " - ";
		cf::setTextColor(TEXT_D_YELLOW);
		cout << player->getAttack(i)->name;
		cf::setTextColor();

		if (player->getLevel() < 2)
		{
			cout << " | Damage: (";
			cf::setTextColor(TEXT_D_RED);
			cout << player->getAttack(i)->damageHP - ((player->getAttack(i)->damageHP / 10.0f) + (enemy->getCurrDEF() / 10.0f));

		}
		else
		{
			cout << " | Damage: (";
			cf::setTextColor(TEXT_D_RED);
			cout << player->getAttack(i)->damageHP + (player->getLevel() * PLAYER_LEVEL_COUNTER) - ((player->getAttack(i)->damageHP / 10.0f) + (enemy->getCurrDEF() / 10.0f));
		}

		cf::showMassage(" ; ");
		cf::setTextColor(TEXT_L_BLUE);
		cout << player->getAttack(i)->damageMP;
		cf::showMassage(" ; ");
		cf::setTextColor(TEXT_L_GRAY);
		cout << player->getAttack(i)->damageDEF;
		cf::showMassage(")");

		cout << " | Mana cost: ";
		cf::setTextColor(TEXT_L_BLUE);
		cout << player->getAttack(i)->manaCost << endl;
		cf::setTextColor();
	}
}
void showPotions()
{
	cf::showMassage("Potions:\n", TEXT_D_YELLOW);
	cf::showMassage("1 - ", TEXT_L_GRAY);
	cout << "Health (";
	cf::setTextColor(TEXT_L_RED);
	cout << player->getHealthPotions();
	cf::setTextColor();
	cout << ")\n";
	cf::showMassage("2 - ", TEXT_L_GRAY);
	cout << "Mana (";
	cf::setTextColor(TEXT_L_BLUE);
	cout << player->getManaPotions();
	cf::setTextColor();
	cout << ")\n";
	cf::showMassage("0 - Back\n\n", TEXT_D_RED);
}
void showStats()
{
	std::system("cls");
	cf::showMassage("FIGHTING GAME\n", TEXT_D_YELLOW);
	cf::showMassage("\n#-----------------------------------------------------#\n", TEXT_L_GRAY);
	cf::showMassage("\n\t\t\tYOUR STATS\n", TEXT_L_GREEN);
	cf::showMassage("\n#-----------------------------------------------------#\n\n", TEXT_L_GRAY);

	cf::setTextColor(TEXT_YELLOW);
	cout << "Level: ";
	cout << player->getLevel();

	cf::setTextColor(TEXT_L_RED);
	cout << "\nHP: ";
	cout << player->getCurrHP() << " / " << player->getMaxHP();

	cf::setTextColor(TEXT_L_BLUE);
	cout << "\nMP: ";
	cout << player->getCurrMP() << " / " << player->getMaxMP();

	cf::setTextColor(TEXT_L_GRAY);
	cout << "\nDEF: ";
	cout << player->getMaxDEF() << endl;

	cf::setTextColor(TEXT_L_RED);
	cout << "\nAttacks:\n";
	showAttacks();
	cf::setTextColor();
}

int checkRestart()
{
	cf::showMassage("Do you want to restart?\n", TEXT_L_GREEN);
	cout << "1 - Yes | 2 - No\n\n";

	cf::showMassage("Choose option: ", TEXT_D_YELLOW);
	int restartOption = cf::getInputInt();

	if (restartOption == 1)
	{
		player = new Player();
		enemy = new Enemy();
		initializeSaveData();
		std::system("cls");
	}
	else if (restartOption == 2)
	{
		std::system("cls");
		showStats();
		std::ofstream("data.json") << std::endl;
		isOpen = false;
		return 0;
	}
}
int checkNextEnemy()
{
	cf::showMassage("Do you want to fight your next opponent?\n", TEXT_L_GREEN);
	cout << "1 - Yes | 2 - No\n\n";

	cf::showMassage("Choose option: ", TEXT_D_YELLOW);
	int nextEnemyOption = cf::getInputInt();

	if (nextEnemyOption == 1)
	{
		enemy->levelUp();
		enemy->isAlive = true;
		player->levelUp();
		player->recover();
		std::system("cls");
	}
	else if (nextEnemyOption == 2)
	{
		showStats();
		isOpen = false;
		return 0;
	}
}
void checkEnemyAttack()
{
	if (enemy->prevAttack.name == enemy->currAttack.name)
	{
		while (enemy->prevAttack.name == enemy->currAttack.name)
		{
			enemy->currAttack = *enemy->getRandAttack();
		}
	}

	if (enemy->getCurrHP() > enemy->currAttack.damageHP +
		enemy->currAttack.damageMP +
		enemy->currAttack.damageDEF)
	{
		Attack* newAttack = nullptr;

		for (int i = 0; i < enemy->getAttackListRange(); i++)
		{
			if (enemy->getAttack(i)->damageHP +
				enemy->getAttack(i)->damageHP +
				enemy->getAttack(i)->damageHP >= enemy->getCurrHP())
			{
				newAttack = enemy->getAttack(i);
			}
			else
			{
				continue;
			}
		}

		delete newAttack;
	}

	if (enemy->currAttack.manaCost > enemy->getCurrMP() + 0.8f)
	{
		for (int i = 0; i < enemy->getAttackListRange(); i++)
		{
			if (enemy->getAttack(i)->manaCost <= enemy->getCurrMP() + 0.8f && enemy->getAttack(i)->manaCost != 0.0f)
			{
				enemy->currAttack = *enemy->getAttack(i);
				enemyAttack();
				enemy->prevAttack = enemy->currAttack;
				break;
			}
			else
			{
				if (enemy->getManaPotions() > 0)
				{
					enemy->useManaPotion();
					checkEnemyAttack();
					break;
				}
				else
				{
					if (enemy->getAttack(i)->manaCost == 0.0f)
					{
						enemy->currAttack = *enemy->getAttack(i);
						enemyAttack();
						enemy->prevAttack = enemy->currAttack;
						break;
					}
				}
			}
		}
	}
	else
	{
		enemyAttack();
		enemy->prevAttack = enemy->currAttack;
	}
	
	this_thread::sleep_for(chrono::duration(2s));
	std::system("cls");
}

int main()
{
	cout << "Updating..." << endl;
	thread* thr_checkData = new thread(checkSaveData);
	thr_checkData->join();
	std::system("cls");
	delete thr_checkData;

	cout << fixed << setprecision(0);

	int chosenOption = -1;
	bool isPlayerMove = true;

	while (isOpen)
	{
		drawUI();

		if (isPlayerMove)
		{
			if (player->isAlive)
			{
				if (enemy->isAlive)
				{
					if (chosenOption == 0)
					{
						std::system("cls");
						showStats();
						cf::showMassage("\nDo you want to save your progress?\n", TEXT_D_YELLOW);
						cout << "1 - Yes | 2 - No\n\n";

						cf::showMassage("Choose option: ", TEXT_D_YELLOW);
						int quitOption = cf::getInputInt();

						if (quitOption == 1)
						{
							cf::setTextColor(TEXT_L_GRAY);
							cout << "\nSaving data...\n";
							thread* thr_saveData = new thread(initializeSaveData);
							thr_saveData->join();
							cf::showMassage("\nYour progress has been saved successful\n", TEXT_L_GREEN);
							delete thr_saveData;
							isOpen = false;
							chosenOption = -1;
							break;
						}
						else if (quitOption == 2)
						{
							std::ofstream("data.json") << std::endl;
							isOpen = false;
							chosenOption = -1;
							break;
						}
					}
					else if (chosenOption == 1)
					{
						if (isPlayerMove)
						{
							cf::showMassage("Attacks:\n", TEXT_D_YELLOW);
							cf::showMassage("0 - Back\n", TEXT_D_RED);
							showAttacks();
							cf::showMassage("\nChoose attack: ", TEXT_D_YELLOW);
							int chosenAttack = cf::getInputInt() - 1;

							if (chosenAttack == -1)
							{
								chosenOption = -1;
							}
							else if (chosenAttack > -1 && chosenAttack < player->getAttackListRange() && player->getAttack(chosenAttack)->manaCost <= player->getCurrMP() + 0.8f)
							{
								if (player->getLevel() < 2)
								{
									enemy->takeDamage(player->getAttack(chosenAttack)->damageHP,
										player->getAttack(chosenAttack)->damageMP,
										player->getAttack(chosenAttack)->damageDEF);
								}
								else
								{
									enemy->takeDamage(player->getAttack(chosenAttack)->damageHP + (player->getLevel() * PLAYER_LEVEL_COUNTER),
										player->getAttack(chosenAttack)->damageMP,
										player->getAttack(chosenAttack)->damageDEF);
								}

								player->useMana(player->getAttack(chosenAttack)->manaCost);

								std::system("cls");
								drawUI();
								cf::showMassage(player->getAttack(chosenAttack)->name + '!', TEXT_L_GREEN);

								if (enemy->isAlive)
								{
									isPlayerMove = false;
								}
								else
								{
									chosenOption = -1;
								}

								this_thread::sleep_for(chrono::duration(2s));
								std::system("cls");
							}

							std::system("cls");
						}
					}
					else if (chosenOption == 2)
					{
						showPotions();
						cf::showMassage("Choose potion: ", TEXT_D_YELLOW);
						int chosenPotion = cf::getInputInt();

						if (chosenPotion == 1)
						{
							if (player->getHealthPotions() > 0)
							{
								player->useHealthPotion();
							}
							else
							{
								cf::showError("You don't have health potions");
								cf::getEnter();
								std::system("cls");
							}
						}
						else if (chosenPotion == 2)
						{
							if (player->getManaPotions() > 0)
							{
								player->useManaPotion();
							}
							else
							{
								cf::showError("You don't have mana potions");
								cf::getEnter();
								std::system("cls");
							}
						}
						else if (chosenPotion == 0)
						{
							std::system("cls");
						}
						else
						{
							cf::showError("uncorrect chosen potion");
							cf::getEnter();
							std::system("cls");
						}

						chosenOption = -1;
					}
					else
					{
						cf::showMassage("Choose option: ", TEXT_D_YELLOW);
						chosenOption = cf::getInputInt();
						std::system("cls");
					}
				}
				else
				{
					checkNextEnemy();
				}
			}
			else
			{
				checkRestart();
			}
		}
		else
		{
			checkEnemyAttack();
			isPlayerMove = true;
		}
	}
	
	delete player;
	delete enemy;
	return EXIT_SUCCESS;
}
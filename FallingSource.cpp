#include "stdafx.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include "ConsoleGaming.h"

using namespace std;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WindowWidth = 80;
const int WindowHeight = 29;
// Rock variables
const char RockSymbol = '#';
const char RockSymbol1 = '^';
const char RockSymbol2 = '&';
int rockSpeed = 2;

// Dwarf variables
int dwarfSpeed = 2;

// Game variables
unsigned long sleepDuration = 200;

vector<GameObject> dwarf;
vector<GameObject> dwarf2;
vector<GameObject> rocks;
vector<GameObject> line;
vector<GameObject> bonus;
vector<GameObject> bonusNegative;


unsigned int frameCounter = 0;
unsigned int rockSpawnInterval = 5;
unsigned int rockSpawnInterval2 = 20;
unsigned int rockSpawnInterval3 = 25;
void Update()
{
	COORD direction = { 0, 0 };
	if (_kbhit())
	{
		char key = _getch();
		switch (key)
		{
		case 75:
			direction.X = -dwarfSpeed;
			direction.Y = 0;
			break;
		case 72:
			direction.X = 0;
			direction.Y = -dwarfSpeed;
			break;
		case 77:
			direction.X = dwarfSpeed;
			direction.Y = 0;
			break;
		case 80:
			direction.X = 0;
			direction.Y = dwarfSpeed;
			break;
		};
	}
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		dwarfBody->Coordinates.X += direction.X;
		dwarfBody->Coordinates.Y += direction.Y;
		if (dwarfBody->Coordinates.X >= WindowWidth)
		{
			for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
			{
				dwarfBody->Coordinates.X -= direction.X;
			}
		}
		if (dwarfBody->Coordinates.X <0)
		{
			for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
			{
				dwarfBody->Coordinates.X -= direction.X;
			}
		}
		if (dwarfBody->Coordinates.Y >= WindowHeight - 4)
		{
			for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
			{
				dwarfBody->Coordinates.Y -= direction.Y;
			}
		}
		if (dwarfBody->Coordinates.Y <0)
		{
			for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
			{
				dwarfBody->Coordinates.Y -= direction.Y;
			}
		}
	}
	for (randomAccess_iterator dwarfBody = dwarf2.begin(); dwarfBody != dwarf2.end(); ++dwarfBody)
	{
		dwarfBody->Coordinates.X += direction.X;
		dwarfBody->Coordinates.Y += direction.Y;
	}

	// Update the position of all rocks. Remove any rock that goes outside the window
	for (randomAccess_iterator rock = rocks.begin(); rock != rocks.end(); /* Empty clause so we can delete elements */)
	{
		rock->Coordinates.Y += rockSpeed;
		if (rock->Coordinates.Y > WindowHeight-4.5)
		{
			rock = rocks.erase(rock);
		}
		else
		{
			++rock;
		}
	}
	for (randomAccess_iterator bonus1 = bonus.begin(); bonus1 != bonus.end(); /* Empty clause so we can delete elements */)
	{
		bonus1->Coordinates.Y += rockSpeed;
		if (bonus1->Coordinates.Y > WindowHeight - 4.5)
		{
			bonus1 = bonus.erase(bonus1);
		}
		else
		{
			++bonus1;
		}
	}
	for (randomAccess_iterator bonus3 = bonusNegative.begin(); bonus3 != bonusNegative.end(); /* Empty clause so we can delete elements */)
	{
		bonus3->Coordinates.Y += rockSpeed;
		if (bonus3->Coordinates.Y > WindowHeight - 4.5)
		{
			bonus3 = bonusNegative.erase(bonus3);
		}
		else
		{
			++bonus3;
		}
	}
	if (frameCounter % rockSpawnInterval == 0)
	{
		// Spawn a new rock at every x frames
		int x = rand() % WindowWidth;
		rocks.push_back(GameObject(x, 0, RockSymbol));
	}
	++frameCounter;
	if (frameCounter % rockSpawnInterval2 == 0)
	{
		// Spawn a new rock at every x frames
		int x = rand() % WindowWidth;
		bonus.push_back(GameObject(x, 0, RockSymbol1));
		bonus.push_back(GameObject(x+1, 1, RockSymbol1));
		bonus.push_back(GameObject(x+2, 0, RockSymbol1));
	}
	++frameCounter;
	if (frameCounter % rockSpawnInterval3 == 0)
	{
		// Spawn a new rock at every x frames
		int x = rand() % WindowWidth;
		bonusNegative.push_back(GameObject(x, 0, RockSymbol2));
		bonusNegative.push_back(GameObject(x + 1, 1, RockSymbol2));
		bonusNegative.push_back(GameObject(x + 2, 2, RockSymbol2));
	}
	++frameCounter;

}
void Draw3()
{
	ClearScreen(consoleHandle);

	for (const_iterator dwarfBody = dwarf2.cbegin(); dwarfBody != dwarf2.cend(); ++dwarfBody)
	{
		dwarfBody->Draw(consoleHandle);
	}
	for (const_iterator dwarfBody = dwarf.cbegin(); dwarfBody != dwarf.cend(); ++dwarfBody)
	{
		dwarfBody->Draw(consoleHandle);
	}
}

void Draw2()
{
	ClearScreen(consoleHandle);

	for (const_iterator dwarfBody = dwarf2.cbegin(); dwarfBody != dwarf2.cend(); ++dwarfBody)
	{
		dwarfBody->Draw(consoleHandle);
	}
	for (const_iterator rock = rocks.cbegin(); rock != rocks.cend(); ++rock)
	{
		rock->Draw(consoleHandle);
	}
	for (const_iterator line1 = line.cbegin(); line1 != line.cend(); ++line1)
	{
		line1->Draw(consoleHandle);
	}
	for (const_iterator bonus2 = bonus.cbegin(); bonus2 != bonus.cend(); ++bonus2)
	{
		bonus2->Draw(consoleHandle);
	}
	for (const_iterator bonus3 = bonusNegative.cbegin(); bonus3 != bonusNegative.cend(); ++bonus3)
	{
		bonus3->Draw(consoleHandle);
	}
}
void Draw()
{
	ClearScreen(consoleHandle);

	for (const_iterator dwarfBody = dwarf.cbegin(); dwarfBody != dwarf.cend(); ++dwarfBody)
	{
		dwarfBody->Draw(consoleHandle);
	}
	for (const_iterator rock = rocks.cbegin(); rock != rocks.cend(); ++rock)
	{
		rock->Draw(consoleHandle);
	}
	for (const_iterator line1 = line.cbegin(); line1 != line.cend(); ++line1)
	{
		line1->Draw(consoleHandle);
	}
	for (const_iterator bonus2 = bonus.cbegin(); bonus2 != bonus.cend(); ++bonus2)
	{
		bonus2->Draw(consoleHandle);
	}
	for (const_iterator bonus3 = bonusNegative.cbegin(); bonus3 != bonusNegative.cend(); ++bonus3)
	{
		bonus3->Draw(consoleHandle);
	}
}
void Collision()
{
	for (const_iterator dwarfBody = dwarf.cbegin(); dwarfBody != dwarf.cend(); ++dwarfBody)
	{
		for (const_iterator rock = rocks.cbegin(); rock != rocks.cend(); ++rock)
		{
			if ((rock->Coordinates.Y == dwarfBody->Coordinates.Y) && (rock->Coordinates.X == dwarfBody->Coordinates.X))
			{
				ClearScreen(consoleHandle);
				cout << "GAME OVER! " << endl;
				system("pause");
			}
		}
	}
	for (const_iterator dwarfBody = dwarf2.cbegin(); dwarfBody != dwarf2.cend(); ++dwarfBody)
	{
		for (const_iterator rock = rocks.cbegin(); rock != rocks.cend(); ++rock)
		{
			if ((rock->Coordinates.Y == dwarfBody->Coordinates.Y) && (rock->Coordinates.X == dwarfBody->Coordinates.X))
			{
				ClearScreen(consoleHandle);
				cout << "GAME OVER! " << endl;
				system("pause");
			}
		}
	}
}
void Collision1()
{
	for (const_iterator dwarfBody = dwarf.cbegin(); dwarfBody != dwarf.cend(); ++dwarfBody)
	{
		for (const_iterator bonus2 = bonus.cbegin(); bonus2 != bonus.cend(); ++bonus2)
		{
			if ((bonus2->Coordinates.Y == dwarfBody->Coordinates.Y) && (bonus2->Coordinates.X == dwarfBody->Coordinates.X))
			{
				dwarfSpeed = 3;
			}
		}
	}

	for (const_iterator dwarfBody = dwarf2.cbegin(); dwarfBody != dwarf2.cend(); ++dwarfBody)
	{
		for (const_iterator bonus2 = bonus.cbegin(); bonus2 != bonus.cend(); ++bonus2)
		{
			if ((bonus2->Coordinates.Y == dwarfBody->Coordinates.Y) && (bonus2->Coordinates.X == dwarfBody->Coordinates.X))
			{
				dwarfSpeed = 3;
			}
		}
	}
	for (const_iterator dwarfBody = dwarf.cbegin(); dwarfBody != dwarf.cend(); ++dwarfBody)
	{
		for (const_iterator bonus3 = bonusNegative.cbegin(); bonus3 != bonusNegative.cend(); ++bonus3)
		{
			if ((bonus3->Coordinates.Y == dwarfBody->Coordinates.Y) && (bonus3->Coordinates.X == dwarfBody->Coordinates.X))
			{
				rockSpeed = 3;
			}
		}
	}
	for (const_iterator dwarfBody = dwarf2.cbegin(); dwarfBody != dwarf2.cend(); ++dwarfBody)
	{
		for (const_iterator bonus3 = bonusNegative.cbegin(); bonus3 != bonusNegative.cend(); ++bonus3)
		{
			if ((bonus3->Coordinates.Y == dwarfBody->Coordinates.Y) && (bonus3->Coordinates.X == dwarfBody->Coordinates.X))
			{
				rockSpeed = 3;
			}
		}
	}
}


int main()
{
	int dwarfY = WindowHeight - 7;
	int dwarfX = WindowWidth / 2;
	char dwarfSymbol = 'x';
	int lineY = WindowHeight - 4.4;
	char lineSymbol = '_';
	int choice;
	bool gameOn = true;
	while (gameOn != false){
		cout << "*******************************\n";
		cout << " 1 - Start the game.\n";
		cout << " 2 - Story.\n";
		cout << " 3 - Help.\n";
		cout << " 4 - Exit.\n";
		cout << " Enter your choice and press return: ";

		cin >> choice;

		switch (choice)
		{
		case 1:
			consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			srand(time(NULL));
			
			dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 1, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 1, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 1, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 1, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX - 2, dwarfY, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX, dwarfY, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX, dwarfY + 1, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX - 1, dwarfY + 2, dwarfSymbol));
			dwarf.push_back(GameObject(dwarfX + 1, dwarfY + 2, dwarfSymbol));

			while (true)
			{
				Update();
				Draw();
				Sleep(sleepDuration);
				Collision();
				Collision1();
			}
			break;
		case 2:
		{
				  consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

				  srand(time(NULL));

				  cout << "Choose your dwarf:";

				  dwarf2.push_back(GameObject(dwarfX, dwarfY - 4, '2'));
				  dwarf.push_back(GameObject(dwarfX - 6, dwarfY - 4, '1'));

				  dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX, dwarfY, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX + 2, dwarfY, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX - 2, dwarfY, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX, dwarfY + 1, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX - 1, dwarfY + 2, dwarfSymbol));
				  dwarf.push_back(GameObject(dwarfX + 1, dwarfY + 2, dwarfSymbol));

				  dwarf2.push_back(GameObject(dwarfX - 7, dwarfY - 1, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 6, dwarfY - 2, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 6, dwarfY - 1, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 5, dwarfY - 1, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 4, dwarfY - 1, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 8, dwarfY - 1, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 8, dwarfY, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 4, dwarfY - 2, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 6, dwarfY, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 6, dwarfY + 1, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 7, dwarfY + 2, dwarfSymbol));
				  dwarf2.push_back(GameObject(dwarfX - 5, dwarfY + 2, dwarfSymbol));
				  Update();
				  Draw3();
				  Sleep(sleepDuration);
				  int number;
				  cout << endl;
				  cout << "Choose your dwarf:";
				  cin >> number;
				  switch (number)
				  {
				  case 1:
				  {
							ClearScreen(consoleHandle);
							consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

							srand(time(NULL));

							dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 1, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 1, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 1, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 1, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX - 2, dwarfY, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX, dwarfY, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX, dwarfY + 1, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX - 1, dwarfY + 2, dwarfSymbol));
							dwarf.push_back(GameObject(dwarfX + 1, dwarfY + 2, dwarfSymbol));

							while (true)
							{
								Update();
								Draw();
								Sleep(sleepDuration);
								Collision();
								Collision1();
							}
							break;
				  }
				  case 2:
				  {
							ClearScreen(consoleHandle);
							consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

							srand(time(NULL));

							dwarf2.push_back(GameObject(dwarfX - 1, dwarfY - 1, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX + 1, dwarfY - 1, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX + 2, dwarfY - 1, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX - 2, dwarfY - 1, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX - 2, dwarfY, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX, dwarfY, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX, dwarfY + 1, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX - 1, dwarfY + 2, dwarfSymbol));
							dwarf2.push_back(GameObject(dwarfX + 1, dwarfY + 2, dwarfSymbol));

							while (true)
							{
								Update();
								Draw2();
								Sleep(sleepDuration);
								Collision();
								Collision1();
							}
							break;
				  }

				  default:
					  break;
				  }
		}
		case 3:
			cout << "Ahahah, you really think I will help you?\n";
			// rest of code here
			break;
		case 4:
			cout << "End of Program.\n";
			gameOn = false;
			break;
		default:
			cout << "Not a Valid Choice. \n";
			cout << "Choose again.\n";
			cin >> choice;
			break;
		}

	}
	

	return 0;
}
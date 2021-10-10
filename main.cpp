#include <iostream>
#include <windows.h>

using namespace std;


char board[64];
bool IsGame = true;

bool UpLeft, UpRight, DownLeft, DownRight;
short RandomDirection, choice;

int PlayerPoints = 0, GamerPoints = 0;
int PlayerY = 3, GamerY = 3;
int Ball_Y = 4, Ball_X = 2;
int BallSpeed = 100, PointsToWin = 10;


void mapRefresh()
{
	for (int i = 0; i < 64; i++)
	{
		board[i] = '.';
	}
}

void mapGenerate()
{
	system("CLS");

	for (int i = 0; i < 64; i++)
	{
		board[Ball_X + Ball_Y * 8] = 'o';

		board[7 + (PlayerY * 8)] = 'G';
		board[7 + ((PlayerY + 1) * 8)] = 'G';

		board[0 + (GamerY * 8)] = 'x';
		board[0 + ((GamerY + 1) * 8)] = 'x';



		if (i % 8 == 0 || i == 0)
		{
			printf("\n");
			printf("%c", board[i]);
			printf(" ");
		}
		else
		{
			printf("%c", board[i]);
			printf(" ");
		}
	}

	cout << endl << GamerPoints << "           " << PlayerPoints;
}

void BallDirection()
{
	if (Ball_Y == 0)
	{
		if (UpLeft == true)
		{
			UpLeft = false;
			DownLeft = true;
		}
		if (UpRight == true)
		{
			UpRight = false;
			DownRight = true;
		}
	}
	if (Ball_Y == 7)
	{
		if (DownLeft == true)
		{
			DownLeft = false;
			UpLeft = true;
		}
		if (DownRight == true)
		{
			DownRight = false;
			UpRight = true;
		}
	}

	if (Ball_X == 0)
	{
		PlayerPoints++;
		if (UpLeft == true)
		{
			UpLeft = false;
			UpRight = true;
		}
		if (DownLeft == true)
		{
			DownLeft = false;
			DownRight = true;
		}
	}
	if (Ball_X == 7)
	{
		GamerPoints++;
		if (UpRight == true)
		{
			UpRight = false;
			UpLeft = true;
		}
		if (DownRight == true)
		{
			DownRight = false;
			DownLeft = true;
		}
	}
	if (Ball_X == 1 && (GamerY == Ball_Y || GamerY + 1 == Ball_Y))
	{
		if (UpLeft == true)
		{
			UpLeft = false;
			UpRight = true;
		}
		if (DownLeft == true)
		{
			DownLeft = false;
			DownRight = true;
		}
	}
	if (Ball_X == 6 && (PlayerY == Ball_Y || PlayerY + 1 == Ball_Y))
	{
		if (UpRight == true)
		{
			UpRight = false;
			UpLeft = true;
		}
		if (DownRight == true)
		{
			DownRight = false;
			DownLeft = true;
		}
	}
}

void WinCheck()
{
	if (PlayerPoints >= PointsToWin)
	{
		IsGame = false;
		system("CLS");
		cout << endl << "\n\nGracz po prawej wygral! (" << GamerPoints << ":" << PlayerPoints << ")\n";
		Sleep(3000);
	}
	if (GamerPoints >= PointsToWin)
	{
		IsGame = false;
		system("CLS");
		cout << endl << "\n\nGracz po lewej wygral! (" << GamerPoints << ":" << PlayerPoints << ")\n";
		Sleep(3000);
	}
}

void GameOptions()
{
	while (true)
	{
		system("CLS");
		cout << "1. Predkosc pilki\n2. Ilosc pkt do wygranej\n3. Powrot do menu\n";
		cin >> choice;

		if (choice == 1)
		{
			system("CLS");
			cout << "1. Wolno\n2. Normalnie\n3. Szybko\n4. Powrot do opcji\n";
			cin >> choice;
			if (choice == 1)
			{
				BallSpeed = 150;
			}
			else if (choice == 2)
			{
				BallSpeed = 100;
			}
			else if (choice == 3)
			{
				BallSpeed = 50;
			}
			else
			{
				continue;
			}
		}
		else if (choice == 2)
		{
			system("CLS");
			cout << "Wprowadz ilosc pkt do wygranej (wpisz 0, jesli nie chcesz nic zmieniac): ";
			cin >> choice;

			if (choice == 0)
			{
				continue;
			}
			else if (choice < 0)
			{
				cout << "\n\nWartosc nieprawidlowa!";
				continue;
			}
			else
			{
				PointsToWin = choice;
			}
		}
		else
		{
			break;
		}
	}
}

DWORD WINAPI MapRefreshing(LPVOID lpParameter)
{
	while (IsGame)
	{
		mapRefresh();
		mapGenerate();

		Sleep(15);
	}
	
	return 0;
}

DWORD WINAPI BallMove(LPVOID lpParameter)
{
	while (IsGame)
	{
		BallDirection();

		if (UpLeft == true)
		{
			Ball_Y--;
			Ball_X--;

			Sleep(BallSpeed);
		}
		if (UpRight == true)
		{
			Ball_Y--;
			Ball_X++;

			Sleep(BallSpeed);
		}
		if (DownLeft == true)
		{
			Ball_Y++;
			Ball_X--;
			
			Sleep(BallSpeed);
		}
		if (DownRight == true)
		{
			Ball_Y++;
			Ball_X++;
			
			Sleep(BallSpeed);
		}
	}

	return 0;
}

DWORD WINAPI GamerControls(LPVOID lpParameter)
{

	if (GamerY != 0)
	{
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{

			GamerY--;
			Sleep(50);


			board[0 + (GamerY * 8)] = 'x';
			board[0 + ((GamerY + 1) * 8)] = 'x';


		}
	}


	if (GamerY != 6)
	{
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{

			GamerY++;
			Sleep(50);


			board[0 + (GamerY * 8)] = 'x';
			board[0 + ((GamerY + 1) * 8)] = 'x';


		}
	}

	return 0;
}

DWORD WINAPI PlayerControls(LPVOID lpParameter)
{

	if (PlayerY != 0)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{

			PlayerY--;
			Sleep(50);


			board[7 + (PlayerY * 8)] = 'x';
			board[7 + ((PlayerY + 1) * 8)] = 'x';


		}
	}

	if (PlayerY != 6)
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{

			PlayerY++;
			Sleep(50);

			

			board[7 + (PlayerY * 8)] = 'x';
			board[7 + ((PlayerY + 1) * 8)] = 'x';


		}
	}

	return 0;
}

int main()
{

	while (true)
	{
		system("CLS");

		cout << "\n\n1. Graj\n2. Opcje\n";
		cin >> choice;

		if (choice == 2)
		{
			GameOptions();
		}
		else
		{
			system("CLS");
			break;
		}
	}
	
	cout << "Kliknij ENTER, aby zagrac.";
	getchar();								//I don't know, why 2 getchar's, but hey! - it works...somehow
	getchar();

	srand(time(NULL));
	RandomDirection = (rand() % 4) + 1;

	if (RandomDirection == 1)
	{
		UpLeft = true;
	}
	else if (RandomDirection == 2)
	{
		UpRight = true;
	}
	else if (RandomDirection == 3)
	{
		DownLeft = true;
	}
	else if (RandomDirection == 4)
	{
		DownRight = true;
	}

	mapRefresh();
	mapGenerate();

	HANDLE MapRefreshingThread = CreateThread(NULL, 0, MapRefreshing, NULL, 0, NULL);
	HANDLE BallMoveThread = CreateThread(NULL, 0, BallMove, NULL, 0, NULL);

	//game loop
	while (IsGame)
	{
		WinCheck();

		//calling threads
		HANDLE GamerControlsThread = CreateThread(NULL, 0, GamerControls, NULL, 0, NULL);
		HANDLE PlayerControlsThread = CreateThread(NULL, 0, PlayerControls, NULL, 0, NULL);

		//waiting for threads
		WaitForSingleObject(GamerControlsThread, INFINITE);
		WaitForSingleObject(PlayerControlsThread, INFINITE);

		//closing threads
		CloseHandle(GamerControlsThread);
		CloseHandle(PlayerControlsThread);

	}


	WaitForSingleObject(BallMoveThread, INFINITE);
	WaitForSingleObject(MapRefreshingThread, INFINITE);
	
	CloseHandle(BallMoveThread);
	CloseHandle(MapRefreshingThread);

	return 0;

}
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define UP        72
#define DOWN  80
#define LEFT     75
#define RIGHT   77
using namespace std;
int currentX, currentY;

char ShowMap[20][21] =
{
	"++++++++++++++++++++",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"++++++++++++++++++++"
};
void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void SetRandomPlus()
{
	int checkCount = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int ranX = rand() % 18 + 1;
		int ranY = rand() % 18 + 1;
		if (ShowMap[ranY][ ranX] != '+')
		{
			ShowMap[ranY][ ranX] = '+';
		}
		else
		{
			--i;
		}
	}

}

void displayScreen()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			gotoXY(x, y);
			_putch(ShowMap[y][x]);
		}
	}

	gotoXY(currentX, currentY);
	_putch('&');
	gotoXY(30, 2);
	cout << "Q:종료";
	gotoXY(30, 3);
	cout << currentX << " " << currentY;

}

void RemoveWall()
{
	if (currentY + 1 == 19)
	{
		ShowMap[currentY - 18][currentX] = '.';
		ShowMap[currentY + 1][currentX] = '.';
	}
	if (currentY - 1 == 0)
	{
		ShowMap[currentY + 18][currentX] = '.';
		ShowMap[currentY - 1][currentX] = '.';
	}
	if (currentX + 1 == 19)
	{
		ShowMap[currentY][currentX - 18] = '.';
		ShowMap[currentY][currentX + 1] = '.';
	}
	if (currentX - 1 == 0)
	{
		ShowMap[currentY][currentX + 18] = '.';
		ShowMap[currentY][currentX - 1] = '.';
	}
}

void RemovePlus()
{
	if (currentY + 1 != 19 && currentX + 1 != 19 && currentY - 1 != 0 && currentX - 1 != 0)
	{
		if (ShowMap[currentY + 1][currentX] == '+')
		{
			ShowMap[currentY + 1][currentX] = '.';
		} //아래
		if (ShowMap[currentY - 1][currentX] == '+')
		{
			ShowMap[currentY - 1][currentX] = '.';
		} // 위
		if (ShowMap[currentY][currentX + 1] == '+')
		{
			ShowMap[currentY][currentX + 1] = '.';

		} //오른
		if (ShowMap[currentY][currentX - 1] == '+')
		{
			ShowMap[currentY][currentX - 1] = '.';

		} //왼

	}
}

void Move(int dir)
{
	int dir_x = 0, dir_y = 0;

	switch (dir)
	{
	case LEFT:
		dir_x = -1;
		break;
	case RIGHT:
		dir_x = 1;
		break;
	case UP:
		dir_y = -1;
		break;
	case DOWN:
		dir_y = 1;
		break;
	}

	if (ShowMap[currentY + dir_y][currentX + dir_x] != '+')
	{
		currentX += dir_x;
		currentY += dir_y;
		if (currentX == -1)
		{
			currentX = 19;
		}
		if (currentX == 20)
		{
			currentX = 0;
		}
		if (currentY == -1)
		{
			currentY = 19;
		}
		if (currentY == 20)
		{
			currentY = 0;
		}
	}
}
int main()
{
	int ch;
	currentX = 1;
	currentY = 1;
	SetRandomPlus();
	while (true)
	{

		displayScreen();
		ch = _getch();

		if (ch == 0xE0 || ch == 0)
		{
			ch = _getch();
			switch (ch)
			{
			case LEFT:
			case RIGHT:
			case UP:
			case DOWN:
				Move(ch);
				break;
			}
		}
		else
		{
			ch = tolower(ch);
			if (ch == 'q')
			{
				exit(0);
			}
			else if (ch == 'z')
			{
				ShowMap[currentY][currentX] = 'X';
			}
			else if (ch == 'a')
			{
				RemovePlus();
			}
			else if (ch == 'b')
			{
				RemoveWall();
			}
		}
	}
	return 0;
}

/**************************************
* Автор: Калинин Андрей               *
* Лабораторная №12                    *
* Дата: 10.12.2023                    *
* Название: Змейка                    *
**************************************/

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
unsigned int mapRange = 0;
int mapWidth = 60;
int mapHeight = 20;
int xCoord;
int yCoord;
int xCoordApple;
int yCoordApple;
int xTail[100];
int yTail[100];
int countTail;
int gameScore;
bool teleport = false;
bool checkTeleport = false;
enum snakeDirection { stop = 0, moveUp, moveRight, moveDown, moveLeft };
snakeDirection defaultDirection;

void gameSettings() {
  gameOver = false;
  defaultDirection = stop;
  srand(time(0));
  xCoord = rand() % mapWidth;
  yCoord = rand() % mapHeight;
  xCoordApple = rand() % mapWidth - 1;
  yCoordApple = rand() % mapHeight;
  gameScore = 0;
}

void map() {
  system("cls"); // очистка экрана - обновление карты
  for (int borderIndex = 0; borderIndex <= mapWidth; ++borderIndex) {
	cout << (char)2602;
  }
  cout << endl;

  if (gameScore == 2 && !checkTeleport) {
	mapWidth = 40;
	teleport = true;
	checkTeleport = true;
  } else if (gameScore == 5 && !checkTeleport) {
	mapWidth = 30;
	teleport = true;
	checkTeleport = true;
  } else if (gameScore == 15 && !checkTeleport) {
	mapWidth = 15;
	mapHeight = 15;
	teleport = true;
	checkTeleport = true;
  }

  if (teleport) {
	xCoord = mapWidth / 2;
	yCoord = mapHeight / 2;
	teleport = false;
  }

  if (gameScore > 2 && gameScore < 5) {
	checkTeleport = false;
  } else if (gameScore > 5 && gameScore < 15) {
	checkTeleport = false;
  }

  for (int mapIndex = 0; mapIndex < mapHeight; ++mapIndex) {
	for (int cellIndex = 0; cellIndex < mapWidth; ++cellIndex) {
	  if (cellIndex == 0 || cellIndex == mapWidth - 1) {
		cout << (char)2602;
	  }

	  if (mapIndex == yCoord && cellIndex == xCoord) {
		cout << "0";
	  } else if (mapIndex == yCoordApple && cellIndex == xCoordApple) {
		cout << "A";
	  } else {
		bool printTail = false;
		for (int tailIndex = 0; tailIndex < countTail; ++tailIndex) {
		  if (xTail[tailIndex] == cellIndex && yTail[tailIndex] == mapIndex) {
			printTail = true;
			cout << "o";
		  }

		}

	    if (printTail == false) {
		  cout << " ";
		}

	  }

	}
	cout << endl;
  }

  for (int borderIndex = 0; borderIndex <= mapWidth; ++borderIndex) {
	cout << (char)2602;
  }
  cout << endl;
  cout << "Score: " << gameScore << endl;
}

void controls() {
  if (_kbhit() ) { //проверка нажатия на кнопку
	switch (_getch() )  { //ловим нажатую кнопку
	  case 'w':
	    defaultDirection = moveUp;
	    break;
	  case 'd':
		defaultDirection = moveRight;
		break;
	  case 's':
		defaultDirection = moveDown;
		break;
	  case 'a':
		defaultDirection = moveLeft;
		break;
	  case 'g':
		xCoordApple = rand() % mapWidth - 1;
		yCoordApple = rand() % mapHeight;
		break;
	}
  }

}

void gameLogic() {
  int prevXCoord = xTail[0];
  int prevYCoord = yTail[0];
  int secondPrevXCoord;
  int secondPrevYCoord;

  xTail[0] = xCoord;
  yTail[0] = yCoord;

  for (int tailIndex = 1; tailIndex < countTail; ++tailIndex) {
	secondPrevXCoord = xTail[tailIndex];
	secondPrevYCoord = yTail[tailIndex];
	xTail[tailIndex] = prevXCoord;
	yTail[tailIndex] = prevYCoord;
	prevXCoord = secondPrevXCoord;
	prevYCoord = secondPrevYCoord;
  }

  switch (defaultDirection) { 
	case moveUp:
	  --yCoord;
	  break;
	case moveRight:
	  ++xCoord;
	  break;
	case moveDown:
	  ++yCoord;
	  break;
	case moveLeft:
	  --xCoord;
	  break;
  }

  if (xCoord < 0) {
	xCoord = mapWidth - 2;
  } else if (xCoord >= mapWidth - 1) {
	xCoord = 0;
  }

  if (yCoord < 0) {
	yCoord = mapHeight - 2;
  } else if (yCoord >= mapHeight) {
	yCoord = 0;
  }
  
  for (int tailDeathIndex = 0; tailDeathIndex < countTail; ++tailDeathIndex) {
	if (xTail[tailDeathIndex] == xCoord && yTail[tailDeathIndex] == yCoord) {
	  gameOver = true;
	  cout << "You lost...";
	}
  }

  if (xCoord == xCoordApple && yCoord == yCoordApple) {
	++gameScore;
	xCoordApple = rand() % mapWidth - 1;
	yCoordApple = rand() % mapHeight;
	++countTail;
  }
}

int main() {

  gameSettings();

  while (gameOver != true) {
	map();
	controls();
	gameLogic();
	Sleep(200 - 10 * countTail);
	if (countTail == 20) {
	  map();
	  controls();
	  gameLogic();
	  gameOver = true;
	  cout << "You won!" << endl;
	}
  }

  return 0;
}

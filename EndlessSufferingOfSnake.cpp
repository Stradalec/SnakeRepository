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
int xBarrier[5];
int yBarrier[5];
int barrierCount = 0;
int countTail;
int gameScore;
bool teleport = false;
bool checkTeleport = false;
bool hidden[5] = {true, true, true ,true ,true};
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
	for (int randomBarrier = 0; randomBarrier < sizeof(xBarrier); ++randomBarrier) {
		xBarrier[randomBarrier] = rand() % mapWidth / 2 - 1;
		yBarrier[randomBarrier] = rand() % mapHeight / 2;
	}
  gameScore = 0;
}

void map() {
  system("cls"); // очистка экрана - обновление карты
  char border = (char)2602;
  char barrier = 'B';
  int firstBorder = 40;
  int secondBorder = 30;
  int thirdBorder = 15;
  for (int borderIndex = 0; borderIndex <= mapWidth; ++borderIndex) {
	  cout << border;
  }
  cout << endl;

  if (gameScore == 2 && !checkTeleport) {
	  mapWidth = firstBorder;
	  teleport = true;
	  checkTeleport = true;
  } else if (gameScore == 5 && !checkTeleport) {
	  mapWidth = secondBorder;
	  teleport = true;
	  checkTeleport = true;
  } else if (gameScore == 15 && !checkTeleport) {
	  mapWidth = thirdBorder;
	  mapHeight = thirdBorder;
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
		    cout << border;
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
			  if (gameScore >= 2) {
					if (mapIndex == yBarrier[0] && cellIndex == xBarrier[0] && gameScore >= 2) {
						cout << barrier;
						hidden[0] = false;
					}
					if (mapIndex == yBarrier[1] && cellIndex == xBarrier[1] && gameScore >= 5) {
						cout << barrier;
						hidden[1] = false;
					}
					if (mapIndex == yBarrier[2] && cellIndex == xBarrier[2] && gameScore >= 8) {
						cout << barrier;
						hidden[2] = false;
					}
					if (mapIndex == yBarrier[3] && cellIndex == xBarrier[3] && gameScore >= 10) {
						cout << barrier;
						hidden[3] = false;
					}
					if (mapIndex == yBarrier[4] && cellIndex == xBarrier[4] && gameScore >= 12) {
						cout << barrier;
						hidden[4] = false;
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
	  cout << border;
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
  
  if (xCoord == xCoordApple && yCoord == yCoordApple) {
	  ++gameScore;
	  xCoordApple = rand() % mapWidth - 1;
	  yCoordApple = rand() % mapHeight;
	  ++countTail;
  }

	for (int deathIndex = 0; deathIndex < sizeof(xBarrier); ++deathIndex) {
		if (xCoord == xBarrier[deathIndex] && yCoord == yBarrier[deathIndex] && !hidden[deathIndex]) {
			gameOver = true;
		}
	}
}

int main() {
  gameSettings();

  while (gameOver != true) {
		controls();
		gameLogic();
		map();    
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

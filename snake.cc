#include <iostream>
#include <conio.h>
#include "windows.h"

//-2 - има храна
//-1 - стена
//0 - няма нищо
//1 - змия

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();
char getMapValue(int value);

const int mapwidth = 12;
const int mapheight = 12;
const int size = mapwidth * mapheight;
int map[size];

int headXposition;
int headYposition;
int direction;

// дължина на змията и брой точки 
int food = 3;

// false = end game
bool running;

int main()
{
    run();
    return 0;
}


void run()
{
    initMap();
    running = true;
    while (running) {
        // kbhit дали натиснат клавиш
        if (_kbhit()) {
            // взима това което сме натиснали
            changeDirection(_getch());
        }
        //map
        update();

        clearScreen();

        printMap();

        // изчакване 0.5 секунди
        Sleep(500);
    }

    std::cout << "\t\tGame over!" << std::endl << "\t\tYour score is: " << (food - 3);

    // Непозволява на конзолата да се затваря веднага 
    std::cin.ignore();
}


void changeDirection(char key) {
    switch (key) {
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 0) direction = 2;
        break;
    case 'a':
        if (direction != 1) direction = 3;
        break;
    }
}

// Moves snake head to new location
void move(int dx, int dy) {// tezi 2 promenlivi mogat da sa 0, 1, -1 zavisi na kude iskame da premestim glavata 

    int newX = headXposition + dx;
    int newY = headYposition + dy;

    // Check if there is food at location
    if (map[newX + newY * mapwidth] == -2) { 
        food++;

        generateFood();
    }

    else if (map[newX + newY * mapwidth] != 0) {
        running = false;
    }

    headXposition = newX;
    headYposition = newY;
    map[headXposition + headYposition * mapwidth] = food + 1;

}

void clearScreen() {
    system("cls");
}

void generateFood() {
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the map
        x = rand() % (mapwidth - 2) + 1;//v1 = rand() % 100;     // v1 in the range 0 to 99           v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
        y = rand() % (mapheight - 2) + 1;

        // If location is not free try again
    } while (map[x + y * mapwidth] != 0);

    // Place new food
    map[x + y * mapwidth] = -2;
}

// Updates the map
void update() {
    // Move in direction indicated
    switch (direction) {
    case 0: move(-1, 0);
        break;
    case 1: move(0, 1);
        break;
    case 2: move(1, 0);
        break;
    case 3: move(0, -1);
        break;
    }
    // изтриваме змията
    for (int i = 0; i < size; i++) {
        if (map[i] > 0) map[i]--;
    }
}

void initMap()
{
    // поставяме змията първоначално в средата
    headXposition = mapwidth / 2;
    headYposition = mapheight / 2;
    map[headXposition + headYposition * mapwidth] = 1;

    //слагаме долната и горната стена
    for (int x = 0; x < mapwidth; ++x) {
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }

    // слагаме страничните стени
    for (int y = 0; y < mapheight; y++) {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // слагаме първата храна
    generateFood();
}

void printMap()
{
    for (int x = 0; x < mapwidth; ++x) {
        for (int y = 0; y < mapheight; ++y) {
            // Prints the value at current x,y location
            std::cout << getMapValue(map[x + y * mapwidth]);
        }
        // Ends the line for next x value
        std::cout << std::endl;
    }
}

char getMapValue(int value)
{
    if (value > 0) return 'o';

    switch (value) {
        // Return wall
    case -1: return 'X';
        // Return food
    case -2: return 'O';
    }
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int rows = 6;
const int cols = 6;

bool isExit(int col, int row, int exit[1][2]) {
    if (col == exit[0][0] && row == exit[0][1]) {
        return true;
    }
    return false;
}

bool isHealth(int col, int row, int hpPositions[3][2], int numHp) {
    for (int i = 0; i < numHp; i++) {
        if (col == hpPositions[i][0] && row == hpPositions[i][1]) {
            return true;
        }
    }
    return false;
}

bool isWall(int col, int row, int wallPositions[12][2], int numWalls) {
    for (int i = 0; i < numWalls; i++) {
        if (col == wallPositions[i][0] && row == wallPositions[i][1]) {
            return true;
        }
    }
    return false;
}
void displayFinalMap(int currentCol, int currentRow, int exit[1][2], int hpPositions[3][2], int wallPositions[12][2], int numHp, int numWalls) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool isPlayer = (i == currentRow && j == currentCol);
            bool isExitPoint = isExit(j, i, exit);
            bool isHpPoint = isHealth(j, i, hpPositions, numHp);
            bool isWallPoint = isWall(j, i, wallPositions, numWalls);

            if (isPlayer)
                cout << "P ";
            else if (isExitPoint)
                cout << "E ";
            else if (isHpPoint)
                cout << "H ";
            else if (isWallPoint)
                cout << "W ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}
void updateLocation(int direction, int &currentCol, int &currentRow) {
    switch (direction) {
        case 6:
            if (currentCol < cols - 1)
                currentCol++;
            break;
        case 2:
            if (currentRow < rows - 1)
                currentRow++;
            break;
        case 4:
            if (currentCol > 0)
                currentCol--;
            break;
        case 8:
            if (currentRow > 0)
                currentRow--;
            break;
        default:
            cout << "Wrong direction!";
    }
}

void returnLocation(int direction, int &currentCol, int &currentRow) {
    switch (direction) {
        case 6:
            if (currentCol > 0)
                currentCol--;
            break;
        case 2:
            if (currentRow > 0)
                currentRow--;
            break;
        case 4:
            if (currentCol < cols - 1)
                currentCol++;
            break;
        case 8:
            if (currentRow < rows - 1)
                currentRow++;
            break;
        default:
            cout << "Wrong direction!";
    }
}

void displayMap(const char rows,const char cols, int currentCol, int currentRow) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == currentRow && j == currentCol) {
                cout << "P ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;           
    }
}

string getLocation(int currentCol, int currentRow) {
    return to_string(currentCol + 1) + "," + to_string(currentRow + 1);
}

int main() {
    int currentCol = 0;
    int currentRow = 0;
    int direction;
    int playerhp = 100;
    int ishptaken = 0;
    int gameover = 0;
    int a = 1;
    srand(time(NULL));
    int numWalls = 7 + (rand() % 6); // Number of walls
    int wallPositions[10][2];
    int numHp = 2 + (rand() % 3); // Number of health packs
    int hpPositions[3][2];
    int exit[1][2];
    exit[0][0] = 1 + (rand() % 6); // Random x-coordinate
    exit[0][1] = 1 + (rand() % 6); // Random y-coordinate
    for (int i = 0; i < numHp; i++) {
        hpPositions[i][0] = 1 + (rand() % 6); // Random x-coordinate
        hpPositions[i][1] = 1 + (rand() % 6); // Random y-coordinate
    }
    for (int i = 0; i < numWalls; i++) {
        wallPositions[i][0] = 1 + (rand() % 6); // Random x-coordinate
        wallPositions[i][1] = 1 + (rand() % 6); // Random y-coordinate
    }
    cout << "Welcome to the game!" << endl;
    cout << "You can use 2,4,6,8 to control player." << endl;
    string currentLocation = getLocation(currentCol, currentRow);
    cout << endl;
    cout << "Current Location: " << currentLocation << endl;
    displayMap(6,6, currentCol, currentRow);
    while (playerhp > 0 && gameover == 0) {
        cout << "Health: " << playerhp << endl;
        cout << "Which direction do you want to go?";
        cin >> direction;
        cout << endl; 
        updateLocation(direction, currentCol, currentRow);
        string currentLocation = getLocation(currentCol, currentRow);
     
        if (isWall(currentCol, currentRow, wallPositions, numWalls)) {
            playerhp = playerhp - 10;
            cout << "You bumped into a wall!";
            returnLocation(direction, currentCol, currentRow);
        }
        cout << endl;
        cout << "Current Location: " << currentLocation << endl;
        displayMap(6,6, currentCol, currentRow);
        if (isExit(currentCol, currentRow, exit)){
            displayFinalMap(currentCol, currentRow, exit, hpPositions, wallPositions, numHp, numWalls);
            cout << "Congratulations you won! Press 0 to start again." << endl;
            cin >> a;
            if (a == 0)
                main();
            gameover = 1;
        }
            if (isHealth(currentCol, currentRow, hpPositions, numHp) && ishptaken == 0) {
        cout << "50 hp recovered!" << endl;
        playerhp = playerhp + 50;
        ishptaken = 1;
    }
    }

    if (playerhp <= 0) {
        displayFinalMap(currentCol, currentRow, exit, hpPositions, wallPositions, numHp, numWalls);
        cout << "You lose the game. Press 0 to start again." << endl;
        cin >> a;
        if (a == 0)
            main();
        gameover = 1;
    }
    return 0;
}

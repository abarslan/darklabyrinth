#include <iostream>
#include <string>

using namespace std;

const int rows = 7;
const int cols = 7;

void updateLocation(int direction, int &currentCol, int &currentRow) {
    switch (direction) {
        case 6:
            currentCol = currentCol + 1;
            break;
        case 2:
            currentRow = currentRow + 1;
            break;
        case 4:
            currentCol = currentCol - 1;
            break;
        case 8:
            currentRow = currentRow - 1;
            break;
        default:
            cout << "Wrong direction!";
    }
}
void returnLocation(int direction, int &currentCol, int &currentRow) {
    switch (direction) {
         case 6:
            currentCol = currentCol - 1;
            break;
         case 2:
            currentRow = currentRow - 1;
            break;
        case 4:
            currentCol = currentCol + 1;
            break;
        case 8:
            currentRow = currentRow + 1;
            break;
        default:
            cout << "Wrong direction!";
    }
}
void displayMap(const char map[rows][cols], int currentCol, int currentRow) {
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
    return to_string(currentCol+1) + "," + to_string(currentRow+1);
}

int main() {
    char map[rows][cols];
    int currentCol = 0;
    int currentRow = 0;
    int direction;
    int playerhp = 100;
    int wall = 1;
    int ishptaken = 0;
    cout<< "Welcome to the game!" << endl;
    cout<< "You can use 2,4,6,8 to control player." << endl;
    string currentLocation = getLocation(currentCol, currentRow);
    cout << endl;
    cout << "Current Location: " << currentLocation << endl;
    displayMap(map, currentCol, currentRow);
    while(playerhp > 0){
    if(wall == 0){
        cout << "You bumped into a wall!" << endl;
        wall = 1;
    }
    if (playerhp > 100)
        playerhp = 100;
    cout << "Health: " << playerhp << endl;
    cout << "Which direction do you want to go?";
    cin >> direction;
    cout << endl;
    updateLocation(direction, currentCol, currentRow);
    if(     currentCol == -1 || currentRow == -1 || currentCol == 7 || currentRow == 7 ||
            currentCol == 1 && currentRow == 1 || currentCol == 1 && currentRow == 3 ||currentCol == 1 && currentRow == 4 || currentCol == 1 && currentRow == 5 || currentCol == 1 && currentRow == 6 ||
            currentCol == 3 && currentRow == 0 || currentCol == 3 && currentRow == 2 ||currentCol == 3 && currentRow == 4 || currentCol == 3 && currentRow == 5 || currentCol == 3 && currentRow == 6 || 
            currentCol == 4 && currentRow == 4 ||
            currentCol == 5 && currentRow == 0 || currentCol == 5 && currentRow == 1 ||currentCol == 5 && currentRow == 2 || currentCol == 5 && currentRow == 4 || currentCol == 5 && currentRow == 5)
    {  playerhp = playerhp - 50;
         wall = 0;
        returnLocation(direction, currentCol, currentRow);}
    
    currentLocation = getLocation(currentCol, currentRow);
    cout<< endl;
    cout << "Current Location: " << currentLocation << endl;
    displayMap(map, currentCol, currentRow);
    if(currentCol == 4 && currentRow == 5)
        cout << "Congratulations you won!" << endl;
    if(currentCol == 0 && currentRow == 6 && ishptaken == 0 ){
        cout << "50 hp recovered!" << endl;
        playerhp = playerhp + 50;
        ishptaken = 1;
        }
    }
   
    int a=1;
    cout << "You lose the game. Press 0 to start again." << endl;
    cin >> a;
    if( a == 0)
        main();
    return 0;
}           

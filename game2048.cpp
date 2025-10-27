#include <iostream>
#include <iomanip>  
#include <vector>
#include <ctime>
#include <conio.h>  // chars without Enter
using namespace std;
void printBoard();
void addRandomTile();
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
bool checkGameOver();


int board[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0 },
        {0, 0, 0, 0 },
        {0, 0, 0, 0 }
};


int main()
{
    srand(time(0));
    addRandomTile();
    addRandomTile();

    char input;
    bool gameOver = false;
    while (!gameOver) {
        printBoard();
        cout << "Use W/A/S/D to move: ";
        input = _getch();       // get char without  enter
        input = toupper(input); // so we can get small too

        int oldBoard[4][4];
        memcpy(oldBoard, board, sizeof(board)); // копія матриці

        switch (input) {
        case 'W': moveUp(); break;
        case 'A': moveLeft(); break;
        case 'S': moveDown(); break;
        case 'D': moveRight(); break;
        default: continue; // ignore others input except W A S D
        }
        bool moved = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (oldBoard[i][j] != board[i][j]) {
                    moved = true;
                    break;
                }
            }
            if (moved) break;
        }

        if (moved) {
            addRandomTile();
        }

        if (checkGameOver()) {  // перевірка, чи немає ходів
            gameOver = true;
            printBoard();
            cout << "Game Over!" << endl;
        }
    }
}

void addRandomTile() {
    vector<pair<int, int>> emptyCells;    //pair ==> name.first; name.second
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                emptyCells.push_back({ i, j });  //array with coordinate of empty elemts 
            }
        }
    }
    int k = rand() % emptyCells.size();     // randc position
    int row = emptyCells[k].first;          // row of rand el
    int col = emptyCells[k].second;         // col of rand el

    if (rand() % 10 == 0) {
        board[row][col] = 4;   // 10% chanse that it will be a 4 instead of 2 to make game more unexceptable
    }
    else {
        board[row][col] = 2;   // 90% chanse
    }
}

void printBoard() {
    cout << "MATRIX A" << endl;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (board[i][j] == 0)
            {
                cout << setw(5) << ". ";
            }
            else
            {
                cout << setw(5) << board[i][j];
            }
        }
        cout << endl;
    }
}

void moveLeft() {
    for (int i = 0; i < 4; i++) {
        vector<int> temp;

        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                temp.push_back(board[i][j]);
            }
        }

        vector<int> newRow;
        int k = 0;
        while (k < temp.size()) {
            if (k + 1 < temp.size() && temp[k] == temp[k + 1]) {
                newRow.push_back(temp[k] * 2);
                k += 2;
            }
            else {
                newRow.push_back(temp[k]);
                k++;
            }
        }

        while (newRow.size() < 4) {
            newRow.push_back(0);
        }

        for (int j = 0; j < 4; j++) {
            board[i][j] = newRow[j];
        }
    }
}

void moveRight() {
    for (int i = 0; i < 4; i++) {
        vector<int> temp;

        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                temp.push_back(board[i][j]);
            }
        }

        vector<int> newRow;
        int k = 0;
        while (k < temp.size()) {
            if (k + 1 < temp.size() && temp[k] == temp[k + 1]) {
                newRow.push_back(temp[k] * 2);
                k += 2;
            }
            else {
                newRow.push_back(temp[k]);
                k++;
            }
        }

        while (newRow.size() < 4) {
            newRow.push_back(0);
        }

        for (int j = 0; j < 4; j++) {
            board[i][3 - j] = newRow[j];
        }
    }
}

void moveUp() {
    for (int j = 0; j < 4; j++) {
        vector<int> temp;

        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                temp.push_back(board[i][j]);
            }
        }

        vector<int> newCol;
        int k = 0;
        while (k < temp.size()) {
            if (k + 1 < temp.size() && temp[k] == temp[k + 1]) {
                newCol.push_back(temp[k] * 2);
                k += 2;
            }
            else {
                newCol.push_back(temp[k]);
                k++;
            }
        }

        while (newCol.size() < 4) {
            newCol.push_back(0);
        }

        for (int i = 0; i < 4; i++) {
            board[i][j] = newCol[i];
        }
    }
}

void moveDown() {
    for (int j = 0; j < 4; j++) {
        vector<int> temp;

        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                temp.push_back(board[i][j]);
            }
        }

        vector<int> newCol;
        int k = 0;
        while (k < temp.size()) {
            if (k + 1 < temp.size() && temp[k] == temp[k + 1]) {
                newCol.push_back(temp[k] * 2);
                k += 2;
            }
            else {
                newCol.push_back(temp[k]);
                k++;
            }
        }

        while (newCol.size() < 4) {
            newCol.push_back(0);
        }

        for (int i = 0; i < 4; i++) {
            board[3 - i][j] = newCol[i];
        }
    }
}

bool checkGameOver() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                return false;
            }

            if (j < 3 && board[i][j] == board[i][j + 1]) {
                return false;
            }

            if (i < 3 && board[i][j] == board[i + 1][j]) {
                return false;
            }
        }
    }

    return true;
}
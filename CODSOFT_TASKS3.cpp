#include <iostream>
#include <vector>
#include <limits>
#include <cctype>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;   
    char currentPlayer;           
    int movesMade;

public:
    TicTacToe() { reset(); }

    void reset() {
        board.assign(3, vector<char>(3, ' '));
        currentPlayer = 'X';
        movesMade = 0;
    }

    void display() const {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << "  ";
            for (int j = 0; j < 3; j++) {
                char c = board[i][j] == ' ' ? char('1' + i * 3 + j) : board[i][j];
                cout << c;
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << " ---+---+---\n";
        }
        cout << "\n";
    }

    int getMove() const {
        int move;
        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            if (!(cin >> move)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (move < 1 || move > 9) {
                cout << "Move must be between 1 and 9.\n";
                continue;
            }
            int r = (move - 1) / 3, c = (move - 1) % 3;
            if (board[r][c] != ' ') {
                cout << "That cell is already taken. Try again.\n";
                continue;
            }
            return move;
        }
    }

    void makeMove(int move) {
        int r = (move - 1) / 3, c = (move - 1) % 3;
        board[r][c] = currentPlayer;
        movesMade++;
    }

    bool checkWin() const {
        char p = currentPlayer;
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == p && board[i][1] == p && board[i][2] == p) return true;  
            if (board[0][i] == p && board[1][i] == p && board[2][i] == p) return true; 
        }
        if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return true;     
        if (board[0][2] == p && board[1][1] == p && board[2][0] == p) return true;     
        return false;
    }

    bool checkDraw() const { return movesMade == 9; }

    void switchPlayer() { currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; }

    char getCurrentPlayer() const { return currentPlayer; }

    void play() {
        reset();
        cout << "\n=== TIC-TAC-TOE ===\nPlayer X goes first.\n";
        while (true) {
            display();                
            int move = getMove();
            makeMove(move);

            if (checkWin()) {
                display();
                cout << "Result: Player " << currentPlayer << " wins!\n";
                break;
            }
            if (checkDraw()) {
                display();
                cout << "Result: It's a draw!\n";
                break;
            }
            switchPlayer();
            cout << "Result: Game ongoing...\n";
        }
    }
};

bool playAgain() {
    char ans;
    while (true) {
        cout << "\nPlay again? (y/n): ";
        cin >> ans;
        ans = tolower(ans);
        if (ans == 'y') return true;
        if (ans == 'n') return false;
        cout << "Please enter 'y' or 'n'.\n";
    }
}

int main() {
    TicTacToe game;
    do {
        game.play();
    } while (playAgain());

    cout << "Thanks for playing!\n";
    return 0;
}

#include "Game.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
using namespace std;

// Function to clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ___________Score Class
Score::Score() { score = 0; }
void Score::addPoint() { score++; }
void Score::loss() { score--; }
int Score::getScore() { return score; }
void Score::reset() { score = 0; }

// _____________User Class
void User::setCredentials(string u, string p) {
    username = u;
    password = p;
}

string User::getUsername() const {
    return username;
}

bool User::userExists(string usernameToCheck) {
    ifstream fin("users.txt");
    string user, pass;
    while (fin >> user >> pass) {
        if (user == usernameToCheck) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}
// User Signup
void User::signup() {
    string user, pass;
    bool duplicate = true;
    while (duplicate) {
        setColor(COLOR_PROMPT);
        cout << "Enter new username: ";
        setColor(COLOR_DEFAULT);
        cin >> user;
        if (userExists(user)) {
            setColor(COLOR_ERROR);
            cout << "Username already exists. Please choose another.\n";
        } else {
            duplicate = false;
        }
    }
    setColor(COLOR_PROMPT);
    cout << "Enter new password: ";
    setColor(COLOR_DEFAULT);
    cin >> pass;
    ofstream fout("users.txt", ios::app);
    fout << user << " " << pass << endl;
    fout.close();
    setColor(COLOR_SUCCESS);
    cout << "Signup successful! You can now log in.\n";
    setColor(COLOR_DEFAULT);
}

//User Login
bool User::login() {
    string user, password;
    char ch;
    setColor(COLOR_PROMPT);
    cout << "Enter username: ";
    setColor(COLOR_DEFAULT);
    cin >> user;
    setColor(COLOR_PROMPT);
    cout << "Enter password: ";
    setColor(COLOR_DEFAULT);
    while ((ch = _getch()) != 13) {
        if (ch == 8 && !password.empty()) {
            password.pop_back();
            cout << "\b \b";
        } else {
            password += ch;
            cout << '*';
        }
    }

    ifstream fin("users.txt");
    string fileUser, filePass;
    while (fin >> fileUser >> filePass) {
        if (user == fileUser && password == filePass) {
            setCredentials(user, password);
            fin.close();
            setColor(COLOR_SUCCESS);
            cout << "\nLogin successful. Welcome, " << user << "!\n";
            setColor(COLOR_DEFAULT);
            return true;
        }
    }
    fin.close();
    setColor(COLOR_ERROR);
    cout << "\nLogin failed.\n";
    setColor(COLOR_DEFAULT);
    return false;
}

// _____________Developer Class

void Developer::listUsers() {
    ifstream file("users.txt");
    string u, p;
    setColor(COLOR_HEADER);
    cout << "Registered Users:\n";
    setColor(COLOR_DEFAULT);
    int i = 0;
    while (file >> u >> p) {
        cout << i + 1 << ". " << u << endl;
        i++;
    }
    file.close();
}

void Developer::deleteUser(const string& targetUser) {
    ifstream file("users.txt");
    ofstream temp("temp.txt");
    string u, p;
    while (file >> u >> p) {
        if (u != targetUser) {
            temp << u << " " << p << endl;
        }
    }
    file.close();
    temp.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
    setColor(COLOR_SUCCESS);
    cout << "User deleted if existed.\n";
    setColor(COLOR_DEFAULT);
}

// _____________RockPaperScissors

string RockPaperScissors::getComputerChoice() {
    string choices[] = {"rock", "paper", "scissors"};
    return choices[rand() % 3];
}

string RockPaperScissors::toLower(string str) {
    for (char &c : str)
        c = tolower(c);
    return str;
}

void RockPaperScissors::play() {
    clearScreen();
    setColor(COLOR_HEADER);
    cout << "\n--- Rock Paper Scissors ---\n";
    setColor(COLOR_DEFAULT);
    playerScore.reset();
    string playerChoice, computerChoice;
    char choice = 'y';

    while (choice == 'y' || choice == 'Y') {
        clearScreen();
        setColor(COLOR_PROMPT);
        cout << " - Enter rock, paper or scissors: ";
        setColor(COLOR_DEFAULT);
        cin >> playerChoice;
        
        
        setColor(COLOR_DEFAULT);
        playerChoice = toLower(playerChoice);
        computerChoice = getComputerChoice();
        setColor(COLOR_PROMPT);
        cout << "Computer chose: "; 
		setColor(COLOR_DEV); 
		cout <<  computerChoice << endl;

        if (playerChoice == computerChoice) {
            setColor(COLOR_HEADER);
            cout << "Draw!\n";
        } else if ((playerChoice == "rock" && computerChoice == "scissors") ||
                   (playerChoice == "paper" && computerChoice == "rock") ||
                   (playerChoice == "scissors" && computerChoice == "paper")) {
            setColor(COLOR_SUCCESS);
            cout << "You win!\n";
            playerScore.addPoint();
        } else {
            setColor(COLOR_ERROR);
            cout << "Computer Wins!\n";
        }
        setColor(COLOR_PROMPT);
        cout << "Wanna Play Again? (Y/N): ";
        setColor(COLOR_DEFAULT);
        cin >> choice;
    }
	setColor(COLOR_SUCCESS);
    cout << "Your score: " << playerScore.getScore() << "\n";
}

// _____________TicTacToe

void TicTacToe::initializeBoard() {
    char ch = '1';
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ch++;
}

void TicTacToe::printBoard() {
	setColor(COLOR_DEV);
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << "\n";
        if (i < 2)
            cout << "---|---|---\n";
    }
    setColor(COLOR_DEFAULT);
}

bool TicTacToe::isWinner(char player) {
    for (int i = 0; i < 3; ++i)
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;

    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool TicTacToe::isDraw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

bool TicTacToe::makeMove(int position, char player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    if (position < 1 || position > 9 || board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    board[row][col] = player;
    return true;
}

int TicTacToe::minimax(bool isMax) {
    if (isWinner('O')) return 1;
    if (isWinner('X')) return -1;
    if (isDraw()) return 0;

    int best = isMax ? -1000 : 1000;

    for (int i = 1; i <= 9; ++i) {
        int row = (i - 1) / 3, col = (i - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            char backup = board[row][col];
            board[row][col] = isMax ? 'O' : 'X';
            int score = minimax(!isMax);
            board[row][col] = backup;
            best = isMax ? max(best, score) : min(best, score);
        }
    }
    return best;
}

int TicTacToe::findBestMove() {
    int bestVal = -1000, bestMove = -1;

    for (int i = 1; i <= 9; ++i) {
        int row = (i - 1) / 3, col = (i - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            char backup = board[row][col];
            board[row][col] = 'O';
            int moveVal = minimax(false);
            board[row][col] = backup;
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

void TicTacToe::play() {
    char playAgain;
    do {
        clearScreen();
        setColor(COLOR_HEADER);
        cout << "\n--- Tic Tac Toe ---\n";
        setColor(COLOR_DEFAULT);
        cout << "Select Mode:\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        setColor(COLOR_PROMPT);
        cout << "Choice: ";
        setColor(COLOR_DEFAULT);
        cin >> mode;
        initializeBoard();
        currentPlayer = 'X';

        while (true) {
            clearScreen();
            printBoard();
            int move;

            if (mode == 1 || (mode == 2 && currentPlayer == 'X')) {
                cout << "Player " << currentPlayer << ", enter move (1-9): ";
                cin >> move;
                if (!makeMove(move, currentPlayer)) {
                    setColor(COLOR_ERROR);
                    cout << "Invalid move. Try again.\n";
                    setColor(COLOR_DEFAULT);
                    cin.ignore();
                    cin.get();
                    continue;
                }
            } else {
                cout << "Computer (O) is making a move...\n";
                move = findBestMove();
                makeMove(move, 'O');
            }

            if (isWinner(currentPlayer)) {
                clearScreen();
                printBoard();
                setColor(COLOR_SUCCESS);
                cout << "Player " << currentPlayer << " wins!\n";
                setColor(COLOR_DEFAULT);
                break;
            }

            if (isDraw()) {
                clearScreen();
                printBoard();
                setColor(COLOR_HEADER);
                cout << "It's a draw!\n";
                setColor(COLOR_DEFAULT);
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        cout << "Wanna play again? (Y/N): ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
}

	//____________Race to 100
	
void RaceTo100::play() {
    clearScreen();
    setColor(COLOR_HEADER);
    cout << "\n=== Race to 100 Game ===\n";
    setColor(COLOR_DEFAULT);
    int total = 0;
    bool playerTurn = true;
    bool gameEnded = false;

    while (!gameEnded) {
        clearScreen();
        setColor(COLOR_PROMPT);
        cout << "Your goal is to reach exactly 100.\n";
        setColor(COLOR_DEFAULT);

        if (playerTurn) {
            int add;
            setColor(COLOR_PROMPT);
            cout << "Your turn! Choose a number to add (1-10): ";
            setColor(COLOR_DEFAULT);
            cin >> add;

            if (add < 1 || add > 10) {
                setColor(COLOR_ERROR);
                cout << "Invalid input. Please enter a number between 1 and 10.\n";
                setColor(COLOR_DEFAULT);
                continue;
            }

            if (total + add > 100) {
                setColor(COLOR_ERROR);
                cout << "That would exceed 100. You lose your turn!\n";
                setColor(COLOR_DEFAULT);
            } else {
                total += add;
            }
        } else {
            int compAdd = rand() % 10 + 1;
            if (total + compAdd > 100) {
                setColor(COLOR_HEADER);
                cout << "Computer loses its turn!\n";
            } else {
                total += compAdd;
                setColor(COLOR_PROMPT);
                cout << "Computer added: " << compAdd << endl;
            }
            setColor(COLOR_DEFAULT);
        }

        if (total == 100) {
            if (playerTurn) {
                setColor(COLOR_SUCCESS);
                cout << "Congratulations, you reached 100 first and win!\n";
            } else {
                setColor(COLOR_ERROR);
                cout << "Computer reached 100 first and wins!\n";
            }
            setColor(COLOR_DEFAULT);
            gameEnded = true;
        }

        playerTurn = !playerTurn;
        cout << "Press Enter to continue...\n";
        cin.ignore();
        cin.get();
    }
}

	//____________Number Gusseing Game

void NumberGuessing::play() {
    clearScreen();
    setColor(COLOR_HEADER);
    cout << "=== Number Guessing Game ===\n";
    setColor(COLOR_DEFAULT);
    int number, guess, choice, attempts, range;
    char playAgain;
    srand(time(0));

    do {
        while (true) {
            setColor(COLOR_PROMPT);
            cout << "Choose Difficulty Level\n";
            cout << " 1. Easy \n 2. Normal \n 3. Hard \n 4. Custom\n";
            cout << "Enter your Choice: ";
            setColor(COLOR_DEFAULT);
            cin >> choice;

            if (choice == 1)
                range = 10;
            else if (choice == 2)
                range = 100;
            else if (choice == 3)
                range = 1000;
            else if (choice == 4) {
                setColor(COLOR_PROMPT);
                cout << "Enter the range for the number: ";
                setColor(COLOR_DEFAULT);
                cin >> range;
            } else {
                setColor(COLOR_ERROR);
                cout << "Invalid choice, please try again.\n";
                setColor(COLOR_DEFAULT);
                continue;
            }
            break;
        }

        number = rand() % range + 1;
        attempts = 0;

        setColor(COLOR_PROMPT);
        cout << "Try to guess the number between 1 and " << range << "!\n";
        setColor(COLOR_DEFAULT);

        do {
            setColor(COLOR_PROMPT);
            cout << "Enter your guess: ";
            setColor(COLOR_DEFAULT);
            cin >> guess;
            attempts++;

            if (guess < number) {
                setColor(COLOR_ERROR);
                cout << "Too low! Try again.\n";
            } else if (guess > number) {
                setColor(COLOR_ERROR);
                cout << "Too high! Try again.\n";
            } else {
                setColor(COLOR_SUCCESS);
                cout << "Congratulations! You guessed the number in " << attempts << " attempts.\n";
                break;
            }
            setColor(COLOR_DEFAULT);
        } while (true);

        setColor(COLOR_PROMPT);
        cout << "Would you like to play again? (y/n): ";
        setColor(COLOR_DEFAULT);
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    setColor(COLOR_SUCCESS);
    cout << "Thanks for playing!\n";
    setColor(COLOR_DEFAULT);
}


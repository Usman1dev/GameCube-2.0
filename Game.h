#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

const int COLOR_DEV   = 14;  // Yellow
const int COLOR_PROMPT   = 11;  // Light Cyan
const int COLOR_SUCCESS  = 10;  // Light Green
const int COLOR_ERROR    = 12;  // Light Red
const int COLOR_DEFAULT  = 15;  // White / Default
const int COLOR_HEADER      = 13;  // Light Magenta

inline void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

// Score class
class Score {
private:
    int score;
public:
    Score();           
    void addPoint();
    void loss();
    int getScore();
    void reset();
};

// User class
class User {
private:
    string username;
    string password;
public:
    void setCredentials(string u, string p);
    string getUsername() const;
    bool userExists(string usernameToCheck);
    void signup();
    bool login();
};

// Developer class
class Developer : public User {
public:
    void listUsers();
    void deleteUser(const string& targetUser);
};

// Abstract Game class
class Game {
public:
    virtual void play() = 0;
    virtual ~Game() {}
};

// RockPaperScissors
class RockPaperScissors : public Game {
private:
    string getComputerChoice();
    string toLower(string str);
    Score playerScore;
public:
    void play() override;
};

// TicTacToe
class TicTacToe : public Game {
private:
    char board[3][3];
    char currentPlayer;
    int mode;
    void initializeBoard();
    void printBoard();
    bool isWinner(char player);
    bool isDraw();
    bool makeMove(int position, char player);
    int minimax(bool isMax);
    int findBestMove();
public:
    void play() override;
};

// RaceTo100
class RaceTo100 : public Game {
public:
    void play() override;
};

// NumberGuessing
class NumberGuessing : public Game {
public:
    void play() override;
};

#endif

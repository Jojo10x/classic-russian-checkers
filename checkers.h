#ifndef CHECKERS_H
#define CHECKERS_H

#include <vector>
#include <string>
#include <utility>
#include <mutex>  

const int SIZE = 8;
extern std::mutex mtx; 

class Checkers {
public:
    Checkers();
    void initializeBoard();
    void printBoard();
    bool isValidMove(int x1, int y1, int x2, int y2, char player);
    void makeMove(int x1, int y1, int x2, int y2, char player);
    std::vector<std::pair<int, int> > getPossibleMoves(char player);
    std::vector<std::pair<int, int> > getMandatoryCaptures(char player);
    void computerMove(char player);
    bool hasValidMoves(char player);
    bool gameOver();
    std::vector<std::vector<char> >& getBoard();

private:
    std::vector<std::vector<char> > board;
};

void playerTurn(Checkers& game, char player);
void computerTurn(Checkers& game, char player);

#endif
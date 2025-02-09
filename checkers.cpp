#include "checkers.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <cctype>

std::mutex mtx; 

Checkers::Checkers() {
    board.resize(SIZE, std::vector<char>(SIZE, ' '));
    initializeBoard();
}

void Checkers::initializeBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((i + j) % 2 != 0) {
                if (i < 3) board[i][j] = 'B';
                else if (i > 4) board[i][j] = 'W';
            }
        }
    }
}

void Checkers::printBoard() {
    std::cout << "  A B C D E F G H" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Checkers::isValidMove(int x1, int y1, int x2, int y2, char player) {
    if (x2 < 0 || x2 >= SIZE || y2 < 0 || y2 >= SIZE) return false;
    if (board[x2][y2] != ' ') return false;

    char piece = board[x1][y1];
    if (piece != player && piece != toupper(player)) return false;

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) == 1 && abs(dy) == 1) {
        if (piece == 'W' && dx == -1) return true;
        if (piece == 'B' && dx == 1) return true;
        if (piece == 'X' || piece == 'Y') return true;
    }

    if (abs(dx) == 2 && abs(dy) == 2) {
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        char midPiece = board[midX][midY];
        if (midPiece != ' ' && midPiece != player && midPiece != toupper(player)) {
            return true;
        }
    }

    return false;
}

void Checkers::makeMove(int x1, int y1, int x2, int y2, char player) {
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = ' ';

    if (abs(x2 - x1) == 2) {
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        board[midX][midY] = ' ';
    }

    if (player == 'W' && x2 == 0) board[x2][y2] = 'X';
    if (player == 'B' && x2 == SIZE - 1) board[x2][y2] = 'Y';
}

std::vector<std::pair<int, int> > Checkers::getPossibleMoves(char player) {
    std::vector<std::pair<int, int> > moves;
    std::vector<std::thread> threads;
    int numThreads = std::thread::hardware_concurrency();
    int rowsPerThread = SIZE / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? SIZE : startRow + rowsPerThread;
        threads.push_back(std::thread([this, &moves, player, startRow, endRow]() {
            for (int i = startRow; i < endRow; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (board[i][j] == player || board[i][j] == toupper(player)) {
                        for (int dx = -2; dx <= 2; ++dx) {
                            for (int dy = -2; dy <= 2; ++dy) {
                                if (isValidMove(i, j, i + dx, j + dy, player)) {
                                    mtx.lock();
                                    moves.push_back(std::make_pair(i, j));
                                    mtx.unlock();
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }));
    }

    for (size_t i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }

    return moves;
}

std::vector<std::pair<int, int> > Checkers::getMandatoryCaptures(char player) {
    std::vector<std::pair<int, int> > captures;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == player || board[i][j] == toupper(player)) {
                for (int dx = -2; dx <= 2; ++dx) {
                    for (int dy = -2; dy <= 2; ++dy) {
                        if (abs(dx) == 2 && abs(dy) == 2 && isValidMove(i, j, i + dx, j + dy, player)) {
                            captures.push_back(std::make_pair(i, j));
                            break;
                        }
                    }
                }
            }
        }
    }
    return captures;
}

void Checkers::computerMove(char player) {
    std::vector<std::pair<int, int> > moves = getPossibleMoves(player);
    if (!moves.empty()) {
        int idx = rand() % moves.size();
        std::pair<int, int> move = moves[idx];
        int x1 = move.first, y1 = move.second;
        int x2 = x1 + (rand() % 3 - 1) * 2;
        int y2 = y1 + (rand() % 3 - 1) * 2;
        if (isValidMove(x1, y1, x2, y2, player)) {
            makeMove(x1, y1, x2, y2, player);
        }
    }
}

bool Checkers::hasValidMoves(char player) {
    return !getPossibleMoves(player).empty();
}

bool Checkers::gameOver() {
    return !hasValidMoves('W') || !hasValidMoves('B');
}

std::vector<std::vector<char> >& Checkers::getBoard() {
    return board;
}
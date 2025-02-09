#include "checkers.h"
#include <iostream>

int main() {
    Checkers game;
    char player;
    std::cout << "Choose your side (W/B): ";
    std::cin >> player;
    player = toupper(player);

    if (player == 'W') {
        while (!game.gameOver()) {
            game.printBoard();
            playerTurn(game, player);
            game.printBoard();
            computerTurn(game, 'B');
        }
    } else {
        while (!game.gameOver()) {
            computerTurn(game, 'W');
            game.printBoard();
            playerTurn(game, player);
            game.printBoard();
        }
    }

    std::cout << "Game over!" << std::endl;
    return 0;
}
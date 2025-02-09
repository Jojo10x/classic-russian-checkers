#include "checkers.h"
#include <iostream>
#include <string>

void playerTurn(Checkers& game, char player) {
    std::string move;
    std::vector<std::pair<int, int> > captures = game.getMandatoryCaptures(player);

    if (!captures.empty()) {
        std::cout << "You must capture!" << std::endl;
    }

    std::cout << "Your move: ";
    std::cin >> move;

    if (move.size() < 5) {
        std::cout << "Invalid move format. Use format A1-B2." << std::endl;
        return playerTurn(game, player);
    }

    int x1 = move[1] - '1';
    int y1 = toupper(move[0]) - 'A';
    int x2 = move[4] - '1';
    int y2 = toupper(move[3]) - 'A';

    if (x1 < 0 || x1 >= SIZE || y1 < 0 || y1 >= SIZE || x2 < 0 || x2 >= SIZE || y2 < 0 || y2 >= SIZE) {
        std::cout << "Move out of bounds. Try again." << std::endl;
        return playerTurn(game, player);
    }

    if (!captures.empty()) {
        bool isCaptureMove = (abs(x1 - x2) == 2 && abs(y1 - y2) == 2);
        if (!isCaptureMove) {
            std::cout << "You must capture! Try again." << std::endl;
            return playerTurn(game, player);
        }
    }

    if (game.isValidMove(x1, y1, x2, y2, player)) {
        game.makeMove(x1, y1, x2, y2, player);
    } else {
        std::cout << "Invalid move. Try again." << std::endl;
        playerTurn(game, player);
    }
}
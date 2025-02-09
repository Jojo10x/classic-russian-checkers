# Checkers Game (C++)

This is a C++ program that implements a classic (Russian) checkers game, allowing the user to play against the computer. The program follows the standard rules of checkers, supports forced captures, and utilizes a parallel algorithm for improved performance.

## Features

- Classic checkers rules (regular moves, king moves, capturing opponent's pieces).
- User can choose to play as white or black.
- Parallel algorithm implemented with multithreading to improve performance.
- Draw condition if no progress is made in 15 moves.
- Clear text-based game board interface in the console.
- Written in C++ (C++17 or higher).

## Game Rules

- The game follows the classic Russian checkers rules: regular moves, king moves, and forced captures.
- The board is 10x10, and players can make moves in the format `A6 B5`, where the first part is the starting position and the second is the target position.
- White pieces are represented by `W` and black pieces by `B`. Kings are denoted by `X` for white and `Y` for black.
- The game ends in a draw if no progress is made (i.e., no captures or piece promotions) in 15 moves.

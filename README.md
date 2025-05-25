# Chess-in-CPP

A graphical Chess game built using *C++* and the *SplashKit* library.

## Game Features

- Graphical chess board and pieces perfectly aligned using SplashKit
- Correct algorithms for:
  - Pawn
  - Rook
  - Knight
  - Bishop
  - Queen
  - King
- Turn-based play: White and Black alternate turns
- Player Timers
- Random chess quotes display on the right side of the screen.
- Warning messages to alert about check/checkmates.

- # COMING SOON!
    - AI opponent
    - Animations
    - Restart Button
    - Sound Effects
    - Highlighting selected piece
    - Marking legal moves of a piece

### Requirements

- C++ compiler (g++, clang)
- [SplashKit](https://www.splashkit.io/)
- Git (for cloning)

### Setup

# bash
git clone https://github.com/KrishAtGit/Chess-in-CPP.git
cd Chess-in-CPP
g++ *.cpp -o chess_game -l SplashKit
./chess_game

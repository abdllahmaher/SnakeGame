# Snake Game

## Description

Snake Game is a classic console-based game developed in C++ utilizing Windows-specific libraries for sound effects, screen rendering, and input handling. The objective of the game is to control the snake to eat food and grow longer while avoiding collisions with the walls (if enabled) and the snake's own body. The game features multiple difficulty levels, movement modes, and bonus items like golden fruit for additional points and length.

This version of the game allows for both manual and automatic movement modes, different difficulty levels, and wall modes. The game also includes sound effects to enhance the player's experience and a high-score system to track the best performance.

## Features

- **Multiple Difficulty Levels**:
  - Easy, Medium, and Hard modes.
- **Movement Modes**:
  - **Automove**: Snake moves automatically in the last pressed direction.
  - **Manual Move**: Player controls the snake using keyboard input.
- **Wall Mode**: Play with or without walls.
- **Golden Fruits**: Occasionally appears on the screen, rewarding extra points and increasing the snake's length.
- **Sound Effects**: Includes sound effects for the game intro, eating food, and game over.
- **High Score Tracking**: Keeps track of the player's highest score and updates it when necessary.

## Installation

To run the Snake Game, you need to have a C++ compiler installed. The game uses Windows-specific libraries, so it is recommended to run it on a Windows machine.

### Prerequisites

- **C++ Compiler**: You can use a C++ compiler like **GCC** or **Microsoft Visual Studio**.
- **Windows OS**: The game uses `windows.h` for console manipulation and sound effects.

### Steps to Install

1. **Clone the repository**:
   - Download the game files by cloning this repository.
   - If you're using Git, you can clone it using the following command:
     ```bash
     git clone https://github.com/abdllahmaher/SnakeGame.git
     ```

2. **Setup the C++ project**:
   - Open the project in your preferred IDE or text editor (e.g., **Visual Studio**, **Code::Blocks**, or **Visual Studio Code**).
   - Make sure your IDE supports Windows API (since `windows.h` is required).

3. **Compile the Code**:
   - Open a terminal or command prompt in the project's root directory.
   - If you’re using **GCC**, run the following command:
     ```bash
     g++ -o snake_game main.cpp -lwinmm
     ```
   - For **Visual Studio**, create a new console application project, add the `main.cpp` file, and build the project.

4. **Ensure sound files are present**:
   - The game requires `intro.wav`, `eat.wav`, and `gameover.wav` for sound effects. Ensure these `.wav` files are in the same directory as the game executable.

5. **Run the Game**:
   - Once the project is compiled, navigate to the folder containing the executable file (e.g., `snake_game.exe`).
   - Open a command prompt or terminal and run:
     ```bash
     snake_game.exe
     ```

## How to Play

1. **Start Screen**: After starting the game, you'll see an intro screen. Press any key to proceed to the game.
2. **Select Movement Mode**: Choose between **Automove** (snake moves automatically) or **Manual Move** (control the snake with your keyboard).
3. **Select Wall Mode**: Choose if the snake should interact with walls. In **No Wall Mode**, the snake wraps around the screen edges.
4. **Choose Difficulty**: Select a difficulty level:
   - **Level 1**: Easy
   - **Level 2**: Medium
   - **Level 3**: Hard
5. **Gameplay**:
   - **W, A, S, D** or **Arrow Keys** to control the snake's movement.
   - **'X'** to immediately end the game.
6. **Game Over**: The game ends if the snake runs into itself or the walls (depending on the wall mode). After the game ends, your score will be displayed, and you will be prompted to replay or exit.

## Controls

- **Arrow Keys** or **WASD** to control the snake:
  - `W` or Up Arrow to move up.
  - `S` or Down Arrow to move down.
  - `A` or Left Arrow to move left.
  - `D` or Right Arrow to move right.
- **'X'** to end the game.
- Press **'R'** after Game Over to replay, or any other key to exit.



Enjoy playing the Snake Game! ??

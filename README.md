# Snake Game

 **Improved Version of the Classic Game**

## Features

- **Customizable Gameplay**:
  - Choose between manual and auto-movement modes.
  - Enable or disable walls.
  - AI-controlled snake that competes for fruit.
  - Golden fruit for bonus points.

- **Dynamic Levels**:
  - Difficulty increases as time progresses.
  - Easy and Hard modes available.

- **Sound Effects**:
  - Includes eat, game over, and intro sound effects.

- **Menu System**:
  - Start Screen with animations.
  - Pause Menu to toggle settings during gameplay.
  - Game Over Screen with high score tracking.

## Installation and Compilation

1. **Requirements**:
   - A C++ compiler (e.g., GCC, MSVC).
   - Windows operating system (for `windows.h` and `mmsystem.h` dependencies).

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/abdllahmaher/SnakeGame.git
   cd SnakeGame
   ```

3. **Compile the Code**:
   Use a C++ compiler to compile the project:
   ```bash
   g++ -o SnakeGame main.cpp -lwinmm
   ```

4. **Run the Game**:
   ```bash
   ./SnakeGame
   ```

## How to Play

1. **Game Start**:
   - Run the game to see the start screen.
   - Press any key to proceed to the main menu.

2. **Menu Options**:
   - Navigate using the arrow keys and select with `Enter`.
   - Customize game settings before starting.

3. **Gameplay**:
   - Use the arrow keys to control the snake.
   - Collect fruit (`@`) to grow and increase your score.
   - Avoid collision with walls (if enabled), your own tail, or the AI snake.
   - Collect golden fruit (`$`) for bonus points.

4. **Pause Menu**:
   - Press `p` during the game to access the Pause Menu.

5. **Game Over**:
   - View your score and high score.
   - Press `r` to replay or any other key to exit.

## Developer Notes

- **Golden Fruit**:
  - Rare fruit that appears randomly and gives extra rewards.
  - Avoid missing it, as it disappears after a short time.

- **AI Snake**:
  - The AI snake competes for the same fruit as the player.
  - Increases the challenge significantly.

- **Wall Mode**:
  - "No Walls" mode allows the snake to pass through the screen edges.
  - "With Walls" mode ends the game if the snake hits the boundary.
Enjoy the game and happy coding!

# Pong Clone (SDL3 & C++)

## Description
This is a simple Pong clone developed using **SDL3** and **C++**. It replicates the classic Pong gameplay, where two paddles hit a ball back and forth, aiming to score against the opponent.

## Features
- **Single-player**
- **Smooth paddle movement** using keyboard controls
- **Basic AI opponent** in single-player mode
- **Customizable game settings** (ball speed, paddle speed, etc.) via code

## Requirements
To run this game, you need:
- **C++ Compiler** (GCC, Clang, or MSVC recommended)
- **SDL3 Library** (installed via package manager or manually)
- **CMake** (optional, for easier building)

## Installation & Compilation

### Linux / macOS
1. Install SDL3:
   ```sh
   sudo apt install libsdl3-dev  # Debian/Ubuntu
   brew install sdl3  # macOS (using Homebrew)
   ```
2. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/Pong-SDL3.git
   cd Pong-SDL3
   ```
3. Compile the game:
   ```sh
   g++ -std=c++17 src/*.cpp -o pong -lSDL3
   ```
4. Run the game:
   ```sh
   ./pong
   ```

### Windows (MinGW / MSVC)
1. Download and install SDL3 from [SDL's official site](https://github.com/libsdl-org/SDL).
2. Clone the repository and navigate to the project folder:
   ```sh
   git clone https://github.com/yourusername/Pong-SDL3.git
   cd Pong-SDL3
   ```
3. Compile using MinGW:
   ```sh
   g++ -std=c++17 src/*.cpp -o pong.exe -lSDL3
   ```
   Or using MSVC:
   ```sh
   cl /std:c++17 /EHsc /I "SDL3/include" /link SDL3.lib src/*.cpp /OUT:pong.exe
   ```
4. Run the game:
   ```sh
   pong.exe
   ```

## Controls
- **Player 1 (Left Paddle)**: `W` (Up), `S` (Down)
- **Player 2 (Right Paddle)**: `Up Arrow` (Up), `Down Arrow` (Down)
- **Pause/Resume**: `Space`
- **Quit**: `Esc`

## Game Rules
- Players control paddles to prevent the ball from passing them.
- The ball bounces off the walls and paddles.
- A player scores when the ball passes the opponent’s side.
- The first to reach the winning score (default: 10) wins the match.

## Customization
You can modify game settings in the `config.h` file:
```cpp
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BALL_SPEED 5
#define PADDLE_SPEED 7
#define WINNING_SCORE 10
```

## License
This project is licensed under the **MIT License**.

## Contributions
Feel free to contribute by submitting pull requests or reporting issues!

## Contact
For any inquiries, reach out at **your-email@example.com** or open an issue on GitHub.

---
Enjoy playing Pong! 🎮


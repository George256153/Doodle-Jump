# Doodle Jump Game Implementation

## Introduction

This project is a custom implementation of the popular game **Doodle Jump**. The player controls a character (Doodle) that jumps automatically and navigates an endless series of platforms, dodging obstacles and collecting items to boost their performance. The main objective is to achieve the highest possible score by ascending as high as possible without falling or losing all health points.

## Game Features

1. **Core Mechanics:**
   - Doodle automatically jumps upon landing on a platform.
   - The jumping process includes:
     - Ascending to a maximum height of 320 pixels.
     - Ignoring platforms while ascending.
     - Falling back to land on a new platform.

2. **Player Controls:**
   - Move Doodle left or right using the keyboard.
   - Fire bullets to eliminate monsters using the mouse.

3. **Platform Types:**
   - Normal platforms for jumping.
   - Broken platforms that break upon contact.
   - Moving platforms that shift left or right.
   - Disappearing platforms that vanish after a single use.

4. **Item Effects:**
   - **Spring:** Boosts jump height to 960 pixels.
   - **Trampoline:** Boosts jump height to 1920 pixels.
   - **Propeller Hat:** Flies to 3840 pixels.
   - **Jet Pack:** Flies to 7680 pixels.

5. **Obstacles:**
   - Monsters block the path; touching them causes health loss.
   - Doodle can eliminate monsters by:
     - Jumping on their heads.
     - Shooting bullets.

6. **Advanced Features:**
   - Wrapping around the screen edges.
   - Dynamic camera following Doodle's movement.
   - Sound effects for jumping and shooting.

## Winning Conditions
- The game ends when:
  1. Doodle falls below the screen.
  2. Doodle loses all health points.
- Score is calculated based on the maximum height reached.

## How to Play
- Control the Doodle using the keyboard for movement and the mouse for aiming/shooting.
- Collect items to enhance jump height and avoid obstacles.
- Survive as long as possible to achieve a higher score.

## Additional Features
- Two-player mode:
  - Players compete to avoid falling off the screen.
  - The game view follows the player with the highest score.

## Game Description

The game features two modes: single-player mode and multiplayer mode. After entering the main screen, clicking "Play" will start the single-player mode, while clicking "Multiplayer" will launch the multiplayer mode. 

- In **single-player mode**, the game ends when the player's HP reaches zero or the Doodle touches the bottom of the screen.
- In **multiplayer mode**, there are no items or monsters. The game ends when one of the Doodles touches the bottom of the screen.

## Controls

- **Single-player Mode:**  
  Use the left and right arrow keys on the keyboard to move the Doodle and use the mouse to aim and shoot bullets.

- **Multiplayer Mode:**  
  - Player 1 (Yellow Doodle): Use the left and right arrow keys to control movement.
  - Player 2 (Blue Doodle): Use the "A" (left) and "D" (right) keys to control movement.

- To **pause** the game, press the `Esc` key. Then, click "Resume" to continue the game or "Menu" to return to the main screen.

- When the game is over, click "Menu" to return to the main screen.


## How to execute
### Terminal 1
1. Navigate to the project directory
2. Generate the Makefile using qmake
   ```bash
   qmake-qt5
3. Compile the project
    ```bash
   make
### Terminal 2 
1. Start the X Window System
    ```bash
   startxwin
### Go to cygwin Folder
1. Run /bin/pulseaudio.exe
### Back to Terminal 1
1. Set the display environment variable
   ```bash
   export DISPLAY=:0.0
2. Run the Big Two game executable
   ```bash
   ./big_two

Explore the world of **Doodle Jump** with this fun and challenging project!

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

## Technical Information
- **Screen Resolution:** 540 x 960 pixels.
- **Game Objects:**
  - Platforms: 120 x 30 pixels.
  - Doodle: 80 x 80 pixels.
  - Items: Dimensions vary based on type.

## How to Run
1. Clone this repository to your local machine.
2. Follow the compilation and execution steps in the `README` file to launch the game.

## Future Improvements
- Add more advanced obstacles like black holes.
- Improve item variety and effects.
- Implement online multiplayer functionality.

Explore the world of **Doodle Jump** with this fun and challenging project!

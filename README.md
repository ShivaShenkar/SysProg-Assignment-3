# SysProg-Assignment-3

````

````


Made changes.

Here is a detailed and comprehensive README section for your project, covering all requested categories:

---

# SysProg-Assignment-3

## Overview
This project is a C++ implementation of a turn-based strategy game inspired by Coup, featuring a graphical user interface (GUI) built with SFML. Players assume unique roles, each with special abilities, and interact through actions such as gathering coins, taxing, bribing, arresting, sanctioning, and performing coups. The game supports both GUI and demo/test modes.

## Project Structure
- main.cpp: Entry point for the GUI version.
- makefile: Build instructions for compiling the project.
- demo: Contains Demo.cpp for console-based demonstration.
- include: Header files for all classes (game logic, player roles, GUI, utilities).
- src: Source files for game logic and GUI.
  - `gui/`: All GUI-related source files and the `fonts/` directory.
    - `fonts/`: Required font files (arial.ttf, Gloock-Regular.ttf).
- tests: Unit tests and the doctest.h framework.
- bin: Compiled binaries.

## GUI
- Built with SFML.
- **Main Menu**: Start the game.
- **Player Setup**: Add/remove players, each with a random role.
- **Game Page**: Shows each player’s name, role, coins, and action buttons (based on role). Highlights the current player.
- **Popups**: Informative popups for errors, insufficient coins, and action results.
- **Victory Screen**: Displays the winner and allows returning to the main menu.
- **Fonts**: Loaded from arial.ttf and Gloock-Regular.ttf.  
  **You must update the font file paths in gui.cpp if you move the project or fonts.**

## Class Explanations
- **Game**: Manages players, turn order, and game state.
- **Player**: Abstract base class for all player types. Handles coins, actions, and state.
- **Baron, General, Governor, Judge, Merchant, Spy**: Derived from `Player`, each with unique abilities:
  - *Baron*: Can invest for extra coins.
  - *General*: Can grant coup immunity.
  - *Governor/Judge*: Can undo actions.
  - *Merchant*: Special post-action logic.
  - *Spy*: Can watch coins and cancel arrests.
- **PlayerController**: GUI component for player info and action buttons.
- **PlayerEntry**: GUI component for player setup.
- **Button**: Custom SFML button class.
- **PopupWindow**: Custom popup for messages/errors.
- **GUI**: Manages all GUI logic, screens, and events.

## How to Build the Program
1. **Dependencies**: Install SFML on your system.
2. **Build**:
   - GUI version:  
     `make main`
   - Demo (console):  
     `make demo && ./bin/demo.out`
   - Tests:  
     `make test && ./bin/test.out`
3. **Run the GUI**:  
   main.out

## Important Notes
- **Valgrind**: Running with Valgrind may show many memory errors, especially from SFML/GUI. These are mostly false positives and do not indicate real leaks in the game logic.
- **Fonts**: If you move the project or fonts, update the font file paths in gui.cpp:
  - `mainFont.loadFromFile("src/gui/fonts/arial.ttf")`
  - `titleFont.loadFromFile("src/gui/fonts/Gloock-Regular.ttf")`
- **Linux Compatibility**: Developed and tested on Linux. Ensure SFML libraries are installed.

---

You can copy and paste this into your README.md. If you want this inserted automatically, please let me know once your quota allows file edits again.

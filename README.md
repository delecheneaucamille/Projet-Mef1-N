# 🎴 Projet-Mef1-N 🎲

Welcome to **Projet-Mef1-N**, a console-based card game inspired by the thrilling and strategic gameplay of **Skyjo**! Whether you're a fan of card games or just looking for a fun way to pass the time, this project is designed to provide an exciting and interactive experience for players, featuring both human and AI opponents. Let the fun begin!

---

## 📖 Table of Contents

- [✨ About the Game](#-about-the-game)
- [🚀 Features](#-features)
- [🛠️ Requirements](#️-requirements)
- [📥 Installation](#-installation)
- [🎮 How to Play](#-how-to-play)
- [📂 Project Structure](#-project-structure)
- [📜 License](#-license)
- [💡 Acknowledgments](#-acknowledgments)

---

## ✨ About the Game

**Skyjo** is a card game where players aim to achieve the lowest score by flipping, swapping, and discarding cards. This project brings the magic of Skyjo to your terminal, allowing you to compete against friends or AI opponents in a battle of strategy and luck. Will you emerge victorious with the lowest score? 🏆

---

## 🚀 Features

- 🤖 **Human and AI Players**: Play against your friends or challenge cunning AI opponents.
- 🔄 **Dynamic Gameplay**: Cards are shuffled, distributed, and managed dynamically for a unique experience every time.
- 🎨 **Interactive Console Interface**: Enjoy a clean and colorful console output that keeps you engaged.
- ⚙️ **Customizable Settings**: Adjust the number of players, AI difficulty, and card values to suit your preferences.

---

## 🛠️ Requirements

To run this project, you'll need:

- A C compiler (e.g., GCC).
- A Linux or Windows environment with `make` installed.
- Basic knowledge of how to use the terminal.

---

## 📥 Installation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/your-username/Projet-Mef1-N.git
   cd Projet-Mef1-N
   ```

2. Compile the project using `make`:
   ```bash
   make
   ```

3. Run the game:
   ```bash
   make run
   ```

4. Clean up compiled files when you're done:
   ```bash
   make clean
   ```

---

## 🎮 How to Play

1. Launch the game by running the executable:
   ```bash
   ./main
   ```

2. Follow the on-screen instructions to:
   - 🃏 Start a new game.
   - 💾 Load a saved game (feature coming soon!).
   - 📜 View the rules.
   - ❌ Exit the game.

3. During the game:
   - Flip, swap, or discard cards to achieve the lowest score.
   - Compete against AI or other players in a battle of wits and strategy.

4. The game ends when all cards are flipped or the stack is empty. Scores are calculated, and the player with the lowest score wins! 🎉

---

## 📂 Project Structure

```plaintext
Projet-Mef1-N/
├── sources/               # Source code files
│   ├── main.c             # Entry point of the program
│   ├── game.c             # Game logic
│   ├── player.c           # Player management
│   ├── card.c             # Card and stack management
│   ├── ia.c               # AI logic
│   ├── display.c          # Console display functions
│   ├── menu.c             # Menu management
│   ├── *.h                # Header files
├── includes/              # Header files (optional, if separated)
├── Makefile               # Build system
├── README.md              # Project documentation
├── .gitignore             # Git ignore file
└── .vscode/               # VS Code configuration files
```

---

## 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

## 💡 Acknowledgments

- 🎲 Inspired by the card game **Skyjo**.
- 🙌 Special thanks to all contributors, testers, and players who made this project possible.
- 💻 Built with love for coding and gaming.

---

Enjoy the game and may the best strategist win! 🏅

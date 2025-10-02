# Tic-Tac-Toe

A console-based Tic-Tac-Toe game written in C++. Clean, keyboard-driven UI with multiple board sizes, AI opponents, and a persistent match history.

---

## Overview

Tic-Tac-Toe is a two-player turn-based game where each player places their symbol (X or O) on a square grid. The goal is to complete a full line (horizontal, vertical, or diagonal) before your opponent. This implementation supports boards from **3×3 up to 6×6**, is fully keyboard-controlled, and offers both Human vs Human and Human vs AI play.

---

## Key Features (Current)

* **Board sizes:** 3×3 through 6×6 (selectable in the menu).
* **Game modes:** Human vs Human, Human vs AI.
* **AI levels:**

  * **Neko (Easy)** — fast, casual opponent.
  * **Tora (Medium)** — stronger heuristics for a harder match.
  * **Hard (Unbeatable)** — coming soon (planned).
* **Keyboard-first UI:** Arrow keys or WASD to move, `Enter` to confirm, and **`Escape`** to go back from anywhere.
* **Clean console UI:** Designed to feel GUI-like while remaining text-based.
* **Persistent history:** Every completed match is appended to a plain-text history file (default: `history.txt`) and can be loaded from the menu for review.
* **External terminal required:** *Do not run inside an IDE integrated terminal.* Use a native terminal (Windows Terminal / PowerShell / cmd, macOS Terminal / iTerm2, Linux gnome-terminal / xterm) for correct UI rendering.

---


## Preview

to be added once finalized

---


## Quick Start (Build & Run)

### Clone the repo

```bash
https://github.com/sizan14789/Tic-Tac-Toe.git
```
### Build and Run

```cmd
g++ main.cpp -o main.exe; start main.exe
```

> **Important:** Run the executable in a native external terminal. Integrated IDE terminals often mishandle special key sequences and raw input.

---

## Controls

* **Move cursor:** Arrow keys or `W` `A` `S` `D`
* **Select / Confirm:** `Enter`
* **Back / Cancel / Menu:** `Escape` (works anywhere except name selection)
* **All input is keyboard-only; no mouse required.**

---

## Match History

* All finished matches are recorded in a plain-text file (`history.txt`).
* Each entry includes: players' name, board size and result (winner/draw).
* From the main menu, choose **History** to see the previous matches.

---

## UI & Design Notes

* The UI uses terminal control (ANSI sequences) to provide a clean, fast keyboard-driven experience.
* Special keys (arrow keys, Escape) are handled via getch().
* The UI attempts to mimic GUI-like clarity (menus, highlights, clear focus) while staying fully terminal-based.

---

## Notes & Known Issues

* **Do not run in IDE integrated terminals.** They commonly fail to handle special key sequences correctly.
* History file is plain text — it can grow large over time. Consider rotating or archiving if you play many matches.

## Greek Wordle - C++ Terminal Game

A terminal-based Wordle-style game implemented in C++ where players guess 5-letter **Greek words** within 6 tries. This project was created as a university group assignment focused on applying object-oriented principles and working with Unicode input/output.

---

## 🎮 Game Overview

- Guess the correct 5-letter **Greek** word within 6 attempts.
- After each guess, letters are color-coded:
  - 🟩 **Green** = Correct letter in correct position
  - 🟨 **Yellow** = Correct letter in wrong position
  - ⬜ **Gray** = Letter not in the word
- Greek keyboard layout and Unicode input/output fully supported.

---

## 📷 Screenshot (Terminal Preview)
![image](https://github.com/user-attachments/assets/155342ed-5659-4060-9757-542d3fdd2779)
![image](https://github.com/user-attachments/assets/48ea3c07-f725-4ec7-8972-77cb08b3b1d6)


---

## 🧠 Features

- UTF-8 / UTF-16 Greek character handling
- Colorful terminal output (Windows-only)
- Input validation for 5-letter Greek words
- Replay option after game ends
- Built-in keyboard display with dynamic color updates
- Dictionary-based random word selection (`5letterwords.txt`)

---

## 💻 How to Run

### ✅ Requirements

- Windows OS (uses `<windows.h>`)
- C++17 compiler (e.g. MSVC, MinGW)
- UTF-8/Greek console font (like Consolas or Lucida Console)

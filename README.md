# Quiz Game (C Console Application)

A modular, text-based interactive quiz system developed in C for **CSE103: Structured Programming** at **East West University**.

---

## Features

- **Authentication System:**
  - User registration and login persisted in `users.txt`.
  - Admin login panel with administrative privileges (`admin` / `admin123`).
- **Dynamic Quiz Categories & Difficulty:**
  - 8 distinct categories: Science, Technology, Movies, Sports, General Health, Geography, History, and Math.
  - 3 difficulty levels per topic: Easy (100 pts), Moderate (200 pts), and Difficult (300 pts).
- **Gamified Scoring & Health System:**
  - Players start with **3 lives**.
  - Incorrect answers deduct 1 life; reaching 0 lives ends the game.
- **Admin Management Panel:**
  - Add or remove questions dynamically per topic and difficulty level.
  - Limit of 10 questions per difficulty file.
  - Register new users directly from the admin panel.

---

## File Storage Format

Questions are organized using plain text files matching the pattern `<topic>_<difficulty>.txt` (e.g., `science_easy.txt`).

Each question entry occupies exactly **6 lines**:
```text
Question string
Option 1
Option 2
Option 3
Option 4
Correct Option (1-4)
```

Example (`math_easy.txt`):
```text
1+1=?
1
2
3
4
2
```

---

## Getting Started

### Prerequisites
- GCC or any standard C compiler (MinGW, Clang, MSVC).

### Compilation
Compile `main.c` using GCC:
```bash
gcc -o quiz_game main.c
```

### Execution
Run the compiled executable:
```bash
# On Linux/macOS
./quiz_game

# On Windows
quiz_game.exe
```

---

## Default Credentials

| Role | Username | Password |
| :--- | :--- | :--- |
| **Admin** | `admin` | `admin123` |

---

## Project Information

- **Institution:** East West University
- **Course:** CSE103: Structured Programming (Fall 2024)
- **Course Instructor:** Md. Ashraful Haider Chowdhury
- **Group:** 08 (Section 28)

### Team Members
- **Subha Hoq** (ID: 2024-3-60-081)
- **Fazle Rabbi** (ID: 2024-3-60-084)
- **Tonmoy Shil** (ID: 2024-3-60-702)
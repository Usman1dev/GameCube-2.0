# 🎮 Game Cube 2.0

## 📌 Project Description
Game Cube 2.0 is a console-based C++ application that combines multiple mini-games into a single platform. It includes a user authentication system and developer tools, while demonstrating core Object-Oriented Programming (OOP) concepts such as inheritance, polymorphism, encapsulation, and abstraction.

Done in collaboration with @codeBIlal-exe

---

## 🎯 Features
- 🎲 Multiple mini-games in one system:
  - Rock Paper Scissors
  - Tic Tac Toe (Player vs Player & Player vs AI)
  - Race to 100 (Computer-based game)
  - Guess the Number (4 modes)

- 👤 User Management System:
  - Signup / Login functionality
  - File-based data storage
  - Secure authentication system

- 🛠️ Developer Tools:
  - View registered users
  - Delete user accounts
  - Administrative control over system

- 🤖 AI Integration:
  - Tic Tac Toe AI using Minimax algorithm
  - Randomized computer behavior in games

---

## 🧠 Technologies Used
- C++
- Object-Oriented Programming (OOP)
- File Handling (ifstream / ofstream)
- Data Structures (Vectors)
- Algorithms (Minimax, Randomization)

---

## 🧩 OOP Concepts Implemented

- **Encapsulation**
  - User credentials are hidden using private data members
  - Access controlled via public methods

- **Inheritance**
  - `Game` is a base class
  - All games inherit from `Game`
  - `Developer` class inherits from `User`

- **Polymorphism**
  - Virtual function `play()` overridden in each game class
  - Games executed dynamically using `Game*` pointers

- **Abstraction**
  - `Game` class defines structure without exposing implementation

---

## 👨‍💻Author

**🔹Muhammad Usman Khan**<br>
  GitHub: https://github.com/Usman1dev<br>
  LinkedIn: https://www.linkedin.com/in/usman0310<br>
**🔹Muhammad Bilal**<br>
  GitHub: https://github.com/codeBilal-exe
---
## ⚙️ How to Run the Project

### 🔹 Using Terminal / CMD
```bash
g++ main.cpp -o GameCube
./GameCube

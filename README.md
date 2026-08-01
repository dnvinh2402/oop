# 🚀 Space Defender

A 2D Space Shooter game developed in **C++** using the **SFML 3.0** graphics library.

The project was built for an Object-Oriented Programming (OOP) course and applies object-oriented design principles together with resource management, collision detection, game states, and buff mechanics.

---

# Features

## Gameplay
- Player movement (WASD / Arrow Keys)
- Shoot enemies
- 3 rounds with increasing difficulty
- Boss battle in the final round
- Score system
- High score saving
- Match history
- Pause / Resume
- Main Menu
- Victory / Game Over screens

---

## Buff System

Enemies have a chance to drop buffs after being destroyed.

Current buffs:

- 🟢 Double Shot
  - Fires two bullets simultaneously
  - Duration: 10 seconds

- 🔵 Shield
  - Protects the player from enemy bullets
  - Limited duration

- 🔴 Bomb
  - Launches a missile after a short delay
  - Destroys nearby enemies on impact

---

## Audio System

Implemented using SFML Audio.

Includes:

- Shoot sound
- Explosion sound
- Enemy eliminated sound
- Shield hit sound
- Player hit sound
- Item pickup sound
- Background music

Supports:

- Volume adjustment
- Mute / Unmute
- Global audio settings shared across menus

---

# Project Structure

```
OOP/
│
├── assets/
│   ├── audio/
│   ├── font/
│   └── images/
│
├── build/
│   ├── main.exe
│   └── SFML DLLs
│
├── docs/
│
├── include/
│   ├── Alien.hpp
│   ├── AlienManager.hpp
│   ├── Buff.hpp
│   ├── BuffManager.hpp
│   ├── Bullet.hpp
│   ├── CollisionManager.hpp
│   ├── Game.hpp
│   ├── GameOverMenu.hpp
│   ├── GlobalAudio.hpp
│   ├── MainMenu.hpp
│   ├── Missile.hpp
│   ├── PauseMenu.hpp
│   ├── Player.hpp
│   ├── ResourceManager.hpp
│   ├── ScoreHistoryMenu.hpp
│   ├── SoundManager.hpp
│   └── UI.hpp
│
├── src/
│   ├── Alien.cpp
│   ├── AlienManager.cpp
│   ├── Buff.cpp
│   ├── BuffManager.cpp
│   ├── Bullet.cpp
│   ├── CollisionManager.cpp
│   ├── Game.cpp
│   ├── GameOverMenu.cpp
│   ├── GlobalAudio.cpp
│   ├── MainMenu.cpp
│   ├── Missile.cpp
│   ├── PauseMenu.cpp
│   ├── Player.cpp
│   ├── ResourceManager.cpp
│   ├── ScoreHistoryMenu.cpp
│   ├── SoundManager.cpp
│   ├── UI.cpp
│   └── main.cpp
│
└── .gitignore
```

---

# Main Components

## Game
Controls the main game loop.

Responsibilities:

- Update()
- Render()
- ProcessEvents()
- RestartGame()
- Manage game states

---

## Player

Responsible for:

- Movement
- Shooting
- Health
- Buff effects
- Score

---

## AlienManager

Responsible for:

- Enemy spawning
- Round management
- Boss spawning
- Enemy shooting

---

## CollisionManager

Handles all collision detection:

- Bullet ↔ Alien
- Bullet ↔ Player
- Player ↔ Buff
- Missile ↔ Alien

---

## ResourceManager

Loads and manages:

- Textures
- Fonts

Avoids loading the same resource multiple times.

---

## SoundManager

Handles:

- Sound effects
- Background music
- Volume control
- Mute state

Uses `GlobalAudio` to synchronize audio settings across the game.

---

## UI

Displays:

- Score
- Lives
- Buff information
- Current round
- High score

---

## Menus

### MainMenu

- Start Game
- Match History
- Volume
- Mute

### PauseMenu

- Resume
- Return to Main Menu
- Volume
- Mute

### GameOverMenu

- Restart
- Return to Main Menu

### ScoreHistoryMenu

Displays scores from previous matches.

---

# Controls

| Key | Action |
|------|--------|
| A / Left Arrow | Move Left |
| D / Right Arrow | Move Right |
| W / Up Arrow | Move Up |
| S / Down Arrow | Move Down |
| Space | Shoot |
| Left Mouse | Shoot / Menu Interaction |

---

# Technologies

- C++
- SFML 3.0
- Object-Oriented Programming
- Visual Studio Code
- MSYS2 UCRT64
- Git
- GitHub

---

# Design Principles

The project follows Object-Oriented Programming concepts including:

- Encapsulation
- Inheritance
- Polymorphism
- Resource Management
- Modular Design

---

# Future Improvements

- Additional enemy types
- More buff varieties
- Sound settings menu
- Particle effects
- Animation system
- Save & Load progress
- Multiple difficulty levels

---

# Authors

OOP Project - Space Defender

Developed as part of the Object-Oriented Programming course.
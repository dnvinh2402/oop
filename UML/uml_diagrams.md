# UML Diagrams for the Game Project

## Class Diagram

```mermaid
classDiagram

    class GameObject {
        +sf::Vector2f position
        +sf::Sprite sprite
        +bool isActive
        +IsActive()
        +Destroy()
        +GetBounds()
        +GetPosition()
        +Update(float)
        +Render(sf::RenderWindow&)
    }

    class Player {
        -float speed
        -int lives
        -int score
        -float fireCooldown
        -float currentCooldown

        -int healthLevel
        -int fireRateLevel
        -int speedLevel

        -bool doubleShot
        -bool shield
        -float doubleShotTimer
        -float shieldTimer
        -int shieldHitsRemaining

        -bool bombReady
        -float bombTimer
        -int bombCount

        -bool invincible
        -float invincibleTimer
        -float blinkTimer
        -bool blinkVisible

        +Player(sf::Texture*, sf::Vector2f, int, int, int)
        +Update(float)
        +Render(sf::RenderWindow&)
        +HandleInput(float)
        +Shoot(std::vector<Bullet*>&, sf::Texture*)
        +TakeDamage()
        +ActivateDoubleShot()
        +ActivateShield()
        +ActivateBomb()
        +ResetBomb()
        +IsBombReady()
        +HasShield()
        +GetShieldTimer()
        +GetShieldHitsRemaining()
        +GetScore()
        +GetLives()
    }

    class Alien {
        -int pointValue
        -MovementType movementType
        -sf::Vector2f orbitCenter
        -float orbitRadius
        -float angle
        -float spawnDelay
        -float spawnTimer
        -bool hasSpawned
        -float aliveTimer
        -float survivalTime
        -sf::Vector2f entryStartPos
        -float shootCooldown
        -float shootTimer
        -int maxHealth
        -int currentHealth

        +Update(float)
        +Render(sf::RenderWindow&)
        +CanShoot()
        +ResetShootCooldown()
        +TakeDamage(int)
        +CalculateNormalScore()
        +CalculateBossHitScore()
        +CalculateBossKillScore()
        +GetMaxHealth()
    }

    class Bullet {
        -sf::Vector2f velocity
        -bool isPlayerBullet

        +Update(float)
        +Render(sf::RenderWindow&)
        +IsPlayerBullet()
    }

    class Missile {
        -sf::Vector2f velocity

        +Missile(sf::Texture*, sf::Vector2f)
        +Update(float)
        +Render(sf::RenderWindow&)
    }

    class Buff {
        -BuffType type
        -float fallSpeed

        +Buff(sf::Texture*, sf::Vector2f, BuffType)
        +Update(float)
        +Render(sf::RenderWindow&)
        +GetType()
    }

    class AlienManager {
        -std::vector<Alien*> aliens
        -float moveSpeed
        -bool movingRight
        -int currentRound
        -int maxRounds

        +InitializeSwarm(sf::Texture*)
        +Update(float)
        +Render(sf::RenderWindow&)
        +AlienShoot(std::vector<Bullet*>&, sf::Texture*)
        +IsRoundCleared()
        +IsFinalRound()
        +StartNextRound(sf::Texture*)
        +Reset(sf::Texture*)
        +GetAliens()
    }

    class BuffManager {
        -std::vector<Buff*> buffs

        +SpawnBuff(sf::Texture*, sf::Vector2f, BuffType)
        +Update(float)
        +Render(sf::RenderWindow&)
        +CleanUp()
        +GetBuffs()
    }

    class CollisionManager {
        +CheckCollisions(Player*, std::vector<Alien*>&, std::vector<Bullet*>&, std::vector<Buff*>&, BuffManager*, ResourceManager&, SoundManager&)
    }

    class ResourceManager {
        -std::map<std::string, sf::Texture*> textures
        -std::map<std::string, sf::Font*> fonts

        +LoadTexture(std::string, std::string)
        +GetTexture(std::string)
        +LoadFont(std::string, std::string)
        +GetFont(std::string)
    }

    class SoundManager {
        -std::map<std::string, sf::SoundBuffer*> soundBuffers
        -std::map<std::string, sf::Sound*> sounds
        -sf::Music music

        +LoadSound(std::string, std::string)
        +LoadMusic(std::string)
        +Play(std::string)
        +PlayMusic()
        +UpdateVolume()
    }

    class UI {
        -sf::Font* font
        -sf::Text scoreText
        -sf::Text livesText
        -sf::Text shieldText
        -sf::Text doubleShotText
        -sf::Text titleText
        -sf::Text subText
        -sf::Text scoreResultText
        -sf::RectangleShape overlay
        -GameState state

        +Update(Player*, GameState, int)
        +Render(sf::RenderWindow&)
    }

    class MainMenu {
        -sf::Font* font
        -sf::Sprite* bgSprite

        +Update(sf::Vector2f)
        +HandleClick(sf::Vector2f)
        +Render(sf::RenderWindow&)
        +SetVolume(int, bool)
    }

    class ShipSelectionMenu {
        -sf::Font* font
        -sf::Text titleText
        -sf::Text instructionText
        -sf::Text shipNameText
        -sf::Sprite* shipSprite
        -std::vector<sf::Texture*> shipTextures
        -int selectedShip
        -sf::Vector2f shipBasePosition
        -sf::RectangleShape frameShape
        -sf::RectangleShape frameBackground

        -int healthLevel
        -int fireRateLevel
        -int speedLevel

        +ShipSelectionMenu(sf::Font*, std::vector<sf::Texture*>&)
        +Update()
        +Render(sf::RenderWindow&)
        +UpdateAnimation(float)
        +SetSelectedShip(int)
        +MoveSelection(int)
        +GetSelectedShip()
        +GetHealthLevel()
        +GetFireRateLevel()
        +GetSpeedLevel()
    }

    class PauseMenu {
        -sf::Font* font
        -sf::RectangleShape backgroundOverlay
        -sf::Sprite* menuBgSprite
        -sf::Sprite* pauseSprite
        -sf::Sprite* resumeSprite
        -sf::Sprite* homeSprite
        -sf::Sprite* muteSprite
        -sf::Sprite* minusSprite
        -sf::Sprite* plusSprite
        -sf::Text volumeText
        -float volume
        -bool isMuted

        +IsPauseButtonClicked(sf::Vector2f)
        +Update(sf::Vector2f)
        +HandleClick(sf::Vector2f)
        +Render(sf::RenderWindow&, bool)
    }

    class GameOverMenu {
        -sf::Font* font
        -sf::Sprite* titleSprite
        -sf::Text finalScoreText
        -sf::Sprite* restartSprite
        -sf::Sprite* menuSprite

        +Update(sf::Vector2f)
        +HandleClick(sf::Vector2f)
        +Render(sf::RenderWindow&)
    }

    class ScoreHistoryMenu {
        -sf::Font* font
        -sf::RectangleShape backgroundOverlay
        -sf::Sprite* menuBgSprite
        -sf::Text titleText
        -sf::Sprite* backSprite
        -std::vector<sf::Text> scoreTexts

        +Update(sf::Vector2f)
        +IsBackButtonClicked(sf::Vector2f)
        +Render(sf::RenderWindow&)
    }

    class Game {
        -sf::RenderWindow window
        -sf::View gameView

        -ResourceManager resourceManager
        -Player* player
        -AlienManager* alienManager

        -std::vector<Bullet*> bullets
        -std::vector<Missile*> missiles

        -BuffManager* buffManager
        -CollisionManager collisionManager

        -UI* gameUI
        -SoundManager soundManager

        -sf::Sprite* backgroundSprite
        -sf::Sprite* explosionSprite
        -sf::Sprite* shieldSprite

        -GameState currentState
        -int highScore

        -MainMenu* mainMenu
        -ShipSelectionMenu* shipSelectionMenu
        -PauseMenu* pauseMenu
        -GameOverMenu* gameOverMenu
        -ScoreHistoryMenu* scoreHistoryMenu

        -std::vector<sf::Texture*> shipTextures
        -int selectedShip

        -bool isPaused
        -bool viewingHistory
        -std::vector<int> matchHistory

        -bool explosionActive
        -float explosionTimer

        +Run()
        +ProcessEvents()
        +Update(float)
        +CleanUpDeadEntities()
        +Render()
        +RestartGame()
        +DestroyNearestAliens(sf::Vector2f)
    }


    GameObject <|-- Player
    GameObject <|-- Alien
    GameObject <|-- Bullet
    GameObject <|-- Missile
    GameObject <|-- Buff

    Game --> ResourceManager
    Game --> Player
    Game --> AlienManager
    Game --> BuffManager
    Game --> CollisionManager
    Game --> UI
    Game --> SoundManager
    Game --> MainMenu
    Game --> ShipSelectionMenu
    Game --> PauseMenu
    Game --> GameOverMenu
    Game --> ScoreHistoryMenu
    Game --> Missile

    AlienManager --> Alien
    BuffManager --> Buff

    CollisionManager --> Player
    CollisionManager --> Alien
    CollisionManager --> Bullet
    CollisionManager --> Buff
    CollisionManager --> BuffManager
    CollisionManager --> ResourceManager
    CollisionManager --> SoundManager
```

---

# Sequence Diagram

## 1. Game Loop and Shooting Sequence

```mermaid
sequenceDiagram
    actor User
    participant Main as main.cpp
    participant Game
    participant Player
    participant Bullets as BulletList
    participant MissileList
    participant AlienManager
    participant BuffManager
    participant Collision as CollisionManager

    User ->> Main: start program
    Main ->> Game: instantiate Game

    Game ->> ResourceManager: load textures/fonts
    Game ->> SoundManager: load sounds/music

    Main ->> Game: Run()

    loop while window is open

        Game ->> Game: ProcessEvents()

        alt Player shoots
            Game ->> Player: Shoot(bullets, bulletTexture)
            Player ->> Bullets: push_back(new Bullet)
            Game ->> SoundManager: Play("shoot")
        end

        Game ->> Player: HandleInput(deltaTime)
        Game ->> Player: Update(deltaTime)

        alt Bomb is ready
            Game ->> Player: IsBombReady()
            Game ->> MissileList: push_back(new Missile)
            Game ->> Player: ResetBomb()
        end

        Game ->> AlienManager: Update(deltaTime)
        Game ->> BuffManager: Update(deltaTime)

        Game ->> Bullets: Update each Bullet
        Game ->> MissileList: Update each Missile

        Game ->> Collision: CheckCollisions(...)

        alt Bullet hits Alien
            Collision ->> Alien: TakeDamage(1)
            Collision ->> Bullet: Destroy()
        end

        alt Bullet hits Player
            Collision ->> Player: TakeDamage()
            Collision ->> Bullet: Destroy()
        end

        alt Player picks Buff
            Collision ->> Player: ActivateBuff()
            Collision ->> Buff: Destroy()
        end

        Game ->> Game: CleanUpDeadEntities()
        Game ->> Game: Render()

    end
```

---

# 2. Main Menu Interaction

```mermaid
sequenceDiagram
    actor User
    participant Game
    participant MainMenu
    participant ShipSelection as ShipSelectionMenu
    participant ScoreHistory as ScoreHistoryMenu

    User ->> Game: open application

    Game ->> MainMenu: Render()

    alt User selects Play
        User ->> MainMenu: click Play
        MainMenu ->> Game: HandleClick(mousePos)

        Game ->> ShipSelection: Render()

    else User selects History

        User ->> MainMenu: click History
        MainMenu ->> Game: HandleClick(mousePos)

        Game ->> ScoreHistory: new ScoreHistoryMenu()

        ScoreHistory ->> Game: Render()

        User ->> ScoreHistory: click Back
        ScoreHistory ->> Game: IsBackButtonClicked(mousePos)

        Game ->> ScoreHistory: delete menu
        Game ->> MainMenu: return to MainMenu
    end
```

---

# 3. Ship Selection Sequence

```mermaid
sequenceDiagram
    actor User
    participant Game
    participant ShipSelection as ShipSelectionMenu
    participant Player

    Game ->> ShipSelection: Render()

    loop Ship selection
        User ->> Game: press Left / Right

        Game ->> ShipSelection: MoveSelection(delta)

        ShipSelection ->> ShipSelection: SetSelectedShip(index)
        ShipSelection ->> ShipSelection: RefreshSelection()

        ShipSelection ->> ShipSelection: update ship image
        ShipSelection ->> ShipSelection: update ship name
        ShipSelection ->> ShipSelection: update Attributes
    end

    User ->> Game: press Enter

    Game ->> ShipSelection: GetSelectedShip()
    Game ->> ShipSelection: GetHealthLevel()
    Game ->> ShipSelection: GetFireRateLevel()
    Game ->> ShipSelection: GetSpeedLevel()

    Game ->> Player: create Player(selectedTexture, position, stats)

    Game ->> Game: currentState = Playing
```

---

# 4. Buff Pickup Sequence

```mermaid
sequenceDiagram
    actor User
    participant Game
    participant BuffManager
    participant Buff
    participant Collision as CollisionManager
    participant Player
    participant Sound as SoundManager

    Game ->> BuffManager: Update(deltaTime)
    BuffManager ->> Buff: Update(deltaTime)

    Game ->> Collision: CheckCollisions(...)

    Collision ->> Player: GetBounds()
    Collision ->> Buff: GetBounds()

    alt Double Shot picked up

        Collision ->> Player: ActivateDoubleShot()
        Player ->> Player: doubleShot = true
        Player ->> Player: doubleShotTimer = 10s

        Collision ->> Sound: Play("pickup")
        Collision ->> Buff: Destroy()

    else Shield picked up

        Collision ->> Player: ActivateShield()
        Player ->> Player: shield = true
        Player ->> Player: shieldTimer = ...

        Collision ->> Sound: Play("pickup")
        Collision ->> Buff: Destroy()

    else Bomb picked up

        Collision ->> Player: ActivateBomb()
        Player ->> Player: bombCount++

        Collision ->> Sound: Play("pickup")
        Collision ->> Buff: Destroy()

    end
```

---

# 5. Missile / Bomb Sequence

```mermaid
sequenceDiagram
    actor User
    participant Game
    participant Player
    participant Missile
    participant AlienManager
    participant Alien
    participant Sound as SoundManager

    User ->> Player: pick up Bomb

    Player ->> Player: ActivateBomb()
    Player ->> Player: bombReady = true
    Player ->> Player: bombTimer = 1s

    Game ->> Player: IsBombReady()

    alt Bomb ready

        Game ->> Missile: create Missile(player position)
        Game ->> Player: ResetBomb()

        loop while Missile is active
            Game ->> Missile: Update(deltaTime)
        end

    end

    Missile ->> Alien: collision check

    alt Missile hits Alien

        Missile ->> Missile: Destroy()

        Game ->> Sound: Play("explosion")

        Game ->> AlienManager: GetAliens()

        Game ->> Game: DestroyNearestAliens(missile position)

        loop maximum 5 nearest active Aliens
            Game ->> Alien: Destroy()
        end

        Game ->> Game: explosionActive = true
        Game ->> Game: explosionTimer = 0.3s

    end
```

---

# 6. Scoring Sequence

```mermaid
sequenceDiagram
    participant Bullet
    participant Collision as CollisionManager
    participant Alien
    participant Player

    Bullet ->> Collision: collision with Alien

    Collision ->> Alien: TakeDamage(1)
    Collision ->> Bullet: Destroy()

    alt Normal Alien is destroyed

        Alien ->> Alien: currentHealth <= 0
        Collision ->> Alien: CalculateNormalScore()
        Alien -->> Collision: normalScore
        Collision ->> Player: AddScore(normalScore)

    else Boss is hit

        Collision ->> Alien: CalculateBossHitScore()
        Alien -->> Collision: hitScore

        Collision ->> Player: AddScore(hitScore)

        alt Boss is destroyed

            Collision ->> Alien: CalculateBossKillScore()
            Alien -->> Collision: killScore

            Collision ->> Player: AddScore(killScore)

        end

    end
```

---

# 7. Shield and Player Damage Sequence

```mermaid
sequenceDiagram
    participant Bullet
    participant Collision as CollisionManager
    participant Player
    participant Sound as SoundManager

    Bullet ->> Collision: hit Player

    alt Player has Shield

        Collision ->> Player: HasShield()
        Player -->> Collision: true

        Collision ->> Player: TakeDamage()
        Player ->> Player: reduce shield hit count

        Collision ->> Sound: Play("shield")

        Collision ->> Bullet: Destroy()

    else Player has no Shield

        Collision ->> Player: TakeDamage()
        Player ->> Player: lives--

        Collision ->> Sound: Play("hit")

        Collision ->> Bullet: Destroy()

    end
```

---

## 8. Game Over / Victory Sequence

```mermaid
sequenceDiagram
    participant Game
    participant Player
    participant AlienManager
    participant GameOverMenu

    Game ->> Player: IsActive()

    alt Player is dead

        Player -->> Game: false
        Game ->> Game: AddScoreToHistory()
        Game ->> GameOverMenu: create GameOverMenu()
        Game ->> Game: currentState = GameOver

    else All rounds cleared

        Game ->> AlienManager: IsRoundCleared()

        alt Final round

            AlienManager -->> Game: IsFinalRound() = true

            Game ->> Game: AddScoreToHistory()
            Game ->> GameOverMenu: create Victory menu
            Game ->> Game: currentState = Victory

        else Not final round

            Game ->> AlienManager: StartNextRound()

        end
    end
```

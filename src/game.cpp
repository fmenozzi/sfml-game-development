#include "game.hpp"

#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const float PLAYER_SPEED = 100.f;
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
              "SFML Game Development"),
      mTexture(),
      mPlayer(),
      mIsDebugInfoEnabled(false),
      mDebugInfoFont(),
      mDebugInfoText(),
      mDebugInfoUpdateTime(),
      mDebugInfoNumFrames(0),
      mIsMovingUp(false),
      mIsMovingDown(false),
      mIsMovingLeft(false),
      mIsMovingRight(false) {
    // Load player texture/sprite.
    mTexture.loadFromFile(RESOURCE_DIRECTORY "textures/eagle.png");
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);

    // Load debug info font/text.
    mDebugInfoFont.loadFromFile(RESOURCE_DIRECTORY "/fonts/sansation.ttf");
    mDebugInfoText.setFont(mDebugInfoFont);
    mDebugInfoText.setColor(sf::Color::White);
    mDebugInfoText.setPosition(5.f, 5.f);
    mDebugInfoText.setCharacterSize(10);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        auto elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            processEvents();
            update(TIME_PER_FRAME);
        }
        updateDebugInfo(elapsedTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, /*isPressed=*/true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, /*isPressed=*/false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time dt) {
    sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingUp) {
        movement.y -= PLAYER_SPEED;
    }
    if (mIsMovingDown) {
        movement.y += PLAYER_SPEED;
    }
    if (mIsMovingLeft) {
        movement.x -= PLAYER_SPEED;
    }
    if (mIsMovingRight) {
        movement.x += PLAYER_SPEED;
    }

    mPlayer.move(movement * dt.asSeconds());
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer);
    if (mIsDebugInfoEnabled) {
        mWindow.draw(mDebugInfoText);
    }
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
        case sf::Keyboard::W:
            mIsMovingUp = isPressed;
            break;
        case sf::Keyboard::S:
            mIsMovingDown = isPressed;
            break;
        case sf::Keyboard::A:
            mIsMovingLeft = isPressed;
            break;
        case sf::Keyboard::D:
            mIsMovingRight = isPressed;
            break;
        case sf::Keyboard::F3:
            toggleDebugInfo(isPressed);
            break;
        default:
            break;
    }
}

void Game::toggleDebugInfo(bool isPressed) {
    if (isPressed) {
        mIsDebugInfoEnabled = !mIsDebugInfoEnabled;
    }
}

void Game::updateDebugInfo(sf::Time elapsedTime) {
    mDebugInfoUpdateTime += elapsedTime;
    mDebugInfoNumFrames += 1;

    if (mDebugInfoUpdateTime >= sf::seconds(1.f)) {
        mDebugInfoText.setString("FPS: " + std::to_string(mDebugInfoNumFrames));

        mDebugInfoUpdateTime -= sf::seconds(1.f);
        mDebugInfoNumFrames = 0;
    }
}

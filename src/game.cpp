#include "game.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const float PLAYER_SPEED = 100.f;
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
              "SFML Game Development"),
      mPlayer() {
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            processEvents();
            update(TIME_PER_FRAME);
        }
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
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) {
        mIsMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        mIsMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        mIsMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        mIsMovingRight = isPressed;
    }
}

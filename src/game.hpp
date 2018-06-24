#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    void updateDebugInfo(sf::Time elapsedTime);
    void toggleDebugInfo(bool isPressed);

private:
    sf::RenderWindow mWindow;

    // Player character.
    sf::Texture mTexture;
    sf::Sprite mPlayer;

    // Debug info metadata.
    bool mIsDebugInfoEnabled;
    sf::Font mDebugInfoFont;
    sf::Text mDebugInfoText;
    sf::Time mDebugInfoUpdateTime;
    std::size_t mDebugInfoNumFrames;

    // Player character movement.
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};

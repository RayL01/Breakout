#include <SFML/Graphics.hpp>
#include <vector>

struct Brick {
    sf::RectangleShape shape;
    bool destroyed{false};
    Brick() : destroyed(false){}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout Game");

    sf::RectangleShape paddle(sf::Vector2f(100, 20));
    paddle.setFillColor(sf::Color::Blue);
    paddle.setPosition(350, 550);

    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(390, 500);

    std::vector<Brick> bricks;
    for (int iX = 0; iX < 10; ++iX) {
        for (int iY = 0; iY < 4; ++iY) {
            bricks.emplace_back((Brick){});
            bricks.back().shape.setPosition(5 + iX * 60, 5 + iY * 30);
            bricks.back().shape.setSize({50, 20});
            bricks.back().shape.setFillColor(sf::Color::Yellow);
        }
    }

    sf::Vector2f velocity(0.1f, -0.1f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ball.move(velocity);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paddle.move(-0.4f, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paddle.move(0.4f, 0);
        }

        if (paddle.getPosition().x < 0) {
            paddle.setPosition(0, paddle.getPosition().y);
        }

        if (paddle.getPosition().x > window.getSize().x - paddle.getSize().x) {
            paddle.setPosition(window.getSize().x - paddle.getSize().x, paddle.getPosition().y);
        }

        sf::FloatRect ballBounds = ball.getGlobalBounds();

        if (ballBounds.intersects(paddle.getGlobalBounds())) {
            velocity.y = -velocity.y;
        }

        if (ballBounds.left <= 0 || ballBounds.left + ballBounds.width >= window.getSize().x) {
            velocity.x = -velocity.x;
        }

        if (ballBounds.top <= 0) {
            velocity.y = -velocity.y;
        }

        for (auto& brick : bricks) {
            if (!brick.destroyed && ballBounds.intersects(brick.shape.getGlobalBounds())) {
                brick.destroyed = true;
                velocity.y = -velocity.y;
                break;
            }
        }

        window.clear(sf::Color::Black);

        if (ball.getPosition().y > window.getSize().y) {
            window.close();
        }

        window.draw(paddle);
        window.draw(ball);

        for (auto& brick : bricks) {
            if (!brick.destroyed) {
                window.draw(brick.shape);
            }
        }

        window.display();
    }

    return 0;
}


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Breakout Game");

    sf::RectangleShape paddle(sf::Vector2f(100, 20));
    paddle.setFillColor(sf::Color::Blue);
    paddle.setPosition(350, 550);

    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(390, 500);

    sf::Vector2f velocity(0.1f, -0.1f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            paddle.move(-0.1f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            paddle.move(0.1f, 0);

        ball.move(velocity.x, velocity.y);
        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::FloatRect paddleBounds = paddle.getGlobalBounds();

        if (ballBounds.intersects(paddleBounds))
            velocity.y = -velocity.y;
        if (ballBounds.left <= 0 || ballBounds.left+ballBounds.width >= window.getSize().x)
            velocity.x = -velocity.x;
        if (ballBounds.top <= 0)
            velocity.y = -velocity.y;

        window.clear();
        window.draw(paddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}


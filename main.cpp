#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

sf::RenderWindow createWindow(){
    return{
      sf::VideoMode { 1200, 800 },
      "cpp program",
      sf::Style::Titlebar | sf::Style::Close
    };
}



sf::Texture loadTexture(const std::string & filename) {
    sf::Texture tex;
    if (not tex.loadFromFile(filename)){
        std::cerr << "Reading texture from file " << filename << " failed." << std::endl;
        std::exit(-1);
    }
    return tex;
}

bool detectCollision(const sf::RectangleShape & rect, const sf::Vector2i){
    const auto dx = mouse.x - rect.getPosition().x;
    const auto dy = (mouse.y - rect.getPosition().y) * -1;
    const auto d = std::sqrt(dx*dx + dy*dy);

    const auto cos = (double)dx / d;
    auto phi = std::acos(cos);

    if (dy < 0 or (dy == 0 and dx < 0)){
        phi = 2*M_PI - phi;
    }

    std::cout << phi << std::endl;

    return false;
}

int main() {
    auto win = createWindow();

    auto texture = loadTexture("../picture.png");

    texture.setSmooth(true);

    sf::Sprite sprite { texture };

    constexpr float spriteSize = 256.f;

    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(spriteSize / texture.getSize().x, spriteSize / texture.getSize().y);
    sprite.setPosition(200, 200);

    sf::RectangleShape rect({ 100, 100 });
    rect.setFillColor(sf::Color::Red);
    rect.setOrigin(50, 50);
    rect.setPosition(600, 400);

    std::vector<sf::RectangleShape> rects;

    rects.emplace_back(sf::RectangleShape({ 50, 50 }));
    rects.back().setFillColor(sf::Color::White);
    rects.back().setOrigin(25, 25);
    rects.back().setPosition(400, 400);
    rects.back().setRotation(15.f);

    rects.emplace_back(sf::RectangleShape({ 50, 50 }));
    rects.back().setFillColor(sf::Color::White);
    rects.back().setOrigin(25, 25);
    rects.back().setPosition(500, 200);
    rects.back().setRotation(45.f);

    rects.emplace_back(sf::RectangleShape({ 50, 50 }));
    rects.back().setFillColor(sf::Color::White);
    rects.back().setOrigin(25, 25);
    rects.back().setPosition(300, 300);
    rects.back().setRotation(37.f);

    constexpr float rectVelocity = 80.f;

    constexpr float g = 500.f;
    constexpr float jump = 500.f;

    float spriteVelocity = 0.f;

    sf::Clock clock;

    while (win.isOpen()){

        sf::Event event {};
        while(win.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                win.close();}
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Q){
                    win.close();}}
            if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Space){
                spriteVelocity = -jump;
            }
        }

        auto dt = clock.restart().asSeconds();

        int x = 0;
        int y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            x += 1;
        }

        spriteVelocity += dt * g;

        sprite.move(0.f, spriteVelocity * dt);

        const auto bounds = sprite.getGlobalBounds();

        if (bounds.top + bounds.height > win.getSize().y){
            const auto diff = bounds.top + bounds.height - win.getSize().y;
            sprite.move(0.0, diff * -1);
            spriteVelocity = -(spriteVelocity / 2);
        }

        if (not x or not y){
            sprite.move(x * rectVelocity * dt, y * rectVelocity * dt);
        } else {
            sprite.move (x * rectVelocity * dt * (1/std::sqrt(2)), y * rectVelocity * dt * (1/std::sqrt(2)));
        }

        for (auto & rect : rects) {
            rect.setFillColor(sf::Color::White);

            const auto pos = sf::Mouse::getPosition(win);

            if (detectCollision()){

            }
        }

        win.clear(sf::Color::Black);
        win.draw(rect);
        win.draw( sprite);
        for (const auto & rect : rects) {
            win.draw(rect);
        }
        win.display();
    }
}


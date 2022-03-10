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

int main() {
    auto win = createWindow();

    sf::RectangleShape rect({ 100, 100 });
    rect.setFillColor(sf::Color::White);
    rect.setOrigin(50, 50);
    rect.setPosition(600, 400);

    const float rectVelocity = 80.f;

    sf::Clock clock;

    while (win.isOpen()){

        sf::Event event {};
        while(win.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                win.close();}
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Q){
                    win.close();}}
        }

        auto dt = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            rect.move(0.0, -rectVelocity * dt);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            rect.move(0.0, rectVelocity * dt);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            rect.move(-rectVelocity * dt, 0.0);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            rect.move(rectVelocity * dt, 0.0);}

        win.clear(sf::Color::Black);
        win.draw(rect);
        win.display();
    }
}


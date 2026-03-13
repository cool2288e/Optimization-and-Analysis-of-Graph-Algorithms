#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Карта України");
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("data/image/map.png")){
        std::cout <<"Помилка: не вдалося знайти файл карти!" <<std::endl;
        std::cin.get();
        return -1;
    }
    sf::Sprite mapSprite(mapTexture);

    // Камера
    sf::View view = window.getDefaultView();

    bool isDragging = false;
    sf::Vector2i oldMousePos;

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            // Зум
            if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>()){
                if (scroll->delta > 0) {
                    view.zoom(0.9f); // Наближення
                } else if (scroll->delta < 0){
                    view.zoom(1.1f); // Віддалення 
                }
            }
            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseBtn->button == sf::Mouse::Button::Left){
                    isDragging = true;
                    oldMousePos = sf::Mouse::getPosition(window);
                }
            }
            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonReleased>()){
                if (mouseBtn->button == sf::Mouse::Button::Left){
                    isDragging = false;
                }
            }
            if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()){
                if (isDragging){
                    sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f delta = window.mapPixelToCoords(oldMousePos) - window.mapPixelToCoords(newMousePos);
                    view.move(delta);
                    oldMousePos = newMousePos;
                }
            }
        }
        window.clear(sf::Color(200, 220, 240));
        window.setView(view);
        window.draw(mapSprite);
        window.display();
        
    } 
    return 0;
}

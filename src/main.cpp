#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/graph.h" 
int main() {
    CityGraph poltava; 
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("data/image/map.png")){
        std::cout <<"Помилка: не вдалося знайти файл карти!" <<std::endl;
        return -1;
    }
    mapTexture.setSmooth(true); 
    sf::Sprite mapSprite(mapTexture);
    sf::RenderWindow window(sf::VideoMode({1000, 800}), L"Навігатор Полтави");
    sf::View view = window.getDefaultView();
    bool isDragging = false;
    sf::Vector2i oldMousePos;
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>()){
                if (scroll->delta > 0) {
                    if (view.getSize().x > 300.f) view.zoom(0.9f); 
                } else if (scroll->delta < 0){
                    if (view.getSize().x < 2000.f) view.zoom(1.1f);  
                }
            }
            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseBtn->button == sf::Mouse::Button::Left){
                    isDragging = true;
                    oldMousePos = sf::Mouse::getPosition(window);
                }
                else if (mouseBtn->button == sf::Mouse::Button::Right){
                    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    std::cout << "poltava.addCity(\"Name\", " << worldPos.x << "f, " << worldPos.y << "f);" << std::endl;
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
        window.clear(); 
        window.setView(view);
        window.draw(mapSprite);
        for (auto const& [name, node] : poltava.cities) {
            for (const auto& edge : node.neighbors) {
                City& targetNode = poltava.cities[edge.to_city];
                
                sf::Vertex line[2];
                line[0].position = sf::Vector2f(node.x, node.y);
                line[0].color = sf::Color::Blue; 
                line[1].position = sf::Vector2f(targetNode.x, targetNode.y);
                line[1].color = sf::Color::Blue;
                
                window.draw(line, 2, sf::PrimitiveType::Lines);
            }
        }
        for (auto const& [name, node] : poltava.cities) {
            sf::CircleShape dot(6.f); 
            dot.setFillColor(sf::Color::Green); 
            dot.setPosition(sf::Vector2f(node.x - 6.f, node.y - 6.f));
            window.draw(dot);
        }
        window.display();
    }
    return 0;
}
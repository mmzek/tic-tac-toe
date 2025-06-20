#include <SFML/Graphics.hpp>
#include <iostream>
#include "interface.h"
#include "choice_menu.h"

#include "algorithm.h"
int SIZE = 3;
int WIN_CONDITION = 3;

void menuChoices(sf::RenderWindow& window, int& parameter, const std::string& text) {
    int windowMenuSize = window.getSize().x;
    int buttonWidth = windowMenuSize / 7;
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Font not found\n";
    }
    while (window.isOpen()) {

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(blue);

            sf::Text menuText(text, font, 60);
            menuText.setFillColor(purple);
            menuText.setPosition(windowMenuSize/2 - windowMenuSize/3, windowMenuSize/10);
            window.draw(menuText);

            sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonWidth));
            button.setFillColor(sf::Color::White);
            for (int i = 0; i < 3; ++i) {
                button.setPosition(buttonWidth*(i*2)+buttonWidth,(buttonWidth)*2);
                window.draw(button);
            }
            for (int i = 0; i < 3; ++i) {
                sf::Text number(std::to_string(i+3), font, 60);
                number.setFillColor(purple);
                number.setPosition(buttonWidth*(i*2)+buttonWidth*1.35,(buttonWidth)*2+buttonWidth*0.25);
                window.draw(number);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int mx = event.mouseButton.x;
                int my = event.mouseButton.y;
                sf::FloatRect buttonArea3(buttonWidth,(buttonWidth)*2, buttonWidth, buttonWidth);
                sf::FloatRect buttonArea4(3 * buttonWidth,(buttonWidth)*2, buttonWidth, buttonWidth);
                sf::FloatRect buttonArea5(buttonWidth*5,(buttonWidth)*2, buttonWidth, buttonWidth);
                if (buttonArea3.contains(mx, my)) {
                    parameter = 3;
                    break;
                }
                if (buttonArea4.contains(mx, my)) {
                    parameter = 4;
                    break;
                }
                if (buttonArea5.contains(mx, my)) {
                    if (SIZE != 0 && SIZE == 4) {
                        sf::Text error("Cannot choose 5 for 4x4 board", font, 50);
                        error.setFillColor(pink);
                        error.setPosition(windowMenuSize*0.08,( windowMenuSize/10)+100);
                        window.draw(error);
                    }else {
                        parameter = 5;
                        break;
                    }
                }
            }
            window.display();
        }

}
void menu() {
        int windowMenuSize = 1000;
        sf::RenderWindow window(sf::VideoMode(windowMenuSize, windowMenuSize/2), "Menu");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                    break;
            }
            SIZE =1;
            menuChoices(window,SIZE,"Choose board size:");
            sf::Event flushEvent;
            while (window.pollEvent(flushEvent)) {}
            if (SIZE != 3) {
                menuChoices(window, WIN_CONDITION,"How many to win?");
            }
            game(SIZE, WIN_CONDITION);
        };
}
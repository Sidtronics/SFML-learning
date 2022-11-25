#include <SFML/Window.hpp>
#include <iostream>

int main() {

    sf::Window window(sf::VideoMode(800,600), "Arch-SFML");

    while(window.isOpen()) {
    
        sf::Event event;
        while(window.pollEvent(event)) {
        
            switch(event.type) {

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    
                    if(event.key.code == sf::Keyboard::Escape) {
                        std::cout << "Close Requested...closing\n";
                        window.close();
                    }
                    break;

                default:
                    break;


            }
        }
    }
}

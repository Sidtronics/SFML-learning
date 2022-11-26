#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <thread>

void renderingThread(sf::RenderWindow *window, bool &closingWindow) {

    window->setActive(true);

    sf::Texture marbleTex;
    marbleTex.loadFromFile("res/textures/marble.png");
    marbleTex.setSmooth(true);

    sf::Sprite marbleSpr;
    marbleSpr.setTexture(marbleTex);
    marbleSpr.setOrigin(sf::Vector2f(300.f , 300.f));
    marbleSpr.setPosition(400,300);

    sf::Font font;
    font.loadFromFile("res/fonts/fira-code.ttf");
    sf::Text info, help;
    info.setFont(font);
    info.setCharacterSize(15);
    info.setFillColor(sf::Color::White);

    help.setFont(font);
    help.setCharacterSize(15);
    help.setFillColor(sf::Color::White);
    help.setString("Use arrow keys to move, + - to resize, 1 2 3 to change colour.");
    help.setPosition(5, 580);

    u_char R=255,G=255,B=255;
    float scale = 1.f;
    while(!closingWindow) {
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            marbleSpr.move(0,-1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            marbleSpr.move(0,1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            marbleSpr.move(1,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            marbleSpr.move(-1,0);


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            R++;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            G++;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            B++;
        marbleSpr.setColor(sf::Color(R,G,B));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
            scale += 0.01f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
            scale -= 0.01f;
        marbleSpr.setScale(scale,scale);

        std::stringstream info_ss;
        info_ss << "R: " << +R << "\n" << "G: " 
                << +G << "\n" << "B: " << +B << "\n" << "scale: " << scale;
        info.setString(info_ss.str());

        window->clear(sf::Color::Black);
        window->draw(info);
        window->draw(help);
        window->draw(marbleSpr);
        window->display();
    }

}

int main() {

    sf::RenderWindow window(sf::VideoMode(800,600), "SFML-learning");
    window.setActive(false);

    bool closingWindow = false;
    std::thread Renderer(renderingThread, &window, std::ref(closingWindow));

    while(window.isOpen()) {
    
        sf::Event event;
        while(window.pollEvent(event)) {
        
            switch(event.type) {

                case sf::Event::Closed:
                    closingWindow = true;
                    Renderer.join();
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    
                    if(event.key.code == sf::Keyboard::Escape) {

                        std::cout << "Closing with ESC...\n";
                        closingWindow = true;
                        Renderer.join();
                        window.close();
                    }
                    break;

                default:
                    break;


            }
        }
    }
}

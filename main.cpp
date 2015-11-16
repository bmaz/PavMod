
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text;
    text.setColor(sf::Color::Black);
    
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(29, 29));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(3);
    
    bool  temp = false;
    sf::Vector2i position;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                position = sf::Mouse::getPosition(window);
                temp = true;
            }
        }
        // Clear screen
        window.clear();
        
        std::vector< std::vector< sf::RectangleShape > > rectangleMatrix;
        rectangleMatrix.resize(20, std::vector<sf::RectangleShape>(20, rectangle));
        
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                rectangleMatrix[i][j].setPosition(i*30 + 3, j*30 + 3);
                window.draw(rectangleMatrix[i][j]);
            }
        }
        
        if (temp) {
            text.setString(std::to_string(position.x/30 + 1)+", "+std::to_string(position.y/30 + 1));
            window.draw(text);
            // il faut gerer les index qui sortent du tableau
            rectangleMatrix[position.x/30][position.y/30].setFillColor(sf::Color::Blue);
            rectangleMatrix[position.x/30+1][position.y/30].setFillColor(sf::Color::Blue);
            rectangleMatrix[position.x/30-1][position.y/30].setFillColor(sf::Color::Blue);
            rectangleMatrix[position.x/30][position.y/30+1].setFillColor(sf::Color::Blue);
            // clairement il faut reflechir a une structure de classe pour etre plus efficace
            window.draw(rectangleMatrix[position.x/30][position.y/30]);
            window.draw(rectangleMatrix[position.x/30+1][position.y/30]);
            window.draw(rectangleMatrix[position.x/30-1][position.y/30]);
            window.draw(rectangleMatrix[position.x/30][position.y/30+1]);
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

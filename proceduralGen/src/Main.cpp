#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
    sf::Event event;
    sf::Clock deltaTimeClock;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Procedural Gen");
    ImGui::SFML::Init(window);



    while (window.isOpen())
    {     
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaTimeClock.restart());

        ImGui::Begin("Procedural Generation");
        ImGui::Text("test");
        ImGui::End();

        //Render
        window.clear();

        ImGui::SFML::Render(window);
        window.display();
    }

	return 0;
}
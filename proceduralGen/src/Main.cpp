#include <iostream>
#include <string>

#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <FastNoiseLite/FastNoiseLite.h>

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;
    sf::Event event;
    sf::Clock deltaTimeClock;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Procedural Gen");
    ImGui::SFML::Init(window);

	int offsetX = 0;
	int offsetY = 0;
	int octaves = 5;
	float frequency = 0.025f;

	float amplitude = 1.5;
	float persistance = 0;

	//Create and init image
	srand(time(NULL));
	int seed = rand();

	sf::Image image;
	FastNoiseLite noise(seed);

	image.create(WIDTH, HEIGHT, sf::Color::Red);
	noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
	noise.SetFrequency(frequency);


	for (float y = 0; y < HEIGHT; y++)
	{
		for (float x = 0; x < WIDTH; x++)
		{
			float height = noise.GetNoise(x, y);

			height = height * 255;
			
			image.setPixel(x, y, sf::Color(height, height, height));
		}
	}

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	
	//Main loop
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
		ImGui::Text(std::to_string(seed).c_str());
		ImGui::SliderInt("OffsetX", &offsetX, -1000, 1000);
		ImGui::SliderInt("OffsetY", &offsetY, -1000, 1000);
		ImGui::SliderFloat("Frequency", &frequency, 0.01f, 1);
		ImGui::SliderFloat("Amplitude", &amplitude, 0.1f, 100);

		if (ImGui::Button("Apply"))
		{
			noise.SetFrequency(frequency);
			for (float y = 0; y < HEIGHT; y++)
			{
				for (float x = 0; x < WIDTH; x++)
				{
					float height = noise.GetNoise(x + offsetX, y + offsetY);
					height *= 255;
					height *= amplitude;
					image.setPixel(x, y, sf::Color(height, height, height));
				}
			}
			texture.update(image);
		}
        ImGui::End();

        //Render
        window.clear();
		window.draw(sprite);
        ImGui::SFML::Render(window);
        window.display();
    }

	return 0;
}
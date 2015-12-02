#include <SFML/Graphics.hpp>
#include "const.h"
#include <iostream>
#include <cstdlib>


using namespace sf;
struct RectangleStruct
{
	RectangleShape square;
	RectangleShape square2;
	RectangleShape square3;
	RectangleShape square4;
	RectangleShape square5;
};
struct SecreteStruct
{
	int color;
	int size;
	int move;
	int rotation;
};

void Draw(RenderWindow& window, RectangleStruct Rect[QUANTITY])
{
	for (int i = 0; i < QUANTITY; i++)
	{
		window.draw(Rect[i].square);
	}
	window.display();
	window.clear(sf::Color::White);
}
void InitializationSecret(SecreteStruct& Secret)
{
	Secret.color = 1;
	Secret.move = 1;
	Secret.rotation = 1;
	Secret.size = 1;
}
void InitializationSqure(RectangleStruct(& Rect)[QUANTITY])
{
	for (int i = 0; i < QUANTITY; i++)
	{
		Rect[i].square.setSize(sf::Vector2f(SQURE_SIEZE, SQURE_SIEZE));
		Rect[i].square.setFillColor(Color(255, 0, 0));
		Rect[i].square.setPosition(50 * i, 50);
	}	
}
void ChangeColor(RectangleStruct(&Rect)[QUANTITY], int i, float time)
{
	
	Rect[0].square.setFillColor(Color(255, i* 1 * time, 0));
	Rect[1].square.setFillColor(Color(0, i * 1 * time, i* 1 * time));
	Rect[2].square.setFillColor(Color(0, i* 1 * time, 0));
	Rect[3].square.setFillColor(Color(i* 1 * time, 0, 0));
	Rect[4].square.setFillColor(Color(255, 0, i * 1 * time));
}
void ChangeSize(RectangleStruct(&Rect)[QUANTITY], float j, float time)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		Rect[i].square.setScale(j, j);
	}
}
void StageSelect(int& color_stage, int i, int& size_stage, float j, int& move_stage, RectangleStruct Rect[QUANTITY])
{
	if (i == 256) color_stage = -1;
	if (i == 0) color_stage = 1;
	if (j >= 2) { size_stage = -1; }
	if (j <= 1) { size_stage =  1; }
	if ((Rect[2].square.getPosition().x <= 150) && (Rect[2].square.getPosition().y <= 100)) move_stage = 1;
	if ((Rect[2].square.getPosition().x >= WINDOW_X - 200) && (Rect[2].square.getPosition().y <= 100)) move_stage = 2;
	if ((Rect[2].square.getPosition().x >= WINDOW_X - 200) && (Rect[2].square.getPosition().y >= WINDOW_X - 100)) move_stage = 3;
	if ((Rect[2].square.getPosition().x <= 150) && (Rect[2].square.getPosition().y >= WINDOW_X - 100)) move_stage = 4;

}
void Move(RectangleStruct(&Rect)[QUANTITY], Vector2f speed_move)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		Rect[i].square.move(speed_move.x, speed_move.y);
	}
}
void Rotation(RectangleStruct(&Rect)[QUANTITY], float time)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		Rect[i].square.setRotation(Rect[i].square.getRotation() + (1 * time));
		
	}
}
int main()
{
	struct RectangleStruct Rect[QUANTITY] = {};
	struct SecreteStruct Secret;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ScreenSaver", sf::Style::Default, settings);
	InitializationSqure(Rect);
	Clock clock;
	Clock change_clock;
	srand(time(NULL));
	int secret = 1;
	int i_color = 0;
	int num_turns = 0;
	int color_stage = 1; int size_stage = 1; int move_stage = 1; int stage_rotation = 1;
	float i_size = 1;
	Vector2f speed_move;
	speed_move.x = SPEED;
	speed_move.y = SPEED;
	InitializationSecret(Secret);
	change_clock.restart();
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float time_for_change = change_clock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 1000;
		sf::Event event;
		if (time_for_change >= 5)
		{
			change_clock.restart();
			Secret.color = rand() % 2;
			Secret.move = rand() % 2;
			Secret.rotation = rand() % 2;
			Secret.size = rand() % 2;
		}
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}
		StageSelect(color_stage, i_color, size_stage, i_size, move_stage, Rect);
		if (color_stage == 1) i_color++;
		if (color_stage == -1) i_color--;
		if (size_stage == 1) i_size = i_size + 0.1 * time / 100;
		if (size_stage == -1) i_size = i_size - 0.1 * time / 100;
		if (move_stage == 1) { speed_move.x = SPEED; speed_move.y = 0;}
		if (move_stage == 2) { speed_move.x = 0; speed_move.y = SPEED; }
		if (move_stage == 3) { speed_move.x = -SPEED; speed_move.y = 0; }
		if (move_stage == 4) { speed_move.x = 0; speed_move.y = -SPEED; }
		
		if (Secret.rotation == 1) Rotation(Rect, time);
		if (Secret.color == 1) ChangeColor(Rect, i_color, time);
		if (Secret.size == 1) ChangeSize(Rect, i_size, time);
		if (Secret.move == 1) Move(Rect, speed_move);

		Draw(window, Rect);
	}
	return 0;
}
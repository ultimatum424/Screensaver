#include <SFML/Graphics.hpp>
#include "const.h"
#include <iostream>
#include <cstdlib>


using namespace sf;
typedef struct RectangleStruct
{
	RectangleShape square1;
	RectangleShape square2;
	RectangleShape square3;
	RectangleShape square4;
	RectangleShape square5;
};
typedef struct SecreteStruct
{
	int color;
	int size;
	int move;
	int rotation;
};

void Draw(RenderWindow& window, RectangleStruct Rect)
{
	
	window.draw(Rect.square1);
	window.draw(Rect.square2);
	window.draw(Rect.square3);
	window.draw(Rect.square4);
	window.draw(Rect.square5);
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
void InitializationSqure(RectangleStruct& Rect)
{
	Rect.square1.setSize(sf::Vector2f(squre_sieze, squre_sieze));
	Rect.square1.setFillColor(Color(255, 0 , 0));
	Rect.square1.setPosition(50, 50);

	Rect.square2.setSize(sf::Vector2f(squre_sieze, squre_sieze));
	Rect.square2.setFillColor(Color(255, 0, 0));
	Rect.square2.setPosition(100, 50);

	Rect.square3.setSize(sf::Vector2f(squre_sieze, squre_sieze));
	Rect.square3.setFillColor(Color(255, 0, 0));
	Rect.square3.setPosition(150, 50);

	Rect.square4.setSize(sf::Vector2f(squre_sieze, squre_sieze));
	Rect.square4.setFillColor(Color(255, 0, 0));
	Rect.square4.setPosition(200, 50);

	Rect.square5.setSize(sf::Vector2f(squre_sieze, squre_sieze));
	Rect.square5.setFillColor(Color(255, 0, 0));
	Rect.square5.setPosition(250, 50);
}
void ChangeColor(RectangleStruct& Rect, int i, float time)
{
	
	Rect.square1.setFillColor(Color(255, i* 1 * time, 0));
	Rect.square2.setFillColor(Color(0, i * 1 * time, i* 1 * time));
	Rect.square3.setFillColor(Color(0, i* 1 * time, 0));
	Rect.square4.setFillColor(Color(i* 1 * time, 0, 0));
	Rect.square5.setFillColor(Color(255, 0, i * 1 * time));
}
void ChangeSize(RectangleStruct& Rect, float j, float time)
{
	Rect.square1.setScale(j, j);
	Rect.square2.setScale(j, j);
	Rect.square3.setScale(j, j);
	Rect.square4.setScale(j, j);
	Rect.square5.setScale(j, j);
}
void StageSelect(int& color_stage, int i, int& size_stage, float j, int& move_stage,  RectangleStruct Rect)
{
	if (i == 256) color_stage = -1;
	if (i == 0) color_stage = 1;
	if (j >= 2) { size_stage = -1; }
	if (j <= 1) { size_stage =  1; }
	if ((Rect.square3.getPosition().x <= 150) && (Rect.square3.getPosition().y <= 100)) move_stage = 1;
	if ((Rect.square3.getPosition().x >= window_x - 200) && (Rect.square3.getPosition().y <= 100)) move_stage = 2;
	if ((Rect.square3.getPosition().x >= window_x - 200) && (Rect.square3.getPosition().y >= window_x - 100)) move_stage = 3;
	if ((Rect.square3.getPosition().x <= 150) && (Rect.square3.getPosition().y >= window_x - 100)) move_stage = 4;

}
void Move(RectangleStruct& Rect, Vector2f speed_move)
{
	Rect.square1.move(speed_move.x, speed_move.y);
	Rect.square2.move(speed_move.x, speed_move.y);
	Rect.square3.move(speed_move.x, speed_move.y);
	Rect.square4.move(speed_move.x, speed_move.y);
	Rect.square5.move(speed_move.x, speed_move.y);
}
void Rotation(RectangleStruct& Rect, float time)
{
	Rect.square1.setRotation(Rect.square1.getRotation() + (1 * time));
	Rect.square2.setRotation(Rect.square2.getRotation() - (1 * time));
	Rect.square3.setRotation(Rect.square3.getRotation() + (1 * time));
	Rect.square4.setRotation(Rect.square4.getRotation() - (1 * time));
	Rect.square5.setRotation(Rect.square5.getRotation() + (1 * time));
}
int main()
{
	struct RectangleStruct Rect;
	struct SecreteStruct Secret;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(window_x, window_y), "ScreenSaver", sf::Style::Default, settings);
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
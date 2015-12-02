#include <SFML/Graphics.hpp>
#include "const.h"
#include <iostream>
#include <cstdlib>


using namespace sf;
struct RectangleStruct
{
	RectangleShape square;
};
struct SecreteStruct
{
	int color;
	int size;
	int move;
	int rotation;
};
struct StageStruct
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
void InitializationStage(StageStruct& Stage)
{
	Stage.color = 1;
	Stage.size = 1;
	Stage.move = 1;
	Stage.rotation = 1;
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
void StageSelect(StageStruct& Stage, int i, float j, RectangleStruct Rect[QUANTITY])
{
	if (i == 256) Stage.color = -1;
	if (i == 0) Stage.color = 1;
	if (j >= 2) { Stage.size = -1; }
	if (j <= 1) { Stage.size =  1; }
	if ((Rect[2].square.getPosition().x <= 150) && (Rect[2].square.getPosition().y <= 100)) Stage.move = 1;
	if ((Rect[2].square.getPosition().x >= WINDOW_X - 200) && (Rect[2].square.getPosition().y <= 100)) Stage.move = 2;
	if ((Rect[2].square.getPosition().x >= WINDOW_X - 200) && (Rect[2].square.getPosition().y >= WINDOW_X - 100)) Stage.move = 3;
	if ((Rect[2].square.getPosition().x <= 150) && (Rect[2].square.getPosition().y >= WINDOW_X - 100)) Stage.move = 4;

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
void SceneChange(StageStruct Stage, int& i_color, float& i_size, Vector2f& speed_move, float& time)
{
	if (Stage.color == 1) i_color++;
	if (Stage.color == -1) i_color--;
	if (Stage.size == 1) i_size = i_size + 0.1 * time / 100;
	if (Stage.size == -1) i_size = i_size - 0.1 * time / 100;
	if (Stage.move == 1) { speed_move.x = SPEED; speed_move.y = 0; }
	if (Stage.move == 2) { speed_move.x = 0; speed_move.y = SPEED; }
	if (Stage.move == 3) { speed_move.x = -SPEED; speed_move.y = 0; }
	if (Stage.move == 4) { speed_move.x = 0; speed_move.y = -SPEED; }
}
int main()
{
	struct RectangleStruct Rect[QUANTITY] = {};
	struct SecreteStruct Secret;
	struct StageStruct Stage;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ScreenSaver", sf::Style::Default, settings);
	InitializationSqure(Rect);
	Clock clock;
	Clock change_clock;
	srand(time(NULL));

	InitializationStage(Stage);
	int secret = 1;
	int i_color = 0;
	int num_turns = 0;
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
		if (time_for_change >= TIME)
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
		StageSelect(Stage, i_color, i_size, Rect);
		SceneChange(Stage, i_color, i_size, speed_move, time);
		
		if (Secret.rotation == 1) Rotation(Rect, time);
		if (Secret.color == 1) ChangeColor(Rect, i_color, time);
		if (Secret.size == 1) ChangeSize(Rect, i_size, time);
		if (Secret.move == 1) Move(Rect, speed_move);

		Draw(window, Rect);
	}
	return 0;
}
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

void Draw(RenderWindow& window, RectangleStruct rect[QUANTITY])
{
	for (int i = 0; i < QUANTITY; i++)
	{
		window.draw(rect[i].square);
	}
	window.display();
	window.clear(sf::Color::White);
}
void InitializationStage(StageStruct& stage)
{
	stage.color = 1;
	stage.size = 1;
	stage.move = 1;
	stage.rotation = 1;
}
void InitializationSecret(SecreteStruct& secret)
{
	secret.color = 1;
	secret.move = 1;
	secret.rotation = 1;
	secret.size = 1;
}
void InitializationSqure(RectangleStruct(&rect)[QUANTITY])
{
	for (int i = 0; i < QUANTITY; i++)
	{
		rect[i].square.setSize(sf::Vector2f(SQURE_SIEZE, SQURE_SIEZE));
		rect[i].square.setFillColor(Color(255, 0, 0));
		rect[i].square.setPosition(50 * i, 50);
	}	
}
void ChangeColor(RectangleStruct(&rect)[QUANTITY], int i, float time)
{
	
	rect[0].square.setFillColor(Color(255, i* 1 * time, 0));
	rect[1].square.setFillColor(Color(0, i * 1 * time, i* 1 * time));
	rect[2].square.setFillColor(Color(0, i* 1 * time, 0));
	rect[3].square.setFillColor(Color(i* 1 * time, 0, 0));
	rect[4].square.setFillColor(Color(255, 0, i * 1 * time));
}
void ChangeSize(RectangleStruct(&rect)[QUANTITY], float j, float time)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		rect[i].square.setScale(j, j);
	}
}
void StageSelect(StageStruct& stage, int i, float j, RectangleStruct rect[QUANTITY])
{
	if (i == 256) stage.color = -1;
	if (i == 0) stage.color = 1;
	if (j >= 2) { stage.size = -1; }
	if (j <= 1) { stage.size =  1; }
	if ((rect[2].square.getPosition().x <= 150) && (rect[2].square.getPosition().y <= 100)) stage.move = 1;
	if ((rect[2].square.getPosition().x >= WINDOW_X - 200) && (rect[2].square.getPosition().y <= 100)) stage.move = 2;
	if ((rect[2].square.getPosition().x >= WINDOW_X - 200) && (rect[2].square.getPosition().y >= WINDOW_X - 100)) stage.move = 3;
	if ((rect[2].square.getPosition().x <= 150) && (rect[2].square.getPosition().y >= WINDOW_X - 100)) stage.move = 4;

}
void Move(RectangleStruct(&rect)[QUANTITY], Vector2f speed_move)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		rect[i].square.move(speed_move.x, speed_move.y);
	}
}
void Rotation(RectangleStruct(&rect)[QUANTITY], float time)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		rect[i].square.setRotation(rect[i].square.getRotation() + (1 * time));
		
	}
}
void SceneChange(StageStruct stage, int& i_color, float& i_size, Vector2f& speed_move, float& time)
{
	if (stage.color == 1) i_color++;
	if (stage.color == -1) i_color--;
	if (stage.size == 1) i_size = i_size + 0.1 * time / 100;
	if (stage.size == -1) i_size = i_size - 0.1 * time / 100;
	if (stage.move == 1) { speed_move.x = SPEED; speed_move.y = 0; }
	if (stage.move == 2) { speed_move.x = 0; speed_move.y = SPEED; }
	if (stage.move == 3) { speed_move.x = -SPEED; speed_move.y = 0; }
	if (stage.move == 4) { speed_move.x = 0; speed_move.y = -SPEED; }

	
}
void SecretChange(SecreteStruct& secret)
{
	secret.color = rand() % 2;
	secret.move = rand() % 2;
	secret.rotation = rand() % 2;
	secret.size = rand() % 2;
}
void RunProgram(RenderWindow& window)
{
	RectangleStruct rect[QUANTITY] = {};
	SecreteStruct secret;
	StageStruct stage;
	InitializationSqure(rect);
	Clock clock;
	Clock change_clock;
	srand(time(NULL));

	InitializationStage(stage);
	int secret_stage = 1;
	int i_color = 0;
	int num_turns = 0;
	float i_size = 1;

	Vector2f speed_move;
	speed_move.x = SPEED;
	speed_move.y = SPEED;

	InitializationSecret(secret);

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
			SecretChange(secret);
		}
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}
		StageSelect(stage, i_color, i_size, rect);
		SceneChange(stage, i_color, i_size, speed_move, time);

		if (secret.rotation == 1) Rotation(rect, time);
		if (secret.color == 1) ChangeColor(rect, i_color, time);
		if (secret.size == 1) ChangeSize(rect, i_size, time);
		if (secret.move == 1) Move(rect, speed_move);

		Draw(window, rect);
	}
}
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ScreenSaver", sf::Style::Default, settings);
	RunProgram(window);
	return 0;
}
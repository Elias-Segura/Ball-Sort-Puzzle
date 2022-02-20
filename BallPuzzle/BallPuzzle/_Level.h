#pragma once
#include<iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "stack.h"
#include "space_stack.h"
#include "LinkedList.h"
#include "Tube.h"
#include "Options.h"
#include "_Main.h"
#include <vector>
#include <future>
#include <thread>
#include <chrono>
#include "Level.h"
#include <fstream>
#include "SaveGame.h"
#include "savedGame.h"



using namespace std;
using namespace sf; 
class _Level
{

private:

	Options* op;
	SoundBuffer bf;
	Sound sn;
	Tube tube;
	LinkedList list{};
	RenderWindow* window;
	VideoMode videoMode;
	Event* ev;
	Texture texture;
	Texture _tube;
	Texture* level;
	Vector2i mousePosition;
	bool state{ false };
	bool selectNextLevel{ false };
	int nWin{ 0 };
	int nLevel{ 0 };
	int NWIN[12] = { 2,3,3,5,5,5,5,7,7,7,5,7 };
	const int* Levels[3] = {
		LEVEL_1,
		LEVEL_2,
		LEVEL_3

	};
	string nBall[7] = {
	RED,
	YELLOW,
	GREEN,
	BLUE,
	CYAN,
	ORANGE,
	PURPLE
	};
	string TITLES[12] = {
		TITLE_LEVEL_1,
		TITLE_LEVEL_2,
		TITLE_LEVEL_3,
		TITLE_LEVEL_4,
		TITLE_LEVEL_5,
		TITLE_LEVEL_6,
		TITLE_LEVEL_7,
		TITLE_LEVEL_8,
		TITLE_LEVEL_9,
		TITLE_LEVEL_10,
		TITLE_LEVEL_11,
		TITLE_LEVEL_12
	};
	String Colors[6] = { "Red", "Yellow", "Green", "Blue","Cyan", "Orange" };
	string _LEVELS[12] = { "Nivel_1.txt" , "Nivel_2.txt", "Nivel_3.txt", "Nivel_4.txt", "Nivel_5.txt", "Nivel_6.txt", "Nivel_7.txt", "Nivel_8.txt", "Nivel_9.txt","Nivel_10.txt", "Nivel_11.txt", "Nivel_12.txt" };
	double Size = 54;
	fstream archivo;
	bool Sound{ true }; 
public:
	_Level(RenderWindow* window, int Level, int nWin, vector<savedGame> movements, int backCount, bool sound);





	~_Level();
	void loadLevel();
	void Run();
	void DrawElement();
	void pollEvents();
	void updateEvents();
	void MousePosition();
	void loadNextLevel();
	Tube* createTube(); 
	Texture* createBall(string color);
};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Definitions.h"
#include <future>
#include <thread>
#include <chrono>
#include "_Level.h"
#include <fstream>
#include <vector>
#include "savedGame.h"

using namespace sf;
using namespace std; 

class _Main
{
private: 

	fstream file; 
	vector<savedGame> movements{}; 


	RenderWindow* window; 
	Texture* background;
	Texture* pmain;
	Texture* txLevels; 
	Texture* txMainLevel; 
	Texture* txContinue; 
	Texture* txSound; 

	Sprite* MainLevel; 
	Sprite* btnLevels; 
	Sprite* _background;
	Sprite* Pmain;
	Sprite* btnContinue; 
	Sprite* btnSound; 

	Vector2i mousePosition; 

	Texture* txClose;
	Sprite* btnClose; 

	Texture* txBackMain;
	Sprite* btnBackMain;

	Texture* tx_Level[12]; 
	Sprite* levels[12];
	Event* ev;
	bool state{ false };
	bool showing{ true };
	bool showingLevel{ false };
	bool stateLevel{ false };
	bool continueGame{ false }; 
	bool sound{ false }; 
	int n;
	int nLevel{ 0 }; 
	int back_count{ 0 }; 
	Texture l[5];
	int NWIN[12] = {2,3,3,5,5,5,5,7,7,7,5,7};

public: 

	 _Main(RenderWindow* Rwindow);
	 ~_Main() {};



	void Run();
	void pollEvents();
	void levelEvents();
	void MousePosition();
	void updateEvents();
	void DrawElements();
	void DrawMainLevel();
	void loadLevel();
	void loadLevelSprites();
	bool loadTimer();
	bool checkFileIsEmpty(string archivo);




};


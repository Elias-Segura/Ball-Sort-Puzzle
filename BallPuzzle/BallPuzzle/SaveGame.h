#pragma once
#include <iostream>
#include <vector>
#include "Queue.h"
#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>


using namespace std; 
using namespace sf;

class SaveGame
{
private: 

	RenderWindow* window; 
	Event* ev; 
	Vector2i mouseposition; 
	vector<Queue> movements{}; 


	Texture* txTSave; 
	Texture* txYes; 
	Texture* txNo; 

	Sprite* tSave; 
	Sprite* btnNo;
	Sprite* btnYes; 
	ofstream archivo;
	fstream leer;
	int nLevel{ 0 };
	int back_count{ 0 }; 
	string SAVED[1] = { "SavedGame.txt" }; 

public: 

	SaveGame(vector<Queue>  q, RenderWindow * w, int nLevel, int backCount);
	~SaveGame();

	void Run();
	void Draw();
	void pollEvents(); 
	void UpdateEvents();
	void MousePosition();
	void Save();


};


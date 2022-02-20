#pragma once
#include <SFML/Graphics.hpp>
#include "LinkedList.h"
#include "Definitions.h"
#include "Queue.h"
#include <vector>
#include "SaveGame.h"
using namespace sf; 
class Options
{
private: 

	RenderWindow* window; 
	Event* event; 
	Texture* txMain; 
	Sprite* btnMain;
	Texture* txRestart;
	Sprite* btnRestart;
	Texture* txBack; 
	Sprite* btnBack; 
	Sprite* level;
	Texture* txClose;
	Sprite* btnClose; 
	Texture* txPlay; 
	Sprite* btnPlay; 
	Texture* txNext; 
	Sprite* btnNext;
	Texture* backGround;
	Sprite* bground; 
	Vector2f scale; 
	Event* ev; 
	int back_count{ 5 }; 
	bool state{ false };
	bool repeat{ false };
	bool restart{ false }; 
	bool nextLevel{ false };
	bool showing{ true };
	bool showOption{ false }; 
	bool stateScale{ false }; 
	string n[6] = 
	{ 
			BACK_COUNT_0,
			BACK_COUNT_1,
			BACK_COUNT_2,
			BACK_COUNT_3,
			BACK_COUNT_4,
			BACK_COUNT_5 
	};
	
public: 
	Options(RenderWindow* window, Texture* texture);
	~Options();
	void loadOptions();
	void DrawOptions(LinkedList& lista);
	void pollEvents(Vector2i mousePosition,Event* ev, LinkedList & lista, RenderWindow* window,  int nLevel);
	void setCount();
	bool getRepeat();
	void setRepeat();
	bool getRestart();
	void setRestart(bool x);
	bool getShowing();
	bool getNextLevel();
	void setNextLevel();
	void MouseHover(Vector2i mousePosition, Sprite* option);
	void NextLevel(); 
	int getBackCount();
	void setBackCount(int backCount);
};


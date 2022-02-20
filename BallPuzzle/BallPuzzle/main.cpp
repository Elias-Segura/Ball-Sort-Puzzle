
#include <iostream>;
#include "stack.h"; 
#include <string>;
#include "space_stack.h";
#include <SFML/Graphics.hpp>;
#include "_Main.h"


using namespace std;

int main() {

    	Image icon;
    	icon.loadFromFile("../Resources/Icon.png"); 
    
    	RenderWindow window(VideoMode(630, 700), "Ball Sort Puzzle", sf::Style::Close | sf::Style::Titlebar);
    	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    	_Main* m;
    	m = new _Main(&window);
    	
    


    
	return 0;
}
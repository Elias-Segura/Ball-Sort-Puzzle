#include "Options.h"

Options::Options(RenderWindow* window, Texture* texture)
{
	
	this->window = window;
	

	txMain = new Texture();
	txRestart = new Texture();
	txBack = new Texture();
	txClose = new Texture();
	txPlay = new Texture();
	txNext = new Texture();
	backGround  = new Texture();


	backGround->loadFromFile(BACKGROUND_OPTIONS);
	txMain->loadFromFile(BTN_MAIN); 
	txRestart->loadFromFile(BTN_RESTART);
	txBack->loadFromFile(n[back_count]);
	txClose->loadFromFile(BTN_CLOSE);
	txPlay->loadFromFile(PLAY);
	txNext->loadFromFile(NEXT_LEVEL); 

	btnBack = new Sprite();
	btnMain = new Sprite();
	btnRestart = new Sprite();
	btnClose = new Sprite();
	
	level = new Sprite();
	bground = new Sprite();


	btnMain->setTexture(*txMain);
	btnRestart->setTexture(*txRestart); 
	btnBack->setTexture(*txBack);
	btnClose->setTexture(*txClose);

	scale = btnClose->getScale();
	bground->setTexture(*backGround);
	level->setTexture(*texture); 

	
	loadOptions();
}

void Options::loadOptions() {
	
	for (int i = 0; i < 13; i++) {
		if (i == 2) {
			btnMain->setPosition((35 * i), 0); 
		}
		if (i == 4) {
			btnRestart->setPosition((32 * i), 0);
		}
		if (i == 7) {
			
			btnBack->setPosition((60 * i), 0);

		}
		if (i == 8) {
			btnClose->setPosition((60 * i), 0);
		}
		if (i == 5) {
			level->setPosition((45 * i), 30);
			
		}
	}
}
void Options::DrawOptions(LinkedList& lista) {

	
	this->window->draw(*btnMain);
	this->window->draw(*btnRestart);
	this->window->draw(*btnBack);
	this->window->draw(*btnClose);
	this->window->draw(*level);
	if (lista.Win()) {
	
		if (!showOption) {
			
			std::future<int> future = std::async(std::launch::async, []() {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return 4;
				});

			std::cout << "waiting...\n";
			std::future_status status;
			do {
				status = future.wait_for(std::chrono::seconds(1));
				if (status == std::future_status::deferred) {
			
				}
				else if (status == std::future_status::timeout) {
			
				}
				else if (status == std::future_status::ready) {
					
					btnNext = new Sprite();
					btnPlay = new Sprite();
					btnPlay->setTexture(*txPlay);
					btnNext->setTexture(*txNext);
					btnPlay->setPosition((40 * 5), 400);
					btnNext->setPosition((60 * 5), 400);
					showOption = true;

				}
			} while (status != std::future_status::ready);
		}
		else {
		
			bground->setPosition(315, 300);
			bground->setOrigin(bground->getTexture()->getSize().x / 2, bground->getTexture()->getSize().y / 2);
			this->window->draw(*bground);
			
			this->window->draw(*btnNext);
			this->window->draw(*btnPlay);
			
		}
		
	
		
	}

}
void Options::MouseHover(Vector2i mousePosition, Sprite* option) {


		if (option->getGlobalBounds().intersects(FloatRect(Vector2f(mousePosition), { 1,1 }))) {
			if (!stateScale && option->getScale().y <= scale.y + 0.03f) {
				option->setScale(option->getScale().x, option->getScale().y + 0.03f);
				stateScale = true;
			}
		}
		else {
			
			option->setScale(option->getScale().x, scale.y);
			
			
		}

	
	stateScale = false;

}
void Options::pollEvents(Vector2i mousePosition,Event* ev, LinkedList & lista, RenderWindow* window, int nLevel) {
	MouseHover(mousePosition, btnClose);
	MouseHover(mousePosition, btnBack);
	MouseHover(mousePosition, btnRestart);
	MouseHover(mousePosition, btnMain);
	if (ev->type == Event::MouseButtonPressed) {
		if (ev->key.code == Mouse::Left) {

		
			if (!lista.Win() && !repeat && btnClose->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
				if (lista.getVector().empty()) {
					this->window->close();
				}
				else {
					SaveGame s(lista.getVector(), window, nLevel, back_count);
				}
			}
			if (!lista.Win() && !repeat && btnMain->getGlobalBounds().contains(mousePosition.x, mousePosition.y) ){
				showing= false;
			}
			if (!lista.Win() && !repeat && btnBack->getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !state && back_count>0) {
				bool result = lista.BackMovement();
				if (result == true) {
					back_count--;
					txBack->loadFromFile(n[back_count]);
					btnBack->setTexture(*txBack);
				}
				state = true;
			
			}
			if (!lista.Win() && !repeat && btnRestart->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
				restart = true;
			}
			if (btnPlay != NULL && btnNext != NULL && showOption) {
				if (btnNext->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					lista.Clear(true);
					nextLevel = true;
				}
				if (lista.Win() && btnPlay->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {


					repeat = true;
				}
			}
		}
	}
	if (ev->type == Event::MouseButtonReleased) {
		if (ev->key.code == Mouse::Left) {
			state = false; 
			
		}
	}
}
void Options::setCount() {
	back_count = 5;
	txBack->loadFromFile(n[back_count]);
	btnBack->setTexture(*txBack);
}
bool Options::getRepeat() {
	return repeat;
}
void Options::setRepeat() {
	repeat = false;
}
bool Options::getRestart() {
	return restart; 
}
void Options::setRestart(bool x) {
	restart = x;
}

bool Options::getShowing() {
	return showing;
}
bool Options::getNextLevel() {
	return nextLevel;
}
void Options::setNextLevel() {
	nextLevel = false;
}
void Options::NextLevel() {
	back_count= 5;
	state = false;
	repeat=false ;
	 restart= false ;
	 nextLevel= false ;
	 showing= true ;
	 delete(btnPlay);
	 delete(btnNext);
}
void Options::setBackCount(int backCount) {
	back_count = backCount;
	txBack->loadFromFile(n[back_count]);
	btnBack->setTexture(*txBack);
}
int Options::getBackCount() {
	return back_count;
}
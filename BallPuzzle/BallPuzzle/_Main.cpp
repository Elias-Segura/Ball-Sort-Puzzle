#include "_Main.h"

_Main::_Main(RenderWindow* Rwindow) {
	ev = new Event(); 

	continueGame = checkFileIsEmpty("SavedGame.txt");

	this->window = Rwindow; 

	 background = new Texture();
	 pmain = new Texture();
	 txLevels = new Texture();
	 txMainLevel = new Texture();
	 txClose = new Texture();
	 txBackMain = new Texture();
	 txContinue = new Texture();
	 txSound = new Texture();

	pmain->loadFromFile(PMAIN);
	background->loadFromFile(MAIN_1);
	txLevels->loadFromFile(LEVELS);
	txMainLevel->loadFromFile(LEVELMAIN);
	txClose->loadFromFile(CLOSE);
	txBackMain->loadFromFile(BACK_MAIN);
	txContinue->loadFromFile(CONTINUE); 



	
	checkFileIsEmpty("Sound.txt") ? txSound->loadFromFile(SOUND): txSound->loadFromFile(NSOUND);
	sound = checkFileIsEmpty("Sound.txt");

	_background = new Sprite();
	Pmain = new Sprite();
	btnLevels = new Sprite();
	MainLevel = new Sprite();
	btnClose = new Sprite();
	btnBackMain = new Sprite();
	btnContinue = new Sprite();
	btnSound = new Sprite();


	btnClose->setTexture(*txClose);
	btnLevels->setTexture(*txLevels);
	Pmain->setTexture(*pmain);
	_background->setTexture(*background);
	MainLevel->setTexture(*txMainLevel);
	btnBackMain->setTexture(*txBackMain); 
	btnContinue->setTexture(*txContinue); 
	btnSound->setTexture(*txSound); 


	//posicion en ventana
	btnLevels->setPosition(170, 160);
	btnSound->setPosition(170, 230); 
	btnContinue->setPosition(170, 300);

	_background->setPosition(315, 300);
	Pmain->setPosition(315, 300);
	MainLevel->setPosition(315, 300);
	btnClose->setPosition(412.5, 132);

	//posicionar en el centro

	_background->setOrigin(_background->getTexture()->getSize().x / 2, _background->getTexture()->getSize().y / 2);

	Pmain->setOrigin(Pmain->getTexture()->getSize().x / 2, Pmain->getTexture()->getSize().y / 2);
	MainLevel->setOrigin(MainLevel->getTexture()->getSize().x / 2, MainLevel->getTexture()->getSize().y / 2);

	n = 0;
	loadLevel();
	loadLevelSprites();
	Run();

}
void _Main::Run() {
	  
	while (this->window->isOpen()) {
		window->clear();
		DrawElements();
		DrawMainLevel();
		updateEvents();
		window->display();


	}

}
void _Main::DrawMainLevel() {
	if (showing && showingLevel ) {
	
		this->window->draw(*MainLevel);
		this->window->draw(*btnBackMain);

		for (int j = 0; j < 12; j++) {
			this->window->draw(*levels[j]);
		}
		
	}

}
bool _Main::loadTimer() {
	background->loadFromFile(MAIN_1);
	_background->setTexture(*background);
	this->window->draw(*_background);
	std::future<int> future = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return 1;
		});

	std::cout << "waiting...\n";

	
	std::future_status status;
	do {
		status = future.wait_for(std::chrono::seconds(1));
		if (status == std::future_status::deferred) {
		
			std::cout << "deferred\n";
		}
		else if (status == std::future_status::timeout) {
			
			std::cout << "timeout\n";
		}
		else if (status == std::future_status::ready) {
			
			return true;

		}
	} while (status != std::future_status::ready);
	return false;
}
void _Main::DrawElements() {
	if (showing && !showingLevel) {
		if (!state) {
			loadTimer();
			
			if (n ==1)  {
				background->loadFromFile(MAIN_1);
				_background->setTexture(*background);
				this->window->draw(*_background);
			}
			else if (n==2) {
				background->loadFromFile(MAIN_2);
				_background->setTexture(*background);
				this->window->draw(*_background);
			}
			else if (n==3) {
				background->loadFromFile(MAIN);
				_background->setTexture(*background);
				this->window->draw(*_background);
			}else if (n == 4) {
				background->loadFromFile(MAIN_1);
				_background->setTexture(*background);
				this->window->draw(*_background);
			}
			else if (n == 5) {
				background->loadFromFile(MAIN_2);
				_background->setTexture(*background);
				this->window->draw(*_background);
			}
			else if (n == 6) {
				background->loadFromFile(MAIN);
				_background->setTexture(*background);
				this->window->draw(*_background);
			}
			
			
			if (n > 6) {
				state = true;
			}
			n++;
		}
		else {
			this->window->draw(*Pmain);
			this->window->draw(*btnClose);
			this->window->draw(*btnLevels);
			this->window->draw(*btnSound);

			if (continueGame)
			{
				this->window->draw(*btnContinue);
			}

		}
	}

}
bool _Main::checkFileIsEmpty(string archivo) {

	fstream file(archivo); 

	if (!file.is_open()) {
		cout << "Error" << endl; 
		return false;
	}
	file.seekg(0, ios::end); 
	unsigned int Size = file.tellg();
	if (!Size) {
		cout << "Empty File" << endl; 
		return false; 
	}
	else {
		return true; 
	}



}
void _Main::updateEvents() {
	if (showing) {
		pollEvents();
		levelEvents();
		MousePosition();
	}

}
void _Main::levelEvents() {

	if (stateLevel && ev->type == Event::MouseButtonPressed) {
		if (ev->key.code == Mouse::Left) {
			for (int i = 0; i < 12; i++) {
				if (levels[i]->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					showing = false;
					_Level _Level(window, i, NWIN[i], movements, back_count, sound);
				}
			}
		}
	  }

}
void _Main::pollEvents() {
	while (this->window->pollEvent(*ev)) {
		switch (this->ev->type) {
		case Event::Closed:
			this->window->close();
		case Event::MouseButtonPressed:
			if (ev->key.code == Mouse::Left) {

				if (showingLevel) {
					stateLevel = true;
				}
				if (btnLevels->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

					showingLevel = true;
				
				}
				if (btnSound->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

					if (checkFileIsEmpty("Sound.txt")) {
						txSound->loadFromFile(NSOUND);
						btnSound->setTexture(*txSound);
						try {
							file.open("Sound.txt", std::ofstream::out | std::ofstream::trunc);
							file.close();
						}
						catch (exception) {
							cout << "" << endl; 
						}
						sound = false;
					}
					else {
						ofstream writeFile("Sound.txt");

						if (writeFile.is_open()) {
							writeFile << 1 << "";
						}
						writeFile.close();

						txSound->loadFromFile(SOUND);
						btnSound->setTexture(*txSound);
						sound = true;
					}
					
					
				}
				if (!showingLevel && btnClose->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					this->window->close();
				}
				if (btnBackMain->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					showingLevel = false;
					stateLevel = false;
				}
				if (continueGame && btnContinue->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

					file.open("SavedGame.txt", ios::in);


					if (file.fail()) {
						cout << "The file doesnt exists" << endl;
					}
					else {

						bool state = false;
						while (!file.eof()) {
							if (!state) {
								file >> nLevel;
								file >> back_count; 
								state = true;
							}
							else {
								savedGame* move = new savedGame();
								file >> move->lastId;
								file >> move->newId;

								movements.push_back(*move);

							}
						}

					}
					file.close();
					_Level _Level(window, nLevel, 0, movements, back_count, sound);
				}




	
			}

		}
		

	}
}
void _Main::MousePosition() {
	mousePosition = Mouse::getPosition(*window);
}
void _Main::loadLevel() {
	string level[12] = { L_1, L_2, L_3, L_4, L_5, L_6,L_7,L_8,L_9,L_10,L_11,L_12 };
	for (int i = 0; i < 12; i++) {
		tx_Level[i] = new Texture();
		tx_Level[i]->loadFromFile(level[i]);
		levels[i] = new Sprite();
	}
}
void _Main::loadLevelSprites() {


	

	int n = 143;
	int k = 180; 
	for (int j = 0; j < 12; j++) {
		levels[j]->setTexture(*tx_Level[j]);
		levels[j]->setPosition(k,n);
		
		k = k + 90;
		if (k >= 420) {
			n = n + 80;
			k = 180;
		}
	}
}
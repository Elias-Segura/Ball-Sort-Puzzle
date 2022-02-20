#include "SaveGame.h"

SaveGame::SaveGame(vector<Queue> q, RenderWindow* w, int nLevel, int backCount) {

	txNo = new Texture();
	txTSave = new Texture();
	txYes = new Texture();


	txNo->loadFromFile(NO); 
	txYes->loadFromFile(YES); 
	txTSave->loadFromFile(TITLE_SAVE); 

	tSave = new Sprite(); 
	btnNo = new Sprite;
	btnYes = new Sprite();

	tSave->setTexture(*txTSave); 
	btnYes->setTexture(*txYes); 
	btnNo->setTexture(*txNo); 


	tSave->setPosition(315, 300);
	tSave->setOrigin(tSave->getTexture()->getSize().x / 2, tSave->getTexture()->getSize().y / 2);

	btnNo->setPosition(210, 330);
	
	btnYes->setPosition(300, 330);



	this->window = w;
	this->ev = new Event();
	this->movements = q; 

	this->nLevel = nLevel;
	this->back_count = backCount; 

	Run();

}
SaveGame::~SaveGame() {}
void SaveGame::Run() {

	while (this->window->isOpen()) {

		window->clear();
		Draw(); 
		UpdateEvents();


		window->display();


	}

}

void SaveGame::pollEvents() {
	while (this->window->pollEvent(*ev)) {
		switch (this->ev->type) {
		case Event::Closed:
			this->window->close();

		case Event::MouseButtonPressed:
			if (ev->key.code == Mouse::Left) {

				if (btnNo->getGlobalBounds().contains(mouseposition.x, mouseposition.y)) {

					this->window->close();

				}

				if (btnYes->getGlobalBounds().contains(mouseposition.x, mouseposition.y)) {
			
					Save();
	
				}
			}

		}
	
	}

}
void SaveGame::Save() {

	std::ofstream writeFile("SavedGame.txt");

	if (writeFile.is_open())
	{
		if (!movements.empty()) {
			writeFile << std::to_string(nLevel) << " "; 
			writeFile << std::to_string(back_count)<< " "; 
			for (auto j = movements.begin(); j != movements.end(); j++) {
				writeFile << std::to_string(j->lastId) << " " << std::to_string(j->newId)<< " ";
			}
			cout << "saved..." << endl;
		

		}
		else {
			writeFile << "";
		}
	}
	else {
		cout << "Can not open file." << endl;
	}

	writeFile.close();
	this->window->close();


}
void SaveGame::MousePosition() {
	this->mouseposition = Mouse::getPosition(*window);

}
void SaveGame::UpdateEvents() {
	pollEvents();
	MousePosition();
}

void SaveGame::Draw() {

	this->window->draw(*tSave); 
	this->window->draw(*btnNo);
	this->window->draw(*btnYes);
}

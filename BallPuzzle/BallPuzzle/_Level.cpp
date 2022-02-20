#include "_Level.h"

_Level::_Level(RenderWindow* Rwindow, int nLevel, int nWin, vector<savedGame> movements, int backCount, bool sound) {
	
	 this->nLevel = nLevel;
	 this->nWin = nWin;
	 Sound = sound; 
	 texture.loadFromFile(BALLS);
	 _tube.loadFromFile(TUBE);
	 level = new Texture();
	 level->loadFromFile(TITLES[nLevel]);
	 op = new Options(Rwindow, level);
	 loadLevel();
	 this->window = Rwindow;
	
	 if (!bf.loadFromFile("moving.wav")) {
		cout << "NotFound" << endl;
	 }
	 this->sn.setBuffer(bf);
	
	 this->window->setFramerateLimit(60); 
	 this->ev = new Event(); 
	
	 if (!movements.empty()) { //cargar partida guardada
		this->nWin = NWIN[nLevel]; 
		list.loadSavedGame(movements);
		op->setBackCount(backCount);
		archivo.open("SavedGame.txt", std::ofstream::out | std::ofstream::trunc);
		archivo.close();
	 }

	 Run(); 
}
 _Level::~_Level(){}
 void _Level::loadLevel() {




	 archivo.open(_LEVELS[nLevel].c_str(), ios::in);

	 int level[13][11];
	 if (archivo.fail()) {
		 cout << "The file doesnt exists" << endl;
	 }
	 else {
		 for (int i = 0; i < 13; i++) {
			 for (int j = 0; j < 11; j++) {
				 archivo >> level[i][j];
			 }
		 }
	 }
	 archivo.close();

	 int index = 4, value, n = 150;
	 Tube* tube = createTube();
	 for (int i = 0; i < 11; i++) {
		 for (int j = 12; j >= 0; j--) {
			 if (level[j][i] == -1) {
				 tube->space[index].setPosition(((Size + 2) * i) + 10, (Size + 2) * j);
				 tube->space[index].setSize(Vector2f(Size, Size));
				 tube->space[index].setFillColor(Color::Transparent);
				 index--;
			 }
			 else {
				 if (level[j][i] != 0) {
					 tube->state = true;
					 tube->space[index].setPosition(((Size + 2) * i) + 10, (Size + 2) * j);
					 tube->space[index].setSize(Vector2f(Size, Size));
					 tube->space[index].setFillColor(Color::Transparent);
					 Element_stack* element = new Element_stack();
					 value = level[j][i] - 1;
					 element->color = level[j][i];
					 element->mysprite = new Sprite();
					 element->mysprite->setPosition(((Size + 2) * i) + 15, (Size + 2) * j);
					 element->mysprite->setTexture(*createBall(nBall[value]));
					 element->lastPos = element->mysprite->getPosition();
					 element->Origen = element->mysprite->getOrigin();
					 tube->stack.Push(*element);
					 index--;
				 }

			 }

			 if (index == -1) {
				 j >= 7 ? n = n + 280 : n = 150;
				 tube->tube = new Sprite();
				 tube->tube->setPosition(((Size + 2) * i) - 10.5, n);
				 tube->tube->setTexture(_tube);
				 list.insertHead(*tube);
				 tube = createTube();
				 index = 4;
			 }
		 }
	 }
 }

Texture* _Level::createBall(string color) {
	Texture* ball = new Texture();
	ball->loadFromFile(color);
	return ball;
}
Tube* _Level::createTube() {
		Tube* tube = new Tube();
		return tube;
}
void _Level::Run() {
	while (this->window->isOpen()) {
		
		this->window->clear();
		loadNextLevel();
		if (op->getShowing()) {
			DrawElement();
			updateEvents();
		}
		else {
			_Main* m;
			m = new _Main(window);

		}
		
		this->window->display();
		
	}

}
void _Level::DrawElement() {

	if (!op->getRepeat()) {

	
			
			list.Draw(window);
		
		
		op->DrawOptions(list);
		if (Sound) {
			list.PlaySound();
		}
		//Reiniciar partida
		if (op->getRestart()) {
			list.Clear(true);
			
			op->setRestart(false);
		}
		if (list.isEmpty()) {
			_Level::loadLevel();
			op->setCount();
		}
	}
	else {

		//se reinicia el juego para empezar la repeticion. 
		if (!state) {
			list.Clear(false);
			if (list.isEmpty()) {
				_Level::loadLevel();
				op->setCount();
				list.Draw(window);
				op->DrawOptions(list);
			}
			state = true;
		}
		else {
				//Repeticion 
				
				
				  if (!list.RepeatCompleted()) {

					  //Si repetir aún no esta completado se recorre el vector por tiempos

					  std::future<int> future = std::async(std::launch::async, []() {
						  std::this_thread::sleep_for(std::chrono::seconds(1));
						  return 4;
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


							  list.ShowVector();
						  }
					  } while (status != std::future_status::ready);
				
					 
					}
				  list.Draw(window);
				  op->DrawOptions(list);
				  op->pollEvents(mousePosition, ev, list, window, nLevel);
		}

	}
	
}
void _Level::pollEvents() {
	while (this->window->pollEvent(*ev)) {
		switch (this->ev->type) {
		case Event::Closed:
			if (list.getVector().empty()) {
				this->window->close(); 
			}
			else {
				SaveGame s(list.getVector(), window, nLevel,op->getBackCount());
			}

		}
	}
}
void _Level::MousePosition() {
	this->mousePosition = Mouse::getPosition(*window); 

}
void _Level::updateEvents() {
	
	pollEvents();
	MousePosition();
	if (!list.Win() && !op->getRepeat()) {
		list.CheckIntersect(*ev, mousePosition, bf);
	}
	op->pollEvents(mousePosition, ev, list, window, nLevel);
	list.isStackCompleted(nWin);



}

void _Level::loadNextLevel() {
	if (!op->getNextLevel()) {
		selectNextLevel = false;
	}
	if (!selectNextLevel && op->getNextLevel()) {


		list.Clear(true);
		if (list.isEmpty() ) {
			
			if (nLevel + 1 <= 11) {
				nLevel += 1;
				nWin = NWIN[nLevel];
				state = false;
				level->loadFromFile(TITLES[nLevel]);
				selectNextLevel = true;
				level->loadFromFile(TITLES[nLevel]);
				op = new Options(window, level);
				op->setRestart(true);
			}
			else {

				_Main* m;
				m = new _Main(this->window);

			}
		

		}
	}
	
}

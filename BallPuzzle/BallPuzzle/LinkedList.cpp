#include "LinkedList.h"

bool LinkedList::BackMovement() {

    Nodo* lastStack = head;
    Nodo* newStack = head;
    bool found = false;
    while (lastStack && queue->last) {

        if (queue->last->lastId == lastStack->id) {
            while (newStack) {

                if (queue->last->newId == newStack->id) {
                    auto top = lastStack->dato.stack;
                    auto p = newStack->dato.stack.Pop();
                    int n = 4;
                    for (int j = 4; j >= 1; j--) {
                        if (!top.isEmpty()) {
                            top.Pop();
                            n--;
                        }
                    }
                    auto pos = lastStack->dato.space[n].getPosition();
                    p.mysprite->setPosition(pos.x + 5, pos.y + 5);
                    p.lastPos = p.mysprite->getPosition();
                    lastStack->dato.stack.Push(p);

                    Queue* move = new Queue();
                    move->id = m++;
                    move->lastId = queue->last->newId;
                    move->newId = queue->last->lastId;

                    movements.push_back(*move);
                    Queue* actual = queue->first;
                    Queue* r = NULL;

                    while (actual) {
                        if (actual != queue->last) {
                            r = actual;

                        }
                        actual = actual->next;
                    }

                    if (r) {
                        r->next = NULL;

                    }
                    queue->last = r;
                    queue->last ? queue->first = queue->first : queue->first = NULL;
                    found = true;
                    return true;

                }
                found ? newStack = NULL : newStack = newStack->next;
            }
        }

        found ? lastStack = NULL : lastStack = lastStack->next;
    }
    return false;

}
void LinkedList::SaveMovement(int  lastStack, int newStack) {

    Queue* move = new Queue();

    move->lastId = lastStack;
    move->newId = newStack;
    move->id = m;
    m++;
    move->next = NULL;

    movements.push_back(*move);

    if (!queue->first) {

        queue->first = queue->last = move;
    }
    else {
        queue->last->next = move;
        queue->last = move;
    }


}
vector<Queue> LinkedList::getVector() {
    return movements;
}
bool LinkedList::Win() {
    return isCompleted;
}
bool LinkedList::RepeatCompleted() {
    return movements.empty() ? false : movements.back().state;
}
void LinkedList::loadSavedGame(vector<savedGame> movements) {
    Nodo* lastStack = NULL;
    Nodo* newStack = NULL;

    for (auto j = movements.begin(); j != movements.end(); j++) {

        if (j->lastId != j->newId) {
            lastStack = head;

            while (lastStack) {


                if (j->lastId == lastStack->id) {

                    newStack = head;

                    while (newStack) {


                        if (j->newId == newStack->id) {

                            SaveMovement(j->lastId, j->newId);

                            auto top = newStack->dato.stack;
                            auto p = lastStack->dato.stack.Pop();
                            int n = 4;
                            for (int j = 4; j >= 1; j--) {
                                if (!top.isEmpty()) {
                                    top.Pop();
                                    n--;
                                }
                            }
                            auto pos = newStack->dato.space[n].getPosition();
                            p.mysprite->setPosition(pos.x + 5, pos.y + 5);
                            p.lastPos = p.mysprite->getPosition();
                            newStack->dato.stack.Push(p);
                            newStack->dato.state = true;
                        }

                        newStack = newStack->next;
                    }
                }

                lastStack = lastStack->next;
            }


        }

    }

}

void LinkedList::ShowVector() {
    isVector = true;

    Nodo* lastStack = NULL;
    Nodo* newStack = NULL;
    bool found = false;

    lastStack = head;
    for (auto j = movements.begin(); j != movements.end(); j++) {
        if (!j->state && !found) {

            while (lastStack && !found) {


                if (j->lastId == lastStack->id) {

                    newStack = head;
                    while (newStack) {

                        if (j->newId == newStack->id) {

                            auto top = newStack->dato.stack;
                            auto p = lastStack->dato.stack.Pop();
                            int n = 4;
                            for (int j = 4; j >= 1; j--) {
                                if (!top.isEmpty()) {
                                    top.Pop();
                                    n--;
                                }
                            }
                            auto pos = newStack->dato.space[n].getPosition();
                            p.mysprite->setPosition(pos.x + 5, pos.y + 5);
                            p.lastPos = p.mysprite->getPosition();
                            newStack->dato.stack.Push(p);
                            newStack->dato.state = true;
                            found = true;
                            j->state = true;
                        }
                        found ? newStack = NULL : newStack = newStack->next;
                    }
                }
                found ? lastStack = NULL : lastStack = lastStack->next;
            }
        }
    }
}


void LinkedList::Play(SoundBuffer b) {
    sound.setBuffer(b);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::milliseconds(1));
    };
}

void LinkedList::isStackCompleted(int x) {
    Nodo* actual = head;
    int n = 0;
    count = 0;
    while (actual) {

        if (actual->dato.stack.isFull()) {
            auto p = actual->dato.stack;
            auto m = p.Top();

            for (i = 0; i < actual->dato.stack.Size(); i++) {
                if (m.color == p.Pop().color) {
                    n++;
                }
            }
        }
        if (n == 4) {
            actual->isCompleted = true;
            n = 0;
            count++;
        }
        else {
            actual->isCompleted = false;
            n = 0;

        }
        actual = actual->next;
    }
    count == x ? isCompleted = true : isCompleted = false;
}

void LinkedList::Draw(RenderWindow* window) {


    Nodo* actual = head;

    while (actual) {

        auto _tube = actual->dato.tube;
        if (actual->dato.state == true) {
            auto m = actual->dato.stack;
            for (i = 0; i < actual->dato.stack.Size(); i++) {
                auto top = m.Pop();
                auto position = top.mysprite->getPosition();
                if (actual->isCompleted && (RepeatCompleted() || Win())) {

                    top.mysprite->setPosition(top.mysprite->getPosition().x + 22, top.mysprite->getPosition().y + 20);
                    top.mysprite->setOrigin(top.mysprite->getLocalBounds().width / 2, top.mysprite->getLocalBounds().height / 2);

                    top.mysprite->rotate(1);
                    window->draw(*top.mysprite);
                    top.mysprite->setPosition(position);
                }
                else {
                    top.mysprite->setRotation(0); 
                    top.mysprite->setOrigin(top.Origen); 
                    window->draw(*top.mysprite);
                }
  
           
            }
        }
        for (i = 0; i < 5; i++) {
            window->draw(actual->dato.space[i]);
        }
        window->draw(*_tube);
        actual = actual->next;

    }

}

void LinkedList::PlaySound() {
    if (statePlay) {
        Play(b);
        statePlay = false;
    }
}

void LinkedList::Show() {
    Nodo* actual = head;

    while (actual) {
        cout << actual->dato.stack.maxSize() << endl;
        actual = actual->next;
    }
}

void LinkedList::CheckIntersect(Event ev, Vector2i position, SoundBuffer sn) {
    b = sn;
    if (onHead != NULL) {
        Move(ev, position, onHead);
    }

    Nodo* actual = head;
    FloatRect rec(Vector2f(position), { 1,1 });

    while (actual) {
        auto m = actual->dato.space[0];
        if (ev.type == Event::MouseButtonPressed) {
            if (ev.key.code == Mouse::Left) {

                if (actual->state == false) {
                    if (actual->dato.Up == true) {
                        actual->dato.stack.Top().mysprite->setPosition(actual->dato.stack.Top().lastPos);
                        actual->dato.Up == false;

                    }
                    if (actual->dato.tube->getGlobalBounds().intersects(rec) && actual->dato.state == true) {

                        actual->dato.stack.Top().mysprite->setPosition(m.getPosition().x + 5, m.getPosition().y);
                        actual->dato.Up = true;
                        onHead = actual;

                    }
                    if (actual->dato.tube->getGlobalBounds().intersects(rec) && actual->dato.state == true) {
                        statePlay = true;
                    }

                }
          


            }
        }
        if (ev.type == Event::MouseButtonReleased) {
            if (ev.key.code == Mouse::Left) {
                if (actual->dato.tube->getGlobalBounds().intersects(rec) && actual->state == true) {
                    actual->state = false;
                    if (actual->dato.Up == true) {
                        actual->dato.stack.Top().mysprite->setPosition(actual->dato.stack.Top().lastPos);
                        actual->dato.Up == false;
                    }
                }
            }
        }

        actual = actual->next;
    }

}

void LinkedList::Move(Event ev, Vector2i position, Nodo* onHead) {
    FloatRect rec(Vector2f(position), { 1,1 });

    Nodo* move = head;
    bool found = false;

    if (onHead->dato.Up == true) {

        while (move && !found) {

            if (onHead->id != move->id && move->dato.tube->getGlobalBounds().intersects(rec)) {

                if (ev.type == Event::MouseButtonPressed && ev.key.code == Mouse::Left) {
                    auto spr = onHead->dato.stack.Top();
                    if (move->dato.stack.isEmpty()) {
                        auto p = onHead->dato.stack.Pop();
                        auto pos = move->dato.space[4].getPosition();
                        SaveMovement(onHead->id, move->id);
                        p.mysprite->setPosition(pos.x + 5, pos.y + 5);
                        p.lastPos = p.mysprite->getPosition();
                        move->dato.stack.Push(p);
                        move->dato.state = true;
                        move->state = true;
                        onHead->dato.Up = false;
                        move->dato.Up = false;
                        found = true;

                    }
                    else {

                        if (!move->dato.stack.isEmpty() && !move->dato.stack.isFull()) {
                            //cambio de pelota a otro tubo
                            if (move->dato.stack.Top().color == onHead->dato.stack.Top().color) {

                                onHead->dato.Up = true;
                                auto top = move->dato.stack;
                                auto p = onHead->dato.stack.Pop();
                                SaveMovement(onHead->id, move->id);
                                int n = 4;
                                for (int j = 4; j >= 1; j--) {
                                    if (!top.isEmpty()) {
                                        top.Pop();
                                        n--;
                                    }
                                }
                                auto pos = move->dato.space[n].getPosition();
                                p.mysprite->setPosition(pos.x + 5, pos.y + 5);
                                p.lastPos = p.mysprite->getPosition();
                                move->dato.stack.Push(p);
                                move->dato.state = true;
                                move->state = true;
                                move->dato.Up = false;
                                onHead->dato.Up = false;
                                found = true;
                                StackWithSameColor(move);
                            }
                        }
                    }
                }
            }
            move = move->next;
        }
    }



}

void LinkedList::StackWithSameColor(Nodo* nodo) {

    if (nodo->dato.stack.isFull()) {
        i = 0;
        color = nodo->dato.stack.Top().color;
        auto actual = nodo->dato.stack;
        while (true) {

            if (!actual.isEmpty()) {
                if (actual.Pop().color == color) {
                    i++;
                }
            }
            else {
                break;
            }
        }
        if (i == 4) {
            if (!b.loadFromFile("completed.wav")) {
                cout << "NotFound" << endl;
            }
            else {
                statePlay = true;
            }
        }
    }

}

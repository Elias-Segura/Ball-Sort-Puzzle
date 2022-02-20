#pragma once
#include "stack.h"
#include "space_stack.h"
#include <assert.h>
#include "Tube.h"; 
#include "stack.h"
#include "Element_stack.h"
#include "QueueMovements.h"
#include "Queue.h"
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <future>       
#include <chrono>  
#include "savedGame.h"
using namespace std;
using namespace sf;
class LinkedList
{
private:
    vector<Queue> movements{};
    SoundBuffer b;
    Sound sound;
    int i{ 0 }, k{ 0 }, m{ 0 }, count{ 0 }, color{0};
    bool isCompleted{false};
    bool isRepeatCompleted{ false };
    bool isVector{ false }; 
    bool statePlay{ false }; 

    struct Nodo {
        int id{0};
        bool state{ false } ;
        bool isCompleted{ false }; 
        Tube dato;
        Nodo* next;
        Nodo() = default;
        explicit Nodo(const Tube& data)
            :dato{ data } {}
        Nodo(const Tube& data, Nodo* next)
            :dato{ data }, next{ next } {}
    };

    Nodo* head{ nullptr };
    Nodo* onHead{ nullptr };
    QueueMovements* queue = new QueueMovements();
    int _count{ 0 };
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator = (const LinkedList&) = delete;

public:
    LinkedList() = default;
    ~LinkedList() {
        Clear(true);
    }
    int Count() {
        return _count;
    }
    bool isEmpty() const {
        return (_count == 0);
    }
    void Clear(bool clear) {
        while (!isEmpty()) {
            RemoveHead();
        }
        if (isEmpty()) {
            head = nullptr;
        }
       k=0, m=0, count=0, _count=0;
       isCompleted= false ;
     
       onHead = nullptr;
       queue->first = queue->last = nullptr;
       if (clear) {
           isRepeatCompleted = false;
           movements.clear();
       }
    }
    void insertHead(const Tube& value) {
    
        Nodo* nodo = new Nodo{ value };
        nodo->id = k;
        k++;
        nodo->next = head;
        head = nodo;
        onHead = nodo;
        _count++;
    }
    void RemoveHead() {
        assert(!isEmpty());
        Nodo* newHead = head->next;
        delete head;
        head = newHead;
        --_count;
    }
    bool BackMovement(); // move steps back
    void SaveMovement(int  lastStack, int newStack); // save every movement 
    vector<Queue> getVector(); // getVector of movements 
    bool Win(); // check if win
    bool RepeatCompleted(); // check if repeated game is done
    void loadSavedGame(vector<savedGame> movements); //load save game
    void ShowVector(); // sample repeat
    void Play(SoundBuffer b);
    void isStackCompleted(int x);
    void Draw(RenderWindow* window);
    void PlaySound();
    void Show(); 
    void CheckIntersect(Event ev, Vector2i position, SoundBuffer sn); //check which tube has been clicked
    void Move(Event ev, Vector2i position, Nodo* onHead); ///move to another tube
    void StackWithSameColor(Nodo* nodo);
};


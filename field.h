#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef unsigned int uint;

class field{
    uint area[4][4];
    bool hasmoved;
    uint score;
public:
    field();
    void rotateLeft();
    void slide();
    double getScore();
    void print();
    void addRandom();
    bool lost();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void reset();
    int getLargest();
    bool isLegal();
    uint *operator [](uint i);
};

#endif // FIELD_H

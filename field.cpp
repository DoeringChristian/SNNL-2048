#include "field.h"

field::field(){
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            area[i][j] = 0;
    hasmoved = true;
    addRandom();
    addRandom();
}

void field::rotateLeft(){
    uint area2[4][4];
    for(uint j = 0;j < 4;j++){
        for(uint i = 0;i < 4;i++){
            area2[i][j] = area[3-j][i];
        }
    }
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            area[i][j] = area2[i][j];
}

void field::print(){
    for(int j = 0;j < 4;j++){
        for(int i = 0;i < 4;i++)
            cout << area[i][j] << "|";
        cout << endl;
    }
}

void field::slide(){
    hasmoved = false;
    for(uint i = 0;i < 4;i++)
        for(uint j = 0;j < 4;j++){
            uint k = j;
            while(k != 0 && (area[i][k] == 0 || k == j))
                k--;
            if(area[i][k] == area[i][j] || area[i][k] == 0){
                uint b = area[i][j];
                area[i][j] = 0;
                area[i][k] += b;
                if(k != j)
                    hasmoved = true;
            }
            else if(area[i][k] != area[i][j] && area[i][k] != 0){
                uint b = area[i][j];
                area[i][j] = 0;
                area[i][k+1] = b;
                if(k+1 != j)
                    hasmoved = true;
            }
        }
}

void field::moveUp(){
    slide();
    addRandom();
}
void field::moveDown(){
    rotateLeft();
    rotateLeft();
    slide();
    rotateLeft();
    rotateLeft();
    addRandom();
}
void field::moveRight(){
    rotateLeft();
    slide();
    rotateLeft();
    rotateLeft();
    rotateLeft();
    addRandom();
}
void field::moveLeft(){
    rotateLeft();
    rotateLeft();
    rotateLeft();
    slide();
    rotateLeft();
    addRandom();
}

void field::addRandom(){
    srand(time(0));
    if(hasmoved){
        uint i = -1;
        uint j = -1;
        while(area[i][j] != 0){
            i = rand() % 4;
            j = rand() % 4;
            srand(time(0));
        }
        area[i][j] = 2;
    }
}

bool field::lost(){
    bool l = true;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 3;j++)
            if(area[i][j] == area[i][j+1])
                l = false;
    for(int j = 0;j < 4;j++)
        for(int i = 0;i < 3;i++)
            if(area[i][j] == area[i+1][j])
                l = false;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            if(area[i][j] == 0)
                l = false;
    
    return l;
}

int field::getScore(){
    int s = 0;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            s += area[i][j];
    return s;
}

uint *field::operator [](uint i){
    uint *j = area[i];
    return j;
}

void field::reset(){
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            area[i][j] = 0;
    hasmoved = true;
    addRandom();
    addRandom();
}

int field::getLargest(){
    int largest = 0;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
            if(area[i][j] > largest)
                largest = area[i][j];
    return largest;
}
















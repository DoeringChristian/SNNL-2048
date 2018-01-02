#include <iostream>
#include "field.h"
#include "network.h"

using namespace std;

int main(){
    int fc = 0;
    field f;
    uint nodes[4] = {16,10,10,4};
    Network n(nodes,4);
    Trainer tr(n,0.001);
    while(true){
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++){
                n.setInput(i*4+j,f[i][j]/f.getLargest());
            }
        n.update();
        uint j = 0;
        double k = 0;
        for(int i = 0;i < 4;i++)
            if(n.getOutput()[i] > k){
                k = n.getOutput()[i];
                j = i;
            }
        switch (j) {
        case 0:
            f.moveUp();
            break;
        case 1:
            f.moveLeft();
            break;
        case 2:
            f.moveDown();
            break;
        case 3:
            f.moveRight();
            break;
        }
        f.print();
        cout << "network: " << tr.currentNet;
        cout << endl;
        if(f.lost() || fc > 10000){
            n = tr.update(-f.getScore(),0.001);
            f.reset();
            fc = 0;
        }
        //cin.get();
        fc++;
    }
    return 0;
}

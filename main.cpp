#include <iostream>
#include "field.h"
#include "network.h"

using namespace std;

double logx(double b,double v);

int main(){
    int fc = 0;
    field f;
    uint nodes[4] = {16,16,10,2};
    Network n(nodes,4);
    Trainer tr(n,0.001);
    while(true){
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++){
                n.setInput(i*4+j,logx(2,f[i][j])/logx(2,f.getLargest()));
            }
        n.update();
        
        if(n.getOutput()[0] < 0.5 && n.getOutput()[1] < 0.5)
            f.moveUp();
        if(n.getOutput()[0] > 0.5 && n.getOutput()[1] > 0.5)
            f.moveDown();
        if(n.getOutput()[0] < 0.5 && n.getOutput()[1] > 0.5)
            f.moveLeft();
        if(n.getOutput()[0] > 0.5 && n.getOutput()[1] < 0.5)
            f.moveRight();
        
        f.print();
        cout << "               network: " << tr.currentNet 
             << " fitness: " << f.getScore() 
             << " mutation: " << 0.1/f.getScore()
             << " output: " 
             << n.getOutput()[0] << " | "
             << n.getOutput()[1] 
             << " fc: " << fc << endl;;
        cout << endl;
        if(f.lost() || fc > 10000){
            n = tr.update(-f.getScore(),1/f.getScore());
            f.reset();
            fc = 0;
        }
        //cin.get();
        fc++;
    }
    return 0;
}

double logx(double b, double v){
    if(v == 0)
        return 0;
    else
        return log(v)/log(b);
}

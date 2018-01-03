#include <iostream>
#include "field.h"
#include "network.h"
#include <fstream>

using namespace std;

double logx(double b,double v);

int main(){
    field f;
    uint nodes[4] = {16,16,10,2};
    Network n(nodes,4);
    Trainer tr(n,0.001);
    n = tr[1];
    uint iteration = 0;
    while(true){
        uint simcounter = 0;
        uint framecounter = 0;
        double addedfitness = 0;
        for(simcounter = 0;simcounter < 10;simcounter++){
            for(framecounter = 0;framecounter < 10000;framecounter++){
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
                cout << "              "
                     << " fitness: " << addedfitness/(simcounter+1)
                     << " mutation: " << 1/(addedfitness/(simcounter+1))
                     << " output: " 
                     << n.getOutput()[0] << " | "
                     << n.getOutput()[1] 
                     << " iteration: " << iteration
                     << " network: " << tr.currentNet 
                     << " simulation: " << simcounter 
                     << " frame: " << framecounter
                     << endl;
                cout << endl;
                if(f.lost())
                    break;
            }
            addedfitness += f.getScore();
            f.reset();
        }
        n = tr.update(-addedfitness/(simcounter+1),1/(addedfitness/(simcounter+1)));
        if(tr.currentNet == 0){
            iteration++;
            ofstream log;
            log.open("2048-logging.txt");
            log << "iteration: " << iteration << " fitness: " << addedfitness/(simcounter+1) << endl;
        }
    }
    return 0;
}

double logx(double b, double v){
    if(v == 0)
        return 0;
    else
        return log(v)/log(b);
}

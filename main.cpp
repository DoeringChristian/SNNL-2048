#include <iostream>
#include "field.h"
#include "network.h"
#include <fstream>

using namespace std;

double logx(double b,double v);

int main(){
    field f;
    uint nodes[4] = {16,16,10,4};
    Network n(nodes,4,false);
    Trainer tr(n,0.001);
    n = tr[1];
    uint iteration = 0;
    while(true){
        uint simcounter = 0;
        uint framecounter = 0;
        double addedfitness = 0;
        for(simcounter = 0;simcounter < 100;simcounter++){
            uint illegalmoves = 0;
            for(framecounter = 0;framecounter < 1000000;framecounter++){
                for(int i = 0;i < 4;i++)
                    for(int j = 0;j < 4;j++){
                        n.setInput(i*4+j,logx(2,f[i][j])/logx(2,f.getLargest()));
                    }
                n.update();
                
                int j = 0;
                for(int i = 0;i < 4;i++)
                	if(n.getOutput()[i] > n.getOutput()[j])
                		j = i;
                switch(j){
                	case 0:
                		f.moveUp();
                		break;
                	case 1:
                		f.moveDown();
                		break;
                	case 2:
                		f.moveLeft();
                		break;
                	case 3:
                		f.moveRight();
                		break;
                }
                
                if(f.isLegal())
                    illegalmoves = 0;
                if(!f.isLegal())
                    illegalmoves ++;
                
                f.print();
                cout << "              "
                     << " fitness: " << addedfitness/(simcounter+1)
                     << " mutation: " << 1/(addedfitness/(simcounter+1))
                     << " output: " 
                     << n.getOutput()[0] << " | "
                     << n.getOutput()[1] << " | "
                     << n.getOutput()[2] << " | "
                     << n.getOutput()[3] << endl
                     << "              "
                     << " score: " << f.getScore()
                     << " iteration: " << iteration
                     << " network: " << tr.currentNet 
                     << " simulation: " << simcounter  
                     << " frame: " << framecounter
                     << endl;
                cout << endl;
                if(f.lost())
                    break;
                if(illegalmoves > 200)
                    break;
            }
            addedfitness += f.getScore();
            f.reset();
        }
        n = tr.update(-addedfitness/(simcounter+1),0.1,0.1);
        if(tr.currentNet == 0){
            iteration++;
            ofstream log;
            log.open("2048-logging.txt", ofstream::out | ofstream::app);
            log << "iteration: " << iteration << " fitness: " << addedfitness/(simcounter+1) << endl;
            log.close();
            tr.current().SavetoFile("network.snn");
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

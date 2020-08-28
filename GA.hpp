//
//  GA.hpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/16.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#ifndef GA_hpp
#define GA_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

class GA{
public:
    GA();
    GA(int b,int iterations,int population,double crossover,double mutation);
    void init_point(int *str);
    int Sum(int *str);
    void run();
    int get_max(){return Max;}
    void init_population();
    int find_best_index();
    int *FitnessFunction();
    int **RouletteWheelSelection();
    int **TournamentSelection();
    void Crossover(int **p);
    void Mutation(int **p);
private:
    int iter;
    int bits;
    int Max;
    int *max_bitstr; //temp
    int pop;
    double Pm;
    double Pc;
    int **Pop;
    double *Prob;//for rws
    int *f;
    int tnt_count;
    vector<int> v;
};

#endif /* GA_hpp */

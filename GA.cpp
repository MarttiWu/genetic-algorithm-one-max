//
//  GA.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/16.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//
//  GA C++ Array version

#include "GA.hpp"

GA::GA(){
    bits = 10;
    iter = 5;
    Max=0;
    max_bitstr = new int [10];
    memset(max_bitstr, 0, 10);
    pop = 10;
    Pm = 0.01;
    Pc = 0.6;
    Pop = new int*[pop];
    for(int i=0;i<pop;i++){
        Pop[i] = new int[bits];
        memset(Pop[i], 0, bits);
    }
    Prob = new double [pop];
    memset(Prob, 0, pop);
    f = new int [10];
    memset(f, 0, 10);
    tnt_count=0;
    for (int i=0;i<pop;i++)
        v.push_back(i);
    random_shuffle(v.begin(),v.end());
     
}

GA::GA(int b,int iterations,int population,double crossover,double mutation){
    bits = b;
    iter = iterations;
    Max=0;
    max_bitstr = new int [bits];
    memset(max_bitstr, 0, bits);
    pop = population;
    Pm = mutation;
    Pc = crossover;
    Pop = new int*[pop];
    for(int i=0;i<pop;i++){
        Pop[i] = new int[bits];
        memset(Pop[i], 0, bits);
    }
    Prob = new double [pop];
    memset(Prob, 0, pop);
    f = new int [bits];
    memset(f, 0, bits);
    tnt_count=0;
    for (int i=0;i<pop;i++)
        v.push_back(i);
    random_shuffle(v.begin(),v.end());
}

void GA::init_population(){
    for (int i=0;i<pop;i++){
        init_point(Pop[i]);
    }
}

void GA::init_point(int *str){
    for (int i=bits-1;i>=0;i--){
        str[i] = rand()%2;
    }
}

int GA::Sum(int *str){
    int sum=0;
    for (int i=0;i<bits;i++){
        sum+=str[i];
    }
    return sum;
}

int GA::find_best_index(){
    int best = 0;
    int index=0;
    for (int i=0;i<pop;i++){
        if (f[i]>best){
            best = f[i];
            index = i;
        }
    }
    return index;
}

int *GA::FitnessFunction(){
    int *f = new int [pop];
    memset(f, 0, pop);
    double total=0;
    for (int i=0;i<pop;i++){
        f[i] = Sum(Pop[i]);
        total+=(double)f[i];
    }
    for (int i=0;i<pop;i++){
        Prob[i] = f[i] / total;
    }
    return f;
}

int **GA::RouletteWheelSelection(){
    int **p = new int *[2];
    for (int i=0;i<2;i++){
        p[i] = new int [bits];
        memset(p[i], 0, bits);
    }
    double base=0.0;
    int n=0;
    double r1,r2;
    do{
        r1 = (double)rand()/(RAND_MAX);
        r2 = (double)rand()/(RAND_MAX);
    }while(r1==r2);
    for (int i=0;i<pop;i++){
        if ( r1>base&&r1<base+Prob[i] ){
            for (int j=0;j<bits;j++){
                p[n][j] = Pop[i][j];
            }
            n++;
        }
        if ( r2>base&&r2<base+Prob[i] ){
            for (int j=0;j<bits;j++){
                p[n][j] = Pop[i][j];
            }
            n++;
        }
        base+=Prob[i];
    }
    return p;
}

int **GA::TournamentSelection(){
    int **p = new int *[2];
    for (int i=0;i<2;i++){
        p[i] = new int [bits];
        memset(p[i], 0, bits);
    }
    
    const int tnt_size = 2;
    for (int i=0;i<2;i++){
        int index[tnt_size];
        random_shuffle(v.begin(),v.end());
        for (int j=0;j<tnt_size;j++){
            index[j] = v[j];
        }
        int maxidx=index[0];
        int max=f[index[0]];
        int maxi=0;
        for (int i=0;i<tnt_size;i++){
            if (f[index[i]]>max){
                maxidx = index[i];
                max = f[index[i]];
                maxi=i;
            }
        }
        for (int j=0;j<bits;j++){
            p[i][j] = Pop[maxidx][j];
        }
    }
    return p;
}


//One point crossover
void GA::Crossover(int **p){
    int index = rand()%bits;
    int *temp = new int [bits];
    for (int i=0;i<bits;i++){
        temp[i] = p[0][i];
    }
    for (int i=index+1;i<bits;i++){
        p[0][i] = p[1][i];
        p[1][i] = temp[i];
    }
}

void GA::Mutation(int **p){
    int index = rand()%bits;
    p[0][index] = p[0][index]==0?1:0;
    p[1][index] = p[1][index]==0?1:0;
}

void GA::run(){
    init_population();
    f = FitnessFunction();
    int it=0;
    int bestIdx = find_best_index();
    Max=f[bestIdx];
    for (int i=0;i<bits;i++)
        max_bitstr[i] = Pop[bestIdx][i];
    while (it<iter&&Max<bits){
        int **newPop = new int*[pop];
        for(int i=0;i<pop;i++){
            newPop[i] = new int[bits];
            memset(newPop[i], 0, bits);
        }
        for (int i=0;i<pop;i+=2){
            //int **p = RouletteWheelSelection();
            int **p = TournamentSelection();
            if ((double)rand()/(RAND_MAX)<Pc){
                Crossover(p);
            }
            if ((double)rand()/(RAND_MAX)<Pm){
                Mutation(p);
            }
            newPop[i] = p[0];
            newPop[i+1] = p[1];
        }
        tnt_count=0;
        Pop = newPop;
        f = FitnessFunction();
        int bestIdx = find_best_index();
        if (f[bestIdx]>Max){
            Max=f[bestIdx];
            for (int i=0;i<bits;i++)
                max_bitstr[i] = Pop[bestIdx][i];
        }
        it+=pop;
    }
    cout<<"Max: "<<Max<<endl;
    for (int i=0;i<bits;i++){
        cout<<max_bitstr[i];
    }
    cout<<endl;
}

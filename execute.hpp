//
//  execute.hpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/1.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#ifndef execute_hpp
#define execute_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include "GA.hpp"
using namespace std;

const int block = 10;

void execute(const int Algo,const int runs,const int iterations,const int bits,const string filename,const int population,const double Pc, const double Pm);

#endif /* execute_hpp */


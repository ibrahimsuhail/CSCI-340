//
//  main.cpp
//  mtrand
//
//  Created by ibrahim suhail on 3/18/20.
//  Copyright © 2020 ibrahim suhail. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
/*
specs:
1) generate 10k random numbers from 1-10,000 [x]
2) sort using and then output the min, max from the sample [x]
3) find the min of the 10k samples using non MT way. [x]
4) find the min using MT way. (10,000/5) => 2,000/5 => 400/5 => 80 per thread. Could even stop at 400
*/

#define NUM_THREADS 5
#define cap 10000
using namespace std;
int num;
int min_th[NUM_THREADS] = { 0 };
int minArray[cap];
vector<int> myVector;
int threadNumber = 0;
  
void getRands(){
  srand(time(NULL));
  for (int i = 0; i < cap; i++)
    minArray[i] = (rand() % cap);
}
void *minimum(void *arg){
    getRands();
    int num = threadNumber++;
    int min1 = 0;
    for (int i = num * (cap / NUM_THREADS); i < (num + 1) * (cap / NUM_THREADS); i++) {
        if (minArray[i] < min1)
            min1 = minArray[i];
    }
    min_th[num] = min1;
    pthread_exit(0);
}
void nonMT(){
  getRands();
  for (int i = 0; i < cap; i++)
  myVector.push_back(minArray[i]);
  sort(myVector.begin(), myVector.end());
  int min1 = myVector[0];
  int max1= myVector[cap-1];
  cout <<"min nonMT: "<< min1 <<endl << "max nonMT: " << max1 << endl;
}
void minMT(){
       int MIN = 0;
       int i;
       pthread_t threads[NUM_THREADS];
         for (i = 0; i < NUM_THREADS; i++)
           pthread_create(&threads[i], NULL, minimum, (void*)NULL);
       for (i = 0; i < NUM_THREADS; i++)
           pthread_join(threads[i], NULL);
       for (i = 0; i < NUM_THREADS; i++) {
           if (min_th[i] < MIN)
               MIN = min_th[i];
       }
       
       cout<< "Minimum Element using multiple threads: " << MIN << endl;
}
// Driver code
int main(){
    nonMT();
    minMT();
    return 0;
}





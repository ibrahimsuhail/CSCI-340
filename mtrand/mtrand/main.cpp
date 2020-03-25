//
//  main.cpp
//  multi threaded random number generator
//  project 2
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
// generate 5 * 20 threads
#define NUM_THREADS 5
#define NUM_SUBTHREADS 20
#define cap 10000
using namespace std;
int num;
// this array stores the minimum element of each subthread
int min_th[NUM_SUBTHREADS] = { 0 };
int minArray[cap];
vector<int> myVector;
int threadNumber = 0;
  // generate 10,000 random numbers from 0 - 10,000 and place in minArray
void getRands(){
  srand(time(NULL));
  for (int i = 0; i < cap; i++)
    minArray[i] = (rand() % cap);
}
// find the minimum element without multithreading
void nonMT(){
  getRands();
    // add each element of minArray to vector
  for (int i = 0; i < cap; i++)
  myVector.push_back(minArray[i]);
    // sort the vector from smallest to largest element
  sort(myVector.begin(), myVector.end());
  int min1 = myVector[0];
  int max1= myVector[cap-1];
  cout <<"min nonMT: "<< min1 <<endl << "max nonMT: " << max1 << endl;
}
// finds the minimum element in each array of random numbers
void *minimum(void *arg){
    getRands();
    int num = threadNumber++;
    int min1 = minArray[0];
    for (int i = 0 ; i < cap; i++) {
        if (minArray[i] < min1)
            min1 = minArray[i];
    }
    min_th[num] = min1;
    pthread_exit(0);
}
// each subthread will call the minimum function
void *subth(void *arg){
    int i;
    // array of threads
    pthread_t threads[NUM_SUBTHREADS];
    // create 20 subthreads and join them
    // each thread will call the minimum function to find the minimum element in each array of random numbers
    for (i = 0; i < NUM_SUBTHREADS; i++)
        pthread_create(&threads[i], NULL, minimum, (void*)NULL);
    for (i = 0; i < NUM_SUBTHREADS; i++)
        pthread_join(threads[i], NULL);
    pthread_exit(0);
}
// gets the minimum element from array containing the minimum elements of each thread
void minMT(){
    int i;
    pthread_t threads[NUM_THREADS];
    // create 5 threads and join them
    // each thread will call subth() to create 20 subthreads
    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, subth, (void*)NULL);
    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
    // sort array of minimum values from threads
    int j = sizeof(min_th)/sizeof(min_th[0]);
    sort(min_th, min_th+j);
    /*                                          uncomment to see every value of array
    for (i = 0; i < NUM_THREADS ; i++)
    cout<< min_th[i] << ", ";
    */
    int MIN = min_th[0];
    cout << "minimum element using multithreading: " << MIN << endl;
}

int main(){
    // find minimum element without multithreading
    nonMT();
    // find minimum element with multithreading
    minMT();
    return 0;
}





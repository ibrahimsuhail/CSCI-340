
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
// function to find the wait time for every process
void calculate_wait_time(int process[],int num,int burst_time[], int wait_time[], int tq){
    // To store remaining burst times,
    // make a copy of burst times bt[]
    int remaining_bt[num];
    for(int i=0;i<num;i++)
        remaining_bt[i]=burst_time[i];
    int t=0;
     // traverse all processes while they are running
    while(true){
        bool done=true;
        for(int i=0;i<num;i++){
        if(remaining_bt[i]>0){
            done=false; // there is still a pending process
            // a loop that increments an integer time variable 0 to 96
            if(t<=96){
            
            if(remaining_bt[i]>tq){
                    t+=tq; // increase the value of time
                    remaining_bt[i]-=tq; // decrease the remaining burst time by time quantum
                }
                // If burst time is <= to time quantum
                // it is the last cycle for this process
            else{
                t+= remaining_bt[i];
                // increase the value of time by the remaining burst time
                wait_time[i] = t - burst_time[i];
                // the wait time = current time - time used by this process
                remaining_bt[i]=0;
                // process complete so remaining burst time is 0
                }
            }
        }
        }
        if  (done == true)
            // if we have completed the process, break
        break;
        }
    }
    
int main(){
    int num, tq = 10;
    ifstream fin("/Users/ibrahimsuhail/Desktop/input.txt");
    // create ifstream object pointing to your input file
    if (!(fin)) cout<< "File not found";
    int burst_time[20],process[20],wait_time[20],turnaround_time[20],priority[20], arrival_time[20];
    // initialize all relevant arrays
    int tot = 0, proc, prior, bt, arvl;
    // number of processes = 0 at first
    
    string firstLine = "process\tpriority\tburst\tarrival\n";
    cout << firstLine;
    // print contents of file
     while(fin >> proc >> prior >> bt >> arvl ){
         // the integers in the file are put into their repective fields
         process[tot] = proc;
         priority[tot] = prior;
         burst_time[tot] = bt;
         arrival_time[tot] = arvl;
         
         cout<<process[tot]<<"\t"<<priority[tot]<<"\t"<<burst_time[tot]<<"\t"<<arrival_time[tot]<<endl;
         tot++;
     }
    num = tot;
    
        int temp;
        int position;
        // sort process based on priority
    for(int i=0 ;i<num;i++){
               position=i;
               for (int j = i+1; j<num;j++)
                   if (priority[j]<priority[position]) position=j;
               temp = priority[i];
               priority [i] = priority[position];
               priority[position]=temp;
               temp=burst_time[i];
               burst_time[i]=burst_time[position];
               burst_time[position]=temp;
               temp=process[i];
               process[i]=process[position];
               process[position]=temp;
    }
        calculate_wait_time(process,num,burst_time,wait_time,tq);
        // the turnaround time is computed by adding wait_time[i] + burst_time[i]
        // it is the time difference between completion time and arrival time
        for(int i = 0; i < num; i++)
        turnaround_time[i]=burst_time[i]+wait_time[i];
        // now that all processes are sorted, and values are computed,
        // print out results
        cout<<"Process\t"<<"Priority\t"<<"Burst Time\t"<< "Wait Time\t"<<"Turn Around Time"<<"\n";

        for(int i=0;i<num;i++){
            cout<<"\t"<<i+1<<"\t"<<priority[i]<<"\t"<<burst_time[i]<<"\t"<<wait_time[i]<<"\t"<<turnaround_time[i]<<endl;
        }
    return 0;
    }
   

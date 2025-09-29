// msMPITest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>
#include <string>
#include <cmath>
#include <vector>
using namespace std; 
const int MAX_STRING = 100;
const double PI = 3.14159265358979323846;

vector<int> globalBinFreqs = {};

float randomFloat()
{
    //taken from geeksforgeeks.org
    return (float)rand() / (float)RAND_MAX;
}

double f(double x) {
    return sin(x);
}
/*
void oddEvenComms(int rank, int size) {
    vector<int> sentRank;
    int buffIndex = 0;
    if (!(rank%2==0)) { //odd
        int numEvens = size / 2;
        sentRank.resize(numEvens);
        int* sentRank = new int[(int)size / 2];

        for (int i = 0; i < size; i+=2) { //odd process sends rank to all other even processes 
            MPI_Sendrecv(&rank, 1, MPI_INT,i,0,&sentRank[buffIndex],1, MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            cout << "Rank: "<< rank << "  Received: " << sentRank[buffIndex] << endl;
            buffIndex++;
        }

    }
    else{ //even
        int numOdds = (size + 1) / 2;
        sentRank.resize(numOdds);
        for (int i = 1; i < size; i+=2) { //even process sends rank to all other odd processes 
            MPI_Sendrecv(&rank, 1, MPI_INT, i, 0, &sentRank[buffIndex], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << "Rank: " << rank << "  Received: " << sentRank[buffIndex] << endl;
            buffIndex++;
        }
    }

}*/

/*
void maxAmongRands(int rank, int size) {
    srand(time(NULL) + log(rank*1231341414.4145125215)); //trying to create a random seed
    int rando = rand() % 100;
    int rec;
    cout << "Process " << rank << " rand value: " << rando << endl;
    if (rank == 0) {
        MPI_Send(&rando, 1, MPI_INT, 1,0,MPI_COMM_WORLD);
        MPI_Recv(&rec,size,MPI_INT,size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        cout << "Process " << rank << " Received: " << rec;
        if (rec > rando) {
            cout << "  Max: " << rec << endl;
        }else
            cout << "  Max: " << rando << endl;

    }
    else{
        MPI_Recv(&rec,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        cout << "Process " << rank << " Received: " << rec;
        if (rec > rando) {
            cout << " ..Sending received value... " << endl;
            MPI_Send(&rec, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }else{
            cout << endl;
            MPI_Send(&rando, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }
    }
}*/

/*
void area(double a, double b, double inc, int rankNum, int cores, double &coreArea) {
    int increment = 0;
    if (a > b) {
        cerr << "a greater than b, incorrect range" << endl;
        abort();
    }
    //cout << "area function accessed by "<<rankNum<< endl;
    //function = sin(x);

    double startIn = a + (double)rankNum * ((b-a) / cores);
    double endIn = a + (rankNum+1) * ((b - a) / cores);
    cout << "StartIn : " << startIn << "  endIn: " << endIn << "   from rank " << rankNum << endl;
    //cout << "inc: " << inc << endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(5*1000));
    double area = 0;
    for (double i = startIn; i < endIn; i += inc) {
        double next = i + inc;
        //cout << "i: " << i << " next: " << next;
        double subAr = ((next - i) * f(i)) + .5 * ((next - i) * (f(next) - f(i)));
        //cout << "  subAr: " << subA
        //cout << " Current Area: " << area << endl;
        area += subAr;
        increment++;
    }
    cout << "Increments: "<<increment << "    area from process " << rankNum << " :" << area << endl;
    MPI_Reduce(&area, &coreArea, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
}*/
/*
void ignore() {
    char       greeting[MAX_STRING];  // String storing message 
    int        comm_sz;             //  Number of processes    //
    int        my_rank;
    if (my_rank != 0) {
        //  Create message //
        sprintf_s(greeting, "Greetings from process %d of %d!",
            my_rank, comm_sz);
        //   Send message to process 0 //
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0,
            MPI_COMM_WORLD);
    }
    else {
        //  Print my message  //
        printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
        for (int q = 1; q < comm_sz; q++) {
           //  Receive message from process q //
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q,
                0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //  Print message from process q  //
            printf("%s\n", greeting);
        }
    }
}*/

int subIntIndex(float val, vector<float> &subInts) {
    for (int i = 0; i < subInts.size(); i++) {
        if (subInts[0] - subInts[i] <= val <= subInts[i])
            return i;
    }
}

void parallelBins(int rank, int size, vector<float> dataSet, vector<float>& subInts, int range, int startInd) {
    vector<int> binFreqs(subInts.size());
    for (int i = startInd; i < startInd+range;i++) {
        cout << "Process: "<<rank << "  dataSet[i] " << dataSet[i] << endl;
        binFreqs[subIntIndex(dataSet[i], subInts)] += 1;
    }
    cout << "Process " << rank<<"  ";
    for (auto temp : binFreqs) {
        cout << temp << ", ";
    }
    cout << endl;
    MPI_Reduce(&binFreqs, &globalBinFreqs, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}

int main(void) {
    srand(static_cast<unsigned int>(time(0)));
    /**/
    int        comm_sz;               /* Number of processes    */
    int        my_rank;               /* My process rank        */

   // /* Start up MPI */ //
    MPI_Init(NULL, NULL);

    ///* Get the number of processes */ //
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   // /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    /*
    * COMMENTING OUT TRAPEZOIDAL RULE TEST
    * 
    double a = 1;
    double b = PI;
    int resolution = 10000;
    double inc = (b - a) / resolution;
    double coreArea = 0;

    //cout << "comm_sz from "<< my_rank << ": "<<comm_sz<<endl;

    area(a, b, inc, my_rank, comm_sz, coreArea);
    if (my_rank == 0)
        cout << "(ROOT) Area from all processes: " << coreArea << endl;
    //else
        //cout << "(CHILD) Area from process: (testing) " << coreArea << endl;
        */
    /*
    * COMMENTING OUT ODDEVENCOMM PROBLEM 
    * 
    //cout << "size: " << (double)comm_sz/2 << endl;
    //cout << "check: " << (int) (((double)comm_sz / 2) + .5) << endl;
    //oddEvenComms(my_rank,comm_sz);
    */

    /*
    * 
    * COMMENTING OUT AMONGMANYRANDS PROBLEM 
    maxAmongRands(my_rank, comm_sz);*/


    int cores = 4;
    int sampleSize = 10000;
    int bins = 5;

    vector<float> subInts = {}; //only contains max values of each sub interval
    for (int i = 1; i <= bins; i++) {
        subInts.push_back(i*(1/(float)bins));
    } //creating a vector of subIntervals 
    float range = sampleSize / cores; 

    vector<float> randArr(sampleSize);
    //first process populates randArr 

    if (my_rank == 0) {
        range = floor(range); //ensures equal ranges between all processes 
        //ex: 
        // 9,999/4 = 2,499.75
        // 2,499 + 2,500*3 = 9,999 (no floating point indices) 

        for (int i = 0; i < sampleSize; i++) {
            float x = randomFloat();
            randArr[i] = x;
        }
        cout << "finished randArr" << endl;
        
        int buffer = range;

        MPI_Bcast(randArr.data(), sampleSize, MPI_FLOAT, my_rank, MPI_COMM_WORLD); //Process 0 broadcasts randArr to others
        MPI_Send(&range, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        parallelBins(my_rank, comm_sz, randArr, subInts, range,buffer);
        // for mapping the subIntervals to their respective frequencies (debug purposes) 
        cout << "Combined bin frequencies: " << endl;
        for (auto temp : globalBinFreqs) {
            cout << temp << ", ";
        }
        cout << endl;
    }
    else {
        range = ceil(range);
        int recBuffer;
        MPI_Recv(&recBuffer, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (!(my_rank == comm_sz - 1))
            MPI_Send(&range, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
        MPI_Bcast(randArr.data(), sampleSize, MPI_FLOAT, 0, MPI_COMM_WORLD);
       
        cout << "Process " << my_rank << "startInd: " << recBuffer << endl;
        //cout << "received randArr from process " << my_rank << endl;
        parallelBins(my_rank, comm_sz, randArr, subInts,range,recBuffer);
    }
    MPI_Finalize();
    return 0;
}  


// msMPITest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>
#include <string>
#include <cmath>
using namespace std; 
const int MAX_STRING = 100;
const double PI = 3.14159265358979323846;


double f(double x) {
    return sin(x);
}
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
}
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

int main(void) {

    /**/
    int        comm_sz;               /* Number of processes    */
    int        my_rank;               /* My process rank        */

   // /* Start up MPI */ //
    MPI_Init(NULL, NULL);

    ///* Get the number of processes */ //
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   // /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
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

    MPI_Finalize();
    return 0;
}  


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

vector<int> globalBinFreqs(5); 

float randomFloat()
{
    //taken from geeksforgeeks.org
    return (float)rand() / (float)RAND_MAX;
}

double randomDouble()
{
    //taken from geeksforgeeks.org
    return 1-(double)rand() / (double)RAND_MAX*2;
    //1000000000
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

/*
int subIntIndex(float val, vector<float> &subInts) {
    for (int i = 0; i < subInts.size(); i++) {
        if (subInts[0] - subInts[i] < val && val < subInts[i])
            return i;
    }
}

void parallelBins(int rank, int size, vector<float> dataSet, vector<float>& subInts, int range) {
    cout << "Accessed Parallel Bins Func from process " << rank << endl;
    vector<int> binFreqs(subInts.size());
    for (int i = 0; i < range;i++) {
       // cout << "Process: "<<rank << "  dataSet[i] " << dataSet[i] << endl;
        binFreqs[subIntIndex(dataSet[i], subInts)]++;
    }
    cout << "BIN FREQS FOR Process " << rank<<"  ";
    for (auto temp : binFreqs) {
        cout << temp << ", ";
    }
    cout << endl;
    MPI_Reduce(binFreqs.data(), globalBinFreqs.data(), 5, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}


*/

/*
double operator*(vector<double> &A, vector<double>&B) { //dotproduct
    //practicing operator overloading
    double product = 0;
    if (A.size() != B.size()) {
        cerr << "unexpected size passed to dotProduct operator" << endl;
        return 0.0;
    }
    for (int i = 0; i < A.size(); i++) {
        product += A[i] * B[i];
    }
    return product;
}
double operator*(double k, vector<double> &C) { //"scalarProduct"
    double product = 0;
    for (int i = 0; i < C.size(); i++) {
        product += k * C[i];
    }

    //how to use:
    //int k = 5;
    //vector<double> arr = {0,1,2};
    //double scalPro = k*arr = (underlying operation 0 + 5 + 2) = 7

    return product;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& arr) { //output stream insertion operator for printing vectors

    //*
    //* << = insertion into stream
    //* >> = extraction from stream
    //* this operator inserts elements into the stream buffer and gets extracted via cout?
    //*
    //Syntax notes:
    //ostream = An "output stream", used for printing text via the terminal
    //since we're passing in an alias of the ostream, copy-reference is avoided and outputted to the actual ostream

    //const vector<T> &arr simply references the actual vector (wtihout making changes)
    //template <typename T> a cpp feature that enables generic typing, which eliminates the overhead of function overloading
    //e.g.
    //int add(int x, int y) return x + y;
    //double add(double x, double y) return x + y;

    //template<typename T>
    //T add(T x, T y) return x + y;

    //example:
    //    vector <double> A(order), B(order);
    //    A = { 1,2,3,4,5 };  B = { 9,5,6,7,8 };
    //    cout >> A; //extracting from cout stream
    //    cout >> B;
    for (auto temp : arr) {
        os << temp << ", ";
    }
    os << "\n";
    return os;
}

*/

/*
long long int pointsInCircle(const vector<double> points, int rank) {
    int count = 0;
    for (int i = 0; i < points.size();i++) {
        int nextIndex = i++;
        double randX = points[i], randY = points[nextIndex];
       // cout << "process: " << rank << "   randX: " << randX << "  randY: " << randY << "  withinCircle:" << withinCircle << endl;
        count += sqrt(randX * randX + randY * randY) <= 1; //if radius <= 1, then add to globalCount
    }
    return count;
}
*/
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& arr) { //output stream insertion operator for printing vectors
    for (auto temp : arr) {
        os << temp << ", ";
    }
    os << "\n";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& arr) { //output stream insertion operator for printing vectors
    //OSTREAM OPERATOR FOR 2D VECTORS 
    for (auto temp : arr) {
        cout << "{ ";
        for(auto xTemp : temp)
        os << xTemp << ", ";
        cout << "} ,\n";
    }
    os << "\n";
    return os;
}

int calcSubRange(int rank, int commSize,int bulkArraySize){ //allocates appropriate range for given process rank
    double baseR = (double)bulkArraySize / commSize;
    double remainder = (baseR - bulkArraySize / commSize) * 10;
    if (remainder >= 5)
        return rank == 0 ? floor(baseR) : ceil(baseR);
    else
        return rank == 0 ? ceil(baseR) : floor(baseR);
}

void calcVariance(const vector<double> &subVector, int range, double &recvBuffer) {
    double sum = 0;
    for (auto temp : subVector) //calculating local mean (within sub processes' subVector) 
        sum += temp;
    double localBuffer = sum / range;
    MPI_Reduce(&localBuffer, &recvBuffer, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    //adding localMean to globalMean 
    double localVariance = 0;
    for (auto temp : subVector)
        localVariance += (temp - recvBuffer) * (temp - recvBuffer);
    MPI_Reduce(&localBuffer, &recvBuffer, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
}

int main(void) {
    srand(static_cast<unsigned int>(time(0)));
    /**/
    int        commSize;               /* Number of processes    */
    int        rank;               /* My process rank        */

   // /* Start up MPI */ //
    MPI_Init(NULL, NULL);

    ///* Get the number of processes */ //
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);

   // /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    //OTHER TESTS
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

    /*
     int cores = 4;
    int sampleSize = 10000;
    int bins = 5;

    vector<float> subInts = {}; //only contains max values of each sub interval
    for (int i = 1; i <= bins; i++) {
        subInts.push_back(i*(1/(float)bins));
    } //creating a vector of subIntervals 

    float range = (float)sampleSize / cores; 
    
    if (my_rank == 0) {
        cout << "PRINTING SUBINTS: " << endl;
            for (auto temp : subInts) {
                cout << ", " << temp;
            }
        cout << endl;
    }
    vector<float> randArr(sampleSize);


    if (my_rank == 0) {
        vector<float> coreSubVect = {};
        //ensures equal ranges between all processes 
        //ex: 
        // 9,999/4 = 2,499.75
        // 2,499 + 2,500*3 = 9,999

        for (int i = 0; i < sampleSize; i++) {
            float x = randomFloat();
            randArr[i] = x;
        }
        //first process should populate randArr to minimize space 

        vector<int> endIndices(comm_sz);

        for (int i = 0; i < comm_sz; i++) {
            endIndices[i] = i == 0 ? floor(range) : endIndices[i-1] + ceil(range);
            cout << "endIndices[process] " << i<<" "<<endIndices[i] << endl;
        }

        int startInd = 0;
        vector<float> subVectBuffer(ceil(range));

        for (int i = 0; i < comm_sz; i++) {
            for (int x = 0; endIndices[i] == 0 ? x < floor(range) : x < ceil(range); x++) {
                if (i == 0)
                    coreSubVect.push_back(randArr[startInd]); //sub vector for core process 
                else {
                    subVectBuffer[x] = randArr[startInd]; //sub vector for other processes
                    //cout << "subVectBuffer[" << x << "]: " << subVectBuffer[x] << "  " << endl;
                }
                startInd++;
            }
            if (!(i == 0))
                MPI_Send(subVectBuffer.data(), subVectBuffer.size(), MPI_FLOAT, i, 0, MPI_COMM_WORLD);
            //NOTE TO SELF: REMEMBER THAT VECTORS MUST BE PASSED AS vect.data() for MPI FUNCTIONS 
            //ADDITIONALLY, THE RECEIVING VECTOR MUST BE INTIALIZED WITH ENOUGH SPACE
            startInd = endIndices[i];
        }

        range = floor(range);
      
        parallelBins(my_rank, comm_sz, coreSubVect, subInts, range);
        // for mapping the subIntervals to their respective frequencies (necessary for comparisons within sub-intervals)
        cout << "\033[32m" <<"Combined bin frequencies among all processes: " << endl;
        for (auto temp : globalBinFreqs) {
            cout << temp << ", ";
        }
        cout << "\033[0m" << endl;
    }
    else {
        range = ceil(range);
        vector<float> recBuffer(range); //pre-initialize buffer with enough space for MPI_Recv
        MPI_Recv(recBuffer.data(), range, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Successfully received subVect " << my_rank << endl;

        parallelBins(my_rank, comm_sz, recBuffer, subInts,range);
    }
    
    */
   
    /*
        int order = 0;
    double scalar = 0;
    if (rank == 0) {
        cout << "Enter 'order': " << endl;
        cin >> order;
        cout << "Enter scalar: " << endl;
        cin >> scalar;
    }
    MPI_Bcast(&order, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&scalar, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double baseR = (double)order / commSize;
    double remainder = (baseR - order / commSize) * 10;

    int range0 = remainder >= 5 ? floor(baseR) : ceil(baseR); 
    int range1 = remainder >= 5 ? ceil(baseR) : floor(baseR);
    //ensuring balanced subVector distribution 

   //example:
   //10(order)/3(cores) = 3.333                         5(order)/3(cores) = 1.666
   //process0 subVect_Size = ceil() = 4                 process0 subVect_Size = floor() = 1
   //process1 subVect_Size = floor() = 3                process1 subVect_Size = ceil() = 2
   //process2 subVect_Size = floor() = 3                process2 subVect_Size = ceil() = 2

    vector <double> A(order), B(order);

    vector<double>tempVect;
    double tempSend = 0;

    double dotProSum = 0;
    double scalProSum = 0;

    tempVect.resize(range1 * 2); //tempVect contiguously stores two vectors
    if (rank == 0) {
                for (int i = 0; i < order; i++) { //populating A & B with random values 
            A[i] = randomDouble();
            B[i] = randomDouble();
        }
        cout << "range1: " << range1 << " range0: " << range0 << endl;
        cout << "\033[34m Proc0 A: \033[0m" << A;
        cout << "\033[34m Proc0 B: \033[0m" << B <<endl;

        vector<double> baseA(A.begin(), A.begin()+range0);
        vector<double> baseB(B.begin(), B.begin() + range0);

        cout << " Proc 0: dotProsum: " << baseA * baseB << endl;
        cout << " Proc 0: scalProsum: " << (baseA * baseB) * scalar << endl;

        int proc = 1;
        for (int i = range0; i < order; i+=range1) {//distributing 
            cout <<"begin() + i: "<< i << " (next index) i+range1: " << i + range1 << endl;
            tempVect.assign(A.begin() + i, (A.begin() + i) + range1); //temporarily assigns subRange of a A & B **combined**
            tempVect.insert(tempVect.end(), B.begin() + i, (B.begin() + i) + range1);
            cout << "tempVect from proc0 loop: \n" << tempVect << endl;

            //ex: A = {1,2,3,4,5} B = {9,5,6,7,8}
            // 5(order)/3(cores) = 1.66
            // range0 = 1
            // range1 = 2
            // i = range1-1 = 1
            // A.begin() + i = 1 
            // A.begin() + i + range1 = 3
            //tempVect.assign(A.begin() + i, (A.begin() + i) + range1); {2,3}
            //tempVect.insert(tempVect.end(), B.begin() + i, (B.begin() + i) + range1); {2,3,5,6}
                   
            //*          vector<double> tempA(range1), tempB(range1);
            //*         tempA.assign(tempVect.begin(), tempVect.begin() + range1);
            //*         tempB.assign(tempVect.begin()+range1, (tempVect.begin()+range1) + range1);
            //* 
            //tempVect:            TempA:            TempB:
            //2, 3, 5, 6,          2, 3,             5, 6
            
            MPI_Send(tempVect.data(), range1*2, MPI_DOUBLE, proc, 0, MPI_COMM_WORLD);
            proc++;
        }
        //delete &proc; //testing out memory management 
        tempSend = baseA * baseB;
        MPI_Reduce(&tempSend,&dotProSum,1, MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD); //dotProductResult

        tempSend = (baseA * baseB)*scalar;
        MPI_Reduce(&tempSend,&scalProSum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD); //scalarProductResult (vectorA * vectorB) * k 

        cout << "\033[32m TOTAL dotProSum result: \033[0m" << dotProSum << endl;
        cout << "\033[32m TOTAL scalProSum result: \033[0m" << scalProSum << endl;
    }
    else{ //other processes
        vector<double> tempA(range1), tempB(range1);
        MPI_Recv(tempVect.data(), range1*2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //other processes receive subVectors

        cout << "Process: " << rank << " tempVect from recV: \n" << tempVect;

        tempA.assign(tempVect.begin(), tempVect.begin() + range1);
        tempB.assign(tempVect.begin()+range1, (tempVect.begin()+range1) + range1);

        cout << "Process: " << rank << " tempA: " << tempA;
        cout << "Process: " << rank << " tempB: " << tempB << endl;

        tempSend = tempA * tempB;
        cout << "Process: " << rank << " (A*B) tempSend: " << tempSend << endl;
        MPI_Reduce(&tempSend, &dotProSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        tempSend *= scalar;
        cout << "Process: " << rank << " (A*B)*k tempSend: " << tempSend << endl;
        MPI_Reduce(&tempSend, &scalProSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        cout << "process: "<<rank << "  Successfully reduced. " << endl;
    }
    */
    
    /*
        vector<double> subRandPoints; //2d vector flattened to a row
    long long int globalCount = 0, tempSend = 0;
    long long int range1 = 0;

    if (rank == 0) {
        int randArrSize=0;
        cout << "enter point count:"<< endl;
        cin >> randArrSize;

        long long int range0 = calcSubRange(0,commSize, randArrSize);
            range1 = calcSubRange(1,commSize, randArrSize);
            cout << "range0: " << range0 << endl;
            cout << "range1: " << range1 << endl;

        vector<double> randPoints(randArrSize*2);
        MPI_Bcast(&range1, 1, MPI_INT, 0, MPI_COMM_WORLD);

       // cout << "randPoints before loop:\n" << randPoints << endl;

        for (int row = 0; row < randArrSize*2; row++) 
        randPoints[row] = randomDouble();

        // cout << "randPoints after loop:\n" << randPoints << endl;

        //cout << "\n "<<"proc: "<<rank << " randPoints after loop:\n" << randPoints << endl;

        int proc = 1;
        for (int i = range0*2; i < randArrSize*2; i+=range1*2) {
            //cout << "begin() + i    " << i << "   i + range1*2: " << i+range1*2 << endl;

            subRandPoints.assign( randPoints.begin() + i, (randPoints.begin() + i) + range1*2 ); //extracting subVector from randPoints
            //cout << "subRandPoints for proc " << proc << ": \n" << subRandPoints << endl;
            MPI_Send(subRandPoints.data(), range1, MPI_DOUBLE, proc, 0, MPI_COMM_WORLD);
            proc++;
        }
        subRandPoints.clear();
        subRandPoints = { randPoints.begin(), randPoints.begin() + range0*2 };
        //cout << "subRandPoints for proc " << rank << ": \n" << subRandPoints << endl;

        tempSend = pointsInCircle(subRandPoints, rank);
        MPI_Reduce(&tempSend, &globalCount, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        cout << "globalCount: " << globalCount << endl;
        cout << "4*globalCount/arrSize: " << 4*globalCount/ (double)randArrSize << endl;
    }
    else {
        subRandPoints.resize(range1*2);

        //cout << "Proc: " << rank << "   rangeRecv: "<< range1 << endl;
        MPI_Recv(subRandPoints.data(), range1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        tempSend = pointsInCircle(subRandPoints, rank);
        //function desc:
        // counts the number of points within a circle, as determined by the calculated radius. (sqrt{x^2 + y^2}) 
        //

        //cout << "proc: " << rank << " tempSend: " << tempSend << endl;
        MPI_Reduce(&tempSend, &globalCount, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    */
int vectSize;
vector<int> subCount(commSize);
vector<int> displacements(commSize);

vector<double>subVector;
double recvMean;

if (rank == 0) {
    vector<double> bulkVect; 
    cout << "enter vectorSize: " << endl;
    cin >> vectSize;
    bulkVect.resize(vectSize);
    for (auto i = bulkVect.begin(); i < bulkVect.end(); i++)
        *i = randomDouble();

    cout << "Proc: " << rank << " bulkVect: " << bulkVect << endl;

    //initializing array of subCounts 
    int tempDisp = 0;
    for (int i = 0; i < commSize; i++) {
        int range = calcSubRange(i, commSize, vectSize);
        tempDisp += range;
        subCount[i] = range;
        displacements[i] = tempDisp;
    }
    cout << "\nsubCount: " << subCount;
    cout << "\nDisplacements: " << displacements << endl;
    MPI_Bcast(&subCount, commSize,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&displacements, commSize, MPI_INT, 0, MPI_COMM_WORLD);

    //testing out scatterV
    //used to evenly distribute elements among an uneven number of processes 
    MPI_Scatterv(bulkVect.data(), subCount.data(), displacements.data(), MPI_DOUBLE, subVector.data(), subCount[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    cout << "Proc: " << rank << "   range: " << subCount[rank] << " subVect: " << subVector << endl;
    calcVariance(subVector, subCount[rank], recvMean);
    cout << "Variance from proc " << rank << ":  " << recvMean / commSize << endl;
}
else {
    MPI_Bcast(&subCount, commSize, MPI_INT, 0, MPI_COMM_WORLD); //blocking other processes 
    MPI_Bcast(&displacements, commSize, MPI_INT, 0, MPI_COMM_WORLD); //ensuring subCount & displ is broadcasted
    subVector.resize(subCount[rank]);
    MPI_Scatterv(NULL, NULL, NULL, MPI_DOUBLE, subVector.data(), subCount[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    cout << "Proc: " << rank << "   range: " << subCount[rank] << " subVect: " << subVector << endl;
    calcVariance(subVector, subCount[rank], recvMean);
    /*
        double sum = 0;
    for (auto temp : subVector) //calculating local mean (within sub processes' subVector) 
        sum += temp;
    double localMean = sum / subCount[rank];
    MPI_Reduce(&localMean, &recvMean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    //adding localMean to globalMean 
    double localVariance = 0;
    for (auto temp : subVector)
        localVariance += (temp - recvMean) * (temp - recvMean);
    */
}

MPI_Finalize();
return 0;
}  


/*
*------------------------------------------
* ex1_remastered.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACION
* CC3086 - Programacion de Microprocesadores
*
* by Samuel Chamalé
* jueves, 25 de agosto del 2022
*------------------------------------------
* Description: Basic program that multiplies prime numbers given an interval (Using threads).
*------------------------------------------
*/
#include <iostream>
#include <pthread.h>
#include <bits/stdc++.h>
#include <string>
using namespace std;

int NTHREADS, LIMIT;

void askData();
void calculateSeparation();
void coutSplitter();
bool isPrime(int n);

struct intervalData {
    int begin;
    int end;
    int id;
};
intervalData *threadData;

void *CALC(void *arg) {
    intervalData *pointer = (intervalData*) arg;
    int thisId = pointer -> id;
    int thisBegin = pointer -> begin;
    int thisEnd = pointer -> end; 
    long threadSum = 0;

    coutSplitter(); 
    std::cout << "Thread: " + std::to_string(thisId) << std::endl; 
    std::cout << "Lower limit: " + std::to_string(thisBegin) << std::endl;  
    std::cout << "Upper limit: " + std::to_string(thisEnd) << std::endl;  

    for (int i = thisBegin; i < thisEnd; i++)
        if(isPrime(i))
           threadSum += i;

    std::cout << "Sum of thread: " + std::to_string(threadSum) << std::endl;  

    return (void*) threadSum;
}

int main(int argc, char *argv[]) {
    askData();
    calculateSeparation();

    pthread_t threads[NTHREADS];
    
    void *individualSum;
    long int totalSum = 0;
    
    for (int i = 0; i < NTHREADS; i++) {        
        pthread_create(&threads[i], nullptr, CALC, &threadData[i]);
        pthread_join(threads[i], &individualSum);
        totalSum += (long) individualSum;
    }
    
    std::cout << "Total amount: " + std::to_string(totalSum) << std::endl;  
    return 0;
}

void askData() {
    cout << "MAX VALUE: ";
    cin >> LIMIT;
    cout << "N-THREADS: ";
    cin >> NTHREADS;
}

void calculateSeparation() {    
    int N = LIMIT / NTHREADS;
    int ODD = LIMIT % 2;
    
    threadData = new intervalData[NTHREADS];
    
    std::cout << "Values per thread: " + std::to_string(N) << std::endl;
    std::cout << "Remainder: " + std::to_string(ODD) << std::endl;
    std::cout << "Looking for prime numbers... "<< std::endl;
    
    for (int i = 0; i < NTHREADS; i++) {           
        threadData[i].id = i; 
        threadData[i].begin = N * i;
        
        if(i == (NTHREADS - 1)) {
            while ( (NTHREADS * N + ODD) <= LIMIT)  
                ODD++;
            threadData[i].end = N * (i+1) + ODD;
        } else {
            threadData[i].end = N * (i+1);
        }
    }
}

void coutSplitter() {
    std::cout << "------------------------------------------"<< std::endl; 
}

bool isPrime(int n) {   
    if (n <= 1)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;     
    std::cout << n << std::endl; 
    return true;
}

// REFERENCES
// https://www.geeksforgeeks.org/prime-numbers/
// https://en.cppreference.com/w/cpp/string/basic_string/to_string
// https://www.tutorialspoint.com/cplusplus/cpp_data_types.htm
// https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/ThreadArgs.html
// https://stackoverflow.com/questions/21323628/warning-cast-to-from-pointer-from-to-integer-of-different-size

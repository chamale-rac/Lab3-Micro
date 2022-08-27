/*
*------------------------------------------
* ex2_remastered.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACION
* CC3086 - Programacion de Microprocesadores
*
* by Samuel Chamalé
* viernes, 26 de agosto del 2022
*------------------------------------------
* Description: Basic program that calculate the convergence of Σn 3/2^n;
*------------------------------------------
*/

#include <iostream>
#include <pthread.h>
#include <bits/stdc++.h>
#include <string>
#include <cmath>

using namespace std;

string textIntro = "Calculate the convergence of Σn 3/2^n\nn: ";

void *CALC(void* arg){	
	long input;
	input = (long) arg;
	double* output = (double*) malloc(sizeof(double));
	*output = 3/(pow(2,input));
	return output;
}

int main(int argc, char *argv[]) {
    int nSERIES;
    
    
    std::cout << textIntro; 
    cin >> nSERIES;

    pthread_t threads[nSERIES];
    
    void *exit_value;
    double CONVERGENCE = 0;

    for (long i = 0; i < nSERIES; i++) {
        pthread_create(&threads[i], nullptr, CALC, (void*)i);
        pthread_join(threads[i], &exit_value);
        double dbl = *(double*) exit_value;
        CONVERGENCE += dbl;
    }
    
    CONVERGENCE = 6 - CONVERGENCE;

    std::cout << "Result: " << CONVERGENCE << std::endl;
    return 0;
}

//REFERENCES 
// https://stackoverflow.com/questions/15350776/how-to-return-a-double-value-from-pthread-in-c
// https://www.symbolab.com/solver/series-calculator/%5Csum_%7Bn%3D3%7D%5E%7B%5Cinfty%7D%20%5Cfrac%7B3%7D%7B2%5E%7Bn%7D%7D?or=input
// https://www.w3schools.com/cpp/cpp_strings.asp
// https://stackoverflow.com/questions/19387647/c-invalid-cast-from-type-void-to-type-double

#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"
#include<math.h>

using namespace std;

/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){
    
    for (int i=0; i<=n; i++) {
        H[i][0] = 0;
        P[i][0] = '0';
    }
    for (int j=0; j<=m; j++) {
        H[0][j] = 0;
        P[0][j] = '0';
    }

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            int val1;
            int val2 = H[i-1][j]-1;
            int val3 = H[i][j-1]-1;
            if (X[i-1] == Y[j-1]) {
                val1 = H[i-1][j-1]+2;
            } 
            else {
                val1 = H[i-1][j-1]-1;
            }
            H[i][j] = max(val1, max(val2, val3));

            if (H[i][j] == val1) {
                P[i][j] = 'D';
            }
            else if (H[i][j] == val2) {
                P[i][j] = 'U';
            }
            else {
                P[i][j] = 'L';
            }
        }
    }
}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW(char* X, char* Y, char** P, int** H, int n, int m){

}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m){
	
}

/*
 * Print X'
 */
void print_Seq_Align_X(char* X, char** P, int n, int m){
	if (n>=0 && m>=0) {
        if (P[n][m] == 'D') {
            print_Seq_Align_X(X, P, n-1, m-1);
            cout << X[n];
        }
        else if (P[n][m] == 'L') {
            print_Seq_Align_X(X, P, n, m-1);
            cout << X[n];
        }
        else {
            print_Seq_Align_X(X, P, n-1, m);
            cout << '-';
        }
    }
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m){
	if (n>=0 && m>=0) {
        if (P[n][m] == 'D') {
            print_Seq_Align_Y(Y, P, n-1, m-1);
            cout << Y[n];
        }
        else if (P[n][m] == 'L') {
            print_Seq_Align_Y(Y, P, n, m-1);
            cout << '-';
        }
        else {
            print_Seq_Align_Y(Y, P, n-1, m);
            cout << Y[n];
            
        }
    }
}

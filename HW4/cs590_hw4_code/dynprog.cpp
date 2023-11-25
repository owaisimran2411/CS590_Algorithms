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
            H[i][j] = max(max(val1, max(val2, val3)), 0);

            if (H[i][j] == val1) {
                P[i][j] = '3'; // 3 = diagonal
            }
            else if (H[i][j] == val2) {
                P[i][j] = '2'; // 2 = up
            }
            else if (H[i][j] == val3) {
                P[i][j] = '1'; // 1 = left
            }
        }
    }
}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW(char* X, char* Y, char** P, int** H, int n, int m){
    for (int i=0; i<=n; i++) {
        for(int j=0; j<=m; j++) {
            H[i][j] = -1;
            P[i][j] = 'X';
        }
    }
    int max = memoized_SW_AUX(X, Y, P, H, n, m);
    return max;
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m){
	if (m==0 || n ==0) {
        H[n][m] = 0;
        return H[n][m];
    }
    else {
        if (H[n][m] != -1) {
            return H[n][m];
        }
        int val1=0;
        // int val2 = memoized_SW_AUX(X, Y, P, H, n, m-1)-1;
        // int val3 = memoized_SW_AUX(X, Y, P, H, n-1, m)-1;
        if (X[n-1]==Y[m-1]) {
            val1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1)+2;
        }
        else if (X[n-1] != Y[m-1]) {
            val1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1)-1;
        }
        int val2 = memoized_SW_AUX(X, Y, P, H, n, m-1)-1;
        int val3 = memoized_SW_AUX(X, Y, P, H, n-1, m)-1;
        int val = max(0, max(val1, max(val2, val3)));
        if (val == val1) {
            P[n][m] = '3';
        }
        else if (val == val2) {
            P[n][m] = '1';
        }
        else if (val == val3) {
            P[n][m] = '2';
        }
        H[n][m] = val;
        return H[n][m];
         
    }
}

/*
 * Print X'
 */
void print_Seq_Align_X(char* X, char** P, int n, int m){
	if (m>=0 && n>=0) {
        if (P[n][m] == '3') {
            print_Seq_Align_X(X, P, n-1, m-1);
            cout << X[n-1];
        }
        else {
            if (P[n][m] == '1') {
                print_Seq_Align_X(X, P, n, m-1);
                cout << '-';
                // cout << X[n-1];
            }
            else {
                print_Seq_Align_X(X, P, n-1, m);
                cout << X[n-1];
            }
        }
    }
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m){
   if (m>=1 && n>=1) {
        if (P[n][m] == '3') {
            print_Seq_Align_Y(Y, P, n-1, m-1);
            cout << Y[m-1];
        }
        else {
            if (P[n][m] == '1') {
                print_Seq_Align_Y(Y, P, n, m-1);
                cout << Y[m-1];
                // cout << X[n-1];
            }
            else {
                print_Seq_Align_Y(Y, P, n-1, m);
                cout << '-';
                // cout << Y[m-1];
            }
        }
    }
}

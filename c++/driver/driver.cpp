//https://replit.com/join/fvraorugvy-selinaliu3
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;


//part 1
//iteration
int lcs_it(int** c,string x,string y, int m, int n){
    for(int i=0;i<=m;i++)
        c[i][0]=0;   // Eg LCS of "abc" & "" = 0
    for(int j=0;j<=n;j++)
        c[0][j]=0;   // Eg LCS of "" & "abc" = 0

    for(int i=1;i<m+1;i++){

        for(int j=1;j<n+1;j++){
          // if current character of `X` and `Y` matches
            if(x[i-1]==y[j-1]){
              c[i][j]=1+c[i-1][j-1];
            }else{
              // otherwise, if the current character of `X` and `Y` don't match
                c[i][j]=max(c[i-1][j],c[i][j-1]);
            }
        }

    }
    return c[m][n];
}
//recursion
string backtrack(int **c, string x, string y, int m, int n) {
// return an empty string if the end of either sequence is reached
    if (n == 0 || m == 0)
        return string("");
  // if the last character of `X` and `Y` matches
    if(x[m-1]==y[n-1])
    // append current character (`X[m-1]` or `Y[n-1]`) to LCS of
    // substring `X[0…m-2]` and `Y[0…n-2]`
        return backtrack(c,x,y,m-1,n-1)+x[m-1];
    // otherwise, if the last character of `X` and `Y` are different
 
    // if a top cell of the current cell has more value than the left
    // cell, then drop the current character of string `X` and find LCS
    // of substring `X[0…m-2]`, `Y[0…n-1]`
    if(c[m-1][n]>c[m][n-1]){
        return backtrack(c,x,y,m-1,n);
    }else{
      // if a left cell of the current cell has more value than the top
      // cell, then drop the current character of string `Y` and find LCS
      // of substring `X[0…m-1]`, `Y[0…n-2]`
        return backtrack(c,x,y,m,n-1);
    }


}

//part 2
//iteration
int lcs_it_test( string x,string y, int m, int n){
    vector<int> temp(n+1,0);
    vector<vector<int>>dp(m+1,temp);
    int start_s, stop_s;
    for(int i=1;i<m+1;i++){
        start_s=clock();
        for(int j=1;j<n+1;j++){
            if(x[i-1]==y[j-1]){
                dp[i][j]=1+dp[i-1][j-1];
            }else{
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        stop_s=clock();
        clog << i << "\t" << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    }
    return dp[m][n];
}

// recursion
int lcs_re(string x, string y, int n, int m) {
    int start_s, stop_s;

    start_s = clock();

    if (n == 0 || m == 0){
  
        return 0;
    }


    if (x[n - 1] == y[m - 1]) {
            stop_s = clock();
            clog << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;

        return 1 + lcs_re(x, y, n - 1, m - 1);}


    else {
        stop_s = clock();
        clog << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;
        return max(lcs_re(x, y, m, n - 1), lcs_re(x, y, m - 1, n));
    }
}



#include<bits/stdc++.h>
#include<pthread.h>
#include<time.h>
long long int n;
long long int** mat;
long long int** mat1;
long long int** res;

using namespace std;


int main(int argc, char **argv)
{
    
     
   
    
    n= atoi((argv[1]));
    long long int r=0;
    mat = new long long int*[n];
    for(int i = 0; i < n; ++i)
        mat[i] = new long long int[n];
    mat1 = new long long int*[n];
    for(int i = 0; i < n; ++i)
        mat1[i] = new long long int[n];
    res = new long long int*[n];
    for(int i = 0; i < n; ++i)
        res[i] = new long long int[n];
    
  
    for(long long int i=0;i<n;i++)
    {
        for(long long int j=0;j<n;j++)
        {
            mat[i][j]=rand() % 300;
        }
    }
    cout<<"Matrix 1"<<endl<<endl;
    for(long long int i=0;i<n;i++)
    {
        for(long long int j=0;j<n;j++)
        {
            cout<<mat[i][j]<<"   ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    for(long long int i=0;i<n;i++)
    {
        for(long long int j=0;j<n;j++)
        {
            mat1[i][j]=rand() % 300;
        }
    }
    cout<<"Matrix 2"<<endl<<endl;
    for(long long int i=0;i<n;i++)
    {
        for(long long int j=0;j<n;j++)
        {
            cout<<mat1[i][j]<<"   ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < n; k++)
                res[i][j] += mat[i][k] * mat1[k][j];
        }
    }
    cout<<endl<<endl<<endl;
    cout<<"Resultant Matrix\n";
    for(long long int i=0;i<n;i++)
    {
        for(long long int j=0;j<n;j++)
        {
            cout<<res[i][j]<<"  ";
        }
        cout<<endl;
    }
    
    
    
}

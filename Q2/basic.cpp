#include<iostream>
#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
long long int n;
long long int** mat;
long long int** mat1;
long long int** res;
int* a;

using namespace std;

void *printer(void *argment)
{
    int *ptr = (int *) argment;
    
    int in= (*ptr)*n/8;
    int ed;
    ed = ((*ptr)+1)*n/8;
    for(int i=in;i<ed;i++)
    {
        for(int j=0;j<n;j++)
        {
            res[i][j]=0;
            for(int k=0;k<n;k++)
            {
                res[i][j]+=mat[i][k]*mat1[k][j];
            }
        }
    }
    
    
    pthread_exit(NULL);
}
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
    
    //long long int mat[n][n];
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
    pthread_t thrds[8];
    a = new int[8];
    
    for(long long int i=0;i<8;i++)
    {
        
        a[i]=i;
        
        
    }
    int u=0;
    pthread_create(&thrds[0],NULL,printer,(void *)(&u));
    pthread_create(&thrds[1],NULL,printer,(void *)(&a[1]));
    pthread_create(&thrds[2],NULL,printer,(void *)(&a[2]));
    pthread_create(&thrds[3],NULL,printer,(void *)(&a[3]));
    pthread_create(&thrds[4],NULL,printer,(void *)(&a[4]));
    pthread_create(&thrds[5],NULL,printer,(void *)(&a[5]));
    pthread_create(&thrds[6],NULL,printer,(void *)(&a[6]));
    pthread_create(&thrds[7],NULL,printer,(void *)(&a[7]));
    
    pthread_join(thrds[0],NULL);
    pthread_join(thrds[1],NULL);
    pthread_join(thrds[2],NULL);
    pthread_join(thrds[3],NULL);
    pthread_join(thrds[4],NULL);
    pthread_join(thrds[5],NULL);
    pthread_join(thrds[6],NULL);
    pthread_join(thrds[7],NULL);
    cout<<"Resultant Matrix"<<endl;
    for(long long int i=0;i<n;i++)
    {
        for(long long int j=0;j<n;j++)
        {
            cout<<res[i][j]<<"  ";
        }
        cout<<endl;
    }
    
    
    pthread_exit(NULL);
}
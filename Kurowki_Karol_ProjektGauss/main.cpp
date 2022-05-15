#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

unsigned reading(double **&A, double *&B,string fileName);//tworzenie macierzy oraz wczytanie danych z pliku
void displayMatrix(double **&A,int matrix_size);//wyswietlanie macierzy
void delMatrix(double **&A, double *&B);//usuwa macierze
int maxFromLine(double **A,unsigned i,unsigned matrixSize);//zwraca indeks wiersza gdzie znjaduje sie najwiekszy element
void swapLines(double **A,double *B, unsigned i, unsigned matrixSize,int mj);//zamiana wiersza i z wierszem mj w macierzach
int maxFromColumn(double **A,unsigned i,unsigned matrixSize);//zwraca indeks kolumny gdzie znjaduje sie najwiekszy element
void swapColumns(double **A, unsigned i, unsigned matrixSize,int mj);//zamiana kolumny i i kolumny mj w macierzy
void zadanie1(string fileName);
void zadanie2(string fileName);
void zadanie3(string fileName);
void zadanie4(string fileName);


int main()
{

    zadanie1("z1.csv");
    //zadanie2("z1.csv");
    //zadanie3("z3.csv");
    //zadanie4("z3.csv");
    return 0;
}


unsigned reading(double **&A, double *&B,string fileName)
{

    unsigned matrix_size;
    ifstream source_file(fileName);
    if (!source_file.is_open())
    {
        cout <<"The file has not been open!"<<endl;
        exit(-1);
    }
    source_file >> matrix_size;

    A = new double*[matrix_size];
    A[0] = new double[matrix_size*matrix_size];
    for(unsigned i = 1; i< matrix_size; i++)
        A[i] = A[i-1] + matrix_size;

    B = new double[matrix_size];

    char semicolumn;
    for (unsigned i = 0; i < matrix_size+1; i++)
        source_file >> semicolumn;

    for (unsigned i = 0; i < matrix_size; i++)
    {
        for (unsigned j = 0; j < matrix_size; j++)
        {
            source_file >> A[i][j];
            source_file >> semicolumn;
        }
        source_file >> semicolumn;
        source_file >> B[i];
    }
    source_file.close();
    return matrix_size;
}



void displayMatrix(double **&A,int matrix_size)
{

    for(int i=0;i<matrix_size;i++){
        for(int j=0;j<matrix_size;j++){
            cout.width(8);
            cout.precision(4);
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

}

void delMatrix(double **&A, double *&B)
{
    delete [] B;
    delete [] A[0];
    delete [] A;
}



int maxFromLine(double **A,unsigned i,unsigned matrixSize)
{
    double  mx=abs(A[i][i]);
    int maxj=i;
    for(int j=i;j<matrixSize;j++)
    {
        if (abs(mx)<abs(A[j][i]))
        {
            mx=A[j][i];
            maxj=j;
        }
    }
    return maxj;

}
void swapLines(double **A,double *B, unsigned i, unsigned matrixSize,int mj)
{
    double sc;
    if (i!=mj){
        cout<<"zamieniany jest wiersz "<<i+1<<" i "<<mj+1<<endl;
        for (int j=i;j<matrixSize;j++)
        {
            sc=A[i][j];
            A[i][j]=A[mj][j];
            A[mj][j]=sc;
        }
        sc=B[i];
        B[i]=B[mj];
        B[mj]=sc;
        displayMatrix(A,matrixSize);
    }
}

int maxFromColumn(double **A,unsigned i,unsigned matrixSize)
{
    double  mx=abs(A[i][i]);
    int maxj=i;
    for(int j=i;j<matrixSize;j++)
    {

        if (abs(mx)<abs(A[i][j]))
        {

            mx=A[i][j];
            maxj=j;

        }

    }

    return maxj;
}
void swapColumns(double **A, unsigned i, unsigned matrixSize,int mj)
{
    double sc;
    if (i!=mj){
        cout<<"zamieniana jest kolumna "<<i+1 <<" i "<<mj+1<<endl;
        for (int j=0;j<matrixSize;j++)
        {
            sc=A[j][i];
            A[j][i]=A[j][mj];
            A[j][mj]=sc;
        }
        displayMatrix(A,matrixSize);
    }
}
void zadanie1(string fileName)
{
    cout<<"zadanie 1"<<endl;
    double** A=nullptr;
    double* B=nullptr;
    int mj;
    unsigned matrixSize = reading(A,B,fileName);
    cout<<matrixSize<<endl;
    displayMatrix(A,matrixSize);
    cout<<endl;
    double p;
    for(int i=0;i<matrixSize-1;i++)// i = numer kroku
    {

        if (A[i][i]!=0)
        {cout<<"krok "<<i+1<<endl;

            for(int j=i+1;j<matrixSize;j++)// j = indeks p,numer wiersza
            {
                p=A[j][i]/A[i][i];
                cout<<"p = "<<p<<endl;
                if(p==0)continue;
                else {for(int k=i;k<matrixSize;k++)// obliczanie nowych elementow wiersza
                    {
                        A[j][k]=A[j][k]-(p*A[i][k]);
                    }
                    B[j]=B[j]-p*B[i];
                }
                displayMatrix(A,matrixSize);
            }
        }
        else {
            cout<<"wykonaie algorytmu nie jest mozliwe"<<endl;
            exit(1);

        }
    }
    cout<<"matrix b:"<<endl;
    cout<<B[0]<<endl;
    cout<<B[1]<<endl;
    cout<<B[2]<<endl;
    double xl,xm=0;
    double x[matrixSize];
    for (int i=matrixSize-1;i>=0;i--)
    {
        xm=0;
        for(int j=matrixSize-1;j>i;j--)
        {
            xm+=A[i][j]*x[j];
        }

        xl=(B[i]-xm)/(A[i][i]);
        x[i]=xl;
    }
    cout<<"Wyniki:"<<endl;
    for(int i=0;i<matrixSize;i++)
    {
        cout<<"x"<<i+1<<" = "<<x[i]<<endl;
    }
    cout<<endl;
    delMatrix(A,B);
}

void zadanie2(string fileName)
{
    cout<<"zadanie 2"<<endl;
    double** A=nullptr;
    double* B=nullptr;

    int mj;

    unsigned matrixSize = reading(A,B,fileName);
    cout<<matrixSize<<endl;
    displayMatrix(A,matrixSize);
    cout<<endl;
    double p;
    for(int i=0;i<matrixSize-1;i++)// i =numer kroku
    {
        if (A[i][i]!=0)
        {cout<<"krok "<<i+1<<endl;
            mj=maxFromLine(A,i,matrixSize);
            swapLines(A,B,i,matrixSize,mj);
            for(int j=i+1;j<matrixSize;j++)// j = indeks p
            {
                p=A[j][i]/A[i][i];
                cout<<"p = "<<p<<endl;
                if(p==0)continue;
                else {for(int k=i;k<matrixSize;k++)
                    {
                        A[j][k]=A[j][k]-(p*A[i][k]);
                    }
                    B[j]=B[j]-p*B[i];
                }
                displayMatrix(A,matrixSize);
            }
        }
        else {
            cout<<"wykoanie algorytmu nie jest mozliwe"<<endl;
            exit(1);
        }
    }

    double xl,xm=0;
    double x[matrixSize];
    for (int i=matrixSize-1;i>=0;i--)
    {
        xm=0;
        for(int j=matrixSize-1;j>i;j--)
        {
            xm+=A[i][j]*x[j];
        }

        xl=(B[i]-xm)/(A[i][i]);
        x[i]=xl;

    }
    cout<<"Wyniki:"<<endl;
    for(int i=0;i<matrixSize;i++)
    {
        cout<<"x"<<i+1<<" = "<<x[i]<<endl;
    }
    cout<<endl;
    delMatrix(A,B);

}

void zadanie3(string fileName)
{
    cout<<"zadanie 3"<<endl;
    double** A=nullptr;
    double* B=nullptr;

    int mj;
    int var;

    unsigned matrixSize = reading(A,B,fileName);
    int tabChanges[matrixSize];
    for (int i=0;i<matrixSize;i++)
    {
        tabChanges[i]=i;
    }
    cout<<matrixSize<<endl;
    displayMatrix(A,matrixSize);
    cout<<endl;
    double p;
    for(int i=0;i<matrixSize-1;i++)// i =numer kroku
    {

        if (A[i][i]!=0)
        {cout<<"krok "<<i+1<<endl;

            mj=maxFromColumn(A,i,matrixSize);
            swapColumns(A,i,matrixSize,mj);
            if (i!=mj){
                var=tabChanges[i];
                tabChanges[i]=tabChanges[mj];
                tabChanges[mj]=var;
            }
            for(int j=i+1;j<matrixSize;j++)// j = indeks p
            {
                p=A[j][i]/A[i][i];
                cout<<"p = "<<p<<endl;
                if(p==0)continue;
                else {for(int k=i;k<matrixSize;k++)
                    {
                        A[j][k]=A[j][k]-(p*A[i][k]);
                    }
                    B[j]=B[j]-p*B[i];
                }
                displayMatrix(A,matrixSize);
            }
        }
        else {
            cout<<"wykoanie algorytmu nie jest mozliwe"<<endl;
            exit(1);
        }
    }

    double xl,xm=0;
    double x[matrixSize];
    for (int i=matrixSize-1;i>=0;i--)
    {
        xm=0;
        for(int j=matrixSize-1;j>i;j--)
        {
            xm+=A[i][j]*x[j];
        }
        xl=(B[i]-xm)/(A[i][i]);
        x[i]=xl;
    }
    cout<<"Wyniki:"<<endl;
    for(int i=0;i<matrixSize;i++)
    {
        cout<<"x"<<tabChanges[i]+1<<" = "<<x[i]<<endl;
    }
    cout<<endl;
    delMatrix(A,B);

}

void zadanie4(string fileName)
{
    cout<<"zadanie 4"<<endl;
    double** A=nullptr;
    double* B=nullptr;
    int mj;
    int var;
    unsigned matrixSize = reading(A,B,fileName);
    int tabChanges[matrixSize];
    for (int i=0;i<matrixSize;i++)
    {
        tabChanges[i]=i;

    }
    cout<<matrixSize<<endl;
    displayMatrix(A,matrixSize);
    cout<<endl;
    double p;
    for(int i=0;i<matrixSize-1;i++)// i =numer kroku
    {

        if (A[i][i]!=0)
        {cout<<"krok "<<i+1<<endl;
            mj=maxFromLine(A,i,matrixSize);
            swapLines(A,B,i,matrixSize,mj);
            mj=maxFromColumn(A,i,matrixSize);
            swapColumns(A,i,matrixSize,mj);
            if (i!=mj){
                var=tabChanges[i];
                tabChanges[i]=tabChanges[mj];
                tabChanges[mj]=var;

            }
            for(int j=i+1;j<matrixSize;j++)// j = indeks p
            {
                p=A[j][i]/A[i][i];
                cout<<"p = "<<p<<endl;
                if(p==0)continue;
                else {for(int k=i;k<matrixSize;k++)
                    {
                        A[j][k]=A[j][k]-(p*A[i][k]);
                    }
                    B[j]=B[j]-p*B[i];
                }
                displayMatrix(A,matrixSize);
            }
        }
        else {
            cout<<"wykoanie algorytmu nie jest mozliwe"<<endl;
            exit(1);
        }
    }

    double xl,xm=0;
    double x[matrixSize];

    for (int i=matrixSize-1;i>=0;i--)
    {
        xm=0;
        for(int j=matrixSize-1;j>i;j--)
        {
            xm+=A[i][j]*x[j];
        }

        xl=(B[i]-xm)/(A[i][i]);
        x[i]=xl;
    }
    cout<<"Wyniki:"<<endl;
    for(int i=0;i<matrixSize;i++)
    {
        cout<<"x"<<tabChanges[i]+1<<" = "<<x[i]<<endl;
    }
    cout<<endl;
    delMatrix(A,B);

}

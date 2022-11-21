#include <iostream>
#include <algorithm>
#include <ctime>
#include <stdlib.h>

using namespace std;

void wstawianie(int A[],int wielkosc)
{
    for(int k=1; k<wielkosc; k++)
    {
        int temp = A[k];
        int j= k-1;
        while(j>=0 && temp <= A[j])
        {
            A[j+1] = A[j];
            j = j-1;
        }
        A[j+1] = temp;
    }
}

void kopiec(int A[],int wielkosc , int i){
    int lewe =2*i+1;
    int prawe=2*i+2;
    int najwieksza=i;

    if(lewe<wielkosc && A[lewe]>A[i])
    {
        najwieksza=lewe;
    }

    if(prawe<wielkosc && A[prawe]>A[najwieksza])
    {
        najwieksza=prawe;
    }

    if(najwieksza != i)
    {
        swap(A[i],A[najwieksza]);
        kopiec(A,wielkosc,najwieksza);
    }

}

void kopiec_builder(int A[],int wielkosc)
{
    for(int i=(wielkosc/2);i>=0;i--)
    {
        kopiec(A,wielkosc,i);
    }
}

void kopiec_sort(int A[],int wielkosc)
{
    kopiec_builder(A,wielkosc);
    for(int i= wielkosc-1;i>=0;i--)
    {
        swap(A[0],A[i]);
        kopiec(A,wielkosc,0);
    }
}

void odwroc(int tab[], int left, int right)
{
    if(left<right)
    {
        //Zamienienie elementów skrajych
        swap(tab[left], tab[right]);
        //Odwrócenie pozostalych elementow tablicy
        odwroc(tab, left+1, right-1);
    }
}

int Partycja(int A[], int p, int r)
{
 int pivot=A[r];
 int mniejsza = p;

 for(int j=p;j<r-1;j++)
 {
        if(A[j]<=pivot)
        {
            swap(A[mniejsza],A[j]);
            mniejsza++;
        }
 }

  swap(A[mniejsza], A[r]);
    return mniejsza;
}

void QS(int A[], int p, int r)
{
    if(p<r)
    {
        int q=Partycja(A,p,r);
        QS(A,p,q-1);
        QS(A,q+1,r);
    }
}

int main() {

    clock_t startqs, koniecqs;
    long czasqs;

    srand(time(0));

    int n=50000; //(rand()%900000)+100000;
    cout<<"ilosc liczb w tablicy:"<<n<<endl;
    int A[n],B[n],C[n];

    for(int i=0;i<n-1;i++)
    {
        int k=(rand()%999)+1;
        A[i]=k;
        B[i]=k;
        C[i]=k;
    }

    startqs=clock();
    QS(A,0,n-1);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec quicksort na nieposortowanej, czas:"<<czasqs<<"ms"<<endl;

    startqs=clock();
    QS(A,0,n-1);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec quicksort na posortowanej, czas:"<<czasqs<<"ms"<<endl;

    odwroc(A,n-1,0);
    startqs=clock();
    QS(A,0,n-1);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec quicksort na posorotowanej odwroconej, czas:"<<czasqs<<"ms"<<endl;

    cout<<"---------------------------------------------------------------------------"<<endl;

    startqs=clock();
    kopiec_sort(B,n);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec kopcowania na nieposortowanej, czas:"<<czasqs<<"ms"<<endl;

    startqs=clock();
    kopiec_sort(B,n);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec kopcowania na posortowanej, czas:"<<czasqs<<"ms"<<endl;

    odwroc(B,n-1,0);
    startqs=clock();
    kopiec_sort(B,n);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec kopcowania na posorotowanej odwroconej, czas:"<<czasqs<<"ms"<<endl;

    cout<<"---------------------------------------------------------------------------"<<endl;

    startqs=clock();
    wstawianie(C,n);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec wstawiania na nieposortowanej, czas:"<<czasqs<<"ms"<<endl;

    startqs=clock();
    wstawianie(C,n);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec wstawiania na posortowanej, czas:"<<czasqs<<"ms"<<endl;

    odwroc(C,n-1,0);
    startqs=clock();
    wstawianie(C,n);
    koniecqs=clock();
    czasqs=(long)(koniecqs-startqs);
    cout<<"koniec wstawianie na posorotowanej odwroconej, czas:"<<czasqs<<"ms"<<endl;

    return 0;
}

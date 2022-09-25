#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <fstream>
using namespace std;
int main()
{
    srand(time(NULL)); //zerowanie czasu do losowania pseudolosowego
    fstream wypis;
    wypis.open("wyniki.txt",ios_base::out | ios_base::trunc); //czyszczenie pliku wyniki.txt
    wypis.close();
    int a,b,c, min, max_x, max_war_x,fsuma, pokolenia;
    double pr_krzyz, pr_mut;
    cout<<"Wpisz a, b i c do funkcji kwadratowej\nA: ";
    cin>>a;
    cout<<"B: ";
    cin>>b;
    cout<<"C: ";
    cin>>c;
    cout<<"Ile wykonan programu:";
    int wykonania;
    cin>>wykonania;
    cout<<"Ile pokolen:"; //LICZBA POPULACJI
    cin>>pokolenia;
    cout<<"Wpisz parzysta liczbe osobnikow na populacje:";
    int y;
    do
    {
    cin >>y;                                //ILE OSOBNIKÓW
    if(y%2==1) cout<<"TYLKO PARZYSTE\n y:";
    }while(y%2==1);
    cout<<"Prawdopodobienstwo KRZYZOWANIA (0-1): ";
    cin>>pr_krzyz;
    cout<<"PRAWDOPODOBIENSTWO MUTACJI:";
    cin>>pr_mut;
    int dziesietne[y], wynik[y];
    bool tab[8][y];
    double pr_wylos[y];
    for(int p=0; p<wykonania; p++)
    {
        ///Kodowanie Z DZIESIETNYCH NA BINARNY DLA CIAGU O DLUGOSCI 8
        int z;
       // cout<<"KODOWANIE\n";
        //cout<<"Zakres x -> 0-255"<<endl;
        for (int l=0;l<y;l++)
            dziesietne[l]=rand()%256; // LOSOWANIE PSEUDOLOSOWE X
      
        for(int czas = 0; czas<pokolenia; czas++)
        {
            random_shuffle(&dziesietne[0],&dziesietne[y]); // PAROWANIE POPRZEZ MIESZANIE TABLICY 
            for (int l=0;l<y;l++)
            {
                z=dziesietne[l];
                for(int i=7; i>=0; i--)     // ZAMIANA DZIESIETNYCH NA BINARNE
                {                           // Zapis od indeks 7 do 0
                    tab[i][l]=z%2;
                    z/=2;   
                }
            }   
            float r=(float)rand()/RAND_MAX;
          //  r = (roundf(r*10))/10;
           // if (r==0) r=0.1;
            for(int i=0; i<y; i+=2)
            {
                if(r<=pr_krzyz)
                {                   
                    int cut =rand()%7;    // LOSOWANIE MIEJSCA CIECIA                      
                    switch (cut)            // W Z
                    {
                        case 0:
                        for(cut+=1;cut<8;cut++)
                        {
                            swap(tab[cut][i],tab[cut][i+1]);  
                        }
                        break;
                        case 1:
                        for(cut+=1;cut<8;cut++)
                        {
                            swap(tab[cut][i],tab[cut][i+1]);  
                        }
                        break;
                        case 2:
                        for(cut+=1;cut<8;cut++)
                        {
                            swap(tab[cut][i],tab[cut][i+1]);  
                        }
                        break;
                        case 3:
                        for(cut+=1;cut<8;cut++)
                        {
                            swap(tab[cut][i],tab[cut][i+1]);  
                        }
                        break;
                        case 4:
                        for(cut+=1;cut<8;cut++)
                        {
                            swap(tab[cut][i],tab[cut][i+1]);  
                        }
                        break;
                        case 5:
                        for(cut+=1;cut<8;cut++)
                        {
                            swap(tab[cut][i],tab[cut][i+1]);  
                        }
                        break;
                        case 6:
                        for(cut+=1;cut<8;cut++)
                        {
                            swap(tab[cut][i],tab[cut][i+1]);  
                        }
                        break;
                    }
                }
            } 
            for(int l=0; l<y; l++)
            {
                for(int i=0; i<8; i++)
                {
                        
                    r=(float)rand()/RAND_MAX;
                   // r = (roundf(r*10))/10;
                  //  if (r==0) r=0.1;
                    if(r<=pr_mut)
                    {   
                        if(tab[i][l]==0) tab[i][l]=1;   //MUTACJA
                        else tab[i][l]=0;
                    }      
                }   
            }        
            min = 0;
            for(int l=0; l<y; l++)
            {
                int pot=0, pom=0;
                for(int i=7; i>=0; i--)
                {           
                    pom=pom+(tab[i][l] *pow(2,pot));   // ZAMIANA Z BINARNYCH NA DZIESIETNE
                    pot++;
                }
                dziesietne[l]=pom;
                wynik[l]=a*dziesietne[l]*dziesietne[l]+b*dziesietne[l]+c;
                if (wynik[l]<min) min = wynik[l];
            }
            if (min<0) for(int l=0; l<y; l++) wynik[l]+=abs(min)+1; // DODAWANIE MINIMALNEJ DO KAŻDEGO WYNIKU
             fsuma =0;
            for(int l=0; l<y; l++) fsuma+=wynik[l]; //SUMOWANIE WSZYSTKICH F(X)
            for(int l=0; l<y; l++) pr_wylos[l] = double(wynik[l])/fsuma; // WYLICZANIE PRAWDOPODOBIEŃST DLA KAŻDEGO OSOBNIKA
            for(int l=0; l<y; l++)
            {
                for(int k=1; k<y-l; k++) /// SORTOWANIE PRAWDOPODOBIENST ORAZ X W TABLICACH
                    if(pr_wylos[k-1]>pr_wylos[k])
                    {
                        swap(pr_wylos[k-1], pr_wylos[k]);       
                        swap(dziesietne[k-1],dziesietne[k]);
                    }   
            } 
            int pomocnicza_tab[y];
            for(int l=0; l<y; l++)
            {
                float r=(float)rand()/RAND_MAX;
              //  r = (roundf(r*10))/10;
               // if (r==0)  r=0.1;
               // else if(r==1) r=0.9;
                
                
                double pom1=0,pom2=0;
                for(int k=0; k<y; k++)
                {
                    pom2+=pr_wylos[k];          
                    if(r < pom2) // SPRAWDZANIE CZY WYLOSOWANA WARTOŚĆ MIEŚCI SIĘ W PRZEDZIALE
                    {
                        pomocnicza_tab[l]=dziesietne[k]; // WYPIS DO POMOCNICZEJ TABLICY WYLOSOWANYCH X
                        break;
                    }
                } 
        
            }
            for(int l=0; l<y; l++) dziesietne[l]= pomocnicza_tab[l]; // PODMIANA WARTOSCI Z TABLICY POMOCNICZEJ DO GŁÓWNEJ TABLICY
            max_war_x = a*dziesietne[0]*dziesietne[0]+b*dziesietne[0]+c;
            max_x = dziesietne[0];
            for(int l=1; l<y; l++)
                if(a*dziesietne[l]*dziesietne[l]+b*dziesietne[l]+c>max_war_x)
                {
                    max_war_x = a*dziesietne[l]*dziesietne[l]+b*dziesietne[l]+c;
                    max_x = dziesietne[l];
                }
        }
        wypis.open("wyniki.txt", ios_base::app);// OTWARCIE PLIKU WYNIKI.TXT
        wypis<<max_war_x<<" "<<max_x<<endl; // WYPIS DO PLIKU
        wypis.close(); // ZAMKNIECIE PLIKU
    }
    return 0;
}


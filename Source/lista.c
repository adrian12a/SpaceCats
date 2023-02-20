#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "kolizja.h"

struct list{// struktura listy
    int data;// pole z wartoscia wprowadzana w funkcji push
    struct list *next;// wksaznik na nastepny element listy
};

struct list_pointers
{
    struct list *first,*last;// wskazniki na pierwszy i ostatni element listy
}l;

 void push(struct list_pointers *l,int data)// wprowadzanie nowego elementu na koniec listy
{
    struct list *node = (struct list*)malloc(sizeof(struct list));// nowy wezel
        node->data = data;// wprowadzenie wartosci data do nowego elementu w liscie
        node->next = NULL;// nowy element jest ostatnim elementem listy, zatem wskaznik na nastepny element jest pusty
        if(l->first==NULL)// gdy lista jest pusta
            l->first = l->last = node;// nowy element jest jednoczesnie pierwszym i ostatnim
        else// gdy lista nie jest pusta
        {
            l->last->next = node;// nowy element jest elementem nastepnym od dotychczasowego ostatniego elementu
            l->last = node;// nowy element zostaje nowym elementem ostatnim
        }
}

int pop(struct list_pointers *l)// usuwanie elementu z konca listy
{
    if(l->first){// gdy lista nie jest pusta
        int data = l->last->data;// pobranie wartosci data z elementu do usuniecia
        if(l->first == l->last)// gdy lista ma tylko jeden element
        {
            l-> first = l->last = NULL;// lista staje sie pusta
        }
        else// gdy lista ma wiecej niz jeden element
        {
            struct list *temp = l->first;// tymczasowy wskaznik na pierwszy element
            while(temp->next!=l->last)// przechodzimy po kolejnych elementach listy, az do uzyskania przedostatniego elementu
            temp = temp->next;
            free(l->last);// zwalniamy pamiec ostatniego elementu
            l->last = temp;// nowym ostatnim elementem zostaje element przedostatni
            l->last->next = NULL;// pusty wskaznik na element nastepny od ostatniego
        }
        return data;// zwracamy wartosc data z usunietego elementu
    }
    else
        return 0;
}

void clear(struct list_pointers *l)// wyczyszczenie calej listy
{
    while(l->first!=NULL)// usuwamy element z konca listy dopoki lista nie jest pusta
        pop(l);
}

 int draw(struct list_pointers *l,ALLEGRO_BITMAP *kula,ALLEGRO_BITMAP *statek,int x,int y,int vy_pocisk_boss)
{
    int kolizja_gracz = 0;// 0 - gdy nie nastapila kolizja pocisku z graczem
    int random = rand()%+1000;// losowanie wartosci wspolrzednej x pocisku
    if(vy_pocisk_boss==700)// resetowanie pozycji, gdy pociski wyleca poza mape
        clear(l);
    if(l->first==NULL)// wprowadzenie danych, gdy lista jest pusta
    {
        for(int i=0;i<3;i++)
        push(l,random*(i+1));
    }
    else// wprowadzenie danych, gdy lista nie jest pusta
    {
        {// wyswietlenie bitmap na bufor ekranu
            al_draw_bitmap(kula,l->first->data,vy_pocisk_boss+100,0);
            al_draw_bitmap(kula,l->first->next->data,vy_pocisk_boss+100,0);
            al_draw_bitmap(kula,l->first->next->next->data,vy_pocisk_boss+100,0);
            al_draw_bitmap(kula,vy_pocisk_boss+100,vy_pocisk_boss+100,0);
            al_draw_bitmap(kula,vy_pocisk_boss+100,300,0);
        }
    }
    if(kolizja(statek,x,y,kula,vy_pocisk_boss+100,300)||kolizja(statek,x,y,kula,vy_pocisk_boss+100,vy_pocisk_boss+100)||kolizja(statek,x,y,kula,l->first->data,vy_pocisk_boss+100)||kolizja(statek,x,y,kula,l->first->next->data,vy_pocisk_boss+100)||kolizja(statek,x,y,kula,l->first->next->next->data,vy_pocisk_boss+100))// sprawdzanie kolizji
        kolizja_gracz=1;// 1 - gdy nastapila kolizja pocisku z graczem
    return kolizja_gracz;// zwracamy wartosc kolizji z graczem
}

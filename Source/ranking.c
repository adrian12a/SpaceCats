#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void rank(int score,int score_rank[6],char nick[3],char nick_rank[6][3],int display,ALLEGRO_FONT *font)// ranking
{
    if(display==0)// tryb wprowadzania danych
    {
        char tmp_nick[3];// tablica tymczasowo przechowujaca nazwy graczy
        int tmp;// zmienna tymczasowo przechowyujaca wyniki
        score_rank[5]=score;// wprowadzenie wyniku na 6 miejsce w rankingu
        nick_rank[5][0]=nick[0];// wprowadzenie nazwy gracza na 6 miejsce w rankingu
        nick_rank[5][1]=nick[1];// wprowadzenie nazwy gracza na 6 miejsce w rankingu
        nick_rank[5][2]=nick[2];// wprowadzenie nazwy gracza na 6 miejsce w rankingu
        for(int j=0;j<6;j++)// podwojna petla dla sortowania wynikow
        for(int i=0;i<6;i++)
        if (score_rank[i-1]<score_rank[i])// sprawdzenie czy wynik nizszy w rankingu ma wieksza wartosc niz wynik znajdujacy sie wyzej
            {
                tmp = score_rank[i-1];// zamiana wartosci wynikow w rankingu
                score_rank[i-1] = score_rank[i];
                score_rank[i] = tmp;
                tmp_nick[0] = nick_rank[i-1][0];// zamiana przypisanych do wynikow nazw gracza
                nick_rank[i-1][0] = nick_rank[i][0];
                nick_rank[i][0] = tmp_nick[0];
                tmp_nick[1] = nick_rank[i-1][1];
                nick_rank[i-1][1] = nick_rank[i][1];
                nick_rank[i][1] = tmp_nick[1];
                tmp_nick[2] = nick_rank[i-1][2];
                nick_rank[i-1][2] = nick_rank[i][2];
                nick_rank[i][2] = tmp_nick[2];
            }
    }
    if(display==1)// tryb wyswietlania rankingu
    {
        int y=200;// zmienna pozycji pionowej napisu w rankingu
       for(int k=0;k<5;k++)
       {
            al_draw_textf(font,al_map_rgb(255,255,0),300,y,0,"%d.",k+1);// tworzenie napisu - indeks miejsca w rankingu
            al_draw_textf(font,al_map_rgb(255,255,0),400,y,0,"%c%c%c",nick_rank[k][0],nick_rank[k][1],nick_rank[k][2]);// tworzenie napisu - nazwa gracza
            al_draw_textf(font,al_map_rgb(255,255,0),600,y,0,"%d",score_rank[k]);// tworzenie napisu - wynik
            y+=50;// wartosc y dla nastepnej pozycji w rankingu
       }
        al_flip_display(); // wyswietlenie aktualnego bufora na ekran
    }
}

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

bool kolizja(ALLEGRO_BITMAP *bitmapa1,double x1,double y1,ALLEGRO_BITMAP *bitmapa2,double x2,double y2)// funkcja sprawdzajaca czy wystapila kolizja
{
    int sz1=al_get_bitmap_width(bitmapa1);// szerokosc bitmapy nr 1
    int sz2=al_get_bitmap_width(bitmapa2);// szerokosc bitmapy nr 2
    int wy1=al_get_bitmap_height(bitmapa1);// wysokosc bitmapy nr 1
    int wy2=al_get_bitmap_height(bitmapa2);// wysokosc bitmapy nr 2
    if(sz1+x1<x2||x1>x2+sz2||wy1+y1<y2||y1>y2+wy2)// sprawdzanie czy nie wystepuje kolizja miedzy bitmapa nr 1 i bitmapa nr 2
        return false;// brak kolizji
    else
        return true;// kolizja
}

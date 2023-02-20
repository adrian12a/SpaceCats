#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "lista.h"
#include "kolizja.h"

int gra(ALLEGRO_EVENT_QUEUE *kolejka,ALLEGRO_TIMER *timer,ALLEGRO_EVENT events,ALLEGRO_FONT *font,char nick[3])
{
    // wczytanie muzyki
    al_reserve_samples(4);

    ALLEGRO_SAMPLE *dzwiek_pocisk = al_load_sample("pocisk.wav");// dzwiek pocisku
    ALLEGRO_SAMPLE_INSTANCE *dzwiek_pocisk_instance = al_create_sample_instance(dzwiek_pocisk);
    al_set_sample_instance_playmode(dzwiek_pocisk_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(dzwiek_pocisk_instance,al_get_default_mixer());

    ALLEGRO_SAMPLE *dzwiek_bonus = al_load_sample("bonus.wav");// dzwiek zbierania bonusu
    ALLEGRO_SAMPLE_INSTANCE *dzwiek_bonus_instance = al_create_sample_instance(dzwiek_bonus);
    al_set_sample_instance_playmode(dzwiek_bonus_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(dzwiek_bonus_instance,al_get_default_mixer());

    ALLEGRO_SAMPLE *muzyka_gra = al_load_sample("muzyka_gra.ogg");// muzyka w grze
    ALLEGRO_SAMPLE_INSTANCE *muzyka_gra_instance = al_create_sample_instance(muzyka_gra);
    al_set_sample_instance_playmode(muzyka_gra_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(muzyka_gra_instance,al_get_default_mixer());
    al_play_sample_instance(muzyka_gra_instance);

    ALLEGRO_SAMPLE *muzyka_boss = al_load_sample("muzyka_boss.ogg");// muzyka podczas walki z bossem
    ALLEGRO_SAMPLE_INSTANCE *muzyka_boss_instance = al_create_sample_instance(muzyka_boss);
    al_set_sample_instance_playmode(muzyka_boss_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(muzyka_boss_instance,al_get_default_mixer());

    // wczytanie bitmap do pamieci
    ALLEGRO_BITMAP *tlo_gry = al_load_bitmap("tlo_gry.png");
    ALLEGRO_BITMAP *statek = al_load_bitmap("statek.png");
    ALLEGRO_BITMAP *starter_pocisk = al_load_bitmap("pocisk.png");
    ALLEGRO_BITMAP *wrog = al_load_bitmap("wrog.png");
    ALLEGRO_BITMAP *pocisk_wroga = al_load_bitmap("pocisk_wroga.png");
    ALLEGRO_BITMAP *boss = al_load_bitmap("boss.png");
    ALLEGRO_BITMAP *pocisk_boss = al_load_bitmap("pocisk_boss.png");
    ALLEGRO_BITMAP *bariera = al_load_bitmap("bariera.png");
    ALLEGRO_BITMAP *laser = al_load_bitmap("laser.png");
    ALLEGRO_BITMAP *triple_pocisk = al_load_bitmap("triple_pocisk.png");
    ALLEGRO_BITMAP *kula = al_load_bitmap("kula.png");
    ALLEGRO_BITMAP *bonus0 = al_load_bitmap("bonus0.png");
    ALLEGRO_BITMAP *bonus1 = al_load_bitmap("bonus1.png");
    ALLEGRO_BITMAP *bonus2 = al_load_bitmap("bonus2.png");
    ALLEGRO_BITMAP *bonus3 = al_load_bitmap("bonus3.png");
    ALLEGRO_BITMAP *bonus4 = al_load_bitmap("bonus4.png");
    ALLEGRO_BITMAP *bonus5 = al_load_bitmap("bonus5.png");
    ALLEGRO_BITMAP *bonus6 = al_load_bitmap("bonus6.png");
    ALLEGRO_BITMAP *bonus7 = al_load_bitmap("bonus7.png");
    ALLEGRO_BITMAP *bonus8 = al_load_bitmap("bonus8.png");
    ALLEGRO_BITMAP *wrog2 = al_load_bitmap("wrog2.png");
    ALLEGRO_BITMAP *pocisk_boss_2 = al_load_bitmap("pocisk_boss_2.png");
    ALLEGRO_BITMAP *pocisk_boss_3 = al_load_bitmap("pocisk_boss_3.png");

    al_convert_mask_to_alpha(wrog, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(statek, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(boss, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(pocisk_boss, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(triple_pocisk, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(laser, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(kula, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bariera, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(wrog2, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(pocisk_boss_2, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus0, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus1, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus2, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus3, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus4, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus5, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus6, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus7, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(bonus8, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(starter_pocisk, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(pocisk_wroga, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci
    al_convert_mask_to_alpha(pocisk_boss_3, al_map_rgb(255, 0, 255));// ustawienie przezroczystosci

    int x=640;// pozycja poczatkowa pozioma statku
    int y=620;// pozycja poczatkowa pionowa statku
    int vx=0;// wektor poziomy statku
    int vy=0;// wektor pionowy statku
    double speed=1;// predkosc statku
    int check_timer=0;// sprawdzenie timera
    int vy_pocisk=-800;// wspolrzedna y pocisku nr 1 ( -800 - poczatkowa wartosc domyslna poza ekranem rozgrywki)
    int vx_pocisk=-800;// wspolrzedna x pocisku nr 1
    int vy_pocisk_2=-800;// wspolrzedna y pocisku nr 2
    int vx_pocisk_2=-800;// wspolrzedna x pocisku nr 2
    double vy_pocisk_wrog=-800;// wspolrzedna y pocisku wroga
    int vx_pocisk_wrog=-800;// wspolrzedna x pocisku wroga
    int strzal=0;// sprawdzenie wystrzelenia pocisku
    int time=0;// zliczanie czasu
    int kolizja_wrog[10][3];// kolizja wrogow
    int kolizja_gracz=0;// kolizja gracza
    int wrog_score[10];// sprawdzenie mozliwosci zapisu wyniku po pokonaniu wroga nr 1
    int poziom = 1;// liczba poziomow wrogow w fali
    int clear_poziom_1 = 0;// zestrzelenie wszystkich wrogow w poziomie 1
    int clear_poziom_2 = 0;// zestrzelenie wszystkich wrogow w poziomie 2
    double speed_wrog=1;// predkosc pociskow wroga
    int ilosc_wrogow = 3;// ilosc wrogow
    int clear_fala = 0;// sprawdzenie czy zestrzelono cala fale wrogow
    int score=0;// zmienna zapisujaca wynik gracza
    double boss_x=100;// wspolrzedna x bossa
    int boss_y=10;// wspolrzedna y bossa
    int boss_hp=10000;// puntky zdrowia bossa
    int boss_check_x=0;// sprawdza czy boss nie wylecial za daleko poza mape
    int boss_faza = 1;// faza bossa
    int fala = 1;// aktualna fala wrogow
    double vy_pocisk_boss=10;// wspolrzedna y pocisku wroga
    double wrog_x=0;// wspolrzedna x wroga
    double wrog_y=0;// wspolrzedna y wroga
    int wrog_check_x=0;// sprawdza czy wrog nie wylecial za daleko poza mape
    int bonus[10];// tablica bonusow
    int frame=0;// animacja
    int bonus_x = 150+rand()%+1100;// wspolrzedna x bonusu
    double bonus_y = rand()%+200;// wspolrzedna y bonusu
    int bonus_los = 1+rand()%+9;// losowanie bonusu
    int pocisk_gap = 0;// wyrownanie pocisku do srodka statku
    ALLEGRO_BITMAP *pocisk = starter_pocisk;// rodzaj pocisku
    ALLEGRO_BITMAP *bonus_bitmap = bonus6;// bitmapa bonus
    ALLEGRO_BITMAP *pocisk_boss_bitmap = pocisk_boss;// bitmapa bonus
    for(int i=0;i<10;i++)// wprowadzenie wartosci poczatkowych tablic
    {
        for(int j=0;j<3;j++)
        kolizja_wrog[i][j]=0;
        wrog_score[i]=0;
        bonus[i]=i+1;
    }
    al_clear_to_color(al_map_rgb( 0, 0, 0));// wyczyszczenie aktualnego bufora ekranu
    al_draw_bitmap (tlo_gry,0,0,0);  // wyswietlenie bitmapy "tlo_gry" na bufor ekranu
    al_flip_display(); // wyswietlenie aktualnego bufora na ekran
    al_draw_bitmap (statek,x,y,0);  // wyswietlenie bitmapy "tlo_gry" na bufor ekranu
    al_flip_display(); // wyswietlenie aktualnego bufora na ekran
    al_start_timer(timer);// wlaczenie timera

    // uruchomienie gry ///////////////////////////////////
    while(events.keyboard.keycode!=ALLEGRO_KEY_BACKSPACE) {
        // ruch statku ////////////////////////////
        while(!al_is_event_queue_empty(kolejka)) {
            al_wait_for_event(kolejka, &events);//
                switch(events.type) {
                    case ALLEGRO_EVENT_KEY_DOWN:// dodawanie wektorow poruszania sie statku, gdy klawisze sa wcisniete
                    switch(events.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_UP:
                            vy-=speed;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            vy+=speed;
                            break;
                        case ALLEGRO_KEY_LEFT:
                            vx-=speed;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            vx+=speed;
                            break;
                        case ALLEGRO_KEY_SPACE:
                            strzal=1;// wystrzelenie pociskow
                            break;
                    }
                    break;
                    case ALLEGRO_EVENT_KEY_UP:// odejmowanie wektorow poruszania sie statku, gdy klawisze nie sa wcisniete
                    switch(events.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_UP:
                            vy+=speed;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            vy-=speed;
                            break;
                        case ALLEGRO_KEY_LEFT:
                            vx+=speed;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            vx-=speed;
                            break;
                        case ALLEGRO_KEY_SPACE:
                            strzal=0;// zaprzestanie strzelenia pociskow
                            break;
                    }
                    break;
                    case ALLEGRO_EVENT_TIMER:// sprawdzenie timera
                        {
                        check_timer = 1;
                        vy_pocisk_wrog+=speed_wrog;// poruszanie sie pocisku wroga w osi y po strzale
                        break;
                        }}}
        if(pocisk==starter_pocisk)// wyrownanie pozycji pocisku do srodka statku dla kazdego rodzaju broni
            pocisk_gap=12;
        if(pocisk==laser)
            pocisk_gap=4;
        if(pocisk==kula)
            pocisk_gap=0;
        if(pocisk==triple_pocisk)
            pocisk_gap=1;
        // sprawdzanie kolizji ///////
        for(int i=0;i<ilosc_wrogow;i++)
        {
            if(poziom==1||kolizja_wrog[i][1]==1)
            if(kolizja(pocisk,vx_pocisk+pocisk_gap,vy_pocisk,wrog,wrog_x+i*150,wrog_y)||kolizja(pocisk,vx_pocisk_2,vy_pocisk_2,wrog,wrog_x+i*150,wrog_y))
            {
                kolizja_wrog[i][0]=1;// kolizja wroga nr i w 1 rzedzie
                wrog_score[i]=1;
            }
            if(poziom==2||kolizja_wrog[i][2]==1)
            if(kolizja(pocisk,vx_pocisk+pocisk_gap,vy_pocisk,wrog,wrog_x+50+i*150,wrog_y+100)||kolizja(pocisk,vx_pocisk_2,vy_pocisk_2,wrog2,wrog_x+50+i*150,wrog_y+100))
            {
                kolizja_wrog[i][1]=1;// kolizja wroga nr i w 2 rzedzie
                wrog_score[i]=1;
            }
            if(poziom==3)
            if(kolizja(pocisk,vx_pocisk+pocisk_gap,vy_pocisk,wrog,wrog_x+i*150,wrog_y+200)||kolizja(pocisk,vx_pocisk_2,vy_pocisk_2,wrog2,wrog_x+i*150,wrog_y+200))
            {
                kolizja_wrog[i][2]=1;// kolizja wroga nr i w 3 rzedzie
                wrog_score[i]=1;
            }
           if(kolizja_wrog[i][0]==0)// kolizja gracza z pociskiem wroga nr i
           if(kolizja(statek,x,y,pocisk_wroga,vx_pocisk_wrog+i*150,vy_pocisk_wrog))
            kolizja_gracz=1;
           if(kolizja_wrog[i][0]==0)// kolizja gracza z wrogiem nr i
           {
                if(kolizja(statek,x,y,wrog,wrog_x+i*150,wrog_y))
                    kolizja_gracz=1;
                if(kolizja(statek,x,y,wrog2,wrog_x+50+i*150,wrog_y+100)&&poziom>1)
                    kolizja_gracz=1;
                if(kolizja(statek,x,y,wrog2,wrog_x+i*150,wrog_y+200)&&poziom>2)
                    kolizja_gracz=1;
           }
        }
        if(kolizja_gracz==1)// zakonczenie gry, gdy nastapi kolizja z graczem
            break;
        for(int i=0;i<ilosc_wrogow;i++)// sprawdzenie czy gracz zestrzelil wszystkich przeciwnikow w danym rzedzie
            for(int j=0;j<poziom;j++)
            {
                if(kolizja_wrog[i][2]!=1)
                    clear_poziom_2=0;
                else
                    if(kolizja_wrog[0][2]==1)
                    clear_poziom_2=1;
                if(kolizja_wrog[i][1]!=1)
                    clear_poziom_1=0;
                else
                    if(kolizja_wrog[0][1]==1)
                    clear_poziom_1=1;
            }
        for(int i=0;i<ilosc_wrogow;i++)// gdy gracz zestrzelil wszystkich przeciwnikow w danym rzedzie zmniejszamy rzad o 1
            for(int j=0;j<poziom;j++){
        if(clear_poziom_1==1)
            poziom=1;
        if(clear_poziom_2==1)
            poziom=2;
        if(kolizja_wrog[i][j]==1)// sprawdzenie czy zostaly zestrzelone wszystkie statki wroga aby wypuscic kolejna fale wrogow
            clear_fala = 1;
        else
            clear_fala = 0;}
            if((wrog_x>1400)&&clear_fala==1&&kolizja_wrog[0][0]==1)
            {
                for(int i=0;i<ilosc_wrogow;i++)
                    for(int j=0;j<3;j++)
                kolizja_wrog[i][j]=0;// resetowanie kolizji dla nowej fali wrogow
                speed_wrog+=0.25;// zwiekszenie predkosci pociskow wroga
                score+=100;// dodanie 100 do wyniku
                fala+=1;// nastepna fala
                poziom=1+rand()%+3;// losowanie liczby rzedow wrogow w nastepnej fali
                bonus_y = rand()%+400;// losowanie pozycji bonusu
                bonus_los = 1+rand()%+9;// losowanie bonusu
                if(ilosc_wrogow<8)
                    ilosc_wrogow=ilosc_wrogow+3;//zwiekszenie ilosci przeciwnikow
                else
                   ilosc_wrogow=0;//zresetowanie liczby wrogow, wprowadzanie bossa
            }
        if (check_timer==1) {
        // modul strzelania
        if(strzal==1)// gdy wcisnieto spacje
            {
                if(vy_pocisk<-100){// resetowanie pozycji pocisku nr 1 gdy opuscil obszar gry
                    vy_pocisk=y;// resetowanie wspolrzednej y pocisku nr 1
                    vx_pocisk=x+pocisk_gap;}// resetowanie wspolrzednej x pocisku nr 1
                if(vy_pocisk_2<-100&&vy_pocisk==300&&y>450){// resetowanie pozycji pocisku nr 2 gdy opuscil obszar gry i gdy pocisk nr 1 przebyl pewien obszar
                    vy_pocisk_2=y;// resetowanie wspolrzednej y pocisku nr 2
                    vx_pocisk_2=x+pocisk_gap;}// resetowanie wspolrzednej x pocisku nr 2
                    vy_pocisk-=1;// ruch pionowo pocisku nr 1
                    vy_pocisk_2-=1;// ruch pionowo pocisku nr 2
                    al_play_sample_instance(dzwiek_pocisk_instance);// dzwiek pocisku
            }
        if(strzal==0&&(vy_pocisk_2>-100||vy_pocisk>-100))// gdy puszczono spacje,a pociski nie opuscily obszaru gry pociski dalej poruszaja sie
            {
                vy_pocisk-=1;// ruch pionowo pocisku nr 1
                vy_pocisk_2-=1;// ruch pionowo pocisku nr 2
            }
        if(strzal==0&&vy_pocisk_2<-100&&vy_pocisk<-100&&x!=640&&y!=620)// gdy puszczono spacje i pociski opuscily obszar gry
            {
                vy_pocisk=y;// resetowanie wspolrzednej y pocisku nr 1
                vy_pocisk_2=y;// resetowanie wspolrzednej y pocisku nr 2
                vx_pocisk=x+pocisk_gap;// resetowanie wspolrzednej x pocisku nr 1
                vx_pocisk_2=x+pocisk_gap;// resetowanie wspolrzednej x pocisku nr 2
            }
        // modul przenoszenia statku na druga strone ekranu, gdy wyleci poza ekran
        if(x<-100)
        x=1380;
        if(x>1380)
        x=-100;
        if(y<-100)
        y=820;
        if(y>820)
        y=-100;
        // modul pociskow wroga
        time++;
        if(time==1400)// czestotlwiosc wystrzeliwania pociskow
        {
            vx_pocisk_wrog=wrog_x+45;
            vy_pocisk_wrog=wrog_y;
            time=0;
            if(frame==0)// przejscie z pierwszej na druga klatke w animacji
                frame=1;
            else// przejscie z drugiej na pierwsza klatke w animacji
                frame=0;
        }
        // ruch wroga //////////
        if(wrog_check_x==0)// poruszanie sie po osi x w prawo
        {
            if(wrog_x<=1680)
            wrog_x+=0.5;
            else wrog_check_x=1;
        }
        if(wrog_check_x==1)// poruszanie sie po osi x w lewo
        {
            if(wrog_x>=-400)
            wrog_x-=0.5;
            else wrog_check_x=0;
        }
        if(wrog_x>1380)// poruszanie sie po osi y
        {
            wrog_y=rand()%200;// losowanie wartosci y po wyleceniu wrogow poza ekran
        }
        x += vx;// dodanie wektora poziomego do pozycji statku
        y += vy;// dodanie wektora pionowego do pozycji statku
        al_clear_to_color(al_map_rgb( 0, 0, 0));// wyczyszczenie aktualnego bufora ekranu
        al_draw_bitmap (tlo_gry,0,0,0);  // wyswietlenie bitmapy "tlo_gry" na bufor ekranu
        al_draw_bitmap(pocisk,vx_pocisk+pocisk_gap,vy_pocisk,0); // wyswietlenie bitmapy pocisku nr 1 na bufor ekranu
        al_draw_bitmap(pocisk,vx_pocisk_2+pocisk_gap,vy_pocisk_2,0); // wyswietlenie bitmapy pocisku nr 2 na bufor ekranu
        al_draw_bitmap(statek,x,y,0);// wyswietlenie bitmapy "statek" na bufor ekranu
        for(int i=0;i<ilosc_wrogow;i++)
            for(int j=0;j<poziom;j++)
        if(kolizja_wrog[i][j]==0)// sprawdzenie czy nie nastapila kolizja
        {
            al_draw_bitmap(pocisk_wroga,vx_pocisk_wrog+i*150,vy_pocisk_wrog,0);// wyswietlenie bitmapy pocisku wroga nr i
            al_draw_bitmap_region(wrog,frame*48,0,48,48,wrog_x+i*150,wrog_y,0);// wyswietlenie bitmapy "wrog" na bufor ekranu
            if(poziom>1&&j>0)
            al_draw_bitmap_region(wrog2,frame*59,0,59,62,wrog_x+50+i*150,wrog_y+100,0);// wyswietlenie bitmapy "wrog2" na bufor ekranu
            if(poziom>2&&j==2)
            al_draw_bitmap_region(wrog2,frame*59,0,59,62,wrog_x+i*150,wrog_y+200,0);// wyswietlenie bitmapy "wrog2" na bufor ekranu
            if(wrog_score[i]==1)// dodanie 10 pkt do wyniku za zestrzelenie wroga nr i
                if(wrog_x>1680||wrog_x<-399)
                {
                    score+=10;
                    wrog_score[i]=0;
                }
        }
        if(ilosc_wrogow==0)// walka z bossem
                {
                    if(boss_hp==10000&&boss_faza==1)
                    {
                        al_stop_sample_instance(muzyka_gra_instance);// zatrzymanie muzyki z gry
                        al_play_sample_instance(muzyka_boss_instance);// uruchomienie muzyki do walki z bossem
                    }
                    if(boss_check_x==0)// poruszanie sie po osi x w prawo bossa
                    {
                        if(boss_x<=800)
                        boss_x+=0.25;
                        else boss_check_x=1;
                    }
                    if(boss_check_x==1)// poruszanie sie po osi x w lewo bossa
                    {
                        if(boss_x>=-200)
                        boss_x-=0.25;
                        else boss_check_x=0;
                    }
                    if(boss_hp!=10000||boss_faza!=1){// wyswietlanie bitmap pociskow bossa
                    al_draw_bitmap(pocisk_boss_bitmap,boss_x+100,vy_pocisk_boss+100,0);
                    al_draw_bitmap(pocisk_boss_bitmap,boss_x+800,vy_pocisk_boss+100,0);}
                    vy_pocisk_boss=vy_pocisk_boss+0.2;// poruszanie sie pociskow bossa
                    if(vy_pocisk_boss>720)
                        vy_pocisk_boss=10;// resetowanie pozycji pociskow, gdy wyleca poza obszar gry
                    if(boss_faza==1)
                    {
                        al_draw_bitmap(bariera,boss_x,boss_y,0);// wyswietlanie bitmapy bossa w fazie 1
                    }
                    if(boss_faza==2)
                    {
                        kolizja_gracz = draw(&l,pocisk_boss_2,statek,x,y,vy_pocisk_boss);// wyswietlanie bitmap pociskow typu 2 za pomoca listy
                        al_draw_bitmap(boss,boss_x,boss_y,0);// wyswietlanie bitmapy bossa w fazie 2
                    }
                    al_draw_textf(font,al_map_rgb(255,255,255),5,75,0,"Boss HP: %d",boss_hp);// wyswietlanie punktow zdrowia bossa
                    if(kolizja(pocisk,vx_pocisk,vy_pocisk,boss,boss_x,boss_y)||kolizja(pocisk,vx_pocisk_2,vy_pocisk_2,boss,boss_x,boss_y))// zmniejszenie zdrowia bossa po trafieniu pociskiem
                        boss_hp=boss_hp-1;
                    if(boss_hp!=10000)
                    if(kolizja(statek,x,y,boss,boss_x,boss_y)||kolizja(statek,x,y,pocisk_boss_bitmap,boss_x+100,vy_pocisk_boss+100)||kolizja(statek,x,y,pocisk_boss_bitmap,boss_x+800,vy_pocisk_boss+100))// sprawdzenie kolizji gracza z pociskami bossa i bossem
                        kolizja_gracz=1;
                    if(boss_hp<10)
                    {
                        boss_hp=0;
                        if(boss_faza==1&&vy_pocisk_boss>700)// przejscie do drugiej fazy bossa
                        {
                            pocisk_boss_bitmap = pocisk_boss_3;// zmiana wygladu pocisku podstawowego
                            boss_hp=20000;// zwiekszenie zdrowia bossa do drugiej fazy
                            boss_faza=2;
                        }
                        if(boss_faza==2&&boss_hp<10)// zakonczenie walki z bossem
                        {
                            ilosc_wrogow = 3;
                            fala++;
                            boss_hp=10000;
                            boss_faza=1;
                            al_stop_sample_instance(muzyka_boss_instance);// zatrzymanie muzyki do walki z bossem
                            al_play_sample_instance(muzyka_gra_instance);// uruchomienie muzyki z gry
                            pocisk_boss_bitmap = pocisk_boss;// zmiana wygladu pocisku podstawowego
                        }
                    }
                }
        for(int i=0;i<9;i++)
        if(bonus[i]==bonus_los)// sprawdzenie czy wylosowano bonus
        {
            bonus_y+=0.25;// poruszanie sie bonusu w dol
            al_draw_bitmap(bonus_bitmap,bonus_x,bonus_y,0);// wyswietlenie bitmapy bonusu
                    if(bonus[0]==bonus_los)// wybranie odpowiedniej bitmapy bonusu
                        bonus_bitmap=bonus0;
                    if(bonus[1]==bonus_los)
                        bonus_bitmap=bonus1;
                    if(bonus[2]==bonus_los&&speed<3)
                        bonus_bitmap=bonus2;
                    if(bonus[3]==bonus_los&&speed_wrog>2)
                        bonus_bitmap=bonus3;
                    if(bonus[4]==bonus_los)
                        bonus_bitmap=bonus4;
                    if(bonus[5]==bonus_los)
                        bonus_bitmap=bonus5;
                    if(bonus[6]==bonus_los)
                        bonus_bitmap=bonus6;
                    if(bonus[7]==bonus_los&&ilosc_wrogow!=0)
                        bonus_bitmap=bonus7;
                    if(bonus[8]==bonus_los)
                        bonus_bitmap=bonus8;
            if(kolizja(statek,x,y,bonus1,bonus_x,bonus_y)||kolizja(pocisk,vx_pocisk+pocisk_gap,vy_pocisk,bonus1,bonus_x,bonus_y)||kolizja(pocisk,vx_pocisk_2+pocisk_gap,vy_pocisk_2,bonus1,bonus_x,bonus_y))
                {// gdy nastapi kolzija statku gracza, pocisku gracza z bonusem
                    if(bonus[0]==bonus_los)// bonus - zmiana rodzaju pocisku
                        pocisk = laser;
                    if(bonus[1]==bonus_los)// bonus - zmiana rodzaju pocisku
                        pocisk = triple_pocisk;
                    if(bonus[2]==bonus_los&&speed<3)// bonus - przyspieszenie statku gracza
                        speed=speed+0.25;
                    if(bonus[3]==bonus_los&&speed_wrog>2)// bonus - spowolnienie pociskow wroga
                        speed_wrog=speed_wrog-1;
                    if(bonus[4]==bonus_los)// bonus - zmiana rodzaju pocisku
                        pocisk = kula;
                    if(bonus[5]==bonus_los)// bonus - +1000 do wyniku
                        score=score+1000;
                    if(bonus[6]==bonus_los)// bonus - dotychczasowy wynik *2
                        score=score*2;
                    if(bonus[7]==bonus_los&&ilosc_wrogow!=0)// bonus - zlikwidowanie wszystkich wrogow i przejscie do nastepnej fali
                        for(int i=0;i<ilosc_wrogow;i++)
                        for(int j=0;j<poziom;j++)
                        kolizja_wrog[i][j]=1;
                    if(bonus[8]==bonus_los)// negatywny bonus - koniec gry po zebraniu bonusu
                        kolizja_gracz=1;
                    al_play_sample_instance(dzwiek_bonus_instance);// uruchomienie dzwieku zebrania bonusu
                    bonus_x = 150+rand()%+1100;// losowanie nowej pozycji bonusu
                    bonus_y = rand()%+300;
                    bonus_los=0;
                }
        }
        al_draw_textf(font,al_map_rgb(255,255,255),5,50,0,"Fala: %d",fala);// wyswietlanie numeru fali
        al_draw_textf(font,al_map_rgb(255,255,255),5,5,0,"Wynik: %d",score);// wyswietlanie wyniku
        al_draw_textf(font,al_map_rgb(255,255,255),5,25,0,"Nazwa: %c%c%c",nick[0],nick[1],nick[2]);// wyswietlenie nazwy gracza
        al_flip_display(); // wyswietlenie aktualnego bufora na ekran
        check_timer=0;
        }
        }
        // zwalnianie pamieci
        al_stop_sample_instance(muzyka_gra_instance);
        al_destroy_bitmap(tlo_gry);
        al_destroy_bitmap(statek);
        al_destroy_bitmap(starter_pocisk);
        al_destroy_bitmap(wrog);
        al_destroy_bitmap(pocisk_wroga);
        al_destroy_bitmap(boss);
        al_destroy_bitmap(pocisk_boss);
        al_destroy_bitmap(bariera);
        al_destroy_bitmap(laser);
        al_destroy_bitmap(triple_pocisk);
        al_destroy_bitmap(kula);
        al_destroy_bitmap(bonus0);
        al_destroy_bitmap(bonus1);
        al_destroy_bitmap(bonus2);
        al_destroy_bitmap(bonus3);
        al_destroy_bitmap(bonus4);
        al_destroy_bitmap(bonus5);
        al_destroy_bitmap(bonus6);
        al_destroy_bitmap(bonus7);
        al_destroy_bitmap(bonus8);
        al_destroy_bitmap(wrog2);
        al_destroy_bitmap(pocisk_boss_2);
        al_destroy_bitmap(pocisk_boss_3);
        al_destroy_sample(muzyka_gra);
        al_destroy_sample(dzwiek_bonus);
        al_destroy_sample(dzwiek_pocisk);
        al_destroy_sample(muzyka_boss);
        al_destroy_sample_instance(muzyka_boss_instance);
        al_destroy_sample_instance(dzwiek_pocisk_instance);
        al_destroy_sample_instance(dzwiek_bonus_instance);
        al_destroy_sample_instance(muzyka_gra_instance);
        return score;// zwracanie wyniku
}

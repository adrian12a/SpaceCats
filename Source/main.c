#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "ranking.h"
#include "kolizja.h"
#include "gra.h"
#include "lista.h"

int main()
{
    al_init();// wprowadzenie biblioteki allegro
    al_init_image_addon();// wprowadzenie dodatku obslugujacego obrazy
    al_init_font_addon();// wprowadzenie dodatku obslugujacego czcionki
    al_init_ttf_addon();// wprowadzenie dodatku obslugujacego czcionki ttf
    al_install_keyboard();// wprowadzenie obslugi klawiatury
    al_install_audio();// wprowadzenie dodatku obslugujacego muzyke
    al_init_acodec_addon();// wprowadzenie dodatku obslugujacego muzyke
    ALLEGRO_DISPLAY *ekran=al_create_display(1280,720);// wskaznik okna z gra
    al_set_window_title(ekran,"Space Invaders");// ustawianie nazwy okna

    // wczytujemy muzyke

    al_reserve_samples(1);
    ALLEGRO_SAMPLE *muzyka_menu = al_load_sample("muzyka_menu.ogg");
    ALLEGRO_SAMPLE_INSTANCE *muzyka_menu_instance = al_create_sample_instance(muzyka_menu);
    al_set_sample_instance_playmode(muzyka_menu_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(muzyka_menu_instance,al_get_default_mixer());
    al_play_sample_instance(muzyka_menu_instance);

    // wczytujemy bitmapy do pamieci
    ALLEGRO_BITMAP *menu = al_load_bitmap("menu.png");
    ALLEGRO_BITMAP *ranking = al_load_bitmap("ranking.png");
    ALLEGRO_BITMAP *koniec_gry = al_load_bitmap("koniec_gry.png");
    ALLEGRO_BITMAP *wybor_nazwy = al_load_bitmap("wybor_nazwy.png");

    ALLEGRO_EVENT_QUEUE *kolejka=al_create_event_queue();// tworzenie kolejki
    ALLEGRO_FONT *font=al_load_ttf_font("OpenSans-Regular.ttf",15,0);// wskaznik na czcionke
    ALLEGRO_FONT *font_big=al_load_ttf_font("OpenSans-Regular.ttf",40,0);// wskaznik na duza czcionke
    al_register_event_source(kolejka,al_get_keyboard_event_source());// wprowadzenie obslugi kolejki za pomoca klawiatury
    ALLEGRO_EVENT events;// wprowadzenie eventow
    ALLEGRO_TIMER *timer = al_create_timer(1.0/1024);// wprowadzenie timera
    al_register_event_source(kolejka,al_get_timer_event_source(timer));// wprowadzeine rejestrowania timera

        al_draw_bitmap (menu,0,0,0);  // wyswietlenie bitmapy "menu" na bufor ekranu
        al_flip_display(); // wyswietlenie aktualnego bufora na ekran
        int exit=0;// zmienna sluzaca do wychodzenia z petli w menu
        int score=0;// zmienna zapisujaca wynik gracza
        char nick[3]="   ";// zmienna zapisujaca nazwe gracza
        int name_loop=0;// zmienna sluzaca do wpisywania nazwy gracza
        int litera;// zmienna zapisujaca litere z wcisnietgo klawisza
        int score_rank[6];// zmienna zapisujaca wyniki w rankingu
        char nick_rank[6][3];// zmienna zapisujaca nazwy gracza w rankingu
        for(int i=0;i<5;i++)// ustawianie domyslnych wartosci dla rankingu
        {
            score_rank[i]=0;
            nick_rank[i][0]='X';
            nick_rank[i][1]='Y';
            nick_rank[i][2]='Z';
        }
    // menu ////////////////////////////////////////////////////////////////////////
    while(exit==0){
            al_wait_for_event(kolejka,&events);// czekanie na wcisniecie przycisku
        switch(events.keyboard.keycode){
            case ALLEGRO_KEY_1:// wcisniety przycisk 1
            {
                al_clear_to_color(al_map_rgb( 0, 0, 0));// wyczyszczenie aktualnego bufora ekranu

                while(events.keyboard.keycode!=ALLEGRO_KEY_ENTER)// czekanie na wcisniecie przycisku ENTER
                {
                    al_clear_to_color(al_map_rgb( 0, 0, 0));// wyczyszczenie aktualnego bufora ekranu
                    al_draw_bitmap (wybor_nazwy,0,0,0);  // wyswietlenie bitmapy "wybor_nazwy" na bufor ekranu
                    al_wait_for_event(kolejka,&events);// czekanie na wcisniecie przycisku
                    litera=events.keyboard.keycode;// wpisanie znaku z klawiatury do zmiennej litera
                    if(litera>0&&litera<27&&nick[name_loop-1]!=litera+64)// sprawdzenie czy wprowadzony znak jest litera i jest rozny od poprzedniej wprowadzonej litery
                    {
                        nick[name_loop]=litera+64;//wprowadzenie litery do tablicy z nazwa gracza, +64 - zamiana z unichar na ascii
                        name_loop++;// nastepny znak
                        if(name_loop==4)// resetowanie gdy wprowadzono wszystkie znaki
                            name_loop=0;
                    }
                    al_draw_textf(font_big,al_map_rgb(255,255,255),360,360,0,"Wprowadz swoja nazwe: %c%c%c",nick[0],nick[1],nick[2]);// tworzenie napisu - nazwa gracza
                    al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"Nacisnij ENTER, aby kontynuowac");// tworzenie napisu
                    al_flip_display(); // wyswietlenie aktualnego bufora na ekran
                }
                al_stop_sample_instance(muzyka_menu_instance);// zatrzymanie muzyki z menu przed uruchomieniem gry
                score=gra(kolejka,timer,events,font,nick);// uruchomienie gry, pobranie wyniku
                rank(score,score_rank,nick,nick_rank,0,font_big);// wprowadzenie wyniku do rankingu
                nick[0]=0;// wyczyszczenie nazwy gracza
                nick[1]=0;
                nick[2]=0;
                name_loop=0;// resetowanie zmiennej sluzacej do wpisywania nazwy gracza
                al_clear_to_color(al_map_rgb( 0, 0, 0));// wyczyszczenie aktualnego bufora ekranu
                al_draw_bitmap (koniec_gry,0,0,0);  // wyswietlenie bitmapy "koniec_gry" na bufor ekranu
                al_draw_textf(font_big,al_map_rgb(255,255,255),550,500,0,"Wynik: %d",score);// wyswietlanie wyniku
                al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"Nacisnij BACKSPACE, aby kontynuowac");// tworzenie napisu
                al_flip_display(); // wyswietlenie aktualnego bufora na ekran
                while(events.keyboard.keycode!=ALLEGRO_KEY_BACKSPACE)// czekanie na wcisniecie przycisku BACKSPACE
                al_wait_for_event(kolejka,&events);
                al_play_sample_instance(muzyka_menu_instance);// uruchomienie muzyki z menu po zakonczeniu gry
                break;
            }
            case ALLEGRO_KEY_3:// wcisniety przycisk 3 lub ESCAPE
            case ALLEGRO_KEY_ESCAPE:
            {
                exit=1;// calkowite wyjscie z gry
                break;
            }
            case ALLEGRO_KEY_2:// wcisniety przycisk 2
            {
                al_clear_to_color(al_map_rgb( 0, 0, 0));// wyczyszczenie aktualnego bufora ekranu
                al_draw_bitmap (ranking,0,0,0);  // wyswietlenie bitmapy "ranking" na bufor ekranu
                al_draw_textf(font,al_map_rgb(255,255,0),0,0,0,"Nacisnij BACKSPACE, aby powrocic do menu");// tworzenie napisu
                al_flip_display(); // wyswietlenie aktualnego bufora na ekran
                rank(score,score_rank,nick,nick_rank,1,font_big);// wywolanie funkcji ranking
                break;
            }
            case ALLEGRO_KEY_BACKSPACE:// wcisniety przycisk BACKSPACE
            {
                al_clear_to_color(al_map_rgb( 0, 0, 0));// wyczyszczenie aktualnego bufora ekranu
                al_draw_bitmap (menu,0,0,0);  // wyswietlenie bitmapy "menu" na bufor ekranu
                al_flip_display(); // wyswietlenie aktualnego bufora na ekran
                break;
            }
    }}

    // zwalnianie pamieci
    al_destroy_display(ekran);
    al_uninstall_keyboard();
    al_destroy_bitmap(menu);
    al_destroy_bitmap(ranking);
    al_destroy_bitmap(koniec_gry);
    al_destroy_bitmap(wybor_nazwy);
    clear(&l);
    al_destroy_sample(muzyka_menu);
    al_destroy_sample_instance(muzyka_menu_instance);
    al_destroy_event_queue(kolejka);
    al_destroy_font(font);
    return 0;
}

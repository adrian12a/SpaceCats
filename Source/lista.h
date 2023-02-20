struct list{
    int data;
    struct list *next;
};

struct list_pointers
{
    struct list *first,*last;
}l;

 void push(struct list_pointers *l,int data);
 int pop(struct list_pointers *l);
 void clear(struct list_pointers *l);
 int draw(struct list_pointers *l,ALLEGRO_BITMAP *kula,ALLEGRO_BITMAP *statek,int x,int y,int vy_pocisk_boss);

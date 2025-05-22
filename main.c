#include <stdio.h>
#include <stdlib.h>
typedef struct element{
char val;
struct element *precedent;
}Element;
typedef struct liste{
Element *sommet;
int taille;
}Pile;
void affiche(Pile *p){
Element *courant;
courant=p->sommet;
while(courant!=NULL){
        printf("%d -> ",courant->val);
        courant=courant->precedent;
}printf("NULL \n");
}
int empiler(Pile *p , char val){
    Element *new;
    new=malloc(sizeof(Element));
    if(new==NULL) return -1;
    new->val=val;
    if(p==NULL){
        new->precedent=NULL;
        p->taille++;
        return 1;
    }
    else{
        new->precedent=p->sommet;
        p->sommet=new;
        p->taille++;
        return 1;
    }
}
void initialisation(Pile *p){
    p->sommet=NULL;
    p->taille=0;
}
void depiler(Pile *p){
    Element *head;
    if(p->sommet==NULL){
    printf("erreur");
    return;
    }
    else{
        head=p->sommet->precedent;
        free(p->sommet);
        p->sommet=head;
        p->taille--;
    }
}
void verifie_fichier(FILE *f){
    Pile p;
    initialisation(&p);
    if(f==NULL) {
        printf("erreur le ficher vide");
    }
    char c;
    while ((c=fgetc(f)) != EOF ){
            if(c=='{' || c=='(' || c=='['){
                empiler(&p,c);
               }
            else if(p.taille==0){
                printf("erreur la pile est vide \n");
                return;
            }
            else if( c==']' && p.sommet->val == '['){
                depiler(&p);
            }
            else if( c=='}' && p.sommet->val == '{'){
                depiler(&p);
            }
            else if( c==')' && p.sommet->val == '('){
                depiler(&p);
            }
            else{
                printf("erreur d'empilation \n");
                return;
            }

           }
    if(p.taille >0){
                printf("Error: %d unclosed opening symbols\n", p.taille);
                return;
            }
    else {
        printf("All symbols are properly matched\n");
    }

}
void tester_fichiers() {
    const char* fichiers[] = {
        "test1.txt", "test2.txt", "test3.txt", "test4.txt",
        "test5.txt", "test6.txt", "test7.txt"
    };
int i;
    for( i = 0; i < 7; i++) {
        printf("\nTest du fichier %s :\n", fichiers[i]);
        FILE *f = fopen(fichiers[i], "r");
        if(f != NULL) {
            verifie_fichier(f);
            fclose(f);
        } else {
            printf("Erreur : impossible d'ouvrir %s\n", fichiers[i]);
        }
    }
}
int main()
{
Pile p;
    initialisation(&p);

    // Test 1 : Empiler des éléments
    printf("Test 1 : Empiler des éléments\n");
    empiler(&p, 10);
    empiler(&p, 20);
    empiler(&p, 30);
    printf("Après avoir empilé 10, 20, 30 :\n");
    affiche(&p);
    printf("Taille de la pile : %d\n\n", p.taille);

    // Test 2 : Dépiler un élément
    printf("Test 2 : Dépiler un élément\n");
    depiler(&p);
    printf("Après avoir dépilé un élément :\n");
    affiche(&p);
    printf("Taille de la pile : %d\n\n", p.taille);

    // Test 3 : Tester la pile vide
    printf("Test 3 : Tester la pile vide\n");
    depiler(&p);
    depiler(&p);
    printf("Après avoir tout dépilé :\n");
    affiche(&p);
    printf("Taille de la pile : %d\n\n", p.taille);

    // Test 4 : Tester depiler sur une pile vide
    printf("Test 4 : Tester depiler sur une pile vide\n");
    depiler(&p);

    // Test 5 : Réempiler après avoir vidé
    printf("\nTest 5 : Réempiler après avoir vidé\n");
    empiler(&p, 100);
    empiler(&p, 200);
    printf("Après avoir empilé 100, 200 :\n");
    affiche(&p);
    printf("Taille de la pile : %d\n", p.taille);
    tester_fichiers();
    return 0;
}

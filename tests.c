#include <stdio.h>
#include "polynome.h"
#include "tests.h"

void main_test() {

    printf("Début des tests\n\n");


    printf("Création de polynomes:\n");
    
    int temp_array_1[5] = {0, 1, 2, 3, 4};
    polynome* poly1 = creer_poly(temp_array_1, 4);
    afficher(poly1);

    int temp_array_2[6] = {-2, 1, 0, -1, 5, -1};
    polynome* poly2 = creer_poly(temp_array_2, 5);
    afficher(poly2);

    polynome* poly3 = creer_poly_aleatoire(6, 100);
    afficher(poly3);

    supprimer_polynome(poly3);

    int temp_array_4[4] = {5, 4, 7, 3};
    polynome* poly4 = creer_poly(temp_array_4, 3);
    afficher(poly4);


    printf("\nÉvaluation, dérivation:\n");

    printf("%d\n", evaluation(poly4, 170));

    polynome* poly5 = derivee(poly4);
    afficher(poly5);

    printf("\nAddition, multiplication:\n");

    int temp_array_6[4] = {5, -4, -7, -3};
    polynome* poly6 = creer_poly(temp_array_6, 3);
    poly6 = addition(poly6, poly4);
    afficher(poly6);

    int temp_array_7[2] = {1, -1};
    int temp_array_8[7] = {1, 1, 1, 1, 1, 1, 1};
    polynome* poly7 = creer_poly(temp_array_7, 1);
    afficher(poly7);
    polynome* poly8 = creer_poly(temp_array_8, 6);
    afficher(poly8);
    polynome* poly9 = produit(poly7, poly8);
    afficher(poly9);

}
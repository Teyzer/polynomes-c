#include <stdio.h>
#include "polynome.h"
#include "tests.h"

void main_test() {

    /* Ensemble des tests de fonctions */
    /* Toutes les fonctions demandées sont écrites sans appel à une fonction auxiliaire */

    printf("\nDébut des tests\n\n");


    //Création et affichage de deux polynômes
    int tab1[4] = {5, 6, 2, 3};
    polynome* poly1 = creer_poly(tab1, 3);
    printf("Affichage poly1 : ");
    afficher(poly1);

    int tab2[3] = {0, 5, 1};
    polynome* poly2 = creer_poly(tab2, 2);  
    printf("Affichage poly2 : ");
    afficher(poly2);

    //Affichage évaluation
    int a = evaluation(poly2, 2);
    printf("Résultat evaluation : %d\n", a);

    // Dérivée d'un polynôme
    polynome* poly1_prime = derivee(poly1);
    printf("Résultat dérivée : ");
    afficher(poly1_prime);

    // Somme de deux polynomes
    polynome* added = addition(poly1, poly2);
    printf("Résultat addition poly1 et poly2 : ");
    afficher(added);

    // Produit de deux polynomes
    polynome* mult = produit(poly1, poly2);
    printf("Produit de poly1 et poly2 : ");
    afficher(mult);

    fonctions_non_demandees(poly1, poly2);

    printf("\nPolynome : \n");
    polynome* entree = creer_a_la_main();
    printf("Votre polynome : ");
    afficher(entree);

    ask_newton(entree);

}

void fonctions_non_demandees(polynome* poly1, polynome* poly2) {

    /* Ici se trouvent tous les tests relatifs aux fonctions non demandées  */


    printf("\nFonctions non demandées:\n");

    // Augmentation du degrès d'un polynome
    polynome* raised = augmenter_degree(poly1, 5);
    printf("Poly1 augmenté de 5 degrés : ");
    afficher(raised);

    // Division longue entre deux polynomes
    polynome* div = division(poly1, poly2);
    printf("Division de poly1 et poly2 : ");
    afficher(div);

    // Reste de la division longue entre deux polynomes
    polynome* res = reste(poly1, poly2);
    printf("Reste de la division de poly1 et poly2 : ");
    afficher(res);

    // Verification que le quotient et reste reforment bien le bon produit:
    polynome* reconstruction = produit(div, poly2);
    reconstruction = addition(reconstruction, res);
    printf("Reconstruction de poly1 comme (poly2) * (poly1/poly2) + reste : ");
    afficher(reconstruction);

}

void ask_newton(polynome* poly) {

    /* Fonction qui permet de tester la méthode de newton en rajoutant un peu d'affichage */

    double* x_0 = (double*)malloc(sizeof(double));

    printf("\nMéthode de Newton (avec polynome fourni) : \n");
    printf("Rentrez un nombre réel (décimal) pour la première approximation: ");
    scanf("%lf", x_0);

    double r = newtons_method(poly, *x_0, 30);

    printf("Une racine du polynome se trouve approximativement en: %.15lf\n", r);
    printf("On obtient le résultat suivant en évaluant le polynome en ce réel : %.15lf\n", evaluation_double(poly, r));

}
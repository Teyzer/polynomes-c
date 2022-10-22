#include "polynome.h"
#include "tests.h"

void main_test() {

    /* Ensemble des tests de fonctions */
    /* Toutes les fonctions demandées sont écrites sans appel à une fonction auxiliaire */

    srand(time(0));

    printf("\nDébut des tests\n\n");

    // Listes d'assertions:
    int tab_nul[1] = {0};
    polynome* polynome_nul = creer_poly(tab_nul, -1);
    int polytab[5] = {4, 5, 6, -8, -2};
    polynome* poly_quelconque = creer_poly(polytab, 4);

    assert(test_egalite(produit(polynome_nul, poly_quelconque), polynome_nul));
    assert(test_egalite(produit_par_scalaire(polynome_nul, 5), polynome_nul));
    assert(test_egalite(produit_par_scalaire(poly_quelconque, 0), polynome_nul));
    assert(evaluation(poly_quelconque, 3) == -305);
    assert(evaluation(polynome_nul, 450000054) == 0);;
    assert(test_egalite(derivee(polynome_nul), polynome_nul));
    assert(test_egalite(addition(polynome_nul, polynome_nul), polynome_nul));
    assert(test_egalite(addition(polynome_nul, poly_quelconque), poly_quelconque));


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
    printf("Résultat evaluation poly2 en x=2: %d\n", a);

    // Dérivée d'un polynôme
    polynome* poly1_prime = derivee(poly1);
    printf("Résultat dérivée poly1 : ");
    afficher(poly1_prime);

    // Somme de deux polynomes
    polynome* added = addition(poly1, poly2);
    printf("Résultat addition poly1 et poly2 : ");
    afficher(added);

    // Produit de deux polynomes
    polynome* mult = produit(poly1, poly2);
    printf("Produit de poly1 et poly2 : ");
    afficher(mult);

    int borne = 4;
    polynome* aleatoire = creer_poly_aleatoire(borne, borne);
    printf("Polynome aléatoire de degrès %d, avec coefficients entre -%d et %d:\n", borne, borne, borne);
    afficher(aleatoire);

    int scalaire2 = 10; 
    polynome* produit_scalaire = produit_par_scalaire(aleatoire, scalaire2);
    printf("Produit du polynome aleatoire par %d: ", scalaire2);
    afficher(produit_scalaire);

    // Creation d'un polynome à la main
    printf("\nPolynome : \n");
    polynome* entree = creer_a_la_main();
    printf("Votre polynome : ");
    afficher(entree);

}
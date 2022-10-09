#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef POLYNOME
#define POLYNOME

typedef struct Polynome {int* coefs; int degree;} polynome;

polynome* creer_poly(int tab[], int degree);

polynome* creer_poly_aleatoire(int degree, int borne);
void supprimer_polynome(polynome* poly);
void afficher(polynome* poly);
int evaluation(polynome* poly, int x);

bool test_egalite(polynome* poly1, polynome* poly2);
polynome* derivee(polynome* poly);
polynome* addition(polynome* poly1, polynome* poly2);
polynome* produit_par_scalaire(polynome* poly, int a);
polynome* produit(polynome* poly1, polynome* poly2);
polynome* creer_a_la_main(void);

// FONCTIONS NON DEMANDEES

polynome* soustraction(polynome* poly1, polynome* poly2);
int actual_polynome_degree(polynome* poly);
polynome* augmenter_degree(polynome* poly1, int degree);
polynome* copie(polynome* poly);
polynome* division(polynome* poly1, polynome* poly2);
polynome* reste(polynome* numerator, polynome* denominator);
double evaluation_double(polynome* poly, double x);
double newtons_method(polynome* poly, double x0, int iterations);

#endif
polynome.c                                                                                          0000664 0001750 0001750 00000027634 14324755664 012414  0                                                                                                    ustar   pacome                          pacome                                                                                                                                                                                                                 #include "polynome.h"

// Entrée: un tableau contenant les coefficients du polynome ainsi que le degré désiré
// Sortie: Un pointeur vers l'objet polynome correspondant aux coefficients fournis
polynome* creer_poly(int tab[], int deg) {

    while (tab[deg] == 0) {
        deg--;
    }

    int* t;
    if (deg == -1) {
        t = (int*)malloc(sizeof(int));
    } else {
        t = (int*)malloc(sizeof(int) * (deg + 1));
    }

    polynome* q = (polynome*)malloc(sizeof(polynome));
    
    q -> coefs = t;
    q -> degree = deg;

    // Variant: "i": entier, majoré par deg, et augmente strictement à chaque passage
    // Invariant: coefs[0..i-1] = tab[0..i-1]
    for (int i = 0; i <= deg; i =  i + 1) {
        (q -> coefs)[i] = tab[i];
    }



    return q;

}

// Entrée: Le degrès du polynome ainsi que la valeur borne pour laquelle on aura chaque coefficient entre borne et -borne
// Sortie: Un pointeur vers l'objet polynome ayant le degrès correspondant et des coefficients aléatoires
polynome* creer_poly_aleatoire(int deg, int borne) {

    int* t = (int*)malloc(sizeof(int) * (deg + 1));
    polynome* q = (polynome*)malloc(sizeof(polynome));

    q -> coefs = t;
    q -> degree = deg;

    // Variant de boucle: "i": entier, majoré par deg, et augmantant strictement de 1 à chaque itération
    // Invariant de boucle: pour tout k dans [0,i-1], -borne <= coefs[k] <= borne
    for (int i = 0; i <= deg; i =  i + 1) {
        // On a l'inégalité suivante: (0 <= rand() % m < m) donc il faut adapter le modulo  
        if (i == deg) {
            // on évite le cas ou le coef directeur est 0 
            (q -> coefs)[i] = ((rand() % borne) + 1) * (rand() % 2 == 0 ? 1 : -1); 
        } else {
            (q -> coefs)[i] = (rand() % (2 * borne + 1)) - borne; 
        }
    }

    return q;

}

// Entrée: Un pointeur vers un objet polynome
// Sortie: Void, et supprime le rattachement des pointeurs coefficients et polynome aux emplacements mémoires.
void supprimer_polynome(polynome* poly) {
    free(poly -> coefs);
    free(poly);
}

// Entrée: Prend un pointeur vers un objet polynome
// Sortie: Un affichage du polynome avec ses coefficients et les puissances de x correspondantes
void afficher(polynome* poly) {

    // On évite le cas du polynome nul
    if (poly -> degree == -1) {
        printf("0\n");
        return;
    }

    int current;

    // Variant: "i", entier, minoré par 0, et décroit strictement de 1 à chaque itération
    // Invariant: chaque coefficient dans (i+1)..(poly->degree) a été affiché correctement
    for (int i = (poly -> degree); i >= 0; i = i - 1) {
        
        current = (poly -> coefs)[i];

        if (current != 0) {

            if (i != (poly -> degree)) { // On adapte le signe en fonction de : (coefficient directeur ou non) et (positif ou négatif) 
                if (current > 0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                }
            } else if (current < 0) {
                printf("-");
            }
            

            // si current == -1 ou current == 1
            if (current * current != 1 || i == 0) {
                printf("%d", abs(current)); // On a déjà adapté le signe avant donc on affiche la valeur absolue
            }
            
            if (i != 0) {
                printf("x");
            }

            if (i > 1) {
                printf("^%d", i); // On affichela puissance seulement si degrès 2 ou plus
            }

        }
    }

    printf("\n");

}

// Entrée: Un pointeur vers un objet polynome ainsi qu'un entier x
// Sortie: Un entier qui représente l'évalutation du polynome correspondant au point x
int evaluation(polynome* poly, int x) {

    if (poly -> degree <= 0) {
        return (poly -> coefs)[0];
    } 

    
    int sum = (poly -> coefs)[poly -> degree] * x + (poly -> coefs)[(poly -> degree) - 1];
    
    // Variant: "i": entier, minoré par 0, et strictement décroissant de 1 à chaque itération
    // Invariant: sum représente le ième degrès de factorisation du polynome évalué en x (mal formulé je le sais, mais j'ai un peu de mal à le formaliser)
    for (int i = poly -> degree - 2; i >= 0; i = i - 1) {
        sum = x * sum + (poly -> coefs)[i];
    }
    
    return sum;

}

// Entrée: Prend deux pointeurs vers des objets polynomes en entrée
// Sortie: Un booléan, vrai si les deux polynomes sont égaux, faux sinon
bool test_egalite(polynome* poly1, polynome* poly2) {

    if (poly1 -> degree != poly2 -> degree) { // deux polynomes de degrès différents sont forcément différents, puisque l'on a a_n != 0 et b_n != 0
        return false;
    }

    if (poly1 -> degree == -1) {
        return true;
    }

    int d = poly1 -> degree;

    // Variant de boucle: "i", entier, majoré par d, et croit strictement de 1 à chaque itération
    // Invariant: pour tout k dans [0,i-1], poly1[k] == poly2[k]
    for (int i = 0; i <= d; i = i + 1) { // Deux polynomes sont égaux si tous leur coefficients sont égaux
        if ((poly1 -> coefs)[i] != (poly2 -> coefs)[i]) {
            return false;
        }
    }

    return true;

}

// Entrée: Un pointeur vers un objet polynome
// Sortie: Un pointeur vers un objet polynome représentant la dérivé du polynome fourni
polynome* derivee(polynome* poly) {

    if (poly -> degree == -1) { // Cas du polynome nul qui est égal à sa dérivée
        int* t = (int*)malloc(sizeof(int));
        polynome* r = (polynome*)malloc(sizeof(polynome));

        r -> coefs = t;
        r -> degree = -1;
 
        (r -> coefs)[0] = 0;

        return r;
    }

    int* t = (int*)malloc(sizeof(int) * ((poly -> degree) + 1 - 1));
    polynome* new_poly = (polynome*)malloc(sizeof(polynome));

    new_poly -> degree = (poly -> degree) - 1;
    new_poly -> coefs = t;

    // Variant de boucle: "i", entier, majoré par le degrès du polynome, et qui augmente strictement de 1 à chaque itération.
    // Invariant: pour tout k dans [1,i-1], (new_poly -> coefs)[k-1] = k * (poly->coefs)[k]
    for (int i = 1; i <= poly -> degree; i = i + 1) { // On commence bien à 1 car le terme de puissance 0 est supprimé
        (new_poly -> coefs)[i - 1] = i * (poly -> coefs)[i];
    }

    return new_poly;

}

// Entrée: deux pointeurs vers des objets polynomes
// Sortie: Un pointeur vers un objet polynome représentant la somme de ces deux polynomes
polynome* addition(polynome* poly1, polynome* poly2) {
    
    int deg1 = poly1 -> degree;
    int deg2 = poly2 -> degree;

    // On prend le plus grand degré des deux polynomes
    int max_degree = deg1 > deg2 ? deg1 : deg2;
    int n = max_degree;

    // On vérifie que les coefficients ne s'annulent pas, sinon le degrès baisse
    // Variant: "i", entier, minoré par 0, et baisse strictement de 1 à chaque itération
    // Invariant: max_degree >= vrai_degre_final
    for (int i = n; i >= 0; i = i - 1) {
        if ((poly1 -> coefs)[i] + (poly2 -> coefs)[i] == 0) {
            max_degree = max_degree - 1;
        } else {
            break;
        }
    }

    int* t = (int*)malloc(sizeof(int) * max_degree);
    polynome* new_poly = (polynome*)malloc(sizeof(polynome));

    new_poly -> coefs = t;
    new_poly -> degree = max_degree;

    // On itère au travers des coefficients et on additione tant que l'on ne dépasse pas
    // le degrès maximal de chaque polynome
    // Variant: "i", entier, majoré par max_degree, et croit strictement de 1 à chaque itération
    // Invariant: pour tout k dans [0,i-1], new_poly -> coefs[k] = poly1->coefs[k] + poly2->coefs[k]
    for (int i = 0; i <= max_degree; i = i + 1) {
        
        (new_poly -> coefs)[i] = 0;

        if (i <= deg1) {
            (new_poly -> coefs)[i] += (poly1 -> coefs)[i];
        }

        if (i <= deg2) {
            (new_poly -> coefs)[i] += (poly2 -> coefs)[i];
        }

    }
    
    return new_poly;

}

// Entrée: Un pointeur vers un objet polynome, ainsi qu'un entier
// Sortie: Un pointeur vers un objet polynome dont tous les coefficients ont etes multiplies par a
polynome* produit_par_scalaire(polynome* poly, int a) {

    // Si le scalaire est nul, on renvoie le polynome nul car P(x) * 0 = 0
    if (a == 0) {
        int* t = (int*)malloc(sizeof(int));
        polynome* r = (polynome*)malloc(sizeof(polynome));
        
        r -> coefs = t;
        r -> degree = -1;
        (r -> coefs)[0] = 0;

        return r;
    }

    int* t;
    if (poly -> degree == -1) {
        t = (int*)malloc(sizeof(int));
    } else {
        t = (int*)malloc(sizeof(int) * (poly -> degree + 1));
    }

    polynome* r = (polynome*)malloc(sizeof(polynome));

    // Variant: "i", entier, augmente strictement de 1 à chaque itération et majoré par le degrès du polynome 
    // Invariant: pour tout k dans [0,i-1], t[k] = scalaire * (poly -> coefs)[k]
    for (int i = 0; i <= poly -> degree; i = i + 1) {
        t[i] = (poly -> coefs)[i] * a;
    }

    r -> coefs = t;
    r -> degree = poly -> degree;

    return r;

}

// Entrée: deux pointeurs vers deux objets polynomes
// Sortie: Un pointeur vers un objet polynome représentant le produit des deux polynomes fournis
polynome* produit(polynome* poly1, polynome* poly2) {

    if (poly1 -> degree == -1 || poly2 -> degree == -1) { // On traite le cas où l'un des deux polynomes est nul
        int* t = (int*)malloc(sizeof(int));
        polynome* resultat = (polynome*)malloc(sizeof(polynome));
        resultat -> degree = -1;
        resultat -> coefs = t;
        (resultat -> coefs)[0] = 0;
        return resultat;
    }

    int new_degree = (poly1 -> degree) + (poly2 -> degree);
    int* t = (int*)malloc(sizeof(int) * (new_degree + 1));

    polynome* r = (polynome*)malloc(sizeof(polynome));

    r -> coefs = t;
    r -> degree = new_degree;

    // Est ce que l'on peut faire un invariant pour les deux boucles? ie:
    // Invariant: coefs[k] = somme des poly1->coefs[i] + poly2->coefs[j] pour i+j=k
    // Variant de boucle: "i", entier, majoré par le degrès du premier polynome, et augmente strictement de 1 à chaque itération
    for (int i = 0; i <= poly1 -> degree; i = i + 1) {
        // Variant de boucle: "j", entier, majoré par le degrès du deuxième polynome, et augmente strictement de 1 à chaque itération
        for (int j = 0; j <= poly2 -> degree; j = j + 1) {

            // Le résultat de a_k * x^i * b_k * x^j sera a_k * b_k x^(i + j), d'où on multiplie les coefficient et accès à la somme des degrees 
            (r -> coefs)[i + j] = (r -> coefs)[i + j] + (poly1 -> coefs)[i] * (poly2 -> coefs)[j];

        }
    }

    return r;

}

// Entrée: rien directement, puis une entrée utilisateur qui représente les coefficients du polynome désiré
// Sortie: Un pointeur vers un objet polynome associé aux coefficients entrés
polynome* creer_a_la_main(void) {

    int* degree = (int*)malloc(sizeof(int));
    char key = 'x';

    printf("Degree du polynome : ");
    if (scanf("%d%c", degree, &key) != 2 || key != '\n') {
        printf("L'entree n'est pas un nombre, fin du programme\n");
        exit(1);
    }

    int* t = (int*)malloc(sizeof(int) * (*degree + 1));
    polynome* resultat = (polynome*)malloc(sizeof(polynome));

    // Variant de boucle: "i", entier, majoré par le dgrès désiré, et croit strictement de 1 à chaque itération, à condition que l'utilisateur rentre des coefs
    // Invariant: pour tout k dans [0,i-1], t[k] contient un coefficient rentré par l'utilisateur
    for (int i = 0; i <= *degree; i = i + 1) {
        printf("Coefficient du degree %d : ", i);
        if (scanf("%d%c", t + i, &key) != 2 || key != '\n') {
            printf("L'entree n'est pas un nombre, fin du programme\n");
            exit(1);
        } 
        if (i == *degree && t[i] == 0) {
            printf("Impossible de choisir 0 comme coefficient directeur\n");
            exit(1);
        }
        // (t + i) ici pour que scanf accède à *(t + i) c.a.d t[i], notre coefficient
    }

    resultat -> coefs = t;
    resultat -> degree = *degree;

    return resultat;
}                                                                                                    polynome.h                                                                                          0000664 0001750 0001750 00000001224 14324754424 012375  0                                                                                                    ustar   pacome                          pacome                                                                                                                                                                                                                 #include <stdbool.h>
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

#endif                                                                                                                                                                                                                                                                                                                                                                            tests.c                                                                                             0000664 0001750 0001750 00000004700 14324756103 011666  0                                                                                                    ustar   pacome                          pacome                                                                                                                                                                                                                 #include "polynome.h"
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

}                                                                tests.h                                                                                             0000664 0001750 0001750 00000000350 14324755705 011677  0                                                                                                    ustar   pacome                          pacome                                                                                                                                                                                                                 #include <stdio.h>
#include <assert.h>
#include <time.h>
#include "polynome.h"

#ifndef TESTS
#define TESTS

void main_test();

void fonctions_non_demandees(polynome* poly1, polynome* poly2);
void ask_newton(polynome* poly);

#endif                                                                                                                                                                                                                                                                                        Makefile                                                                                            0000664 0001750 0001750 00000000553 14324755733 012032  0                                                                                                    ustar   pacome                          pacome                                                                                                                                                                                                                 .PHONY: all clean

all: clean polynome tests main afterhandclean
run: clean polynome tests main afterhandclean runner

polynome: polynome.c
	gcc -c -Wall polynome.c
	
tests: tests.c polynome.h
	gcc -c -Wall tests.c
	
main: main.c polynome.h tests.h
	gcc -o main polynome.o tests.o main.c -Wall

afterhandclean:
	rm -f *.o

runner:
	./main

clean: 
	rm -f *.o main                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
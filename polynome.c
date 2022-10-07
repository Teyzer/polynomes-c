#include "polynome.h"

polynome* creer_poly(int tab[], int deg) {

    int* t = (int*)malloc(sizeof(int) * (deg + 1));
    polynome* q = (polynome*)malloc(sizeof(polynome));
    
    q -> coefs = t;
    q -> degree = deg;

    for (int i = 0; i <= deg; i =  i + 1) {
        (q -> coefs)[i] = tab[i];
    }

    return q;

}

polynome* creer_poly_aleatoire(int deg, int borne) {

    int* t = (int*)malloc(sizeof(int) * (deg + 1));
    polynome* q = (polynome*)malloc(sizeof(polynome));

    q -> coefs = t;
    q -> degree = deg;

    for (int i = 0; i <= deg; i =  i + 1) {
        (q -> coefs)[i] = (rand() % (2 * borne + 1)) - borne;
    }

    return q;

}

void supprimer_polynome(polynome* poly) {
    free(poly -> coefs);
    poly -> coefs = NULL;
}

void afficher(polynome* poly) {

    if (poly -> degree == 0) {
        printf("%d\n", (poly -> coefs)[0]);
        return;
    }

    int current;

    for (int i = (poly -> degree); i >= 0; i = i - 1) {
        
        current = (poly -> coefs)[i];

        if (current != 0) {

            if (i != (poly -> degree)) {
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
                printf("%d", abs(current));
            }
            
            if (i != 0) {
                printf("x");
            }

            if (i > 1) {
                printf("^%d", i);
            }

        }
    }

    printf("\n");

}

int evaluation(polynome* poly, int x) {

    if (poly -> degree == 0) {
        return (poly -> coefs)[0];
    } 

    // méthode de holder
    int sum = (poly -> coefs)[poly -> degree] * x + (poly -> coefs)[(poly -> degree) - 1];
    for (int i = poly -> degree - 2; i >= 0; i = i - 1) {
        sum = x * sum + (poly -> coefs)[i];
    }
    
    return sum;

}

bool test_egalite(polynome* poly1, polynome* poly2) {

    if (poly1 -> degree != poly2 -> degree) {
        return false;
    }

    int d = poly1 -> degree;

    for (int i = 0; i <= d; i = i + 1) {
        if ((poly1 -> coefs)[i] != (poly2 -> coefs)[i]) {
            return false;
        } 
    }

    return true;

}

polynome* derivee(polynome* poly) {

    polynome* new_poly = (polynome*)malloc(sizeof(polynome));
    int* t = (int*)malloc(sizeof(int) * ((poly -> degree) + 1 - 1));

    for (int i = 1; i <= poly -> degree; i = i + 1) {
        t[i - 1] = i * (poly -> coefs)[i];
    }

    new_poly -> degree = (poly -> degree) - 1;
    new_poly -> coefs = t;

    return new_poly;

}

polynome* addition(polynome* poly1, polynome* poly2) {

    // On prend le plus grand degré des deux polynomes
    int deg1 = poly1 -> degree;
    int deg2 = poly2 -> degree;

    int max_degree = deg1 > deg2 ? deg1 : deg2;
    int n = max_degree;

    // On vérifie que les coefficients ne s'annulent pas
    for (int i = n; i > 0; i = i - 1) {
        if ((poly1 -> coefs)[i] + (poly2 -> coefs)[i] == 0) {
            max_degree = max_degree - 1;
        } else {
            break;
        }
    }

    polynome* new_poly = (polynome*)malloc(sizeof(polynome));
    int* t = (int*)malloc(sizeof(int) * max_degree);

    // On itère au travers des coefficients et on additione tant que l'on ne dépasse pas
    // le degrès maximal de chaque polynome
    for (int i = 0; i <= max_degree; i = i + 1) {
        
        t[i] = 0;

        if (i <= deg1) {
            t[i] += (poly1 -> coefs)[i];
        }

        if (i <= deg2) {
            t[i] += (poly2 -> coefs)[i];
        }

    }

    new_poly -> coefs = t;
    new_poly -> degree = max_degree;
    
    return new_poly;

}

polynome* produit_par_scalaire(polynome* poly, int a) {

    polynome* r = (polynome*)malloc(sizeof(polynome));

    if (a == 0) {
        int* t = (int*)malloc(sizeof(int));
        r -> coefs = t;
        r -> degree = 0;
        return r;
    }

    int* t = (int*)malloc(sizeof(int) * (poly -> degree + 1));

    for (int i = 0; i <= poly -> degree; i++) {
        t[i] = (poly -> coefs)[i] * a;
    }

    r -> coefs = t;
    r -> degree = poly -> degree;

    return poly;

}

polynome* produit(polynome* poly1, polynome* poly2) {

    polynome* r = (polynome*)malloc(sizeof(polynome));
    int new_degree = (poly1 -> degree) + (poly2 -> degree);

    int* t = (int*)malloc(sizeof(int) * (new_degree + 1));

    for (int i = 0; i <= poly1 -> degree; i = i + 1) {
        for (int j = 0; j <= poly2 -> degree; j = j + 1) {

            t[i + j] += (poly1 -> coefs)[i] * (poly2 -> coefs)[j];

        }
    }
    
    r -> degree = new_degree;
    r -> coefs = t;

    return r;

}
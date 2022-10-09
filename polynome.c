#include "polynome.h"

/* Fonction qui prend un tableau et un degree et renvoie l'objet polynome* qui représente le polynome correspondant */
polynome* creer_poly(int tab[], int deg) {

    int* t = (int*)malloc(sizeof(int) * (deg + 1));
    polynome* q = (polynome*)malloc(sizeof(polynome));
    
    q -> coefs = t;
    q -> degree = deg;

    // Itère à travers le tableau donné pour associer chaque coefficient
    for (int i = 0; i <= deg; i =  i + 1) {
        (q -> coefs)[i] = tab[i];
    }

    return q;

}

/* Création d'un polynome aléatoire, de degrès indiqué et avec coefficients entre -borne et borne */
polynome* creer_poly_aleatoire(int deg, int borne) {

    int* t = (int*)malloc(sizeof(int) * (deg + 1));
    polynome* q = (polynome*)malloc(sizeof(polynome));

    q -> coefs = t;
    q -> degree = deg;

    for (int i = 0; i <= deg; i =  i + 1) { // On attribue à chaque coef un nombre aléatoire
        (q -> coefs)[i] = (rand() % (2 * borne + 1)) - borne; // On a l'inégalité suivante: (0 <= rand() % m < m) donc il faut adapter le modulo  
    }

    return q;

}

// On supprime de la mémoire les coefficients du polynome puis le polynome lui même
void supprimer_polynome(polynome* poly) {
    free(poly -> coefs);
    free(poly);
}

// Prend un polynome en entrée et génère son affichage
void afficher(polynome* poly) {

    // Si le polynome est de degrès 0, on affiche seulement son premier coefficient
    // Permet d'éviter le cas où P(x) = 0, qui n'afficherait rien sinon
    if (poly -> degree == 0) {
        printf("%d\n", (poly -> coefs)[0]);
        return;
    }

    int current;

    for (int i = (poly -> degree); i >= 0; i = i - 1) { // On itère dans les coefficients
        
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

// On évalue le polynome, grâce à la méthode de holder
int evaluation(polynome* poly, int x) {

    if (poly -> degree == 0) {
        return (poly -> coefs)[0];
    } 

    // On commence avec 
    int sum = (poly -> coefs)[poly -> degree] * x + (poly -> coefs)[(poly -> degree) - 1];
    for (int i = poly -> degree - 2; i >= 0; i = i - 1) {
        sum = x * sum + (poly -> coefs)[i];
    }
    
    return sum;

}

// On prend deux polynomes en entrée et on teste s'ils sont égaux
bool test_egalite(polynome* poly1, polynome* poly2) {

    if (poly1 -> degree != poly2 -> degree) { // deux polynomes de degrès différents sont forcément différents, puisque l'on a a_n != 0 et b_n != 0
        return false;
    }

    int d = poly1 -> degree;

    for (int i = 0; i <= d; i = i + 1) { // Deux polynomes sont égaux si tous leur coefficients sont égaux
        if ((poly1 -> coefs)[i] != (poly2 -> coefs)[i]) {
            return false;
        }
    }

    return true;

}

// Fonction qui prend en entrée un polynome et renvoie sa dérivée
polynome* derivee(polynome* poly) {

    int* t = (int*)malloc(sizeof(int) * ((poly -> degree) + 1 - 1));
    polynome* new_poly = (polynome*)malloc(sizeof(polynome));

    new_poly -> degree = (poly -> degree) - 1;
    new_poly -> coefs = t;

    // Un polynome de la forme somme de a_k*x^k a comme dérivée k * a_k * x ^ (k - 1)
    for (int i = 1; i <= poly -> degree; i = i + 1) { // On commence bien à 1 car le terme de puissance 0 est supprimé
        (new_poly -> coefs)[i - 1] = i * (poly -> coefs)[i];
    }

    return new_poly;

}

// Prend deux polynomes en entrée et les additionne
polynome* addition(polynome* poly1, polynome* poly2) {
    
    int deg1 = poly1 -> degree;
    int deg2 = poly2 -> degree;

    // On prend le plus grand degré des deux polynomes
    int max_degree = deg1 > deg2 ? deg1 : deg2;
    int n = max_degree;

    // On vérifie que les coefficients ne s'annulent pas, sinon le degrès baisse
    for (int i = n; i > 0; i = i - 1) {
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

// Prend un polynome et un entier en entrée et renvoie le produit du polynome et d'un scalaire
polynome* produit_par_scalaire(polynome* poly, int a) {

    // Si le scalaire est nul, on renvoie la fonction nulle car P(x) * 0 = 0
    if (a == 0) {
        int* t = (int*)malloc(sizeof(int));
        polynome* r = (polynome*)malloc(sizeof(polynome));
        r -> coefs = t;
        r -> degree = 0;
        return r;
    }

    int* t = (int*)malloc(sizeof(int) * (poly -> degree + 1));
    polynome* r = (polynome*)malloc(sizeof(polynome));

    // Sinon on multiplie chaque coefficient par le scalaire
    for (int i = 0; i <= poly -> degree; i++) {
        t[i] = (poly -> coefs)[i] * a;
    }

    r -> coefs = t;
    r -> degree = poly -> degree;

    return r;

}

// Réalise le produit de deux polynomes fournit en argument
polynome* produit(polynome* poly1, polynome* poly2) {

    int new_degree = (poly1 -> degree) + (poly2 -> degree);
    int* t = (int*)malloc(sizeof(int) * (new_degree + 1));

    polynome* r = (polynome*)malloc(sizeof(polynome));

    r -> coefs = t;
    r -> degree = new_degree;

    for (int i = 0; i <= poly1 -> degree; i = i + 1) {
        for (int j = 0; j <= poly2 -> degree; j = j + 1) {

            // Le résultat de a_k * x^i * b_k * x^j sera a_k * b_k x^(i + j), d'où on multiplie les coefficient et accès à la somme des degrees 
            (r -> coefs)[i + j] = (r -> coefs)[i + j] + (poly1 -> coefs)[i] * (poly2 -> coefs)[j];

        }
    }

    return r;

}

// Ne prend aucun argument direct et utilise les entrées utilisateurs pour renvoyer un polynome
polynome* creer_a_la_main(void) {

    printf("Degree du polynome : ");
    int* degree;
    scanf("%d", degree);

    int* t = (int*)malloc(sizeof(int) * (*degree + 1));
    polynome* resultat = (polynome*)malloc(sizeof(polynome));

    // Boucle pour demander un à un les coefficients des degrès
    for (int i = 0; i <= *degree; i = i + 1) {
        printf("Coefficient du degree %d : ", i);
        scanf("%d", t + i); // (t + i) ici pour que scanf accède à *(t + i) c.a.d t[i], notre coefficient
    }

    resultat -> coefs = t;
    resultat -> degree = *degree;

    return resultat;
}


/* FIN DES FONCTIONS DEMANDEES */




















// FONCTIONS NON DEMANDEES

// Prend deux polynomes et renvoie poly1 - poly2
polynome* soustraction(polynome* poly1, polynome* poly2) {

    int deg1 = poly1 -> degree;
    int deg2 = poly2 -> degree;

    int max_degree = deg1 > deg2 ? deg1 : deg2;
    int n = max_degree;

    for (int i = n; i > 0; i = i - 1) {
        // seule modification ici: '+' -> '-' pour le test d'egalite
        if ((poly1 -> coefs)[i] - (poly2 -> coefs)[i] == 0) {
            max_degree = max_degree - 1;
        } else {
            break;
        }
    }

    int* t = (int*)malloc(sizeof(int) * max_degree);
    polynome* new_poly = (polynome*)malloc(sizeof(polynome));

    for (int i = 0; i <= max_degree; i = i + 1) {
        
        t[i] = 0;

        if (i <= deg1) {
            t[i] = t[i] + (poly1 -> coefs)[i];
        }

        if (i <= deg2) {
            // seule modification ici: '+' -> '-'
            t[i] = t[i] - (poly2 -> coefs)[i];
        }

    }

    new_poly -> coefs = t;
    new_poly -> degree = max_degree;
    
    return new_poly;

}

// Est utile dans la fonction division, et permet de vérifier que le degrée d'un polynome est bien celui attendu
// Renvoie donc le degrès du premier coefficient non égal à 0 pour un polynome donné en entrée
int actual_polynome_degree(polynome* poly) {

    int d = poly -> degree;
    for (int i = d; i >= 0; i = i - 1) {
        if ((poly -> coefs)[i] == 0) { // On baisse le dégré tant que les coefficients sont des 0 
            d = d - 1;
        } else {
            break; // Et on sort immédiatement de la boucle quand un coefficient non nul est rencontré
        }
    }

    return d;

}

// Sert également dans la fonction division
// Prend un polynome et le mulitplie par x^(degree), degree étant l'entier fourni 
polynome* augmenter_degree(polynome* poly1, int degree) {

    int new_degree = (poly1 -> degree) + degree;
    int* t = (int*)malloc(sizeof(int) * (new_degree + 1));
    polynome* r = (polynome*)malloc(sizeof(polynome));

    // On décale tous les coefficients de (degree)
    for (int i = 0; i <= poly1 -> degree; i = i + 1) {
        t[i + degree] = (poly1 -> coefs)[i];
    }

    r -> coefs = t;
    r -> degree = new_degree; 
    
    return r;

}

// Permet de réaliser la copie d'un polynome
polynome* copie(polynome* poly) {

    int* t = (int*)malloc(sizeof(int) * (poly -> degree + 1));
    polynome* r = (polynome*)malloc(sizeof(polynome));

    // Copie du degrès et des coefficients
    r -> coefs = t;
    r -> degree = poly -> degree;

    *(r -> coefs) = *(poly -> coefs);
    
    return r;

}

// Renvoie le résultat de la division longue de numerateur et denominateur
polynome* division(polynome* num, polynome* denominator) {

    // On réalise une copie de numérateur, car il sera modifié dans la fonction
    polynome* numerator = copie(num);
    
    // On défini un quotient
    int* quotient = (int*)malloc(sizeof(int) * ((numerator -> degree) - (denominator -> degree) + 1));

    int deg_n = numerator -> degree;
    int deg_d = denominator -> degree;


    // On initalise un polynome temporaire, qui va servire aux résultats intermédiaires
    polynome* temp1 = NULL;

    // Méthode de la division longue
    while (deg_n >= deg_d) {

        temp1 = augmenter_degree(denominator, deg_n - deg_d);
        quotient[deg_n - deg_d] = (numerator -> coefs)[deg_n] / (temp1 -> coefs)[deg_n];

        temp1 = produit_par_scalaire(temp1, quotient[deg_n - deg_d]);

        numerator = soustraction(numerator, temp1);

        deg_n = actual_polynome_degree(numerator);
        deg_d = actual_polynome_degree(denominator);

    }

    polynome* result = (polynome*)malloc(sizeof(polynome));

    result -> coefs = quotient;
    result -> degree = (numerator -> degree) - (denominator -> degree) + 1; 

    return result;

}

// Réalise les mêmes opérations que division, mais renvoie le reste à la fin
polynome* reste(polynome* num, polynome* denominator) {

    // On réalise une copie de numérateur, car il sera modifié dans la fonction
    polynome* numerator = copie(num);
    
    // On défini un quotient
    int* quotient = (int*)malloc(sizeof(int) * ((numerator -> degree) - (denominator -> degree) + 1));

    int deg_n = numerator -> degree;
    int deg_d = denominator -> degree;

    polynome* temp1 = NULL;

    while (deg_n >= deg_d) {

        temp1 = augmenter_degree(denominator, deg_n - deg_d);
        quotient[deg_n - deg_d] = (numerator -> coefs)[deg_n] / (temp1 -> coefs)[deg_n];

        temp1 = produit_par_scalaire(temp1, quotient[deg_n - deg_d]);

        numerator = soustraction(numerator, temp1);

        deg_n = actual_polynome_degree(numerator);
        deg_d = actual_polynome_degree(denominator);

    }

    // Ce qui reste dans le numérateur correspond au reste
    numerator -> degree = actual_polynome_degree(numerator);
    return numerator;

}

// Permet d'évaluer un polynome avec des chiffres décimaux
double evaluation_double(polynome* poly, double x) {

    if (poly -> degree == 0) {
        return (double)(poly -> coefs)[0];
    }

    // Toujours avec la méthode de Holder
    double sum = (poly -> coefs)[poly -> degree] * x + (poly -> coefs)[(poly -> degree) - 1];
    for (int i = poly -> degree - 2; i >= 0; i = i - 1) {
        sum = x * sum + (poly -> coefs)[i];
    }

    return sum;

}

// Méthode de newton, qui permet d'approximer des racines
double newtons_method(polynome* poly, double x0, int iterations) {

    double x_n = x0;
    
    polynome* deri = derivee(poly);

    // La méthode de Newton se réalise en utilisant une suite définie par x_(n+1) = x_n - P(x_n)/P'(x_n)
    for (int i = 0; i < iterations; i = i + 1) {
        x_n = x_n - evaluation_double(poly, x_n) / evaluation_double(deri, x_n);
    }

    return x_n;

}
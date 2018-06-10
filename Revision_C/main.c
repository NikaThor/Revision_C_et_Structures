
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <string.h>
#include <assert.h>
#include <limits.h>
#include <basetsd.h>
#include "digits.h"

#define PAUSE \
printf("\nPress la Touche\n"); \
    while (getchar() != '\n')

#define Ret_CH printf("\n")

#define PRINT_ADRESSE(ADR) printf("ox%" PRIxPTR "\n", (intptr_t) ADR)

#define Ret_CH printf("\n")

#define boolGenericMax(type)\
bool type##Max(type a, type b)\
{ return a > b ? true : false; }

boolGenericMax(double);

#define GenericMax(type)\
type type##Max(type a, type b)\
{ return a > b ? a : b; }

#define PRESS_LA_TOUCHE \
printf("\nPress la touche\n"); \
    while (getchar() != '\n')

typedef unsigned short ushrt;

const unsigned int LIGNE = 5;
const unsigned int COLONNE = 4;


typedef int Entier;

typedef enum {
    TRUE, FALSE
} Bool;

typedef struct {
    double reel;
    double imaginaire;
} Complexe;

struct Camion {
    unsigned volume;
};

struct Car {
    unsigned nbrePlace;
};

struct Moto {
    char type;
};

union DetailVehicule {
    struct Camion camion;
    struct Car car;
    struct Moto moto;
};

enum TypeVehicule {
    CAMION, CAR, MOTO
};

struct Vehicule {
    char noPlaques[10];
    unsigned annee;
    enum TypeVehicule typeVehicule;
    union DetailVehicule details;
};

struct Tableau {
    Entier tab[100]; // Entier <==> int 
};
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

typedef enum {
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
} Mois;
const char* MOIS[] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

typedef enum {
    LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE
} Jour;
const char *JOUR[] = {"lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi", "dimanche"};

typedef struct {
    int jour;
    Mois mois;
    int annee;
} Date;

typedef struct {
    int heure;
    int minute;
} Heure;

bool estBissextile(size_t annee) {
    return annee % 4 == 0 || (annee % 4 == 0 && 100 != 0);
}

int nbreJourMaxDunMois(Mois mois, int annee) {
    switch (mois) {
        case JAN: return 31;
        case FEB: return 28 + (int) estBissextile(annee);
        case MAR: return 31;
        case APR: return 30;
        case MAY: return 31;
        case JUN: return 30;
        case JUL: return 31;
        case AUG: return 31;
        case SEP: return 30;
        case OCT: return 31;
        case NOV: return 30;
        case DEC: return 31;
        default: return -1;
    }
}

Date fct_AfficheDate(Date date) {
    printf("%d-%s-%d\n", date.jour, MOIS[date.mois], date.annee);
    return date;
}

Date fct_setNextDay(Date date) {
    if (date.jour == nbreJourMaxDunMois(date.mois, date.annee)) {
        if (date.mois == 12) {
            date.jour = 1;
            date.mois = 1;
            date.annee++;
        } else {
            date.jour = 1;
            date.mois++;
        }
    } else {
        date.jour++;
    }
    return date;
}

Date fct_setBeforeDay(Date date) {
    if (date.jour == 1) {
        if (date.mois == 1) {
            date.jour = 31;
            date.mois = 12;
            date.annee--;
        } else {
            date.jour = nbreJourMaxDunMois(date.mois - 1, date.annee);
            date.mois--;
        }
    } else {
        date.jour--;
    }
    return date;
}

// Fonctions pour qsort

int fct_d1_After_d2(const void* d1, const void* d2) {
    const Date* dd1 = d1;
    const Date* dd2 = d2;
    if (dd1->annee < dd2->annee ||
            (dd1->annee == dd2->annee && (dd1->mois < dd2->mois)) ||
            (dd1->mois == dd2->mois && dd1->jour < dd2->jour))
        return 0;
    return 1;
}

int fct_d1_Before_d2(const void* d1, const void* d2) {
    return (!fct_d1_After_d2(d1, d2));
}
// --------------

void traiterLesDates(Date* tab, size_t taille, Date(*fct)(Date)) {
    for (int i = 0; i < taille; i++) {
        if (fct) {
            *(tab + i) = fct(*(tab + i));
        }
    }
}
// --------------

Bool fct_plusGrand_Date(const Date d1, const Date d2) {
    if (d1.annee < d2.annee ||
            (d1.annee == d2.annee && (d1.mois < d2.mois ||
            (d1.mois == d2.mois && d1.jour < d2.jour))))
        return FALSE;
    return TRUE;
}

Bool fct_plusPetit_Date(const Date d1, const Date d2) {
    return ( !fct_plusGrand_Date(d1, d2));
}

Bool fct_equal_Date(const Date d1, const Date d2) {
    return ( d1.jour == d2.jour &&
            d1.mois == d2.mois &&
            d1.annee == d2.annee);
}

int analyseSurDate(const Date d1, const Date d2, Bool(*fct)(const Date, const Date)) {
    int nbJours = 0;
    Date dd1 = d1;
    while (!fct(dd1, d2) && nbJours < 1000000) {
        nbJours++;
        dd1 = fct_setNextDay(dd1);
    }
    return nbJours;
}

bool strToJour(const char *jour, Jour * const j) {
    if (jour && j) {
        int nbJour = 7;
        for (int i = 0; i < nbJour; i++) {
            if (strcmp(jour, JOUR[i]) == 0) {
                *j = i;
                return true;
            }
        }
    }
    return false;
}
// -----------------------------------------------------------------------------
// ------------------ Autres structures dépendante des autres ------------------
// -----------------------------------------------------------------------------

struct Periode {
    Date debut;
    Date fin;
};

struct Personne {
    char* nom; // Pour bloc03. Sinon a été déclaré comme - char nom[30];
    char* prenom; // Pour bloc03. Sinon a été déclaré comme - char prenom[30];
    unsigned age;
    Date dateDeNaissance;
    struct Periode vacances;
    struct Vehicule vehicul_1, vehicul_2;
};
// Fonctions pour qsort

int fct_personnePlusJeuneQue(const void* d1, const void* d2) {
    const struct Personne* dd1 = d1;
    const struct Personne* dd2 = d2;

    if (dd1->dateDeNaissance.annee < dd2->dateDeNaissance.annee ||
            (dd1->dateDeNaissance.annee == dd2->dateDeNaissance.annee && dd1->dateDeNaissance.mois < dd2->dateDeNaissance.mois) ||
            (dd1->dateDeNaissance.mois == dd2->dateDeNaissance.mois && dd1->dateDeNaissance.jour < dd2->dateDeNaissance.jour))
        return FALSE;
    return TRUE;
}

int fct_personnePlusAgeeQue(const void* d1, const void* d2) {
    return (!fct_personnePlusJeuneQue(d1, d2));
}
// --------------

Date retourneDebut(const struct Periode periode) {
    return periode.debut;
}

void initTab(int* tab, size_t taille) {
    for (size_t i = 0; i < taille; i++) {
        *(tab + i) = 6;
    }
}

void affichePersonne(const struct Personne moi) {
    printf("%s %s\nage %d\n%d-%s-%d\n%d-%d-%d --> %d-%d-%d\n---------\n",
            moi.nom, moi.prenom,
            moi.age,
            moi.dateDeNaissance.jour, MOIS[moi.dateDeNaissance.mois], moi.dateDeNaissance.annee,
            moi.vacances.debut.jour, moi.vacances.debut.mois, moi.vacances.debut.annee, moi.vacances.fin.jour, moi.vacances.fin.mois, moi.vacances.fin.annee);
}

void afficherDate(const char* texte, const Date* date) {
    printf("%s%d-%d-%d\n", texte, date->jour, date->mois, date->annee);
}

void afficherVehiculePlaques(const struct Vehicule* adrVehivule) {
    printf("Plaques : %s\n", adrVehivule->noPlaques);
    printf("Constr : %d\n", adrVehivule->annee);
    switch (adrVehivule->typeVehicule) {
        case CAMION: printf("CAMION\n");
        case CAR: printf("CAR\n");
        case MOTO: printf("MOTO\n");
    }
}


// -----------------------------------------------------------------------------
// ---------------- Autres Fonctions -------------------------------------------
// -----------------------------------------------------------------------------

size_t recherche_Dichotomique(const int* tab, const int TAILLE, const int aChercher) {
    int first = 0, last = TAILLE;
    while (first < last) {
        size_t mid = (first + last) / 2;
        if (*(tab + mid) == aChercher) // c'est trouvé
            return mid;
        else if (*(tab + mid) < aChercher) // il faut chercher après
            first = mid + 1;
        else // il faut chercher avant
            last = mid;
    }
    return -1; // c'est pas trouvé
}

void afficher_bis(const int* ptr, size_t taille, const char* message) {
    assert(ptr != NULL);
    printf("%s[", message);
    for (size_t i = 0; i < taille; i++) {
        if (i > 0) printf("%s", ", ");
        printf("%d", *(ptr + i));
    }
    printf("]\n");
}
//------------------------------------------------
// affichers des matrices quelconques

void afficher(const int* tab, size_t LIGNE, size_t COL) {
    for (size_t ligne = 0; ligne < LIGNE; ++ligne) {
        for (size_t colonne = 0; colonne < COL; ++colonne)
            printf("%4d", *(tab + ligne * COL + colonne));
        printf("\n");
    }
}
//------------------------------------------------
//------------------------------------------------

const int* min(const int* tab, size_t LIGNE, size_t COL) {
    // en prenant les adresses
    const int* FIN = tab + LIGNE*COL;
    const int* reference = tab;

    while (tab + 1 < FIN) {
        if (*tab < *reference)
            reference = tab;
        ++tab;
    }

    return reference;
}

int** minMaxTab(const int tab[], size_t taille) {
    if (taille == 0 || tab == NULL)
        return NULL; //NULL si tab vaut NULL ou si tab est vide
    int** ptr = (int**) calloc(2, sizeof (int*)); //pour stocker min et max
    if (ptr) {
        int min = tab[0], max = tab[0];
        ptr[0] = ptr[1] = (int*) tab;
        for (size_t i = 0; i < taille; i++) {
            if (tab[i] < min) {
                min = tab[i];
                ptr[0] = (int*) &tab[i]; // Ou ptr[0] = (int*)(tab + i);
            } else if (tab[i] > max) {
                max = tab[i];
                ptr[1] = (int*) &tab[i]; // Ou ptr[1] = (int*)(tab + i);
            }
        }
    }
    return ptr;
}

int** minMaxTab_bis(const int tab[], size_t taille) {
    if (taille == 0 || tab == NULL)
        return NULL; //NULL si tab vaut NULL ou si tab est vide
    int** ptr = (int**) calloc(2, sizeof (int*)); //pour stocker min et max
    if (ptr) {
        ptr[0] = ptr[1] = (int*) tab;
        for (size_t i = 0; i < taille; i++) {
            if (*(tab + i) < *ptr[0]) {
                ptr[0] = (int*) &tab[i]; // Ou ptr[0] = (int*)(tab + i);
            } else if (*(tab + i) > *ptr[1]) {
                ptr[1] = (int*) (tab + i); // Ou ptr[1] = (int*)(tab + i);
            }
        }
    }
    return ptr;
}

//------------------------------------------------

void parcourirTab1D(int tab[], size_t LIGNE, int (*action) (int), const char* message) {// int* tab == int tab[]
    printf("%s", message);
    for (size_t i = 0; i < LIGNE; ++i)
        *(tab + i) = action(*(tab + i));
}

void parcourirTab2D(int (*tab)[], size_t LIGNE, size_t COLONE, int (*action) (int), const char* message) {
    printf("%s", message);
    for (size_t i = 0; i < LIGNE * COLONE; ++i)
        *(*tab + i) = action(*(*tab + i));
}

/*
void parcourirTab3D(const int** tab,  //(**tab)[MAX_LIGNE][MAX_COLONNE]
        size_t CELLS, size_t LIGNE, size_t COLONE, int (*action) (int), const char* message) {

    printf("%s", message);
    size_t taille = LIGNE * COLONE * CELLS;
    for (size_t i = 0; i < taille; ++i) {
        //*(tab + i) = action(*(tab + i));
    }
}
 */

//------------------------------------------------

int affi(int val) {
    printf("%d ", val);
    return val;
}

int plus2(int valeur) {
    return valeur + 2;
}

void plus2_bis(int* const adrValeur) {
    //*adrValeur += 2;
    *adrValeur = *adrValeur + 2;
}
//------------------------------------------------

int* pointeur(int* ptr) {
    *ptr = *ptr + 3;

    return ptr;
}
//------------------------------------------------
// serait identique (pour un tableau à 1 seule dimension)
// void put(const int tab[], unsigned taille) {

void put(const int* tab, unsigned taille) {
    // FAUX car tab est ici un pointeur et non un tableau
    // sizeof(tab)/sizeof(int)
    for (register unsigned i = 0; i < taille; ++i) {
        printf("tab[%d] = %d\n", i, *(tab + i));
        // serait identique à
        // printf("tab[%d] = %d\n", i, tab[i] );
    }
}
//------------------------------------------------
// la signature est "inutile" mais DOIT être
// compatible avec le pointeur de fonction de "parcourir"

int put_int(int valeur) {
    printf("%3d", valeur);
    return valeur;
}

char put_char(char valeur) {
    printf(" %c ", valeur);
    return valeur;
}
//------------------------------------------------

int saisie(const char* msg_invite, const char* msg_erreur, int MIN, int MAX) {

    bool ok;
    int valeur;
    do {
        printf("%s [%d - %d] : ", msg_invite, MIN, MAX);
        ok = (bool) scanf("%d", &valeur);
        while (getchar() != '\n');
    } while ((!ok || valeur < MIN || valeur > MAX) &&
            printf("%s\n", msg_erreur));
    return valeur;
}
//------------------------------------------------
//------------------------------------------------
// calculer la somme des éléments (ligne et colonne)

int somme0(const int* tab, size_t LIGNE, size_t COL) {
    int total = 0;
    // Méthode naïve
    for (size_t ligne = 0; ligne < LIGNE; ++ligne)
        for (size_t colonne = 0; colonne < COL; ++colonne)
            total += *(tab + ligne * COL + colonne); // Fameuse formule de parcourt de tableau
    return total;
}
//------------------------------------------------
// calculer la somme des éléments (en ligne)

int somme1(const int* tab, size_t LIGNE, size_t COL) {
    int total = 0;
    // en prenant tous les éléments
    for (size_t i = 0; i < LIGNE * COL; ++i)
        total += *(tab + i);
    return total;
}
//------------------------------------------------
// calculer la somme des éléments (par adresses)

int somme2(const int* tab, size_t LIGNE, size_t COL) {
    // en prenant les adresses
    const int* FIN = tab + LIGNE*COL;
    int total = 0;

    while (tab < FIN)
        total += *tab++;
    return total;
}
//------------------------------------------------
#define INT_SIZE sizeof(int) * 8

ushrt getBit(ushrt pos, int n) {
    //#define INT_SIZE sizeof(int) * 8
    assert(pos < INT_SIZE);
    return (n >> pos) & 1;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -------------- Les bateaux --------------------------------------------------

typedef const char* Nom;

typedef enum {
    VOILIER, MOTEUR
} Type_Bateau;
// On ne peut pas utiliser 'Nom'. Il faut utiliser 'char*' sinon, warning dans
// le 'printf' du 'main' qui le prend pour un 'char' ???
const char* TYPES_BATEAU[] = {"Voilier", "Moteur"};

typedef enum {
    PECHE, PLAISANCE
} Type_Bateau_Moteur;
// On ne peut pas utiliser 'Nom'. Il faut utiliser 'char*' sinon, warning dans
// le 'printf' du 'main' qui le prend pour un 'char' ???
const char* TYPE_BATEAU_MOTEUR[] = {"Bateau de peche", "Bateau de plaisance"};

typedef struct {
    uint16_t surfaceVoile;
} Voilier;

typedef struct {
    uint8_t tonnage;
} Peche;

typedef struct {
    char* nom;
} Plaisance;

typedef union {
    Peche bateauPeche;
    Plaisance bateauPlaisance;
} TypeBateauMoteur;

typedef struct {
    uint16_t puissance_CV;
    Type_Bateau_Moteur typeBateauMoteur;
    TypeBateauMoteur detailBateauMoteur;
} Moteur;

typedef union {
    Voilier voilier;
    Moteur moteur;
} SpecificiteBateau;

typedef struct {
    char* nom;
    Type_Bateau typeBateau;
    SpecificiteBateau detailBateau;
} Bateau;

typedef enum {
    PREMIERE, SECOND, CABINE
} classDuBillet;

typedef struct {
    uint8_t numeroPont;
    uint8_t numeroCabine;
} Cabine;

typedef struct {
    uint8_t numeroPlace;
} Premiere;

typedef struct {
    uint8_t numeroPlace;
} Second;

typedef union {
    Cabine billetEnCabine;
    Premiere billetEnPremiere;
    Second billetEnSeconde;
} TypeBillet;

typedef struct {
    char* nom;
    Date dateDepart;
    Heure heureDepart;
    char* lieuDepart;
    char* lieuArrive;
    classDuBillet classe;
    TypeBillet typeDuBillet;
} BilletBateau;

BilletBateau* Billet(const char* nom, const char* lieuDepart, const char* lieuArrive, const Date* d, const Heure* h, const classDuBillet classe, uint8_t place, uint8_t cabine, uint8_t pont) {
    if (!nom || !lieuDepart || !lieuArrive)
        return NULL;
    switch (classe) {
        case(PREMIERE):
            return &(BilletBateau){(char*) nom,
                {.jour = (int)
                    {d->jour}, .mois = (Mois)
                    {d->mois}, .annee = (int)
                    {d->annee}},
                {.heure = (int)
                    {h->heure}, .minute = (int)
                    {h->minute}},
                (char*) lieuDepart,
                (char*) lieuArrive,
                PREMIERE,
                {.billetEnPremiere.numeroPlace = (uint8_t)
                    {place}}};
        case(SECOND):
            return &(BilletBateau){(char*) nom,
                {.jour = (int)
                    {d->jour}, .mois = (Mois)
                    {d->mois}, .annee = (int)
                    {d->annee}},
                {.heure = (int)
                    {h->heure}, .minute = (int)
                    {h->minute}},
                (char*) lieuDepart,
                (char*) lieuArrive,
                SECOND,
                {.billetEnSeconde.numeroPlace = (uint8_t)
                    {place}}};
        case(CABINE):
            return &(BilletBateau){(char*) nom,
                {.jour = (int)
                    {d->jour}, .mois = (Mois)
                    {d->mois}, .annee = (int)
                    {d->annee}},
                {.heure = (int)
                    {h->heure}, .minute = (int)
                    {h->minute}},
                (char*) lieuDepart,
                (char*) lieuArrive,
                CABINE,
                (TypeBillet)
                {.billetEnCabine.numeroPont = (uint8_t)
                    {pont}, .billetEnCabine.numeroCabine = (uint8_t)
                    {cabine}}};

    }
}

void afficherBillet(const BilletBateau* b) {
    if (!b) {
        return;
    }
    printf("Nom             : %s\n", b->nom);
    afficherDate("Date depart     : ", &b->dateDepart);
    printf("Heure depart    : %d:%d\n", b->heureDepart.heure, b->heureDepart.minute);
    printf("Lieu depart     : %s\n", b->lieuDepart);
    printf("Lieu d'arrivee  : %s\n", b->lieuArrive);
    switch (b->classe) {
        case(PREMIERE):
            printf("Numero place    : %hhu\n", b->typeDuBillet.billetEnPremiere.numeroPlace);
            break;
        case(SECOND):
            printf("Numero place    : %hhu\n", b->typeDuBillet.billetEnSeconde.numeroPlace);
            break;
        case(CABINE):
            printf("Numero du pont  : %hhu\n", b->typeDuBillet.billetEnCabine.numeroPont);
            printf("Numero cabine   : %hhu\n", b->typeDuBillet.billetEnCabine.numeroCabine);
            break;

    }
    Ret_CH;
}

Bateau* Bateau_Voilier(Nom nomBateau, uint16_t surface) {
    // Obligé de caster le nom car il est const par defaut
    return &(Bateau){ (char*) nomBateau, VOILIER,
        {.voilier =
            {surface}}};
}

Bateau* Bateau_Peche(Nom nomBateau, uint16_t puissance, uint8_t tonnage) {
    return &(Bateau){ (char*) nomBateau, MOTEUR,
        {.moteur =
            {puissance, PECHE,{.bateauPeche =
                    {tonnage}}}}};
}

Bateau Bateau_Plaisance(Nom nomBateau, uint16_t puissance, Nom proprietaire) {
    return (Bateau){ (char*) nomBateau, MOTEUR,
        {.moteur =
            { puissance, PLAISANCE,{.bateauPlaisance =
                    { (char*) proprietaire}}}}};
}

void afficheBateau(const Bateau* b) {
    if (!b)
        return;
    switch (b->typeBateau) {
        case(VOILIER):
            printf("Nom             : %s\n", b->nom);
            printf("Genre           : %s\n", TYPES_BATEAU[b->typeBateau]);
            printf("Voilure [m2]    : %hu\n", b->detailBateau.voilier.surfaceVoile);
            break;
        case(MOTEUR):
            printf("Nom             : %s\n", b->nom);
            printf("Genre           : %s\n", TYPE_BATEAU_MOTEUR[b->detailBateau.moteur.typeBateauMoteur]);
            printf("Moteur [CV]     : %hu\n", b->detailBateau.moteur.puissance_CV);
            switch (b->detailBateau.moteur.typeBateauMoteur) {
                case(PECHE):
                    printf("Tonnage [Tonnes]: %hhu\n", b->detailBateau.moteur.detailBateauMoteur.bateauPeche.tonnage);
                    break;
                case(PLAISANCE):
                    printf("Proprietaire    : %s\n", b->detailBateau.moteur.detailBateauMoteur.bateauPlaisance.nom);
                    break;
            }
            break;
    }
}

int main(int argc, char** argv) {
    Bool suite = FALSE;
    goto BLOC31;

BLOC32:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n32\n");
        PAUSE;
}
    if (suite == FALSE)
        goto FIN;
BLOC31:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n31\n");
        PAUSE;
        Date dep =
        {6, 7, 2018};
        Heure hr =
        {22, 35};
        BilletBateau* b2 = Billet("Toto", "Honkong", "Majorka", &dep, &hr, PREMIERE, 12, 0, 0);
        ;
        BilletBateau* b3 = Billet("Tutu", "Paris", "Istanboul", &dep, &hr, SECOND, 29, 0, 0);
        ;
        BilletBateau* b1 = Billet("Lambert", "Geneve", "Hartolla", &dep, &hr, CABINE, 0, 42, 1);

        afficherBillet(b1);
        afficherBillet(b2);
        afficherBillet(b3);
}
    if (suite == FALSE)
        goto FIN;
BLOC30:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n30\n");
        PAUSE;
        Bateau* bateau_01 = Bateau_Voilier("Viking", 200);
        Bateau* bateau_02 = Bateau_Peche("Sirene", 100, 200);
        Bateau bateau_03 = Bateau_Plaisance("Daube", 300, "Escalope");

        afficheBateau(bateau_01);
        Ret_CH;
        afficheBateau(bateau_02);
        Ret_CH;
        afficheBateau(&bateau_03);
        Ret_CH;}

    if (suite == FALSE)
        goto FIN;
BLOC29:
    // -------------------------------------------------------------------------
    {
        printf("-------------------------------------------------------------------------\nBLOC n29\n");
        for (ushrt pos = INT_SIZE - 1; pos != 65535; --pos) {
            printf("%hu ", getBit(pos, SHRT_MAX));
        }
        Ret_CH;
}
    if (suite == FALSE)
        goto FIN;
BLOC28:
    // -------------------------------------------------------------------------
    {
        printf("-------------------------------------------------------------------------\nBLOC n28\n");
        PAUSE;
        const int TAILLE_TAB = 10;
        int tab[] =
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        int* copy = (int*) calloc(TAILLE_TAB, sizeof (int));


        if (!copy) {
            printf("Le calloc s'est mal passe et aucune reservation memoir a ete faite\n"
                    "La suite du programme sera instable\n"
                    "Il faudrait faire quelque chose....");
        }
        memcpy(copy, tab, TAILLE_TAB * sizeof (int));
        parcourirTab1D(tab, TAILLE_TAB, put_int, "\nAffiche tab              : ");
        parcourirTab1D(copy, TAILLE_TAB, put_int, "\nAffiche copy de tab      : ");

        printf("\n\nCreation de int* reallocation = NULL\n"
        "Reallocation de copy dans reallocation avec 50 * sizeof(int)\n");
        int* reallocation = NULL;
        reallocation = (int*) realloc(copy, 50 * sizeof (int));

        if (copy != reallocation) {
            parcourirTab1D(tab, TAILLE_TAB, put_int, "\nAffiche tab          : ");
            parcourirTab1D(copy, TAILLE_TAB, put_int, "\nAffiche copy de tab  : ");
            parcourirTab1D(reallocation, TAILLE_TAB, put_int, "\nAffiche reallocation : ");
            printf("\nAdr de copy != de Adr de reallocation\n"
                    "On realigne copy et reallocation\n");
            copy = reallocation;
        }

        parcourirTab1D(tab, TAILLE_TAB, put_int, "\nAffiche tab          : ");
        parcourirTab1D(copy, TAILLE_TAB, put_int, "\nAffiche copy de tab  : ");
        parcourirTab1D(reallocation, TAILLE_TAB, put_int, "\nAffiche reallocation qui a un espace de 50 cases: ");

        free(copy);
        free(reallocation);}
    if (suite == FALSE)
        goto FIN;
BLOC27:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n27\n");
        PAUSE;
        const int tab2D_int[5][4] =
        {
            {1, 2, 3, 4},
            {-4, 5, 6, -7},
            {9, 8, 7, 6},
            {5, 4, 3, 2},
            {1, 0, 1, 0}
        };
        for (size_t ligne = 0; ligne < LIGNE; ++ligne) {
            for (size_t colonne = 0; colonne < COLONNE; ++colonne) {
                //printf("%d ", *(tab2D + ligne * COLONNE + colonne));
                //printf("%4d", tab2D[ligne][colonne]);
                printf("%4d", *((*tab2D_int) + ligne * COLONNE + colonne)); // Affiche la valeur de la case
                printf("%8d", *(tab2D_int + ligne * COLONNE + colonne)); // Affiche l'adresse de la case
            }
            printf("\n");
        }
        printf("\n");
        const char tab2D_car[5][4] =
        {
            {'a', 'b', 'c', 'd'},
            {'e', 'f', 'g', 'h'},
            {'l', 'k', 'j', 'i'},
            {'m', 'n', 'o', 'p'},
            {'t', 's', 'r', 'q'}
        };
        for (size_t ligne = 0; ligne < LIGNE; ++ligne) {
            for (size_t colonne = 0; colonne < COLONNE; ++colonne) {
                //printf("%4d", tab2D[ligne][colonne]);
                printf("%4c", *((*tab2D_car) + ligne * COLONNE + colonne)); // Affiche la valeur de la case
                printf("%8d", *(tab2D_car + ligne * COLONNE + colonne)); // Affiche l'adresse de la case
            }
            Ret_CH;
        }
        Ret_CH;}
    if (suite == FALSE)
        goto FIN;
BLOC26:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n26\n");
        PAUSE;
        const t_matrice * ptrTab[12] =
        {&digitZero, &digitUn, &digitDeux, &digitTrois,
            &digitQuatre, &digitCinq, &digitSix, &digitSept,
            &digitHuit, &digitNeuf, &digitPlus, &digitMoins};


        printf("AFFICHE 1\n");
        for (size_t cellule = 0; cellule < 12; cellule++) {
            for (size_t ligneDigit = 0; ligneDigit < MAX_LIGNE; ligneDigit++) {
                printf("%s", ptrTab[cellule][0][ligneDigit]);
                printf("%s", (*(ptrTab[cellule]))[ligneDigit]);
                printf("\n");
            }
        }

        // Ou
        PRESS_LA_TOUCHE;

        printf("AFFICHE 2\n");
        for (size_t cellule = 0; cellule < 12; cellule++) {
            for (size_t ligneDigit = 0; ligneDigit < MAX_LIGNE; ligneDigit++) {
                for (size_t coloneDigit = 0; coloneDigit < MAX_COLONNE; coloneDigit++) {
                    //printf("%c", (*ptrTab[cellule])[ligneDigit][coloneDigit]);
                    //printf("%c", *( ( (const char*)   ptrTab[cellule]   ) + ligneDigit * MAX_COLONNE + coloneDigit ));
                    printf("%c", *(((const char*) *(ptrTab + cellule)) + ligneDigit * MAX_COLONNE + coloneDigit));
                }
                printf("\n");
            }
            printf("\n");
        }

        PRESS_LA_TOUCHE;

        printf("AFFICHE HORIZONTALE\n");
        for (size_t li = 0; li < MAX_LIGNE; li++) {
            for (size_t ce = 0; ce < 12; ce++) {
                for (size_t co = 0; co < MAX_COLONNE; co++) {
                    printf("%c", *(((const char*) *(ptrTab + ce)) + li * MAX_COLONNE + co));
                }
            }
            printf("\n");
        }


        printf("\ntest ... \n");
        for (size_t i = 0; i < MAX_LIGNE; ++i) {
            for (size_t j = 0; j < MAX_COLONNE; ++j)
                printf("%c", *((char*) digitSix + i * MAX_COLONNE + j));
            printf("\n");
        }}
    if (suite == FALSE)
        goto FIN;
BLOC25:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n25\n");
        PAUSE;
        // tableau à une dimension
        int tab[12] =
        {1, 2, 3, 4, 5};
        // pointeurs sur tableaux
        int* ptrTab = tab;
        ptrTab = NULL; // tableau à 1 dim.

        // tableau à deux dimensions
        int tab1[4][3] =
        {
            {1, 2, 3},
            {4, 5, 6},
            {0, 0, -1},
            {0, 0, 0}
        };

        // DECLARATION 1 SUR TAB1
        int* ptr1 = (int*) tab1;
        //ptr1 = NULL; // avec cast
        for (size_t i = 0; i < 12; i++) {
            printf("[%2d]", *(ptr1 + i)); // Aff la valeur de la case
            printf("%p ", (ptr1 + i)); // Aff l'adresse de la case
        }
        printf("\n");
        for (size_t li = 0; li < 4; li++) {
            for (size_t co = 0; co < 3; co++) {
                printf("[%2d]", *(ptr1 + li * 3 + co));
            }
            printf("\n");
        }
        PRESS_LA_TOUCHE;

        // DECLARATION 2 SUR TAB1
        int (*ptr2)[] = tab1;
        //ptr2 = NULL; // un ptr sur un tableau d'entiers
        for (size_t i = 0; i < 12; i++) {
            printf("[%2u]", *(*ptr2 + i)); // Aff la valeur de la case
            printf("%p ", (*ptr2 + i)); // Aff l'adresse de la case
        }
        PRESS_LA_TOUCHE;

        // parcours avec pointeur de fonction
        printf("\nFonction Parcourir\n");
        parcourirTab1D(tab, 12, put_int, "Affiche tab : ");
        parcourirTab1D(tab, 12, plus2, "\nIncremente de 2 tout le tableau\n");
        parcourirTab1D(tab, 12, put_int, "Affiche tab : ");

        PRESS_LA_TOUCHE;

        parcourirTab2D(tab1, 3, 4, put_int, "Affiche tab1 : ");
        parcourirTab2D(tab1, 3, 4, plus2, "\nIncremente de 2 tout le tableau\n");
        parcourirTab2D(tab1, 3, 4, put_int, "Affiche tab1 : ");

        PRESS_LA_TOUCHE;

        const int tab3D_int[][3][4] =
        {
            {
                {1, 2, 3, 4},
                {-4, 5, 6, -7},
                {9, 8, 7, 6}
            },
            {
                {5, 4, 3, 2},
                {5, 4, 3, 2},
                {1, 0, 1, 0}
            }
        };
        printf("Affiche parcourire3D\n");
        /*
                parcourirTab3D(tab3D_int, 2, 3, 4, put_int, "Affiche tab3D : ");
                parcourirTab3D(tab3D_int, 2, 3, 4, plus2, "\nIncremente de 2 tout le tableau\n");
         */
        printf("\n");
        /*
                parcourirTab3D(tab3D_int, 2, 3, 4, put_int, "Affiche tab3D : ");
         */}
    if (suite == FALSE)
        goto FIN;
BLOC24:
    // -------------------------------------------------------------------------    
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n24\n");
        PAUSE;
        // pointeurs
        const int CONSTANTE = 12;
        int variable = 7;
        float reel = 3.14;

        int* const ptr = (int*) &reel;

        printf("variable         : %d\n", variable);
        printf("valeur pointee   : %d\n", *ptr);
        printf("adresse variable : %p\n", &variable);
        printf("adresse prt      : %p\n", &ptr);
        printf("contenu prt      : %p\n", ptr);

        *ptr = 8;

        printf("variable         : %d\n", variable);
        printf("valeur pointee   : %d\n", *ptr);}
    if (suite == FALSE)
        goto FIN;
BLOC23:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n23\n");
        PAUSE;
        int tab1[][3] =
        {
            {1, 2, 3},
            {4, 5, 6}
        };
        const int tab2[3][4] =
        {
            {1, 2, 3},
            {-4, 5, 6}
        };

        int valeur = 3;
        const int* const ptr = &valeur;

        // vérification des adresses
        printf("tab          = %p\n", (void*) tab1);
        printf("tab*         = %p\n", (void*) *tab1);
        printf("&tab[0][0]   = %p\n", (void*) &tab1[0][0]);

        // affichers des matrices quelconques
        afficher((const int*) tab1, 2, 3);
        printf("\n");
        afficher((const int*) tab2, 3, 4);

        printf("somme0   = %d\n", somme0((const int*) tab2, 3, 4));
        printf("somme1   = %d\n", somme1((const int*) tab2, 3, 4));
        printf("somme2   = %d\n", somme2((const int*) tab2, 3, 4));

        printf("min      = %d\n", *min((const int*) tab2, 3, 4));}
    if (suite == FALSE)
        goto FIN;
BLOC22:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n22\n");
        PAUSE;
        int tab[10] =
        {18, 2, 3, 4, 5, 6, 7};

        printf("adresse tableau : %p\n", &tab);
        printf("adresse tableau : %p\n", tab);
        printf("valeur  tab[0]  : %d\n", tab[0]);
        printf("adresse tab[0]  : %p\n", &tab[0]);
        printf("adresse tab[1]  : %p\n", &tab[1]);
        printf("adresse tab+1   : %p\n", tab + 1);

        printf("valeur  tab[0]  : %d\n", tab[0]);
        printf("valeur  tab[0]  : %d\n", *tab);
        printf("valeur  tab[3]  : %d\n", tab[3]);
        printf("valeur  tab[3]  : %d\n", *(tab + 3));

        printf("nbre valeurs    : %ld\n", (tab + 9) - tab);

        pointeur(tab);
        printf("valeur  tab[0]  : %d\n", tab[0]);

        // ici possible et correct car dans l'espace de
        // définition de tab (voir commentaire dans la fonction)
        put(tab, sizeof (tab) / sizeof (int));}
    if (suite == FALSE)
        goto FIN;
BLOC21:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n21\n");
        PAUSE;
        int tab[10] =
        {18, 2, 3, 4, 5, 6, 7};

        printf("adresse tableau : %p\n", &tab);
        printf("adresse tableau : %p\n", tab);
        printf("valeur  tab[0]  : %d\n", tab[0]);
        printf("adresse tab[0]  : %p\n", &tab[0]);
        printf("adresse tab[1]  : %p\n", &tab[1]);
        printf("adresse tab+1   : %p\n", tab + 1);

        printf("valeur  tab[0]  : %d\n", tab[0]);
        printf("valeur  tab[0]  : %d\n", *tab);
        printf("valeur  tab[3]  : %d\n", tab[3]);
        printf("valeur  tab[3]  : %d\n", *(tab + 3));

        printf("nbre valeurs    : %ld\n", (tab + 9) - tab);

        pointeur(tab);
        printf("valeur  tab[0]  : %d\n", tab[0]);

        // ici possible et correct car dans l'espace de
        // définition de tab (voir commentaire dans la fonction)
        put(tab, sizeof (tab) / sizeof (int));

        int* ptr = tab;
        printf("*ptr = %d\n", (*ptr)++);
        printf("*ptr = %d\n", *ptr);

        int n = 12;
        int* ptr1 = &n;
        int* ptr2 = &n;

        if (*ptr1 == *ptr2)
            ;

        const char* chaine = "bonjour";
        const char* ptrChaine = chaine;
        printf("chaine    = %s\n", chaine);
        ptrChaine = chaine + 3;
        printf("ptrChaine = %s\n", ptrChaine);

        char zoo1 [][20] =
        {"chien", "chat"};
        char* zoo2 [] =
        {"chien", "chat"};
        char* ptrChar1 = zoo1[0];
        char* ptrChar2 = zoo2[0];

        char** ptrPtr = &ptrChar2;

        printf("%s\n", zoo1[1]);
        printf("%s\n", zoo2[1]);

        printf("ptrChar1 : %s\n", ptrChar1);
        printf("ptrChar2 : %s\n", ptrChar2);

        printf("*ptrPtr : %s\n", *ptrPtr);

        printf("**ptrPtr : %c\n", **ptrPtr);}
    if (suite == FALSE)
        goto FIN;
BLOC20:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n20\n");
        PAUSE;
        int valeur = saisie("une valeur", "c'est faux !!", -10, +10);

        int a = 12;
        int* ptrA = &a;

        printf("valeur de a : %d\n", a);
        printf("valeur de a : %d\n", *ptrA);

        scanf("%d", &a);
        scanf("%d", ptrA);

        printf("valeur de a : %d\n", a);
        printf("valeur de a : %d\n", *ptrA);}
    if (suite == FALSE)
        goto FIN;
BLOC19:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n19\n");
        PAUSE;
        int tab[] =
        {10, 10000, 42, 57, 1000, 10, -60};
        const int SIZE = sizeof (tab) / sizeof (int);
        int** minMax = NULL;
        minMax = minMaxTab_bis(tab, SIZE);
        printf("Adresse min %p\nmin : %d\n\nAdresse max %p\nmax : %d\n", *minMax, **minMax, *(minMax + 1), **(minMax + 1));}
    if (suite == FALSE)
        goto FIN;
BLOC18:
    // -------------------------------------------------------------------------
    {

        printf("\n-------------------------------------------------------------------------\nBLOC n18\n");
        PAUSE;
        const char* c[] =
        {"elle", "mangera", "une", "petite", "tomme"};
        const char** f = &c[4];
        const char** d[] =
        {c + 1, c + 2, c + 3, c + 4, c};
        const char*** e = &(*(d + 3)); // => = &d[3];

        printf("%s\n", **(e + 1));
        printf("%c", ***(e + 1));
        printf("%c\n", *(**(e - 1) + 2));
        for (int i = 0; i < 3; i++) {
            printf("%c", *(**(e - 2) + i));
        }
        printf("\n");

        printf("%s\n", **(d + 2));
        printf("%c", ***(d + 2));
        for (int i = 1; i < 5; i++) {

            printf("\n");
            printf("%c", *(**(d + 3) + i));
        }

        printf("%c\n", **f);
        printf("%s\n", *f);}
    if (suite == FALSE)
        goto FIN;
BLOC17:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n17\n");
        PAUSE;
        const char* c[] =
        {"comprendre", "tes", "hazardeux", "c\'est", "difficile"};
        const char** cp[] =
        {c, c + 2, c + 4, c + 1, c + 3};

        const char*** cpp1 = cp;
        const char*** cpp2 = &cp[0];
        const char*** ptr3 = cpp1;

        const char* ptr1 = *c;
        const char** ptr2 = c;


        printf("&**c        :   %p\n", &**c);
        printf("&***cp      :   %p\n", &***cp);
        printf("&***ptr3    :   %p\n", &***ptr3);
        printf("&***cpp1    :   %p\n", &***cpp1);
        Ret_CH;
        printf("*c          :   %p\n", *c);
        printf("**cp        :   %p\n", **cp);
        printf("**ptr3      :   %p\n", **ptr3);
        printf("**cpp1      :   %p\n", **cpp1);
        Ret_CH;
        printf("c           :   %p\n", c);
        printf("*ptr3       :   %p\n", *ptr3);
        printf("*cp         :   %p\n", *cp);
        printf("*cpp1       :   %p\n", *cpp1);
        Ret_CH;
        printf("cp          :   %p\n", cp);
        printf("ptr3        :   %p\n", ptr3);
        printf("cpp1        :   %p\n", cpp1);
        printf("cpp1        :   %p\n", cpp2);
        Ret_CH;



        printf("%s ", ptr1); //comprendre
        printf("%s", *(ptr2 + 4) + 7); //le - diffici le
        printf("%c ", *(*(ptr2 + 1) + 2)); //s - te s
        printf("%c", *(*(ptr2) + 3)); //p - com p rendre
        printf("%c", *(ptr1 + 1)); //o - c o mprendre
        printf("%c", *(ptr1 + 32)); //i - d i fficile
        printf("%c", *(**cpp2 + 6)); //n - compre n dre
        for (int i = 0; i < 2; i++) {
            printf("%c", *(*(*cpp1 + 1) + i)); //te - te s
        }
        printf("%c", *(*(*cpp1 + 2) + 7)); //u - hazarde u x
        printf("%s", ptr1 + 8); //re - comrend re
        printf("%c ", *(*(*cpp2 + 1) + 2)); //s - te s
        printf("%s", *(*cpp2 + 4)); //difficile
        printf("%c ", *(*(*cpp1 + 3) + 3)); //s - c'e s t
        printf("%s ", *(*cpp1 + 3)); //c'est
        printf("%c", *(*ptr2 + 3)); //p - com p rendre
        printf("%c", *(*(*cpp2 + 2) + 3)); //a - haz a rdeux
        printf("%c ", cpp2[0][1][2]); //s - te s
        printf("%s", ptr1 + 31); //difficile
        Ret_CH;
        for (size_t i = 0; i < 5; i++) {
            printf("%s ", c[i]);
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) {
            printf("%s ", *cp[i]);
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) {
            printf("%s ", *cpp1[i]);
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) {
            printf("%s ", **(cpp1 + i));
        }
        Ret_CH;

        int i = 0;


        for (i = 0; i < 3; i++) {
            printf("%c", *(**cpp1 + i));
            printf("%c", *(**cpp2 + i));
        }
        printf("%c", *(*cp[0] + 2));
        printf("%s ", *cpp1[2] + 8);
        printf("%s ", *cpp2[2] + 8);

        printf("%s ", *++*++cpp1);
        printf("%s ", *++*++cpp2);

        for (i = 1; i < 4; i++) {
            printf("%c", *(cpp1[-1][i % 3] + 2));
            printf("%c", *(cpp2[-1][i % 3] + 2));
        }
        printf("%c", **--*cpp1);
        printf("%c", **--*cpp2);
        printf("%s\n", **++cpp1 + 7);
        printf("%s\n", **++cpp2 + 7);}
    if (suite == FALSE)
        goto FIN;
BLOC16:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n16\n");
        PAUSE;
        // Variables
        char c = 'A';
        int i = 6;
        //Pointeurs
        char* ptrC = &c;
        int* ptrI = &i;
        //double pointeurs
        char* ptrPtrC1 = ptrC;
        char** ptrPtrC2 = &ptrC;

        //Affichage via les pointeurs
        printf("c            : %c\t&c         : %p\n", c, &c);
        printf("*ptrC        : %c\tptrC       : %p\t&ptrC     : %p\n",
        *ptrC, ptrC, & ptrC);
        printf("*ptrPtrC1    : %c\tptrPtrC1   : %p\t\t\t\t&ptrPtrC1 : %p\n",
        *ptrPtrC1, ptrPtrC1, &ptrPtrC1);
        printf("**ptrPtrC2   : %c\t*ptrPtrC2  : %p\tptrPtrC2  : %p\t&ptrPtrC2 : %p\n",
        **ptrPtrC2, *ptrPtrC2, ptrPtrC2, &ptrPtrC2);}
    if (suite == FALSE)
        goto FIN;
BLOC15:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n15\n");
        PAUSE;
        //tableau
        const char* tab[] =
        {"Je", "Suis", "Tres", "Content", "Aujourd'hui"}; // Collection de char*
        const char** tabPPtrC[] =
        {tab + 4, tab + 2, tab + 3, tab, tab + 1}; // Tableau de ptr de ptr de caractere

        //Pointeurs
        const char* ptr1 = *tab; // un simple ptr constant sur le 1er caractère de tab
        const char** ptr2 = tab; // ptr de ptr de caractere constant sur tab[0]
        const char*** ptr4 = &tabPPtrC[3]; // ptr de ptr de ptr de caractere sur l'adresse tabPPtrC[3] - qui est le début du tableau tab
        const char*** ptr5 = tabPPtrC; // ptr de ptr de ptr de caractere sur l'adresse tabPPtrC[0]

        //Affichage des deux tableaux
        for (size_t i = 0; i < 5; i++) {
            printf("%s ", *(tab + i)); // Ou tab[i]);
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) {
            printf("%s ", **(tabPPtrC + i)); // Ou *tabPPtrC[i]);
        }
        Ret_CH;
        //Affichage des pointeurs
        for (size_t i = 0; i < 33; i++) { // const char*   ptr1 = *tab;
            printf("%c", *(ptr1 + i)); // Je Suis Tres Content Aujourd'hui - caracteres par caracteres - affiche tab
        }
        Ret_CH;

        for (size_t i = 0; i < 33; i++) { // const char**  ptr2 = tab;
            printf("%c", *(*ptr2 + i)); // Je Suis Tres Content Aujourd'hui - caracteres par caracteres - affiche tab
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) { // const char**  ptr2 = tab;
            printf("%s ", *(ptr2 + i)); // Je Suis Tres Content Aujourd'hui - mots par mots - affiche tab
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) { // const char**  ptr2 = tab;
            printf("%c ", **(ptr2 + i)); // J S T C A - Les premiers caracteres de chaques mots - affiche tab
        }
        Ret_CH;

        for (size_t i = 0; i < 5; i++) { // const char*** ptr4 = &tabPPtrC[3];
            printf("%s ", *(*ptr4 + i)); // Je Suis Tres Content Aujourd'hui - mots par mots - affiche tab
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) { // const char*** ptr4 = &tabPPtrC[3];
            printf("%c ", **(*ptr4 + i)); // J S T C A - Les premiers caracteres de chaques mots - affiche tab
        }
        Ret_CH;
        for (size_t i = 0; i < 33; i++) { // const char*** ptr4 = &tabPPtrC[3];
            printf("%c", *(**ptr4 + i)); // Je Suis Tres Content Aujourd'hui - caracteres par caracteres - affiche tab
        }
        Ret_CH;

        // Pour afficher depuis ptr4 le tableau tabPPtrC : Rappel, ptr4 pointe sur la case 3 de tabPPtrC
        //ptr4-=3;   // On recule l'adresse pointé du pointeur de 3 cases. On se retrouve à {tab + 4} de tabPPtrC[0].
        ptr4 = ptr5; // Ou on affect la meme adresse pointé
        Ret_CH;
        for (size_t i = 0; i < 5; i++) { // const char*** ptr4 = &tabPPtrC[0]; <==> Changement d'endroit pointé
            printf("%s ", **(ptr4 + i)); // Aujourd'hui Tres Content Je Suis - mots par mots - affiche tabPPtrC
        }
        Ret_CH;
        for (size_t i = 0; i < 5; i++) { // const char*** ptr5 = tabPPtrC;
            printf("%s ", **(ptr5 + i)); // Aujourd'hui Tres Content Je Suis - mots par mots - affiche tabPPtrC
        }
        Ret_CH;}
    if (suite == FALSE)
        goto FIN;
BLOC14:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n14\n");
        PAUSE;
        int n = 127;
        double x = 12.3456;

        printf("R1 : |%-4d|\n", n);
        printf("R2 : |%04d|\n", n);
        printf("R3 : |%x|\n", n);
        printf("R4 : |%#o|\n", n);
        printf("R5 : |%f|\n", x);
        printf("R6 : |%5.2f|\n", x);
        printf("R7 : |%.2e|\n", x);
        printf("R8 : |%g|\n", x);}
    if (suite == FALSE)
        goto FIN;
BLOC13:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n13\n");
        PAUSE;

        size_t i = 1;
        uint32_t j = UINT32_MAX;

        printf("%zd\n", i); // 1
        printf("%u\n", j); // 4294967295
    }
    if (suite == FALSE)
        goto FIN;
BLOC12:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n12n");
        PAUSE;
        int n;
        char c;
        printf("Un nbre et un cara : ");
        scanf("%d", &n);
        while (getchar() != '\n');
        scanf("%c", &c);
        printf("%d %c\n", n, c);}
    if (suite == FALSE)
        goto FIN;
BLOC11:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n11\n");
        PAUSE;

        int n = 1;
        int* ptr = &n;
        printf("%d\n", *ptr);
        printf("%p\n", ptr);
        printf("%p\n", &n);
        printf("%p\n", &ptr);}
    if (suite == FALSE)
        goto FIN;
BLOC10:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n10\n");
        PAUSE;
        int taille = 5;
        int a[] =
        {65, 66, 67, 68, 69};
        int* ptr1 = a;
        int* ptr2 = a;
        int** ptr3 = &ptr1;

        printf("%c, %p\n", **ptr3, ptr2);

        int** ptr4 = NULL;
        ptr4 = minMaxTab_bis(a, taille);
        printf("%d,  %d\n", **ptr4, **(ptr4 + 1));

        parcourirTab1D(a, taille, affi, "Fonction parcourirs -->\n");
        Ret_CH;

        int* copy = (int*) calloc(taille, sizeof (int));
        memcpy(copy, a, taille * sizeof (int));

        for (int* i = copy; i < copy + taille; i++) {
            printf("%c ", *i);
        }
        Ret_CH;
        free(copy);
        copy = NULL;}
    if (suite == FALSE)
        goto FIN;

BLOC09:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n09\n");
        PAUSE;
#define str(x) #x
#define xstr(s) str(s)
#define NAME_LEN_MAX 80
        GenericMax(int);
        char name[NAME_LEN_MAX + 1];
        printf("entrer une CHAINE de caractere et les 80 seront retenu\n");
        for (int i = 0; i < 80; i++)
            printf("%d", i % 10);
        Ret_CH;
        scanf("%" xstr(NAME_LEN_MAX) "s", name);
        printf("%s", name);

        int a = 3;
        double b = 4.6;
        printf("\n%d\n", intMax(a, b));}

    if (suite == FALSE)
        goto FIN;
BLOC08:
    // -------------------------------------------------------------------------
    {
        printf("\n-------------------------------------------------------------------------\nBLOC n08\n");
        PAUSE;

        /* char chaine0[]; */
        /* ne compile pas, car la taille ne peut être déterminée */
        char chaine1[] =
        {'E', 'r', 'r', 'o', 'r'};
        /* il manque '\0', le tableau est correct, mais */
        /* inutilisable comme chaîne C : l’affichage par */
        /* printf("%s", chaine1) est indéterminé après Error */
        char chaine2[] =
        {'H', 'e', 'l', 'l', 'o', '\0'};
        /* correct mais lourd, d'où le raccourci suivant : */
        char chaine3[] = "Hello";
        /* même effet que chaine2 */
        /* les tailles de chaine2 et de chaine3 valent 6 */
        char chaine4[10] = "Bonjour";
        /* correct, toute la place n'est pas utilisée, taille 10 */
        for (int i = 0; i < 22; ++i)
            printf("%c ", chaine4[i]);
        /* B o n j o u r 􀀀 􀀀 􀀀 H e l l o 􀀀 H e l l o 􀀀 */
        /* Ne pas chercher à accéder aux adresses non prévues ! */
        char* chaine5; /* correct, pointeur sur un caractère */
        chaine5 = chaine4;
        /* affecte à chaine5 l'adresse de chaine4 */
        /* affichée comme "Bonjour" mais sa taille vaut 4 */
        for (int i = 0; i < 6; ++i) chaine5[i] = chaine2[i];
        /* on modifie chaine5, attention à garder/copier le \0 */
        /* l'affichage de chaine5 par printf("%s", chaine1) */
        /* donne "Hello", tout comme chaine4 (modifiée aussi) */

        char c;
        int nbre;
        printf(" Un chiffre à convertir en hexa (0->15)  ");
        scanf("%d", &nbre);
        c = "0123456789ABCDEF"[nbre];
        printf("%c\n", c);}

    if (suite == FALSE)
        goto FIN;
BLOC07:
    // -------------------------------------------------------------------------
    {
        printf("\nBLOC 06\n");

        const int TAILLE_COLLECT = 3;
        struct Personne collectionPersonne[TAILLE_COLLECT];
}
    if (suite == FALSE)
        goto FIN;
BLOC06:
    // -------------------------------------------------------------------------
    {
        printf("\nBLOC 06\n");

        Date maDate =
        { 6, FEB, 1971};
        Date dateLimite =
        { 1, 6, 2018};
        int nbJ = 0;

        nbJ = analyseSurDate(maDate, dateLimite, fct_plusPetit_Date);
        printf("\nLa diff : %d\n", nbJ);
        Ret_CH;

        nbJ = analyseSurDate(maDate, dateLimite, fct_equal_Date);
        printf("\nEqual : %d\n", nbJ);
        Ret_CH;

        afficherDate("Date   : ", &maDate);
        afficherDate("Date   : ", &dateLimite);
        Ret_CH;
}
    if (suite == FALSE)
        goto FIN;
BLOC05:// Labo 10
    // -------------------------------------------------------------------------
    {
        printf("\nBLOC 05\n");
        Date dateTab[] =
        {
            {12, MAR, 2002},
            { 1, JAN, 2013},
            {31, MAY, 2018},
            {28, FEB, 2002},
            {31, DEC, 1999},
            { 6, FEB, 1971}
        };
        const size_t SIZE = sizeof (dateTab) / sizeof (Date);

        printf("\ntableau de dates\n");
        traiterLesDates(dateTab, SIZE, fct_AfficheDate);

        printf("\nplus 1 jour\n");
        traiterLesDates(dateTab, SIZE, fct_setNextDay);
        traiterLesDates(dateTab, SIZE, fct_AfficheDate);

        printf("\nmoin 1 jour\n");
        traiterLesDates(dateTab, SIZE, fct_setBeforeDay);
        traiterLesDates(dateTab, SIZE, fct_AfficheDate);

        printf("\ntri croissant des dates\n");
        qsort(dateTab, SIZE, sizeof (Date), fct_d1_After_d2);
        traiterLesDates(dateTab, SIZE, fct_AfficheDate);

        printf("\ntri decroissant des dates\n");
        qsort(dateTab, SIZE, sizeof (Date), fct_d1_Before_d2);
        traiterLesDates(dateTab, SIZE, fct_AfficheDate);

        //printf("presser ENTER pour quitter");
        //while (getchar() != '\n');
    }
    if (suite == FALSE)
        goto FIN;
BLOC04:
    // -------------------------------------------------------------------------
    {
        printf("\nBLOC 04\n");
        struct Vehicule moto;
        strcpy(moto.noPlaques, "VI123");
        moto.details.moto.type = 'M';
        //afficherVehiculePlaques(moto);
    }
    if (suite == FALSE)
        goto FIN;
BLOC03:
    // -------------------------------------------------------------------------
    {
        printf("\nBLOC 03\n");

        const size_t TAILLE = 3;
        struct Personne collectionPersonne[TAILLE];

        collectionPersonne[0].nom = "Personne";
        collectionPersonne[0].prenom = "Age Moyen";
        collectionPersonne[0].age = 47;
        collectionPersonne[0].dateDeNaissance = (Date)
        { 8, FEB, 1981};
        collectionPersonne[0].vacances = (struct Periode)
        {
            {1, AUG, 18},
            {1, OCT, 18}
        };

        collectionPersonne[1].nom = "Peronne";
        collectionPersonne[1].prenom = "Age Jeune";
        collectionPersonne[1].age = 4;
        collectionPersonne[1].dateDeNaissance = (Date)
        { 6, APR, 2015};
        collectionPersonne[1].vacances = (struct Periode)
        {
            {1, 7, 28},
            {1, NOV, 28}
        };

        collectionPersonne[2].nom = "Personne";
        collectionPersonne[2].prenom = "Agee";
        collectionPersonne[2].age = 7;
        collectionPersonne[2].dateDeNaissance = (Date)
        { 16, 12, 1911};
        collectionPersonne[2].vacances = (struct Periode)
        {
            {11, 17, 18},
            {11, 19, 18}
        };

        printf("\n---------\n");
        for (int i = 0; i < TAILLE; i++) {
            affichePersonne(collectionPersonne[i]);
        }
        PAUSE;

        qsort(collectionPersonne, TAILLE, sizeof (struct Personne), fct_personnePlusJeuneQue);

        printf("\n---------\n");
        for (int i = 0; i < TAILLE; i++) {
            affichePersonne(collectionPersonne[i]);
        }

        qsort(collectionPersonne, TAILLE, sizeof (struct Personne), fct_personnePlusAgeeQue);

        printf("\n---------\n");
        for (int i = 0; i < TAILLE; i++) {
            affichePersonne(collectionPersonne[i]);
        }}
    if (suite == FALSE)
        goto FIN;
BLOC02:
    // -------------------------------------------------------------------------
    {
        printf("\nBLOC 02\n");
        Date naissance =
        {6, 2, 1971};
        struct Periode vacances =
        {
            {1, 7, 18},
            {1, 9, 18}
        };
        struct Personne moi =
        {"Lambert", "Dimitri", 47, naissance, vacances};

        printf("Voici le resumee de unePersonne:\n");
        affichePersonne(moi);}
    if (suite == FALSE)
        goto FIN;
BLOC01:
    // -------------------------------------------------------------------------
    {
        printf("\nBLOC 01\n");

        Date uneDate;
        Date uneAutreDate =
        {6, 2, 1971};
        struct Periode vacances =
        {
            {1, 6, 2018},
            {1, 9, 2020}
        };
        struct Personne unePersonne =
        {"Lambert", "Dimitri", 47, // Nom, Prenom, Age
            {6, 2, 1971}, // Date de naissance
            {
                {1, 6, 2018}, // Periode de vacances debut
                {1, 9, 2018} // Periode de vacances fin
            }};

        printf("Voici le resumee de unePersonne:\n");
        printf("%s\n%s\n%d\n%d-%d-%d\n%d-%d-%d\n%d-%d-%d\n---------\n", unePersonne.nom, unePersonne.prenom, unePersonne.age, unePersonne.dateDeNaissance.jour, unePersonne.dateDeNaissance.mois, unePersonne.dateDeNaissance.annee,
        unePersonne.vacances.debut.jour, unePersonne.vacances.debut.mois, unePersonne.vacances.debut.annee, unePersonne.vacances.fin.jour, unePersonne.vacances.fin.mois, unePersonne.vacances.fin.annee);

        afficherDate("Date   : ", &vacances.debut);
        afficherDate("Date   : ", &vacances.fin);
        vacances.fin.annee = 2018;

        afficherDate("Date   : ", &vacances.debut);
        afficherDate("Date   : ", &vacances.fin);

        vacances.debut = vacances.fin;
        afficherDate("Date   : ", &vacances.debut);
        afficherDate("Date   : ", &vacances.fin);

        struct Tableau tab1, tab2;
        initTab(tab1.tab, 10);
        tab2 = tab1;
        for (int i = 0; i < 10; i++) {
            printf("%d ", tab2.tab[i]);
        }
        printf("\n");

        Date collection[10];
        collection[0] = vacances.debut;
        collection[0].jour = 17;

        uneDate.jour = 6;
        uneDate.mois = 2;
        uneDate.annee = 1971;

        printf("%d-%d-%d\n", uneDate.jour, uneDate.mois, uneDate.annee);
        printf("%d-%d-%d\n", uneAutreDate.jour, uneAutreDate.mois, uneAutreDate.annee);
        afficherDate("Date   : ", &uneAutreDate);}

FIN:
    PAUSE;
    return (EXIT_SUCCESS);
}
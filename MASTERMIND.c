#include <stdio.h>
#include <stdlib.h>
#define TAILLE 5
#define MAX_ESSAIS 20
void saisirCodeSecret(int code[], int niveau);
void saisirCodeJoueur(int code[]);
void verifierCombinaison(int secret[], int joueur[], int *bienPlaces, int *malPlaces);
int gererJoker(int secret[]);
int verifierDoublons(int code[]);
int main() {
    int codeSecret[TAILLE];
    int codeJoueur[TAILLE];
    int niveau;
    int nb_essais = 0;
    int gagne = 0;
    int bp, mp;
    int jokerDispo = 1;
    int k;
    char nomJ1[50], nomJ2[50];
    printf("=== JEU MASTERMIND ===\n");
    printf("Joueur 1 : ");
    scanf("%s", nomJ1);
    printf("Joueur 2 : ");
    scanf("%s", nomJ2);
    do {
        printf("\nNiveaux :\n1. Debutant(tous les chiffres du code sont distincts)\n2. Expert(les chiffres peuvent se repeter)\nChoix : ");
        scanf("%d", &niveau);
    } while (niveau != 1 && niveau != 2);
    printf("\n%s, entrez le code secret.\n", nomJ1);
    saisirCodeSecret(codeSecret, niveau);
    for (k = 0; k < 100; k++) {
        printf("\n");
    }
    printf("Code enregistre.\n");
    while (nb_essais < MAX_ESSAIS && gagne == 0) {
        printf("\nEssai %d / %d\n", nb_essais + 1, MAX_ESSAIS);
        if (nb_essais >= 9 && jokerDispo == 1) {
            int choix;
            printf("JOKER DISPONIBLE (1=Oui, 0=Non) : ");
            scanf("%d", &choix);
            if (choix == 1) {
                int penalite = gererJoker(codeSecret);
                nb_essais =nb_essais + penalite;
                jokerDispo = 0;
                if (nb_essais >= MAX_ESSAIS) {
                    printf("Joker utilise. Plus d'essais disponibles.\n");
                    break;
                }
            }
        }
        saisirCodeJoueur(codeJoueur);
        verifierCombinaison(codeSecret, codeJoueur, &bp, &mp);
        printf("Resultat : %d Bien places, %d Mal places\n", bp, mp);
        if (bp == TAILLE) {
            gagne = 1;
        } else {
            nb_essais++;
        }
    }
    printf("\n=============================================\n");
    if (gagne) {
        printf("BRAVO %s ! Score : %d essais.\n", nomJ2, nb_essais + 1);
    } else {
        printf("PERDU. Le code etait : ");
        for (int i = 0; i < TAILLE; i++) printf("%d ", codeSecret[i]);
        printf("\n");
    }
    return 0;
}
int verifierDoublons(int code[]) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = i + 1; j < TAILLE; j++) {
            if (code[i] == code[j]) return 1;
        }
    }
    return 0;
}
void saisirCodeSecret(int code[], int niveau) {
    int valide = 0;
    while (!valide) {
        printf("Entrez %d chiffres (0-9) avec espace entre les chiffres : ", TAILLE);
        int correct = 1;
        for (int i = 0; i < TAILLE; i++) {
            scanf("%d", &code[i]);
            if (code[i] < 0 || code[i] > 9) correct = 0;
        }
        if (correct == 0) {
            printf("Chiffres invalides.\n");
        } else if (niveau == 1 && verifierDoublons(code)) {
            printf("Erreur : Chiffres doivent etre distincts.\n");
        } else {
            valide = 1;
        }
    }
}
void saisirCodeJoueur(int code[]) {
    printf("Votre proposition : ");
    for (int i = 0; i < TAILLE; i++) {
        scanf("%d", &code[i]);
    }
}
void verifierCombinaison(int secret[], int joueur[], int *bienPlaces, int *malPlaces) {
    int tempS[TAILLE], tempJ[TAILLE];
    int i, j;
    *bienPlaces = 0;
    *malPlaces = 0;
    for (i = 0; i < TAILLE; i++) {
        tempS[i] = secret[i];
        tempJ[i] = joueur[i];
    }
    for (i = 0; i < TAILLE; i++) {
        if (tempJ[i] == tempS[i]) {
            (*bienPlaces)++;
            tempS[i] = -1;
            tempJ[i] = -2;
        }
    }
    for (i = 0; i < TAILLE; i++) {
        if (tempJ[i] != -2) {
            for (j = 0; j < TAILLE; j++) {
                if (tempS[j] != -1 && tempJ[i] == tempS[j]) {
                    (*malPlaces)++;
                    tempS[j] = -1;
                    break;
                }
            }
        }
    }
}
int gererJoker(int secret[]) {
    int choix;
    printf("1. Reveler un chiffre (Cout: 3)\n");
    printf("2. Tester exclusion (Cout: 5)\n");
    printf("Choix : ");
    scanf("%d", &choix);
    if (choix == 1) {
        int pos;
        printf("Position (1-5) : ");
        scanf("%d", &pos);
        if (pos >= 1 && pos <= 5) {
            printf("Chiffre : %d\n", secret[pos - 1]);
        }
        return 3;
    }
    else if (choix == 2) {
        int val, present = 0;
        printf("Chiffre a tester : ");
        scanf("%d", &val);
        for (int i = 0; i < TAILLE; i++) {
            if (secret[i] == val) present = 1;
        }
        if (present) printf("Le chiffre %d est present.\n", val);
        else printf("Le chiffre %d est absent.\n", val);
        return 5;
    }
    return 0;
}
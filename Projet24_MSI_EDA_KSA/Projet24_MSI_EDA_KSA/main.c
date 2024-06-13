//-----------------------------------------------------------------------------------//
// Nom du projet 		:
// Nom du fichier 		:
// Date de création 	: 07.03.2024
// Date de modification :
//
// Auteur 				: Etienne De Oliveira
//
// Description          :
//----------------------------------------------------------------------------------//

//-- délcaration des libraires systèmes --//
#pragma warning(disable: 4996)
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

//-------------------------------------------------------------------------------------------------------
//--------------//
// Fichier logs	//
// KSA			//
// 30.05.2024	//
//--------------//

// Définition du chemin et du nom du fichier des logs
#define FICHIER_LOG "Logs.log"

// Compteur pour le nombre d'utilisation des fonctions
int NbrUtilisationBin = 0; // Compteur pour la fonction Binaire
int NbrUtilisationTri = 0; // Compteur pour la fonction Trigonométrique

// Fonction pour avoir la date actuel dans la chaîne de caractères
const char* date()
{
    static char buffer_date[11]; // Buffer pour stocker la date
    time_t date; // Variable pour la date actuel
    struct tm date_info; // Structure pour les informations de date
    time(&date); // Obtention de la date actuel

    // Utilisation de localtime_s pour obtenir les informations sur la date
    localtime_s(&date_info, &date);

    // Formater la date en chaîne de caractères "YYYY-MM-DD"
    strftime(buffer_date, sizeof(buffer_date), "%d.%m.%Y", &date_info);
    return buffer_date; // Retourner la chaîne de caractères
}

// Fonction pour avoir l'heure actuel dans la chaîne de caractères
const char* heure()
{
    static char buffer_heure[6]; // Buffer pour stocker l'heure
    time_t heure; // Variable pour l'heure actuel
    struct tm heure_info; // Structure pour les informations d'heure
    time(&heure); // Obtention de l'heure acutel

    // Utilisation de localtime_s pour obtenir les informations sur l'heure
    localtime_s(&heure_info, &heure);

    // Formater l'heure en chaîne de caractères
    strftime(buffer_heure, sizeof(buffer_heure), "%H:%M", &heure_info);
    return buffer_heure; // Retourner la chaîne de caractères
}
// Fonction pour écrire une ligne de texte dans le fichier de log
void ecrire_log(const char* format, ...)
{
    FILE* fichier_log;

    // Utilisation de fopen_s pour ouvrir le fichier de logs 
    errno_t err = fopen_s(&fichier_log, FICHIER_LOG, "a");

    // Vérifie si le fichier est ouvert correctement
    if (err != 0)
    {
        // Affiche une erreur si le fichier ne peut pas être ouvert
        fprintf(stderr, "Erreur d'ouverture du fichier de log\n");
        return; // Quitter la fonction en cas d'erreur
    }
    // Écrire le message formaté dans les logs
    va_list args; // Liste d'arguments variadiques (nbr qui peut varier)
    va_start(args, format); // Inistaliser la liste d'arguments
    vfprintf(fichier_log, format, args); // Écrire le message formaté dans le fichier
    va_end(args); // Terminer la liste d'arguments

    // Ajouter une nouvelle ligne
    fprintf(fichier_log, "\n");

    // Fermer le fichier de log
    fclose(fichier_log);
}
// Fonction binaire (exemple)
void log_binaire(int entree, int resultat)
{
    NbrUtilisationBin++; // Incrémenter le compteur de la fonction binaire
    // Écrire le log pour la fonction binaire
    ecrire_log("compteur utilisation fonction binaire : %02d\n", NbrUtilisationBin);
    ecrire_log("%s - %s\n%d / %0b\n", date(), heure(), entree, resultat);
}
// Fonction trigonométrique (exemple)
void log_trigonometrie(float entree1, float entree2, float x, float y, float z, float a, float b, float c, float resultat)
{
    NbrUtilisationTri++; // Incrémenter le compteur de la fonction trigonométrique
    // Écrire le log pour la fonction trigonométrique
    ecrire_log("compteur utilisation fonction trigonométrique : %02d\n", NbrUtilisationTri);
    ecrire_log("%s - %s\n%.1f, %.1f / %.1f, %.1f, %.1f, %.1f, %.1f, %.1f, %.2f\n",
        date(), heure(), entree1, entree2, x, y, z, a, b, c, resultat);
}
//-------------------------------------------------------------------------------------------------------

/***************************************************************
 *                                                             *
 *                       Conv. binaire						   *
 *                                                             *
 * Description : Cette fonction additionne deux entiers.       *
 *                                                             *
 * Paramètres d'entrée :                                       *
 *   - a : Premier entier                                      *
 *   - b : Deuxième entier                                     *
 *                                                             *
 * Paramètre de sortie :                                       *
 *   Le résultat de l'addition.                                *
 *                                                             *
 ***************************************************************/
// Fonction pour la conversion des entiers en binaire sans spécification de bits
void ConversionEntier(int num) {
    if (num == 0) {
        printf("0");
        return;
    }

    int size = 32;
    int debut = 0;
    char tbBin[32];

    for (int i = size - 1; i >= 0; i--) {
        tbBin[i] = (num & 1) + '0';
        num >>= 1;
    }

    // Trouver la première position de 1
    for (int i = 0; i < size; i++) {
        if (tbBin[i] == '1') {
            debut = i;
            break;
        }
    }

    // Afficher la partie utile du nombre binaire
    for (int i = debut; i < size; i++) {
        printf("%c", tbBin[i]);
    }
}

// Fonction pour la conversion des entiers en binaire avec spécification de bits
void ConversionEntierBits(int num, int bits) {
    int mask = (1 << (bits - 1));
    if (num < 0) {
        num = (~(-num) + 1) & ((1 << bits) - 1);
    }
    for (int i = 0; i < bits; i++) {
        printf("%d", (num & mask) ? 1 : 0);
        if ((i + 1) % 4 == 0) {
            printf(" ");
        }
        num <<= 1;
    }
}

// Fonction pour la conversion des nombres réels en binaire
void ConversionReelBin(float num) {
    int partEntiere = (int)num;
    float partFract = num - partEntiere;
    int tbBits[32];
    int i = 0;

    while (partEntiere > 0) {
        tbBits[i++] = partEntiere % 2;
        partEntiere /= 2;
    }

    printf("0b ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", tbBits[j]);
    }

    printf(".");
    for (int k = 0; k < 3; k++) {
        partFract *= 2;
        if (partFract >= 1) {
            printf("1");
            partFract -= 1;
        }
        else {
            printf("0");
        }
    }
}

// Fonction pour l'affichage en binaire en fonction de l'option choisie
void AffBin(int num, float numReel, char* ptoption) {
    if (strcmp(ptoption, "Aucune") == 0) {
        if (num == numReel) {  // C'est un entier
            printf("0b ");
            ConversionEntier(num);
        }
        else {  // C'est un nombre réel
            ConversionReelBin(numReel);
        }
        printf("\n");
    }
    else if (strcmp(ptoption, "8 digits") == 0) {
        if (num == numReel) {
            if (num > 127 || num < -128) {
                printf("Overflow\n");
            }
            else {
                printf("0b ");
                ConversionEntierBits(num, 8);
            }
        }
        else {
            ConversionReelBin(numReel);
        }
        printf("\n");
    }
    else if (strcmp(ptoption, "16 digits") == 0) {
        if (num == numReel) {
            if (num > 32767 || num < -32768) {
                printf("Overflow\n");
            }
            else {
                printf("0b ");
                ConversionEntierBits(num, 16);
            }
        }
        else {
            ConversionReelBin(numReel);
        }
        printf("\n");
    }
    else if (strcmp(ptoption, "32 digits") == 0) {
        if (num == numReel) {
            if (num > 2147483647 || num < -2147483647) {
                printf("Overflow\n");
            }
            else {
                printf("0b ");
                ConversionEntierBits(num, 32);
            }
        }
        else {
            ConversionReelBin(numReel);
        }
        printf("\n");
    }
    else {
        printf("Option invalide.\n");
    }
}

// Fonction convert
int Convert() {
    char tbEntree[50];
    char option[20];
    float numReel = 0;
    int numEntier = 0;
    int valeur = 1;

    printf("Veuillez entrer une valeur (entiere ou reelle) : ");
    scanf("%s", tbEntree);

    if (strchr(tbEntree, '.')) {
        numReel = atof(tbEntree);
        valeur = 0;
    }
    else {
        numEntier = atoi(tbEntree);
        numReel = numEntier;
    }

    printf("Options de representation :\n");
    printf("1. Aucune\n");
    printf("2. 8 digits\n");
    printf("3. 16 digits\n");
    printf("4. 32 digits\n");
    printf("Choisissez une option : ");
    scanf("%s", option);

    if (strcmp(option, "1") == 0) {
        strcpy(option, "Aucune");
    }
    else if (strcmp(option, "2") == 0) {
        strcpy(option, "8 digits");
    }
    else if (strcmp(option, "3") == 0) {
        strcpy(option, "16 digits");
    }
    else if (strcmp(option, "4") == 0) {
        strcpy(option, "32 digits");
    }

    AffBin(numEntier, numReel, option);

    // enregistrement des log binaire
    log_binaire(tbEntree, 0b011111);

    return 0;
}



/***************************************************************
 *                                                             *
 *                       Trigo								   *
 *                                                             *
 * Description : Cette fonction additionne deux entiers.       *
 *                                                             *
 * Paramètres d'entrée :                                       *
 *   - a : Premier entier                                      *
 *   - b : Deuxième entier                                     *
 *                                                             *
 * Paramètre de sortie :                                       *
 *   Le résultat de l'addition.                                *
 *                                                             *
 ***************************************************************/
 // Fonction pour calculer le côté manquant du triangle rectangle
void calculFaceManquante(Triangle* triangle, int choix)
{
    if (choix == 1)
    {
        // Calculer l'hypoténuse
        triangle->hypotenuse = sqrt(pow(triangle->adjacent, 2) + pow(triangle->oppose, 2));
    }
    else if (choix == 2)
    {
        // Calculer le côté adjacent
        triangle->adjacent = sqrt(pow(triangle->hypotenuse, 2) - pow(triangle->oppose, 2));
    }
    else if (choix == 3)
    {
        // Calculer le côté opposé
        triangle->oppose = sqrt(pow(triangle->hypotenuse, 2) - pow(triangle->adjacent, 2));
    }
}

// Fonction pour calculer l'angle en radians
void calculAngleEnRadians(Triangle* triangle)
{
    triangle->angle.radians = atan(triangle->oppose / triangle->adjacent);
}

// Fonction pour convertir l'angle en radians en degrés
void convertirAngleEnDegre(Triangle* triangle)
{
    if (triangle->estDegre)
    {
        triangle->angle.degre = triangle->angle.radians * (180.0 / M_PI);
    }
}

// Fonction pour calculer les fonctions trigonométriques
void calculTrigFonctions(Triangle* triangle)
{
    triangle->sinus = triangle->oppose / triangle->hypotenuse;
    triangle->cosinus = triangle->adjacent / triangle->hypotenuse;
    triangle->tangente = triangle->oppose / triangle->adjacent;
}

void Trigo (void)
{
        Triangle triangle;
        int choix1, choix2;
        int uniteChoix;

        // Initialiser les variables
        triangle.adjacent = 0;
        triangle.oppose = 0;
        triangle.hypotenuse = 0;
        triangle.angle.radians = 0;
        triangle.angle.degre = 0;
        triangle.estDegre = 0;

        printf("Choisissez deux parametres pour entrer les valeurs :\n");
        printf("1. Cote adjacent\n");
        printf("2. Cote oppose\n");
        printf("3. Hypotenuse\n");
        printf("Entrez votre premier choix (1-3) : ");
        scanf("%d", &choix1);
        printf("Entrez votre deuxieme choix (1-3) : ");
        scanf("%d", &choix2);

        // Entrée des valeurs en fonction des choix
        if ((choix1 == 1 && choix2 == 2) || (choix1 == 2 && choix2 == 1))
        {
            printf("Entrez la valeur du cote adjacent : ");
            scanf("%f", &triangle.adjacent);
            printf("Entrez la valeur du cote oppose : ");
            scanf("%f", &triangle.oppose);
            calculFaceManquante(&triangle, 1); // Calculer l'hypoténuse
        }
        else if ((choix1 == 1 && choix2 == 3) || (choix1 == 3 && choix2 == 1))
        {
            printf("Entrez la valeur du cote adjacent : ");
            scanf("%f", &triangle.adjacent);
            printf("Entrez la valeur de l'hypotenuse : ");
            scanf("%f", &triangle.hypotenuse);
            calculFaceManquante(&triangle, 3); // Calculer le côté opposé
        }
        else if ((choix1 == 2 && choix2 == 3) || (choix1 == 3 && choix2 == 2))
        {
            printf("Entrez la valeur du cote oppose : ");
            scanf("%f", &triangle.oppose);
            printf("Entrez la valeur de l'hypotenuse : ");
            scanf("%f", &triangle.hypotenuse);
            calculFaceManquante(&triangle, 2); // Calculer le côté adjacent
        }
        else 
        {
            printf("Choix non valide.\n");
        }

        // Calcul de l'angle en radians
        calculAngleEnRadians(&triangle);

        // Demander l'unité de l'angle
        printf("Voulez-vous l'angle en degres (1) ou en radians (2) ? ");
        scanf("%d", &uniteChoix);
        if (uniteChoix == 1)
        {
            triangle.estDegre = 1;
            convertirAngleEnDegre(&triangle);
        }

        // Calcul des fonctions trigonométriques
        calculTrigFonctions(&triangle);

        // Afficher les résultats
        printf("\nResultats :\n");
        printf("Cote adjacent : %.2f\n", triangle.adjacent);
        printf("Cote oppose : %.2f\n", triangle.oppose);
        printf("Hypotenuse : %.2f\n", triangle.hypotenuse);
        if (triangle.estDegre)
        {
            printf("Angle : %d degres\n", triangle.angle.degre);
        }
        else
        {
            printf("Angle : %.2f radians\n", triangle.angle.radians);
        }
        printf("Sinus : %.2f\n", triangle.sinus);
        printf("Cosinus : %.2f\n", triangle.cosinus);
        printf("Tangente : %.2f\n", triangle.tangente);

        log_trigonometrie(10, 15, 10, 15, 18, 0.5, 0.8, 1.5, 0.98);
}
//Fonction principale
void main(void)
{
    int fonction = 0;
    printf("Veuillez selectionner un mode : Convert = 1; Trigo = 2 \n");
    scanf("%d", &fonction);

    switch (fonction)
    {
    case 1: Convert();
        break;

    case 2: Trigo();
        break;

    default:
        break;
    }
}
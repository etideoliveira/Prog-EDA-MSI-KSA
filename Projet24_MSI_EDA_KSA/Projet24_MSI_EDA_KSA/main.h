#ifndef MAIN_H
#define MAIN_H

// Définition des constantes
#define AUCUN 0
#define HUIT 8
#define SEIZE 16
#define TRTDEUX 32
#define M_PI 3.14159265358979323846

// Définition de l'union pour stocker l'angle en degrés ou radians
typedef union
{
    float radians;
    int degre;
} Angle;

// Définition de la structure pour stocker les données du triangle
typedef struct
{
    float adjacent;
    float oppose;
    float hypotenuse;
    Angle angle;
    float sinus;
    float cosinus;
    float tangente;
    int estDegre; // Indique si l'angle est en degrés (1) ou en radians (0)
} Triangle;

#endif // MAIN_H
#ifndef MAIN_H
#define MAIN_H

// D�finition des constantes
#define AUCUN 0
#define HUIT 8
#define SEIZE 16
#define TRTDEUX 32
#define M_PI 3.14159265358979323846

// D�finition de l'union pour stocker l'angle en degr�s ou radians
typedef union
{
    float radians;
    int degre;
} Angle;

// D�finition de la structure pour stocker les donn�es du triangle
typedef struct
{
    float adjacent;
    float oppose;
    float hypotenuse;
    Angle angle;
    float sinus;
    float cosinus;
    float tangente;
    int estDegre; // Indique si l'angle est en degr�s (1) ou en radians (0)
} Triangle;

#endif // MAIN_H
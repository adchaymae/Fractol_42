 /*minilibX is a simple API. It is based on the X-Window system, which, in layman’s terms, is the foundation that allows graphical user interfaces (GUIs) to run on UNIX-like operating systems.
 minilibX is a simple API. It is based on the X-Window system, which, in layman’s terms, is the foundation that allows graphical user interfaces (GUIs) to run on UNIX-like operating systems.

1. Création d'une image avec MiniLibX
Avant de pouvoir écrire des pixels, il faut d'abord créer une image où ces pixels seront stockés. Voici comment on fait :*/


#include <mlx.h>

int main(void)
{
    void    *img;
    void    *mlx;

    mlx = mlx_init();  // Initialisation de la connexion avec le serveur graphique
    img = mlx_new_image(mlx, 1920, 1080);  // Création d'une image de 1920x1080 pixels
}
/*Explication :

mlx_init(): Cette fonction initialise la connexion avec le serveur graphique (c'est comme démarrer une session avec le serveur X sur Linux, par exemple).
mlx_new_image(mlx, 1920, 1080): Crée une nouvelle image en mémoire, de taille 1920x1080 pixels.
2. Obtenir l'adresse mémoire de l'image
Maintenant que l'image est créée, il faut accéder à sa mémoire pour y écrire des pixels. C'est ici que les choses deviennent intéressantes. On va récupérer l'adresse mémoire de l'image avec la fonction mlx_get_data_addr().3/


#include <mlx.h>

typedef struct s_data {
    void    *img;
    char    *addr;            // Adresse mémoire de l'image
    int     bits_per_pixel;   // Nombre de bits par pixel
    int     line_length;      // Longueur d'une ligne en mémoire
    int     endian;           // Endianness (ordre des octets)
}              t_data;

int main(void)
{
    void    *mlx;
    t_data  img;

    mlx = mlx_init();
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
}
/*Explication :

img.addr: C'est l'adresse mémoire où les données de l'image sont stockées. C'est là que tu vas écrire les pixels.
img.bits_per_pixel: Indique combien de bits sont utilisés pour représenter un pixel (souvent 32 bits, soit 4 octets).
img.line_length: La longueur d'une ligne de l'image en mémoire (c'est-à-dire combien d'octets représentent une ligne entière).
img.endian: Indique si le système est "little endian" ou "big endian", ce qui affecte l'ordre des octets pour les couleurs.
3. Calculer l'offset mémoire pour un pixel
Pour écrire un pixel à une position spécifique (x, y), tu dois calculer l'offset dans la mémoire. L'offset te dit combien d'octets tu dois sauter depuis le début de l'image pour atteindre ce pixel.


int offset = (y * img.line_length + x * (img.bits_per_pixel / 8));
Explication :

y * img.line_length: Cela te donne le début de la ligne où se trouve ton pixel.
x * (img.bits_per_pixel / 8): Cela te donne combien d'octets tu dois sauter pour atteindre la bonne colonne sur cette ligne.
4. Écrire un pixel à l'adresse mémoire
Maintenant que tu sais où écrire, tu peux placer un pixel à cette adresse. Voici une fonction qui le fait :*/


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
/*Explication :

dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)): dst est le pointeur qui pointe vers l'endroit exact où tu dois écrire le pixel.
*(unsigned int*)dst = color: On écrit la couleur (sous forme d'un entier non signé de 32 bits) à l'adresse mémoire calculée.
5. Afficher l'image dans la fenêtre
Une fois que tous les pixels sont écrits dans l'image, tu dois afficher cette image dans la fenêtre. C'est ce qu'on appelle "pousser l'image dans la fenêtre".*/



#include <mlx.h>

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}              t_data;

int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);  // Mettre un pixel rouge à la position (5, 5)
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);  // Afficher l'image dans la fenêtre

    mlx_loop(mlx);
}
/*Explication :

mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0): Cette fonction affiche l'image dans la fenêtre à la position (0, 0).
mlx_loop(mlx): C'est une boucle infinie qui attend des événements (comme fermer la fenêtre) pour que ton programme ne se termine pas immédiatement.
6. Problème potentiel : tearing
Le fait d'écrire des pixels directement dans l'image affichée peut provoquer un "tearing" (déchirure de l'image), où l'image semble décalée ou divisée lors du rafraîchissement. Pour éviter cela, tu peux utiliser deux images : une pour afficher et une autre pour écrire les pixels, puis échanger les deux images.*/
///////////////////////////////////////////////////////////////////////////
//
// ------------------------------------------------------------------------
//   _____      _            _ _
//  |  _  |    | |          | (_)
//  | |/' | ___| |_ ___   __| |_  ___ ___
//  |  /| |/ __| __/ _ \ / _` | |/ __/ _ \
//  \ |_/ / (__| || (_) | (_| | | (_|  __/
//   \___/ \___|\__\___/ \__,_|_|\___\___|
//
// ------------------------------------------------------------------------
//
//  Projet de synthèse d'image Master 1 Informatique
//  ~ Thomas DUMONT A.K.A 0ctodice
//
// ------------------------------------------------------------------------
//
///////////////////////////////////////////////////////////////////////////

#include <object.h>
/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

Shape *sphere_can;
Shape *torus_can;
Shape *cylinder_can;
Shape *cone_can;
Shape *cube_can;

Node *pilar1;
Node *pilar2;
Node *pilar3;
Node *pilar4;

double mat[4] = {0.5, 0.65, 0.5, 0.5};

Node *gl_toupie()
{
    Node *toupie = init_node();
    Node *sphere = init_node();
    Node *tore = init_node();
    Node *cylindre = init_node();
    Node *cone = init_node();

    set_down(toupie, sphere);
    set_next(sphere, tore);
    set_next(tore, cylindre);
    set_next(cylindre, cone);

    G3Xcolor col = (G3Xcolor){0.8, 0.8, 0.8, 1.};
    G3Xcolor col1 = (G3Xcolor){1., 0.6, 0.7, 1.};

    set_material_and_instance(sphere, col1, mat, sphere_can);
    set_material_and_instance(tore, col1, mat, torus_can);
    set_material_and_instance(cylindre, col, mat, cylinder_can);
    set_material_and_instance(cone, col, mat, cone_can);

    set_Homothetie3d(cylindre, 0.05, 0.05, 1.);
    set_Homothetie3d(sphere, 0.3, 0.3, 0.3);
    set_Homothetie3d(tore, 0.3, 0.3, 0.3);
    set_Homothetie3d(cone, 0.05, 0.05, 0.05);

    set_rotation3dX(cone, PI);

    set_translation3d(sphere, 0., 0., -2.);
    set_translation3d(tore, 0., 0., -2.);
    set_translation3d(cone, 0., 0., 21.);
    set_translation3d(toupie, 0., 0., 1.1);

    return toupie;
}

Node *gl_socle(double x, double y)
{
    Node *socle = init_node();
    Node *cube = init_node();
    Node *tore = init_node();
    Node *cylindre = init_node();
    Node *toupie = gl_toupie();

    set_down(socle, cylindre);
    set_next(cylindre, tore);
    set_next(tore, cube);
    set_next(cube, toupie);

    G3Xcolor col = (G3Xcolor){0.8, 0.8, 0.8, 1.};

    set_material_and_instance(tore, col, mat, torus_can);
    set_material_and_instance(cylindre, col, mat, cylinder_can);
    set_material_and_instance(cube, col, mat, cube_can);

    set_Homothetie3d(cylindre, 0.2, 0.2, 1.);
    set_Homothetie3d(cube, 0.4, 0.4, 0.1);
    set_Homothetie3d(tore, 0.15, 0.15, 0.15);
    set_Homothetie3d(toupie, 0.5, 0.5, 0.5);

    set_rotation3dX(toupie, x);
    set_rotation3dY(toupie, y);

    set_translation3d(cube, 0., 0., -11.);
    set_translation3d(tore, 0., 0., -6.5);
    set_translation3d(toupie, 0., 0., 0.8);
    return socle;
}

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
    sphere_can = load_sphere();
    torus_can = load_torus();
    cylinder_can = load_cylinder();
    cone_can = load_cone();
    cube_can = load_cube();
    pilar1 = gl_socle(0.3, 0.3);
    pilar2 = gl_socle(0.3, -0.3);
    pilar3 = gl_socle(-0.3, 0.3);
    pilar4 = gl_socle(-0.3, -0.3);
    set_next(pilar1, pilar2);
    set_next(pilar2, pilar3);
    set_next(pilar3, pilar4);
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
    draw_node(pilar1);
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void)
{
    free_node(pilar1);
    free_node(pilar2);
    free_node(pilar3);
    free_node(pilar4);
    free_object(sphere_can);
    free_object(torus_can);
    free_object(cylinder_can);
    free_object(cone_can);
    free_object(cube_can);
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS ou presque                    */
/***************************************************************************/
int main(int argc, char **argv)
{
    /* creation de la fenetre - titre et tailles (pixels) */
    g3x_InitWindow(argv[0], WWIDTH, WHEIGHT);

    g3x_SetInitFunction(init); /* fonction d'initialisation */
    g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
    g3x_SetDrawFunction(draw); /* fonction de dessin        */
    g3x_SetAnimFunction(anim); /* fonction d'animation      */
    g3x_SetExitFunction(quit); /* fonction de sortie        */

    /* lancement de la boucle principale */
    return g3x_MainStart();
    /* RIEN APRES CA */
}

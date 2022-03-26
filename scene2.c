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

Node *scene;

double mat[4] = {0.5, 0.65, 0.5, 0.5};

Node *gl_toupie()
{
    Node *toupie = init_node();
    Node *sphere = init_node();
    Node *tore = init_node();
    Node *cylindre = init_node();

    set_down(toupie, sphere);
    set_next(sphere, tore);
    set_next(tore, cylindre);

    G3Xcolor col1 = (G3Xcolor){0.8, 0.8, 0.8, 1.};
    G3Xcolor col2 = (G3Xcolor){1., 0., 0., 1.};
    G3Xcolor col3 = (G3Xcolor){0., 1., 0.2, 1.};

    set_material_and_instance(sphere, col3, mat, sphere_can);
    set_material_and_instance(tore, col3, mat, torus_can);
    set_material_and_instance(cylindre, col2, mat, cylinder_can);

    set_Homothetie3d(cylindre, 0.05, 0.05, 1.);
    set_Homothetie3d(sphere, 0.3, 0.3, 0.3);
    set_Homothetie3d(tore, 0.3, 0.3, 0.3);

    set_translation3d(sphere, 0., 0., -1.5);
    set_translation3d(tore, 0., 0., -1.5);
    set_translation3d(toupie, 0., 0., 1.);

    return toupie;
}

Node *gl_damier()
{
    Node *damier = init_node();
    Node *sq1 = init_node();
    Node *sq2 = init_node();
    Node *sq3 = init_node();
    Node *sq4 = init_node();

    set_down(damier, sq1);
    set_down(sq1, sq2);
    set_next(sq1, sq3);
    set_down(sq3, sq4);

    G3Xcolor col1 = (G3Xcolor){0.8, 0.8, 0.8, 1.};
    G3Xcolor col2 = (G3Xcolor){0.2, 0.2, 0.2, 1.};

    set_material_and_instance(sq1, col1, mat, cube_can);
    set_material_and_instance(sq2, col1, mat, cube_can);
    set_material_and_instance(sq3, col2, mat, cube_can);
    set_material_and_instance(sq4, col2, mat, cube_can);

    set_Homothetie3d(damier, 0.4, 0.4, 0.01);

    set_translation3d(sq1, 1., 1., 0.);
    set_translation3d(sq2, -2., -2., 0.);
    set_translation3d(sq3, 1., -1., 0.);
    set_translation3d(sq4, -2., 2., 0.);

    return damier;
}

Node *gl_ground()
{
    Node *ground = init_node();
    Node *dam1 = gl_damier();
    Node *dam2 = gl_damier();
    Node *dam3 = gl_damier();
    Node *dam4 = gl_damier();
    Node *dam5 = gl_damier();

    set_down(ground, dam1);
    set_next(dam1, dam2);
    set_next(dam2, dam3);
    set_next(dam3, dam4);
    set_next(dam4, dam5);

    set_translation3d(dam1, 8., 0., 0.);
    set_translation3d(dam2, 4., 0., 0.);
    set_translation3d(dam4, -4., 0., 0.);
    set_translation3d(dam5, -8., 0., 0.);

    set_translation3d(ground, 0., 0., -1.44);

    return ground;
}

Node *gl_tower()
{
    Node *tower = init_node();
    Node *cube = init_node();
    Node *tore = init_node();
    Node *cylindre = init_node();
    Node *toupie = gl_toupie();

    set_down(tower, cylindre);
    set_next(cylindre, tore);
    set_next(tore, cube);
    set_next(cube, toupie);

    G3Xcolor col1 = (G3Xcolor){0.8, 0.8, 0.8, 1.};
    G3Xcolor col2 = (G3Xcolor){0., 0.8, 1., 1.};

    set_material_and_instance(tore, col2, mat, torus_can);
    set_material_and_instance(cylindre, col2, mat, cylinder_can);
    set_material_and_instance(cube, col2, mat, cube_can);

    set_Homothetie3d(cylindre, 0.2, 0.2, 1.);
    set_Homothetie3d(cube, 0.4, 0.4, 0.1);
    set_Homothetie3d(tore, 0.175, 0.175, 0.175);
    set_Homothetie3d(toupie, 0.5, 0.5, 0.5);

    set_rotation3dX(toupie, 15 * (PI / 180));
    set_rotation3dY(toupie, 15 * (PI / 180));

    set_translation3d(cube, 0., 0., -11.);
    set_translation3d(tore, 0., 0., -6.);
    set_translation3d(toupie, 0., 0., 0.85);
    set_translation3d(tower, 0., 0., -0.25);
    return tower;
}

Node *gl_towers()
{
    Node *towers = init_node();
    Node *tower1 = gl_tower();
    Node *tower2 = gl_tower();
    Node *tower3 = gl_tower();
    Node *tower4 = gl_tower();

    set_down(towers, tower1);
    set_next(tower1, tower2);
    set_next(tower2, tower3);
    set_next(tower3, tower4);

    set_rotation3dZ(tower2, 90 * (PI / 180));
    set_rotation3dZ(tower3, 180 * (PI / 180));
    set_rotation3dZ(tower4, 270 * (PI / 180));

    set_translation3d(tower1, 0.4, 1.2, 0.);
    set_translation3d(tower2, 1.2, 0.4, 0.);
    set_translation3d(tower3, 0.4, 1.2, 0.);
    set_translation3d(tower4, 1.2, 0.4, 0.);

    return towers;
}

Node *gl_scene()
{
    Node *scene = init_node();
    Node *ground = gl_ground();
    Node *towers1 = gl_towers();
    Node *towers2 = gl_towers();
    Node *towers3 = gl_towers();
    Node *towers4 = gl_towers();
    Node *towers5 = gl_towers();

    set_down(scene, ground);
    set_next(ground, towers1);
    set_next(towers1, towers2);
    set_next(towers2, towers3);
    set_next(towers3, towers4);
    set_next(towers4, towers5);

    set_translation3d(towers1, 3.2, 0., 0.);
    set_translation3d(towers3, 1.6, 0., 0.);
    set_translation3d(towers4, -1.6, 0., 0.);
    set_translation3d(towers5, -3.2, 0., 0.);

    return scene;
}

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
    sphere_can = load_sphere();
    torus_can = load_torus();
    cylinder_can = load_cylinder();
    cone_can = load_cone();
    cube_can = load_cube();

    scene = gl_scene();
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
    draw_node(scene);
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void)
{
    free_node(scene);
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

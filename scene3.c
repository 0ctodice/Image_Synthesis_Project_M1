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

Node *gl_brain_part()
{
    Node *brain_part = init_node();
    Node *sphere = init_node();
    Node *tore = init_node();

    set_down(brain_part, sphere);
    set_next(sphere, tore);

    G3Xcolor col1 = (G3Xcolor){255. / 255., 102. / 255., 102. / 255., 1.};

    set_material_and_instance(sphere, col1, mat, sphere_can);
    set_material_and_instance(tore, col1, mat, torus_can);

    set_Homothetie3d(sphere, 0.3, 0.3, 0.3);
    set_Homothetie3d(tore, 0.3, 0.3, 0.3);

    set_rotation3dX(brain_part, 15 * (PI / 180));
    set_rotation3dY(brain_part, 15 * (PI / 180));

    set_translation3d(sphere, 0., 0., 1.);
    set_translation3d(tore, 0., 0., 1.);

    return brain_part;
}

Node *gl_brain()
{
    Node *brain = init_node();
    Node *brain_part1 = init_node();
    Node *brain_part2 = init_node();
    Node *brain_part3 = init_node();
    Node *brain_part4 = init_node();
    Node *spike = init_node();
    Node *plateau = init_node();

    set_down(brain, brain_part1);
    set_next(brain_part1, brain_part2);
    set_down(brain_part1, gl_brain_part());
    set_next(brain_part2, brain_part3);
    set_down(brain_part2, gl_brain_part());
    set_next(brain_part3, brain_part4);
    set_down(brain_part3, gl_brain_part());
    set_next(brain_part4, spike);
    set_down(brain_part4, gl_brain_part());
    set_next(spike, plateau);

    G3Xcolor col1 = (G3Xcolor){1., 215. / 255., 0., 1.};

    set_material_and_instance(spike, col1, mat, cylinder_can);
    set_material_and_instance(plateau, col1, mat, cylinder_can);

    set_Homothetie3d(spike, 0.05, 0.05, 0.3);
    set_Homothetie3d(plateau, 0.5, 0.5, 0.05);

    set_rotation3dZ(brain_part2, 90 * (PI / 180));
    set_rotation3dZ(brain_part3, 180 * (PI / 180));
    set_rotation3dZ(brain_part4, 270 * (PI / 180));

    set_translation3d(spike, 0., 0., -1.);
    set_translation3d(plateau, 0., 0., -13.);

    return brain;
}

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
    sphere_can = load_sphere();
    torus_can = load_torus();
    cylinder_can = load_cylinder();
    cone_can = load_cone();
    cube_can = load_cube();

    scene = gl_brain();
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
    set_rotation3dZ(scene, 0.005);
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

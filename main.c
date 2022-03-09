#include <object.h>
/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

Shape *sphere_can;
Shape *torus_can;
Shape *cylinder_can;
Shape *cone_can;
Shape *cube_can;

static double alpha = 1.;
static double ambi = 0.25;
static double diff = 0.5;
static double spec = 0.5;
static double shine = 0.5;

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
  sphere_can = load_sphere();
  torus_can = load_torus();
  cylinder_can = load_cylinder();
  cone_can = load_cone();
  cube_can = load_cube();
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
  g3x_Material((G3Xcolor){1., 0., 0., 1.}, ambi, diff, spec, shine, alpha);
  // sphere_can->draw_quads(sphere_can);
  // torus_can->draw_quads(torus_can);
  // cylinder_can->draw_quads(cylinder_can);
  // cone_can->draw_quads(cone_can);
  cube_can->draw_quads(cube_can);
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
  free(sphere_can);
  free(torus_can);
  free(cylinder_can);
  free(cone_can);
  free(cone_can);
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void)
{
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS ou presque                    */
/***************************************************************************/
int main(int argc, char **argv)
{
  /* creation de la fenetre - titre et tailles (pixels) */
  g3x_InitWindow(*argv, WWIDTH, WHEIGHT);

  g3x_SetInitFunction(init); /* fonction d'initialisation */
  g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
  g3x_SetDrawFunction(draw); /* fonction de dessin        */
  g3x_SetAnimFunction(anim); /* fonction d'animation      */
  g3x_SetExitFunction(quit); /* fonction de sortie        */

  /* lancement de la boucle principale */
  return g3x_MainStart();
  /* RIEN APRES CA */
}

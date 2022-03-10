#include <object.h>
/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

Shape *sphere_can;
Shape *torus_can;
Shape *cylinder_can;
Shape *cone_can;
Shape *cube_can;

SceneTree tree;

double scale = 0.5;

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
  sphere_can = load_sphere();
  torus_can = load_torus();
  cylinder_can = load_cylinder();
  cone_can = load_cone();
  cube_can = load_cube();

  tree = malloc(sizeof(SceneTree));
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
  tree->col = (G3Xcolor){1., 0.3, 0., 1.};
  tree->mat[0] = 0.25;
  tree->mat[1] = 0.5;
  tree->mat[2] = 0.5;
  tree->mat[3] = 0.5;
  tree->instance = torus_can;

  g3x_SetScrollWidth(10);

  int id;

  id = g3x_CreateScrollv_d("ray", &scale, 0.01, 01., 1., "scale factor");
  g3x_SetScrollColor(id, G3Xrb_c);
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
  // draw_tree(tree);
  g3x_Material((G3Xcolor){0., 1., 0., 1.}, 0.25, 0.5, 0.5, 0.5, 1.);
  cone_can->draw_quads(cone_can, (G3Xvector){scale, scale, scale});
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
  free(tree);
  free(sphere_can);
  free(torus_can);
  free(cylinder_can);
  free(cone_can);
  free(cube_can);
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
  g3x_InitWindow("Image Synthesis", WWIDTH, WHEIGHT);

  g3x_SetInitFunction(init); /* fonction d'initialisation */
  g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
  g3x_SetDrawFunction(draw); /* fonction de dessin        */
  g3x_SetAnimFunction(anim); /* fonction d'animation      */
  g3x_SetExitFunction(quit); /* fonction de sortie        */

  /* lancement de la boucle principale */
  return g3x_MainStart();
  /* RIEN APRES CA */
}

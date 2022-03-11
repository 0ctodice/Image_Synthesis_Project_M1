#include <object.h>
/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

Shape *sphere_can;
Shape *torus_can;
Shape *cylinder_can;
Shape *cone_can;
Shape *cube_can;

Node *node;

double scale = 0.5;

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
  sphere_can = load_sphere();
  torus_can = load_torus();
  cylinder_can = load_cylinder();
  cone_can = load_cone();
  cube_can = load_cube();
  node = init_node();
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
  node->col = (G3Xcolor){202. / 255., 110. / 255., 20. / 255., 1.};
  node->mat[0] = 0.25;
  node->mat[1] = 0.5;
  node->mat[2] = 0.5;
  node->mat[3] = 0.5;
  node->instance = torus_can;
  *(node->Md) = g3x_Homothetie3d(1., 0.5, 0.5);

  g3x_SetScrollWidth(11);

  int id;
  id = g3x_CreateScrollv_d("step", &scale, 0.01, 0.5, 1., "scale factor");
  g3x_SetScrollColor(id, G3Xrb_c);
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
  node->scale_factor = (G3Xvector){scale, scale, scale};
  draw_node(node);
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
  free_node(node);
  free_object(sphere_can);
  free_object(torus_can);
  free_object(cylinder_can);
  free_object(cone_can);
  free_object(cube_can);
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

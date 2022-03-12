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

Node *table;

double init_scale = 1.;

Node *gl_pied(double x, double y, double z, Node *initNode)
{
  Node *pied = init_node();

  pied->col = (G3Xcolor){0.30, 0.20, 0.10, 1.};
  pied->mat[0] = 0.5, pied->mat[1] = 0.75, pied->mat[2] = pied->mat[3] = 0.;
  pied->instance = cylinder_can;

  *(pied->Md) = g3x_Mat_x_Mat(*(initNode->Md), g3x_Homothetie3d(0.12, 0.12, 0.99));
  *(pied->Md) = g3x_Mat_x_Mat(*(pied->Md), g3x_Translation3d(x, y, z));
  *(pied->scale_factor) = g3x_Mat_x_Vector(*(pied->Md), *(initNode->scale_factor));

  return pied;
}

Node *gl_table()
{
  // Noeud Principal
  Node *table = init_node();
  *(table->Md) = g3x_Mat_x_Mat(*(table->Md), g3x_Homothetie3d(0.75, 0.75, 0.75));
  *(table->scale_factor) = g3x_Mat_x_Vector(*(table->Md), (G3Xvector){init_scale, init_scale, init_scale});

  // Plateau
  Node *plateau = init_node();
  plateau->col = (G3Xcolor){0.50, 0.40, 0.20, 1.};
  plateau->mat[0] = 0.5, plateau->mat[1] = 0.65, plateau->mat[2] = plateau->mat[3] = 0.5;
  plateau->instance = cube_can;
  plateau->scale_factor = table->scale_factor;
  *(plateau->Md) = *(table->Md);
  *(plateau->Md) = g3x_Mat_x_Mat(*(plateau->Md), g3x_Homothetie3d(1.8, 1., 0.1));
  *(plateau->Md) = g3x_Mat_x_Mat(*(plateau->Md), g3x_Translation3d(0., 0., 9.));
  *(plateau->scale_factor) = g3x_Mat_x_Vector(*(plateau->Md), *(plateau->scale_factor));

  // Pieds
  Node *pied1 = gl_pied(+12.5, +5.5, -0.19, table);
  Node *pied2 = gl_pied(+12.5, -5.5, -0.19, table);
  Node *pied3 = gl_pied(-12.5, -5.5, -0.19, table);
  Node *pied4 = gl_pied(-12.5, +5.5, -0.19, table);

  table->down = plateau;
  plateau->next = pied1;
  pied1->next = pied2;
  pied2->next = pied3;
  pied3->next = pied4;

  return table;
}

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
  sphere_can = load_sphere();
  torus_can = load_torus();
  cylinder_can = load_cylinder();
  cone_can = load_cone();
  cube_can = load_cube();
  table = gl_table();
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
  draw_node(table);
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
  free_node(table);
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

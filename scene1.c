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
Node *table2;
Node *tabouret;
Node *tabouret2;
Node *ground;

Node *gl_ground()
{
  Node *ground = init_node();
  Node *sq1 = init_node();
  Node *sq2 = init_node();
  Node *sq3 = init_node();
  Node *sq4 = init_node();

  scaled_Homothetie3d(ground, 1., 1., 0.05);

  set_down_or_next(ground, sq1, true);
  set_down_or_next(sq1, sq3, false);

  sq1->col = (G3Xcolor){0.8, 0.8, 0.8, 1.};
  sq1->mat[0] = 0.5, sq1->mat[1] = 0.65, sq1->mat[2] = sq1->mat[3] = 0.5;

  set_down_or_next(sq1, sq2, true);

  sq3->col = (G3Xcolor){0.2, 0.2, 0.2, 1.};
  sq3->mat[0] = 0.5, sq3->mat[1] = 0.65, sq3->mat[2] = sq3->mat[3] = 0.5;

  set_down_or_next(sq3, sq4, true);

  sq1->instance = sq2->instance = sq3->instance = sq4->instance = cube_can;

  *(sq1->Md) = g3x_Mat_x_Mat(*(ground->Md), g3x_Translation3d(1., 1., 0.));
  *(sq2->Md) = g3x_Mat_x_Mat(*(ground->Md), g3x_Translation3d(-2., -2., 0.));

  *(sq3->Md) = g3x_Mat_x_Mat(*(ground->Md), g3x_Translation3d(1., -1., 0.));
  *(sq4->Md) = g3x_Mat_x_Mat(*(ground->Md), g3x_Translation3d(-2., 2., 0.));

  return ground;
}

void gl_pied(Node *node, double x, double y, double z)
{
  Node *pied1 = init_node();
  Node *pied2 = init_node();
  Node *pied3 = init_node();
  Node *pied4 = init_node();

  node->col = (G3Xcolor){0.30, 0.30, 0.30, 1.};
  node->mat[0] = 0.5, node->mat[1] = 0.75, node->mat[2] = node->mat[3] = 0.;
  scaled_Homothetie3d(node, 0.3, 0.3, 0.8);

  set_down_or_next(node, pied1, true);
  set_down_or_next(pied1, pied2, false);
  set_down_or_next(pied2, pied3, false);
  set_down_or_next(pied3, pied4, false);

  *(pied1->Md) = g3x_Mat_x_Mat(*(pied1->Md), g3x_Translation3d(x, y, z));
  *(pied2->Md) = g3x_Mat_x_Mat(*(pied2->Md), g3x_Translation3d(x, -y, z));
  *(pied3->Md) = g3x_Mat_x_Mat(*(pied3->Md), g3x_Translation3d(-x, -y, z));
  *(pied4->Md) = g3x_Mat_x_Mat(*(pied4->Md), g3x_Translation3d(-x, y, z));

  pied1->instance = pied2->instance = pied3->instance = pied4->instance = cylinder_can;
}

Node *gl_table()
{
  // Noeud Principal
  Node *table = init_node();

  // Plateau
  Node *plateau = init_node();
  Node *pieds = init_node();

  set_down_or_next(table, plateau, true);
  set_down_or_next(plateau, pieds, false);

  plateau->col = (G3Xcolor){0.50, 0.40, 0.20, 1.};
  plateau->mat[0] = 0.5, plateau->mat[1] = 0.65, plateau->mat[2] = plateau->mat[3] = 0.5;
  plateau->instance = cube_can;

  scaled_Homothetie3d(plateau, 1., 0.7, 0.1);
  *(plateau->Md) = g3x_Mat_x_Mat(*(plateau->Md), g3x_Translation3d(0., 0., 1.));

  // Pieds
  gl_pied(pieds, 9., 5.5, -1.);

  return table;
}

Node *gl_tabouret()
{
  Node *tabouret = init_node();

  Node *plateau = init_node();
  Node *pieds = init_node();

  set_down_or_next(tabouret, plateau, true);
  set_down_or_next(plateau, pieds, false);

  plateau->col = (G3Xcolor){0.50, 0.40, 0.20, 1.};
  plateau->mat[0] = 0.5, plateau->mat[1] = 0.65, plateau->mat[2] = plateau->mat[3] = 0.5;
  plateau->instance = cylinder_can;

  scaled_Homothetie3d(plateau, 0.4, 0.4, 0.05);
  *(plateau->Md) = g3x_Mat_x_Mat(*(plateau->Md), g3x_Translation3d(0., 0., 1.));

  scaled_Homothetie3d(pieds, 0.75, 0.75, 0.9);

  gl_pied(pieds, 2.5, 2.5, -1.);

  return tabouret;
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
  table2 = gl_table();
  tabouret = gl_tabouret();
  tabouret2 = gl_tabouret();
  ground = gl_ground();

  scaled_Homothetie3d(table, 0.75, 0.75, 0.75);
  scaled_Homothetie3d(table2, 0.75, 0.75, 0.75);
  scaled_Homothetie3d(tabouret, 0.75, 0.75, 0.6);
  scaled_Homothetie3d(tabouret2, 0.75, 0.75, 0.6);

  *(table2->Md) = g3x_Mat_x_Mat(*(table2->Md), g3x_RotationZ(-0.5));
  *(table->Md) = g3x_Mat_x_Mat(*(table->Md), g3x_RotationZ(0.785398));
  *(tabouret2->Md) = g3x_Mat_x_Mat(*(tabouret2->Md), g3x_RotationZ(-0.5));
  *(tabouret2->Md) = g3x_Mat_x_Mat(*(tabouret2->Md), g3x_RotationX(1.5708));
  *(tabouret2->Md) = g3x_Mat_x_Mat(*(tabouret2->Md), g3x_RotationX(1.5708));

  *(table->Md) = g3x_Mat_x_Mat(*(table->Md), g3x_Translation3d(0., -2., 1.29));
  *(table2->Md) = g3x_Mat_x_Mat(*(table2->Md), g3x_Translation3d(0.6, 1.9, 1.29));
  *(tabouret->Md) = g3x_Mat_x_Mat(*(tabouret->Md), g3x_Translation3d(-1., -1., 1.04));
  *(tabouret2->Md) = g3x_Mat_x_Mat(*(tabouret2->Md), g3x_Translation3d(0.5, -2., -1.978));
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
  draw_node(ground);
  draw_node(table);
  draw_node(table2);
  draw_node(tabouret);
  draw_node(tabouret2);
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
  free_node(tabouret);
  free_node(tabouret2);
  free_node(table);
  free_node(table2);
  free_node(ground);
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

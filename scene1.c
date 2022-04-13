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

double mat[4] = {0.5, 0.65, 0.5, 0.5};

Node *gl_ground()
{
  Node *ground = init_node();
  Node *sq1 = init_node();
  Node *sq2 = init_node();
  Node *sq3 = init_node();
  Node *sq4 = init_node();

  set_down(ground, sq1);
  set_down(sq1, sq2);
  set_next(sq1, sq3);
  set_down(sq3, sq4);

  G3Xcolor col1 = (G3Xcolor){0.8, 0.8, 0.8, 1.};
  G3Xcolor col2 = (G3Xcolor){0.2, 0.2, 0.2, 1.};

  set_material_and_instance(sq1, col1, mat, cube_can);
  set_material_and_instance(sq2, col1, mat, cube_can);
  set_material_and_instance(sq3, col2, mat, cube_can);
  set_material_and_instance(sq4, col2, mat, cube_can);

  set_Homothetie3d(ground, 1., 1., 0.01);

  set_translation3d(sq1, 1., 1., 0.);
  set_translation3d(sq2, -2., -2., 0.);
  set_translation3d(sq3, 1., -1., 0.);
  set_translation3d(sq4, -2., 2., 0.);

  return ground;
}

Node *gl_pied(double x, double y, double z)
{

  Node *pieds = init_node();
  Node *pied1 = init_node();
  Node *pied2 = init_node();
  Node *pied3 = init_node();
  Node *pied4 = init_node();

  set_down(pieds, pied1);
  set_next(pied1, pied2);
  set_next(pied2, pied3);
  set_next(pied3, pied4);

  G3Xcolor col = (G3Xcolor){0.80, 0.80, 0.80, 1.};

  set_material_and_instance(pied1, col, mat, cylinder_can);
  set_material_and_instance(pied2, col, mat, cylinder_can);
  set_material_and_instance(pied3, col, mat, cylinder_can);
  set_material_and_instance(pied4, col, mat, cylinder_can);

  set_Homothetie3d(pieds, 0.09, 0.09, 0.7);

  set_translation3d(pied1, x, y, z);
  set_translation3d(pied2, x, -y, z);
  set_translation3d(pied3, -x, -y, z);
  set_translation3d(pied4, -x, y, z);

  return pieds;
}

Node *gl_table()
{
  Node *table = init_node();
  Node *plateau = init_node();
  Node *pieds = pieds = gl_pied(9., 5.5, -1.);

  set_down(table, plateau);
  set_next(plateau, pieds);

  set_material_and_instance(plateau, (G3Xcolor){0.50, 0.40, 0.20, 1.}, mat, cube_can);

  set_Homothetie3d(plateau, 1., 0.7, 0.1);
  set_translation3d(plateau, 0., 0., 1.);

  return table;
}

Node *gl_tabouret()
{
  Node *tabouret = init_node();

  Node *plateau = init_node();
  Node *pieds = gl_pied(2.5, 2.5, -1.);

  set_down(tabouret, plateau);
  set_next(plateau, pieds);

  set_material_and_instance(plateau, (G3Xcolor){0.50, 0.40, 0.20, 1.}, mat, cylinder_can);

  set_Homothetie3d(plateau, 0.4, 0.4, 0.05);
  set_Homothetie3d(pieds, 0.75, 0.75, 0.9);
  set_translation3d(plateau, 0., 0., 1.);

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

  set_Homothetie3d(table, 0.75, 0.75, 0.75);
  set_Homothetie3d(table2, 0.75, 0.75, 0.75);
  set_Homothetie3d(tabouret, 0.75, 0.75, 0.6);
  set_Homothetie3d(tabouret2, 0.75, 0.75, 0.6);

  set_rotation3dZ(table2, -0.5);
  set_rotation3dZ(tabouret2, -0.5);
  set_rotation3dZ(table, 0.785398);
  set_rotation3dX(tabouret2, 3.1416);

  set_translation3d(table, 0., -2., 1.42);
  set_translation3d(table2, 0.6, 1.9, 1.42);
  set_translation3d(tabouret, -1., -1., 1.3);
  set_translation3d(tabouret2, 0.5, -2., -2.13);
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

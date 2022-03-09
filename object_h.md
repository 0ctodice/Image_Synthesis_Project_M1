### Object.h in my include directory

```c
#include <g3x.h>

#define MAXRES 100

typedef struct _shape_
{
    int id;
    size_t n1, n2, n3;
    G3Xpoint *vrtx;
    G3Xvector *norm;
    void (*draw_points)(struct _shape_ *); /*Affichage par point*/
    void (*draw_quads)(struct _shape_ *);  /*affichage par facette*/
} Shape;

typedef struct _node_
{
    struct _node_ *down, *next; /*chaînage*/
    G3Xhmat Md;                 /*matrice de transformation directe*/
    G3Xcolor col;               /*couleur RGBA*/
    // g3x_Material mat;           /*4 réels dans [0, 1] : (ambi, diff, spec, shine)*/
    G3Xvector scale_factor; /*facteur d'échelles locaux x, y, z*/
    Shape *instance;        /*une éventuelle instance d'objet*/
} Node, *SceneTree;

void normVrtx3dv(G3Xvector *N, G3Xpoint *P, int i);
void free_object(Shape *obj);

void draw_sphere_points(Shape *obj);
void draw_sphere_quads(Shape *obj);
Shape *init_sphere();
Shape *load_sphere();

void draw_torus_points(Shape *obj);
void draw_torus_quads(Shape *obj);
Shape *init_torus();
Shape *load_torus();

void draw_cylinder_points(Shape *obj);
void draw_cylinder_quads(Shape *obj);
Shape *init_cylinder();
Shape *load_cylinder();

void draw_cone_points(Shape *obj);
void draw_cone_quads(Shape *obj);
Shape *init_cone();
Shape *load_cone();

void draw_cube_points(Shape *obj);
void draw_cube_quads(Shape *obj);
Shape *init_cube();
Shape *load_cube();
```
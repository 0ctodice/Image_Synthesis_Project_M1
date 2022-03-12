### Object.h in my include directory

```c
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

#include <g3x.h>

#define MAXRES 100

typedef struct _shape_
{
    size_t n1, n2, n3;
    G3Xpoint *vrtx;
    G3Xvector *norm;
    void (*draw_points)(struct _shape_ *, G3Xvector scale_factor); /*Affichage par point*/
    void (*draw_quads)(struct _shape_ *, G3Xvector scale_factor);  /*affichage par facette*/
} Shape;

typedef struct _node_
{
    struct _node_ *down, *next; /*chaînage*/
    G3Xhmat *Md;                /*matrice de transformation directe*/
    G3Xcolor col;               /*couleur RGBA*/
    double mat[4];              /*4 réels dans [0, 1] : (ambi, diff, spec, shine)*/
    G3Xvector *scale_factor;    /*facteur d'échelles locaux x, y, z*/
    Shape *instance;            /*une éventuelle instance d'objet*/
} Node;

void normVrtx3dv(G3Xvector *N, G3Xpoint *P, int i);
void free_object(Shape *obj);

Node *init_node();
void draw_node(Node *node);
void free_node(Node *node);

void draw_sphere_points(Shape *obj, G3Xvector scale_factor);
void draw_sphere_quads(Shape *obj, G3Xvector scale_factor);
Shape *init_sphere();
Shape *load_sphere();

void draw_torus_points(Shape *obj, G3Xvector scale_factor);
void draw_torus_quads(Shape *obj, G3Xvector scale_factor);
Shape *init_torus();
Shape *load_torus();

void draw_cylinder_points(Shape *obj, G3Xvector scale_factor);
void draw_cylinder_quads(Shape *obj, G3Xvector scale_factor);
Shape *init_cylinder();
Shape *load_cylinder();

void draw_cone_points(Shape *obj, G3Xvector scale_factor);
void draw_cone_quads(Shape *obj, G3Xvector scale_factor);
Shape *init_cone();
Shape *load_cone();

void draw_cube_points(Shape *obj, G3Xvector scale_factor);
void draw_cube_quads(Shape *obj, G3Xvector scale_factor);
Shape *init_cube();
Shape *load_cube();
```
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
    void (*draw_points)(struct _shape_ *, G3Xvector scale_factor, double dcam);
    void (*draw_quads)(struct _shape_ *, G3Xvector scale_factor, double dcam);
} Shape;

typedef struct _node_
{
    struct _node_ *down, *next;
    G3Xhmat *Md;
    G3Xcolor col;
    double mat[4];
    G3Xvector *scale_factor;
    Shape *instance;
} Node;

void normVrtx3dv(G3Xvector *N, G3Xpoint *P, int i);
void free_object(Shape *obj);

Node *init_node();
void set_down(Node *node, Node *down);
void set_next(Node *node, Node *down);
void set_Homothetie3d(Node *node, double x, double y, double z);
void set_translation3d(Node *node, double x, double y, double z);
void set_rotation3dX(Node *node, double angle_x);
void set_rotation3dY(Node *node, double angle_y);
void set_rotation3dZ(Node *node, double angle_z);
void update_scale_factor(Node *node, G3Xvector daddy_scale_factor);
double compute_cam_node_distance(G3Xhmat Md);

void set_material_and_instance(Node *node, G3Xcolor col, double mat[], Shape *shape);
void draw_node(Node *node);
void free_node(Node *node);

void draw_sphere_points(Shape *obj, G3Xvector scale_factor, double dcam);
void draw_sphere_quads(Shape *obj, G3Xvector scale_factor, double dcam);
Shape *init_sphere();
Shape *load_sphere();

void draw_torus_points(Shape *obj, G3Xvector scale_factor, double dcam);
void draw_torus_quads(Shape *obj, G3Xvector scale_factor, double dcam);
Shape *init_torus();
Shape *load_torus();

void draw_cylinder_points(Shape *obj, G3Xvector scale_factor, double dcam);
void draw_cylinder_quads(Shape *obj, G3Xvector scale_factor, double dcam);
Shape *init_cylinder();
Shape *load_cylinder();

void draw_cone_points(Shape *obj, G3Xvector scale_factor, double dcam);
void draw_cone_quads(Shape *obj, G3Xvector scale_factor, double dcam);
Shape *init_cone();
Shape *load_cone();

void draw_cube_points(Shape *obj, G3Xvector scale_factor, double dcam);
void draw_cube_quads(Shape *obj, G3Xvector scale_factor, double dcam);
Shape *init_cube();
Shape *load_cube();
```
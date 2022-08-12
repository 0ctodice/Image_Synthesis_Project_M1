#include <object.h>

void normVrtx3dv(G3Xvector *N, G3Xpoint *P, int i)
{
    g3x_Normal3dv(N[i]);
    g3x_Vertex3dv(P[i]);
}

void free_object(Shape *obj)
{
    free(obj->vrtx);
    free(obj->norm);
    free(obj);
}

Node *init_node()
{
    Node *node;

    if (NULL == (node = malloc(sizeof(Node))))
        return NULL;

    node->down = NULL;
    node->next = NULL;
    node->instance = NULL;

    if (NULL == (node->Md = malloc(sizeof(G3Xhmat))))
        return NULL;

    if (NULL == (node->scale_factor = malloc(sizeof(G3Xvector))))
        return NULL;

    *(node->Md) = g3x_Identity();
    *(node->scale_factor) = g3x_Mat_x_Vector(*(node->Md), (G3Xvector){1., 1., 1.});

    return node;
}

void set_material_and_instance(Node *node, G3Xcolor col, double mat[], Shape *shape)
{
    node->col = col;
    node->mat[0] = mat[0];
    node->mat[1] = mat[1];
    node->mat[2] = mat[2];
    node->mat[3] = mat[3];

    node->instance = shape;
}

void set_down(Node *node1, Node *node2) { node1->down = node2; }

void set_next(Node *node1, Node *node2) { node1->next = node2; }

void set_Homothetie3d(Node *node, double x, double y, double z)
{
    *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_Homothetie3d(x, y, z));
    update_scale_factor(node, *(node->scale_factor));
}

void set_translation3d(Node *node, double x, double y, double z) { *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_Translation3d(x, y, z)); }

void set_rotation3dX(Node *node, double angle_x) { *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_RotationX(angle_x)); }

void set_rotation3dY(Node *node, double angle_y) { *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_RotationY(angle_y)); }

void set_rotation3dZ(Node *node, double angle_z) { *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_RotationZ(angle_z)); }

void update_scale_factor(Node *node, G3Xvector daddy_scale_factor)
{
    *(node->scale_factor) = g3x_Mat_x_Vector(*(node->Md), daddy_scale_factor);
    if (node->down != NULL)
    {
        update_scale_factor(node->down, *(node->scale_factor));
    }
    if (node->next != NULL)
    {
        update_scale_factor(node->next, daddy_scale_factor);
    }
}

double compute_cam_node_distance(G3Xhmat Md)
{
    G3Xpoint node_pos = (G3Xpoint){Md.m[12], Md.m[13], Md.m[14]};
    G3Xpoint cam_pos = *(g3x_GetCamera()->pos);

    return 1. / (sqrt(pow((node_pos.x - cam_pos.x), 2.) + pow((node_pos.y - cam_pos.y), 2.) + pow((node_pos.z - cam_pos.z), 2.)) / 5.);
}

void free_node(Node *node)
{
    if (node->instance)
        free_object(node->instance);
    if (node->down)
        free_node(node->down);
    if (node->next)
        free_node(node->next);
    free(node->Md);
    free(node->scale_factor);
    free(node);
}

void draw_node(Node *node)
{
    g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 1.);
    glPushMatrix();
    glMultMatrixd(node->Md->m);
    if (node->instance != NULL)
        node->instance->draw_quads(node->instance, *(node->scale_factor), compute_cam_node_distance(*(node->Md)));
    if (node->down != NULL)
    {
        draw_node(node->down);
    }
    glPopMatrix();
    if (node->next != NULL)
    {
        draw_node(node->next);
    }
}
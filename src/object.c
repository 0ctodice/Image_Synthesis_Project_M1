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

void draw_tree(SceneTree tree)
{
    // Node *node = tree;
    // while (node != NULL)
    // {
    //     glPushMatrix();
    //     g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 1.);
    //     // glMultMatrixd(node->Md.m);
    //     if (node->instance != NULL)
    //         node->instance->draw_quads(node->instance);
    //     if (node->down != NULL)
    //         draw_tree(node->down);
    //     glPopMatrix();
    //     node = node->next;
    // }
}
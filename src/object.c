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

    if (NULL == (node->down = malloc(sizeof(Node))))
        return NULL;

    if (NULL == (node->next = malloc(sizeof(Node))))
        return NULL;

    if (NULL == (node->Md = malloc(sizeof(G3Xhmat))))
        return NULL;

    return node;
}

void free_node(Node *node)
{
    free(node->down);
    free(node->next);
    free(node->Md);
    free(node);
}

void draw_node(Node *node)
{
    while (node != NULL)
    {
        glPushMatrix();
        g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 1.);
        glMultMatrixd(node->Md->m);
        if (node->instance != NULL)
            node->instance->draw_quads(node->instance, node->scale_factor);
        if (node->down != NULL)
            draw_node(node->down);
        glPopMatrix();
        node = node->next;
    }
}
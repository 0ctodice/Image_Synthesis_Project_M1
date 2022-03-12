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

    if (NULL == (node->scale_factor = malloc(sizeof(G3Xvector))))
        return NULL;

    *(node->Md) = g3x_Identity();

    return node;
}

void free_node(Node *node)
{
    if (node->instance)
        free_object(node->instance);
    if (node->down)
        free_node(node->down);
    if (node->next)
        free_node(node->next);
    free(node);
}

void draw_node(Node *node)
{
    while (node)
    {
        glPushMatrix();
        g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 1.);
        glMultMatrixd(node->Md->m);
        if (node->instance)
            node->instance->draw_quads(node->instance, *(node->scale_factor));
        if (node->down)
            draw_node(node->down);
        glPopMatrix();
        node = node->next;
    }
}
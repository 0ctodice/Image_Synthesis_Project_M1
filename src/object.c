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
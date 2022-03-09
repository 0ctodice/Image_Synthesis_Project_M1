#include <object.h>
#include <math.h>

void draw_cone_points(Shape *obj)
{
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)((obj->n1 * obj->n3) + (obj->n1 * obj->n2)); i++)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i);
    }
    glEnd();
}

void draw_cone_quads(Shape *obj)
{
    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;
    int Nn = obj->n3;

    glPointSize(1);
    glBegin(GL_QUADS);

    for (i = 0; i < Nn - 1; i++)
    {

        for (j = 0; j < Nm - 1; j++)
        {
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j);
        }

        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j);
    }

    int start = Nm * Nn;

    for (i = 0; i < Np - 1; i++)
    {

        for (j = 0; j < Nm - 1; j++)
        {
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + start);
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + 1 + start);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j + 1 + start);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j + start);
        }

        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + start);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + start);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + start);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j + start);
    }

    glEnd();
}

Shape *init_cone()
{
    Shape *obj;

    if (NULL == (obj = malloc(sizeof(Shape))))
    {
        return NULL;
    }

    obj->n1 = MAXRES * PI;
    obj->n2 = (obj->n1) / 2.;
    obj->n3 = MAXRES;

    if (NULL == (obj->vrtx = calloc((obj->n1 * obj->n3) + (obj->n1 * obj->n2), sizeof(G3Xpoint))))
        return NULL;

    if (NULL == (obj->norm = calloc((obj->n1 * obj->n3) + (obj->n1 * obj->n2), sizeof(G3Xvector))))
        return NULL;

    obj->draw_points = draw_cone_points;
    obj->draw_quads = draw_cone_quads;

    return obj;
}

Shape *load_cone()
{
    Shape *obj;

    if (NULL == (obj = init_cone()))
        return NULL;

    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;
    int Nn = obj->n3;

    double teta = (2. * PI) / (double)Nm;
    double phi = PI / (double)Np;

    for (i = 0; i < Nn; i++)
    {
        double r = (double)i / (double)(Nn - 1);

        for (j = 0; j < Nm; j++)
        {
            double x = r * cos((double)j * teta);
            double y = r * sin((double)j * teta);

            obj->vrtx[(i * Nm) + j] = (G3Xpoint){x, y, -1};
            obj->norm[(i * Nm) + j] = (G3Xvector){0, 0, -1};
        }
    }

    int start = Nm * Nn;

    for (i = 0; i < Np; i++)
    {
        double Zp = cos((double)i * phi);

        for (j = 0; j < Nm; j++)
        {
            double x = cos((double)j * teta);
            double y = sin((double)j * teta);
            obj->vrtx[i * Nm + j + start] = (G3Xpoint){((1. - Zp) / 2.) * x, ((1. - Zp) / 2.) * y, Zp};
            obj->norm[i * Nm + j + start] = (G3Xvector){x, y, 0};
        }
    }

    return obj;
}
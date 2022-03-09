#include <object.h>
#include <math.h>

void draw_sphere_points(Shape *obj)
{
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)obj->n1 * (int)obj->n2; i++)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i);
    }
    glEnd();
}

void draw_sphere_quads(Shape *obj)
{
    int i, j;
    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < (int)obj->n2 - 1; i++)
    {
        for (j = 0; j < (int)obj->n1 - 1; j++)
        {
            normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1 + j);
            normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1 + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * obj->n1 + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * obj->n1 + j);
        }
        normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1 + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * obj->n1);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * obj->n1 + j);
    }

    for (j = 0; j < (int)obj->n1 - 1; j++)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1 + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1 + j + 1);
        normVrtx3dv(obj->norm, obj->vrtx, obj->n2 * obj->n1 - 1);
        normVrtx3dv(obj->norm, obj->vrtx, obj->n2 * obj->n1 - 1);
    }

    normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1 + j);
    normVrtx3dv(obj->norm, obj->vrtx, i * obj->n1);
    normVrtx3dv(obj->norm, obj->vrtx, obj->n2 * obj->n1 - 1);
    normVrtx3dv(obj->norm, obj->vrtx, obj->n2 * obj->n1 - 1);
    glEnd();
}

Shape *init_sphere()
{
    Shape *obj;

    if (NULL == (obj = malloc(sizeof(Shape))))
        return NULL;

    obj->n1 = MAXRES * PI;
    obj->n2 = (obj->n1) / 2.;
    obj->n3 = 1;

    if (NULL == (obj->vrtx = calloc(obj->n1 * obj->n2, sizeof(G3Xpoint))))
        return NULL;

    if (NULL == (obj->norm = calloc(obj->n1 * obj->n2, sizeof(G3Xvector))))
        return NULL;

    obj->draw_points = draw_sphere_points;
    obj->draw_quads = draw_sphere_quads;

    return obj;
}

Shape *load_sphere()
{
    Shape *obj;

    if (NULL == (obj = init_sphere()))
        return NULL;

    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;

    double teta = (2. * PI) / (double)Nm;
    double phi = PI / (double)Np;

    i = 0;
    for (j = 0; j < Nm; j++)
    {
        obj->vrtx[i * Nm + j] = (G3Xpoint){0., 0., +1.};
        obj->norm[i * Nm + j] = (G3Xvector){0., 0., +1.};
    }

    for (i = 1; i < Np - 1; i++)
    {
        double Zp = cos((double)i * phi);
        double Rp = sin((double)i * phi);

        for (j = 0; j < Nm; j++)
        {
            double x = Rp * cos((double)j * teta);
            double y = Rp * sin((double)j * teta);
            double z = Zp;
            obj->vrtx[i * Nm + j] = (G3Xpoint){x, y, z};
            obj->norm[i * Nm + j] = (G3Xvector){x, y, z};
        }
    }
    j = Np - 1;
    for (j = 0; j < Nm; j++)
    {
        obj->vrtx[i * Nm + j] = (G3Xpoint){0., 0., -1.};
        obj->norm[i * Nm + j] = (G3Xvector){0., 0., -1.};
    }

    return obj;
}
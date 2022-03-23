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
#include <math.h>

void draw_sphere_points(Shape *obj, G3Xvector scale_factor, double dcam)
{
    double nx = (scale_factor.x + (1. / dcam) * 10) / 11.;
    double ny = (scale_factor.y + (1. / dcam) * 10) / 11.;
    double dxy = (nx + ny) / 2.;
    int mpas = 1. / dxy;
    mpas = MAX(1, mpas);

    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)obj->n1 * (int)obj->n2 - mpas; i += mpas)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i);
    }
    glEnd();
}

void draw_sphere_quads(Shape *obj, G3Xvector scale_factor, double dcam)
{
    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;

    double nx = (scale_factor.x + (1. / dcam) * 10) / 11.;
    double ny = (scale_factor.y + (1. / dcam) * 10) / 11.;
    double nz = (scale_factor.z + (1. / dcam) * 10) / 11.;

    double dxy = (nx + ny) / 2.;
    int mpas = 1. / dxy;
    mpas = MAX(1, mpas);
    int ppas = 1. / nz;
    ppas = MAX(1, ppas);

    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < (int)Np - ppas; i += ppas)
    {
        for (j = 0; j < (int)Nm - mpas; j += mpas)
        {
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm + j);
        }

        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm + j);
    }

    for (j = 0; j < (int)Nm - mpas; j += mpas)
    {

        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + mpas);
        normVrtx3dv(obj->norm, obj->vrtx, Np * Nm - mpas);
        normVrtx3dv(obj->norm, obj->vrtx, Np * Nm - mpas);
    }

    normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
    normVrtx3dv(obj->norm, obj->vrtx, i * Nm);
    normVrtx3dv(obj->norm, obj->vrtx, Np * Nm - mpas);
    normVrtx3dv(obj->norm, obj->vrtx, Np * Nm - mpas);
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
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

void draw_cylinder_points(Shape *obj, G3Xvector scale_factor, double dcam)
{
    double nx = (scale_factor.x * dcam);
    double ny = (scale_factor.y * dcam);
    double dxy = (nx + ny) / 2.;
    int mpas = 1. / dxy;
    mpas = MAX(1, mpas);

    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)(2 * (obj->n1 * obj->n3) + (obj->n1 * obj->n2)) - mpas; i += mpas)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i);
    }
    glEnd();
}

void draw_cylinder_quads(Shape *obj, G3Xvector scale_factor, double dcam)
{
    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;
    int Nn = obj->n3;

    double nx = (scale_factor.x * dcam);
    double ny = (scale_factor.y * dcam);
    double nz = (scale_factor.z * dcam);

    double dxy = (nx + ny) / 2.;
    int mpas = 1. / dxy;
    mpas = MAX(1, mpas);
    int ppas = 1. / nz;
    ppas = MAX(1, ppas);
    int npas = ppas;

    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < Nn - npas; i += npas)
    {
        for (j = 0; j < Nm - mpas; j += mpas)
        {

            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, (i + npas) * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, (i + npas) * Nm + j);

            normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (i + npas) * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (i + npas) * Nm + j);
        }

        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + npas) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + npas) * Nm + j);

        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (i + npas) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (i + npas) * Nm + j);
    }

    for (j = 0; j < Nm - mpas; j += mpas)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + mpas);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn - 1) * Nm + j + mpas);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn - 1) * Nm + j);

        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm + j + mpas);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (Nn - 1) * Nm + j + mpas);
        normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (Nn - 1) * Nm + j);
    }

    normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
    normVrtx3dv(obj->norm, obj->vrtx, (Nn - 1) * Nm + j);
    normVrtx3dv(obj->norm, obj->vrtx, (Nn - 1) * Nm);
    normVrtx3dv(obj->norm, obj->vrtx, i * Nm);

    normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm + j);
    normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (Nn - 1) * Nm + j);
    normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + (Nn - 1) * Nm);
    normVrtx3dv(obj->norm, obj->vrtx, (Nn * Nm) + i * Nm);

    int start = 2 * (Nm * Nn);

    for (i = 0; i < Np - ppas; i += ppas)
    {
        for (j = 0; j < Nm - mpas; j += mpas)
        {
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + start);
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + mpas + start);
            normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm + j + mpas + start);
            normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm + j + start);
        }

        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + start);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + start);
        normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm + start);
        normVrtx3dv(obj->norm, obj->vrtx, (i + ppas) * Nm + j + start);
    }

    for (j = 0; j < Nm - mpas; j += mpas)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + start);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + mpas + start);
        normVrtx3dv(obj->norm, obj->vrtx, (Np - 1) * Nm + j + mpas + start);
        normVrtx3dv(obj->norm, obj->vrtx, (Np - 1) * Nm + j + start);
    }

    normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + start);
    normVrtx3dv(obj->norm, obj->vrtx, (Np - 1) * Nm + j + start);
    normVrtx3dv(obj->norm, obj->vrtx, (Np - 1) * Nm + start);
    normVrtx3dv(obj->norm, obj->vrtx, i * Nm + start);

    glEnd();
}

Shape *init_cylinder()
{
    Shape *obj;

    if (NULL == (obj = malloc(sizeof(Shape))))
        return NULL;

    obj->n1 = MAXRES * PI;
    obj->n2 = (obj->n1) / 2.;
    obj->n3 = MAXRES;

    if (NULL == (obj->vrtx = calloc(2 * (obj->n1 * obj->n3) + (obj->n1 * obj->n2), sizeof(G3Xpoint))))
        return NULL;

    if (NULL == (obj->norm = calloc(2 * (obj->n1 * obj->n3) + (obj->n1 * obj->n2), sizeof(G3Xvector))))
        return NULL;

    obj->draw_points = draw_cylinder_points;
    obj->draw_quads = draw_cylinder_quads;

    return obj;
}

Shape *load_cylinder()
{
    Shape *obj;

    if (NULL == (obj = init_cylinder()))
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
            obj->vrtx[i * Nm + j] = (G3Xpoint){x, y, 1};
            obj->norm[i * Nm + j] = (G3Xvector){0, 0, 1};

            obj->vrtx[(Nn * Nm) + (i * Nm) + j] = (G3Xpoint){x, y, -1};
            obj->norm[(Nn * Nm) + (i * Nm) + j] = (G3Xvector){0, 0, -1};
        }
    }

    int start = 2 * (Nm * Nn);

    for (i = 0; i < Np; i++)
    {
        double Zp = cos((double)i * phi);

        for (j = 0; j < Nm; j++)
        {
            double x = cos((double)j * teta);
            double y = sin((double)j * teta);
            obj->vrtx[i * Nm + j + start] = (G3Xpoint){x, y, Zp};
            obj->norm[i * Nm + j + start] = (G3Xvector){x, y, 0};
        }
    }

    return obj;
}
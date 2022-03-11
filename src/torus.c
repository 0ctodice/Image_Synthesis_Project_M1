#include <object.h>
#include <math.h>

void draw_torus_points(Shape *obj, G3Xvector scale_factor)
{
    double dxy = (scale_factor.x + scale_factor.y) / 2.;
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

void draw_torus_quads(Shape *obj, G3Xvector scale_factor)
{
    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;

    double dxy = (scale_factor.x + scale_factor.y) / 2.;
    int mpas = 1. / dxy;
    mpas = MAX(1, mpas);
    int ppas = 1. / scale_factor.z;
    ppas = MAX(1, ppas);

    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < Nm - mpas - 1; i += mpas)
    {
        for (j = 0; j < Np - ppas - 1; j += ppas)
        {

            normVrtx3dv(obj->norm, obj->vrtx, (i + mpas) * Np + j + ppas);
            normVrtx3dv(obj->norm, obj->vrtx, (i + mpas) * Np + j);
            normVrtx3dv(obj->norm, obj->vrtx, i * Np + j);
            normVrtx3dv(obj->norm, obj->vrtx, i * Np + j + ppas);
        }

        normVrtx3dv(obj->norm, obj->vrtx, (i + mpas) * Np);
        normVrtx3dv(obj->norm, obj->vrtx, (i + mpas) * Np + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Np + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Np);
    }

    for (j = 0; j < Np - ppas - 1; j += ppas)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i * Np + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Np + j + ppas);
        normVrtx3dv(obj->norm, obj->vrtx, j + ppas);
        normVrtx3dv(obj->norm, obj->vrtx, j);
    }

    normVrtx3dv(obj->norm, obj->vrtx, i * Np + j);
    normVrtx3dv(obj->norm, obj->vrtx, i * Np);
    normVrtx3dv(obj->norm, obj->vrtx, 0);
    normVrtx3dv(obj->norm, obj->vrtx, j);
    glEnd();
}

Shape *init_torus()
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

    obj->draw_points = draw_torus_points;
    obj->draw_quads = draw_torus_quads;

    return obj;
}

Shape *load_torus()
{
    Shape *obj;

    if (NULL == (obj = init_torus()))
        return NULL;

    int i, j;
    int Np = obj->n1;
    int Nm = obj->n2;
    double r = 1.;
    double s = 0.5;

    double teta = (2. * PI) / (double)Nm;
    double phi = (2. * PI) / (double)Np;

    for (i = 0; i < Np - 1; i++)
    {
        double NRp = cos((double)i * phi);
        double NZp = sin((double)i * phi);

        double Rp = r + s * NRp;
        double Zp = s * NZp;

        for (j = 0; j < Nm; j++)
        {
            double x = Rp * cos((double)j * teta);
            double y = Rp * -sin((double)j * teta);
            double z = Zp;

            double nx = NRp * cos((double)j * teta);
            double ny = NRp * -sin((double)j * teta);
            double nz = NZp;

            obj->vrtx[i * Nm + j] = (G3Xpoint){x, y, z};
            obj->norm[i * Nm + j] = (G3Xvector){nx, ny, nz};
        }
    }

    return obj;
}

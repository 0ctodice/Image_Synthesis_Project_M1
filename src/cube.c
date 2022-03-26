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

void draw_cube_points(Shape *obj, G3Xvector scale_factor, double dcam)
{
    double nx = (scale_factor.x * dcam);
    double ny = (scale_factor.y * dcam);
    double dxy = (nx + ny) / 2.;
    int mpas = 1. / dxy;
    mpas = MAX(1, mpas);

    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)(6 * (obj->n1 * obj->n2)) - mpas; i += mpas)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i);
    }
    glEnd();
}

void draw_cube_quads(Shape *obj, G3Xvector scale_factor, double dcam)
{
    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;

    double nx = (scale_factor.x * dcam);
    double ny = (scale_factor.y * dcam);
    double nz = (scale_factor.z * dcam);

    double dxy = (nx + ny) / 2.;
    int mpas = 1. / dxy;
    mpas = MAX(1, mpas);
    int ppas = 1. / nz;
    ppas = MAX(1, ppas);

    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < Np - ppas; i += ppas)
    {
        for (int k = 0; k < 6; k++)
        {
            for (j = 0; j < Nm - mpas; j += mpas)
            {
                normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + j);
                normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + j + mpas);
                normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (i + ppas) * Nm + j + mpas);
                normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (i + ppas) * Nm + j);
            }
        }
    }

    for (int k = 0; k < 6; k++)
    {

        for (j = 0; j < Nm - mpas; j += mpas)
        {
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (Np - 1) * Nm + j + mpas);
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (Np - 1) * Nm + j);
        }

        for (i = 0; i < Np - ppas; i += ppas)
        {
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + (Nm - 1));
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (i + ppas) * Nm + (Nm - 1));
            normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (i + ppas) * Nm + j);
        }

        normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + i * Nm + (Nm - 1));
        normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (Np - 1) * Nm + (Nm - 1));
        normVrtx3dv(obj->norm, obj->vrtx, k * (Np * Nm) + (Np - 1) * Nm + j);
    }
    glEnd();
}

Shape *init_cube()
{
    Shape *obj;

    if (NULL == (obj = malloc(sizeof(Shape))))
    {
        return NULL;
    }

    obj->n1 = MAXRES * PI / 2.;
    obj->n2 = obj->n1;
    obj->n3 = 1;

    if (NULL == (obj->vrtx = calloc(6 * (obj->n1 * obj->n2), sizeof(G3Xpoint))))
        return NULL;

    if (NULL == (obj->norm = calloc(6 * (obj->n1 * obj->n2), sizeof(G3Xvector))))
        return NULL;

    obj->draw_points = draw_cube_points;
    obj->draw_quads = draw_cube_quads;

    return obj;
}

Shape *load_cube()
{
    Shape *obj;

    if (NULL == (obj = init_cube()))
        return NULL;

    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;

    double dX = 2. / (Np - 1);
    double dY = 2. / (Nm - 1);

    for (i = 0; i < Np; i++)
    {

        for (j = 0; j < Nm; j++)
        {
            double x = -1. + j * dX;
            double y = -1. + i * dY;

            // BOTTOM
            obj->vrtx[i * Nm + j] = (G3Xpoint){x, y, -1};
            obj->norm[i * Nm + j] = (G3Xvector){0, 0, -1};

            // TOP
            obj->vrtx[(Np * Nm) + (i * Nm) + j] = (G3Xpoint){x, y, 1};
            obj->norm[(Np * Nm) + (i * Nm) + j] = (G3Xvector){0, 0, 1};

            // BACK
            obj->vrtx[2 * (Np * Nm) + (i * Nm) + j] = (G3Xpoint){x, -1, y};
            obj->norm[2 * (Np * Nm) + (i * Nm) + j] = (G3Xvector){0, -1, 0};

            // FRONT
            obj->vrtx[3 * (Np * Nm) + (i * Nm) + j] = (G3Xpoint){x, 1, y};
            obj->norm[3 * (Np * Nm) + (i * Nm) + j] = (G3Xvector){0, 1, 0};

            // RIGHT
            obj->vrtx[4 * (Np * Nm) + (i * Nm) + j] = (G3Xpoint){-1, x, y};
            obj->norm[4 * (Np * Nm) + (i * Nm) + j] = (G3Xvector){-1, 0, 0};

            // LEFT
            obj->vrtx[5 * (Np * Nm) + (i * Nm) + j] = (G3Xpoint){1, x, y};
            obj->norm[5 * (Np * Nm) + (i * Nm) + j] = (G3Xvector){1, 0, 0};
        }
    }

    return obj;
}
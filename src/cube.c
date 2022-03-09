#include <object.h>
#include <math.h>

void draw_cube_points(Shape *obj)
{
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)(6 * (obj->n1 * obj->n2)); i++)
    {
        normVrtx3dv(obj->norm, obj->vrtx, i);
    }
    glEnd();
}

void draw_cube_quads(Shape *obj)
{
    int i, j;
    int Nm = obj->n1;
    int Np = obj->n2;

    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < Np - 1; i++)
    {

        for (j = 0; j < Nm - 1; j++)
        {
            // BOTTOM
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j);

            // TOP
            normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + i * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + (i + 1) * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + (i + 1) * Nm + j);

            // BACK
            normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + i * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + (i + 1) * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + (i + 1) * Nm + j);

            // FRONT
            normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + i * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + (i + 1) * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + (i + 1) * Nm + j);

            // RIGHT
            normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + i * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + (i + 1) * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + (i + 1) * Nm + j);

            // LEFT
            normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + i * Nm + j);
            normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + i * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + (i + 1) * Nm + j + 1);
            normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + (i + 1) * Nm + j);
        }

        // BOTTOM
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (i + 1) * Nm + j);

        // TOP
        normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + (i + 1) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, (Np * Nm) + (i + 1) * Nm + j);

        // BACK
        normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + (i + 1) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 2 * (Np * Nm) + (i + 1) * Nm + j);

        // FRONT
        normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + (i + 1) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 3 * (Np * Nm) + (i + 1) * Nm + j);

        // RIGHT
        normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + (i + 1) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 4 * (Np * Nm) + (i + 1) * Nm + j);

        // LEFT
        normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + i * Nm + j);
        normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + i * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + (i + 1) * Nm);
        normVrtx3dv(obj->norm, obj->vrtx, 5 * (Np * Nm) + (i + 1) * Nm + j);
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
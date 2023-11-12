#include "../includes/miniRT.h"
#include <float.h>

bool intersection_sphere(t_ray ray, t_obj sp, t_vec *p, t_vec *n, double *t)
{

    double a = 1;
    double b = 2 * dot_product(ray.direction, vec_subtract(ray.coord, sp.coord));
    double c = norm(vec_subtract(ray.coord, sp.coord)) - sp.p.x * sp.p.x;
    double delta = b * b - 4 * a * c;
    if (delta < 0)
        return false;
    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);
    if (t2 < 0)
        return false;
    if (t1 > 0)
    {
        *t = t1;
    }
    else
    {
        *t = t2;
    }

    *p = vec_add(ray.coord, vec_multiply(ray.direction, *t));
    *n = normalize(vec_subtract(*p, sp.coord));

    return true;
}

bool intersection_scene(t_scene scene, t_ray ray, t_vec *p, t_vec *n, t_obj *s)
{
    t_obj *sphere;
    sphere = scene.obj;
    bool has_intersect;
    has_intersect = false;
    double min_t = DBL_MAX;
    while (sphere != NULL)
    {
        t_vec local_p;
        t_vec local_n;
        bool local_has_intersect;
        double local_t;
        local_has_intersect = intersection_sphere(ray, *sphere, &local_p, &local_n, &local_t);
        if (local_has_intersect)
        {
            has_intersect = true;
            if (local_t < min_t)
            {
                min_t = local_t;
                *p = local_p;
                *n = local_n;
                *s = *sphere;
            }
        }
        sphere = sphere->next;
    }
    return has_intersect;
}

#include "../includes/miniRT.h"


bool intersection_sphere(t_ray ray, t_obj sp,t_vec *p,t_vec *n)
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
    double t;
    if(t1 > 0){
        t = t1;
    }else {
        t = t2;
    }

    *p = vec_add(ray.coord, vec_multiply(ray.direction, t));
    *n = normalize(vec_subtract(*p, sp.coord));


    return true;
}

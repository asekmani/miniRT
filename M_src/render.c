/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:19:51 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/26 16:19:54 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
void img_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

// void apply_lighting(t_scene scene, t_vec coord_light, t_vec norm_light, t_obj inter_obj, t_vec *px_color, t_vec p)
// {
//     double dot = dot_product(norm_light, normalize(vec_subtract(scene.light->coord, p)));
//     dot = (dot < 0) ? 0 : dot;
//     double pixel = scene.light->ratio * dot / norm(coord_light);
//     *px_color = vec_multiply(normalize_color(inter_obj.color), pixel);
//     px_color->x = pow(px_color->x, 1 / 2.2);
//     px_color->y = pow(px_color->y, 1 / 2.2);
//     px_color->z = pow(px_color->z, 1 / 2.2);
//     px_color->x = (px_color->x > 255) ? 255 : ((px_color->x < 0) ? 0 : px_color->x);
//     px_color->y = (px_color->y > 255) ? 255 : ((px_color->y < 0) ? 0 : px_color->y);
//     px_color->z = (px_color->z > 255) ? 255 : ((px_color->z < 0) ? 0 : px_color->z);
// }

// bool check_shadow(t_scene scene, t_vec p, t_vec n, t_obj inter_obj, t_vec *px_color)
// {
//     t_ray pos_light;
//     double dis;
//     (void)inter_obj;
	
//     pos_light.coord = vec_add(p, vec_multiply(n, 0.01));
//     pos_light.direc = normalize(vec_subtract(scene.light->coord, p));
//     bool inter_light = inter_scene_ray(scene, pos_light, &dis);

//     if (inter_light && dis * dis < norm(vec_subtract(scene.light->coord, p)))
//     {
//         px_color->x = 0;
//         px_color->y = 0;
//         px_color->z = 0;
//         return true;
//     }
//     return false;
// }

// bool compute_intersection_color(t_scene scene, t_ray ray, t_vec *p, t_vec *n, t_obj *inter_obj, t_vec *px_color)
// {
//     bool inter = inter_scene(scene, ray, p, n, inter_obj);
//     px_color->x = 0;
//     px_color->y = 0;
//     px_color->z = 0;

//     if (inter)
//     {
//         t_vec coord_light = vec_subtract(scene.light->coord, *p);
//         t_vec norm_light = normalize(coord_light);
//         if (!check_shadow(scene, *p, *n, *inter_obj, px_color))
//         {
//             apply_lighting(scene, coord_light, norm_light, *inter_obj, px_color, *p);
//             return true;
//         }
//     }
//     return false;
// }

// t_ray create_ray(t_scene scene, int i, int j)
// {
// 	t_ray ray;
// 	ray.coord = scene.camera.coord;
// 	ray.direc.x = j - W / 2;
// 	ray.direc.y = i - H / 2;
// 	ray.direc.z = -W / (2 * tan(scene.camera.FOV / 2));
// 	ray.direc = normalize(ray.direc);
// 	return ray;
// }

// void tracing(t_minirt *rt)
// {
// 	t_scene scene;
// 	t_ray ray;
// 	t_vec px_color;
// 	t_vec p;
// 	t_vec n;
// 	t_obj inter_obj;
// 	int color;
// 	int i;
// 	int j;

// 	scene = create_scene();
// 	i = 0;
// 	while (i < H)
// 	{
// 		j = 0;
// 		while (j < W)
// 		{
// 			ray = create_ray(scene, i, j);
// 			if (compute_intersection_color(scene, ray, &p, &n, &inter_obj, &px_color))
// 			{
// 				color = create_rgb(px_color.x, px_color.y, px_color.z);
// 				img_pixel_put(&rt->img, j, H - i - 1, color);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
  
// double norm(t_vec v);
// double dot_product(t_vec v1, t_vec v2);
// t_vec normalize(t_vec v);
// t_vec normalize_color(t_vec v);
// t_vec vec_add(t_vec v1, t_vec v2);
// t_vec vec_multiply(t_vec v, double scalar);
// t_vec vec_subtract(t_vec v1, t_vec v2);
// t_scene create_scene();
// bool inter_scene_ray(t_scene scene, t_ray ray, double *t);
// bool inter_scene(t_scene scene, t_ray ray, t_vec *p, t_vec *n, t_obj *s);

void tracing(t_minirt *rt)
{
	t_scene scene;
	t_ray ray;
	t_vec px_color;
	t_vec coord_light;
	t_vec norm_light;
	t_vec p;			 // point d'intersection de rayon avec l'objet
	t_vec n;			 // normal
	t_obj inter_obj;		// l'objet le plus proche qui intersecte avec le rayon
	t_ray pos_light;	// video 2 10m:20
	double dis;		//distance_vers_intersection
	double pixel;
	double dot;
	bool inter_light;
	bool inter;
	int color;
	int i;
	int j;

	scene = create_scene();
	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			// creation de rayon: l'origine de rayon est la position de camera, direction est le pixel courant
			ray.coord = scene.camera.coord;
			ray.direc.x = j - W / 2;
			ray.direc.y = i - H / 2;
			ray.direc.z = -W / (2 * tan(scene.camera.FOV / 2));
			ray.direc = normalize(ray.direc);
			inter = inter_scene(scene, ray, &p, &n, &inter_obj);
			px_color.x = 0;
			px_color.y = 0;
			px_color.z = 0;
			if (inter)
			{
				coord_light = vec_subtract(scene.light->coord, p);
				norm_light = normalize(coord_light);
				// créer un rayon d'origin position p qui est la plus proche intersection et de direction vers la lumiere
				pos_light.coord = vec_add(p, vec_multiply(n, 0.01));
				pos_light.direc = norm_light;
				inter_light = inter_scene_ray(scene, pos_light, &dis);
				if (inter_light && dis * dis < norm(coord_light))
				{
					px_color.x = 0;
					px_color.y = 0;
					px_color.z = 0;
				}
				else
				{
					dot = dot_product(norm_light, n);
					if (dot < 0)
						dot = 0;
					pixel = scene.light->ratio * dot / norm(coord_light);
					px_color = vec_multiply(normalize_color(inter_obj.color), pixel);
					px_color.x = pow(px_color.x, 1 / 2.2);
					px_color.y = pow(px_color.y, 1 / 2.2);
					px_color.z = pow(px_color.z, 1 / 2.2);
					px_color.x = (px_color.x > 255) ? 255 : ((px_color.x < 0) ? 0 : px_color.x);
					px_color.y = (px_color.y > 255) ? 255 : ((px_color.y < 0) ? 0 : px_color.y);
					px_color.z = (px_color.z > 255) ? 255 : ((px_color.z < 0) ? 0 : px_color.z);
				}
			}
			color = create_rgb(px_color.x, px_color.y, px_color.z);
			img_pixel_put(&rt->img, j, H - i - 1, color);
			j++;
		}
		i++;
	}
}

void render_rt(t_minirt *rt)
{
    tracing(rt);
	mlx_put_image_to_window(rt->vars.mlx, rt->vars.win, rt->img.img, 0, 0);
	mlx_key_hook(rt->vars.win, exit_key, &rt->vars);
	mlx_hook(rt->vars.win, 17, 0, end_minirt, &rt->vars);
	mlx_loop(rt->vars.mlx);
}

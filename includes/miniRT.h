/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:55:20 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/14 17:55:23 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define MLX_ERROR 1

# define W 800
# define H 800

# define EPS 0.000001
# define PI 3.14159265358979323846264338327950288
# define CY 2
# define PL 4
# define SP 6
# define CO 8

# include "mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct alloc
{
	void			*adr;
	struct alloc	*next;
}					t_alloc;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef struct s_ray
{
	t_vec			coord;
	t_vec			direc;
}					t_ray;

typedef struct s_light
{
	t_vec			coord;
	double			ratio;
	t_vec			color;
	struct s_light	*next;
}					t_light;

typedef struct s_obj
{
	int				id;
	t_vec			coord;
	t_vec			orient;
	t_vec			p;
	t_vec			cy_axe;
	t_vec			color;
	struct s_obj	*next;
}					t_obj;

typedef struct s_amb
{
	int				counter;
	double			ratio;
	t_vec			color;
}					t_amb;

typedef struct t_cam
{
	int				counter;
	t_vec			coord;
	t_vec			orient;
	t_vec			forward;
	double			FOV;
	double			aspect;
	double			tan;
	t_vec			up;
	t_vec			right;

}					t_cam;

typedef struct s_scene
{
	t_obj			*obj;
	t_vec			color;
	t_amb			ambient;
	t_cam			camera;
	t_light			*light;

}					t_scene;

typedef struct s_minirt
{
	t_vars			vars;
	t_img			img;
	t_vec			vec;
	t_ray			ray;
	t_scene			*scene;

}					t_minirt;

typedef struct s_color_cal
{
	t_vec			p;
	t_vec			n;
	t_obj			inter_obj;
	t_vec			color_result;
	t_vec			coord_light;
	t_vec			norm_light;
	t_ray			pos_light;
	bool			inter;
	bool			inter_light;
	double			dis;
	double			pixel;
}					t_color_cal;

typedef struct cylinder
{
	double			a;
	double			b;
	double			c;
	double			t;
	double			t1;
	double			t2;
	double			delta;
	double			y0;
	double			y1;
	t_vec			oc;
	t_vec			normal;
}					t_cylinder;

typedef struct s_inter
{
	t_vec			p;
	t_vec			n;
	double			t;
}					t_inter;

typedef struct s_sphere
{
	double			a;
	double			b;
	double			c;
	double			t;
	double			t1;
	double			t2;
	t_vec			oc;
}					t_sphere;

typedef struct s_cone
{
	double			a;
	double			b;
	double			c;
	double			delta;
	double			t;
	double			t1;
	double			t2;
	double			y0;
	double			y1;
	t_vec			x;
	t_vec			v;
	double			k;
}					t_cone;

/*Global*/
extern t_alloc		*g_memory;

/*Utils*/
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
char				*get_next_line(int fd);
char				**ft_split(char const *str, char c);
double				ft_atod(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
void				free_split(char **s);

/*Render*/
void				tracing(t_minirt *rt);
void				render_rt(t_minirt *rt);
void				img_pixel_put(t_img *img, int x, int y, int color);
int					shade(t_scene *sc, t_inter inter, t_light *light);

/*Exit*/
void				clean_exit(int exit_code, t_minirt *rt);
void				error_msg(char *str);
int					exit_key(int keycode, t_minirt *rt);
int					end_minirt(t_minirt *mlx);

/*Memory_allocator*/
t_alloc				*new_node(void *adr);
t_alloc				**add_adr(t_alloc **g_memory, void *adr);
void				*memory_adr(t_alloc **g_memory, size_t size);
void				free_memory(t_alloc **g_memory, t_alloc *node);

/*Init_struct*/
void				init_minirt(t_minirt *rt);
t_scene				*init_scence(void);
t_light				*init_light(t_minirt *rt);
t_obj				*init_obj(t_minirt *rt);
t_color_cal			init_color_calculator(void);
t_inter				create_inter(void);
t_vec				create_vector(void);
t_vec				create_vectorv(double x, double y, double z);
t_ray				create_ray(void);
t_obj				create_t_obj(void);

/*Parsing*/
t_vec				color_parse(char *str);
t_vec				vectors_parse(char *str);
void				ambient_parse(t_minirt *rt, char **arv);
void				camera_parse(t_minirt *rt, char **arv);
void				light_parse(t_minirt *rt, char **arv);
void				sphere_parse(t_minirt *rt, char **arv);
void				plane_parse(t_minirt *rt, char **arv);
void				cylinder_parse(t_minirt *rt, char **arv);
void				cone_parse(t_minirt *rt, char **arv);
void				check_id(t_minirt *rt, char **arv, char *id);
void				ft_parsing(t_minirt *rt, int fd);

/*Vectors*/
t_vec				vec_add(t_vec v1, t_vec v2);
t_vec				vec_subtract(t_vec v1, t_vec v2);
t_vec				vec_multiply(t_vec v, double scalar);
t_vec				vec_divide(t_vec v, double scalar);
t_vec				vect_cross(t_vec u, t_vec v);
t_vec				normalize(t_vec v);
double				vec_module(t_vec v);
double				vec_length(t_vec v);
double				dot_product(t_vec v1, t_vec v2);
double				norm(t_vec v);

/*Intersection*/
bool				inter_plan(t_ray ray, t_obj obj, t_inter *inter);
bool				inter_sphere(t_ray ray, t_obj sp, t_inter *inter);
bool				inter_cylindre(t_ray ray, t_obj obj, t_inter *inter);
bool				inter_cone(t_ray ray, t_obj obj, t_inter *inter);
bool				inter_scene(t_scene scene, t_ray ray, t_inter *inter,
						t_obj *s);
bool				find_inter_cy(t_cylinder info, t_ray *ray, t_obj *cy,
						double *t);
bool				find_inter_co(t_cone info, t_obj *co, t_ray *ray, double *t);
bool				inter_scene_ray(t_scene scene, t_ray ray, double *t);
double				take_min(double x, double y);
t_sphere			create_sph(t_ray ray, t_obj sp);
t_cylinder			create_cyl(t_ray ray, t_obj obj);
t_cone				create_cone(t_ray ray, t_obj obj);

/*Camera*/
t_ray				create_ray_cam(t_minirt *rt, double i, double j);
void				set_camera_scene(t_minirt *rt);

/*Color*/
int					create_rgb(int r, int g, int b);
void				color_adjust(t_vec *col_res);
t_vec				diffuse(t_obj obj_int, t_light *light, double d);
t_vec				calcul_color(t_scene sc, t_ray ray);
t_vec				calcul_light_color(t_scene *sc, t_inter inter,
						t_obj obj_int, t_vec amb);

/*Color_vectors*/

t_vec				calcul_coef_color(t_vec obj_color, t_vec amb_col,
						double ratio);
t_vec				add_color(t_vec col1, t_vec col2);
t_vec				norm_color(t_vec v);

#endif
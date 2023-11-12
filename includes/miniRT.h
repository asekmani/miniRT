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

# define WIDTH 1200
# define HEIGHT 1200

# define EPS 0.000001
# define CY 2
# define PL 4
# define SP 6
# define CO 8 

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
#include <stdbool.h>
#include "mlx.h"

typedef struct alloc
{
	void				*adr;
	struct alloc		*next;
}				t_alloc;

typedef struct s_img
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}				t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;


typedef struct s_light
{
	t_vec			coord;
	double			ratio;
	t_vec			color;
	struct s_light	*next;
}				t_light;

typedef struct s_obj
{
	int				id;
	t_vec			coord;
	t_vec			orient;
	t_vec			p;
	t_vec			cy_axe;
	t_vec			color;
	struct s_obj	*next;
}				t_obj;

typedef struct s_amb
{
	int		counter;
	double	ratio;
	t_vec	color;
}				t_amb;

typedef struct t_cam
{
	int		counter;
	t_vec	coord;
	t_vec	orient;
	double	FOV;
}				t_cam;

typedef struct s_scene
{
	t_obj	*obj;
	t_vec	color;
	t_amb	ambient;
	t_cam	camera;
	t_light	*light;

}				t_scene;

typedef struct s_minirt
{
	t_vars	vars;
	t_img	img;
	t_vec	vec;
	t_scene	*scene;

}				t_minirt;


typedef struct s_ray
{
	t_vec	coord;
	t_vec	direction;
}				t_ray;

/*Global*/
t_alloc		*g_memory;

/*Utils*/
size_t		ft_strlen(const char *s);
char		*get_next_line(int	fd);
char		**ft_split(char const *str, char c);
double		ft_atod(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		free_split(char **s);
int			ft_atoi(const char *str);

/*Render*/
void		render_rt(t_minirt *rt);

/*Exit*/
void		clean_exit(int exit_code, t_minirt *rt);
void		error_msg(char *str);
int			exit_key(int keycode, t_minirt *rt);
int			end_minirt(t_minirt *mlx);

/*Memory_allocator*/
t_alloc		*new_node(void *adr);
t_alloc		**add_adr(t_alloc **g_memory, void *adr);
void		*memory_adr(t_alloc **g_memory, size_t size);
void		free_memory(t_alloc **g_memory, t_alloc *node);

/*Init_struct*/
void		init_minirt(t_minirt	*rt);
t_scene		*init_scence(void);
t_light		*init_light(t_minirt *rt);
t_obj		*init_obj(t_minirt *rt);

/*Parsing*/
t_vec		color_parse(char *str);
t_vec		vectors_parse(char *str);
t_vec 		vec_subtract(t_vec v1, t_vec v2);
bool 		intersection_sphere(t_ray ray, t_obj sp,t_vec *p,t_vec *n);
void		ambient_parse(t_minirt *rt, char **arv);
void		camera_parse(t_minirt *rt, char **arv);
void		light_parse(t_minirt *rt, char **arv);
void		sphere_parse(t_minirt *rt, char **arv);
void		plane_parse(t_minirt *rt, char **arv);
void		cylinder_parse(t_minirt *rt, char **arv);
void		check_id(t_minirt *rt, char **arv, char *id);
void		ft_parsing(t_minirt *rt, int fd);
t_vec 		normalize(t_vec v);
double 		dot_product(t_vec v1, t_vec v2);
t_vec 		vec_add(t_vec v1, t_vec v2);
t_vec 		vec_multiply(t_vec v, double scalar);
t_vec 		vec_subtract(t_vec v1, t_vec v2);
t_vec 		normalize_color(t_vec v);
double 		norm(t_vec v);



void save_img(const char* filename, const unsigned char* pixels, int W, int H);

#endif
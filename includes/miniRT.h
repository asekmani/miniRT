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
# define CY 1
# define PL 2
# define SP 3
# define CO 4 

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

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

typedef struct s_lum
{
	double			ratio;
	t_vec			src;
	t_vec			color;
	struct s_lum	*next;
}				t_lum;

typedef struct s_obj
{
	int				type;
	// t_vec			cen;
	// t_vec			dir;
	// t_vec			p;
	// t_vec			col;
	// t_vec			norm;
	struct s_obj	*next;
}				t_obj;

typedef struct s_amb
{
	int		counter;
	double	ratio;
	t_vec	color;
}				t_amb;

typedef struct s_scene
{
	t_obj	*objs;
	t_vec	color;
	t_lum	*light;
	t_amb	ambient;
	// t_cam	camera;

}				t_scene;

typedef struct s_minirt
{
	t_vars	vars;
	t_img	img;
	t_vec	vec;
	t_scene	*scene;

}				t_minirt;

/*Global*/
t_alloc		*g_memory;

/*Utils*/
size_t		ft_strlen(const char *s);
double		ft_atod(const char *str);

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

/*Parsing*/


#endif
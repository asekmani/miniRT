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

typedef struct s_minirt
{
	t_vars	vars;
	t_img	img;
	t_vec	vec;
}				t_minirt;

/*UTILS*/
size_t	ft_strlen(const char *s);
void	error_msg(char *str);

/*INIT*/
void	init_minirt(t_minirt	*rt);
void	render_rt(t_minirt *rt);

/*EXIT*/
void	clean_exit(int exit_code, t_minirt *rt);
int		exit_key(int keycode, t_minirt *rt);
int		end_minirt(t_minirt *mlx);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:34:34 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/07 16:57:30 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

//# include <mlx.h>
# include "../SDL2/include/SDL2/SDL.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "keys.h"
# include "colors.h"

# define WIDTH 1000
# define HEIGHT 800

# define MOVE_SPEED 0.05
# define ZOOM_SPEED 1.06
# define MOUSE_S 0.005

/* typedef enum	e_color_mod
{
	BLUE_MOD,
	RED_MOD,
	GREEN_MOD,
	RAND_MOD
}				t_color_mod; */

typedef struct	s_complex
{
	double		cx;
	double		cy;
	double		xn;
	double		yn;
}				t_complex;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_env
{
	t_point		mouse;
	SDL_Window		*win_ptr;
	void		*img_ptr;
	SDL_Event	*event;
	int			*data;
	int			width;
	int			height;
	int			bpp;
	int			size_l;
	int			endian;
	int			fractal;
	int			itermax;
	double		hor;
	double		vert;
	double		zoom;
	char		colormod;
	char		motion;
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	int			n;
}				t_env;

int			ft_wolf3d(char *mapfile);
int			ft_mlx(t_env *wolf);
int			ft_key_hook(int keycode, t_env *wolf);

#endif

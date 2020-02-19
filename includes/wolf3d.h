/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:34:34 by jcanteau          #+#    #+#             */
/*   Updated: 2020/02/19 12:31:29 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../SDL2/include/SDL2/SDL.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "colors.h"

# define TRUE 1
# define FALSE 0

# define PI 3.14159

# define WIDTH 1000
# define HEIGHT 600

# define FOV PI / 3

# define MAX_DEPTH 20
# define PRECISION 0.02
# define SHADING_DEPTH 0.05
# define BLOCK HEIGHT * 0.01
# define WALL_SIZE 0.8

# define MOVE_SPEED 0.025
# define ROTATE_SPEED 0.025

# define WALL '#'
# define EMPTY '.'

/* typedef enum	e_control
{
	FORWARD,
	STRAFE_RIGHT,
	BACKWARD,
	STRAFE_LEFT,
	ROTATE
}				t_control; */

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_map
{
	int			nbl;
	int			nbcol;
	size_t		cur_line;
	char		**map;
}				t_map;

typedef struct	s_camera
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		angle;
	double		fov;
	double		plane_x;
	double		plane_y;
	size_t		strafe_left;
	size_t		strafe_right;
	size_t		forward;
	size_t		backward;
	size_t		rotate_left;
	size_t		rotate_right;
}				t_camera;

typedef struct	s_env
{
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_PixelFormat *format;
	SDL_Event 		event;
	t_map			mapdata;
	t_camera		cam;
	Uint32			*pixels;
}				t_env;

void		ft_wolf3d(char *mapfile);
void		ft_sdl(t_env *wolf);
void		ft_key_hook(t_env *wolf);
void		ft_exit(t_env *wolf, int exit_type, char *message);
void		ft_print(t_env *wolf);

#endif

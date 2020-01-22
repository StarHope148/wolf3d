/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:34:34 by jcanteau          #+#    #+#             */
/*   Updated: 2020/01/22 13:05:58 by jcanteau         ###   ########.fr       */
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
# include "keys.h"
# include "colors.h"

# define WIDTH 640
# define HEIGHT 480
# define RAYDIST WIDTH / 60

# define BLOCK 16

# define MOVE_SPEED 0.1
# define ZOOM_SPEED 1.06
# define MOUSE_S 0.005

# define WALL '#'
# define EMPTY '.'

typedef enum	e_control
{
	FORWARD,
	STRAFE_RIGHT,
	BACKWARD,
	STRAFE_LEFT,
	ROTATE
}				t_control;

typedef struct	s_vector
{
	float 		posX;
	float 		posY;
	float 		dirX;
	float 		dirY;
	float		planeX;
	float		planeY;
}				t_vector;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_map
{
	size_t		nbl;
	size_t		nbcol;
	size_t		nbl_cur;
	char		**map;
}				t_map;

typedef struct	s_camera
{
	double		x;
	double		y;
	double		angle;
	double		dist;
	ssize_t		velx;
	ssize_t		vely;
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
	t_vector		vec;
}				t_env;

void		ft_wolf3d(char *mapfile);
void		ft_sdl(t_env *wolf);
void		ft_key_hook(t_env *wolf);
void		ft_exit(t_env *wolf, int exit_type, char *message);
void		ft_print(t_env *wolf);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:34:34 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/19 17:03:51 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

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

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_env
{
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_PixelFormat *format;
	SDL_Event 		event;
	int				width;
	int				height;

}				t_env;

void		ft_wolf3d(char *mapfile);
void		ft_sdl(t_env *wolf);
void		ft_key_hook(t_env *wolf);
int			ft_exit(t_env *wolf, int exit_type);

#endif

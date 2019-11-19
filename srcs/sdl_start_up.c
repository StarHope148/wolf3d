/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/19 16:24:48 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				ft_exit(t_env *wolf, int exit_type)
{
	if (wolf->window != NULL)
		SDL_DestroyWindow(wolf->window);
	if (wolf->renderer != NULL)
		SDL_DestroyRenderer(wolf->renderer);
	if (wolf->texture != NULL)
		SDL_DestroyTexture(wolf->texture);
	if (wolf->format != NULL)
		SDL_FreeFormat(wolf->format);
	SDL_Quit();
	return(exit_type);
}

void			ft_init_renderer_texture(t_env *wolf)
{
	wolf->renderer = SDL_CreateRenderer(wolf->window,
										-1,
										SDL_RENDERER_ACCELERATED);
	if (wolf->renderer == NULL)
	{
		perror("Error in SDL_CreateRenderer() ");
		exit(ft_exit(wolf, EXIT_FAILURE));
	}
	wolf->texture = SDL_CreateTexture(wolf->renderer,
									SDL_PIXELFORMAT_RGBA8888,
									SDL_TEXTUREACCESS_STREAMING,
									WIDTH,
									HEIGHT);
	if (wolf->texture == NULL)
	{
		perror("Error in SDL_CreateTexture() ");
		exit(ft_exit(wolf, EXIT_FAILURE));
	}
}

void			ft_init_window_renderer(t_env *wolf)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
	{
		perror("Error in SDL_Init() ");
		exit(EXIT_FAILURE);
	}
	wolf->window = SDL_CreateWindow("WOLF3D",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					wolf->width,
					wolf->height,
					SDL_WINDOW_SHOWN);
	if (wolf->window == NULL)
	{
		perror("Error in SDL_CreateWindow() ");
		exit(ft_exit(wolf, EXIT_FAILURE));
	}
}

void			ft_sdl(t_env *wolf)
{
	ft_init_window_renderer(wolf);
	ft_init_renderer_texture(wolf);
	ft_exit(wolf, EXIT_SUCCESS);
}

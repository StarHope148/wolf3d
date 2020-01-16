/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/01/16 17:03:51 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				ft_exit(t_env *wolf, int exit_type, char *message)
{
	if (wolf->format != NULL)
		SDL_FreeFormat(wolf->format);
	if (wolf->texture != NULL)
		SDL_DestroyTexture(wolf->texture);
	if (wolf->renderer != NULL)
		SDL_DestroyRenderer(wolf->renderer);
	if (wolf->window != NULL)
		SDL_DestroyWindow(wolf->window);
	/* if (wolf->pixels != NULL)
		free(wolf->pixels); */
	SDL_Quit();
	if (message != NULL)
		perror(message);
	exit(exit_type);
}

void			ft_init_window_renderer(t_env *wolf)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_Init() ");
	wolf->window = SDL_CreateWindow("WOLF3D",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					wolf->width,
					wolf->height,
					0);
	if (wolf->window == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateWindow() ");
}

void			ft_init_renderer_texture(t_env *wolf)
{
	wolf->renderer = SDL_CreateRenderer(wolf->window,
										-1,
										SDL_RENDERER_ACCELERATED);
	if (wolf->renderer == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateRenderer() ");
	wolf->texture = SDL_CreateTexture(wolf->renderer,
									SDL_PIXELFORMAT_RGBA8888,
									SDL_TEXTUREACCESS_STREAMING,
									WIDTH,
									HEIGHT);
	if (wolf->texture == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateTexture() ");
}

void			ft_sdl(t_env *wolf)
{
	ft_init_window_renderer(wolf);
	ft_init_renderer_texture(wolf);
	ft_print(wolf);
	ft_key_hook(wolf);
	ft_exit(wolf, EXIT_SUCCESS, NULL);
}

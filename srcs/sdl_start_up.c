/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/24 17:25:42 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_exit(t_env *wolf, int exit_type, char *message)
{
	if (wolf->screen_pixels != NULL)
		free(wolf->screen_pixels);
	//if (wolf->pixels_wall_north != NULL)
	//	free(wolf->pixels_wall_north);
	//if (wolf->pixels_wall_south != NULL)
	//	free(wolf->pixels_wall_south);
	//if (wolf->pixels_wall_east != NULL)
	//	free(wolf->pixels_wall_east);
	//if (wolf->pixels_wall_west != NULL)
	//	free(wolf->pixels_wall_west);
		

	if (wolf->texture != NULL)
		SDL_DestroyTexture(wolf->texture);
	if (wolf->surface_wall_north != NULL)
		SDL_FreeSurface(wolf->surface_wall_north);
	if (wolf->surface_wall_south != NULL)
		SDL_FreeSurface(wolf->surface_wall_south);
	if (wolf->surface_wall_east != NULL)
		SDL_FreeSurface(wolf->surface_wall_east);
	if (wolf->surface_wall_west != NULL)
		SDL_FreeSurface(wolf->surface_wall_west);
	if (wolf->renderer != NULL)
		SDL_DestroyRenderer(wolf->renderer);
	if (wolf->window != NULL)
		SDL_DestroyWindow(wolf->window);
	SDL_Quit();
	
	if (wolf->mapdata.map != NULL)
		ft_free_map(wolf);
	if (message != NULL)
		perror(message);
	exit(exit_type);
}

void	ft_init_window(t_env *wolf)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_Init() ");
	wolf->window = SDL_CreateWindow("WOLF3D",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					WIDTH,
					HEIGHT,
					0);
	if (wolf->window == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_CreateWindow() ");
}

void	ft_init_renderer_texture(t_env *wolf)
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

void	ft_load_surface(t_env *wolf, char *image_file, SDL_Surface **dest)
{
	SDL_Surface	*tmp;

	tmp = NULL;
	tmp = SDL_LoadBMP(image_file);
	if (tmp == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_LoadBMP() ");
	*dest = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 1);
	SDL_FreeSurface(tmp);
	if (*dest == NULL)
		ft_exit(wolf, EXIT_FAILURE, "Error in SDL_ConvertSurfaceFormat() ");
}

void	ft_sdl(t_env *wolf)
{
	ft_init_window(wolf);
	ft_init_renderer_texture(wolf);
	ft_load_surface(wolf, "textures/risitas_wall.bmp",
					&(wolf->surface_wall_north));
	ft_load_surface(wolf, "textures/panda_wall.bmp",
					&(wolf->surface_wall_south));
	ft_load_surface(wolf, "textures/orange_wall.bmp",
					&(wolf->surface_wall_east));
	ft_load_surface(wolf, "textures/green_wall.bmp",
					&(wolf->surface_wall_west));
	ft_print(wolf);
	ft_key_hook(wolf);
	ft_exit(wolf, EXIT_SUCCESS, NULL);
}

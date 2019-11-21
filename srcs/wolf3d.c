/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:57:29 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/21 16:33:41 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_fill_map(char *mapfile, t_env *wolf, int fd)
{
	char	*line;
	
	line = NULL;
	if (get_next_line(fd, &line) != 1)
	{
		ft_putendl_fd("file is empty", 2);
		free(line);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_map(char *mapfile, t_env *wolf)
{
	int		fd;

	if ((fd = open(mapfile, O_RDONLY)) < 0)
	{
		perror("Error during open() ");
		exit(EXIT_FAILURE);
	}
	ft_fill_map(mapfile, wolf, fd);
	if (close(fd) < 0)
	{
		perror("Error during close() ");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_env(t_env *wolf)
{
	wolf->window = NULL;
	wolf->renderer = NULL;
	wolf->texture = NULL;
	wolf->format = NULL;
	//wolf->event = NULL;
	wolf->width = WIDTH;
	wolf->height = HEIGHT;
	wolf->mapdata.nbcol = 0;
	wolf->mapdata.nbl = 0;
	wolf->mapdata.map = NULL;
}

void	ft_wolf3d(char *mapfile)
{
	t_env	wolf;

	ft_init_env(&wolf);
	ft_init_map(mapfile, &wolf);
	ft_sdl(&wolf);
}
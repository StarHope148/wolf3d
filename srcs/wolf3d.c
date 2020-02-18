/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:57:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/02/18 16:53:59 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char		**ft_malloc_tab(t_env *wolf)
{
	char	**tab;
	int			i;

	if ((tab = (char **)malloc(sizeof(char *)
			* wolf->mapdata.nbl)) == NULL)
		return (NULL);
	i = 0;
	while (i < wolf->mapdata.nbl)
	{
		if ((tab[i] = (char *)malloc(sizeof(char)
				* wolf->mapdata.nbcol)) == NULL)
			return (NULL);
		i++;
	}
	return (tab);
}

int		ft_retrieve_data(t_env *wolf, char *line)
{
	if (wolf->mapdata.map == NULL)
		if ((wolf->mapdata.map = ft_malloc_tab(wolf)) == NULL)
			return (-1);
	ft_strcpy(wolf->mapdata.map[wolf->mapdata.cur_line], line);
	wolf->mapdata.map[wolf->mapdata.cur_line][ft_strlen(line)] = '\0';
	wolf->mapdata.cur_line++;
	return (0);
}

int		ft_check_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '.' && line[i] != '#')
			return (-1);
		i++;
	}
	return (0);
}

void	ft_fill_map(t_env *wolf, int fd)
{
	char	*line;
	char	ret;

	line = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_check_line(line) == -1)
		{
			ft_putendl_fd("map format is invalid", 2);
			/* while (*(wolf->mapdata.map))
				free(*(wolf->mapdata.map)++);
			if (wolf->mapdata.map != NULL)
				free(wolf->mapdata.map); */
			free(line);
			exit(EXIT_FAILURE);
		}
		if (ft_retrieve_data(wolf, line) == -1)
		{
			ft_putendl_fd("error during malloc of map", 2);
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
	}
	if (ret != 1 && wolf->mapdata.nbl == 0)
	{
		ft_putendl_fd("reading map error", 2);
		free(line);
		exit(EXIT_FAILURE);
	}

	//DEBUG MAP DISPLAY
	int i = 0;
	printf("map_nbl = %d\tmap_nbcol = %d\n", wolf->mapdata.nbl, wolf->mapdata.nbcol);
	while (i < wolf->mapdata.nbl)
	{
		printf("map[%d] =\t%s\n", i, wolf->mapdata.map[i]);
		i++;
	}
}

void	ft_count_lines_columns(t_env *wolf, char *mapfile)
{
	char		*line;
	int			fd;

	fd = 0;
	if ((fd = open(mapfile, O_RDONLY)) < 0)
	{
		perror("Error during open() ");
		exit(EXIT_FAILURE);
	}
	if ((get_next_line(fd, &line)) <= 0)
	{
		ft_putendl_fd("map is empty", 2);
		free(line);
		exit(EXIT_FAILURE);
	}
	wolf->mapdata.nbcol = ft_strlen(line);
	free(line);
	wolf->mapdata.nbl++;
	while (get_next_line(fd, &line) > 0)
	{
		wolf->mapdata.nbl++;
		free(line);
	}
	if (close(fd) < 0)
	{
		perror("Error during close() ");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_map(char *mapfile, t_env *wolf)
{
	int		fd;

	ft_count_lines_columns(wolf, mapfile);
	if ((fd = open(mapfile, O_RDONLY)) < 0)
	{
		perror("Error during open() ");
		exit(EXIT_FAILURE);
	}
	ft_fill_map(wolf, fd);
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
	wolf->pixels = NULL;

	wolf->mapdata.nbcol = 0;
	wolf->mapdata.nbl = 0;
	wolf->mapdata.cur_line = 0;
	wolf->mapdata.map = NULL;

	wolf->cam.pos_x = 1.5;
	wolf->cam.pos_y = 7.5;
	wolf->cam.dir_x = -1;
	wolf->cam.dir_y = 0;
	wolf->cam.angle = 0;
	wolf->cam.fov = PI / 2;
	wolf->cam.plane_x = 0;
	wolf->cam.plane_y = 1;
	wolf->cam.strafe_left = 0;
	wolf->cam.strafe_right = 0;
	wolf->cam.forward = 0;
	wolf->cam.backward = 0;
	wolf->cam.rotate_left = 0;
	wolf->cam.rotate_right = 0;
}

void	ft_wolf3d(char *mapfile)
{
	t_env	wolf;

	ft_init_env(&wolf);
	ft_init_map(mapfile, &wolf);
	ft_sdl(&wolf);
}
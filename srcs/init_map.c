/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:01:07 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/21 12:02:02 by jcanteau         ###   ########.fr       */
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

int		ft_check_borders(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '#')
			return (-1);
		i++;
	}
	return (0);
}

int		ft_check_line(char *line)
{
	int		i;

	i = 0;
	if (line[i++] != '#')
		return(-2);
	while (line[i])
	{
		if (line[i] != '.' && line[i] != '#')
			return (-1);
		i++;
	}
	if (line[--i] != '#')
		return(-2);
	return (0);
}

void	ft_fill_map(t_env *wolf, int fd)
{
	char	*line;
	char	ret;
	int		i;

	line = NULL;
	i = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_check_line(line) < 0 || i++ == 0 || i == wolf->mapdata.nbl)
		{
			if (ft_check_line(line) == -1)
			{
				ft_putendl_fd("map format is invalid", 2);
				free(line);
				exit(EXIT_FAILURE);
			}
			if ((ft_check_line(line) == -2) || (ft_check_borders(line) == -1))
			{
				ft_putendl_fd("Your map is missing borders, BUILD THAT WALL", 2);
				free(line);
				exit(EXIT_FAILURE);
			}
			/* while (*(wolf->mapdata.map))
				free(*(wolf->mapdata.map)++);
			if (wolf->mapdata.map != NULL)
				free(wolf->mapdata.map); */
		}
		if (ft_retrieve_data(wolf, line) == -1)
		{
			ft_putendl_fd("error during malloc of map", 2);
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
	}
	if (wolf->mapdata.nbl < 3 || wolf->mapdata.nbcol < 3)
	{
		ft_putendl_fd("wrong map format", 2);
	//	if (line) 
	//		free(line);
		exit(EXIT_FAILURE);
	}

	//DEBUG MAP DISPLAY
	i = 0;
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
	int			i;


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
		i = ft_strlen(line);
		if (wolf->mapdata.nbcol != i)
		{
			free(line);
			write(1, "Please use a rectangle map\n", 28);
			close(fd);
			exit(EXIT_FAILURE);
		}
		wolf->mapdata.nbl++;
		free(line);
	}
	if (close(fd) < 0)
	{
		perror("Error during close() ");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_map(t_env *wolf, char *mapfile)
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
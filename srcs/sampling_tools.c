/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:05:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/24 21:21:25 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_free_map(t_env *wolf)
{
	int i;

	i = 0;
	while (i < wolf->mapdata.nbl && wolf->mapdata.map[i] != NULL)
	{
		free(wolf->mapdata.map[i]);
		wolf->mapdata.map[i] = NULL;
		i++;
	}
	free(wolf->mapdata.map);
	wolf->mapdata.map = NULL;
}

void	ft_west_face(t_env *wolf)
{
	wolf->calc.sample_x = wolf->calc.test_point_y -
							(double)wolf->raycast.test_y - 1;
	wolf->orientation = WEST;
}

void	ft_north_face(t_env *wolf)
{
	wolf->calc.sample_x = wolf->calc.test_point_x -
							(double)wolf->raycast.test_x;
	wolf->orientation = NORTH;
}

void	ft_south_face(t_env *wolf)
{
	wolf->calc.sample_x = wolf->calc.test_point_x -
							(double)wolf->raycast.test_x - 1;
	wolf->orientation = SOUTH;
}

void	ft_east_face(t_env *wolf)
{
	wolf->calc.sample_x = wolf->calc.test_point_y -
							(double)wolf->raycast.test_y;
	wolf->orientation = EAST;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:57:29 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/07 16:52:21 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_init_env(t_env *wolf)
{
	wolf->win_ptr = NULL;
	wolf->img_ptr = NULL;
	wolf->data = NULL;
	wolf->width = WIDTH;
	wolf->height = HEIGHT;
	wolf->bpp = 0;
	wolf->size_l = 0;
	wolf->endian = 0;
}

int		ft_wolf3d(char *mapfile)
{
	t_env	wolf;
	
	ft_init_env(&wolf);
	(void)mapfile;
	if (ft_mlx(&wolf) == -1)
		return (-1);
	return (0);
}
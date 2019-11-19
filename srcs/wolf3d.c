/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:57:29 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/19 16:20:06 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_init_env(t_env *wolf)
{
	wolf->window = NULL;
	wolf->renderer = NULL;
	wolf->texture = NULL;
	wolf->format = NULL;
	//wolf->event = 0;
	wolf->width = WIDTH;
	wolf->height = HEIGHT;
}

void	ft_wolf3d(char *mapfile)
{
	t_env	wolf;
	
	ft_init_env(&wolf);
	(void)mapfile;
	ft_sdl(&wolf);
}
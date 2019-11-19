/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/19 14:48:02 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_exit(t_env *wolf)
{
	(void)wolf;
	//mlx_destroy_image(wolf->mlx_ptr, wolf->img_ptr);
	//mlx_destroy_window(wolf->mlx_ptr, wolf->win_ptr);
	exit(EXIT_SUCCESS);
}

int		ft_key_hook(int keycode, t_env *wolf)
{
	if (keycode == ESC)
		ft_exit(wolf);


	/* if (ft_print(wolf) == -1)
		return (-1); */
	return (0);
}

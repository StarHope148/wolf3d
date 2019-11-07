/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/07 16:52:47 by jcanteau         ###   ########.fr       */
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
	/* else if (keycode == MORE || keycode == LESS)
		ft_iteration(wolf, keycode);
	else if (keycode == UP_ARROW || keycode == DOWN_ARROW
			|| keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
		ft_move(wolf, keycode);
	else if (keycode == ONE_NUM_PAD || keycode == TWO_NUM_PAD)
		ft_zoom(wolf, keycode);
	else if (keycode == THREE_NUM_PAD)
		ft_switch_color(wolf);
	else if (keycode == ZERO_NUM_PAD)
		ft_default(wolf);
	else if (keycode == FIVE_NUM_PAD)
		ft_switch_fractal(wolf); */

	/* if (ft_print(wolf) == -1)
		return (-1); */
	return (0);
}

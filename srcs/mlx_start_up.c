/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/07 11:26:27 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				ft_mlx(t_env *frct)
{
	if ((frct->mlx_ptr = mlx_init()) == NULL)
		return (-1);
	frct->win_ptr = mlx_new_window(frct->mlx_ptr, frct->width,
									frct->height, "WOLF3D");
	if (frct->win_ptr == NULL)
		return (-1);
	if (ft_print(frct) == -1)
		return (-1);
	mlx_hook(frct->win_ptr, 2, 0, ft_key_hook, frct);
	mlx_mouse_hook(frct->win_ptr, ft_mouse_hook, frct);
	mlx_hook(frct->win_ptr, 6, 1, ft_mouse_motion, frct);
	mlx_loop(frct->mlx_ptr);
	return (0);
}

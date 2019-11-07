/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:29 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/07 16:57:32 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				ft_mlx(t_env *wolf)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) != 0)
		return (-1);
	wolf->win_ptr = SDL_CreateWindow("WOLF3D", 0, 0, wolf->width, wolf->height, 0);
	if (wolf->win_ptr == NULL)
		return (-1);
	/* if (ft_print(wolf) == -1)
		return (-1); */
	//mlx_hook(wolf->win_ptr, 2, 0, ft_key_hook, wolf);
	//mlx_mouse_hook(wolf->win_ptr, ft_mouse_hook, wolf);
	//mlx_hook(wolf->win_ptr, 6, 1, ft_mouse_motion, wolf);
	//mlx_loop(wolf->mlx_ptr);
	SDL_WaitEvent(wolf->event);
	SDL_DestroyWindow(wolf->win_ptr);
	SDL_Quit();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/19 17:05:06 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_key_hook(t_env *wolf)
{
	while (1)
	{
    	SDL_PollEvent(&wolf->event);
		if (wolf->event.type == SDL_KEYDOWN)
		{
			if (wolf->event.key.keysym.sym == SDLK_ESCAPE)
			{
				ft_exit(wolf, EXIT_SUCCESS);
				break;
			}
			else
				printf("keycode = %d\n", wolf->event.key.keysym.sym);
		}
		else if (wolf->event.type == SDL_QUIT)
		{
			ft_exit(wolf, EXIT_SUCCESS);
			break;
		}
	}
}

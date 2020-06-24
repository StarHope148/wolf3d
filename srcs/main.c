/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:53:23 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/24 21:33:17 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_usage(void)
{
	ft_putendl_fd("usage: ./wolf3d [file.map]", 2);
	return (EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return (ft_usage());
	ft_wolf3d(av[1]);
	return (0);
}

/*
**int		main(int ac, char **av)
**{
**	(void)ac;
**	(void)av;
**
**	SDL_Init(SDL_INIT_VIDEO);
**	SDL_Quit();
**	return (0);
**}
*/

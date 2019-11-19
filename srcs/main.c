/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:53:23 by jcanteau          #+#    #+#             */
/*   Updated: 2019/11/19 16:19:44 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		ft_error(void)
{
	ft_putendl_fd("an error occured", 2);
	return (EXIT_FAILURE);
}

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

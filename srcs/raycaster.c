/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:51:13 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/23 21:03:12 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    ft_casting_ray(t_env *wolf)
{
    wolf->raycast.distance_towall += wolf->precision;
    wolf->raycast.shading -= RAY_LENGHT * SHADING_DEPTH;
    if (wolf->raycast.shading < 0)
        wolf->raycast.shading = 0;
    wolf->raycast.test_x = (int)(wolf->cam.pos_x +
                            wolf->raycast.eye_x *
                            wolf->raycast.distance_towall);
    wolf->raycast.test_y = (int)(wolf->cam.pos_y +
                            wolf->raycast.eye_y *
                            wolf->raycast.distance_towall);
    if (wolf->raycast.test_x < 0 ||
            wolf->raycast.test_x >= wolf->mapdata.nbcol ||
            wolf->raycast.test_y < 0 ||
            wolf->raycast.test_y >= wolf->mapdata.nbl)
    {
        wolf->raycast.hit_wall = 1;
        wolf->raycast.distance_towall = MAX_DEPTH;
    }
    else if (wolf->mapdata.map[wolf->raycast.test_y]
                                [wolf->raycast.test_x] == WALL)
        wolf->raycast.hit_wall = 1;

    //Check if there is no # a bit before the end of the ray casted
    /* double TestX_before;
    double	TestY_before;
    double before;
    int hitbefore;

    before = 0.1;
    int inc = 0;
    hitbefore = 0;
    TestX_before = wolf->raycast.test_x;
    TestY_before = wolf->raycast.test_y;
    while (hitbefore == 0 && wolf->raycast.distance_towall > 0)
    {
        TestX_before -= before;
        TestY_before -= before;

        if (wolf->mapdata.map[(int)TestY_before][(int)TestX_before] == WALL)
        {
            wolf->raycast.distance_towall *= before * inc;
            hitbefore = 1;
        }
    } */
}

void    ft_set_new_ray_angle(t_env *wolf)
{
    wolf->raycast.ray_angle = (wolf->cam.angle + wolf->cam.fov / 2.0) -
							((double)wolf->raycast.x_render / (double)WIDTH) *
							wolf->cam.fov;
    wolf->raycast.distance_towall = 0;
    wolf->raycast.hit_wall = 0;
    wolf->raycast.shading = 1;
    wolf->raycast.eye_x = sin(wolf->raycast.ray_angle);
    wolf->raycast.eye_y = cos(wolf->raycast.ray_angle);
}

void	ft_raycaster(t_env *wolf)
{
	wolf->raycast.x_render = 0;
	while (wolf->raycast.x_render < WIDTH)
	{
		ft_set_new_ray_angle(wolf);
		while (wolf->raycast.hit_wall == 0 &&
				wolf->raycast.distance_towall < MAX_DEPTH)
			ft_casting_ray(wolf);
		ft_calc_sampling_x(wolf);
        ft_fix_fisheye_distorsion(wolf);
        ft_set_ceiling_floor(wolf);
		wolf->raycast.y_render = 0;
		while (wolf->raycast.y_render < HEIGHT)
		{
            if (wolf->raycast.y_render < wolf->ceiling) // UP
                ft_draw_ceiling(wolf);
			else if (wolf->raycast.y_render >= wolf->ceiling &&
                    wolf->raycast.y_render <= wolf->floor) // WALL
                ft_draw_wall(wolf);
			else  //DOWN
                ft_draw_floor(wolf);
			wolf->raycast.y_render++;
		}
		wolf->raycast.x_render++;
	}
}
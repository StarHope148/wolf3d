/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:14:42 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/23 21:19:28 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    ft_fix_fisheye_distorsion(t_env *wolf)
{
	wolf->raycast.distance_towall *= cos(wolf->cam.angle -
                                            wolf->raycast.ray_angle);
}

void    ft_set_ceiling_floor(t_env *wolf)
{
    wolf->ceiling = (double)(HEIGHT / 2) - (double)HEIGHT /
                    wolf->raycast.distance_towall * WALL_SIZE;
	wolf->floor = HEIGHT - wolf->ceiling;
}

void    ft_draw_ceiling(t_env *wolf)
{
    wolf->screen_pixels[wolf->raycast.y_render *
                        WIDTH + wolf->raycast.x_render] = DODGER_BLUE;
}

void    ft_draw_wall(t_env *wolf)
{
    if (wolf->switch_textures == TEXTURED)
    {
        wolf->calc.sample_y = ((double)wolf->raycast.y_render -
                                (double)wolf->ceiling) /
                                ((double)wolf->floor - (double)wolf->ceiling);
        wolf->calc.sample_y = fabs(wolf->calc.sample_y - (int)wolf->calc.sample_y);
        if (wolf->orientation == NORTH)
            ft_apply_north_texture(wolf);
        else if (wolf->orientation == SOUTH)
            ft_apply_south_texture(wolf);
        else if (wolf->orientation == EAST)
            ft_apply_east_texture(wolf);
        else if (wolf->orientation == WEST)
            ft_apply_west_texture(wolf);
    }
    else if (wolf->switch_textures == COLOR_ORIENTED)
    {
        if (wolf->orientation == NORTH)
            wolf->screen_pixels[wolf->raycast.y_render *
                WIDTH + wolf->raycast.x_render] = RED;
        else if (wolf->orientation == SOUTH)
            wolf->screen_pixels[wolf->raycast.y_render *
                WIDTH + wolf->raycast.x_render] = BLUE;
        else if (wolf->orientation == EAST)
            wolf->screen_pixels[wolf->raycast.y_render *
                WIDTH + wolf->raycast.x_render] = YELLOW;
        else if (wolf->orientation == WEST)
            wolf->screen_pixels[wolf->raycast.y_render *
                WIDTH + wolf->raycast.x_render] = PURPLE;
    }
    else if (wolf->switch_textures == SHADED)
        wolf->screen_pixels[wolf->raycast.y_render *
            WIDTH + wolf->raycast.x_render] =
                rgba_to_uint32(255 * wolf->raycast.shading,
                255 * wolf->raycast.shading, 255 * wolf->raycast.shading, 0);
    
    else
        wolf->screen_pixels[wolf->raycast.y_render *
            WIDTH + wolf->raycast.x_render] = WHITE;
}

void    ft_draw_floor(t_env *wolf)
{
	wolf->screen_pixels[wolf->raycast.y_render * WIDTH +
        wolf->raycast.x_render] = rgba_to_uint32(0,
                                                255 *
                                                ((wolf->raycast.y_render -
                                                HEIGHT * 0.5) /
                                                HEIGHT),
                                                0,
                                                0);
}
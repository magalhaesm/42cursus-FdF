/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:09:12 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/25 17:47:35 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define SIN_30 0.500000
#define COS_30 0.866025

static void	set_point(t_point *p, int row, int col, t_scene scene);
static void	isometric(t_point *p);

void	scene_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT, "Fil de Fer");
	data->canvas.img_ptr = mlx_new_image(data->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT);
	data->canvas.addr = mlx_get_data_addr(data->canvas.img_ptr, \
		&data->canvas.bpp, &data->canvas.line_len, &data->canvas.endian);
	// render_background(&data->canvas, CANVAS_BG);
}

void	render_scene(t_data *data)
{
	int		col;
	int		row;
	t_point	p1;
	t_point	p2;

	row = -1;
	while (++row < data->scene.rows)
	{
		col = -1;
		while (++col < data->scene.cols)
		{
			if (col + 1 < data->scene.cols)
			{
				set_point(&p1, row, col + 1, data->scene);
				set_point(&p2, row, col, data->scene);
				draw_line(&data->canvas, p1, p2, GRID);
			}
			if (row + 1 < data->scene.rows)
			{
				set_point(&p1, row + 1, col, data->scene);
				set_point(&p2, row, col, data->scene);
				draw_line(&data->canvas, p1, p2, GRID);
			}
		}
	}
}

static void	set_point(t_point *p, int row, int col, t_scene scene)
{
	p->x = col * scene.scale - scene.scaled_col;
	p->y = row * scene.scale - scene.scaled_row;
	p->z = scene.map[row][col].z * scene.scale * 0.3;
	isometric(p);
	p->x += scene.mid_width;
	p->y += scene.mid_height;
}

static void	isometric(t_point *p)
{
	int	temp_x;

	temp_x = p->x;
	p->x = (temp_x - p->y) * COS_30;
	p->y = (temp_x + p->y) * SIN_30 - p->z;
}

int	get_scale(int row, int col)
{
	int	scale;
	int	area;

	area = WINDOW_WIDTH * WINDOW_HEIGHT / 4;
	scale = area / (row * col);
	scale = sqrt(scale);
	if (scale < 2)
		return (2);
	return (scale);
}

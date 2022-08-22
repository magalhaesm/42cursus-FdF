/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:05:45 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/22 15:17:42 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define MLX_ERROR 1

int	encode_rgb(t_byte red, t_byte green, t_byte blue)
{
	return (red << 16 | green << 8 | blue);
}

int	quit(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_image(data->mlx_ptr, data->canvas.img_ptr);
		mlx_loop_end(data->mlx_ptr);
	}
	ft_printf("Pressionada tecla: %d\n", keysym);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	load_map(&data.scene, argv[1]);
	data.scene.scale = get_scale(data.scene.rows, data.scene.cols);
	data.cache.scaled_col = (data.scene.cols * data.scene.scale) / 2;
	data.cache.scaled_row = (data.scene.rows * data.scene.scale) / 2;
	data.cache.mid_width = WINDOW_WIDTH / 2;
	data.cache.mid_height = WINDOW_HEIGHT / 2;

	scene_init(&data);

	render_scene(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr,
		data.canvas.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, quit, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free_map(&data.scene);
	free(data.mlx_ptr);
	return (EXIT_SUCCESS);
}

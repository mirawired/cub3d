/* ************************************************************************** */
/*                                                4                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:50:13 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/15 23:50:48 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"

// void fill_array_from_file(t_raydata *raydata, const char *filename) {
//     int fd = open(filename, O_RDONLY);
//     char buffer[BUFFER_SIZE];
//     int len;

//     if (fd == -1) {
//         printf("Failed to open file %s\n", filename);
//         return;
//     }


//     char* lines[GRID_HEIGHT];
//     int i = 0, lineCount = 0;
//     while ((len = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
//         buffer[len] = '\0';
//         char *line = strtok(buffer, "\n");

//         while (line) {
//             lines[lineCount] = malloc(strlen(line) + 1);
//             strcpy(lines[lineCount], line);
//             lineCount++;
//             line = strtok(NULL, "\n");
//         }
//     }

//     for (i = 0; i < lineCount; i++) {
//         char *num = strtok(lines[i], ",");
//         int j = 0;
//         while (num) {
//             raydata->map[i][j] = atoi(num);
//             j++;
//             num = strtok(NULL, ",");
//         }
//         free(lines[i]);
//     }
//     for (int k = 0; k < GRID_HEIGHT; k++) {
//         for (int l = 0; l < GRID_WIDTH; l++) {
//             printf("%d ", raydata->map[k][l]);
//         }
//         printf("\n");
//     }
//     close(fd);
// }

// void    grab_arg(t_raydata *raydata, t_arg *arg)
// {

// }

int raycast(t_data *data, t_arg *arg)
{
	(void)data;
	(void)arg;
	t_raydata *raydata;

	raydata = malloc(sizeof (t_raydata));
	if (!raydata)
		return (1);
	raydata->img_buffer = malloc(sizeof(t_buffer));
	if (!raydata->img_buffer)
		return (1);
	raydata->mlx = mlx_init();
	raydata->mlx_win = mlx_new_window(raydata->mlx,TWIDTH,HEIGHT,"RAYCAST");
	raydata->img_buffer->img = mlx_new_image(raydata->mlx,
										  TWIDTH +  1,
										  HEIGHT + 1);
	raydata->img_buffer->address = mlx_get_data_addr(raydata->img_buffer->img,
												  &raydata->img_buffer->bit_per_pixel,
												  &raydata->img_buffer->line_length,
												  &raydata->img_buffer->endian);
    // fill_array_from_file(raydata, "map.txt");
    // grab_args(raydata, arg);
    raydata->player = malloc(sizeof (t_player));
	raydata->player->pos.x = (double)HEIGHT /2;
	raydata->player->pos.y = (double) WIDTH /2;
    raydata->player->angle = 0;
    raydata->player->size = 10;
    raydata->player->fov = 60;
//	printf("brick hitbox start x: %f end x: %f start y: %f end y: %f",raydata->brick_hitbox.start_x,raydata->brick_hitbox.end_x,raydata->brick_hitbox.start_y,raydata->brick_hitbox.end_y);
	mlx_hook(raydata->mlx_win, 2, 1L << 0, key_pressed, raydata);
	mlx_loop_hook(raydata->mlx,render,raydata);
	mlx_loop(raydata->mlx);
//	mlx_destroy_image(raydata->mlx,raydata->img_buffer->img);
//	free(raydata->img_buffer);
//	mlx_destroy_window(raydata->mlx,raydata->mlx_win);
//	mlx_destroy_display(raydata->mlx);
//	free(raydata->mlx);
//	free(raydata);
	return (0);
}

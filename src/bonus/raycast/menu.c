//
// Created by corecaps on 10/8/23.
//

#include "../../../inc/cub3d.h"
void draw_menu(t_raydata * raydata) {
	static int width = 0;
	static int height = 0;

	if (raydata->img_menu == NULL) {
		raydata->img_menu = gc_alloc(1, sizeof(t_buffer ));
		raydata->img_menu->img = mlx_xpm_file_to_image(raydata->mlx,
													   "menu.xpm",
													   &width ,
													   &height);
		raydata->img_menu->address = mlx_get_data_addr(raydata->img_menu->img,
													  &raydata->img_menu->bit_per_pixel,
													  &raydata->img_menu->line_length,
													  &raydata->img_menu->endian);
	}
	else {
		mlx_put_image_to_window(raydata->mlx,
								raydata->mlx_win,
								raydata->img_menu->img,
								0, 0);
	}
}
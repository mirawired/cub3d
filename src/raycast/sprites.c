#include "./../../inc/raycast.h"

void	sort_sprites(t_spr	*spr)
{
	int	i;
	int	tmp;
	i = 1;

	while (i < SPRITENBR)
	{
		if (spr->spride_dist[i] > spr->spride_dist[i - 1])
		{
			tmp = spr->spride_dist[i];
			spr->spride_dist[i] = spr->spride_dist[i - 1];
			spr->spride_dist[i - 1] = tmp;
			spr->sprite_order[i] = i - 1;
			spr->sprite_order[i - 1] = i;
			i = 0;
		}
		i++;
	}
}

void	draw_sprites(t_raydata * data, double perpWallDist, t_point pos)
{
        t_spr   *spr = data->spr;
        spr->sprite[0].x = 2.0;
        spr->sprite[0].y = 2.0;
        // spr->sprite[0].texture = data->spr->sprite[0].texture;
        int i = 0;
        // while (i < SPRITENBR)
        // {
        //     spr->sprite_order[i] = i;
        //     spr->spride_dist[i] = ((pos.x - spr->sprite[i].x) * (pos.x - spr->sprite[i].x) + (pos.y - spr->sprite[i].y) * (pos.y - spr->sprite[i].y));
        //      i++;
        // }
        // sort_sprites(spr);

        while (i < SPRITENBR)
        {
            double  spriteX = spr->sprite[0].x - pos.x;
            double  spriteY = spr->sprite[0].y - pos.y;

            double invDet = 1.0 / (data->player->plane_vector.x * data->player->dir_vector.y - data->player->dir_vector.x * data->player->plane_vector.y);
            double transX = invDet * (data->player->dir_vector.y * spriteX - data->player->dir_vector.x * spriteY);
            double transY = invDet * (-data->player->plane_vector.y * spriteX + data->player->plane_vector.x + data->player->plane_vector.x * spriteY);

            int spriteScreenX = (int)((WIDTH / 2) * (1 + transX / transY));
			int vMoveScreen = (int)(0.0 / transY);

			int spriteHeight = ft_abs((int)(HEIGHT / transY)) / 1;
            int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
            if (drawStartY < 0)
                drawStartY = 0;
            int drawEndY = spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
            if (drawEndY >= HEIGHT)
                drawEndY = HEIGHT - 1;

            int spriteWidth = ft_abs((int)(HEIGHT / transY)) / 1;
            int drawStartX = -spriteWidth / 2 + spriteScreenX;
            if (drawStartX < 0)
                drawStartX = 0;
            int drawEndX = spriteWidth / 2 + spriteScreenX;
            if (drawEndX >= WIDTH)
                drawEndX = WIDTH;

            int stripe = drawStartX;
            while (stripe < drawEndX)
            {
				int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
                int y = drawStartY;
				if (transY > 0 && transY < data->spr->Zbuffer[stripe])
				{
					while (y < drawEndY)
					{
						int d = (y - vMoveScreen) * 256 - HEIGHT * 128 + spriteHeight * 128;
						int texY = ((d * 64) / spriteHeight) / 256;
						// t_color color = data.spr.sprite[0].texture[64 * texY + texX];
						t_color color = spr->sprite[0].texture->texture[64 * texY + texX];
						if (color.color != -16777216)
							my_mlx_pixel_put(data->img_buffer, color, (t_int_point) {stripe + OFFSET_3D, y});
						y++;
					}
				}
				stripe++;
			}
			i++;
		}
}

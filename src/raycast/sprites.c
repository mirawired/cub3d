#include "./../../inc/raycast.h"

// void	sort_sprites(t_spr	*spr)
// {
// 	int	i;

// 	i = 0;
// 	while (i < SPRITENBR)
// 	{
// 		spr->sprite[i].
// 	}
// }

void	draw_sprites(t_raydata * data, double perpWallDist, t_point pos)
{
		data->spr = (t_spr *)gc_alloc(1, sizeof(t_spr));
        t_spr   *spr = data->spr;
        spr->sprite[0].x = 1.0;
        spr->sprite[0].y = 1.0;
        spr->sprite[0].texture = data->sprt1;
        spr->Zbuffer[WIDTH] = perpWallDist;
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
            double  spriteX = spr->sprite[spr->sprite_order[i]].x - pos.x;
            double  spriteY = spr->sprite[spr->sprite_order[i]].y - pos.y;

            double invDet = 1.0 / (data->player->plane_vector.x * data->player->dir_vector.y - data->player->dir_vector.x * data->player->plane_vector.y);
            double transX = invDet * (data->player->dir_vector.y * spriteX - data->player->dir_vector.x * spriteY);
            double transY = invDet * (-data->player->plane_vector.y * spriteX + data->player->plane_vector.x + data->player->plane_vector.x * spriteY);

            int spriteScreenX = ((WIDTH / 2) * (1 + transX / transY));

            int spriteHeight = ft_abs((HEIGHT / transY));

            int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
            if (drawStartY < 0)
                drawStartY = 0;
            int drawEndY = spriteHeight / 2 + HEIGHT / 2;
            if (drawEndY >= HEIGHT)
                drawEndY = HEIGHT - 1;

            int spriteWidth = ft_abs(HEIGHT / transY);
            int drawStartX = -spriteWidth / 2 + spriteScreenX;
            if (drawStartX < 0)
                drawStartX = 0;
            int drawEndX = spriteWidth / 2 + spriteScreenX;
            if (drawEndX >= WIDTH)
                drawEndX = WIDTH - 1;

            int stripe = drawStartX;
            while (stripe < drawEndX)
            {
                int y = drawStartY;
                while (y < drawEndY)
                {
                    int d = y * 256 - HEIGHT * 128 + spriteHeight * 128;
                    int texY = ((d * 64) / spriteHeight) / 256;
					// t_color color = data->sprt1->texture->;
					my_mlx_pixel_put(data->img_buffer, color, (t_int_point) {0 + OFFSET_3D, y});
					y++;
                    // if (())
                }
			}
		}
}

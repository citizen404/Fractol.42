/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzmuda <bzmuda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:09:29 by bzmuda            #+#    #+#             */
/*   Updated: 2017/06/05 11:09:31 by bzmuda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Initialize parameters for Julia fractal.
*/

void		init_julia(t_e *e)
{
	e->width = 1000;
	e->height = 1000;
	e->cRe = -0.7;
	e->cIm = 0.27015;
	e->x = 0;
	e->y = 0;
	e->i = 0;
	e->zoom = 1;
	e->movex = 0;
	e->movey = 0;
	e->itmax = 200;
	e->ix = 1;
	e->iy = 1;
	e->indexfrac = 1;
}

/*
**	Calculate, for each iterations
*/

void 	exten_julia(t_e *e)
{
	while (e->i < e->itmax)
	{
		e->oldRe = e->newRe;
		e->oldIm = e->newIm;
		e->newRe = e->oldRe * e->oldRe - e->oldIm * e->oldIm + e->cRe * e->ix;
		e->newIm = 2 * e->oldRe * e->oldIm + e->cIm * e->iy;
		if (((e->newRe * e->newRe) + (e->newIm * e->newIm)) > 4)
			break;
		e->i++;
	}
}

/*
**	Create image of Julia fractal.
*/

void 	draw_julia(t_e *e)
{
	e->indexfrac = 1;
	printf("indexfra : %d\n", e->indexfrac);
	printf("ix : %f\n", e->ix);
	printf("iy : %f\n", e->iy);
	while (e->y < e->height)
	{
		while (e->x < e->width)
		{
			e->newRe = 1.5 * (e->x - e->width / 2) / (0.5 * e->zoom * e->width)
				+ e->movex;
			e->newIm = (e->y - e->height / 2) / (0.5 * e->zoom * e->height)
				+ e->movey;
			exten_julia(e);
			if (e->i == e->itmax)
				pix_to_img(e, e->i * 0);	
			else
				pix_to_img(e, (e->i * 150000));
			e->x++;
			e->i = 0;
		}
		e->x = 0;
		e->y++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->imgptr, 0, 0);
}

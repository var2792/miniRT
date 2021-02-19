#include "belong_to_obj.h"

int	belong_to_sphere(t_general *gen, t_sphere *sp, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	t_list *lstsp;
	int fl;

	fl = 1;
	//1 842 183 // без проверки (первый if)
	//1 483 772 // C-O
	p = sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo);
	k[0] = len_vec(cross_prv(sum_vs(1, sp->cd, -1, gen->scene.cdo), p)) / len_vec(p);
	if (k[0] <= sp->d * 2)
	{
		(*i)++;
		k[0] = dot_prv(p, p);
		k[1] = 2 * dot_prv(sum_vs( 1, gen->scene.cdo, -1, sp->cd), p);
		k[2] = dot_prv(sum_vs( 1, gen->scene.cdo, -1, sp->cd), sum_vs( 1, gen->scene.cdo, -1, sp->cd)) - sp->d * sp->d / 4;
		t[1] = k[1] * k[1] - 4 * k[0] * k[2];
		if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
			fl = 0;
		t[0] = (fl == 0) ? -5 : (-k[1] + sqrt(t[1]))/ 2 / k[0];
		t[1] = (fl == 0) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
		if (t[0] > t[1]) //проверка что t[0] точно меньше t[1]
		{
			k[2] = t[0];
			t[0] = t[1];
			t[1] = k[2];
		}
		if (t[0] >= 1 && fl > 0)
			p = sum_vs(1, gen->scene.cdo, t[0], p);
		else if (t[1] >= 1 && fl > 0)
			p = sum_vs(1, gen->scene.cdo, t[1], p);

		if (fl > 0)
			if (check_see_objs(*gen, p, (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
				fl = 0;

		/*(fl == 1 && z == 0) fun;
		(fl == 1 && z != 0) fun;
		(fl == 0 && z == 0) -5;
		(fl == 0 && z != 0) color;*/
		gen->cl = (fl == 1) ? light_change_sp(*gen, p, *sp, (int)gen->pix.z) : gen->cl;
	}
	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.sp, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_sphere(gen, lstsp->content, i);
	/*if (gen->objs.sp[(int)gen->pix.z].is == 1)
		gen->cl = belong_to_sphere(gen, i);*/

	return (gen->cl);
	(void)i;
}

int		belong_to_plane(t_general *gen, t_plane *pl, int *i)
{
	t_vector p;
	t_list *lstsp;
	float t;

	(*i)++;

	t = dot_prv(pl->nm, pl->cd) - dot_prv(pl->nm, gen->scene.cdo);
	t /= dot_prv(pl->nm, gen->scene.cdv) - dot_prv(pl->nm, gen->scene.cdo);
	if (t >= 1)
	{
		p = sum_vs(1, gen->scene.cdo, t, sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));

		if (!check_see_objs(*gen, p, 100 + (int)gen->pix.z) && (t > 1 && t < 200))
			gen->cl = light_change_pl(*gen, p, *pl, (int)gen->pix.z);
	}
	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.pl, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_plane(gen, lstsp->content, i);
	return (gen->cl);
}

int		belong_to_square(t_general *gen, t_square *sq, int *i)
{
	t_vector p;
	t_list *lstsp;
	float t;

	(*i)++;
	//printf("\nAA\n\n");
	t = dot_prv(sq->nm, sq->cd) - dot_prv(sq->nm, gen->scene.cdo);
	t /= dot_prv(sq->nm, gen->scene.cdv) - dot_prv(sq->nm, gen->scene.cdo);
	p = sum_vs(1, gen->scene.cdo, t, sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));

	if (t >= 1 && point_in_square(*sq, p))
		if (!check_see_objs(*gen, p, 200 + (int)gen->pix.z))
			gen->cl = light_change_sq(*gen, p, *sq, (int)gen->pix.z);

	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.sq, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_square(gen, lstsp->content, i);
	return (gen->cl);
}

int		belong_to_triangle(t_general *gen, t_triangle *tr, int *i)
{
	t_vector p;
	t_list *lstsp;
	float t;

	(*i)++;

	t = dot_prv(tr->nm, tr->cd1) - dot_prv(tr->nm, gen->scene.cdo);
	t /= dot_prv(tr->nm, gen->scene.cdv) - dot_prv(tr->nm, gen->scene.cdo);
	p = sum_vs(1, gen->scene.cdo, t, sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));

	if (t >= 1 && point_in_triangle(*tr, p))
		if (!check_see_objs(*gen, p, 300 + (int)gen->pix.z))
			gen->cl = light_change_tr(*gen, p, *tr, (int)gen->pix.z);

	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.tr, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_triangle(gen, lstsp->content, i);
	return (gen->cl);
}

int		belong_to_cylinder(t_general *gen, t_cylinder *cy, int *i)
{
	float k[3];
	float t[2];
	t_list *lstsp;
	t_vector p;
	int fl;

	fl = 1;
	(*i)++;
	p = sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo); //V-O = V
	k[0] = dot_prv(cross_prv(p, cy->nm), cross_prv(p, cy->nm)); //(Vn,Vn)
	p = sum_vs(1, cross_prv(gen->scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm)); //On-Cn
	k[1] = 2 * dot_prv(cross_prv(sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo), cy->nm), p); // 2(Vn,On-Cn)
	k[2] = dot_prv(p, p) - dot_prv(cy->nm, cy->nm) * cy->d * cy->d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (fabs(k[0]) < 0.01 && fabs(k[1]) < 0.01))
		fl = 0;
	///if (fl > 0) 		printf("%f %f %f\n", k[0], k[1], k[2]);
	if (fabs(k[0]) < 0.01)
	{
		t[0] = (fl == 0) ? -5 : -k[2] / k[1];
		t[1] = -5;
	}
	else
	{
		t[0] = (fl == 0) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
		t[1] = (fl == 0) ? -5 : (-k[1] + sqrt(t[1]))/ 2 / k[0];
	}
	if (t[0] > t[1]) //проверка что t[0] точно меньше t[1]
	{
		k[2] = t[0];
		t[0] = t[1];
		t[1] = k[2];
	}
	if (t[0] > 1 && fl > 0)
	{
		p = sum_vs(1, gen->scene.cdo, t[0], sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));
		if (len_vec(sum_vs(1, p, -1, cy->cd)) <= sqrt(cy->h * cy->h / 4 + cy->d * cy->d / 4))
			fl = 2;
	}
	if (t[1] > 1 && fl > 0 && fl != 2)
	{
		p = sum_vs(1, gen->scene.cdo, t[1], sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));
		if (len_vec(sum_vs(1, p, -1, cy->cd)) <= sqrt(cy->h * cy->h / 4 + cy->d * cy->d / 4))
			fl = 3;
	}

	//if (fl > 1)
		//if (fabs(len_vec(cross_prv(sum_vs(1, p, -1, cy->cd), cy->nm)) / len_vec(cy->nm) - cy->d / 2) < 0.01)
			//printf("%i\t%f %f %f\n", fl, p.x, p.y, p.z);
	fl = belong_to_cyhead0(*gen, *cy, &p, fl);
	fl = belong_to_cyhead1(*gen, *cy, &p, fl);

	if (check_see_objs(*gen, p, 400 + (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
		fl = 0;

	gen->cl = (fl > 1) ? light_change_cy(*gen, p, (int)gen->pix.z, fl) : gen->cl;

	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.cy, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_cylinder(gen, lstsp->content, i);
	return (gen->cl);
	(void)k;
	(void)t;
	(void)p;
}

int		belong_to_cyhead0(t_general gen, t_cylinder cy, t_vector *pcy, int fl)
{
	t_vector p, h;
	float t;

	h = sum_vs(1, cy.cd, - cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	//h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);

	//printf("Cy %f %f %f\n", h.x, h.y, h.z);

	t = dot_prv(cy.nm, h) - dot_prv(cy.nm, gen.scene.cdo);
	t /= dot_prv(cy.nm, gen.scene.cdv) - dot_prv(cy.nm, gen.scene.cdo);
	p = sum_vs(1, gen.scene.cdo, t, sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
	if (t >= 1 && len_vec(sum_vs(1, p, -1, h)) <= cy.d / 2)
		if ((fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, *pcy, -1, gen.scene.cdo))) || fl < 2)
		{
			pcy->x = p.x;
			pcy->y = p.y;
			pcy->z = p.z;
			return (4);
		}
	return (fl);
}

int		belong_to_cyhead1(t_general gen, t_cylinder cy, t_vector *pcy, int fl)
{
	t_vector p, h;
	float t;

	//h = sum_vs(1, cy.cd, - cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);

	//printf("Cy %f %f %f\n", h.x, h.y, h.z);

	t = dot_prv(cy.nm, h) - dot_prv(cy.nm, gen.scene.cdo);
	t /= dot_prv(cy.nm, gen.scene.cdv) - dot_prv(cy.nm, gen.scene.cdo);
	p = sum_vs(1, gen.scene.cdo, t, sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
	if (t >= 1 && len_vec(sum_vs(1, p, -1, h)) <= cy.d / 2)
		if ((fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, *pcy, -1, gen.scene.cdo))) || fl < 2)
		{
			pcy->x = p.x;
			pcy->y = p.y;
			pcy->z = p.z;
			return (4);
		}
	return (fl);
}

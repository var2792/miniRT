#include "check_shadows.h"

float		check_shadow(t_light num_l, int num_ob, t_scobjs objects, t_vector p)
{
	float res, temp;

	res = 1;
	if (num_ob > -1 && num_ob < 100) //sphere
		res = check_shadow_sp(num_l, num_ob, objects, p);
	else
		res = check_shadow_sp(num_l, -1, objects, p);

	if (num_ob > 99 && num_ob < 200) //plane
		res = ((temp = check_shadow_pl(num_l, (int)(num_ob - 100), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_pl(num_l, -1, objects, p)) < res ) ? temp : res;

	if (num_ob > 199 && num_ob < 300) //square
		res = ((temp = check_shadow_sq(num_l, (int)(num_ob - 200), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_sq(num_l, -1, objects, p)) < res ) ? temp : res;

	if (num_ob > 299 && num_ob < 400) //triangle
		res = ((temp = check_shadow_tr(num_l, (int)(num_ob - 300), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_tr(num_l, -1, objects, p)) < res ) ? temp : res;

	if (num_ob > 399 && num_ob < 500) //cylinder
		res = ((temp = check_shadow_cy(num_l, (int)(num_ob - 400), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_cy(num_l, -1, objects, p)) < res ) ? temp : res;

	return (res);
}

float		check_shadow_sp(t_light num_l, int num_sp, t_scobjs objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float k[3];
	float t_n[2];
	int i;
	t_list *temp;
	t_sphere *sp;

	temp = objects.sp;
	i = 0;
	while (temp)
	{
		if (i != num_sp)
		{
			sp = temp->content;
			k[0] = len_vec(cross_prv(sum_vs(1, sp->cd, -1, num_l.cd), sum_vs(1, p, -1, num_l.cd))) / len_vec(sum_vs(1, p, -1, num_l.cd));
			if (k[0] <= sp->d * 2)
			{
				k[0] = dot_prv(sum_vs(1, p, -1, num_l.cd), sum_vs( 1, p, -1, num_l.cd));
				k[1] = 2 * dot_prv(sum_vs(1, num_l.cd, -1, sp->cd), sum_vs( 1, p, -1, num_l.cd));
				k[2] = dot_prv(sum_vs(1, num_l.cd, -1, sp->cd), sum_vs(1, num_l.cd, -1, sp->cd)) - sp->d * sp->d / 4;
				t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
					t_n[1] = (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
					if ((t_n[0] > 0 && t_n[0] < 1) || (t_n[1] > 0 && t_n[1] < 1))
						return (0);
				}
			}
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float		check_orient(t_vector normal, t_vector l, t_vector cor_0, t_vector p)
{
	float alfa;
	t_vector t;

	t = sum_vs(1, p, -1, cor_0);
	alfa = dot_prv(t, normal) / len_vec(t) / len_vec(normal);
	if (alfa < 0)
		normal = sum_vs(0, t, -1, normal);
	t = sum_vs(1, p, -1, l);
	alfa = dot_prv(t, normal) / len_vec(t) / len_vec(normal);
	if (alfa < 0)
		return (0);
	return (1);
}

float		check_shadow_pl(t_light num_l, int num_pl, t_scobjs objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float t1, t2, t;
	int i;
	t_list *temp;
	t_plane *pl;

	temp = objects.pl;
	i = 0;
	while (temp)
	{
		if (i != num_pl)
		{
			pl = temp->content;
			t1 = dot_prv(pl->nm, pl->cd) - dot_prv(pl->nm, num_l.cd);
			t2 = dot_prv(pl->nm, p) - dot_prv(pl->nm, num_l.cd);
			t = t1 / t2;
			if (t >= 0 && t <= 1)
				return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float		check_shadow_sq(t_light num_l, int num_sq, t_scobjs objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float t1, t2;
	int i;
	t_vector t;
	t_list *temp;
	t_square *sq;

	temp = objects.sq;
	i = 0;
	while (temp)
	{
		if (i != num_sq)
		{
			sq = temp->content;
			t1 = dot_prv(sq->nm, sq->cd) - dot_prv(sq->nm, num_l.cd);
			t2 = dot_prv(sq->nm, p) - dot_prv(sq->nm, num_l.cd);
			t1 = t1 / t2;
			t = sum_vs(1, num_l.cd, t1, sum_vs( 1, p, -1, num_l.cd));

			if (point_in_square(*sq, t))
				if (t1 >= 0 && t1 <= 1)
					return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float		check_shadow_tr(t_light num_l, int num_tr, t_scobjs objects, t_vector p)
{
	float t1, t2;
	int i;
	t_vector t;
	t_list *temp;
	t_triangle *tr;

	temp = objects.tr;
	i = 0;
	while (temp)
	{
		if (i != num_tr)
		{
			tr = temp->content;
			t1 = dot_prv(tr->nm, tr->cd1) - dot_prv(tr->nm, num_l.cd);
			t2 = dot_prv(tr->nm, p) - dot_prv(tr->nm, num_l.cd);
			t1 = t1 / t2;
			t = sum_vs(1, num_l.cd, t1, sum_vs( 1, p, -1, num_l.cd));
			if (point_in_triangle(*tr, t))
				if (t1 >= 0 && t1 <= 1)
					return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

int		shadow_cyhead0(t_cylinder cy, t_vector pcy, t_light num_l)
{
	t_vector p, h;
	float t1, t2;

	h = sum_vs(1, cy.cd, - cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	//h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);

	t1 = dot_prv(cy.nm, h) - dot_prv(cy.nm, num_l.cd);
	t2 = dot_prv(cy.nm, pcy) - dot_prv(cy.nm, num_l.cd);
	t1 = t1 / t2;
	p = sum_vs(1, num_l.cd, t1, sum_vs(1, pcy, -1, num_l.cd));
	if (len_vec(sum_vs(1, p, -1, h)) <= cy.d / 2)
		if (len_vec(sum_vs(1, p, -1, num_l.cd)) <= len_vec(sum_vs(1, pcy, -1, num_l.cd)))
		return (1);
	return (0);
}

int		shadow_cyhead1(t_cylinder cy, t_vector pcy, t_light num_l)
{
	t_vector p, h;
	float t1, t2;

	//h = sum_vs(1, cy.cd, - cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);

	t1 = dot_prv(cy.nm, h) - dot_prv(cy.nm, num_l.cd);
	t2 = dot_prv(cy.nm, pcy) - dot_prv(cy.nm, num_l.cd);
	t1 = t1 / t2;
	p = sum_vs(1, num_l.cd, t1, sum_vs(1, pcy, -1, num_l.cd));
	if (len_vec(sum_vs(1, p, -1, h)) <= cy.d / 2)
		if (len_vec(sum_vs(1, p, -1, num_l.cd)) <= len_vec(sum_vs(1, pcy, -1, num_l.cd)))
		return (1);
	return (0);
}

float		check_shadow_cy(t_light num_l, int num_cy, t_scobjs objects, t_vector pt)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float k[3];
	float t_n[2];
	int i;
	t_vector p;
	t_list *temp;
	t_cylinder *cy;

	temp = objects.cy;
	i = 0;
	while (temp)
	{
		if (i != num_cy)
		{
			cy = temp->content;
			//gen->scene.cdv->pt, gen->scene.cdo->objs.l[num_l].cd
			p = cross_prv(sum_vs(1, pt, -1, num_l.cd), cy->nm);
			k[0] = fabs(dot_prv(sum_vs(1, cy->cd, -1, num_l.cd), p) / len_vec(p));
			if (k[0] <= cy->d / 2)
			{
				p = sum_vs(1, pt, -1, num_l.cd);
				k[0] = dot_prv(cross_prv(p, cy->nm), cross_prv(p, cy->nm)); //(Vn,Vn)
				k[1] = 2 * dot_prv(cross_prv(p, cy->nm), sum_vs(1, cross_prv(num_l.cd, cy->nm), -1, cross_prv(cy->cd, cy->nm))); // 2(Vn,On-Cn)
				k[2] = dot_prv(sum_vs(1, cross_prv(num_l.cd, cy->nm), -1, cross_prv(cy->cd, cy->nm)), sum_vs(1, cross_prv(num_l.cd, cy->nm), -1, cross_prv(cy->cd, cy->nm))) - dot_prv(cy->nm, cy->nm) * cy->d * cy->d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
				t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
					t_n[1] = (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
					if ((t_n[0] > 0 && t_n[0] < 1) || (t_n[1] > 0 && t_n[1] < 1))
						return (0);
				}
				if (shadow_cyhead0(*cy, pt, num_l) || shadow_cyhead1(*cy, pt, num_l))
					return (0);
			}
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

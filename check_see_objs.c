# include "check_see_objs.h"

int		check_see_objs(t_general gen, t_vector ptr, int num_ob)
{
	int res;

	res = 0;
	if (num_ob > -1 && num_ob < 100) //sphere
		res = check_see_sp(gen, ptr, num_ob);
	else
		res = check_see_sp(gen, ptr, -1);

	if (num_ob > 99 && num_ob < 200) //plane
		res = (res == 0) ? check_see_pl(gen, ptr, num_ob - 100) : res;
	else
		res = (res == 0) ? check_see_pl(gen, ptr, -1) : res;

	if (num_ob > 199 && num_ob < 300) //square
		res = (res == 0) ? check_see_sq(gen, ptr, num_ob - 200) : res;
	else
		res = (res == 0) ? check_see_sq(gen, ptr, -1) : res;

	if (num_ob > 299 && num_ob < 400) //triangle
		res = (res == 0) ? check_see_tr(gen, ptr, num_ob - 300) : res;
	else
		res = (res == 0) ? check_see_tr(gen, ptr, -1) : res;

	if (num_ob > 399 && num_ob < 500) //cylinder
		res = (res == 0) ? check_see_cy(gen, ptr, num_ob - 400) : res;
	else
		res = (res == 0) ? check_see_cy(gen, ptr, -1) : res;

	return (res);
}

int		check_see_sp(t_general gen, t_vector ptr, int num_sp)
{
	float k[3];
	float t[2];
	int i;
	t_vector p;
	t_list *temp;
	t_sphere *sp;

	i = 0;
	temp = gen.objs.sp;
	while (temp)
	{
		if (i != num_sp)
		{
			sp = temp->content;
			p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
			k[0] = len_vec(cross_prv(sum_vs(1, sp->cd, -1, gen.scene.cdo), p)) / len_vec(p);
			if (k[0] <= sp->d * 2)
			{
				k[0] = dot_prv(p, p);
				k[1] = 2 * dot_prv(sum_vs( 1, gen.scene.cdo, -1, sp->cd), p);
				k[2] = dot_prv(sum_vs( 1, gen.scene.cdo, -1, sp->cd), sum_vs( 1, gen.scene.cdo, -1, sp->cd)) - sp->d * sp->d / 4;
				t[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
					t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
					if ((t[0] < 0 || t[1] <= t[0]))
						p = sum_vs(1, gen.scene.cdo, t[1], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
					else
					{
						p = sum_vs(1, gen.scene.cdo, t[0], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
						t[1] = t[0];
					}

					if (t[1] >= 0 && (len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, ptr, -1, gen.scene.cdo))))
						return (1);
				}
			}
		}
		temp = temp->next;
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

int		check_see_pl(t_general gen, t_vector ptr, int num_pl)
{
	int i;
	float t;
	t_vector p;
	t_list *temp;
	t_plane *pl;

	i = 0;
	temp = gen.objs.pl;
	while (temp)
	{
		if (i != num_pl)
		{
			pl = temp->content;
			t = dot_prv(pl->nm, pl->cd) - dot_prv(pl->nm, gen.scene.cdo);
			t /= dot_prv(pl->nm, gen.scene.cdv) - dot_prv(pl->nm, gen.scene.cdo);
			p = sum_vs(1, gen.scene.cdo, t, sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
			if ((t >= 1 && t < 200) && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
					return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

int		check_see_sq(t_general gen, t_vector ptr, int num_sq)
{
	int i;
	float t;
	t_vector p;
	t_list *temp;
	t_square *sq;

	i = 0;
	temp = gen.objs.sq;
	while (temp)
	{
		if (i != num_sq)
		{
			sq = temp->content;
			t = dot_prv(sq->nm, sq->cd) - dot_prv(sq->nm, gen.scene.cdo);
			t /= dot_prv(sq->nm, gen.scene.cdv) - dot_prv(sq->nm, gen.scene.cdo);
	//printf("PL %f\n", t);
			p = sum_vs(1, gen.scene.cdo, t, sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
			if (t >= 1 && point_in_square(*sq, p))
				if (len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
					return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

int		check_see_tr(t_general gen, t_vector ptr, int num_tr)
{
	int i;
	float t;
	t_vector p;
	t_list *temp;
	t_triangle *tr;

	i = 0;
	temp = gen.objs.tr;
	while (temp)
	{
		if (i != num_tr)
		{
			tr = temp->content;
			t = dot_prv(tr->nm, tr->cd1) - dot_prv(tr->nm, gen.scene.cdo);
			t /= dot_prv(tr->nm, gen.scene.cdv) - dot_prv(tr->nm, gen.scene.cdo);
	//printf("PL %f\n", t);
			p = sum_vs(1, gen.scene.cdo, t, sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
			if (t >= 1 && point_in_triangle(*tr, p))
				if (len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
					return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

int		check_see_cy(t_general gen, t_vector ptr, int num_cy)
{
	float k[3];
	float t[2];
	int i;
	int fl;
	t_vector p;
	t_list *temp;
	t_cylinder *cy;

	i = 0;
	temp = gen.objs.cy;
	while (temp)
	{
		if (i != num_cy)
		{
			cy = temp->content;
			fl = 1;
			p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
			k[0] = dot_prv(cross_prv(p, cy->nm), cross_prv(p, cy->nm)); //(Vn,Vn)
			k[1] = 2 * dot_prv(cross_prv(p, cy->nm), sum_vs(1, cross_prv(gen.scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm))); // 2(Vn,On-Cn)
			k[2] = dot_prv(sum_vs(1, cross_prv(gen.scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm)), sum_vs(1, cross_prv(gen.scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm))) - dot_prv(cy->nm, cy->nm) * cy->d * cy->d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
			t[1] = k[1] * k[1] - 4 * k[0] * k[2];
			if (!(t[1] < 0 || (k[0] == 0 && k[1] == 0)))
			{
				t[0] = (-k[1] - sqrt(t[1]))/ 2 / k[0];
				t[1] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
				if (t[0] >= 0)
				{
					p = sum_vs(1, gen.scene.cdo, t[0], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
					if (len_vec(sum_vs(1, p, -1, cy->cd)) <= sqrt(cy->h * cy->h / 4 + cy->d * cy->d / 4))
						fl = 2;
				}
				if (t[1] >= 0 && fl != 2)
				{
					p = sum_vs(1, gen.scene.cdo, t[1], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
					if (len_vec(sum_vs(1, p, -1, cy->cd)) <= sqrt(cy->h * cy->h / 4 + cy->d * cy->d / 4))
						fl = 3;
				}
				fl = belong_to_cyhead0(gen, *cy, &p, fl);
				fl = belong_to_cyhead1(gen, *cy, &p, fl);

				if (fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
					return (1);
			}
		}
		temp = temp->next;
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

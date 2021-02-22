#include "../incs/funct_def.h"

float		bright_nl(t_cylinder cy, t_light num_l, t_vector p, int fl)
{
	float bright;
			if (fl != 4)
		{
			bright = -dot_prv(cy.nm, sum_vs(1, cy.cd, -1, p)) / dot_prv(cy.nm, cy.nm);
			if ((bright = dot_prv(sum_vs(-1, p, 1, sum_vs(1, cy.cd, bright, cy.nm)), sum_vs( 1, p, -1, num_l.cd)) / len_vec(sum_vs(-1, p, 1, sum_vs(1, cy.cd, bright, cy.nm))) / len_vec(sum_vs( 1, p, -1, num_l.cd))) < 0)
				bright = 0;
		}
		else
			bright = 20 / len_vec(sum_vs(1, p, -1, num_l.cd));
	return (bright);
}

unsigned int	rescolcy(t_vector cycl, t_vector sum, t_vector acl, float br)
{
	t_vector cl;

	br = (br > 1) ? 1 : br;
	cl = sum_vs(br, sum_vs(0.4, cycl, 0.4, sum), 0.2 * br, acl);
	correct_color(&(cl));
	return(ft_colorvec_unsint(1, cl));
}

int				shadow_cy(t_cylinder *cy, t_light num_l, t_vector pt)
{
	//float k[3];
	float t[2];
	t_vector p;

	p = sum_vs(1, pt, -1, num_l.cd);
	if ((t[1] = find_discr(cross_prv(p, cy->nm), sum_vs(1, cross_prv(num_l.cd, cy->nm), -1, cross_prv(cy->cd, cy->nm)), dot_prv(cy->nm, cy->nm) * cy->d * cy->d / 4, &(t[0]))) > 0)
	{
	// k[0] = dot_prv(cross_prv(p, cy->nm), cross_prv(p, cy->nm)); //(Vn,Vn)
	// k[1] = 2 * dot_prv(cross_prv(p, cy->nm), sum_vs(1, cross_prv(num_l.cd, cy->nm), -1, cross_prv(cy->cd, cy->nm))); // 2(Vn,On-Cn)
	// k[2] = dot_prv(sum_vs(1, cross_prv(num_l.cd, cy->nm), -1, cross_prv(cy->cd, cy->nm)), sum_vs(1, cross_prv(num_l.cd, cy->nm), -1, cross_prv(cy->cd, cy->nm))) - dot_prv(cy->nm, cy->nm) * cy->d * cy->d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
	// t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	// if (!(t[1] < 0 || (k[0] == 0 && k[1] == 0)))
	// {
	// 	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	// 	t[1] = (-k[1] - sqrt(t[1]))/ 2 / k[0];
		if ((t[0] > 0 && t[0] < 1) || (t[1] < 1))
		{
			p = sum_vs(1, num_l.cd, (t[0] > 0 && t[0] < 1) ? t[0] : t[1], sum_vs( 1, pt, -1, num_l.cd));
			if (len_vec(sum_vs(1, p, -1, cy->cd)) <= sqrt(cy->h * cy->h / 4 + cy->d * cy->d / 4))
				return (1);
		}
	}
	return (0);
}

int		see_cy(t_general gen, t_cylinder *cy, t_vector *p)
{
	//float k[3];
	float t[2];
	int fl;

	fl = 1;
	*p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
	if ((t[1] = find_discr(cross_prv(*p, cy->nm), sum_vs(1, cross_prv(gen.scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm)), dot_prv(cy->nm, cy->nm) * cy->d * cy->d / 4, &(t[0]))) < 0.01)
		fl = 0;
	// k[0] = dot_prv(cross_prv(p, cy->nm), cross_prv(p, cy->nm)); //(Vn,Vn)
	// k[1] = 2 * dot_prv(cross_prv(p, cy->nm), sum_vs(1, cross_prv(gen.scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm))); // 2(Vn,On-Cn)
	// k[2] = dot_prv(sum_vs(1, cross_prv(gen.scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm)), sum_vs(1, cross_prv(gen.scene.cdo, cy->nm), -1, cross_prv(cy->cd, cy->nm))) - dot_prv(cy->nm, cy->nm) * cy->d * cy->d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
	// t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	// if (!(t[1] < 0 || (k[0] == 0 && k[1] == 0)))
	// {
	// 	t[0] = (-k[1] - sqrt(t[1]))/ 2 / k[0];
	// 	t[1] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	if (t[0] >= 0 && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[0], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy->cd)) <= sqrt(cy->h * cy->h / 4 + cy->d * cy->d / 4))
			fl = 2;
	}
	if (t[1] >= 0 && fl != 2 && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[1], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy->cd)) <= sqrt(cy->h * cy->h / 4 + cy->d * cy->d / 4))
			fl = 3;
	}
	fl = belong_to_cyhead0(gen, *cy, p, fl);
	fl = belong_to_cyhead1(gen, *cy, p, fl);
	return (fl);
}

int		belong_cy(t_general gen, t_cylinder cy, t_vector *p)
{
	//float k[3];
	float t[2];
	int fl;

	fl = 1;
	if ((t[1] = find_discr(cross_prv(sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo), cy.nm), sum_vs(1, cross_prv(gen.scene.cdo, cy.nm), -1, cross_prv(cy.cd, cy.nm)), dot_prv(cy.nm, cy.nm) * cy.d * cy.d / 4, &(t[0]))) < 1)
	 	fl = 0;
	// p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo); //V-O = V
	// k[0] = dot_prv(cross_prv(p, cy.nm), cross_prv(p, cy.nm)); //(Vn,Vn)
	// p = sum_vs(1, cross_prv(gen.scene.cdo, cy.nm), -1, cross_prv(cy.cd, cy.nm)); //On-Cn
	// k[1] = 2 * dot_prv(cross_prv(sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo), cy.nm), p); // 2(Vn,On-Cn)
	// k[2] = dot_prv(p, p) - dot_prv(cy.nm, cy.nm) * cy.d * cy.d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
	// t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	// if (t[1] < 0 || (fabs(k[0]) < 0.01 && fabs(k[1]) < 0.01))
	// 	fl = 0;
	// ///if (fl > 0) 		printf("%f %f %f\n", k[0], k[1], k[2]);
	// if (fabs(k[0]) < 0.01)
	// {
	// 	t[0] = (fl == 0) ? -5 : -k[2] / k[1];
	// 	t[1] = -5;
	// }
	// else
	// {
	// 	t[0] = (fl == 0) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
	// 	t[1] = (fl == 0) ? -5 : (-k[1] + sqrt(t[1]))/ 2 / k[0];
	// }
	// if (t[0] > t[1]) //проверка что t[0] точно меньше t[1]
	// {
	// 	k[2] = t[0];
	// 	t[0] = t[1];
	// 	t[1] = k[2];
	// }
	if (t[0] > 1 && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[0], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <= sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 2;
	}
	if (t[1] > 1 && fl > 0 && fl != 2)
	{
		*p = sum_vs(1, gen.scene.cdo, t[1], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <= sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 3;
	}
	return (fl);
}

#include "../incs/funct_def.h"

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

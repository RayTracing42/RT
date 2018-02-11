#ifndef EQUATIONS_H
# define EQUATIONS_H
# include "structures.h"

t_dot	equation_get_dot(t_parequation *eq, double t);
int		get_quad_equation_sol(double *res, double fac[4], int i);

#endif

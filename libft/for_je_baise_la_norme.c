/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_je_baise_la_norme.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 21:52:11 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/21 18:32:30 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Ensemble de fct de substitut aux boucles for sans utilisation de pointeur sur
** fonctions, juste à insérer dans une boucle while et roulez jeunesse !
** (sert stt à enlever les parenthèses de mort des boucles while en fait)
** /!\
** - toujours initialiser les vars à incrémenter avant la boucle, le 2e argument
**   sert seulement à la réinitialiser comme son nom l'indique.
**.
** - il faut incrémenter la variable en même temps que le test de la
**   condition d'arrêt, malheureusement c'est pas possible de séparer les 2
**   comme dans une vraie boucle for (j'ai essayé). À part ça c'est comme les
**   vraies on peut mettre tout et n'importe quoi comme condition ça passe.
** /!\
**.
** exemple d'utilisation :
** int i;
** int j;
** int k;
**.
** i = -1;
** j = -1;
** k = -1
** while (forint(&i, -1, ++i < 3))
** 	while (forint(&j, -1, ++j < 3))
** 		while (forint(&k, -1, ++k < 3))
** 			printf("(%d, %d, %d)\n", i, j, k);
**.
** au final on est d'accord ya plus fou comme opti mais chaque ligne est bonne à
** prendre (mine de rien on en a économisé au moins 4 sur l'exemple au dessus).
** Et sinon l'équivalent avec du ternaire c'est ça :
** while (((i = (i < 3 ? i : -1)) || 1) && ++i < 3)
*/

int	forint(int *i, int reset, int cond)
{
	if (!cond)
		*i = reset;
	return (cond);
}

int	fordbl(double *d, double reset, int cond)
{
	if (!cond)
		*d = reset;
	return (cond);
}

int	forptr(void **p, void *reset, int cond)
{
	if (!cond)
		*p = reset;
	return (cond);
}

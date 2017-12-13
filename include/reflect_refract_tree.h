/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_refract_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:06:09 by shiro             #+#    #+#             */
/*   Updated: 2017/12/13 16:07:55 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLECT_REFRACT_TREE_H
# define REFLECT_REFRACT_TREE_H
# include "structures.h"

t_objs_tree	*add_new_leaf(t_objs_tree *root, t_objs_tree **branch, t_object *obj, int lvl);
t_objs_tree	*goto_root_obj(t_objs_tree *leaf, t_object *obj);
void		remove_leaf(t_objs_tree *leaf);

#endif

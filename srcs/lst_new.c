/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:05:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/11 15:07:51 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew(char *name, char *data)
{
	t_env *env;

	if (!(env = malloc(sizeof(*env))))
		return (NULL);
	env->name = name;
    env->data = data;
	env->next = NULL;
	return (env);
}

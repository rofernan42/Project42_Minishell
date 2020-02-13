/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:39:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 14:21:25 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	env_pwd(t_env *env)
{
	t_env *new_tmp;
	t_env *old_tmp;

	new_tmp = ft_envfind(env, "PWD", ft_strcmp);
	old_tmp = ft_envfind(env, "OLDPWD", ft_strcmp);
	free(old_tmp->data);
	old_tmp->data = ft_strdup(new_tmp->data);
	free(new_tmp->data);
	new_tmp->data = getcwd(NULL, 0);
}

void		ft_cd(char *arg, t_env *env)
{
	int	i;
	t_env *tmp;

	if (!arg)
	{
		if (!(tmp = ft_envfind(env, "HOME", ft_strcmp)))
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return ;
		}
		else
			arg = ft_strdup(tmp->data);
	}
	if (chdir(arg) == -1)
		display_error("cd: ", arg, strerror(errno));
	else
		env_pwd(env);
}
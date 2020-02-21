/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 16:04:31 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		status_res(t_shell *shell, int status)
{
	t_env	*tmp;

	tmp = ft_envfind(shell->env, "?", ft_strcmp);
	ft_strdel(&tmp->data);
	tmp->data = ft_strdup(ft_itoa(status));
}

void		fork_args(t_shell *shell, int *pdes, int i)
{
	int		status;
	pid_t	child_right;
	pid_t	child_left;
	int		sl;

	status = -42;
	sl = -42;
	if (!(status = is_builtin(shell, i)))
	{
		if (shell->args && !(child_left = fork()))
			fork_left(shell, pdes);
		if (!(child_right = fork()))
			fork_right(shell, pdes, i);
		close(pdes[1]);
		close(pdes[0]);
		waitpid(child_left, &sl, 0);
		waitpid(child_right, &status, 0);
	}
	status_res(shell, status);
	if (status == 3 || sl == 3)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		//ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	}
	if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 42)
	{
			exit(0);
	}
	if ((WIFEXITED(status) != 0 || status == -42) && i == 0 \
	&& (status != 3 && sl != 3))
	{
		//ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	}
}

void		exec_pipe(t_shell *shell, int i)
{
	int		pdes[2];

	pipe(pdes);
	if (shell->args && !shell->next_args)
	{
		shell->next_args = shell->args;
		shell->args = NULL;
	}
	fork_args(shell, pdes, i);
}

void		ft_stdin(t_shell *shell, char **command)
{
	h_split(shell, command);
	exec_pipe(shell, 0);
}

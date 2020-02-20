/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:16:07 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 13:16:09 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft/libft.h"

void	pop_word(char **s)
{
	int		j;
	int		i;
	char	c;
	int		c1;
	int		c2;

	init_pop_word(&i, &c, &c1, &c2);
	while (s[++i] && (j = -1))
		while (s[i][++j])
			if (c == 0 && s[i][j] == '"' && (c = '"'))
				c1 = j;
			else if (c == '"' && s[i][j] == '"' && !(c = 0))
			{
				c2 = j;
				pop_char(s, i, c1, c2);
				j = j - 2;
			}
			else if (c == 0 && s[i][j] == '\'' && (c = '\''))
				c1 = j;
			else if (c == '\'' && s[i][j] == '\'' && !(c = 0))
			{
				c2 = j;
				pop_char(s, i, c1, c2);
				j = j - 2;
			}
}

char	**ft_reverse(char **s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i][j])
		{
			if (s[i][j] < 0)
				s[i][j] = -1 * s[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	return (s);
}

void	trad(char **s, t_env *env)
{
	int i;

	i = 0;
	while (s[0][i])
	{
		if (s[0][i] == '$' && nb_bs(s[0], i - 1) % 2 == 0 &&
		is_in_s(s[0], i) == 0)
		{
			i = replace(s, i + 1, env);
			if (i == 0)
			{
				s[0][0] = '\0';
				i = 0;
			}
			i--;
		}
		i++;
	}
}

int		contain_c(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_free(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	sig_handle_c(int s)
{
	(void)s;
	ft_putstr_fd("\n\033[33mminishell$\033[0m ", 1);
}

void	sig_handle_b(int s)
{
	(void)s;
}

int		*cp_add(int *t, int p)
{
	int i;
	int *o;

	i = 0;
	o = malloc(sizeof(int) * (p + 1));
	o[p] = -8;
	while (t[i] != -8)
	{
		o[i] = t[i];
		i++;
	}
	while (o[i] != -8)
	{
		o[i] = 0;
		i++;
	}
	free(t);
	return (o);
}
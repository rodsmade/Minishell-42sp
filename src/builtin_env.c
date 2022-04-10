/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:53:54 by afaustin          #+#    #+#             */
/*   Updated: 2022/04/10 23:58:11 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_var(t_env_var *env_var)
{
	ft_putstr_fd(env_var->key, STDOUT_FILENO);
	write(STDOUT_FILENO, "=", 1);
	if (env_var->value)
		ft_putstr_fd(env_var->value, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

void	builtin_env(t_list	*cmd_with_flags)
{
	int		i;
	t_list	*env_var;

	if (cmd_with_flags->next)
	{
		ft_putendl_fd(ft_strjoin_3("env: ‘",
		(char *) cmd_with_flags->next->content,
		"’: No such file or directory"), 2);
		return ;
	}
	i = -1;
	while (++i < TABLE_SIZE)
	{
		env_var = g_tudao.hashtable[i];
		while (env_var != NULL)
		{
			if (((t_env_var *)(env_var->content))->is_env_var == true)
				print_env_var((t_env_var *) env_var->content);
			env_var = env_var->next;
		}
	}
}

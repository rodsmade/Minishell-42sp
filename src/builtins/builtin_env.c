/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:53:54 by afaustin          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
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
		free_and_exit_fork(ft_strjoin_3("env: ‘",
				(char *) cmd_with_flags->next->content,
				"’: No such file or directory"), EXIT_FAILURE);
		return ;
	}
	i = -1;
	while (++i < TABLE_SIZE)
	{
		env_var = g_data.hashtable[i];
		while (env_var != NULL)
		{
			if (((t_env_var *)(env_var->content))->is_env_var == true)
				print_env_var((t_env_var *) env_var->content);
			env_var = env_var->next;
		}
	}
}

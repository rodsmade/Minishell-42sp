/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:15:02 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int		i;
	t_list	*pivot;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		pivot = (*hashtable)[i];
		printf("%d\t: ", i);
		while (pivot != NULL)
		{
			printf("{nome: %s, value: %s}",
				((t_env_var *)(pivot->content))->key,
				((t_env_var *)(pivot->content))->value);
			if (pivot->next != NULL)
				printf(",\n\t  ");
			pivot = pivot->next;
		}
		printf("\n");
	}
	return ;
}

static void	print_command_list(char *str, t_list *lst)
{
	t_list	*pivot;

	pivot = lst;
	printf("\t%s: ", str);
	while (pivot)
	{
		printf("(%s), ", (char *) pivot->content);
		pivot = pivot->next;
	}
	printf("\n");
}

void	print_commands_and_redirects(void)
{
	t_list		*pivot_cmd;
	t_command	*cmd;
	int			i;

	pivot_cmd = g_data.command_table.main_pipeline;
	i = -1;
	while (pivot_cmd)
	{
		cmd = (t_command *) pivot_cmd->content;
		printf("cmd[%i]'s:\n", ++i);
		print_command_list("cmd's with flags", (cmd->cmds_with_flags));
		print_command_list("inputs", (cmd->inputs));
		print_command_list("outputs", (cmd->outputs));
		print_command_list("heredocs", (cmd->heredocs));
		print_command_list("o_concats", (cmd->o_concats));
		pivot_cmd = pivot_cmd->next;
	}
	return ;
}

void	print_token_lst(t_list *lst)
{
	t_list	*pivot;

	pivot = lst;
	printf(">> ");
	while (pivot)
	{
		if (pivot->next)
			printf("{%s} ", (char *)pivot->content);
		else
			printf("{%s}", (char *)pivot->content);
		pivot = pivot->next;
	}
	printf(" <<\n");
}

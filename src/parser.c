/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:58:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/14 13:36:14 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_so_far(void)
{
	t_list *pivot = g_tudao.token_list;

	printf("token list mockada: ");
	while (pivot)
	{
		printf("%s, ", (char *) pivot->content);
		pivot = pivot->next;
	}
	printf("FIM. \n");
}

void	mock_tokens(void)
{
	// ls -l a*|  grep "test"

	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "l\'s\'"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "-l"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "<"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "input.txt"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "a*"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "||"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "grep"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "test"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) ">"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "output.txt"));
	return ;
}

void	free_mock(void)
{
	t_list	*next_el;

	while (g_tudao.token_list->next)
	{
		next_el = g_tudao.token_list->next;
		free(g_tudao.token_list);
		g_tudao.token_list = NULL;
		g_tudao.token_list = next_el;
	}
	free(g_tudao.token_list);
	g_tudao.token_list = NULL;
	return ;
}
/*
while (token && token != '|')
{
	if token = "<" or ">"
		skip two tokens;
	cmd_array = add(token);	// criar função de concatenação de tokens! q faz realloc. 
}
*/

// ATTENTION: uma linha de comando que começa com | (| ls -l) dá erro e isso o parser tem que identificar isso
// por exemplo também ls-l | | grep ou 
// por exemplo também ls-l | | grep ou 
// pode ter mais de um input e mais de um output por comando :smiling_face_with_tear:

int	count_commands(void)
{
	int	cmd_count;
	t_list	*pivot;

	cmd_count = 1;
	pivot = g_tudao.token_list;
	while (pivot)
	{
		if (ft_strncmp((char *) pivot->content, "|", 2) == 0)
			cmd_count++;
		pivot = pivot->next;
	}
	return (cmd_count);
}

void	set_up_command_table(void)
{
	int	cmd_count;

	cmd_count = count_commands();
	printf("commands identified: %d\n", cmd_count);
	
	return ;
}

void	parse_tokens(void)
{
	mock_tokens();
	set_up_command_table();
	// capture_redirect();
	// capture_commands();
	free_mock();
	return ;
}
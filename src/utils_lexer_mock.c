/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_mock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:25:17 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/29 21:34:36 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_so_far(void)
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
	printf("token list mockada: ");
	while (pivot)
	{
		printf("(%p) %s, ", pivot, (char *) pivot->content);
		pivot = pivot->next;
	}
	printf("FIM. \n");
}

void	mock_tokens(void)
{
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "l\'s\'"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "-l"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "<"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "input.txt"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "a*"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "|"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "grep"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "test"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) ">"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "output.txt"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "|"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "grep"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "<"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "input.txt"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "test"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "|"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "grep"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "<"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "input.txt"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "test"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "|"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "grep"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "test"));
	ft_lstadd_back(&(g_tudao.token_list), ft_lstnew((void *) "\n"));
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

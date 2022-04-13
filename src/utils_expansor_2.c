/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:20:55 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/13 19:48:23 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	jump_whitespaces(char* string)
{
	int	i;

	i = -1;
	while (string [++i] && (string[i] == ' ' || string[i] == 't'))
		continue ;
	return (i - 1);
}

static t_list	*create_sublist(char *string)
{
	t_list	*sublist;
	char	*token_content;
	int		i;

	if (!string || string[0] == '\0')
		return (ft_lst_new((void *) NULL));
	sublist = NULL;
	token_content = NULL;
	i = -1;
	while (string[++i])
	{
		if (string[i] && (string[i] != ' ' && string[i] != '\t'))
			token_content = ft_append_char(token_content, string[i]);
		else if (string[i] == ' ' || string[i] == '\t')
		{
			if (token_content)
				ft_lst_add_back(&sublist, ft_lst_new((void *) token_content));
			token_content = NULL;
			i += jump_whitespaces(&string[i]);
		}
	}
	if (token_content)
		ft_lst_add_back(&sublist, ft_lst_new((void *) token_content));
	return (sublist);
}

void	substitute_token_by_sublist(char *expanded_str, t_list **token_address)
{
	t_list	*new_token_sublist;
	t_list	*temp_next;

	if (!*token_address)
		return ;
	temp_next = (*token_address)->next;
	new_token_sublist = create_sublist(expanded_str);

	if (!new_token_sublist)
		return ;

	ft_free_ptr((void *)&(*token_address)->content);
	(*token_address)->content = new_token_sublist->content;
	(*token_address)->next = new_token_sublist->next;

	// FAZER OPERAÇÃO DO UTIMO ELEMENTO
	ft_lst_last(*token_address)->next = temp_next;

	ft_free_ptr((void *)&new_token_sublist);
}

bool	is_expansible(t_list *token)
{
	char	*content;
	int		i;

	content = (char *)token->content;
	i = 0;
	while (content[i])
	{
		if (content[i] && content[i] == '\'')
		{
			i++;
			while (content[i] && content[i] != '\'')
				i++;
		}
		else if (content[i] && content[i] == '\"')
		{
			i++;
			while (content[i] && content[i] != '\"')
			{
				if (content[i] == '$')
					return (true);
				else
					i++;
			}
		}
		else if (content[i] && content[i] == '$')
			return (true);
		if (content[i])
			i++;
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:20:55 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/04 22:41:59 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	jump_whitespaces(char *string)
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
		if (string[i] && !ft_is_blankspace(string[i]))
			token_content = ft_append_char(token_content, string[i]);
		else if (ft_is_blankspace(string[i]))
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
	ft_lst_last(*token_address)->next = temp_next;
	ft_free_ptr((void *)&new_token_sublist);
}

bool	has_wildcard(char* token_content)
{
	int	i;

	i = 0;
	while (token_content[i])
	{
		if (token_content[i] == '\'')
		{
			while (token_content[++i] && token_content[i] != '\'')
				continue ;
			if (token_content[i])
				i++;
		}
		if (token_content[i] == '\"')
		{
			while (token_content[++i] && token_content[i] != '\"')
				continue ;
			if (token_content[i])
				i++;
		}
		if (token_content[i] == '*')
			return (true);
		if (!token_content[i])
			break ;
		i++;
	}
	return (false);
}

bool	is_expandable(char *token_content)
{
	int		i;

	i = 0;
	while (token_content[i])
	{
		if (token_content[i] && token_content[i] == '\'')
		{
			i++;
			while (token_content[i] && token_content[i] != '\'')
				i++;
		}
		else if (token_content[i] && token_content[i] == '\"')
		{
			i++;
			while (token_content[i] && token_content[i] != '\"')
				if (token_content[i++] == '$')
					return (true);
		}
		else if (token_content[i] && (token_content[i] == '$'
				|| ft_strncmp(token_content, "~", 2) == 0))
			return (true);
		if (token_content[i])
			i++;
	}
	return (false || has_wildcard(token_content));
}

void	expand_tilde(t_list *token)
{
	char	*home_to_you;

	if (ft_strncmp((char *) token->content, "~", 2) == 0)
	{
		home_to_you = read_hashtable(g_tudao.hashtable[hash_string("HOME")],
				"HOME");
		ft_free_ptr((void *)&token->content);
		if (home_to_you)
			token->content = (void *) ft_strdup(home_to_you);
		else
			token->content = (void *) ft_strdup(g_tudao.home_at_start);
	}
	return ;
}

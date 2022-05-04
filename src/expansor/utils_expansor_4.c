/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:53:19 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/05 00:03:35 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_wildcard_sublist(char *pattern)
{
	char			*shrunk_pattern;
	t_list			*wildcard_expansion_sublist;
	DIR				*d;
	struct dirent	*dir;

	wildcard_expansion_sublist = NULL;
	shrunk_pattern = shrink_asterisks(pattern);
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (ft_strncmp(dir->d_name, ".", 1) != 0)
				if (matches_pattern(dir->d_name, shrunk_pattern))
					ft_lst_add_back(&wildcard_expansion_sublist,
						ft_lst_new((void *) ft_strdup(dir->d_name)));
			dir = readdir(d);
		}
		closedir(d);
	}
	return (wildcard_expansion_sublist);
}

void	expand_wildcards(t_list **token)
{
	t_list	*curr_next;
	t_list	*substitutions;

	curr_next = (*token)->next;
	substitutions = create_wildcard_sublist((char *)  (*token)->content);
	if (!substitutions)
		return ;
	ft_lst_last(substitutions)->next = curr_next;
	ft_free_ptr((void *)&((*token)->content));
	(*token)->content = substitutions->content;
	(*token)->next = substitutions->next;
	ft_free_ptr((void *)&substitutions);
	// ft_free_ptr((void *)&((*token)->content));
	// ft_free_ptr((void *)&(*token));
	// ft_free_ptr((void *)&(*token));
	// (*token) = substitutions;
	return ;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_expansion_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:13:01 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/09 03:50:31 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unmask_asterisks(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 1)
			str[i] = '*';
	}
	return (1);
}

void	mask_asterisks(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*')
			str[i] = 1;
	}
	return ;
}

void	mask_asterisks_in_quotes(char *pattern)
{
	int	i;

	i = -1;
	while (pattern && pattern[++i])
	{
		if (pattern[i] == '\'')
		{
			while (pattern[++i] && pattern[i] != '\'')
			{
				if (pattern[i] == '*')
					pattern[i] = 1;
			}
		}
		if (pattern[i] == '\"')
		{
			while (pattern[++i] && pattern[i] != '\"')
			{
				if (pattern[i] == '*')
					pattern[i] = 1;
			}
		}
		if (!pattern[i])
			break ;
	}
	return ;
}

t_list	*create_wildcard_sublist(char *pattern)
{
	char			*shrunk_pattern;
	t_list			*wildcard_expansion_sublist;
	DIR				*d;
	struct dirent	*dir;

	wildcard_expansion_sublist = NULL;
	mask_asterisks_in_quotes(pattern);
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
	ft_free_ptr((void *)&shrunk_pattern);
	return (wildcard_expansion_sublist);
}

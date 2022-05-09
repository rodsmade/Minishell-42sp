/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_expansion_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:02:06 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/09 03:30:44 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	sweep_and_search(char *word, char *pattern, size_t n, int *offset)
{
	int	i;

	i = 0;
	if (!word || !pattern)
		return (false);
	while (word[i] && ft_strlen(&word[i]) >= n)
	{
		if (ft_strncmp(&word[i], pattern, n) == 0)
		{
			*offset += (i + n);
			ft_free_ptr((void *)&pattern);
			return (true);
		}
		i++;
	}
	ft_free_ptr((void *)&pattern);
	return (false);
}

bool	matches_pattern(char *str, char *pattern)
{
	int			i;
	int			offsets[2];
	size_t		srch_size;
	char		*substr;

	mask_asterisks(str);
	if (ft_strncmp(pattern, "*", 2) == 0)
		return (true);
	if (!matches_pattern_head_and_tail(str, pattern))
		return (false);
	i = 0;
	offsets[1] = 0;
	while (pattern[i])
	{
		srch_size = 0;
		if (pattern[i] == '*')
			i++;
		offsets[0] = i;
		while (pattern[i] && pattern[i++] != '*')
			srch_size++;
		substr = ft_substr(pattern, offsets[0], srch_size);
		if (!sweep_and_search(&str[offsets[1]], substr, srch_size, &offsets[1]))
			return (false);
	}
	return (true && unmask_asterisks(str));
}

char	*shrink_asterisks(char *pattern)
{
	int		i;
	char	*shrunk_pattern;

	if (!pattern)
		return (NULL);
	shrunk_pattern = NULL;
	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			while (pattern [i] && pattern[i] == '*')
				i++;
			shrunk_pattern = ft_append_char(shrunk_pattern, '*');
		}
		while (pattern[i] && pattern[i] != '*')
			shrunk_pattern = ft_append_char(shrunk_pattern, pattern[i++]);
		if (!pattern[i])
			break ;
	}
	return (shrunk_pattern);
}

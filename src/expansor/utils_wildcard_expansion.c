/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:02:06 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/05 00:15:04 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	matches_pattern_head(char *str, char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i] && pattern[i] != '*')
		i++;
	if (ft_strncmp(str, pattern, i) == 0)
		return (true);
	else
		return (false);
}

bool	matches_pattern_tail(char *str, char *pattern)
{
	int	pattern_end;
	int	n;

	if (!pattern)
		return (false);
	n = 0;
	pattern_end = ft_strlen(pattern);
	while (pattern[--pattern_end] != '*' && pattern_end >= 0)
		n++;
	if (ft_strncmp(&str[ft_strlen(str) - n], &pattern[pattern_end + 1], n) == 0)
		return (true);
	else
		return (false);
}

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
			return (true);
		}
		i++;
	}
	return (false);
}

bool	matches_pattern(char *str, char *pattern)
{
	int			i;
	int			str_offset;
	int			pattern_offset;
	size_t		search_size;
	char		*substring;

	i = 0;
	str_offset = 0;
	pattern_offset = 0;
	search_size = 0;
	if (pattern[i] != '*')
	{
		while (pattern[i] && pattern[i++] != '*')
			search_size++;
		if (!matches_pattern_head(str, pattern))
			return (false);
		str_offset += search_size;
		pattern_offset += search_size;
	}
	while (pattern[i])
	{
		search_size = 0;
		if (pattern[i] == '*')
			i++;
		pattern_offset = i;
		while (pattern[i] && pattern[i++] != '*')
			search_size++;
		substring = ft_substr(pattern, pattern_offset, search_size);
		if (!sweep_and_search(&str[str_offset], substring, search_size, &str_offset))
			return (false);
	}
	if (pattern[ft_strlen(pattern) - 1] != '*')
	{
		if (!matches_pattern_tail(str, pattern))
			return (false);
	}
	return (true);
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

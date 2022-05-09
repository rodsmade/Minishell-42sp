/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_expansion_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:02:06 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/09 03:19:29 by roaraujo         ###   ########.fr       */
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
			ft_free_ptr((void *)&pattern);
			return (true);
		}
		i++;
	}
	ft_free_ptr((void *)&pattern);
	return (false);
}

bool	begins_with_asterisk(char *pattern)
{
	return (pattern[0] == '*');
}

bool	ends_in_asterisk(char *pattern)
{
	return (pattern[ft_strlen(pattern) - 1] == '*');
}

bool	matches_pattern_head_and_tail(char *str, char *pattern)
{
	if (!begins_with_asterisk(pattern) && !matches_pattern_head(str, pattern))
		return (false && unmask_asterisks(str));
	if (!ends_in_asterisk(pattern) && !matches_pattern_tail(str, pattern))
		return (false && unmask_asterisks(str));
	return (true);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_expansion_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 03:29:45 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/09 03:32:01 by roaraujo         ###   ########.fr       */
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

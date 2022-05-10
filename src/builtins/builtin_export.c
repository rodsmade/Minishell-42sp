/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:52:44 by afaustin          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_key(char *line_read, char *key, int *mid_point)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line_read[i] != '=' && line_read[i])
	{
		if (line_read[i] == '\'' || line_read[i] == '\"')
			i++;
		else
		{
			key[j] = line_read[i];
			i++;
			j++;
		}
	}
	*mid_point = i;
	key[j] = '\0';
}

char	*generate_value(char *value)
{
	int		i;
	char	*result;
	char	quote_type;

	i = 0;
	result = ft_strdup("");
	while (value[i] && value[i] != '=')
	{
		if (value[i] == '\'' && value[i] == '\"')
		{
			result = ft_append_char(result, value[i]);
			quote_type = value[i];
			i++;
			while (value[i] && value[i] != quote_type)
			{
				result = ft_append_char(result, value[i]);
				i++;
			}
		}
		else
			result = ft_append_char(result, value[i]);
		if (value[i])
			i++;
	}
	return (result);
}

int	generate_pair(char *line_read, char **pair)
{
	char	*key;
	char	*value;
	int		mid_point;

	mid_point = 0;
	key = (char *)malloc(sizeof(char) * (key_len(line_read) + 1));
	generate_key(line_read, key, &mid_point);
	if (line_read[mid_point] == '=')
	{
		if (line_read[mid_point + 1])
		{
			value = generate_value(&line_read[mid_point + 1]);
			concat_and_free(pair, key, ft_strdup("="), value);
		}
		else
			concat_and_free(pair, key, ft_strdup("="), ft_strdup(""));
		return (1);
	}
	else
	{
		*pair = key;
		return (0);
	}
}

void	iterate_lst_to_export(t_list *lst)
{
	t_list	*pivot;
	char	*pair;

	pivot = lst->next;
	pair = NULL;
	while (pivot != NULL)
	{
		if (is_valid_identifier((char *)pivot->content))
		{
			if (generate_pair((char *)pivot->content, &pair))
				insert_or_update_hashtable(pair, 1, &g_data.hashtable);
			else
				insert_or_update_hashtable(pair, -1, &g_data.hashtable);
			ft_free_ptr((void *)&pair);
		}
		else
		{
			g_data.exit.code = 1;
			g_data.exit.msg = ft_strjoin_3("export: `",
					(char *)pivot->content, "': not a valid identifier");
			ft_free_ptr((void *)&pair);
		}
		pivot = pivot->next;
	}
}

void	builtin_export(t_list *lst)
{
	if (lst->next == NULL)
		print_exported_vars();
	else
		iterate_lst_to_export(lst);
}

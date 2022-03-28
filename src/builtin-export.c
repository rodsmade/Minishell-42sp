/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:52:44 by afaustin          #+#    #+#             */
/*   Updated: 2022/03/28 13:15:05 by adrianofaus      ###   ########.fr       */
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

void	iterate_quoted_value(char *line_read, int *i, char *value, int *j)
{
	char	qtype;

	qtype = line_read[(*i)];
	*i = *i + 1;
	while (line_read[*i] != qtype && line_read[(*i)] && line_read[(*i)] != '=')
	{
		value[(*j)] = line_read[(*i)];
		*i = *i + 1;
		*j = *j + 1;
	}
}

void	generate_value(char *line_read, char *value)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line_read[i] && line_read[i] != '=')
	{
		if (line_read[i] == '\'' || line_read[i] == '\"')
		{
			iterate_quoted_value(line_read, &i, value, &j);
		}
		else
		{
			value[j] = line_read[i];
			i++;
			j++;
		}
	}
	value[j] = '\0';
}

int	generate_pair(char *line_read, char **pair)
{
	char	*key;
	char	*value;
	char	*aux;
	int		mid_point;

	mid_point = 0;
	key = (char *)malloc(sizeof(char) * (key_len(line_read) + 1));
	generate_key(line_read, key, &mid_point);
	if (line_read[mid_point] == '=')
	{
		if (line_read[mid_point + 1])
		{
			value = (char *)malloc(sizeof(char) * (value_len(&line_read[mid_point + 1]) + 1));
			generate_value(&line_read[mid_point + 1], value);
			aux = ft_strjoin(key, "=");
			*pair = ft_strjoin(aux, value);
			ft_free_ptr((void *)&aux);
			ft_free_ptr((void *)&key);
			ft_free_ptr((void *)&value);
		}
		else
		{
			aux = ft_strjoin(key, "=");
			*pair = ft_strjoin(aux, "");
			ft_free_ptr((void *)&aux);
			ft_free_ptr((void *)&key);			
		}
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
	t_list	*tmp;
	char	*pair;
	int		status;

	tmp = lst->next;
	while (tmp != NULL)
	{
		if ((is_valid_key((char *)tmp->content)) == true)
		{
			status = generate_pair((char *)tmp->content, &pair);
			if (status)
				insert_in_hashtable(pair, 1, &g_tudao.hashtable);
			else if (!status)
				insert_in_hashtable(pair, -1, &g_tudao.hashtable);
			ft_free_ptr((void *)&pair);
		}
		else
			printf("minishell: export: `%s': not a valid identifier", \
			(char *)tmp->content);
		tmp = tmp->next;
	}
}

void	builtin_export(t_list *lst)
{
	if (lst->next == NULL)
	{
		print_exported_vars();
		return ;
	}
	iterate_lst_to_export(lst);
}

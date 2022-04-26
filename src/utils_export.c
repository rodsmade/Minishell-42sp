/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:12:26 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/26 17:43:27 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	value_len(char *line_read)
{
	int		i;
	int		len;
	char	qtype;

	i = 0;
	len = 0;
	while (line_read[i] && line_read[i] != '=')
	{
		if (line_read[i] == '\'' || line_read[i] == '\"')
		{
			qtype = line_read[i];
			i++;
			while (line_read[i] != qtype && line_read[i] && line_read[i] != '=')
			{
				i++;
				len++;
			}
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

int	key_len(char *key_value)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (key_value[index] != '=' && key_value[index])
	{
		if (key_value[index] == '\'' || key_value[index] == '\"')
			index++;
		else
		{
			index++;
			len++;
		}
	}
	return (len);
}

int	is_valid_identifier(char *key_value)
{
	int		i;
	int		flag;
	char	quote_type;

	i = 0;
	quote_type = 0;
	flag = 0;
	if (key_value == NULL || key_value[i] == '\0' || key_value[i] == '=')
		return (false);
	while (key_value[i] && key_value[i] != '=')
	{
		if (ft_isalpha(key_value[i]) || key_value[i] == '_')
			flag = 1;
		if (ft_isdigit(key_value[i]) && !flag)
			return (false);
		if ((key_value[i] == '\'' || key_value[i] == '\"') && !quote_type)
			quote_type = key_value[i];
		else if (key_value[i] == quote_type)
			quote_type = 0;
		else if (!ft_isalnum(key_value[i]) && key_value[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	print_exported_vars(void)
{
	int		i;
	t_list	*aux;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		aux = g_tudao.hashtable[i];
		while (aux != NULL)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(((t_env_var *)(aux->content))->key,
				STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			if (((t_env_var *)(aux->content))->value)
				ft_putstr_fd(((t_env_var *)(aux->content))->value,
					STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			aux = aux->next;
		}
	}	
}

void	concat_and_free(char **pair, char *s1, char *s2, char *s3)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	*pair = ft_strjoin(tmp, s3);
	ft_free_ptr((void *)&s1);
	ft_free_ptr((void *)&s2);
	ft_free_ptr((void *)&s3);
	ft_free_ptr((void *)&tmp);
}

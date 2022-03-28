/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:12:26 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/28 14:46:24 by adrianofaus      ###   ########.fr       */
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

int	is_valid_key(char *key_value)
{
	int		i;
	int		flag;
	char	quote_type;

	i = 0;
	quote_type = 0;
	flag = 0;
	while (key_value[i] != '=' && key_value[i])
	{
		if (ft_isalpha(key_value[i]))
			flag = 1;
		if (ft_isdigit(key_value[i]) && !flag)
			return (false);
		if ((key_value[i] == '\'' || key_value[i] == '\"') && !quote_type)
			quote_type = key_value[i];
		else if (key_value[i] == quote_type)
			quote_type = 0;
		else if (!ft_isalnum(key_value[i]))
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
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(((t_env_var *)(aux->content))->name, \
			STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			if (((t_env_var *)(aux->content))->value)
				ft_putstr_fd(((t_env_var *)(aux->content))->value, \
				STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
			aux = aux->next;
		}
	}	
}

void	concat_and_free(char **pair, int num_str, ...)
{
	va_list	args;
	int		count;
	char	*aux;
	char	*tmp;

	count = -1;
	va_start(args, num_str);
	while (++count < num_str)
	{
		if (*pair == NULL)
		{
			tmp = va_arg(args, char *);
			*pair = ft_strdup(tmp);
			ft_free_ptr((void *)&tmp);
		}
		else
		{
			aux = *pair;
			tmp = va_arg(args, char *);
			*pair = ft_strjoin(aux, tmp);
			ft_free_ptr((void *)&aux);
			ft_free_ptr((void *)&tmp);
		}
	}
}

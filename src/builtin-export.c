/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:52:44 by afaustin          #+#    #+#             */
/*   Updated: 2022/03/26 22:14:21 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//corrigir para aspas não fechadas
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

int	value_len(char *line_read)
{
	int		i;
	int		len;
	char	quote_type;

	i = 0;
	len = 0;
	while (line_read[i] && line_read[i] != '=')
	{
		if (line_read[i] == '\'' || line_read[i] == '\"')
		{
			quote_type = line_read[i];
			i++;
			while (line_read[i] != quote_type && line_read[i] && line_read[i] != '=')
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

void	generate_value(char *line_read, char *value)
{
	int		i;
	int		j;
	char	quote_type;

	i = 0;
	j = 0;
	while (line_read[i] && line_read[i] != '=')
	{
		if (line_read[i] == '\'' || line_read[i] == '\"')
		{
			quote_type = line_read[i];
			i++;
			while (line_read[i] != quote_type && line_read[i] && line_read[i] != '=')
			{
				value[j] = line_read[i];
				i++;
				j++;
			}
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

//Corrigir quando o igual é digitado, mas não tenho valor, eu devo alocar nada como valor, mas a variável  precisa estar lá
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

// void	builtin_export(t_list *lst)
void	builtin_export(char *line_read)
{
	// t_list	*tmp;
	char		*pair;
	int			status;
	
	// if (lst == NULL)
	// {
		// print_exported_vars();
		// return ;
	// }
	// tmp = lst;
	// while (tmp != NULL)
	// {
		// if ((is_valid_key((char *)lst->content)) == true)
		if ((is_valid_key(line_read)) == true)
		{
			status = generate_pair(line_read, &pair);
			if (status)
				insert_in_hashtable(pair, 1, &g_tudao.hashtable);
			else if (!status)
				insert_in_hashtable(pair, -1, &g_tudao.hashtable);
			ft_free_ptr((void *)&pair);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", line_read);
			// printf("minishell: export: `%s': not a valid identifier", (char *)lst->content);
	// 	tmp = tmp->next;
	// }
}
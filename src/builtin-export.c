/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:52:44 by afaustin          #+#    #+#             */
/*   Updated: 2022/03/25 00:58:41 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_letter(char *key_value, int *index)
{
	char	quote_type;

	quote_type = 0;
	while (!ft_isalpha(key_value[(*index)]) && key_value[*index])
	{
		if ((key_value[(*index)] == '\'' || key_value[(*index)] == '\"') && !quote_type)
			quote_type = key_value[(*index)];
		else if (key_value[(*index)] == quote_type)
			quote_type = 0;
		else
			return (false);
		*index = *index + 1;
	}
	return (true);	
}

int	is_valid_key(char *key_value)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = 0;
	if (check_first_letter(key_value, &i))
	{
		while (key_value[i] != '=' && key_value[i])
		{
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
	return (false);
}

// void	builtin_export(t_list *lst)
void	builtin_export(char *line_read)
{
	// t_list	*tmp;

	// tmp = lst;
	// while (tmp != NULL)
	// {
		// if ((is_valid_key((char *)lst->content)) == true)
		if ((is_valid_key(line_read)) == true)
		{
			printf("Boaaaaa\n");
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", line_read);
			// printf("minishell: export: `%s': not a valid identifier", (char *)lst->content);
	// 	tmp = tmp->next;
	// }
}
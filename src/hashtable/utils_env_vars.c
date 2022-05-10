/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:47:46 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_var_to_string(t_env_var *env_var)
{
	char	*env_var_str;
	char	*temp;

	temp = ft_strjoin((char *) env_var->key, "=");
	if (env_var->value)
	{
		env_var_str = ft_strjoin(temp, (char *) env_var->value);
		ft_free_ptr((void *)&temp);
		return (env_var_str);
	}
	return (temp);
}

int	count_env_vars(void)
{
	int		count;
	int		i;
	t_list	*pivot;

	i = -1;
	count = 0;
	while (++i < TABLE_SIZE)
	{
		pivot = g_data.hashtable[i];
		while (pivot)
		{
			count++;
			pivot = pivot->next;
		}
	}
	return (count);
}

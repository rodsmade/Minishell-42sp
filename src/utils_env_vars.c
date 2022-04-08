/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:47:46 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/08 18:48:02 by roaraujo         ###   ########.fr       */
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
		pivot = g_tudao.hashtable[i];
		while (pivot)
		{
			count++;
			pivot = pivot->next;
		}
	}
	return (count);
}

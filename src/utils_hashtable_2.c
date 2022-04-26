/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hashtable_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:06:49 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/26 18:23:51 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_env_var_key(char *env_var_str)
{
	char	*key;
	int		length;

	length = -1;
	while (env_var_str[++length] != '=')
		continue ;
	key = malloc((length + 1) * sizeof(char));
	key[length] = '\0';
	while (--length >= 0)
		key[length] = env_var_str[length];
	return (key);
}

char	*alloc_env_var_value(char *env_var_str)
{
	char	*value;
	int		length;
	int		offset;
	int		i;

	i = 0;
	while (env_var_str[++i - 1] != '=')
		continue ;
	length = ft_strlen(env_var_str) - i;
	value = malloc((length + 1) * sizeof(char));
	value[length] = '\0';
	offset = i;
	i--;
	while (env_var_str[++i])
		value[i - offset] = env_var_str[i];
	return (value);
}

char	**split_key_and_value(char *string)
{
	char	**key_value;

	if (!ft_strchr(string, '='))
		return (NULL);
	key_value = malloc(3 * sizeof(*key_value));
	key_value[0] = alloc_env_var_key(string);
	key_value[1] = alloc_env_var_value(string);
	key_value[2] = NULL;
	return (key_value);
}

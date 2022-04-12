/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:22:34 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/11 18:13:55 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*buffer;
	char	*curr_path;

	buffer = NULL;
	curr_path = getcwd(buffer, 0);
	if (!curr_path)
	{
		g_tudao.ext_routine.code = 1;
		g_tudao.ext_routine.msg = ft_strdup("Coudln't find current path");
	}
	else
	{
		g_tudao.ext_routine.code = 0;
		ft_putendl_fd(curr_path, 1);
	}
	ft_free_ptr((void *)&curr_path);
	return ;
}

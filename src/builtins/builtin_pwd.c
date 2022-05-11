/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:22:34 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/05/11 20:47:45 by roaraujo         ###   ########.fr       */
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
		g_data.exit.code = EXIT_FAILURE;
		g_data.exit.msg = \
			ft_strdup("builtin_pwd: Couldn't find current path");
	}
	else
		ft_putendl_fd(curr_path, 1);
	ft_free_ptr((void *)&curr_path);
	return ;
}

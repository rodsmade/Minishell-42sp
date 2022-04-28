/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:15:16 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/27 22:56:10 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file_exists(char *file_name)
{
	char	*err_msg;

	if (access(file_name, F_OK) == -1)
	{
		err_msg = ft_strjoin(file_name, ": No such file or directory");
		free_and_exit_fork(err_msg, 2);
	}
	return ;
}

void	check_file_has_permissions(char *file_name, int permissions)
{
	char	*err_msg;

	if (access(file_name, permissions) == -1)
	{
		err_msg = ft_strjoin(file_name, ": Permission denied");
		free_and_exit_fork(err_msg, EXIT_FAILURE);
	}
	return ;
}

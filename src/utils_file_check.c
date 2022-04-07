/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:15:16 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/06 21:13:13 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file_exists(char *file_name)
{
	char	*err_msg;

	if (access(file_name, F_OK) == -1)
	{
		err_msg = ft_strjoin_3("bash: ",
				file_name,
				": No such file or directory");
		free_and_exit_fork(err_msg);
	}
	return ;
}

void	check_file_has_permissions(char *file_name, int permissions)
{
	char	*err_msg;

	if (access(file_name, permissions) == -1)
	{
		err_msg = ft_strjoin_3("bash: ",
				file_name,
				": Permission denied");
		free_and_exit_fork(err_msg);
	}
	return ;
}
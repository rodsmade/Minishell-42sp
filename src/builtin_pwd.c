/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:22:34 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/09 23:20:01 by coder            ###   ########.fr       */
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
		ft_putendl_fd("error pwd", 2);
	else
		ft_putendl_fd(curr_path, 1);
	ft_free_ptr((void *)&curr_path);
}

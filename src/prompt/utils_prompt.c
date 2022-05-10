/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 00:08:03 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error_exit(void)
{
	char	*minishell_f;

	g_data.exit.flag = true;
	g_data.exit.code = 2;
	minishell_f = ft_strjoin_3(BRED, "✘ minishell: ", COLOUR_RESET);
	g_data.exit.msg = ft_strjoin(minishell_f,
			"syntax error: unexpected end of file");
	ft_putendl_fd(g_data.exit.msg, 2);
	ft_putendl_fd("exit", 2);
	ft_free_ptr((void *)&g_data.exit.msg);
	ft_free_ptr((void *)&minishell_f);
	return ;
}

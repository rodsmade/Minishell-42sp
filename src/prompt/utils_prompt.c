/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 00:08:03 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/03 00:42:52 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error_exit(void)
{
	char	*minishell_f;

	g_tudao.exit.flag = true;
	g_tudao.exit.code = 2;
	minishell_f = ft_strjoin_3(BRED, "✘ minishell: ", COLOUR_RESET);
	g_tudao.exit.msg = ft_strjoin(minishell_f,
			"syntax error: unexpected end of file");
	ft_putendl_fd(g_tudao.exit.msg, 2);
	ft_putendl_fd("exit", 2);
	ft_free_ptr((void *)&g_tudao.exit.msg);
	ft_free_ptr((void *)&minishell_f);
	return ;
}

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   signal_handler.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: roaraujo <roaraujo@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/14 00:11:29 by roaraujo		  #+#	#+#			 */
/*   Updated: 2022/04/19 20:14:27 by roaraujo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	sighandler_within_hd_prompt(int signal)
{
	if (signal == SIGINT)
	{
		g_tudao.heredoc_stopped = true;
		g_tudao.exit.code = 130;
		ft_putendl_fd("", 1);
		rl_replace_line("", 0);
		rl_done = true;
		close(rl_instream->_fileno);
	}
	return ;
}

void	sighandler_parent(int signal)
{
	if (signal == SIGINT)
	{
		g_tudao.exit.code = 130;
		ft_putendl_fd("", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	sighandler_child(int signal)
{
	if (signal == SIGQUIT)
		free_and_exit_fork(ft_strdup("Quit (core dumped)"), 131);
	if (signal == SIGINT)
		free_and_exit_fork(ft_strdup(""), 130);
	return ;
}

void	sighandler_parent_extra_input(int signal)
{
	if (signal == SIGINT)
	{
		g_tudao.skip_execution = true;
		g_tudao.is_ctrl_d = false;
		g_tudao.exit.code = 130;
		ft_putendl_fd("", 1);
		rl_replace_line("", 0);
		rl_done = true;
		close(rl_instream->_fileno);
	}
	return ;
}

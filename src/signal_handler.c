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

void	set_signal(int signal, void handler(int), struct sigaction *act)
{
	act->sa_handler = handler;
	act->sa_flags = SA_RESTART;
	sigemptyset(&(act->sa_mask));
	sigaction(signal, act, NULL);
	return ;
}

void	catch_signals_parent(int signal)
{
	if (signal == SIGINT)
	{
		g_tudao.ext_routine.code = 130;
		ft_putendl_fd("", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	catch_signals_extra_input(int signal)
{
	if (signal == SIGINT)
	{
		g_tudao.ext_routine.code = 130;
		g_tudao.skip_execution = true;
		ft_putendl_fd("", 1);
		// rl_pending_input = 'J';
		rl_done = true;
		// rl_line_buffer = ft_strdup("NAO VAI APRENDER TECH RAPIDO");
		close(rl_instream->_fileno);
		// rl_outstream. = ft_strdup("aaaaaa");
		g_tudao.is_ctrl_d = false;
	}
	return ;
}

// void	catch_signals_extra_input(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		g_tudao.skip_execution = true;
// 		// rl_done = true;
// 		ft_putendl_fd("", 1);
// 		ft_free_ptr((void *)&rl_line_buffer);
// 		rl_line_buffer = ft_strdup("");
// 	}
// 	return ;
// }

void	unset_signal(int signal, struct sigaction *act)
{
	act->sa_handler = SIG_IGN;
	sigaction(signal, act, NULL);
	return ;
}


void	catch_signals_child(int signal)
{
	if (signal == SIGINT)
	{
		(void) signal;
	}
	return;
}

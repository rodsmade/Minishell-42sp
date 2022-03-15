/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:58:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/15 13:36:57 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_tokens_consistency(void)
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
	while (pivot && pivot->next)
	{
		if (is_pipe((char *) pivot->content))
		{
			if (is_pipe((char *) pivot->next->content)
				|| is_and_or((char *) pivot->next->content))
				print_syntax_error_exit(pivot->next);
		}
		else if (is_and_or((char *) pivot->next->content))
		{
			if (is_pipe((char *) pivot->next->content)
				|| is_and_or((char *) pivot->next->content))
				print_syntax_error_exit(pivot->next);
		}
		else if (is_redirect((char *) pivot->content))
		{
			if (is_special_token((char *) pivot->next->content))
				print_syntax_error_exit(pivot->next);
		}
		pivot = pivot->next;
	}
}

int	count_commands(void)
{
	int		cmd_count;
	t_list	*pivot;

	cmd_count = 1;
	pivot = g_tudao.token_list;
	while (pivot)
	{
		if (ft_strncmp((char *) pivot->content, "||", 3) == 0
			|| ft_strncmp((char *) pivot->content, "&&", 3) == 0)
			break ;
		if (ft_strncmp((char *) pivot->content, "|", 2) == 0)
			cmd_count++;
		pivot = pivot->next;
	}
	return (cmd_count);
}

// TODO: implementar lógica de adicionar comando na lista de pipeline
// while (token && token != '|')
// {
// 	if token = "<" or ">"
// 		skip two tokens;
// 	cmd_array = add_token_to_list(token);	// criar função de concatenação de
// tokens! q faz realloc. 
// }
void	set_up_command_table(void)
{
	int	cmd_count;

	cmd_count = count_commands();
	printf("commands identified: %d\n", cmd_count);
	return ;
}

void	parse_tokens(void)
{
	mock_tokens();
	check_tokens_consistency();
	set_up_command_table();
	free_mock();
	return ;
}

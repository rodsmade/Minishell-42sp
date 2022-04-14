/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:47:40 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/14 20:58:38 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assemble_line(char **line_read)
{
	char	*aux_str;
	char	*temp;

	aux_str = readline("> ");
	temp = aux_str;
	aux_str = ft_strjoin(" ", aux_str);
	free(temp);
	temp = (*line_read);
	(*line_read) = ft_strjoin((*line_read), aux_str);
	lexer_line(aux_str);
	expand_tokens();
	parse_tokens();
	free(aux_str);
	free(temp);
}

void	display_cmd_prompt(void)
{
	char	*curr_path;
	char	*prompt;

	curr_path = getcwd(NULL, 0);
	prompt = ft_strjoin(curr_path, " $ ");
	g_tudao.prompt_input = readline(prompt);
	lexer_line(g_tudao.prompt_input);
	expand_tokens();
	parse_tokens();
	while (g_tudao.token_list && !g_tudao.syntax_error
		&& is_pipe_and_or((char *) ft_lst_last(g_tudao.token_list)->content))
		assemble_line(&g_tudao.prompt_input);
	ft_free_ptr((void *)&curr_path);
	ft_free_ptr((void *)&prompt);
	return ;
}

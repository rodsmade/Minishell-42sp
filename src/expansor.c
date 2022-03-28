/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/28 21:54:04 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append_char(char *str, char c)
{
	char	*new_str;
	int		str_size;

	if (str)
		str_size = ft_strlen(str);
	else
		str_size = 0;
	new_str = malloc((str_size + 2) * sizeof(char));
	new_str[str_size + 1] = '\0';
	new_str[str_size] = c;
	ft_free_ptr((void *)&str);
	return (new_str);
}

void	expand_dollar_sign(t_list *token)
{
	char	*token_content;
	char	*expanded_content;
	int		i;

	expanded_content = NULL;
	token_content = (char *) token->content; //token_content = helloadhjadh$USER
	i = -1;
	while (token_content[++i] && token_content[i] != '$')
		expanded_content = ft_append_char(expanded_content, token_content[i]);
	// while (token_content[++i] && token_content[i] != '$')
	// {
	// 	// se tiver aspas simples: não expande
	// 	if (token_content[i] == '\'')
	// 	// se tiver aspas duplas: expande
	// 	if (token_content[i] == '\"')
	// 	// se não tiver nem uma nem outra: o $ é o "divisor" do token, o q vier depois considera o nome da env_var
	// }
	printf("expanded content: %s\n", expanded_content);
	ft_free_ptr((void *)&expanded_content);
	return ;
}

void	expand_wildcards(void)
{
	return ;
}

void	expand_tokens(void)
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
	while (pivot)
	{
		expand_dollar_sign(pivot);
		expand_wildcards();
		pivot = pivot->next;
	}
}
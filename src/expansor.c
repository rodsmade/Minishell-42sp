/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:22:48 by afaustin          #+#    #+#             */
/*   Updated: 2022/04/13 00:20:14 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_expansible(t_list *token)
{
	char	*content;
	int		i;

	content = (char *)token->content;
	i = 0;
	while (content[i])
	{
		if (content[i] && content[i] == '\'')
		{
			i++;
			while (content[i] && content[i] != '\'')
				i++;
		}
		if (content[i] && content[i] == '\"')
		{
			i++;
			while (content[i] && content[i] != '\"')
			{
				if (content[i] == '$')
					return (true);
				else
					i++;
			}
		}
		if (content[i] && content[i] == '$')
			return (true);
		if (content[i])
			i++;
	}
	return (false);
}

void	expand_tokens(t_list *token_list)
{
	 t_list	*tmp;

	 tmp = token_list;
	 while (tmp)
	 {
		 if (is_expansible(tmp) == true)
		 {
			dprintf(2, ">>%s<< is expansible\n", (char *)tmp->content);
		 }
		 else
		 	dprintf(2, ">>%s<< is not expansible\n", (char *)tmp->content);
		 tmp = tmp->next;
	 }
}
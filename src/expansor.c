/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:22:48 by afaustin          #+#    #+#             */
/*   Updated: 2022/04/13 02:13:32 by afaustin         ###   ########.fr       */
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
		else if (content[i] && content[i] == '\"')
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
		else if (content[i] && content[i] == '$')
			return (true);
		if (content[i])
			i++;
	}
	return (false);
}

char	*get_exp_content(char *content)
{
	char	*exp_content;
	int		i;
	
	i = 0;
	exp_content = NULL;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			i++;
			while (content[i] && content[i] != '\'')
			{
				ft_append_char(exp_content, content[i]);
				i++;
			}
		}
		else if (content[i] && content[i] == '\"')
		{
			i++;
			while (content[i] && content[i] != '\"')
			{
				if (content[i] == '$' && content[i + 1])
					/* TO DO:
						-> Buscar um valor de acordo com uma chave
						-> Caso existam caracteres depois do '$' estes serão a chave
						-> O index deverá avançar de acordo com o tamanho da chave
					*/
					dprintf(2, "Get_key_value\n");
				else
				{
					ft_append_char(exp_content, content[i]);
					i++;
				}
			}
		}
		else if (content[i] && content[i] == '$' && content[i + 1])
			/* TO DO:
				-> Buscar um valor de acordo com uma chave
				-> Caso existam caracteres depois do '$' estes serão a chave
				-> O index deverá avançar de acordo com o tamanho da chave
			*/	
			dprintf(2, "Get_key_value\n");
		if (content[i])
		{
			ft_append_char(exp_content, content[i]);
			i++;
		}
	}
	return (exp_content);
}

t_list	*expand_dollar_sign(t_list **head, t_list *token)
{
	char	*expanded_content;

	expanded_content =  get_exp_content((char *)token->content);
	/* TO DO:
		-> quebrar o expanded_content em tokens (sub lista)
		-> caso o token atual seja o primeiro(head)	devo atualizar o head, pois novos tokens serão gerados
		-> caso o token não seja o primeiro(head), não preciso atualizar o head e apenas adiciono
		a sublista dentro da lista
		-> Em todos os casos devo retornar o último token da sublista para a função 'expand tokens'
		para que o loop continue a partir do token adicionado.
	*/
	if (*head)
		//*head = ft_lst_last(sublist);
}

void	expand_tokens(t_list *token_list)
{
	 t_list	*tmp;
	 int	is_head;

	 tmp = token_list;
	 is_head = true;
	 while (tmp)
	 {
		 if (is_expansible(tmp) == true)
		 {
			dprintf(2, ">>%s<< is expansible\n", (char *)tmp->content);
			if (is_head == true)
				expand_dollar_sign(&token_list, tmp);
			else if (is_head == false)
				expand_dollar_sign(NULL, tmp);
		 }
		 else
		 	dprintf(2, ">>%s<< is not expansible\n", (char *)tmp->content);
		 tmp = tmp->next;
		 is_head = false;
	 }
}
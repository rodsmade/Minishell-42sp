#include "minishell.h"

char	*ft_append_char(char *str, char c)
{
	char	*new_str;
	int		str_size;
	int		i;

	i = -1;
	if (str)
		str_size = ft_strlen(str);
	else
		str_size = 0;
	new_str = malloc((str_size + 2) * sizeof(char));
	while (++i < str_size)
		new_str[i] = str[i];
	new_str[str_size] = c;
	new_str[str_size + 1] = '\0';
	ft_free_ptr((void *)&str);
	return (new_str);
}

void	print_token_lst(t_list *lst)
{
	t_list	*pivot;

	pivot = lst;
	dprintf(2, ">> ");
	while (pivot)
	{
		if (pivot->next)
			dprintf(2, "{%s} ", (char *)pivot->content);
		else
			dprintf(2, "{%s}", (char *)pivot->content);
		pivot = pivot->next;
	}
	dprintf(2, " <<\n");
}

int	jump_whitespaces(char* string)
{
	int	i;

	i = -1;
	while (string [++i] && (string[i] == ' ' || string[i] == 't'))
		continue ;
	return (i - 1);
}

t_list	*create_sublist(char *string)
{
	t_list	*sublist;
	char	*token_content;
	int		i;

	sublist = NULL;
	token_content = NULL;
	i = -1;
	while (string[++i])
	{
		if (string[i] && (string[i] != ' ' && string[i] != '\t'))
			token_content = ft_append_char(token_content, string[i]);
		else if (string[i] == ' ' || string[i] == '\t')
		{
			if (token_content)
				ft_lst_add_back(&sublist, ft_lst_new((void *) token_content));
			token_content = NULL;
			i += jump_whitespaces(&string[i]);
		}
	}
	if (token_content)
		ft_lst_add_back(&sublist, ft_lst_new((void *) token_content));
	return (sublist);
}

void	substitute_token_by_sublist(char *string_to_be_broken_into_tokens, t_list **token_address)
{
	t_list	*new_token_sublist;

	new_token_sublist = create_sublist(string_to_be_broken_into_tokens);
	dprintf(2, "new token sublist: ");
	print_token_lst(new_token_sublist);
	if (*token_address)
	{
		ft_lst_last(new_token_sublist)->next = (*token_address)->next;
		ft_free_ptr((void *)&((*token_address)->content));
	}
	ft_free_ptr((void *)token_address);
	*token_address = new_token_sublist;
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		ft_free_ptr((void *)&list->content);
		ft_free_ptr((void *)&list);
		list = tmp;
	}
}

int main(void)
{
	t_list	*token_list;

	token_list = NULL;
	ft_lst_add_back(&token_list, ft_lst_new((void *)ft_strdup("aaa")));
	ft_lst_add_back(&token_list, ft_lst_new((void *)ft_strdup("bbb")));
	ft_lst_add_back(&token_list, ft_lst_new((void *)ft_strdup("$TESTE")));
	ft_lst_add_back(&token_list, ft_lst_new((void *)ft_strdup("ddd")));
	ft_lst_add_back(&token_list, ft_lst_new((void *)ft_strdup("eee")));
	ft_lst_add_back(&token_list, ft_lst_new((void *)ft_strdup("fff")));

	dprintf(2, "token list before: ");
	print_token_lst(token_list);
	substitute_token_by_sublist((char *) token_list->next->next->content, &token_list->next->next);
	dprintf(2, "token list after: ");
	print_token_lst(token_list);
	free_list(token_list);
	return 0;
}
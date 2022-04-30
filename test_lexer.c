#include "minishell.h"

void	print_token_lst(t_list *lst);

char	*rods_create_new_token(char *line_read, int *i)
{
	char	*token_tmp;
	int		j;

	token_tmp = NULL;
	j = 0;
	while (line_read[j] && !ft_is_blankspace(line_read[j]))
	{
		token_tmp = ft_append_char(token_tmp, line_read[j]);
		j++;
	}
	(*i) += j;
	return (token_tmp);
}

int main(void)
{
	char	*line_read;
	char	*token_tmp;
	t_list	*my_token_list;
	int		i;

	line_read = readline("dime-lo: ");
	printf("line read>: %s\n", line_read);
	my_token_list = NULL;
	token_tmp = NULL;
	i = 0;
	while (line_read[i])
	{
		while (line_read[i] && ft_is_blankspace(line_read[i]))
			i++;
		token_tmp = rods_create_new_token(&line_read[i], &i);
		if (token_tmp)
			ft_lst_add_back(&my_token_list, ft_lst_new((void *) token_tmp));
		if (!line_read[i])
			break ;
		token_tmp = NULL;
	}
	print_token_lst(my_token_list);
	return (0);
}

void	print_token_lst(t_list *lst)
{
	t_list	*pivot;

	pivot = lst;
	printf(">> ");
	while (pivot)
	{
		if (pivot->next)
			printf("{%s} ", (char *)pivot->content);
		else
			printf("{%s}", (char *)pivot->content);
		pivot = pivot->next;
	}
	printf(" <<\n");
}

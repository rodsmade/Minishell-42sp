#include "minishell.h"

bool	sweep_and_search(char *word, char *pattern, int n)
{
	int	i;

	i = 0;
	if (!word || !pattern)
		return (false);
	while (word[i] && ft_strlen(&word[i]) >= n)
	{
		if (ft_strncmp(&word[i], pattern, n) == 0)
			return (true);
		i++;
	}
	return (false);
}

int main(int argc, char *argv[])
{
	char *pattern;
	char *word;

	if (argc != 3)
		return -1;
	word = argv[1];
	pattern = argv[2];
	if (sweep_and_search(word, pattern, ft_strlen(pattern)))
		printf("Word: `%s' has pattern `%s' in it\n", word, pattern);
	else
		printf("Word: `%s' does not have pattern `%s' in it\n", word, pattern);
	return 0;
}
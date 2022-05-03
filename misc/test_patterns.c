#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include "minishell.h"

// cenário 1: kdasdhajskhd*
bool	matches_pattern_head(char *str, char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i] && pattern[i] != '*')
		i++;
	if (ft_strncmp(str, pattern, i) == 0)
		return (true);
	else
		return (false);
}

// cenário 2: *kdasdhajskhd
bool	matches_pattern_tail(char *str, char *pattern)
{
	int	i;
	int	x;
	int	n;

	i = 0;
	while (pattern[i] == '*')
		i++;
	x = i;
	n = 0;
	while (pattern[i] && pattern[i] != '*')
	{
		n++;
		i++;
	}
	if (ft_strlen(str) >= n && ft_strncmp(&str[ft_strlen(str) - n], &pattern[x], n) == 0)
			return true;
	else
		return (false);
}

// bool	sweep_and_search(char *word, char *pattern, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (word[i] && ft_strlen(word[i]) >= n)
// 	{
// 		if (ft_strncmp(&word[i], pattern, n) == 0)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

bool	sweep_and_search(char *word, char *pattern, int n, int *offset)
{
	int	i;

	i = 0;
	if (!word || !pattern)
		return (false);
	while (word[i] && ft_strlen(&word[i]) >= n)
	{
		if (ft_strncmp(&word[i], pattern, n) == 0)
		{
			*offset += (i + n);
			return (true);
		}
		i++;
	}
	return (false);
}

// cenário 3: *kasj*dk*as*dafjjd*
// cenário 3: kasj*dk*as*dafjjd*
// cenário 3: *kasj*dk*as*dafjjd
// cenário 3: kasj*dk*as*dafjjd
bool	matches_pattern(char *str, char *pattern)
{
	int		i;
	int		str_offset;
	int		pattern_offset;
	int		search_size;
	char	*substring;

	i = 0;
	str_offset = 0;
	pattern_offset = 0;
	if (pattern[i] != '*')	// tem que começar exatamente igual ao primeiro pattern
	{
		pattern_offset = i;
		search_size = 0;
		while (pattern[i++] != '*')
			search_size++;
		substring = ft_substr(pattern, pattern_offset, search_size);
		if (ft_strncmp(&str[str_offset], substring, search_size) != 0)
			return (false);	// falta dar free no substring
		str_offset += search_size;
	}
	while (pattern[i])
	{
		// trocar pra colocar a função matches_pattern_head
		if (pattern[i] == '*')
			i++;
		pattern_offset = i;
		while (pattern[i++] != '*')
			search_size++;
		substring = ft_substr(pattern, pattern_offset, search_size);
		if (!sweep_and_search(&str[str_offset], substring, search_size, &str_offset))
			return (false);
	}
	if (pattern[ft_strlen(pattern) - 1] != '*')	// tem que terminar exatamente igual ao segundo pattern
	{
		// tem que ajustar a posição do pattern q vai pra dentro da função
		if (!matches_pattern_tail(str, pattern))
			return (false);
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	DIR *d;
	struct dirent	*dir;
	char *dir_name;
	char *pattern;

	if (argc != 2)
		return (-1);
	pattern = shrink_asterisks(argv[1]);

	// opens current directory's contents
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			dir_name = dir->d_name;
			if (matches_pattern_head(dir_name, pattern))
				printf(GREEN"  is  "COLOUR_RESET" a match => %s\n", dir->d_name);
			else
				printf(BRED"is not"COLOUR_RESET" a match => %sn", dir->d_name);
			dir = readdir(d);
		}
		closedir(d);
	}
	return (0);
} 
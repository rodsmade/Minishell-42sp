#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include "minishell.h"

// cenário 1: kdasdhajskhd*
// bool	matches_pattern_cenario1(char *str, char *pattern)
// {
// 	int	i;

// 	i = 0;
// 	while (pattern[i] != '*')
// 		i++;
// 	if (ft_strncmp(str, pattern, i) == 0)
// 		return (true);
// 	else
// 		return (false);
// }

// cenário 2: *kdasdhajskhd
// bool	matches_pattern_cenario2(char *str, char *pattern)
// {
// 	int	i;
// 	int	x;
// 	int	n;

// 	i = 0;
// 	while (pattern[i] == '*')
// 		i++;
// 	x = i;
// 	n = 0;
// 	while (pattern[i] && pattern[i] != '*')
// 	{
// 		n++;
// 		i++;
// 	}
// 	if (ft_strlen(str) >= n && ft_strncmp(&str[ft_strlen(str) - n], &pattern[x], n) == 0)
// 			return true;
// 	else
// 		return (false);
// }

// cenário 3: *kasjdkasjd*
bool	matches_pattern_cenario3(char *str, char *pattern)
{
	/**
	 * W I P, NOT FINISHED, NOT EVEN STARTED LOL HELP.
	 * 
	 */
	static bool	pre_asterisk;
	static bool	post_asterisk;
	int			i;

	if (pattern[0] == '*')
		pre_asterisk == false;
	i = -1;
	// premissa: vai ter só um asterisco.
	while (pattern[++i] == '*')
		continue ;
	
}

char	*shrink_asterisks(char *pattern)
/**
 * @brief TESTS:
 * 	./a.out '******'ne'******'na'*'
 * 		shrunk pattern: *ne*na*
 * 	./a.out '*'ne'******'na'*'
 * 		shrunk pattern: *ne*na*
 * 	./a.out '****'ne'*'na'*'
 * 		shrunk pattern: *ne*na*
 * 	./a.out '*'ne'*'na'*'
 * 		shrunk pattern: *ne*na*
 * 	./a.out ne'*'na'*'
 * 		shrunk pattern: ne*na*
 * 	./a.out ne'*'na
 * 		shrunk pattern: ne*na
 * 	./a.out nena
 * 		shrunk pattern: nena
 *
 */
{
	int		i;
	char	*shrunk_pattern;

	if (!pattern)
		return (NULL);
	shrunk_pattern = NULL;
	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			while (pattern [i] && pattern[i] == '*')
				i++;
			shrunk_pattern = ft_append_char(shrunk_pattern, '*');
		}
		while (pattern[i] && pattern[i] != '*')
			shrunk_pattern = ft_append_char(shrunk_pattern, pattern[i++]);
		if (!pattern[i])
			break ;
	}
	printf("shrunk pattern: %s\n", shrunk_pattern);
	return (shrunk_pattern);
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

	// // opens current directory's contents
	// d = opendir(".");
	// if (d)
	// {
	// 	dir = readdir(d);
	// 	while (dir != NULL)
	// 	{
	// 		dir_name = dir->d_name;
	// 		if (matches_pattern_cenario2(dir_name, pattern))
	// 			printf("%s is a match\n", dir->d_name);
	// 		else
	// 			printf("%s is not a match\n", dir->d_name);
	// 		dir = readdir(d);
	// 	}
	// 	closedir(d);
	// }
	return (0);
} 
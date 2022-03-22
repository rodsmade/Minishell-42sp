/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:46:31 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/22 20:28:22 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*buffer;
	char	*curr_path;

	buffer = NULL;
	curr_path = getcwd(buffer, 0);
	if (!curr_path)
		printf("error pwd\n");
	else
		printf("%s\n", curr_path);
	free(curr_path);
}

char	*get_old_pwd(void)
{
	char	*buffer;
	char	*curr_path;

	buffer = NULL;
	curr_path = getcwd(buffer, 0);
	if (!curr_path)
	{
		printf("error pwd\n");
		return (NULL);
	}
	return (curr_path);
}

void	go_to_path(char	*path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_old_pwd();
	new_pwd = ft_strdup(path);
	if (chdir(new_pwd) != 0)
		printf("cd: no such file or directory: %s\n", new_pwd);
	else
	{
		update_hashtable("OLDPWD", old_pwd);
		update_hashtable("PWD", new_pwd);
	}
	ft_free_ptr((void *)&old_pwd);
	ft_free_ptr((void *)&new_pwd);
}

void	go_to_pattern(char *key)
{
	int		index;
	char	*path;

	index = hash_string(key);
	path = read_hashtable(g_tudao.hashtable[index], key);
	if (path == NULL)
	{
		printf("minishell: cd: %s not set\n", key);
		return ;
	}
	go_to_path(path);
}

void	builtin_cd(char *path)
{
	if (path == NULL || !ft_strncmp(path, "~", 2) || !ft_strncmp(path, "", 1))
		go_to_pattern("HOME");
	else if (!ft_strncmp(path, "-", 2))
		go_to_pattern("OLDPWD");
	else
		go_to_path(path);
	builtin_pwd();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:46:31 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/16 21:11:01 by adrianofaus      ###   ########.fr       */
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

char	*read_hashtable(t_list *head, char *key)
{
	t_list	*pivot;
	int		len;

	len = ft_strlen(key);
	pivot = head;
	while(pivot != NULL)
	{
		if (ft_strncmp(((t_env_var *)pivot->content)->name, key, len) == 0)
		{
			// printf(">: OLDPWD %s\n", ((t_env_var *)pivot->content)->value);
			return (((t_env_var *)pivot->content)->value);
		}
		pivot = pivot->next;
	}
	return (NULL);
}

void	update_hashtable(char *key, char *value)
{
	int		index;
	int		len;
	t_list	*tmp;
	
	len = ft_strlen(key);
	index = hash_string(key);
	tmp = g_tudao.hashtable[index];
	while (g_tudao.hashtable[index] != NULL)
	{
		if (ft_strncmp(((t_env_var *)g_tudao.hashtable[index]->content)->name, key, len) == 0)
		{
			// printf("> before: %s\n", ((t_env_var *)g_tudao.hashtable[index]->content)->name);
			// printf("> before: %s\n", ((t_env_var *)g_tudao.hashtable[index]->content)->value);
			ft_free_ptr((void *)&(((t_env_var *)g_tudao.hashtable[index]->content)->value));
			((t_env_var *)g_tudao.hashtable[index]->content)->value = ft_strdup(value);
			// printf("> after: %s\n", ((t_env_var *)g_tudao.hashtable[index]->content)->name);
			// printf("> after: %s\n", ((t_env_var *)g_tudao.hashtable[index]->content)->value);
			break;
		}
		g_tudao.hashtable[index] = g_tudao.hashtable[index]->next;
	}
	g_tudao.hashtable[index] = tmp;
}

void	go_to_path(char	*path)
{
	char	*old_pwd;

	old_pwd = get_old_pwd();
	if (chdir(path) != 0)
		printf("cd: no such file or directory: %s\n", path);
	else
	{
		update_hashtable("OLDPWD", old_pwd);
		update_hashtable("PWD", path);
	}
	ft_free_ptr((void *)&old_pwd);
}

void	go_to_pattern(char *key)
{
	int		index;
	char	*path;
	
	index = hash_string(key);
	path = read_hashtable(g_tudao.hashtable[index], key);
	if (path == NULL)
		printf("cd: unable to go to %s\n", key);
	go_to_path(path);
}


void	builtin_cd(char *path)
{
	if (path == NULL || ft_strncmp(path, "~", 2) == 0)
		go_to_pattern("HOME");
	else if (ft_strncmp(path, "-", 2) == 0)
		go_to_pattern("OLDPWD");
	else
		go_to_path(path);
	builtin_pwd();
}
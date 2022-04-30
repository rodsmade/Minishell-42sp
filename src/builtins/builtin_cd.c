/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:46:31 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/27 22:52:07 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_old_pwd(void)
{
	char	*buffer;
	char	*curr_path;

	buffer = NULL;
	curr_path = getcwd(buffer, 0);
	if (!curr_path)
	{
		g_tudao.exit.code = EXIT_FAILURE;
		free(buffer);
		ft_putendl_fd("builtin_cd: Error getting current working directory", 2);
		return (NULL);
	}
	return (curr_path);
}

void	go_to_path(char	*path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_old_pwd();
	if (!old_pwd || !path[0])
		return ;
	new_pwd = ft_strdup(path);
	if (chdir(new_pwd) != 0)
	{
		g_tudao.exit.msg = ft_strjoin_3("cd: ", \
		new_pwd, ": No such file or directory");
		g_tudao.exit.code = EXIT_FAILURE;
		ft_free_ptr((void *)&old_pwd);
		ft_free_ptr((void *)&new_pwd);
		return ;
	}
	update_hashtable("OLDPWD", old_pwd, true);
	update_hashtable("PWD", new_pwd, true);
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
		g_tudao.exit.msg = ft_strjoin_3("cd: ", \
		key, " not set");
		g_tudao.exit.code = EXIT_FAILURE;
		ft_free_ptr((void *)&path);
		return ;
	}
	go_to_path(path);
}

void	builtin_cd(t_list *cmd_lst)
{
	char	*path;

	if (!cmd_lst->next)
		go_to_pattern("HOME");
	else if (cmd_lst->next->content)
	{
		path = (char *) cmd_lst->next->content;
		if (cmd_lst->next && cmd_lst->next->next != NULL)
		{
			g_tudao.exit.msg = \
			ft_strdup("cd: too many arguments");
			g_tudao.exit.code = EXIT_FAILURE;
			return ;
		}
		else if (ft_strncmp(path, "~", 2) == 0)
			go_to_pattern("HOME");
		else if (ft_strncmp(path, "-", 2) == 0)
		{
			go_to_pattern("OLDPWD");
			if (!g_tudao.exit.code)
				builtin_pwd();
		}
		else
			go_to_path(path);
	}
}
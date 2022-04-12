/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:46:31 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/11 20:08:05 by afaustin         ###   ########.fr       */
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
		ft_putendl_fd("error pwd", 2);
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
	{
		g_tudao.ext_routine.msg = ft_strjoin_3("minishell: cd: ", \
		new_pwd, ": No such file or directory");
		g_tudao.ext_routine.code = EXIT_FAILURE;
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
		g_tudao.ext_routine.msg = ft_strjoin_3("minishell: cd: ", \
		key, " not set");
		g_tudao.ext_routine.code = EXIT_FAILURE;
		ft_free_ptr((void *)&path);
		return ;
	}
	go_to_path(path);
}

void	builtin_cd(t_list *cmd_lst)
/**
 * TODO: set return code to 1 when theres too many args;
 */
{
	char	*path;

	if (cmd_lst->next)
		path = (char *) cmd_lst->next->content;
	if (cmd_lst->next && cmd_lst->next->next != NULL)
	{
		g_tudao.ext_routine.msg = \
		ft_strdup("minishell: cd: too many arguments");
		g_tudao.ext_routine.code = EXIT_FAILURE;
		return ;
	}
	else if (cmd_lst->next == NULL
		|| (ft_strncmp(path, "", 1) == 0)
		|| (ft_strncmp(path, "~", 2) == 0))
		go_to_pattern("HOME");
	else if (ft_strncmp(path, "-", 2) == 0)
		go_to_pattern("OLDPWD");
	else
		go_to_path(path);
}

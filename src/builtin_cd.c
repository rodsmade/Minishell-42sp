/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:46:31 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/10 22:30:11 by roaraujo         ###   ########.fr       */
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
	char	*err_msg;

	old_pwd = get_old_pwd();
	new_pwd = ft_strdup(path);
	if (chdir(new_pwd) != 0)
	{
		err_msg = ft_strjoin("cd: no such file or directory: ", new_pwd);
		ft_free_ptr((void *)&old_pwd);
		ft_free_ptr((void *)&new_pwd);
		ft_putendl_fd(err_msg, 2);
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
	char	*err_msg;

	index = hash_string(key);
	path = read_hashtable(g_tudao.hashtable[index], key);
	if (path == NULL)
	{
		err_msg = ft_strjoin_3("minishell: cd: ", key, " not set");
		ft_free_ptr((void *)&path);
		ft_putendl_fd(err_msg, 2);
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
		ft_putendl_fd("bash: cd: too many arguments", 2);
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

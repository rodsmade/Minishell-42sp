/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:09:40 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/06 21:10:22 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	int		pipe_fds[2];
// 	char	*arr[] = {
// 		"/usr/bin/ls",
// 		"-la",
// 		NULL
// 	};

// 	pipe(pipe_fds);
// 	printf("vai rodar exec\n");
// 	// printf("resultado dup: %i\n", dup2(pipe_fds[0], STDIN_FILENO));
// 	printf("resultado dup: %i\n", dup2(STDIN_FILENO, STDIN_FILENO));

// 	// if (-1 == execve(arr[0], arr, envp))
// 	// 	printf("deu ruim\n");
// 	printf("resultado da close: %i\n", close(42));
// 	// close(pipe_fds[0]);
// 	// close(pipe_fds[0]);
// 	// close(pipe_fds[0]);
// 	// close(pipe_fds[0]);
// 	// close(pipe_fds[0]);
// 	// close(pipe_fds[0]);
// 	// close(pipe_fds[0]);
// 	// close(pipe_fds[1]);
// 	return (0);
// }

/**
 * CONCLUSÕES:
 * 1- fazer dup2(fd, fd) (o msm fd) não dá ruim - aparentemente;
 * 2- depois do dup2, fechar um fd não fecha automaticamente o outro,
 * eles ficam abertos
 * 3- rodar vários close() no mesmo fd não dá ruim, 
 */

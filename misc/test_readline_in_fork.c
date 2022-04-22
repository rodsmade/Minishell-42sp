/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline_in_fork.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:24:37 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/18 20:25:19 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(void)
// {
// 	int		pid;
// 	int		pid2;
// 	char	*str;
// 	int		wstatus;

// 	pid = fork();
// 	if (pid < 0)
// 		return (1);
// 	else if (pid == 0)
// 	{
// 		printf("entrou filho de fora\n");
// 		pid2 = fork();
// 		if (pid2 < 0)
// 			return (2);
// 		else if (pid2 == 0)
// 		{
// 			printf("entrou filho de dentro, readline:\n");
// 			str = readline("Teste > ");
// 			printf("resultado da readline: ");
// 			printf("%s\n", str);
// 			return (0);
// 		}
// 		else
// 		{
// 			waitpid(pid2, &wstatus, 0);
// 			printf("saiu filho de dentro\n");
// 		}
// 		return (0);
// 	}
// 	else
// 	{
// 		waitpid(pid, &wstatus, 0);
// 		printf("saiu filho de fora\n");
// 	}
// 	return (0);
// }

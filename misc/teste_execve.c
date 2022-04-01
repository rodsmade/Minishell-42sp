/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:21:37 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/01 22:25:18 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

// QUAL É A CONCLUSÃO?
// Dentro da função execve o primeiro argumento precisa necessariamente ser o
// comando "desexpandido", ou seja, se vier no input g"r"ep, o primeiro 
// argumento de execve tem que ser "/usr/bin/grep", caso contrário dá ruim.
// e tudo bem dentro do array estar g"r"ep!
int	main(int argc, char *argv[], char *envp[])
{
	char	*arr[4] = { "dfjklfljkhfjskfhsdfjh", "-l", "-a", NULL };
	char	*cmd_path = "/usr/bin/ls";

	printf("%s\n", "\0");
	printf("%p\n", arr[0]);
	if (-1 == execve(cmd_path, arr, envp))
		printf("deu ruim\n");
	return (0);
}

// ls -l -a

// /user/bin/ls -l -a

// ./ls -l -a
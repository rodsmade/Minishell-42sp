#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	char *arr[] = {
		"/usr/bin/ls",			// QUAL É A CONCLUSÃO?
		"-la",						// Dentro da função execve o primeiro argumento precisa necessariamente ser o comando
		NULL						// "desexpandido", ou seja, se vier no input g"r"ep, o primeiro argumento de execve tem que
	};								// ser "/usr/bin/grep", caso contrário dá ruim. e tudo bem dentro do array estar g"r"ep!

	printf("%s\n", "\0");
	printf("%p\n", arr[0]);
	if (-1 == execve(arr[0], arr, envp))
		printf("deu ruim\n");
	return 0;
}
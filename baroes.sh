#!/bin/bash
#echo -e '\necho oi' | ./minishell > result.txt

echo 'CMD --> echo oi'
echo -e 'echo oi > minishell.txt' | ./minishell >output.txt 2>&1 && echo oi > bash.txt && diff minishell.txt bash.txt >> differ

echo 'CMD --> ls echo $?'
echo -e 'ls\necho $? > minishell.txt' | ./minishell >output.txt 2>&1 && echo oi > bash.txt && diff minishell.txt bash.txt >> differ


rm minishell.txt
rm bash.txt
rm output.txx
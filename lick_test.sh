#!/bin/bash

MINISH=minishell;
SLEEPFOR=2;
while pgrep minishell
do
	tput clear
	leaks ${MINISH}
	sleep ${SLEEPFOR}
done
echo "${MINISH} has stopped."
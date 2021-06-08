#!/bin/bash
MINISH=minishell;
SLEEPFOR=2;
while true
do
    tput clear
    PID=$(pgrep ${MINISH})
    pstree ${PID}
    sleep ${SLEEPFOR}
done
echo "${MINISH} has stopped."

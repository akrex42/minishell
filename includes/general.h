/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:07:20 by yzombie           #+#    #+#             */
/*   Updated: 2021/04/06 11:07:21 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include <curses.h>
# include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_history_list
{
	char					*content;
	struct s_history_list	*next;
	struct s_history_list	*pred;
}	t_hystory_list;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msariasl <msariasl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:22:00 by msariasl          #+#    #+#             */
/*   Updated: 2023/05/12 11:43:35 by msariasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

extern char	**g_envv;

// src/cd_builtin.c

void	change_dir(char *path, int print_path);
int		cd_builtin(char **command);

// src/display_prompt_msg.c

void	exit_shell(void);
char	*parse_home_path(char *path, int reverse_parse);
void	display_prompt_msg(void);

// src/echo_builtin.c

int		echo_builtin(char **command);

// src/exec_command.c

int		exec_command(char **command);


// src/setenv_builtin.c

int		find_env_var(char *var);
char	*get_env_var(char *var);
char	**realloc_envv(int new_size);
void	set_env_var(char *key, char *value);
int		setenv_builtin(char **command);
int		setenv_builtin(char **args);


// src/signal_handler.c

void	signal_handler(int signo);
void	proc_signal_handler(int signo);


// src/unsetenv_builtin.c

void	print_env(void);
void	init_envv(int ac, char **av, char **envv);
int		unsetenv_builtin(char **command);

int		is_space(char x);
int		is_quote(char x);
#endif

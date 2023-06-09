/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msariasl <msariasl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:22:09 by msariasl          #+#    #+#             */
/*   Updated: 2023/05/12 11:45:59 by msariasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//string i parse eder ve değişkenleri değerlerine çevirir daha sonra parse edilmiş halini döndürür

char	**g_envv;

static	char	*parse_env_var(char *str, int pos)
{
	char	*value;
	char	*key;
	char	c;

	key = ft_strnew(1);
	while (str[pos] && !is_space(str[pos]))
	{
		c = str[pos];
		key = ft_strjoinchcl(key, c);
		pos++;
	}
	value = get_env_var(key);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	free(key);
	return (value);
}

//inputu değişken adına göre parse eder

static	char	*parse_input(char *input)
{
	int		i;
	char	*new;

	i = -1;
	new = ft_strnew(1);
	while (input[++i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			new = ft_strjoincl(new, parse_env_var(input, i + 1), 0);
			while (input[i + 1] && !is_space(input[i + 1])
				&& (input[i + 1] != '$'))
				i++;
		}
		else if (((i != 0 && is_space(input[i - 1])) || i == 0)
			&& input[i] == '~')
		{
			new = ft_strjoincl(new, parse_home_path(input + i, 1), 1);
			i += ft_strlen(input + i) - 1;
		}
		else
			new = ft_strjoinchcl(new, input[i]);
	}
	free(input);
	return (new);
}

//ekranda prompt açar ve input ile doldurur ve devam eder.


static	void	get_input(char **input)
{
	*input = readline("\033[5;91mAT\033[0m\033[5;1;92mShell: \033[0m");
	if (!*input)
	{
		free(*input);
		exit_shell();
	}
	if ((ft_strchr(*input, '$') != NULL) || (ft_strchr(*input, '~') != NULL))
		*input = parse_input(*input);
}

//çoklu komutlar ile uğraşır

int	exec_commands(char **commands)
{
	int		i;
	int		ret;
	char	**command;

	i = -1;
	ret = 0;
	while (commands[++i])
	{
		command = ft_strsplitall(commands[i]);
		ret = exec_command(command);
		ft_freestrarr(command);
		if (ret == -1)
			break ;
	}
	return (ret);
}

int	main(int ac, char **av, char **envv)
{
	char	*input;
	int		ret;
	char	**commands;

	init_envv(ac, av, envv);
	while (1)
	{
		signal(SIGINT, signal_handler);
		get_input(&input);
		add_history(input);
		if (ft_isemptystr(input, 1))
		{
			free(input);
			continue ;
		}
		commands = ft_strsplit(input, ';');
		free(input);
		ret = exec_commands(commands);
		ft_freestrarr(commands);
		if (ret == -1)
			break ;
	}
	ft_freestrarr(g_envv);
	return (0);
}

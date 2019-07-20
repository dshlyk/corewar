//
// Created by Spider soldier Bruen on 2019-07-08.
//

#include "../includes/corewar.h"

t_lexem	*check_next_lexem(t_lexem *lexem)
{
	if (lexem->next)
		lexem = lexem->next;
//	else
//	{
////		ft_error("error: incorrect file format", lexem->line, lexem->start);
//		exit(1);
//	}
	lexem = check_comment(lexem);
	return (lexem);
}

t_error *add_error(void)
{
	t_error *new_error;

	new_error = (t_error *)malloc(sizeof(t_error));
	new_error->next = NULL;
	return (new_error);
}

void ft_error(char *error, t_lexem *lexem)
{
	t_error *new_error;

	err->errors = (char *)malloc(sizeof(char) * (ft_strlen(error) + 1));
	ft_strcpy(err->errors, error);
	new_error = add_error();
	err->next = new_error;
	err = new_error;
	ft_printf("line %d:%d:\033[0;31m error: \033[0m%s\n", lexem->line + 1, lexem->start + 1, error);
	ft_printf("%s\n", helper->file[lexem->line]);
	ft_printf("\033[0;31m%*c\033[0m\n", lexem->start + 1, 94);
}

void	print_arr(char **arr)
{
	int 	j;

	j = 0;
	while (arr[j])
	{
		printf("%s\n", arr[j]);
		j++;
	}
}

void	fill_labels(t_lexem *lexem, t_helper *helper)
{
	while (lexem)
	{
		if (lexem->type == LABEL)
		{
			helper->labels = (char **)realloc(helper->labels, sizeof(char *) * (helper->count_labels + 1));
			helper->labels[helper->count_labels - 1] = ft_strdup(lexem->value);
			helper->labels[helper->count_labels] = NULL;
			helper->count_labels++;
		}
		lexem = lexem->next;
	}
//	print_arr(helper->labels);
}

void	copy_file(char **file, int lines)
{
	int 	i;

	i = 0;
	helper->file = (char **)malloc(sizeof(char *) * lines);
	while (file[i])
	{
		helper->file[i] = ft_strdup(file[i]);
		i++;
	}
	helper->file[i] = NULL;
//	print_arr(helper->file);
}

void init_structs(t_lexem *lexem, char **file, int lines)
{
	err = (t_error *)malloc(sizeof(t_error));
	helper = (t_helper *)malloc(sizeof(t_helper));
	helper->file = NULL;
	helper->labels = NULL;
	helper->count_labels = 1;
	copy_file(file, lines);
	fill_labels(lexem, helper);
	err->next = NULL;
}

t_lexem *check_comment(t_lexem *lexem)
{
	if (lexem->type == COMMENT)
	{
		if (!lexem->next)
		{
			ft_error("incorrect file", lexem);
			exit(1);
		}
		lexem = check_next_lexem(lexem);
	}
	return (lexem);
}

void start_checking(t_lexem *lexem, char **file, int lines)
{
	t_error *first_node;
	init_structs(lexem, file, lines);
	first_node = err;
	lexem = check_champion(lexem);
	while (lexem->next)
	{
		if (lexem->type == COMMAND)
		{
			ft_error("wrong command", lexem);
			lexem = check_next_lexem(lexem);
		}
		else if (lexem->type == STRING)
		{
			ft_error("wrong string", lexem);
			lexem = check_next_lexem(lexem);
		}
		else if (lexem->type == INSTRUCT)
			lexem = check_instructions(lexem);
		else if (lexem->type == LABEL)
			lexem = check_next_lexem(lexem);
		else if (lexem->type == SEP)
			lexem = check_separator(lexem);
		else if (lexem->type == UNDEF)
		{
			ft_error("undefined input", lexem);
			lexem = check_next_lexem(lexem);
		}
		else
			exit(100);
	}
}

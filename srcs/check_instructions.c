//
// Created by Spider soldier Bruen on 2019-07-08.
//

#include "../includes/corewar.h"

int 	is_number(char *num)
{
	int 	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

void 	check_reg_argument(t_lexem *lexem)
{
	if (!(is_number(lexem->value) && ft_atoi(lexem->value) >= 0 &&
	ft_atoi(lexem->value) <= REG_NUMBER))
		ft_error("incorrect T_REG argument", lexem);
}

void 	check_dir_indir_argument(t_lexem *lexem)
{
	if (!(is_number(lexem->value)))
	{
		if (lexem->type == DIR)
			ft_error("incorrect T_DIR argument", lexem);
		else
			ft_error("incorrect T_IND argument", lexem);
	}
}

void 	check_label_argument(t_lexem *lexem)
{
	if (!(check_label_name(lexem->value)))
	{
		if (lexem->type == DIR_LABEL)
			ft_error("incorrect T_DIR argument", lexem);
		else
			ft_error("incorrect T_IND argument", lexem);
	}
}

int 	check_argument_type(t_lexem *lexem, int i, int j)
{
	if (g_operations[i].args[j] == 7)
		return (1);
	else if (lexem->type == REG)
	{
		if (g_operations[i].args[j] == 1 || g_operations[i].args[j] == 3 ||
		g_operations[i].args[j] == 5)
			return (1);
	}
	else if (lexem->type == DIR || lexem->type == DIR_LABEL)
	{
		if (g_operations[i].args[j] == 2 || g_operations[i].args[j] == 3 ||
		g_operations[i].args[j] == 6)
			return (1);
	}
	else if (lexem->type == INDIR || lexem->type == INDIR_LABEL)
	{
		if (g_operations[i].args[j] == 4 || g_operations[i].args[j] == 5 ||
		g_operations[i].args[j] == 6)
			return (1);
	}
	return (0);
}

t_lexem	*check_instructions_arguments(t_lexem *lexem, int inst_index)
{
	int 	i;

	i = 0;
	while (g_operations[inst_index].count_args > i)
	{
		lexem = check_next_lexem(lexem);
		if (!check_argument_type(lexem, inst_index, i))
			ft_error("incorrect argument type", lexem);
		if (lexem->type == REG)
			check_reg_argument(lexem);
		else if (lexem->type == DIR || lexem->type == INDIR)
			check_dir_indir_argument(lexem);
		else if (lexem->type == DIR_LABEL || lexem->type == INDIR_LABEL)
			check_label_argument(lexem);
		else if (lexem->type == SEP)
		{
			if (lexem->value[0] == SEPARATOR_CHAR)
				ft_error("too many separators", lexem);
			else
				ft_error("wrong separator", lexem);
			lexem = check_next_lexem(lexem);
		}
		else
			ft_error("wrong argument type", lexem);
		if (g_operations[inst_index].count_args > (i + 1)) {
			lexem = check_separator(lexem);
		}
		i++;
	}
	lexem = check_next_lexem(lexem);
	return (lexem);
}

int 	check_instruction_names(t_lexem *lexem)
{
	int 	i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(lexem->value, g_operations[i].name))
			return (i);
		i++;
	}
	return (-1);
}

t_lexem	*check_instructions(t_lexem *lexem)
{
	int 	inst_index;

	if ((inst_index = check_instruction_names(lexem)) < 0)
	{
		ft_error("instruction doesn't exist", lexem);
		lexem = check_next_lexem(lexem);
		while (lexem)
		{
			if (lexem->type == REG || lexem->type == DIR || lexem->type == INDIR ||
			lexem->type == INDIR || lexem->type == INDIR_LABEL || lexem->type == SEP)
			{
				lexem = lexem->next;
//				ft_error("instruction doesn't exist", lexem->line, lexem->start);
			}
			else
				return (lexem);
		}
	}
	else
		lexem = check_instructions_arguments(lexem, inst_index);
	return (lexem);
}


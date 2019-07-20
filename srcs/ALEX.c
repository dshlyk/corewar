/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALEX.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:40:38 by vferry            #+#    #+#             */
/*   Updated: 2019/07/19 14:53:46 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_is_symbol(char **file, t_cursor *cur)
{
	if ((file[cur->line][cur->pos] >= '0' && file[cur->line][cur->pos] <= '9')
		|| (file[cur->line][cur->pos] >= 'a' && file[cur->line][cur->pos] <= 'z')
		|| file[cur->line][cur->pos] == '_')
		return (1);
	return (0);
}

int		ft_is_only_symbol(char **file, t_cursor **cur)
{
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;
	while (file[i][j])
	{
		if (!(file[i][j] >= 'a' && file[i][j] <= 'z'))
		{
			(*cur)->pos = j;
			return (1);
		}
		j++;
	}
	return (0);
	
}

int		ft_only_dig(char *line, t_cursor **cur)
{
	int		j;

	j = (*cur)->pos;
	while (line[j])
	{
		if (!ft_isdigit(line[j]))
		{
			(*cur)->pos = j;
			return 1;
		}
		j++;
	}
	if (line[j] == '\0')
	{
		(*cur)->pos = j;
		return (1);
	}
	return (0);
}

t_lexem	*ft_hand_diglex(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem *new;

	new = ft_cr_init_list(list);
	new->type = INDIR;
	new->line = (*cur)->line;
	new->start = (*cur)->pos;
	while (ft_isdigit(file[(*cur)->line][(*cur)->pos]) == 1)
		(*cur)->pos++;
	new->value = ft_strsub(file[(*cur)->line], new->start, (*cur)->pos - new->start);
	return (new);
}

t_lexem	*ft_reg_lex(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem *new;
	int		i;
	int		j;

	i = (*cur)->line;;
	j = 0;
	new = ft_cr_init_list(list);
	new->type = REG;
	new->line = (*cur)->line;
	if (file[(*cur)->line][(*cur)->pos] == '-')
	{
		(*cur)->pos++;
		new->start = (*cur)->pos - 2;
	}
	else
		new->start = (*cur)->pos - 1;
	if (ft_only_dig(file[(*cur)->line], cur) == 1)
	{
		j = (*cur)->pos;
		new->value = ft_strsub(file[i], new->start + 1, (j - (new->start + 1)));
		return (new);
	}
	return (NULL);
}

t_lexem	*ft_regchar_lexm(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem *new;
	int		i;
	int		j;

	new = ft_cr_init_list(list);
	new->type = DIR;
	new->line = (*cur)->line;
	new->start = (*cur)->pos - 1;
	if (ft_is_only_symbol(file, cur) == 1)
	{
		i = (*cur)->line;
		j = (*cur)->pos;
		new->value = ft_strsub(file[i], j - 1, (j - (j - 1)));
		return (new);
	}
	return NULL;
}

int		ft_lable_chars(t_cursor **cur, char **file, t_lexem *list)
{
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;
	(*cur)->start = -1;
	while (file[i][j])
	{
		if ((*cur)->start == -1)
			(*cur)->start = j;
		if (!(file[i][j] == '_' || (file[i][j] >= '0' && file[i][j] <= '9') ||
			(file[i][j] >= 'a' && file[i][j] <= 'z')))
		{
				(*cur)->pos = j;
				if (file[i][j] == ':')
					return (1);
				else
					break;
		}
		j++;
	}
	if (file[i][j] == '\0')
		(*cur)->pos = j;
	return (0);
}

t_lexem	*ft_labch_lex(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem *new;
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;
	new = ft_cr_init_list(list);
	new->type = LABEL;
	new->line = (*cur)->line;
	new->start = (*cur)->pos;
	new->value = ft_strsub(file[i], (*cur)->start, (j - (*cur)->start));
	(*cur)->pos++;
	return (new);
}

t_lexem	*ft_instruct_lex(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem	*new;
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;
	new = ft_cr_init_list(list);
	new->type = INSTRUCT;
	new->line = (*cur)->line;
	new->start = (*cur)->pos;
	new->value = ft_strsub(file[i], (*cur)->start, (j - (*cur)->start));
	return (new);
}

t_lexem	*ft_instal_lexm(t_cursor **cur, char **file, t_lexem *list)
{
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;
	if (file[i][j] == ',' || file[i][j] == '%' || file[i][j] == ':')
		return (0);
	if (ft_isdigit(file[i][j]) == 1)
		return ft_hand_diglex(cur, file, list);
	if (file[i][j] == 'r')
	{
		if (ft_isdigit(file[i][j + 1]) == 1 || file[i][j + 1] == '-' ||
			file[i][j + 1] == '+')
		{
			(*cur)->pos++;
			return ft_reg_lex(cur, file, list);
		}
		else if (file[(*cur)->line][(*cur)->pos + 1] >= 'a' && file[(*cur)->line][(*cur)->pos + 1] <= 'z')
		{
			if (ft_is_only_symbol(file, cur) == 1)
			{
				(*cur)->pos++;
				return (ft_regchar_lexm(cur, file, list));
			}
		}
	}
	else if (ft_is_symbol(file, (*cur)) == 1)
	{
		if (ft_lable_chars(cur, file, list) == 1)
			return ft_labch_lex(cur, file, list);
		else
			return ft_instruct_lex(cur, file, list);
	}
	return NULL;
}

/////////////////////////////////

t_lexem	*ft_direct_lex(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem	*new;
	int		i;
	int		j;

	i = (*cur)->line;
	j = 0;
	new = ft_cr_init_list(list);
	new->type = DIR;
	new->line = (*cur)->line;
	if (file[(*cur)->line][(*cur)->pos + 1] == '-')
	{
		(*cur)->pos += 2;
		new->start = (*cur)->pos - 2;
	}
	else
	{
		(*cur)->pos++;
		new->start = (*cur)->pos - 1; 
	}
	if (ft_only_dig(file[(*cur)->line], cur) == 1)
	{
		j = (*cur)->pos;	
		new->value = ft_strsub(file[i], new->start + 1, (j - (new->start + 1)));
		return (new);
	}
	return NULL;
}

int		ft_lable_check_chars(t_cursor **cur, char **file, t_lexem *list)
{
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;
	(*cur)->start = -1;
	while (file[i][j])
	{
		if ((*cur)->start == -1)
			(*cur)->start = j;
		if (!(file[i][j] == '_' || (file[i][j] >= '0' && file[i][j] <= '9') || 
			(file[i][j] >= 'a' && file[i][j] <= 'z')))
		{
			(*cur)->pos = j;
			return (1);
		}
		j++;
	}
	if (file[i][j] == '\0')
	{
		(*cur)->pos = j;
		return (1);
	}
	return (0);
}

t_lexem	*ft_direct_lab_lex(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_cr_init_list(list);
	new->type = DIR_LABEL;
	new->line = (*cur)->line;
	new->start = (*cur)->pos;
	(*cur)->pos += 2;
	if (ft_lable_check_chars(cur, file, list) == 1)
	{
		i = (*cur)->line;
		j = (*cur)->pos;
		new->value = ft_strsub(file[i], (*cur)->start, (j - (*cur)->start));
		return (new);
	}
	return NULL;
}

t_lexem	*ft_check_pct(t_cursor **cur, char **file, t_lexem *list)
{
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;
	if (ft_isdigit(file[i][j + 1]) || file[i][j + 1] == '-' || file[i][j + 1] == '+')
		return ft_direct_lex(cur, file, list);
	else if (file[i][j + 1] == ':')
		return ft_direct_lab_lex(cur, file, list);
	return NULL;
}

/////////////////////////////////////////////////////////

t_lexem	*ft_handling_sep(t_cursor **cur, t_lexem *list)
{
	t_lexem	*new;

	new = ft_cr_init_list(list);
	new->type = SEP;
	new->line = (*cur)->line;
	new->start = (*cur)->pos;
	new->value = ft_strnew(2);
	new->value[0] = ',';
	(*cur)->pos++;
	return (new);
}

//////////////////////////////////////////////////////////

t_lexem	*ft_handling_oktotopr(t_cursor **cur, t_lexem *list)
{
	t_lexem	*new;

	new = ft_cr_init_list(list);
	new->type = COMMENT;
	new->line = (*cur)->line;
	new->start = (*cur)->pos;
	new->value = ft_strnew(2);
	new->value[0] = '#';
	(*cur)->line++;
	(*cur)->pos = 0;
	return (new);
}

/////////////////////////////////////////////////////////

t_lexem *ft_indir_lexem(t_cursor **cur, char **file, t_lexem *list)
{
	t_lexem	*new;
	int		i;
	int		j;

	new = ft_cr_init_list(list);
	new->type = INDIR_LABEL;
	new->line = (*cur)->line;
	new->start = (*cur)->pos;
	(*cur)->pos++;
	i = (*cur)->line;
	j = (*cur)->pos;
	while ((file[i][j] >= '0' && file[i][j] <= '9') ||
		(file[i][j] >= 'a' && file[i][j] <= 'z') || file[i][j] == '_')
		j++;
	(*cur)->pos = j;
	new->value = ft_strsub(file[i], new->start + 1, (*cur)->pos - new->start + 1);
	return (new);
}

///////////////////////////////////////////////////////////

t_lexem	*ft_plus_lex(t_cursor **cur, char **file, t_lexem *list)
{
	int		i;
	int		j;
	int		start;
	t_lexem	*new;

	i = (*cur)->line;
	j = (*cur)->pos;
	start = j;
	j++;
	if (ft_isdigit(file[i][j]) == 1)
	{
		while (ft_isdigit(file[i][j]) == 1)
			j++;
	}
	(*cur)->pos = j;
	new = ft_cr_init_list(list);
	new->type = INDIR;
	new->line = (*cur)->line;
	new->start = start;
	new->value = ft_strsub(file[i], start, ((*cur)->pos - start));
	return new;
}

t_lexem	*ft_minus_lex(t_cursor **cur, char **file, t_lexem *list)
{
	int		i;
	int		j;
	int		start;
	t_lexem	*new;

	i = (*cur)->line;
	j = (*cur)->pos;
	start = j;
	j++;
	if (ft_isdigit(file[i][j]) == 1)
	{
		while (ft_isdigit(file[i][j]) == 1)
			j++;
	}
	(*cur)->pos = j;
	new = ft_cr_init_list(list);
	new->type = INDIR;
	new->line = (*cur)->line;
	new->start = start;
	new->value = ft_strsub(file[i], start, ((*cur)->pos - start));
	return new;
}

t_lexem *ft_p_m_lex(t_cursor **cur, char **file, t_lexem *list)
{
	if (file[(*cur)->line][(*cur)->pos] == '+')
		return ft_plus_lex(cur, file, list);
	else
		return ft_minus_lex(cur, file, list);	
}

///////////////////////////////////////////////////////

// int		ft_is_undef(char c)
// {
// 	if (ft_isdigit(c) == 1 || (c >= 'a' && c <= 'z') || c == '#' || c == ',' || c == ':'
// 		|| c == '.' || c == '"' || c == '%')
// 		return (0);
// 	return (1);
// }

// t_lexem	*ft_undef_lex(t_cursor **cur, char **file, t_lexem *list)
// {
// 	int		i;
// 	int		j;
// 	t_lexem	*new;

// 	i = (*cur)->line;
// 	j = (*cur)->pos;
// 	new = ft_cr_init_list(list);
// 	new->line = (*cur)->line;
// 	new->start = (*cur)->pos;
// 	while (ft_is_undef(file[i][j]) == 1)
// 		j++;
// 	(*cur)->pos = j;
// 	new->value = ft_strsub(file[i], new->start, ((*cur)->pos - new->start));
// 	new->type = UNDEF;
// 	return (new);
// }

t_lexem *ft_low_line_lex(t_cursor **cur, char **file, t_lexem *list)
{
	int		i;
	int		j;

	i = (*cur)->line;
	j = (*cur)->pos;

	while (file[i][j] != ' ')
	{
		if (file[i][j] == ':')
			if (ft_lable_chars(cur, file, list) == 1)
				return ft_labch_lex(cur, file, list);
		j++;
	}
	i = (*cur)->line;
	j = (*cur)->pos;
	if (file[i][j] == '_')
		return ft_undef_lex(cur, file, list);
	return NULL;
}
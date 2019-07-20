//
// Created by Spider soldier Bruen on 2019-07-07.
//

#include "../includes/corewar.h"

t_lexem	*check_separator(t_lexem *lexem)
{
	lexem = check_next_lexem(lexem);
	if (lexem->type == SEP)
	{
		if (!(ft_strlen(lexem->value) == 1 &&
			  lexem->value[0] == SEPARATOR_CHAR))
			ft_error("wrong separator", lexem);
	}
	else
		ft_error("wrong separator", lexem);
	return (lexem);
}
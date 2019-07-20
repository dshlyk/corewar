//
// Created by Spider soldier Bruen on 2019-07-07.
//

#include "../includes/corewar.h"

int 	check_label_name(char *label_name)
{
	int 	i;

	i = 0;
	while (helper->labels[i])
	{
		if (ft_strequ(helper->labels[i], label_name))
			return (1);
		i++;
	}
	return (0);
}

t_lexem	*check_label(t_lexem *lexem)
{
	if (!check_label_name(lexem->value))
		ft_error("incorrect label name", lexem);
	lexem = check_next_lexem(lexem);
	return (lexem);
}
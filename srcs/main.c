/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:30:40 by vferry            #+#    #+#             */
/*   Updated: 2019/07/19 17:36:48 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int     check_format(char *name)
{
    char *p;

    if (!(p = ft_strchr(name, '.')) || ft_strcmp(p, ".s") != 0)
        return (1);
    return (0);
}

void    ft_mount_token(t_lexem *new, t_cursor *cur, char **file)
{
    if (file[cur->line][cur->pos] == '.')
    {
        new->type = COMMAND;
        new->line = cur->line;
        new->start = cur->pos;
        cur->pos++;
    }
    else if (file[cur->line][cur->pos] == '"')
    {
        new->type = STRING;
        new->line = cur->line;
        new->start = cur->pos;
        cur->pos++;
    }
}

int     ft_is_undef(char c)
{
    if ((c >= '0' && c <= '9') ||
    (c  >= 'a' && c <= 'z'))
        return 0;
    if (c == '_')
        return 1;
    if (c == '#' ||c  == ',' ||
            c == ':')
        return 0;
    if (c  == '.' || c == '"' || c == '%')
        return 0;
    else
        return 1;
}

t_lexem *ft_undef_lex(t_cursor **cur, char **file, t_lexem *list)
{
    t_lexem *new;

    new = ft_cr_init_list(list);
    new->line = (*cur)->line;
    new->start = (*cur)->pos;
    while (ft_is_undef(file[(*cur)->line][(*cur)->pos]) == 1)
        (*cur)->pos++;
    new->value = ft_strsub(file[(*cur)->line], new->start, (*cur)->pos - new->start);
    new->type = UNDEF;
    return (new);
}

t_lexem *ft_hand_point(t_cursor **cur, char **file, t_lexem *list)
{
    int     i;
    int     j;
    t_lexem *new;

    i = (*cur)->line;
    new = ft_cr_init_list(list);
    ft_mount_token(new, (*cur), file);
    j = (*cur)->pos;
    while (file[i])
    {
        while (file[i][j])
        {
            if (file[i][j] >= 'a' && file[i][j] <= 'z')
                j++;
            else
            {
                new->value = ft_strsub(file[i], new->start + 1, (j - new->start - 1));
                (*cur)->pos = j;
                return (new);
            }
            (*cur)->pos++;
        }
    }
    return (NULL);
}

t_lexem *ft_hand_string(t_cursor **cur, char **file, t_lexem *list)
{
    int     i;
    int     j;
    int     start_i;
    char    *tmp;
    char    fl;
    t_lexem *new;

    i = (*cur)->line;
    if (!file[i])
        return NULL;
    tmp = NULL;
    fl = 0;
    start_i = (*cur)->line;
    new = ft_cr_init_list(list);
    new->value = "";
    ft_mount_token(new, (*cur), file);
    j = (*cur)->pos;
    while (file[i][j] != '"')
    {
        // ft_printf("str = %s; j = %d\n", &file[i][j], j);
        if (file[i][j] == '\0')
        {
            i++;    
            tmp = ft_strsub(file[start_i], new->start + 1, (j - new->start - 1)); //чистить
            new->value = ft_strjoin(new->value, tmp); // чистить
            j = 0;
            new->start = -1;
            start_i = i;
            fl = 1;
        }
        else
            j++;
        if (!file[i])
            return (NULL);
    }
    if (fl == 0)
    {
        new->value = ft_strsub(file[start_i], new->start + 1, (j - new->start - 1));
        (*cur)->pos = j + 1;
    }
    else
    {
        new->value = ft_strjoin(new->value, ft_strjoin(tmp, ft_strsub(file[start_i], new->start + 1, (j - new->start - 1)))); // чистить
        (*cur)->line = i;
        (*cur)->pos = j + 1;
    }
    return (new);
}

t_lexem *ft_def_lex(t_cursor *cur, char **file, t_lexem *list)
{
    if (file[cur->line][cur->pos] == '.')
        return ft_hand_point(&cur, file, list);
    else if (file[cur->line][cur->pos] == '"')
        return ft_hand_string(&cur, file, list);
    else if ((ft_is_symbol(file, cur) == 1) && file[cur->line][cur->pos] != '_')
        return ft_instal_lexm(&cur, file, list);
    else if (file[cur->line][cur->pos] == '%')
        return ft_check_pct(&cur, file, list);
    else if (file[cur->line][cur->pos] == ',')
        return ft_handling_sep(&cur, list);
    else if (file[cur->line][cur->pos] == '#' || file[cur->line][cur->pos] == ';')
        return ft_handling_oktotopr(&cur, list);
    else if (file[cur->line][cur->pos] == ':')
        return ft_indir_lexem(&cur, file, list);
    else if (file[cur->line][cur->pos] == '+' || file[cur->line][cur->pos] == '-')
        return ft_p_m_lex(&cur, file, list);
    else if (file[cur->line][cur->pos] == '_')
        return ft_low_line_lex(&cur, file, list);
    else
        return ft_undef_lex(&cur, file, list);
}

void    ft_take_lex(char **file, t_cursor *cur, t_lexem **list)
{
    t_lexem     *new;
    t_lexem     *ind;

    new = NULL;
    ind = (*list);
    while (ind && ind->next)
        ind = ind->next;
    while (file[cur->line][cur->pos] != '\0')
    {
        if (file[cur->line][cur->pos] == '\t' || file[cur->line][cur->pos] == ' ')
            cur->pos++;
        else
        {
            new = ft_def_lex(cur, file, ind);
            if (new == NULL)
                break ;
            if ((*list) == NULL)
            {
                (*list) = new;
                ind = (*list);
                new = new->next;
            }
            else
            {
                ind->next = new;
                ind = ind->next;
                new = new->next;
            }
        }
    }
}

void    print_struct(t_lexem *bitch, char fl)
{
    t_lexem *buf = bitch;
    t_lexem *rev;
    int i = 1;
    while (buf)
    {
        ft_printf("%d)Strcut:\n\ttype = %d;\n\tline = %d;\n\tstart = %d;\n\tvalue = \"%s\";\n\tposition = %d;\n", i, buf->type, buf->line, buf->start, buf->value, buf->position);
        if (buf->next == NULL)
            rev = buf;
        buf = buf->next;
        if (buf)
            i++;
    }
    if (fl == 1)
        while (rev)
        {
            ft_printf("%d)Strcut:\n\ttype = %d;\n\tline = %d;\n\tstart = %d;\n\tvalue = \"%s\"\n", i, rev->type, rev->line, rev->start, rev->value);
            rev = rev->prev;
            i--;
        }
}

t_lexem *ft_parse_file(char **file)
{
    t_lexem     *list;
    t_cursor    *cursor;

    list = NULL;
    cursor = (t_cursor *)malloc(sizeof(t_cursor));
    init_cursor(&cursor);
    while (file[cursor->line])
    { 
        cursor->pos = 0;
        ft_take_lex(file, cursor, &list);
        cursor->line++;
    }
    return (list);
}





int     ft_only_digit(char *line)
{
    int i;
    int j;

    i = 0;
    j = 0;

        while (line[j] != '\0')
        {
            if (!(line[j] >= '0' && line[j] <= '9'))
                return 1;
            j++;
        }
        if (line[j] == '\0')
            return 1;
    return  0;
}














void    ft_asm(int fd, int count, char *file_name)
{
    char    **file;
    int     i;
    t_lexem *test;
	t_lexem *res;

    i = 0;
    file = (char **)malloc(sizeof(char *) * (count + 1));
    while (i < count)
    {
        get_next_line(fd, &file[i]);
        i++;
    }
    file[i] = NULL;
    if (close(fd) < 0)
        error("I can't close file in f(asm) :(");
    test = ft_parse_file(file);
    if (!test)
        error("File is empty!");
    print_struct(test, 0);
	start_checking(test, file, i);
//    bytes(test, file_name);
//	print_struct(test, 0);

}

void    take_count_of_str(int fd, char *file)
{
    int ret;
    char c;
    int count;

    if ((ret = read(fd, 0, 0)) == -1)
        error("This is a directory!");
    count = 1;
    while ((ret = read(fd, &c, 1)))
        if (c == '\n')
            count++;
    if (close(fd) < 0)
        error("I can't close file in f(take_count_of_str) :(");
    fd = open("/Users/sbruen/Desktop/1/Batman.s", O_RDONLY);
    if (fd < 0)
        error("Sorry, I can't open of this file :(");
    ft_asm(fd, count, file);
}

int     main(int argc, char **argv)
{
    int fd;

    if (argc != 2)
        error("Not right count of arguments!");
    else
    {
        if (check_format(argv[1]) == 1)
            error("The file format is wrong!");
        fd = open("/Users/sbruen/Desktop/1/Batman.s", O_RDONLY);
        if (fd < 0)
            error("Sorry, I can't open of this file :(");
        take_count_of_str(fd, argv[1]);
    }
    return (0);
}

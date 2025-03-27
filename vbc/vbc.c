#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
    enum { ADD, MULT, VAL } type;
    int val;
    struct node *l;
    struct node *r;
} node;

node *parse_expr(char **s);

node* new_node(node n) {
    node* ret = calloc(1, sizeof(node));
    if (!ret) return NULL;
    *ret = n;
    return ret;
}

void unexpected(char c) {
    static int flag = 0;
    
    if (flag == 0)
    {
        if (c)
            printf("Unexpected token '%c'\n", c);
        else
            printf("Unexpected end of input\n");
        flag += 1;
    }

}

int accept(char **s, char c) {
    if (**s == c){
        (*s)++;
        return 1;
    }
    return 0;
}

int expect(char **s, char c) {
    if (accept(s, c)) {
        return 1;
    }
    unexpected(**s);
    return 0;
}

int eval_tree(node* tree) {
    if (tree->type == ADD)
    {
        if (tree->l || tree->r)
            return eval_tree(tree->l) + eval_tree(tree->r);
    }
    else if (tree->type == MULT)
    {
        if (tree->l || tree->r)
            return eval_tree(tree->l) * eval_tree(tree->r);
    }
    else
    {
        if (tree->val)
            return tree->val;
    }
    return (1);
}

void destroy_tree(node* tree) {
    if (tree) {
        if (tree->type != VAL) {
            destroy_tree(tree->l);
            destroy_tree(tree->r);
        }
        free(tree);
    }
}

// solution below

node    *parse_nbr(char **s)
{
    if (isdigit(**s))
    {
        node n = {.val = **s - '0', .type = VAL, .l = NULL, .r = NULL};
        (*s)++;
        return (new_node(n));
    }
    unexpected(**s);
    return (NULL);
}

node    *parse_fact(char **s)
{
    if (accept(s, '('))
    {
        node    *expr = parse_expr(s);
        if (!expect(s, ')'))
        {
            destroy_tree(expr);
            return (NULL);
        }
        return (expr);
    }
    return (parse_nbr(s));
}

node    *parse_term(char **s)
{
    node    *left = parse_fact(s);
    if (!left)
        return (NULL);
    
    while (1)
    {
        if (accept(s, '*'))
        {
            node    *right = parse_fact(s);
            if (!right)
            {
                destroy_tree(left);
                return (NULL);
            }
            node n = {.type = MULTI, .l = left, .r = right};
            left = new_node(n);
        }
        else
            break ;
    }
    return (left);
    
}

node    *parse_expr(char **s)
{
    node    *left = parse_term(s);
    if (!left)
        return (NULL);

    while (1)
    {
        if (accept(s, '+'))
        {
            node    *right = parse_term(s);
            if (!right)
            {
                destroy_tree(left);
                return (NULL);
            }
            node n = {.type = ADD, .l = left, .r = right};
            left = new_node(n);
        }
        else
            break ;
    }
    return (left);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    char    *input = argv[1];
    node *tree = parse_expr(&input);
    if (!tree)
        return (1);
    else if (*input)
    {
        unexpected(*input);
        destroy_tree(tree);
        return (1);
    }
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return (0);
}
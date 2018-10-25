#include <stdio.h>
#include <stdlib.h>


typedef struct Element
{
    int data;
    struct Element* next;
} Element;


/*Element* occu_recu(Element* liste)
{

}*/

typedef struct s_list
{
    int	data;
    struct s_list *next;
} t_list;

t_list *create_elem(int data)
{
    t_list *temp;

    temp = malloc(sizeof(t_list));
    temp->data = data;
    temp->next = NULL;
    return (temp);
}

t_list *dupl_list(t_list *l)
{
    t_list *cp;
    t_list *temp;

    if (l != NULL)
    {
        cp = create_elem(l->data);
        temp = cp;
        while (l->next != NULL)
        {
            l = l->next;
            temp->next = create_elem(l->data);
            temp = temp->next;
        }
    }
    else return (NULL);
    return (cp);
}

void delete_list(t_list *pl)
{
    if (pl == NULL) return;
    if (pl->next != NULL) delete_list(pl->next);
    free(pl);
    pl = NULL;
}

int main()
{
    t_list *list;
    t_list *cp_list;

    list = create_elem(3);
    list->next = create_elem(4);
    list->next->next = create_elem(5);
    list->next->next->next = create_elem(6);

    cp_list = dupl_list(list);

    delete_list(list);
    return 0;
}


#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void bubble_sort(char *set, int size)
{
    // tri des nb
    int i;
    int j;
    char tmp;
    
    i = 0;
   
    while (i < size -1)
    {
        j = 0;
        while (j < size -1 -i)
        {
            if (set[j] > set[j + 1])
            {
               tmp = set[j + 1];
               set[j + 1] = set[j];
               set[j] = tmp;
            } 
            j++;
        }
        i++;
    }
}
void process(char *set, int size, char *temp, int *placed, int idx)
{
    int i;

    i = 0;
    if (idx == size)
    {
        temp[idx] = '\0';
        puts(temp);
        return ;
    }
    while (i < size)
    {
        if (!placed[i])
        {
            placed[i] = 1;
            temp[idx] = set[i];
            process(set, size, temp, placed, idx + 1);
            placed[i] = 0;
        }
        i++;
    }
    
}

int main(int argc, char **argv)
{

    if (argc != 2)
        return (1);
    int size;
    size = ft_strlen(argv[1]);

    char set[size];
    char temp[size + 1];
    int placed[size];
    //placer les nombres dans set et initialiser placed
    int i;

    i = 0;
    while (i < size)
    {
        set[i] = argv[1][i];
        placed[i] = 0;
        i++;
    }
    temp[size] = '\0';
    bubble_sort(set, size);
    process(set, size, temp, placed, 0);

}
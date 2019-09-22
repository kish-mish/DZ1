#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>

typedef struct plurality
{
    char *word;
    struct plurality *next;
}plurality;

int compareStr(char s1[],char s2[])
{
    int i=0;
    while(s1[i]!='\0')
    {
        if(s1[i]!=s2[i])
            return 0;
        i++;
    }
    i=0;
    while(s2[i]!='\0')
    {
        if(s1[i]!=s2[i])
            return 0;
        i++;
    }
    return 1;
}

char * enterstr()
{
    int i=0;
    char c,str[100];
    while((c=getchar())!='\n')
    {
        str[i]=c;
        i++;
    }
    str[i]='\0';
    for(i=0;str[i]!='\0';i++)
        ;
    char *prev=malloc(i*sizeof(char));
    for (int j=0;j<=i;j++)
        prev[j]=str[j];
    return prev;
}

int searchPlu(plurality **plu,char *str)
{
    plurality *tmp=(*plu);
    int i=0;
    while(tmp!=NULL)
    {
        i++;
        if(compareStr(tmp->word,str))
            return i;
        tmp=tmp->next;
    }
    return 0;
}

void pushPlu(plurality **plu)
{
    plurality *tmp=malloc(sizeof(plurality));
    char *str=enterstr();
    if(searchPlu(plu,str)==0)
    {
        tmp->word=str;
        tmp->next=(*plu);
        (*plu)=tmp;
    }
    else printf("Such an element exists\n");
}

void printPlu(plurality **plu)
{
    plurality *tmp=(*plu);
    while(tmp!=NULL)
    {
        printf("%s\n",tmp->word);
        tmp=tmp->next;
    }
}

void deletePlu(plurality **plu)
{
    plurality *tmp=(*plu);
    char *str=enterstr();
    if(tmp==NULL)
    {
        printf("Empty plurality\n");
        return;
    }
    int c=searchPlu(plu,str);
    if(c==0)
    {
        printf("No matches found\n");
        return;
    }
    if(c==1)
    {
        (*plu)=tmp->next;
        free(tmp);
        return;
    }
    for(int i=1;i<c-1;i++)
        tmp=tmp->next;
    plurality *prev=tmp->next;
    tmp->next=prev->next;
    free(prev);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    int menu,i;
    plurality *plu1=NULL,*plu2=NULL;
    printf("\n-Create the first plurality-\n");
    while (1)
    {
        printf("Enter element: ");
        pushPlu(&plu1);
        printf("Continue?\n1-Yes\\2-No\n");
        scanf("%d",&i);
        getchar();
        if(i!=1)
            break;
    }
    printf("\n-Create the second plurality-\n");
    while (1)
    {
        printf("Enter element: ");
        pushPlu(&plu2);
        printf("Continue?\n1-Yes\\2-No\n");
        scanf("%d",&i);
        getchar();
        if(i!=1)
            break;
    }
    while(1)
    {
        i=0;
        printf("\n-Menu-\n1-First plurality\n2-Second plurality\n3-Exit\nEnter number: ");
        scanf("%d",&menu);
        switch(menu)
        {
            case 1:i=1;break;
            case 2:i=2;break;
            case 3:return 0;break;
            default: printf("Invalid number\n");
        }
        while(i!=0)
        {
            printf("\n-Menu %d plurality-\n1-Print elements of the plurality\n2-Add element of the plurality\n3-Delete element of the plurality\n4-Back\nEnter number: ",i);
            scanf("%d",&menu);
            getchar();
            switch(menu)
            {
                case 1:
                    printf("\n-Print-\n");
                    if(i==1)
                        printPlu(&plu1);
                    else printPlu(&plu2);
                    break;
                case 2:
                    printf("\n-Add-\nEnter element: ");
                    if(i==1)
                        pushPlu(&plu1);
                    else pushPlu(&plu2);
                    break;
                case 3:
                    printf("\n-Remove-\nEnter element: ");
                    if(i==1)
                        deletePlu(&plu1);
                    else deletePlu(&plu2);
                    break;
                case 4: i=0;break;
                default: printf("Invalid number\n");
            }
        }
    }
    return 0;
}

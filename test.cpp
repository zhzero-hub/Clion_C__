/*****************************************************************************************
*  �½ڣ��γ���Ʊ����������
*  ��Ŀ:Huffman���������(����)��Huffman���롢��������
*	[��������]
*		��һƪ������5000�ַ���Ӣ�����£�source.txt����ͳ�Ƹ��ַ����ֵĴ�����ʵ��Huffman����
*		(code.dat)���Լ��Ա������Ľ���(recode.txt)��
*	[����Ҫ��]
*		��1�� ���ÿ���ַ����ֵĴ����ͱ���,���洢�ļ�(Huffman.txt)��
*		��2�� ��Huffman�����Ӣ�����±��������浽�ļ���(code.dat)�������������Ƕ�������ʽ��
*			  ��0 1����Ϣ�ñ���λ��ʾ���������ַ���0���͡�1����ʾ��*����
*		��3�� ʵ�ֽ��빦�ܡ�
*  ���ߣ�������
*  ���� ��2019��12��19
********************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <iostream>

typedef char TElemType;
typedef int Status;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 100			//�������������󳤶�

typedef struct
{
    unsigned int weight;		//Ȩֵ
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
}HTNode, *HuffmanTree;			//��źշ�����

typedef char * *HuffmanCode;	//��źշ����������

unsigned int Min(HuffmanTree HT, int n)
{
    unsigned int minw=0,minn=0;
    minw=INT_MAX;
    int i=1;
    for(int i=1;i<=n;i++)
    {
        if(HT[i].parent==0)
        {
            if(minw>HT[i].weight)
            {
                minw=HT[i].weight;
                minn=i;
            }
        }
    }
    HT[minn].parent=1;
    return minn;
}

/*ѡ�������HT����С��Ԫ�ص��±�*/
void Select(HuffmanTree HT, int n , unsigned int& s1, unsigned int& s2)
{
    s1=Min(HT,n);
    s2=Min(HT,n);
}

/*�����ÿ����ĸ��Ƶ��, ��ÿ����ĸ��Ȩֵ*/
Status FrequencyCoding(int letter[54])
{
    char ch;
    FILE *file;

    if((file = fopen("source.txt", "r")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(OVERFLOW);
    }

    while(!feof(file))
    {
        ch = fgetc(file);
        if(ch >= 'a' && ch <= 'z')		//������Сд��ĸ
        {
            letter[ch -'a' + 1]++;
        }
        else if(ch >= 'A' && ch <= 'B')	//�����˴�д��ĸ
        {
            letter[ch - 'A' + 27]++;
        }
        else							//���������ַ�������
            continue;
    }

    fclose(file);
    return OK;
}

/*�����շ�����*/
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n,	FILE *file1, FILE *file2)//w���n���ַ���Ȩֵ��w>0)
{
    unsigned int s1=0, s2=0, f=0, start=0, c=0;
    int i=0, m=0;
    HuffmanTree p;
    char *cd, ch;

    if(n<=1)	return;

    m = 2*n-1;			//n��Ҷ���ĺշ���������m=2n-1�����
    HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));//0�ŵ�Ԫδʹ��
    for(i=1; i<=n ; ++i)	//��Ҷ�ڵ��Ȩֵ��ֵ
    {
        HT[i].weight = w[i];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(; i<=m; i++, p++)	//����HT��ʣ���㸳��ֵ
    {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(i=n+1; i<=m; i++)	//�����շ�����
    {
        Select(HT, i-1, s1, s2);//ѡ������parentΪ0��weight��С���������s1,s2
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    /*----��Ҷ�ڵ㵽��������ÿ���ַ��ĺշ�������----*/
    HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));//����n���ַ������ͷָ��������
    cd = (char *)malloc(n * sizeof(char));		//����ÿһ����������ʱ�Ĺ����ռ�
    cd[n - 1] = '\0';			//���������־
    for(i=1; i<=n; i++)			//����ַ���շ�������
    {
        start = n-1;			//���������ʱ�Ľ���λ��
        for(c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent)//��Ҷ�ڵ㵽���ڵ����������
        {
            if(HT[f].lchild == c)
                cd[--start] = '0';//����������Ϊ'0'
            else
                cd[--start] = '1';//����������Ϊ'1'

        }
        HC[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);//�ͷſռ�

    fseek(file1, 0, SEEK_SET);			//��file1��ָ���Ƶ��ļ�source.txt�Ŀ�ͷ
    while(!feof(file1))					//����������ŵ��ļ�code.dat��
    {
        ch = fgetc(file1);
        if(ch >= 'a' && ch <= 'z')		//ָ��file1��ȡ���ַ�Ϊ��ĸ
        {
            fwrite(HC[ch -'a' + 1], sizeof(char), strlen(HC[ch -'a' + 1]), file2);
        }
        else if(ch >= 'A' && ch <= 'Z')
        {
            fwrite(HC[ch -'A' + 27], sizeof(char),strlen(HC[ch -'A' + 27]), file2);
        }
        else							//ָ��file1��ȡ���ַ�Ϊ����ĸ�� ����ո񡢻س�
        {
            fwrite(&ch, sizeof(ch), 1, file2);
        }
    }

}

/*���ַ�ch��ӵ��ַ���character�ĵ�i��λ��*/
Status AddLetter(char *character, char ch, int i)
{
    int j = 0;

    for(j = 0; j < i - 1; j++)
    {
        character++;
    }
    *character = ch;
    *(character+1)='\0';

    return OK;
}


/*���շ�������Ľ���������벢�������һ���ļ���*/
Status DecodeCoding(HuffmanCode HC, int n)
{
    int time = 0;
    char ch, str[2] = {}, character[MAXQSIZE] = {};
    FILE *file1, *file2;
    int i = 1, j = 0, k = 0, m = 2*n-1;

    if((file1 = fopen("code.dat", "rb")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(OVERFLOW);
    }

    if((file2 = fopen("recode.txt", "w")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(OVERFLOW);
    }
    while(!feof(file1))
    {
        std::cout << time ++ << std::endl;
        if(time == 52)
        {
            std::cout << "213asd";
        }
        fread(str, sizeof(char), 1, file1);
        AddLetter(character, str[0], i);
        if(strcmp(HC[i], character) == 0)
        {
            if(k <26)
            {
                ch = k + 97;
            }
            if(k >= 26 && k < 52)
            {
                ch = k + 39;
            }
            fputc(ch, file2);
            strcpy(character, " ");
            i = 0;
            k++;
        }
        else
            i++;
    }
    fclose(file1);
    fclose(file2);
    return OK;
}

int main()
{
    int i =0;
    HuffmanTree HT;				//�շ�����
    HuffmanCode HC;				//��źշ������������
    int letter[54] = {0};		//letter��������ĸ���ֵĴ��򣬼�ÿ����ĸ��Ȩ��ǰ26λΪСд��ĸ������Ϊ��д��ĸ
    FILE *file1, *file2, *file3;
    char ch;

    if((file1 = fopen("source.txt", "r")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(OVERFLOW);
    }

    if((file2 = fopen("code.dat", "wb")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(OVERFLOW);
    }

    if((file3 = fopen("recode.txt", "w")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(OVERFLOW);
    }

    FrequencyCoding(letter);
    HuffmanCoding(HT, HC, letter, 52, file1, file2);
    DecodeCoding(HC, 52);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    return 0;
}

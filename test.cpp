/*****************************************************************************************
*  章节：课程设计必做题第五题
*  题目:Huffman编码与解码(必做)（Huffman编码、二叉树）
*	[问题描述]
*		对一篇不少于5000字符的英文文章（source.txt），统计各字符出现的次数，实现Huffman编码
*		(code.dat)，以及对编码结果的解码(recode.txt)。
*	[基本要求]
*		（1） 输出每个字符出现的次数和编码,并存储文件(Huffman.txt)。
*		（2） 在Huffman编码后，英文文章编码结果保存到文件中(code.dat)，编码结果必须是二进制形式，
*			  即0 1的信息用比特位表示，不能用字符’0’和’1’表示（*）。
*		（3） 实现解码功能。
*  作者：范文鑫
*  日期 ：2019年12月19
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
#define MAXQSIZE 100			//哈夫曼编码的最大长度

typedef struct
{
    unsigned int weight;		//权值
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
}HTNode, *HuffmanTree;			//存放赫夫曼树

typedef char * *HuffmanCode;	//存放赫夫曼树编码表

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

/*选择出两个HT中最小的元素的下标*/
void Select(HuffmanTree HT, int n , unsigned int& s1, unsigned int& s2)
{
    s1=Min(HT,n);
    s2=Min(HT,n);
}

/*计算出每个字母的频次, 即每个字母的权值*/
Status FrequencyCoding(int letter[54])
{
    char ch;
    FILE *file;

    if((file = fopen("source.txt", "r")) == NULL)
    {
        printf("打开文件失败！");
        exit(OVERFLOW);
    }

    while(!feof(file))
    {
        ch = fgetc(file);
        if(ch >= 'a' && ch <= 'z')		//遇到了小写字母
        {
            letter[ch -'a' + 1]++;
        }
        else if(ch >= 'A' && ch <= 'B')	//遇到了大写字母
        {
            letter[ch - 'A' + 27]++;
        }
        else							//遇到其他字符则跳过
            continue;
    }

    fclose(file);
    return OK;
}

/*建立赫夫曼树*/
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n,	FILE *file1, FILE *file2)//w存放n个字符的权值（w>0)
{
    unsigned int s1=0, s2=0, f=0, start=0, c=0;
    int i=0, m=0;
    HuffmanTree p;
    char *cd, ch;

    if(n<=1)	return;

    m = 2*n-1;			//n个叶结点的赫夫曼树共有m=2n-1个结点
    HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));//0号单元未使用
    for(i=1; i<=n ; ++i)	//将叶节点的权值赋值
    {
        HT[i].weight = w[i];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(; i<=m; i++, p++)	//将树HT的剩余结点赋初值
    {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(i=n+1; i<=m; i++)	//建立赫夫曼树
    {
        Select(HT, i-1, s1, s2);//选择两个parent为0且weight最小的两个结点s1,s2
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    /*----从叶节点到根逆向求每个字符的赫夫曼编码----*/
    HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));//分配n个字符编码的头指针吗向量
    cd = (char *)malloc(n * sizeof(char));		//分配每一次求编码过程时的工作空间
    cd[n - 1] = '\0';			//编码结束标志
    for(i=1; i<=n; i++)			//逐个字符求赫夫曼编码
    {
        start = n-1;			//逆向求编码时的结束位置
        for(c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent)//从叶节点到根节点逆向求编码
        {
            if(HT[f].lchild == c)
                cd[--start] = '0';//左子树编码为'0'
            else
                cd[--start] = '1';//右子树编码为'1'

        }
        HC[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);//释放空间

    fseek(file1, 0, SEEK_SET);			//将file1的指针移到文件source.txt的开头
    while(!feof(file1))					//将编译结果存放到文件code.dat中
    {
        ch = fgetc(file1);
        if(ch >= 'a' && ch <= 'z')		//指针file1读取的字符为字母
        {
            fwrite(HC[ch -'a' + 1], sizeof(char), strlen(HC[ch -'a' + 1]), file2);
        }
        else if(ch >= 'A' && ch <= 'Z')
        {
            fwrite(HC[ch -'A' + 27], sizeof(char),strlen(HC[ch -'A' + 27]), file2);
        }
        else							//指针file1读取的字符为非字母， 例如空格、回车
        {
            fwrite(&ch, sizeof(ch), 1, file2);
        }
    }

}

/*将字符ch添加到字符串character的第i个位置*/
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


/*将赫夫曼编码的结果进行译码并存放在另一个文件中*/
Status DecodeCoding(HuffmanCode HC, int n)
{
    int time = 0;
    char ch, str[2] = {}, character[MAXQSIZE] = {};
    FILE *file1, *file2;
    int i = 1, j = 0, k = 0, m = 2*n-1;

    if((file1 = fopen("code.dat", "rb")) == NULL)
    {
        printf("打开文件失败！");
        exit(OVERFLOW);
    }

    if((file2 = fopen("recode.txt", "w")) == NULL)
    {
        printf("打开文件失败！");
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
    HuffmanTree HT;				//赫夫曼树
    HuffmanCode HC;				//存放赫夫曼编码的数组
    int letter[54] = {0};		//letter数组存放字母出现的次序，即每个字母的权，前26位为小写字母，其余为大写字母
    FILE *file1, *file2, *file3;
    char ch;

    if((file1 = fopen("source.txt", "r")) == NULL)
    {
        printf("打开文件失败！");
        exit(OVERFLOW);
    }

    if((file2 = fopen("code.dat", "wb")) == NULL)
    {
        printf("打开文件失败！");
        exit(OVERFLOW);
    }

    if((file3 = fopen("recode.txt", "w")) == NULL)
    {
        printf("打开文件失败！");
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

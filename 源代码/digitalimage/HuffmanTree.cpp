#include <iostream>
#include<QWidget>
using namespace std;

typedef struct
{
    char character;
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;
typedef char *EachHuffcode;
class Huff
{
public:
    EachHuffcode *pbm;
    void Select(HuffmanTree HT,int length,int &s1,int &s2)
    { //找出权值最小的节点或子树，分别用s1和s2返回
        unsigned int min=0xffffffff;//给min赋初值(足够大)
        HuffmanTree p=HT;
        int i;
        for(i=1,++p;i<=length;++i,++p)
        {
            if(p->weight<min && p->parent==0)
            {
                min=p->weight;
                s1=i;
            }
        }
        min=0xFFFFFFFF;//恢复min的处置，重新开始计数找出权值第二小的节点或者子数
        p=HT;
        for(i=1,++p;i<=length;++i,++p)
        {
            if(p->weight<min&&p->parent==0)
            {
                if(i==s1) continue;//忽略权值最小的节点或子树
                min=p->weight;
                s2=i;
            }
        }
    }//Select

    void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC, int *w,int n)
    {
        if(n<=1) return;
        int m=2*n-1;//霍夫曼树的节点数
        HT=new HTNode[m+1];//多定义一位，保证第一位空置不用
        HuffmanTree p=HT;
        int i,s1,s2,c,f,start;
        for(i=1,++p;i<=n;++i,++p,++w){
            p->weight=*w;
            p->parent=p->lchild=p->rchild=0;
        }//for 把前n个节点初始化，只赋给其权值
        for(;i<=m;++i,++p) p->weight=p->parent=p->lchild=p->rchild=0;// 把后面的节点都置零
        for(i=n+1;i<=m;++i){
            Select(HT,i-1,s1,s2);
            HT[s1].parent=i;
            HT[s2].parent=i;
            HT[i].lchild=s1;
            HT[i].rchild=s2;
            HT[i].weight=HT[s1].weight+HT[s2].weight;
        }//for 构建霍夫曼树
        HC=new EachHuffcode[n+1];//多定义一位，保证第一位空置不用
        char *cd=new char[n];
        cd[n-1]='\0';//末位的标志，使传值时能到此停止
        for(i=1;i<=n;++i){//得到各节点的霍夫曼编码，并将它们记录在HC[1]到HC[n]中
            start=n-1;
            for(c=i,f=HT[i].parent; f!=0;c=f,f=HT[f].parent){
                if(c==HT[f].lchild) cd[--start]='0';
                else cd[--start]='1';
                HC[i]=new char[n-start];//给HC[]分配存储空间
                strcpy(HC[i],&cd[start]);//将cd[]所存储的霍夫曼编码传给HC[][]
            }//for
        }//for 循环赋值，得到霍夫曼树的编码
        delete []cd;//释放空间
    }//HuffmanCoding

    Huff(int x,int *weight)
    {
        HuffmanTree hftree = NULL;
        HuffmanCode hfcode = NULL;
        // int x;
        // //cout<<"Please input the number of the nodes:"<<endl;
        // cin>>x;
        // int *weight=new int [x];
        // char *character=new char[x];
        // //cout<<"Please give the "<<x<< " nodes' character:"<<endl;
        // for (int j=0; j<x; ++j) cin>> character [j];
        //// cout<<"Please give the "<<x<< " nodes' weight:"<<endl;
        // for (int j=0; j<x; ++j) {
        //   // cout<<character[j]<<": ";
        //    cin>>weight[j];
        // }//for 接收字符及对应的权值
        HuffmanCoding(hftree,hfcode,weight,x);
        pbm=hfcode;
        ++pbm;
        // for(int i=0;i<x;++i,++pbm)
        // {qDebug("%d :%s",i,*pbm);}
        //  //if(i==0)
        //	//  cout<<"The corresponding HuffmanCode of the "<<x<<" nodes are:"<<endl;
        //  //cout<<character[i]<<":"<<*p<<endl;//打印出各节点的字符及对应的霍夫曼编码，每行打印一组
        // }//for
        /*for(int i=1;i<=x;++i) delete hfcode[i];
 delete []hfcode;
 delete []hftree;/*/
        //return 0;
    }//main
};

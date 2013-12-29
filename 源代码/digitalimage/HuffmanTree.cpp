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
    { //�ҳ�Ȩֵ��С�Ľڵ���������ֱ���s1��s2����
        unsigned int min=0xffffffff;//��min����ֵ(�㹻��)
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
        min=0xFFFFFFFF;//�ָ�min�Ĵ��ã����¿�ʼ�����ҳ�Ȩֵ�ڶ�С�Ľڵ��������
        p=HT;
        for(i=1,++p;i<=length;++i,++p)
        {
            if(p->weight<min&&p->parent==0)
            {
                if(i==s1) continue;//����Ȩֵ��С�Ľڵ������
                min=p->weight;
                s2=i;
            }
        }
    }//Select

    void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC, int *w,int n)
    {
        if(n<=1) return;
        int m=2*n-1;//���������Ľڵ���
        HT=new HTNode[m+1];//�ඨ��һλ����֤��һλ���ò���
        HuffmanTree p=HT;
        int i,s1,s2,c,f,start;
        for(i=1,++p;i<=n;++i,++p,++w){
            p->weight=*w;
            p->parent=p->lchild=p->rchild=0;
        }//for ��ǰn���ڵ��ʼ����ֻ������Ȩֵ
        for(;i<=m;++i,++p) p->weight=p->parent=p->lchild=p->rchild=0;// �Ѻ���Ľڵ㶼����
        for(i=n+1;i<=m;++i){
            Select(HT,i-1,s1,s2);
            HT[s1].parent=i;
            HT[s2].parent=i;
            HT[i].lchild=s1;
            HT[i].rchild=s2;
            HT[i].weight=HT[s1].weight+HT[s2].weight;
        }//for ������������
        HC=new EachHuffcode[n+1];//�ඨ��һλ����֤��һλ���ò���
        char *cd=new char[n];
        cd[n-1]='\0';//ĩλ�ı�־��ʹ��ֵʱ�ܵ���ֹͣ
        for(i=1;i<=n;++i){//�õ����ڵ�Ļ��������룬�������Ǽ�¼��HC[1]��HC[n]��
            start=n-1;
            for(c=i,f=HT[i].parent; f!=0;c=f,f=HT[f].parent){
                if(c==HT[f].lchild) cd[--start]='0';
                else cd[--start]='1';
                HC[i]=new char[n-start];//��HC[]����洢�ռ�
                strcpy(HC[i],&cd[start]);//��cd[]���洢�Ļ��������봫��HC[][]
            }//for
        }//for ѭ����ֵ���õ����������ı���
        delete []cd;//�ͷſռ�
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
        // }//for �����ַ�����Ӧ��Ȩֵ
        HuffmanCoding(hftree,hfcode,weight,x);
        pbm=hfcode;
        ++pbm;
        // for(int i=0;i<x;++i,++pbm)
        // {qDebug("%d :%s",i,*pbm);}
        //  //if(i==0)
        //	//  cout<<"The corresponding HuffmanCode of the "<<x<<" nodes are:"<<endl;
        //  //cout<<character[i]<<":"<<*p<<endl;//��ӡ�����ڵ���ַ�����Ӧ�Ļ��������룬ÿ�д�ӡһ��
        // }//for
        /*for(int i=1;i<=x;++i) delete hfcode[i];
 delete []hfcode;
 delete []hftree;/*/
        //return 0;
    }//main
};

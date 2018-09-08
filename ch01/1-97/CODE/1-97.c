#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define TRUE 1
#define FALSE 0
#define OK 1
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
#define N 5 /* ����Ԫ�ظ��� */
typedef char KeyType; /* ��ؼ�����Ϊ�ַ��� */
typedef struct
{
  KeyType key;
  int order;
}ElemType; /* ����Ԫ������ */
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
typedef struct BSTNode
{
  ElemType data;
  int bf; /* ����ƽ������ */
  struct BSTNode *lchild,*rchild; /* ���Һ���ָ�� */
}BSTNode,*BSTree;
Status InitDSTable(BSTree *DT) /* ͬbo6-2.c */
{ /* �������: ����һ���յĶ�̬���ұ�DT */
  *DT=NULL;
  return OK;
}
void DestroyDSTable(BSTree *DT) /* ͬbo6-2.c */
{ /* ��ʼ����: ��̬���ұ�DT���ڡ��������: ���ٶ�̬���ұ�DT */
  if(*DT) /* �ǿ��� */
  {
    if((*DT)->lchild) /* ������ */
      DestroyDSTable(&(*DT)->lchild); /* ������������ */
    if((*DT)->rchild) /* ���Һ��� */
      DestroyDSTable(&(*DT)->rchild); /* �����Һ������� */
    free(*DT); /* �ͷŸ���� */
    *DT=NULL; /* ��ָ�븳0 */
  }
}
BSTree SearchBST(BSTree T,KeyType key)
{ /* �ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ� */
  /* �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ��,���򷵻ؿ�ָ�롣*/
  if((!T)||EQ(key,T->data.key))
    return T; /* ���ҽ��� */
  else if LT(key,T->data.key) /* ���������м������� */
    return SearchBST(T->lchild,key);
  else
    return SearchBST(T->rchild,key); /* ���������м������� */
}
void R_Rotate(BSTree *p)
{ /* ����*pΪ���Ķ�������������������������֮��pָ���µ�������㣬����ת */
  /* ����֮ǰ���������ĸ���㡣*/
  BSTree lc;
  lc=(*p)->lchild; /* lcָ��p������������� */
  (*p)->lchild=lc->rchild; /* lc���������ҽ�Ϊp�������� */
  lc->rchild=*p;
  *p=lc; /* pָ���µĸ���� */
}
void L_Rotate(BSTree *p)
{ /* ����*pΪ���Ķ�������������������������֮��pָ���µ�������㣬����ת */
  /* ����֮ǰ���������ĸ���㡣*/
  BSTree rc;
  rc=(*p)->rchild; /* rcָ��p������������� */
  (*p)->rchild=rc->lchild; /* rc���������ҽ�Ϊp�������� */
  rc->lchild=*p;
  *p=rc; /* pָ���µĸ���� */
}
#define LH +1 /* ��� */
#define EH 0  /* �ȸ� */
#define RH -1 /* �Ҹ� */
void LeftBalance(BSTree *T)
{ /* ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת���������㷨����ʱ�� */
  /* ָ��Tָ���µĸ���㡣*/
  BSTree lc,rd;
  lc=(*T)->lchild; /* lcָ��*T������������� */
  switch(lc->bf)
  { /* ���*T����������ƽ��ȣ�������Ӧƽ�⴦�� */
    case LH: /* �½�������*T�����ӵ��������ϣ�Ҫ������������ */
             (*T)->bf=lc->bf=EH;
             R_Rotate(T);
             break;
    case RH: /* �½�������*T�����ӵ��������ϣ�Ҫ��˫������ */
             rd=lc->rchild; /* rdָ��*T�����ӵ��������� */
             switch(rd->bf)
             { /* �޸�*T�������ӵ�ƽ������ */
               case LH: (*T)->bf=RH;
                        lc->bf=EH;
                        break;
               case EH: (*T)->bf=lc->bf=EH;
                        break;
               case RH: (*T)->bf=EH;
                        lc->bf=LH;
      }
             rd->bf=EH;
             L_Rotate(&(*T)->lchild); /* ��*T��������������ƽ�⴦�� */
             R_Rotate(T); /* ��*T������ƽ�⴦�� */
  }
}
void RightBalance(BSTree *T)
{ /* ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת���������㷨����ʱ�� */
  /* ָ��Tָ���µĸ���� */
  BSTree rc,rd;
  rc=(*T)->rchild; /* rcָ��*T������������� */
  switch(rc->bf)
  { /* ���*T����������ƽ��ȣ�������Ӧƽ�⴦�� */
    case RH: /* �½�������*T���Һ��ӵ��������ϣ�Ҫ������������ */
             (*T)->bf=rc->bf=EH;
             L_Rotate(T);
             break;
    case LH: /* �½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������ */
             rd=rc->lchild; /* rdָ��*T���Һ��ӵ��������� */
      switch(rd->bf)
             { /* �޸�*T�����Һ��ӵ�ƽ������ */
               case RH: (*T)->bf=LH;
                        rc->bf=EH;
                        break;
               case EH: (*T)->bf=rc->bf=EH;
                        break;
               case LH: (*T)->bf=EH;
                        rc->bf=RH;
             }
             rd->bf=EH;
             R_Rotate(&(*T)->rchild); /* ��*T��������������ƽ�⴦�� */
             L_Rotate(T); /* ��*T������ƽ�⴦�� */
  }
}
Status InsertAVL(BSTree *T,ElemType e,Status *taller)
{ /* ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ�� */
  /* ����Ԫ��Ϊe���½�㣬������1�����򷵻�0����������ʹ���������� */
  /* ʧȥƽ�⣬����ƽ����ת��������������taller��ӳT�������*/
  if(!*T)
  { /* �����½�㣬��"����"����tallerΪTRUE */
    *T=(BSTree)malloc(sizeof(BSTNode));
    (*T)->data=e;
    (*T)->lchild=(*T)->rchild=NULL;
    (*T)->bf=EH;
    *taller=TRUE;
  }
  else
  {
    if EQ(e.key,(*T)->data.key)
    { /* �����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ��� */
      *taller=FALSE;
      return FALSE;
    }
    if LT(e.key,(*T)->data.key)
    { /* Ӧ������*T���������н������� */
      if(!InsertAVL(&(*T)->lchild,e,taller)) /* δ���� */
        return FALSE;
      if(*taller) /*  �Ѳ��뵽*T������������������"����" */
        switch((*T)->bf) /* ���*T��ƽ��� */
        {
          case LH: /* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
                   LeftBalance(T);
                   *taller=FALSE;
                   break;
          case EH: /* ԭ�����������ȸߣ��������������߶�ʹ������ */
                   (*T)->bf=LH;
                   *taller=TRUE;
                   break;
          case RH: (*T)->bf=EH; /* ԭ�����������������ߣ������������ȸ� */
                   *taller=FALSE;
        }
    }
    else
    { /* Ӧ������*T���������н������� */
      if(!InsertAVL(&(*T)->rchild,e,taller)) /* δ���� */
        return FALSE;
      if(*taller) /* �Ѳ��뵽T����������������"����" */
        switch((*T)->bf) /* ���T��ƽ��� */
        {
          case LH: (*T)->bf=EH; /* ԭ�����������������ߣ������������ȸ� */
                   *taller=FALSE;
                   break;
          case EH: /* ԭ�����������ȸߣ��������������߶�ʹ������ */
                   (*T)->bf=RH;
                   *taller=TRUE;
	    break;
   case RH: /* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
	    RightBalance(T);
	    *taller=FALSE;
    }
    }
  }
  return TRUE;
}
void TraverseDSTable(BSTree DT,void(*Visit)(ElemType))
{ /* ��ʼ����: ��̬���ұ�DT���ڣ�Visit�ǶԽ�������Ӧ�ú��� */
  /* �������: ���ؼ��ֵ�˳���DT��ÿ�������ú���Visit()һ��������һ�� */
  if(DT)
  {
    TraverseDSTable(DT->lchild,Visit); /* ��������������� */
    Visit(DT->data); /* �ٷ��ʸ���� */
    TraverseDSTable(DT->rchild,Visit); /* ���������������� */
  }
}
void print(ElemType c)
{
  printf("(%d,%d)",c.key,c.order);
}
void main()
{
  BSTree dt,p;
  Status k;
  int i;
  KeyType j;
  ElemType r[N]={{13,1},{24,2},{37,3},{90,4},{53,5}}; /* (�Խ̿���ͼ9.12Ϊ��) */
  InitDSTable(&dt); /* ��ʼ������ */
  for(i=0;i<N;i++)
    InsertAVL(&dt,r[i],&k); /* ��ƽ������� */
  TraverseDSTable(dt,print); /* ���ؼ���˳����������� */
  printf("\n����������ҵĹؼ���: ");
  scanf("%d",&j);
  p=SearchBST(dt,j); /* ���Ҹ����ؼ��ֵļ�¼ */
  if(p)
    print(p->data);
  else
    printf("���в����ڴ�ֵ");
  printf("\n");
  DestroyDSTable(&dt);
}
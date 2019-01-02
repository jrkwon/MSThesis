/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-node.h
 *  �Լ�(��)  :
 *  ���� ���� :  �Ӽ������� ��Ÿ���� �ڷᱸ��
 *  ���� ��   :  1993. 09. 13 ~ 14
 *  ���� ��   :  �� �� ��
 *
 *  ���۱� (C) 1993 �Ѿ���б� ������Ű��а� ���п� �ΰ����ɿ�����
 *  �� ���α׷��� ���� ��� �Ǹ��� ���۱��ڰ� �����ϴ�.
 *
 *
 *  [+] �밡���� ǥ���
 *  -----------------------------------------------------
 *   ���ξ�     ��
 *  -----------------------------------------------------
 *   c          char
 *   by         unsigned char (BYTE)
 *   n          short int or int
 *   x          short int (�׷��� ��ǥ x��ǥ)
 *   y          short int (�׷��� ��ǥ y��ǥ)
 *   i          int
 *   b          int (BOOL)
 *   w          unsigned int (WORD)
 *   h          unsigned int (WORD) (HANDLE)
 *   dw         unsigned long int (DWORD)
 *   fn         Function (�Լ� ������)
 *   s          Character Array (NULL�� ���� �ʿ� ����)
 *   sz         Character String (NULL�� ������)
 *  -----------------------------------------------------
 *
 */

#ifndef _KG_NODE_H_
#define _KG_NODE_H_

/*
 *  �Ӽ������� ��Ÿ���� �ڷ� ���� 1.00 ��
 *
 *  �Ѹ� ���� (root node)
 *    1   2   3   4               MAXARC
 *  +-------------------......-------+
 *  |   |   |   |   |            |   |
 *  +-------------------......-------+
 *    |   |   |   |            |   |
 *    v   v   v   v     .....  v   v
 *
 *   �Ӽ���(MAXFVALUE��ŭ�� ������ ���� �� �ִ�. �̵� ���̿�
 *   AND, OR, NONE�� ���谡 ���� �� �ִ�),�Ǵ�
 *   root node�� �Ȱ��� ������ ����
 *
 *   ( (POS     "�װ� �л����� ������ �˾ҽ��ϴ�")
 *     (HEAD    (SYN    (TENSE  PAST)
 *               .....
 *              )
 *              (SEM    (PRED   "�˴�")
 *                      (SUBJ   "��")
 *                      .....
 *              )
 *      ....
 *    )
 *
 *  POS �� �Ӽ����� "�װ�...�˾ҽ��ϴ�"��� ���ڿ��̰�,
 *  HEAD �� �Ӽ����� SYN, SEM���� ����ִ� �� �ٸ� �������̴�.
 */

/*
 *  ���� �������� ����� ����
 */
#define MAX_ARC_CNT     8       /* �� ���� �ִ� ���� ��              */
#define MAX_FVALUE_CNT  5       /* �ִ� ������ �Ӽ���                  */

/*
 *  ���ο��� �ٷ� ���ڿ��� �ִ� ����
 */
#define MAX_STR_LEN   250

/*
 *  �Ӽ��� ������ ����
 */
#define NONE_REL        0       /* ���� ����                            */
#define AND_REL         1       /* AND ����                             */
#define OR_REL          2       /* OR ����                              */

/*
 *  �Ӽ��� ����ü
 */
typedef struct value_t {
  int  nRelation;               /* ���� (NONE, AND, OR)                 */
  char *pszStr[MAX_FVALUE_CNT]; /* �޸� �Ҵ� �� ���ڿ��� ����         */
  char *pszPtr[MAX_FVALUE_CNT]; /* �ٸ� ���ڿ��� �����͸� ����Ŵ        */
} VALUE;

/*
 *  ����(��ũ) ����ü
 *  �Ӽ��� �Ǵ� �� �ٸ� ���������� �� �� �ϳ��� ���δ�.
 *  �Ӽ����� ������, �� �ٸ� ���� �����͸� ����Ű�� �ִ� ���̰�,
 *  ���������͸� ����Ű�� ������, �Ӽ����� �����ϰ� �ִ� ���̴�.
 */
typedef struct arc_t {
  int           nFeature;       /* �Ӽ�                                 */
  VALUE         Value;          /* �Ӽ���                               */
  struct node_t *pNode;         /* �� �ٸ� ���� ������                  */
} ARC;

/*
 *  ���� ����ü
 *  ������ ������ ���� ������ �Ǿ��ְ�, ������ ���̿� ���踦
 *  ������ �� �ִ�
 */
typedef struct node_t {
  int  nRelation;
  ARC  Arc[MAX_ARC_CNT];
} NODE;

void ClearNode(NODE *pNode);
int GetFeatureNumber(char *pszFeatureStr);
int GetCategoryNumber(char *pszCategoryStr);
int GetRelationNumber(char *pszRelationStr);
int GetArcNumber(NODE *pNode, int nFeature);
int GetArcListNumber(NODE *pNode, int *pnList);
void PrintNode(NODE *pNode);
char *GetFeatureValue(NODE *pNode, int *pnList, int nNum);
int GetFeature(NODE *pNode, int *pnList);
int CheckFeature(NODE *pNode, int *pnList, int nFeature);

#endif

/* ------------------------------------------------------------------------- */

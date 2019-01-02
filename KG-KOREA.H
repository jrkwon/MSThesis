/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-korea.h
 *  �Լ�(��)  :
 *  ���� ���� :
 *  ���� ��   :  1993. 09. 17
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

#ifndef _KG_KOREA_H_
#define _KG_KOREA_H_

#define  MAX_PATH_STACK_DEPTH   25
#define  MAX_PATH_STACK_CNT     25

void InitPathStack(void);
void SortSemNode(NODE *pNode);
void GetPathStackAndPhrase(ARC *pArc, char **ppszPhrase);
NODE *GetNodePtr4List(NODE *pNode, int *pnList);
char *GetTenseMorph(char *pszStr);
void GetPrefixPhrase(NODE *pSyn, char *pszPhrase);
int GetPreEowPhrase(NODE *pSyn, char *pszPhrase);
void GenerateAuxlPhrase(NODE *pSyn, char *pszPhrase);
void GeneratePredPhrase(NODE *pSyn, char *pszPhrase);
void GenerateRefPhrase(NODE *pSyn, char *pszPhrase, int nCase);
void GenerateKoreanPhrase(int *pnPathStack, NODE *pRootNode, char *pszPhrase, char *pszResultStr);
void GenerateKoreanSentence(NODE *pSemNode, NODE *pRootNode, char *pszResultStr);

#endif

/* ------------------------------------------------------------------------- */
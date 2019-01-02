/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-reslt.c
 *  �Լ�(��)  :
 *  ���� ���� :  ������ �о �������� �ٲپ� �ش�.
 *  ���� ��   :  1993. 09. 14
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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef __TURBOC__
#include <alloc.h>
#else
#include <malloc.h>
#endif
#include <string.h>
#include "kg-reslt.h"
#include "kg-node.h"
#include "kg-ftr.h"
#include "kg-file.h"
#include "kg-util.h"
#include "kg-type.h"

static void MakeNode(NODE **ppNode, int nCurArc);
static void MakeArc(NODE *pNode);
static int ReadArc(NODE *pNode);
static int SkipRootOpenParen(void);
static int SkipRootCloseParen(void);

static int nCurArcNum = 0;   /* ���� ��忡�� ��ũ��ȣ (0 ~ MAX_ARC_CNT-1) */

/*
 *  �Է�   :  ���� �������� ������, ���ο� ���� ���� ���� ��ȣ
 *  ���   :  .
 *  ȣ���� :  ReadArc
 *  ȣ��� :
 *  ��  �� :  ������ ���ڿ� �����Ϳ��� �� �ܾ �д´�.
 */
static void MakeNode(ppNode, nCurArc)
NODE **ppNode;
int nCurArc;
{
  nCurArcNum = 0;                         /* ���� ��ũ��ȣ�� �ʱ�ȭ */
  (*ppNode)->Arc[nCurArc].pNode = (NODE *)ClearMemAlloc(1, sizeof(NODE));
  while(ReadArc((*ppNode)->Arc[nCurArc].pNode))
    ;
  if(*pszCurPtr == ')')
    pszCurPtr++;
}

/*
 *  �Է�   :  ���� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���ο� ������ �����.
 */
static void MakeArc(pNode)
NODE *pNode;
{
  char pszBuf[MAX_STR_LEN];
  int nRelation, nCnt, nTempArcNum;

  GetWord(pszBuf);
  pNode->Arc[nCurArcNum].nFeature = GetFeatureNumber(pszBuf);
  if(pNode->Arc[nCurArcNum].nFeature == -1) {
    DispErrorF(true, "�Ӽ� �̸�(%s)�� �߸� �����ϼ̽��ϴ�.\nMakeArc::kg-dict.c\n", pszBuf);
  }
  if(*pszCurPtr == '(') {                            /* ��ȣ�� �����Ѵٸ� */
    nTempArcNum = nCurArcNum;
    MakeNode(&pNode, nTempArcNum);                /* ���ο� ��带 ����� */
    nCurArcNum = nTempArcNum;
    nCurArcNum++;
  }
  else {
    GetWord(pszBuf);
    /* �Ҽ����� AND�� OR, �� ���� �Ҽ����� ��� */
    if((nRelation = GetRelationNumber(pszBuf)) != -1) {
      pNode->Arc[nCurArcNum].Value.nRelation = nRelation;
      GetWord(pszBuf);
      SkipSpace();
    }
    /* ��ȣ�� ���� ������ ������ ��� �о���δ� */
    for(nCnt = 0; nCnt < MAX_FVALUE_CNT; nCnt++) {
      pNode->Arc[nCurArcNum].Value.pszStr[nCnt] = (char *)MemAlloc(strlen(pszBuf)+1);
      strcpy(pNode->Arc[nCurArcNum].Value.pszStr[nCnt], pszBuf);
      if(*pszCurPtr == ')') {
        pszCurPtr++;
        SkipSpace();
        break;
      }
      GetWord(pszBuf);
    }
    nCurArcNum++;
    if(nCurArcNum == MAX_ARC_CNT) {
      DispErrorF(true, "(%s)���� �ִ� �������� �ʰ��ϼ̽��ϴ�.\nMakeArc::kg-dict.c", pszBuf);
    }
  }
}

/*
 *  �Է�   :  ���� ������
 *  ���   :  .
 *  ȣ���� :  MakeArc
 *  ȣ��� :
 *  ��  �� :  ���� �ϳ��� �о� �� ���� �����Ϳ� ���δ�.
 */
static int ReadArc(pNode)
NODE *pNode;
{
  if(SkipSpace() == fail)
    return fail;
  if(*pszCurPtr == '(') {
    pszCurPtr++;
    SkipSpace();
    MakeArc(pNode);
    return true;
  }
  if(*pszCurPtr == ')')
    return false;
  return true;
}

/*
 *  �Է�   :  .
 *  ���   :  ����(success) �Ǵ� ����(fail)
 *  ȣ���� :  SkipSpace
 *  ȣ��� :
 *  ��  �� :  �Ѹ� ���� ���� ��ȣ�� ����ģ��
 */
static int SkipRootOpenParen()
{
  if(SkipSpace() == fail)
    return fail;
  if(*pszCurPtr == '(') {
    pszCurPtr++;
    SkipSpace();
    return (*pszCurPtr == '(') ? success : fail;
  }
  return false;
}

/*
 *  �Է�   :  .
 *  ���   :  ����(success) �Ǵ� ����(fail)
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �Ѹ� ���� �ݴ� ��ȣ�� ����ģ��
 */
static int SkipRootCloseParen()
{
  if(*pszCurPtr == ')') {
    pszCurPtr++;
    return success;
  }
  return fail;
}

/*
 *  �Է�   :  �ؼ� ��� ���� �̸�, ����
 *  ���   :  ����(success) �Ǵ� ����(fail)
 *  ȣ���� :  OpenDataFile, CloseDataFile, SkipRootOpenParen, SkipRootCloseParen
 *            ReadArc
 *  ȣ��� :
 *  ��  �� :  �ؼ� ����� �о���δ�
 */
void ReadResultNode(pszFileName, pResultNode, bView)
char *pszFileName;
NODE *pResultNode;
int bView;
{
  if(bView) {
    printf("�� �ؼ���� ���� (%s)�� �н��ϴ�\n", pszFileName);
  }
  OpenDataFile(pszFileName);
  CheckFileHeader(szFileHeader[RESULT_HEADER]);
  if(SkipRootOpenParen()) {
    while(ReadArc(pResultNode))
      ;
    if(SkipRootCloseParen() == fail)
      DispError("��ȣ�� ���ų�, �������ϴ�.\nReadResultNode::kg-reslt.c\n", true);
  }
  CloseDataFile();
  if(bView) {
    printf("�� �о���� ����Դϴ�\n");
    PrintNode(pResultNode);
  }
}

/* ------------------------------------------------------------------------- */
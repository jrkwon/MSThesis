/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-node.c
 *  �Լ�(��)  :
 *  ���� ���� :  ���� ���� ���� �Լ���
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

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "kg-node.h"
#include "kg-ftr.h"
#include "kg-reslt.h"
#include "kg-util.h"
#include "kg-type.h"

static int MakeFeature(/* pNode, nFeature */);
static void ClearValue(/* pValue */);
static void ClearArc(/* pArc */);

/*
 *  �Է�   :  ���� ������, �Ӽ�
 *  ���   :  ���������� pNode�� ���� ���� �Ӽ� nFeature�� ��� �ִ� ���� ��ȣ
 *  ȣ���� :  .
 *  ȣ��� :
 *  ��  �� :  ���������� pNode�� �Ӽ� nFeature�� ���� �����.
 */
static int MakeFeature(pNode, nFeature)
NODE *pNode;
int nFeature;
{
  int nCnt;

  for(nCnt = 0; pNode->Arc[nCnt].nFeature && nCnt < MAX_ARC_CNT; nCnt++)
    ;
  if(nCnt != MAX_ARC_CNT) {
    pNode->Arc[nCnt].nFeature = nFeature;
    return nCnt;
  }
  DispError("�ִ� �������� �ʰ��ϼ̽��ϴ�.\nMakeFeature::kg-node.c\n", true);
  return -1;
}

/*
 *  �Է�   :  VALUE pointer
 *  ���   :  .
 *  ȣ���� :  .
 *  ȣ��� :  ClearArc
 *  ��  �� :  valuep�� ����Ű�� ������ ��� �����
 */
static void ClearValue(pValue)
VALUE *pValue;
{
  int i;

  pValue->nRelation = 0;
  for(i = 0; i < MAX_FVALUE_CNT; i++)
    pValue->pszStr[i] = NULL;
  for(i = 0; i < MAX_FVALUE_CNT; i++)
    pValue->pszPtr[i] = NULL;
}

/*
 *  �Է�   :  ARC pointer
 *  ���   :  .
 *  ȣ���� :  .
 *  ȣ��� :  ClearNode
 *  ��  �� :  pArc�� ����Ű�� ������ ��� �����
 */
static void ClearArc(pArc)
ARC *pArc;
{
  pArc->nFeature = 0;
  ClearValue(&pArc->Value);
  pArc->pNode = NULL;
}

/*
 *  �Է�   :  NODE pointer
 *  ���   :  .
 *  ȣ���� :  .
 *  ȣ��� :
 *  ��  �� :  pNode�� ����Ű�� ������ ��� �����
 */
void ClearNode(pNode)
NODE *pNode;
{
  int i;

  pNode->nRelation = 0;
  for(i = 0; i < MAX_ARC_CNT; i++)
    ClearArc(&pNode->Arc[i]);
}

/*
 *  �Է�   :  �Ӽ� ���ڿ�
 *  ���   :  ���ǵ� �Ӽ�, ������ -1
 *  ȣ���� :  .
 *  ȣ��� :
 *  ��  �� :  ���ڿ��� �ش��ϴ� �Ӽ��� ���Ѵ�(������)
 */
int GetFeatureNumber(pszFeatureStr)
char *pszFeatureStr;
{
  int i;

  for(i = 0; pszFeature[i]; i++) {
    if(!strcmp(pszFeatureStr, pszFeature[i]))
      return i;
  }
  return -1;
}

/*
 *  �Է�   :  ǰ�� ���ڿ�
 *  ���   :  ���ǵ� ǰ��, ������ -1
 *  ȣ���� :  .
 *  ȣ��� :
 *  ��  �� :  ���ڿ��� �ش��ϴ� ǰ�縦 ���Ѵ�(������)
 */
int GetCategoryNumber(pszCategoryStr)
char *pszCategoryStr;
{
  int i;

  for(i = 0; pszCategory[i]; i++) {
    if(!strcmp(pszCategoryStr, pszCategory[i]))
      return i;
  }
  return -1;
}

/*
 *  �Է�   :  ���� ���ڿ�
 *  ���   :  ���ǵ� ����, ������ -1
 *  ȣ���� :  .
 *  ȣ��� :
 *  ��  �� :  ���ڿ��� �ش��ϴ� ���踦 ���Ѵ�(������)
 */
int GetRelationNumber(pszRelationStr)
char *pszRelationStr;
{
  int i;

  for(i = 0; pszRelationStr[i]; i++) {
    if(!strcmp(pszRelationStr, pszRelation[i]))
      return i;
  }
  return -1;
}

/*
 *  �Է�   :  ���� ������, �Ӽ�
 *  ���   :  ���������� pNode�� �Ӽ� nFeature�� �ִ� ������ȣ
 *            ������, -1�� �����ش�.
 *  ȣ���� :  .
 *  ȣ��� :  GetArcListNumber
 *  ��  �� :  nFeature�� ��� �ִ� ���� ��ȣ (������)
 */
int GetArcNumber(pNode, nFeature)
NODE *pNode;
int nFeature;
{
  int nArcNum;

  for(nArcNum = 0; pNode->Arc[nArcNum].nFeature; nArcNum++)
    if(pNode->Arc[nArcNum].nFeature == nFeature)
      return nArcNum;
  return -1;
}

/*
 *  �Է�   :  ���� ������, �Ӽ��� ����Ʈ(NULL�� ������)
 *  ���   :  ���������� pNode�������� pnList�� ���� ���� ��������
 *            pnList�� ������ �Ӽ��� ��� �ִ� ������ȣ.
 *            ������, -1�� �����ش�.
 *  ȣ���� :  GetArcNumber
 *  ȣ��� :
 *  ��  �� :  pnList�� ������ �Ӽ��� ��� �ִ� ���� ��ȣ (������)
 */
int GetArcListNumber(pNode, pnList)
NODE *pNode;
int *pnList; /* NULL�� ������ ���� �迭�� ������ */
{
  NODE *pTempNode;
  int nArcNum, nCnt;

  pTempNode = pNode;

  for(nCnt = 0; pnList[nCnt]; nCnt++) {
    nArcNum = GetArcNumber(pTempNode, pnList[nCnt]);
    if(nArcNum == -1)
      DispError("�Ҽ� ����Ʈ�� �߸� �����ϼ̽��ϴ�.\nGetArcListNumber::kg-node.c", true);
    if(pnList[nCnt+1] != 0)
      pTempNode = pTempNode->Arc[nArcNum].pNode;
  }
  for(nArcNum = 0; pTempNode->Arc[nArcNum].nFeature; nArcNum++)
    if(pTempNode->Arc[nArcNum].nFeature == pnList[nCnt-1])
      return nArcNum;
  return -1;
}

/*
 *  �Է�   :  ���� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  pNode�� ����Ű�� ���� ������ ȭ�鿡 ����Ѵ�.
 */
static int nDepth = 0;

#ifndef GAP
#define GAP         10     /* ȭ�� ������ ���� ����� ���� ���� ������ ���� */
#endif

void PrintNode(pNode)
NODE *pNode;
{
  int nCnt, i;

  for(nCnt = 0; pNode->Arc[nCnt].nFeature; nCnt++) {
    if(nCnt != 0) {                    /* �� ������ ������ �ϳ� �̻��̶�� */
      for(i = 0; i < nDepth*GAP; i++)
        printf(" ");
    }
    printf("%-10s", Feature2Str(pNode->Arc[nCnt].nFeature));
    if(pNode->Arc[nCnt].pNode == NULL) {                /* ���ĸ� �κ�      */
      if(pNode->Arc[nCnt].Value.pszStr[0] != NULL) {    /* ���� ������      */
        if(pNode->Arc[nCnt].Value.nRelation)   /* ���� ������ ���谡 �ִٸ� */
          printf("%s ", pszRelation[pNode->Arc[nCnt].Value.nRelation]);
        for(i = 0; pNode->Arc[nCnt].Value.pszStr[i]; i++)
          printf("%s ", pNode->Arc[nCnt].Value.pszStr[i]); /* ���� ��´�   */
      }
      else {                 /* ���� ������ �����ͷ� ����� ���� ������ش� */
        for(i = 0; pNode->Arc[nCnt].Value.pszPtr[i]; i++)
          printf("%s(p) ", pNode->Arc[nCnt].Value.pszPtr[i]);  /* ���� ��´�  */
      }
      printf("\n");
    }
    else {                      /* ���ĸ� �κ��� �ƴ϶�� ��� ȣ���� �Ѵ�. */
      nDepth++;
      PrintNode(pNode->Arc[nCnt].pNode);
      nDepth--;
    }
  }
}

#undef  GAP

/*
 *  �Է�   :  ���� ������, �Ӽ� ����Ʈ, �Ӽ��� �� ���°
 *  ���   :  �Ӽ����� ���ڿ� ������
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���������� pNode�������� �Ӽ�����Ʈ pnList�� ���� ����,
 *            �������� nNum��°, ���� �о� �´�.
 *            �� ����Ʈ�� �������� ���ĸ����� �Ѵ�.
 */
char *GetFeatureValue(pNode, pnList, nNum)
NODE *pNode;
int pnList[];
int nNum;
{
  NODE *pTempNode;
  int nArcNum, nCnt;

  pTempNode = pNode;

  for(nCnt = 0; pnList[nCnt]; nCnt++) {
    nArcNum = GetArcNumber(pTempNode, pnList[nCnt]);
    if(nArcNum == -1)
      DispErrorF(true, "�Ҽ� ����Ʈ(%s)�� �߸� �����ϼ̽��ϴ�.\nGetFeatureValue::kg-node.c\n", Feature2Str(pnList[nCnt]));
    if(pnList[nCnt+1] != 0)
      pTempNode = pTempNode->Arc[nArcNum].pNode;
  }
  if(pTempNode->Arc[nArcNum].Value.pszStr[nNum][0] == NULL)
    DispError("�Ҽ� ����Ʈ�� ���� �ٸ��𿩾� �մϴ�.\nGetFeatureValue::kg-node.c\n", true);
  return pTempNode->Arc[nArcNum].Value.pszStr[nNum];
}

/*
 *  �Է�   :  ���� ������, �Ӽ� ����Ʈ
 *  ���   :  �Ӽ�
 *  ȣ���� :  GetArcNumber
 *  ȣ��� :
 *  ��  �� :  ���������� pNode�������� �Ӽ�����Ʈ pnList�� ���� ����
 *            pnList�� ������ �Ӽ��� ����Ű�� ���� �Ӽ��� ���Ѵ�
 *            �� pnList�� �������� ���ĸ��� �ȵȴ�.
 */
int GetFeature(pNode, pnList)
NODE *pNode;
int pnList[];
{
  NODE *pTempNode;
  int nArcNum, nCnt;

  pTempNode = pNode;
  for(nCnt = 0; pnList[nCnt]; nCnt++) {
    nArcNum = GetArcNumber(pTempNode, pnList[nCnt]);
    if(nArcNum == -1) {
      DispErrorF(true, "�Ӽ� ����Ʈ(%s)�� �߸� �����ϼ̽��ϴ�.\nGetFeature::kg-node.c\n", Feature2Str(pnList[nCnt]));
    }
    if(pnList[nCnt+1] != 0)
      pTempNode = pTempNode->Arc[nArcNum].pNode;
  }
  nArcNum = GetArcNumber(pTempNode, pnList[nCnt-1]);
  if(nArcNum == -1) {
    DispErrorF(true, "�Ӽ� ����Ʈ(%s)�� �߸� �����ϼ̽��ϴ�.\nGetFeature::kg-node.c\n", Feature2Str(pnList[nCnt-1]));
  }
  return pTempNode->Arc[nArcNum].nFeature;
}

/*
 *  �Է�   :  ���� ������, �Ӽ� ����Ʈ, �Ӽ�
 *  ���   :  �Ӽ����� ���ڿ� ������
 *  ȣ���� :  GetFeature
 *  ȣ��� :
 *  ��  �� :  ���������� pNode�������� �Ӽ�����Ʈ pnList�� ���� ����
 *            pnList�� ������ �Ӽ��� ����Ű�� ���� �Ӽ��� nFeature����
 *            �� pnList�� �������� ���ĸ��� �ȵȴ�.
 */
int CheckFeature(pNode, pnList, nFeature)
NODE *pNode;
int pnList[];
int nFeature;
{
  return (GetFeature(pNode, pnList) == nFeature) ? true : false;
}

/*
 *  �Է�   :  ���� ������(destination), ���� ������(source)
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  pSource�� ������ pDest�� �����Ѵ�.
 */
void NodeCopy(pDest, pSource)
NODE *pDest;
NODE *pSource;
{
  int nCnt2, nCnt1;

  for(nCnt1 = 0; pSource->Arc[nCnt1].nFeature; nCnt1++) {
    pDest->Arc[nCnt1].nFeature = pSource->Arc[nCnt1].nFeature;
    if(pSource->Arc[nCnt1].pNode == NULL) {   /* ���ĸ� ����� */
      for(nCnt2 = 0; pSource->Arc[nCnt1].Value.pszStr[nCnt2] && nCnt2 < MAX_FVALUE_CNT; nCnt2++) {
        pDest->Arc[nCnt1].Value.pszStr[nCnt2] = (char *)MemAlloc(strlen(pSource->Arc[nCnt1].Value.pszStr[nCnt2])+1);
        strcpy(pDest->Arc[nCnt1].Value.pszStr[nCnt2], pSource->Arc[nCnt1].Value.pszStr[nCnt2]);
      }
    }
    else {
      pDest->Arc[nCnt1].pNode = (NODE *)ClearMemAlloc(1, sizeof(NODE));
      NodeCopy(pDest->Arc[nCnt1].pNode, pSource->Arc[nCnt1].pNode);
    }
  }
}


/* ------------------------------------------------------------------------- */

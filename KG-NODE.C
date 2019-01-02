/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-node.c
 *  함수(들)  :
 *  파일 설명 :  마디 구조 조작 함수들
 *  만든 날   :  1993. 09. 13 ~ 14
 *  만든 이   :  권 재 락
 *
 *  저작권 (C) 1993 한양대학교 전자통신공학과 대학원 인공지능연구실
 *  이 프로그램에 대한 모든 권리는 저작권자가 가집니다.
 *
 *
 *  [+] 헝가리식 표기법
 *  -----------------------------------------------------
 *   접두어     뜻
 *  -----------------------------------------------------
 *   c          char
 *   by         unsigned char (BYTE)
 *   n          short int or int
 *   x          short int (그래픽 좌표 x좌표)
 *   y          short int (그래픽 좌표 y좌표)
 *   i          int
 *   b          int (BOOL)
 *   w          unsigned int (WORD)
 *   h          unsigned int (WORD) (HANDLE)
 *   dw         unsigned long int (DWORD)
 *   fn         Function (함수 포인터)
 *   s          Character Array (NULL로 끝날 필요 없다)
 *   sz         Character String (NULL로 끝난다)
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
 *  입력   :  마디 포인터, 속성
 *  출력   :  마디포인터 pNode에 새로 만든 속성 nFeature가 들어 있는 가지 번호
 *  호출함 :  .
 *  호출됨 :
 *  설  명 :  마디포인터 pNode에 속성 nFeature를 새로 만든다.
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
  DispError("최대 가지수를 초과하셨습니다.\nMakeFeature::kg-node.c\n", true);
  return -1;
}

/*
 *  입력   :  VALUE pointer
 *  출력   :  .
 *  호출함 :  .
 *  호출됨 :  ClearArc
 *  설  명 :  valuep가 가리키는 내용을 모두 지운다
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
 *  입력   :  ARC pointer
 *  출력   :  .
 *  호출함 :  .
 *  호출됨 :  ClearNode
 *  설  명 :  pArc가 가리키는 내용을 모두 지운다
 */
static void ClearArc(pArc)
ARC *pArc;
{
  pArc->nFeature = 0;
  ClearValue(&pArc->Value);
  pArc->pNode = NULL;
}

/*
 *  입력   :  NODE pointer
 *  출력   :  .
 *  호출함 :  .
 *  호출됨 :
 *  설  명 :  pNode가 가리키는 내용을 모두 지운다
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
 *  입력   :  속성 문자열
 *  출력   :  정의된 속성, 없으면 -1
 *  호출함 :  .
 *  호출됨 :
 *  설  명 :  문자열에 해당하는 속성을 구한다(정수값)
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
 *  입력   :  품사 문자열
 *  출력   :  정의된 품사, 없으면 -1
 *  호출함 :  .
 *  호출됨 :
 *  설  명 :  문자열에 해당하는 품사를 구한다(정수값)
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
 *  입력   :  관계 문자열
 *  출력   :  정의된 관계, 없으면 -1
 *  호출함 :  .
 *  호출됨 :
 *  설  명 :  문자열에 해당하는 관계를 구한다(정수값)
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
 *  입력   :  마디 포인터, 속성
 *  출력   :  마디포인터 pNode에 속성 nFeature가 있는 가지번호
 *            없으면, -1을 돌려준다.
 *  호출함 :  .
 *  호출됨 :  GetArcListNumber
 *  설  명 :  nFeature가 들어 있는 가지 번호 (정수값)
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
 *  입력   :  마디 포인터, 속성의 리스트(NULL로 끝나는)
 *  출력   :  마디포인터 pNode에서부터 pnList에 따라 마디를 내려가서
 *            pnList의 마지막 속성이 들어 있는 가지번호.
 *            없으면, -1을 돌려준다.
 *  호출함 :  GetArcNumber
 *  호출됨 :
 *  설  명 :  pnList의 마지막 속성이 들어 있는 가지 번호 (정수값)
 */
int GetArcListNumber(pNode, pnList)
NODE *pNode;
int *pnList; /* NULL로 끝나는 정수 배열의 포인터 */
{
  NODE *pTempNode;
  int nArcNum, nCnt;

  pTempNode = pNode;

  for(nCnt = 0; pnList[nCnt]; nCnt++) {
    nArcNum = GetArcNumber(pTempNode, pnList[nCnt]);
    if(nArcNum == -1)
      DispError("소성 리스트를 잘못 지정하셨습니다.\nGetArcListNumber::kg-node.c", true);
    if(pnList[nCnt+1] != 0)
      pTempNode = pTempNode->Arc[nArcNum].pNode;
  }
  for(nArcNum = 0; pTempNode->Arc[nArcNum].nFeature; nArcNum++)
    if(pTempNode->Arc[nArcNum].nFeature == pnList[nCnt-1])
      return nArcNum;
  return -1;
}

/*
 *  입력   :  마디 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  pNode가 가리키는 마디 구조를 화면에 출력한다.
 */
static int nDepth = 0;

#ifndef GAP
#define GAP         10     /* 화면 위에서 상위 마디와 하위 마디 사이의 공백 */
#endif

void PrintNode(pNode)
NODE *pNode;
{
  int nCnt, i;

  for(nCnt = 0; pNode->Arc[nCnt].nFeature; nCnt++) {
    if(nCnt != 0) {                    /* 이 마디의 가지가 하나 이상이라면 */
      for(i = 0; i < nDepth*GAP; i++)
        printf(" ");
    }
    printf("%-10s", Feature2Str(pNode->Arc[nCnt].nFeature));
    if(pNode->Arc[nCnt].pNode == NULL) {                /* 잎파리 부분      */
      if(pNode->Arc[nCnt].Value.pszStr[0] != NULL) {    /* 값이 있으면      */
        if(pNode->Arc[nCnt].Value.nRelation)   /* 값들 사이의 관계가 있다면 */
          printf("%s ", pszRelation[pNode->Arc[nCnt].Value.nRelation]);
        for(i = 0; pNode->Arc[nCnt].Value.pszStr[i]; i++)
          printf("%s ", pNode->Arc[nCnt].Value.pszStr[i]); /* 값을 찍는다   */
      }
      else {                 /* 값이 없으면 포인터로 연결된 값을 출력해준다 */
        for(i = 0; pNode->Arc[nCnt].Value.pszPtr[i]; i++)
          printf("%s(p) ", pNode->Arc[nCnt].Value.pszPtr[i]);  /* 값을 찍는다  */
      }
      printf("\n");
    }
    else {                      /* 잎파리 부분이 아니라면 재귀 호출을 한다. */
      nDepth++;
      PrintNode(pNode->Arc[nCnt].pNode);
      nDepth--;
    }
  }
}

#undef  GAP

/*
 *  입력   :  마디 포인터, 속성 리스트, 속성값 중 몇번째
 *  출력   :  속성값의 문자열 포인터
 *  호출함 :
 *  호출됨 :
 *  설  명 :  마디포인터 pNode에서부터 속성리스트 pnList를 따라 가서,
 *            마지막에 nNum번째, 값을 읽어 온다.
 *            ※ 리스트의 마지막은 잎파리여야 한다.
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
      DispErrorF(true, "소성 리스트(%s)를 잘못 지정하셨습니다.\nGetFeatureValue::kg-node.c\n", Feature2Str(pnList[nCnt]));
    if(pnList[nCnt+1] != 0)
      pTempNode = pTempNode->Arc[nArcNum].pNode;
  }
  if(pTempNode->Arc[nArcNum].Value.pszStr[nNum][0] == NULL)
    DispError("소성 리스트의 끝은 잎마디여야 합니다.\nGetFeatureValue::kg-node.c\n", true);
  return pTempNode->Arc[nArcNum].Value.pszStr[nNum];
}

/*
 *  입력   :  마디 포인터, 속성 리스트
 *  출력   :  속성
 *  호출함 :  GetArcNumber
 *  호출됨 :
 *  설  명 :  마디포인터 pNode에서부터 속성리스트 pnList를 따라 가서
 *            pnList의 마지막 속성이 가리키는 곳의 속성을 구한다
 *            ※ pnList의 마지막이 잎파리면 안된다.
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
      DispErrorF(true, "속성 리스트(%s)를 잘못 지정하셨습니다.\nGetFeature::kg-node.c\n", Feature2Str(pnList[nCnt]));
    }
    if(pnList[nCnt+1] != 0)
      pTempNode = pTempNode->Arc[nArcNum].pNode;
  }
  nArcNum = GetArcNumber(pTempNode, pnList[nCnt-1]);
  if(nArcNum == -1) {
    DispErrorF(true, "속성 리스트(%s)를 잘못 지정하셨습니다.\nGetFeature::kg-node.c\n", Feature2Str(pnList[nCnt-1]));
  }
  return pTempNode->Arc[nArcNum].nFeature;
}

/*
 *  입력   :  마디 포인터, 속성 리스트, 속성
 *  출력   :  속성값의 문자열 포인터
 *  호출함 :  GetFeature
 *  호출됨 :
 *  설  명 :  마디포인터 pNode에서부터 속성리스트 pnList를 따라 가서
 *            pnList의 마지막 속성이 가리키는 곳의 속성이 nFeature인지
 *            ※ pnList의 마지막이 잎파리면 안된다.
 */
int CheckFeature(pNode, pnList, nFeature)
NODE *pNode;
int pnList[];
int nFeature;
{
  return (GetFeature(pNode, pnList) == nFeature) ? true : false;
}

/*
 *  입력   :  마디 포인터(destination), 마디 포인터(source)
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  pSource의 내용을 pDest로 복사한다.
 */
void NodeCopy(pDest, pSource)
NODE *pDest;
NODE *pSource;
{
  int nCnt2, nCnt1;

  for(nCnt1 = 0; pSource->Arc[nCnt1].nFeature; nCnt1++) {
    pDest->Arc[nCnt1].nFeature = pSource->Arc[nCnt1].nFeature;
    if(pSource->Arc[nCnt1].pNode == NULL) {   /* 잎파리 마디면 */
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


/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-reslt.c
 *  함수(들)  :
 *  파일 설명 :  사전을 읽어서 마디구조로 바꾸어 준다.
 *  만든 날   :  1993. 09. 14
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

static int nCurArcNum = 0;   /* 현재 노드에서 아크번호 (0 ~ MAX_ARC_CNT-1) */

/*
 *  입력   :  마디 포인터의 포인터, 새로운 마디를 만들 가지 번호
 *  출력   :  .
 *  호출함 :  ReadArc
 *  호출됨 :
 *  설  명 :  현재의 문자열 포인터에서 한 단어를 읽는다.
 */
static void MakeNode(ppNode, nCurArc)
NODE **ppNode;
int nCurArc;
{
  nCurArcNum = 0;                         /* 현재 아크번호를 초기화 */
  (*ppNode)->Arc[nCurArc].pNode = (NODE *)ClearMemAlloc(1, sizeof(NODE));
  while(ReadArc((*ppNode)->Arc[nCurArc].pNode))
    ;
  if(*pszCurPtr == ')')
    pszCurPtr++;
}

/*
 *  입력   :  마디 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  새로운 가지를 만든다.
 */
static void MakeArc(pNode)
NODE *pNode;
{
  char pszBuf[MAX_STR_LEN];
  int nRelation, nCnt, nTempArcNum;

  GetWord(pszBuf);
  pNode->Arc[nCurArcNum].nFeature = GetFeatureNumber(pszBuf);
  if(pNode->Arc[nCurArcNum].nFeature == -1) {
    DispErrorF(true, "속성 이름(%s)을 잘못 지정하셨습니다.\nMakeArc::kg-dict.c\n", pszBuf);
  }
  if(*pszCurPtr == '(') {                            /* 괄호로 시작한다면 */
    nTempArcNum = nCurArcNum;
    MakeNode(&pNode, nTempArcNum);                /* 새로운 노드를 만든다 */
    nCurArcNum = nTempArcNum;
    nCurArcNum++;
  }
  else {
    GetWord(pszBuf);
    /* 소성값이 AND나 OR, 즉 복수 소성값인 경우 */
    if((nRelation = GetRelationNumber(pszBuf)) != -1) {
      pNode->Arc[nCurArcNum].Value.nRelation = nRelation;
      GetWord(pszBuf);
      SkipSpace();
    }
    /* 괄호가 닫힐 때까지 값들을 모두 읽어들인다 */
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
      DispErrorF(true, "(%s)에서 최대 가지수를 초과하셨습니다.\nMakeArc::kg-dict.c", pszBuf);
    }
  }
}

/*
 *  입력   :  마디 포인터
 *  출력   :  .
 *  호출함 :  MakeArc
 *  호출됨 :
 *  설  명 :  가지 하나를 읽어 들어서 마디 포인터에 붙인다.
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
 *  입력   :  .
 *  출력   :  성공(success) 또는 실패(fail)
 *  호출함 :  SkipSpace
 *  호출됨 :
 *  설  명 :  뿌리 마디를 여는 괄호를 지나친다
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
 *  입력   :  .
 *  출력   :  성공(success) 또는 실패(fail)
 *  호출함 :
 *  호출됨 :
 *  설  명 :  뿌리 마디를 닫는 괄호를 지나친다
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
 *  입력   :  해석 결과 파일 이름, 갯수
 *  출력   :  성공(success) 또는 실패(fail)
 *  호출함 :  OpenDataFile, CloseDataFile, SkipRootOpenParen, SkipRootCloseParen
 *            ReadArc
 *  호출됨 :
 *  설  명 :  해석 결과를 읽어들인다
 */
void ReadResultNode(pszFileName, pResultNode, bView)
char *pszFileName;
NODE *pResultNode;
int bView;
{
  if(bView) {
    printf("♥ 해석결과 파일 (%s)을 읽습니다\n", pszFileName);
  }
  OpenDataFile(pszFileName);
  CheckFileHeader(szFileHeader[RESULT_HEADER]);
  if(SkipRootOpenParen()) {
    while(ReadArc(pResultNode))
      ;
    if(SkipRootCloseParen() == fail)
      DispError("괄호가 남거나, 빠졌습니다.\nReadResultNode::kg-reslt.c\n", true);
  }
  CloseDataFile();
  if(bView) {
    printf("♥ 읽어들인 결과입니다\n");
    PrintNode(pResultNode);
  }
}

/* ------------------------------------------------------------------------- */

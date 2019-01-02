/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-main.c
 *  함수(들)  :
 *  파일 설명 :  생성기 주 함수
 *  만든 날   :  1993. 09. 15
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
#include "kg-node.h"
#include "kg-type.h"
#include "kg-ftr.h"

#ifndef __LARGE__
#error Complile at large memory model in MS-DOS
#endif

char szEEOWTableFileName[] = "kg-eend.dat";
char szNEOWTableFileName[] = "kg-nend.dat";
char szCaseTableFileName[] = "kg-case.dat";
char szAuxlTableFileName[] = "kg-auxl.dat";

char szTitle[]
 = "The Korean Sentence Generator Ｒｏｃｋ-Ⅱ (C) 1993 Copyright\n\
Department of Electronic Communication Engineering Hanyang University\n\
Artificial Intellegent Lab. Natural Language Processing Group\n\n\
한국어 문장 생성기 돌-2\n\
저작권 1993 (저) 한양대학교 전자통신공학과 인공지능연구실\n\n";

char szHelp[] = "사용법 : kg-rock <파일이름> [선택]\n\n\
  선택 v: 중간과정 보기\n\n";

/*
 *  입력   :  해석결과를 담은 파일 이름
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :  해석 결과 파일을 읽어들여 한국어 생성을 한다.
 */
int main(nArgc, pszArgv)
int   nArgc;
char *pszArgv[];
{
  NODE Node, Sem, *pTempNode;
  char *pszResultFile;
  char szResultStr[MAX_STR_LEN];
  int nArcNum, bView;

  if(nArgc != 2 && nArgc != 3) {
    fprintf(stderr, szTitle);
    fprintf(stderr, szHelp);
    return false;
  }

  fprintf(stderr, szTitle);
  bView = (pszArgv[2][0] == 'v') ? true : false;
  pszResultFile = pszArgv[1];

  ReadEEndOfWordTable(szEEOWTableFileName, bView);
  ReadNEndOfWordTable(szNEOWTableFileName, bView);
  ReadCaseTable(szCaseTableFileName, bView);
  ReadAuxlTable(szAuxlTableFileName, bView);

  szResultStr[0] = NULL;
  ClearNode(&Node);
  ReadResultNode(pszResultFile, &Node, bView);

  ClearNode(&Sem);
  nArcNum = GetArcNumber(&Node, HEAD);
  if(nArcNum == -1)
    DispError("잘못된 마디 구조입니다. [kg-main.c :: main]", true);
  pTempNode = Node.Arc[nArcNum].pNode;

  nArcNum = GetArcNumber(pTempNode, SEM);
  if(nArcNum == -1)
    DispError("잘못된 마디 구조입니다. [kg-main.c :: main]", true);

  NodeCopy(&Sem, pTempNode->Arc[nArcNum].pNode);

  SortSemNode(&Sem);
  GenerateKoreanSentence(&Sem, &Node, szResultStr, bView);

  printf("\n\n♥ 한국어 생성결과입니다.");
  printf("\n\n%s\n", szResultStr);
  return true;
}

/* ------------------------------------------------------------------------- */


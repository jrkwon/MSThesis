/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-file.c
 *  함수(들)  :
 *  파일 설명 :  생성용 사전 파일 따위를 관리.
 *  만든 날   :  1993. 09. 26
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

/*
 *  이 파일 관리 함수를 쓴다면  한번에 한 개의 파일만을 다룰 수 있다.
 *  하나의 파일을 열었으면 파일을 꼭 닫고 다시 다른 파일을 열어야 한다.
 */

#include <stdio.h>
#include "kg-node.h"
#include "kg-file.h"
#include "kg-type.h"

/*
 *  한 줄의 최대 길이
 *  ※ 해석결과 파일을 읽기 위해 넉넉하게 잡았다.
 */
#define MAX_LINE_LEN        MAX_STR_LEN*4

char *szFileHeader[] = {
  "[해석결과]", "[종결어미]", "[비종결어미]", "[조사]", "[보조용언]"
};
char *pszCurPtr;                            /* szLineBuf내에서 현재 포인터 */

static char szLineBuf[MAX_LINE_LEN];          /* 한줄을 읽어들여 놓는 버퍼 */
static int  bFileOpen;                    /* 파일을 열었는지에 대한 플래그 */
static FILE *pfData;                             /* 자료파일의 파일 포인터 */

/*
 *  입력   :  파일 이름
 *  출력   :  성공(success) 또는 실패(fail)
 *  호출함 :
 *  호출됨 :
 *  설  명 :  파일을 읽기 속성으로 연다
 */
int OpenDataFile(pszFileName)
char *pszFileName;
{
  if(bFileOpen)
    DispErrorF(true, "(%s) 파일 열기 실패 !\n열어둔 파일을 먼저 닫아주십시요 [kg-file.c::OpenDataFile]", pszFileName);
  pfData = fopen(pszFileName, "r");
  if(!pfData) {
    fprintf(stderr, "%s : 자료 파일이 없습니다.\n", pszFileName);
  }
  *(pszCurPtr = szLineBuf) = NULL;
  bFileOpen = true;
  return pfData ? success : fail;
}

/*
 *  입력   :  .
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  자료 파일을 닫는다.
 */
void CloseDataFile()
{
  bFileOpen = false;
  fclose(pfData);
}

/*
 *  입력   :  .
 *  출력   :  읽어들인 줄의 문자열 포인터
 *  호출함 :
 *  호출됨 :
 *  설  명 :  자료 파일에서 한줄을 읽어 들인다.
 */
char *ReadLine()
{
  *(pszCurPtr = szLineBuf) = NULL;
  return fgets(szLineBuf, MAX_LINE_LEN, pfData);
}


/*
 *  입력   :  .
 *  출력   :  성공하면 success, 파일 끝에 도달하면 fail
 *  호출함 :  ReadLine, IsComment(매크로)
 *  호출됨 :
 *  설  명 :  공백을 건너 뛴다, 줄 끝이라면, 다음 줄을 읽어들이고
 *            거기에서 다시 공백을 건너 뛴다.
 */
int SkipSpace()
{
  while( true ) {
    while(IsComment(pszCurPtr)) {
      ReadLine();
    }
#ifdef __TURBOC__
    while(isspace((unsigned char)*pszCurPtr)) {
      ++pszCurPtr;
    }
#else
    while(isspace(*pszCurPtr)) {
      ++pszCurPtr;
    }
#endif
    while(IsComment(pszCurPtr)) {
      ReadLine();
    }
    if(*pszCurPtr != NULL) {
      return success;
    }
    if(ReadLine() == NULL) {
      return fail;
    }
  }
}

/*
 *  입력   :  결과를 담을 문자열 포인터.
 *  출력   :  .
 *  호출함 :  SkipSpace
 *  호출됨 :
 *  설  명 :  현재의 문자열 포인터에서 한 단어를 읽는다.
 */
char *GetWord(pszBuf)
char *pszBuf;
{
  char *pszTemp;

  pszTemp = pszBuf;
  SkipSpace();
  while (true) {
#ifdef __TURBOC__
    if(isspace((unsigned char)*pszCurPtr) || *pszCurPtr == ')') {
#else
    if(isspace(*pszCurPtr) || *pszCurPtr == ')') {
#endif
      *pszTemp =  NULL;
      SkipSpace();
      return pszBuf;
    }
    *pszTemp++ = *pszCurPtr++;
  }
}

/*
 *  입력   :  .
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  파일 머리부분을 검사 한다
 */
void CheckFileHeader(pszFileHeader)
char *pszFileHeader;
{
  if(SkipSpace() == fail)
    DispErrorF(true, "파일 머리가 있어야 합니다 (%s)\n", pszFileHeader);
  if(!strncmp(pszCurPtr, pszFileHeader, strlen(pszFileHeader)))
    ReadLine();
  else
    DispErrorF(true, "잘못된 파일 머리 (%s)입니다\n", pszFileHeader);
}


/* ------------------------------------------------------------------------- */

/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-util.c
 *  함수(들)  :
 *  파일 설명 :
 *  만든 날   :  1993. 09. 14
 *  만든 이   :  권 재 락
 *
 *  저작권 (C) 1993 한양대학교 전자통신공학과 대학원 인공지능연구실
 *  이 프로그램에 대한 모든 권리는 저작권자가 가집니다.
 *
 *
 *  [+] 헝가리안 표기법
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
#include <stdarg.h>
#ifdef __TURBOC__
#include <alloc.h>
#else
#include <malloc.h>
#endif
#include "kg-util.h"
#include "kg-node.h"

/*
 *  입력   : 오류 문자열, 치명적 오류인지 아닌지
 *  출력   : .
 *  호출함 : .
 *  호출됨 : .
 *  설  명 : 일반적인 오류 표시 때 사용한다.
 */
void DispError(pszMsg, bCritical)
char *pszMsg;
int bCritical;
{
  printf(pszMsg);
  if(bCritical) {
    printf("\n비 정상적으로 프로그램 마침. 인공지능 연구실 권재락\n");
    exit(-1);
  }
}

/*
 *  입력   : 치명적 오류인지 아닌지, 출력 형식
 *  출력   : .
 *  호출함 : .
 *  호출됨 : .
 *  설  명 : 일반적인 오류 표시 때 사용한다.
 */
void DispErrorF(int bCritical, char *pszFormat,  ... )
/*
int bCritical;
char *pszFormat;
*/
{
  va_list arg;
  char szStr[MAX_STR_LEN];

  va_start(arg, pszFormat);
  vsprintf(szStr, pszFormat, arg);
  DispError(szStr, bCritical);
  va_end(arg);
}

/*
 *  입력   : 할당할 메모리 크기
 *  출력   : 성공여부 (success or fail)
 *  호출함 : .
 *  호출됨 : .
 *  설  명 : 메모리 부족시 프로그램 강제 중단 처리를 포함한 메모리 할당 함수.
 */
void *MemAlloc(wSize)
unsigned int wSize;
{
  void *pPtr;

  pPtr = (void *)malloc(wSize);
  if(!pPtr) {
    DispError("메모리 부족......", 1);
  }
  return pPtr;
}

/*
 *  입력   : wSize 갯수, 할당할 메모리 크기
 *  출력   : 성공여부 (success or fail)
 *  호출함 : .
 *  호출됨 : .
 *  설  명 : 메모리 부족시 프로그램 강제 중단 처리를 포함한 메모리 할당 함수.
 *           실제로 할당되는 메모리 = nEle * wSize Bytes
 */
void *ClearMemAlloc(nEle, wSize)
int nEle;
unsigned int wSize;
{
  void *pPtr;

  pPtr = calloc(nEle, wSize);
  if(!pPtr) {
    DispError("메모리 부족......", 1);
  }
  return pPtr;
}

/* ------------------------------------------------------------------------- */


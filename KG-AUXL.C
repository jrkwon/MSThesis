/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-auxl.c
 *  함수(들)  :
 *  파일 설명 :  보조용언속성에서 보조용언 형태소를 구한다.
 *  만든 날   :  1993. 10. 02
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
 *  한국어 보조용언 생성용 사전의 구조 Ver 1.00
 *
 *    +----- 보조용언 속성
 *    |            +------ 보조연결어미가 변환이 필요한지에 대한 플래그
 *    |            |
 *    |            |                           +-- 보조연결어미+보조용언
 *    |            |                           |
 *  ==+============+===========================+==========================
 *    보조용언     어미변화                    보조용언
 *  ======================================================================
 *    PRGRSS       0                           고_있다
 *    STATE        1                           아_있다
 *    DONOT        0                           지_않다
 *    FORBID       0                           지_말다
 *    .........
 *    <중간 생략>
 *  ----------------------------------------------------------------------
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "kg-auxl.h"
#include "kg-node.h"
#include "kg-file.h"
#include "kg-ftr.h"
#include "kg-type.h"

static char szWord[MAX_STR_LEN];

/*
 *  보조용언 생성용 표
 */
AUXL_TABLE AuxlTable[MAX_AUXL_CNT];

/*
 *  입력   :  파일이름
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  보조용언 표 파일을 읽는다.
 */
void ReadAuxlTable(pszFileName, bView)
char *pszFileName;
int bView;
{
  char szFeature[MAX_AUXL_LEN], szTrans[MAX_AUXL_LEN], szAuxl[MAX_AUXL_LEN];
  char *pszStr, *pTemp;
  int nCnt, nAns;

  if(bView) {
    printf("♥ 보조용언 표 (%s)를 읽습니다\n", pszFileName);
  }
  OpenDataFile(pszFileName);
  CheckFileHeader(szFileHeader[AUXL_HEADER]);
  for(nCnt = 0; nCnt < MAX_AUXL_CNT; nCnt++) {
    if(SkipSpace() == NULL)
      break;
    if(IsTableComment(pszCurPtr)) {
      ReadLine();
      nCnt--;
    }
    else {
      AuxlTable[nCnt].nFeature  = GetFeatureNumber(GetWord(szFeature));
      AuxlTable[nCnt].bTrans    = atoi(GetWord(szTrans));
      strcpy(AuxlTable[nCnt].szAuxl, (char *)GetWord(szAuxl));
      pTemp = strchr(AuxlTable[nCnt].szAuxl, '_');
      if(pTemp)
        *pTemp = ' ';
    }
  }
  CloseDataFile();
}

/*
 *  입력   :  보조용언 속성
 *  출력   :  찾으면 해당 번호, 못찾으면 -1
 *  호출함 :
 *  호출됨 :
 *  설  명 :  보조용언 표에서 찾아서 그 번호를 돌려준다.
 */
int FindAuxlPhrase(nFeature)
int nFeature;
{
  int nCnt;

  for(nCnt = 0; nCnt < MAX_AUXL_CNT; nCnt++) {
    if(nFeature == AuxlTable[nCnt].nFeature) {
       return nCnt;
    }
  }
  return -1;
}

/*
 *  입력   :  보조용언 속성, 결과를 담을 문자열
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  보조용언을 결정해서 결과 문자열에 붙여준다.
 */
void GetAuxlPhrase(nFeature, pszPhrase)
int  nFeature;
char *pszPhrase;
{
  int nCnt;

  nCnt = FindAuxlPhrase(nFeature);
  if(nCnt != -1) {
/*    if(AuxlTable[nCnt].bTrans)
      MergeHangulStr(pszPhrase, AuxlTable[nCnt].szAuxl);
    else */
      strcat(pszPhrase, AuxlTable[nCnt].szAuxl);
  }
}

/* ------------------------------------------------------------------------- */


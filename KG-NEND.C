/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-nend.c
 *  함수(들)  :
 *  파일 설명 :  한국어 비종결어미 사전관리와 비종결어미 생성
 *  만든 날   :  1993. 09. 28
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
 *  한국어 비종결어미 생성용 사전의 구조 Ver 1.00
 *
 *    +----- 비종결어미 종류, (전성어미와 접속어미를 모두 포함)
 *    |            +------------- 완결법(과거)
 *    |            |    +-------- 미정법(미래)
 *    |            |    +    +--- 회상법()
 *    |            |    |    |     +-------  어미형태의 다른 형태를
 *    |            |    |    |     |         처리하기 위한 플래그
 *    |            |    |    |     |           +-- 비종결어미 형태소
 *    |            |    |    |     |           |
 *  ==+============+====+====+=====+===========+==========================
 *    어미종류     었   겠   더    어미변경    비종결어미형태소
 *  ======================================================================
 *    SMPLAR       1    1    0     0           고
 *    ORDRAR       0    0    0     0           고서
 *    RSLTAR       0    0    0     1           어서
 *    SMLTAR       0    0    0     1           면서
 *    IMMDET       0    0    0     0           자마자
 *    <중간 생략>
 *  ------------------------------------------------------------------------
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "kg-nend.h"
#include "kg-node.h"
#include "kg-file.h"
#include "kg-ftr.h"
#include "kg-type.h"

static char szWord[MAX_STR_LEN];

/*
 *  비종결어미 생성용 표
 */
NEOW_TABLE NEndOfWord[MAX_NEOW_CNT];

/*
 *  입력   :  파일이름
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  비종결어미 표 파일을 읽어둔다
 */
void ReadNEndOfWordTable(pszFileName, bView)
char *pszFileName;
int bView;
{
  char szFeature[MAX_NFIELD_LEN], szEOT[MAX_NFIELD_LEN], szGET[MAX_NFIELD_LEN];
  char szDEO[MAX_NFIELD_LEN], szTrans[MAX_NFIELD_LEN], szNEndOfWord[MAX_NFIELD_LEN];
  char *pszStr;
  int nCnt, nAns;

  if(bView) {
    printf("♥ 비종결어미 표 (%s)를 읽습니다\n", pszFileName);
  }
  OpenDataFile(pszFileName);
  CheckFileHeader(szFileHeader[NEOW_HEADER]);
  for(nCnt = 0; nCnt < MAX_NEOW_CNT; nCnt++) {
    if(SkipSpace() == NULL)
      break;
    if(IsTableComment(pszCurPtr)) {
      ReadLine();
      nCnt--;
    }
    else {
      NEndOfWord[nCnt].nFeature  = GetFeatureNumber(GetWord(szFeature));
      NEndOfWord[nCnt].nEOT      = atoi(GetWord(szEOT));
      NEndOfWord[nCnt].nGET      = atoi(GetWord(szGET));
      NEndOfWord[nCnt].nDEO      = atoi(GetWord(szDEO));
      NEndOfWord[nCnt].bTrans    = atoi(GetWord(szTrans));
      strcpy(NEndOfWord[nCnt].szNEndOfWord, (char *)GetWord(szNEndOfWord));
    }
  }
  CloseDataFile();
}

/*
 *  입력   :  비종결어미속성
 *  출력   :  찾으면 해당 번호, 못찾으면 -1
 *  호출함 :
 *  호출됨 :
 *  설  명 :  비종결어미를 표에서 찾아서 그 번호를 돌려준다.
 */
int FindNEowPhrase(nFeature)
int nFeature;
{
  int nCnt;

  for(nCnt = 0; nCnt < MAX_NEOW_CNT; nCnt++) {
    if(nFeature == NEndOfWord[nCnt].nFeature) {
      return nCnt;
    }
  }
  return -1;
}

/*
 *  입력   :  통사정보 마디포인터, 결과를 붙일 문자열 포인터, 시제
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  비종결어미를 구한다.
 */
void GetNEowPhrase(nFeature, pszPhrase, nTense)
int  nFeature;
char *pszPhrase;
int  nTense;
{
  int nCnt;

  nCnt = FindNEowPhrase(nFeature);
  if(nCnt != -1) {
/*    if(NEndOfWord[nCnt].bTrans) */
    if(nTense == PAST || nTense == PPAST ||
       nTense == PASTREC || nTense == PASTFUT || nTense == PASTFUTR) {
      if(NEndOfWord[nCnt].nEOT) {
        MergeHangulStr(pszPhrase, (char *)GetTenseMorph(Feature2Str(nTense)));
/*        strcat(pszPhrase, (char *)GetTenseMorph(Feature2Str(nTense)));*/
      }
    }
    else if(nTense == FUTURE || nTense == FUTUREC) {
      if(NEndOfWord[nCnt].nGET) {
        MergeHangulStr(pszPhrase, (char *)GetTenseMorph(Feature2Str(nTense)));
/*        strcat(pszPhrase, (char *)GetTenseMorph(Feature2Str(nTense)));*/
      }
    }
    else if(nTense == RECOLL) {
      if(NEndOfWord[nCnt].nDEO) {
        MergeHangulStr(pszPhrase, (char *)GetTenseMorph(Feature2Str(nTense)));
/*        strcat(pszPhrase, (char *)GetTenseMorph(Feature2Str(nTense)));*/
      }
    }
    MergeHangulStr(pszPhrase, NEndOfWord[nCnt].szNEndOfWord);
/*    strcat(pszPhrase, NEndOfWord[nCnt].szNEndOfWord);*/
  }
}

/* ------------------------------------------------------------------------- */

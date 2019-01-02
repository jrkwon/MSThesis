/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-eend.c
 *  함수(들)  :
 *  파일 설명 :  한국어 종결어미 사전관리와 종결어미 생성
 *  만든 날   :  1993. 09. 23
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
 *  한국어 종결어미 생성용 사전의 구조 Ver 1.00
 *
 *    +----- 형용사 속성, 지정사 속성, 동사 속성으로 구분
 *    |      품사가 아니라, 통사 속성 중에 형용사 속성, 지정사 속성
 *    |      주어서 이를 표시...
 *    |         +-------- 현재, 현재가 아닌 것
 *    |         |      +------ 평서, 의문, 감탄, 명령, 허락, 약속, 청유
 *    |         |      |    +----- 아주 낮춤, 두루 낮춤, 예사 낮춤
 *    |         |      |    |      예사 높임, 두루 높임, 아주 높임
 *    |         |      |    |           +-----  어미형태의 다른 형태를
 *    |         |      |    |           |       처리하기 위한 플래그
 *    |         |      |    |           |       (-ㄴ다, -는다 처리)
 *    |         |      |    |           |           +- 다른 형태가 존재할 수
 *    |         |      |    |           |           |  있지만 한가지만 등록한다.
 *    |         |      |    |           |           |  처리방법은 따로 논한다.
 *  ==+=========+======+====+===========+===========+========================
 *    품사속성  시제   법   상대높임    어미변경    비종결어미형태소
 *  =========================================================================
 *    OTHERS   PRESNT  DECLM LOWER1      1           는다
 *    OTHERS   PRESNT  DECLM LOWER2      0           아
 *    OTHERS   PRESNT  DECLM LOWER3      0           네
 *  <중간 생략>
 *  ADJNAT     PRESNT  DECLM LOWER1      0           다
 *  <중간 생략>
 *  COPULA     PRESNT  DECLM LOWER1      0           다
 *  <중간 생략>
 *  ------------------------------------------------------------------------
 *
 *  ※ OTHERS  : (ADJNAT -) && (COPULA -) or ~(PRESNT)
 *     ADJNAT  : (ADJNAT +)
 *     COPULA  : (COPULA +)
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "kg-eend.h"
#include "kg-node.h"
#include "kg-file.h"
#include "kg-ftr.h"
#include "kg-type.h"

static char szWord[MAX_STR_LEN];

/*
 *  종결어미 생성용 표
 */
EEOW_TABLE EEndOfWord[MAX_EEOW_CNT];

/*
 *  입력   :  파일이름
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  종결어미 표 파일을 읽어둔다
 */
void ReadEEndOfWordTable(pszFileName, bView)
char *pszFileName;
int bView;
{
  char szCat[MAX_EFIELD_LEN], szTense[MAX_EFIELD_LEN], szMood[MAX_EFIELD_LEN];
  char szHonor[MAX_EFIELD_LEN], szTrans[MAX_EFIELD_LEN], szEEndOfWord[MAX_EFIELD_LEN];
  char *pszStr;
  int nCnt, nAns;

  if(bView) {
    printf("♥ 종결어미 표 (%s)를 읽습니다\n", pszFileName);
  }
  OpenDataFile(pszFileName);
  CheckFileHeader(szFileHeader[EEOW_HEADER]);
  for(nCnt = 0; nCnt < MAX_EEOW_CNT; nCnt++) {
    if(SkipSpace() == NULL)
      break;
    if(IsTableComment(pszCurPtr)) {
      ReadLine();
      nCnt--;
    }
    else {
      EEndOfWord[nCnt].nCat   = GetFeatureNumber(GetWord(szCat));
      EEndOfWord[nCnt].nTense = GetFeatureNumber(GetWord(szTense));
      EEndOfWord[nCnt].nMood  = GetFeatureNumber(GetWord(szMood));
      EEndOfWord[nCnt].nHonor = GetFeatureNumber(GetWord(szHonor));
      EEndOfWord[nCnt].bTrans = atoi(GetWord(szTrans));
      strcpy(EEndOfWord[nCnt].szEEndOfWord, (char *)GetWord(szEEndOfWord));
    }
  }
  CloseDataFile();
}

/*
 *  입력   :  품사속성, 시제, 법, 상대존칭
 *  출력   :  찾으면 해당 번호, 못찾으면 -1
 *  호출함 :
 *  호출됨 :
 *  설  명 :  종결어미를 표에서 찾아서 그 번호를 돌려준다.
 */
int FindEEowPhrase(nCat, nTense, nMood, nHonor)
int nCat;
int nTense;
int nMood;
int nHonor;
{
  int nCnt;

  for(nCnt = 0; nCnt < MAX_EEOW_CNT; nCnt++) {
    if(nCat == EEndOfWord[nCnt].nCat) {
      if(nTense == EEndOfWord[nCnt].nTense) {
        if(nMood == EEndOfWord[nCnt].nMood) {
          if(nHonor == EEndOfWord[nCnt].nHonor) {
            return nCnt;
          }
        }
      }
    }
  }
  return -1;
}

/*
 *  입력   :  통사정보 마디포인터, 구절문자열, 법
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  종결어미를 구한다.
 */
void GetEEowPhrase(pSyn, pszPhrase, nMood)
NODE *pSyn;
char *pszPhrase;
int  nMood;
{
  int nArcNum, nCnt, nCat, nTense, nHonor;

  /*
   * 품사 속성 구하기 (ADJNAT, COPULA, OTHERS)
   */
  nCat = OTHERS;  /* 내정값 */
  nArcNum = GetArcNumber(pSyn, ADJNAT);
  if(nArcNum != -1) {
    if(pSyn->Arc[nArcNum].Value.pszStr[0][0] == '+') {
      nCat = ADJNAT;
    }
  }
  nArcNum = GetArcNumber(pSyn, COPULA);
  if(nArcNum != -1) {
    if(pSyn->Arc[nArcNum].Value.pszStr[0][0] == '+') {
      nCat = COPULA;
    }
  }
  /*
   *  시제 구하기 (TENSE, OTHERS)
   */
  nTense = PRESNT; /* 내정값 */
  nArcNum = GetArcNumber(pSyn, TENSE);
  if(nArcNum != -1) {
    nTense = GetFeatureNumber(pSyn->Arc[nArcNum].Value.pszStr[0]);
    if(nTense != PRESNT)
      nTense = OTHERS;
  }
  /*
   *  상대 높힘 구하기 (LOWER1, LOWER2, LOWER3, HIGHR1, HIGHR2, HIGHR3)
   */
  nHonor = LOWER1; /* 내정값 */
  nArcNum = GetArcNumber(pSyn, OHONOR);
  if(nArcNum != -1) {
    nHonor = GetFeatureNumber(pSyn->Arc[nArcNum].Value.pszStr[0]);
  }

  /*
   *  구한 속성에 따른 종결어미를 구한다.
   */
  nCnt = FindEEowPhrase(nCat, nTense, nMood, nHonor);
  if(nCnt != -1) {
    if(EEndOfWord[nCnt].bTrans)
      MergeHangulStr(pszPhrase, EEndOfWord[nCnt].szEEndOfWord);
    else
      strcat(pszPhrase, EEndOfWord[nCnt].szEEndOfWord);
  }
}


/* ------------------------------------------------------------------------- */

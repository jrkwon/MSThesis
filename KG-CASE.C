/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-case.c
 *  함수(들)  :
 *  파일 설명 :  조사속성으로부터 실제 조사문자열을 구한다.
 *  만든 날   :  1993. 10. 01
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
 *  한국어 조사 생성용 사전의 구조 Ver 1.00
 *
 *    +----- 조사 속성
 *    |            +------ 받침무관, 받침있음, 받침없음
 *    |            |       (FINALZ)  (FINALO)  (FINALX)
 *    |            |            +--- 결합하면서 음운변화가 필요한지에 대한 플래그
 *    |            |            |              +-- 조사 형태소
 *    |            |            |              |
 *  ==+============+============+==============+==========================
 *    조사종류     받침         조사변화       조사 형태소
 *  ======================================================================
 *    SUBJ         FINALX       0              가
 *    SUBJ         FINAL0       0              이
 *    OBJ          FINALX       0              를
 *    OBJ          FINAL0       0              을
 *    .........
 *    <중간 생략>
 *  ----------------------------------------------------------------------
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "kg-case.h"
#include "kg-node.h"
#include "kg-file.h"
#include "kg-ftr.h"
#include "kg-type.h"

static int GetFinalNumber(char *pszFinal);

/* 조사 생성시 받침 유무를 따지는 경우에 필요 */
/*     받침무관, 받침있음, 받침없음           */
enum { FINALZ,   FINALO,   FINALX };
static char *szFinal[] = { "FINALZ", "FINALO", "FINALX", "" };

static char szWord[MAX_STR_LEN];

/*
 *  조사 생성용 표
 */
CASE_TABLE CaseTable[MAX_CASE_CNT];

/*
 *  입력   :  받침종류 문자열
 *  출력   :  받침종류 번호, 실패하면 -1
 *  호출함 :
 *  호출됨 :
 *  설  명 :  받침종류 문자열에서 받침종류 번호를 구한다.
 */
static int GetFinalNumber(pszFinal)
char *pszFinal;
{
  int nCnt;

  for(nCnt = 0; szFinal[nCnt][0]; nCnt++)
    if(!strcmp(szFinal[nCnt], pszFinal))
      return nCnt;
  return -1;
}

/*
 *  입력   :  파일이름
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  조사 표 파일을 읽는다.
 */
void ReadCaseTable(pszFileName, bView)
char *pszFileName;
int bView;
{
  char szFeature[MAX_CASE_LEN], szFinal[MAX_CASE_LEN];
  char szTrans[MAX_CASE_LEN], szCase[MAX_CASE_LEN];
  char *pszStr;
  int nCnt, nAns;

  if(bView) {
    printf("♥ 조사 표 (%s)를 읽습니다\n", pszFileName);
  }
  OpenDataFile(pszFileName);
  CheckFileHeader(szFileHeader[CASE_HEADER]);
  for(nCnt = 0; nCnt < MAX_CASE_CNT; nCnt++) {
    if(SkipSpace() == NULL)
      break;
    if(IsTableComment(pszCurPtr)) {
      ReadLine();
      nCnt--;
    }
    else {
      CaseTable[nCnt].nFeature  = GetFeatureNumber(GetWord(szFeature));
      CaseTable[nCnt].nFinal    = GetFinalNumber(GetWord(szFinal));
      CaseTable[nCnt].bTrans    = atoi(GetWord(szFinal));
      strcpy(CaseTable[nCnt].szCase, (char *)GetWord(szCase));
    }
  }
  CloseDataFile();
}

/*
 *  입력   :  조사 속성
 *  출력   :  찾으면 해당 번호, 못찾으면 -1
 *  호출함 :
 *  호출됨 :
 *  설  명 :  조사 표에서 찾아서 그 번호를 돌려준다.
 */
int FindCasePhrase(nFeature, bFinal)
int nFeature;
int bFinal;
{
  int nCnt;

  for(nCnt = 0; nCnt < MAX_CASE_CNT; nCnt++) {
    if(nFeature == CaseTable[nCnt].nFeature) {
      if(CaseTable[nCnt].nFinal == FINALZ)
        return nCnt;
      if(CaseTable[nCnt].nFinal == FINALO && bFinal)
        return nCnt;
      if(CaseTable[nCnt].nFinal == FINALX && !bFinal)
        return nCnt;
    }
  }
  return -1;
}

/*
 *  입력   :  조사 속성, 결과를 담을 문자열, 종성여부
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  조사를 결정해서 결과 문자열에 붙여준다.
 */
void GetCasePhrase(nFeature, pszPhrase, bFinal)
int  nFeature;
char *pszPhrase;
int  bFinal;
{
  int nCnt;

  nCnt = FindCasePhrase(nFeature, bFinal);
  if(nCnt != -1) {
    if(CaseTable[nCnt].bTrans)
      AttachHangulStr(pszPhrase, CaseTable[nCnt].szCase);
    else
      strcat(pszPhrase, CaseTable[nCnt].szCase);
  }
}

/* ------------------------------------------------------------------------- */

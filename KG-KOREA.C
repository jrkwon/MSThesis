#define DEBUG

/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-korea.c
 *  함수(들)  :
 *  파일 설명 :  한국어 구문, 형태소 생성
 *  만든 날   :  1993. 09. 16
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
#include <string.h>
#include <malloc.h>
#ifdef __TURBOC__
#include <mem.h>
#else
#include <memory.h>
#endif
#include "kg-ftr.h"
#include "kg-node.h"
#include "kg-korea.h"
#include "kg-code.h"
#include "kg-util.h"
#include "kg-type.h"

#define END_FLAG	  3250				/* Word order ending flag	   */

static int GetSentenceOrder(int nFeature);
/* static int SortFunc(ARC *pArcA, ARC *pArcB); */
static NODE *GetNextNode4PathStack(NODE *pNode, int nFeature);
static int GetMoodFeatureNumber(char *pszFeatureValue);
static int IsAuxlFeature(int nFeature);
static char *GetLastKoreanChar(char *pszHangul);
static int IsFinal(char *pszHangulChar);

/*
 *  해석 결과 속성 구조에서, 통사 정보와 의미 정보를 이용해,
 *  한국어 형태소를 생성하는 알고리즘 1.00 판
 *
 *  1. 의미정보를 한국어 어순에 맞도록 정렬한다.
 *  2. SEM 마디에서 각 의미정보까지의 경로를 경로 스택에 저장한다.
 *
 *     (예) SEM    (SUBJ     (PREN    (PRED   그리다)
 *                                    (SUBJ   (REF    철수))
 *                           )
 *                  .............
 *          철수   : SUBJ - PREN - SUBJ - REF - NULL
 *          그리다 : SUBJ - PREN - PRED - NULL
 *          .........
 *  3. 이 경로 스택을 이용하여, 각 의미정보에 해당하는 통사정보를 탐색한다.
 *     이 때 각 의미정보의 품사에 따라 처리방법이 다르다.
 *     (가) 체언
 *          통사 : 가산성 + 복수 + (~단위성의존명사)  = '-들'
 *          의미 : 격속성에 대응하는 격조사 생성
 *     (나) 용언
 *          통사 : 보조용언, 부사성 의존명사, 어미 정보 생성
 *          의미 : ..
 *     ....
 *
 */

/*
 *  통사 정보 탐색 경로를 저장
 */
int nPathStack[MAX_PATH_STACK_CNT][MAX_PATH_STACK_DEPTH];
int nPathStackCnt;
int nPathStackDepth;

/*
 *  각 어절의 기본 형태소를 저장할 문자열 포인터 배열
 */
char *pszPhrase[MAX_PATH_STACK_CNT];            /* String of End Of Word */

/*
 *  입력   :  .
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  경로 스택에 관련된 변수들을 초기화
 */
void InitPathStack()
{
  nPathStackCnt = nPathStackDepth = 0;
  memset(nPathStack, NULL, sizeof(nPathStack));
}

/*
 *  입력   :  속성
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  정해진 어순 중에서 nFeature가 어디 쯤인지 ....
 */
static int GetSentenceOrder(int nFeature)
{
  /* 어순 정의 파일에서 읽어 와야지...
   */
  static int nSentenceOrder[] = {
    VOC, SUBJ, SUBJ2, FROM, TO, TOPIC, INDEP, NONSEL, NONSPC,
    SELECT, SPCL, OFCAUSE, NOMORE, INDICT, EXPAND, DISSAT,
    EMPH, EACH, SURE, UNIFORM, TOO, FOLLOW, TOGETHR,
    SPLOC, TMLOC, SRC, GOAL, STLOC, TOOL, CHANGE, CMPSMP, CMPEQL, CMPSAM, CMPTHN,
    QUADIR, QUAIND, CAUSE,
    OBJ, OBJ2, SPLOC, QUAL, ADVEW, PREN, PRENEW, REF, PRED, 0
  };
  int i;

  for(i = 0; nSentenceOrder[i]; i++)
    if(nFeature == nSentenceOrder[i])
      return i;
  return END_FLAG;
}

/*
 *  입력   :  비교할 가지 포인터, 비교할 가지 포인터
 *  출력   :  .
 *  호출함 :  GetFeatureNumber
 *  호출됨 :
 *  설  명 :  가지의 속성값을 비교한다.
 */
static int SortFunc(pArcA, pArcB)
ARC *pArcA;
ARC *pArcB;
{
  return GetSentenceOrder(pArcA->nFeature) - GetSentenceOrder(pArcB->nFeature);
}

/*
 *  입력   :  의미 정보를 가지는 마디 포인터 (Sem)
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  Sem마디를 한국어 어순에 맞도록 정렬한다.
 */
void SortSemNode(pNode)
NODE *pNode;
{
  int nEle, nCnt;

  nEle = 0;
  while(pNode->Arc[nEle].nFeature)
    nEle++;

  qsort(pNode->Arc, nEle, sizeof(ARC), SortFunc);

  for(nCnt = 0; pNode->Arc[nCnt].nFeature; nCnt++) {
    if(pNode->Arc[nCnt].pNode != NULL) {
      SortSemNode(pNode->Arc[nCnt].pNode);
    }
  }
}

/*
 *  입력   :  마디 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  생성을 위한 정보를 찾기 위한 경로 스택을 구한다.
 */
void GetPathStackAndPhrase(pArc, ppszPhrase)
ARC *pArc;
char **ppszPhrase;
{
  int nCnt, nDepth;

  for(nCnt = 0; pArc[nCnt].nFeature; nCnt++) {
    if(nPathStackDepth < MAX_PATH_STACK_DEPTH)
      nPathStack[nPathStackCnt][nPathStackDepth++] = pArc[nCnt].nFeature;
    else
      DispError("경로 스택의 최대 깊이를 초과하셨습니다\n", true);
    if((pArc[nCnt].Value.pszStr[0] == NULL)
        && (pArc[nCnt].Value.pszPtr[0] == NULL)) {
      GetPathStackAndPhrase(pArc[nCnt].pNode->Arc, ppszPhrase);
      nPathStackDepth -= 2;
      for(nDepth = 0; nDepth < nPathStackDepth; nDepth++)
        nPathStack[nPathStackCnt][nDepth] = nPathStack[nPathStackCnt-1][nDepth];
    }
    else {
      nPathStack[nPathStackCnt][nPathStackDepth] = NULL;
      ppszPhrase[nPathStackCnt] = (char *)MemAlloc(strlen(*(pArc[nCnt].Value.pszStr))+1);
      strcpy(ppszPhrase[nPathStackCnt], *(pArc[nCnt].Value.pszStr));
      if(nPathStackCnt < MAX_PATH_STACK_CNT)
        nPathStackCnt++;
      else
        DispError("경로 스택의 최대 갯수를 초과하셨습니다\n", true);
      return;
    }
  }
}

/*
 *  입력   :  마디 포인터, 속성 리스트를 저장한 정수 배열의 포인터
 *  출력   :  속성 리스트를 따라 찾아간 마디 포인터
 *  호출함 :
 *  호출됨 :
 *  설  명 :  pnList에 따라 마디 구조를 따라 내려가서 그 마디 포인터를 돌려준다
 */
NODE *GetNodePtr4List(pNode, pnList)
NODE *pNode;
int *pnList;
{
  int nCnt, nArcNum;

  for(nCnt = 0; nCnt < MAX_PATH_STACK_DEPTH && pnList[nCnt]; nCnt++) {
    nArcNum = GetArcNumber(pNode, pnList[nCnt]);
    if(nArcNum == -1)
      DispError("마디 구조가 잘못 되었습니다\n", true);
    else
      pNode = pNode->Arc[nArcNum].pNode;
  }
  if(nCnt == MAX_PATH_STACK_DEPTH)
    DispError("경로 스택의 최대 깊이를 초과 하셨습니다\n", true);
  return pNode;
}

/*
 *  입력   :  마디포인터, 다음 마디포인터를 찾기 위한 속성
 *  출력   :  경로스택을 따라 찾아간 다음 마디포인터
 *  호출함 :
 *  호출됨 :
 *  설  명 :  경로스택에 따라 해당성분의 통사정보를 찾는다.
 *            SUBCAT의 가지 중에서 nFeature와 일치하는 속성이 있다면
 *            그쪽 가지로, 아니면 HEADD가지 쪽으로 간다.
 */
static NODE *GetNextNode4PathStack(pNode, nFeature)
NODE *pNode;
int  nFeature;
{
  int nArc;
  NODE *pTempNode;

  nArc = GetArcNumber(pNode, SUBCAT);
  if(nArc == -1)
    DispError("SUBCAT가지가 없습니다. 노드 구조가 잘못되었습니다. [kg-korea::GetNextNode4PathStack]", true);
  pTempNode = pNode->Arc[nArc].pNode;
  nArc = GetArcNumber(pTempNode, nFeature);
  if(nArc == -1) {
    nArc = GetArcNumber(pTempNode, HEADD);
    if(nArc == -1)
      DispError("HEADD가지가 없습니다. 노드 구조가 잘못되었습니다. [kg-korea::GetNextNode4PathStack]", true);
  }
  return pTempNode->Arc[nArc].pNode;
}

/* 사전으로 ---> */
struct Tense2Morph {
  char *pszTense;      /* 시제 속성값 */
  char *pszMorph;      /* 시제에 해당하는 선어말 어미 형태소 */
} Tense2Morph[] = {
  { "PRESNT",   ""       }, { "RECOLL",   "더"     },
  { "FUTURE",   "겠",    }, { "PAST",     "었"     },
  { "PPAST",    "었었",  }, { "FUTUREC",  "겠더"   },
  { "PASTREC",  "었더",  }, { "PASTFUT",  "었겠"   },
  { "PASTREC",  "었더",  }, { "PASTFUT",  "었겠"   },
};

/*
 *  입력   :  시제에 해당하는 속성값
 *  출력   :  시제에 대응하는 선어말 어미
 *  호출함 :
 *  호출됨 :
 *  설  명 :  시제 속성값에 대응하는 시제선어말어미를 구한다
 */
char *GetTenseMorph(pszStr)
char *pszStr;
{
  int nCnt;

  for(nCnt = 0; Tense2Morph[nCnt].pszTense[0]; nCnt++) {
    if(!strcmp(Tense2Morph[nCnt].pszTense, pszStr)) {
      return Tense2Morph[nCnt].pszMorph;
    }
  }
  return "";
}

/*
 *  입력   :  마디 포인터, 생성중인 문자열의 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  접두어 처리
 */
void GetPrefixPhrase(pSyn, pszPhrase)
NODE *pSyn;
char *pszPhrase;
{
  int nArcNum;

  nArcNum = GetArcNumber(pSyn, PASSIV);
  if(nArcNum != -1 && !strcmp(*(pSyn->Arc[nArcNum].Value.pszStr), "+")) {
    /* 음운 축약과 불규칙을 고려해 주어야 한다 */
    /* 사전을 검색해서, 어떤 접미사를 붙혀야 하는지... */
    strcat(pszPhrase, "히");
  }
}

/*
 *  입력   :  통사정보 마디 포인터, 생성중인 문자열 포인터
 *  출력   :  시제 선어말 어미가 붙었으면 그 속성값, 아니면 0
 *  호출함 :
 *  호출됨 :
 *  설  명 :  선어말 어미 정보를 이용해서, 형태소 생성
 *            시제 선어말 어미가 붙었는지에 대한 정보는 어말어미 중에서
 *            비종결어미를 생성할 때 필요한 경우가 있기 때문이다.
 */
int GetPreEowPhrase(pSyn, pszPhrase)
NODE *pSyn;
char *pszPhrase;
{
  int nArcNum, nTense;
  char *pszStr;

  /* 주체 존대 : '-시-' */
  nArcNum = GetArcNumber(pSyn, SHONOR);
  if(nArcNum != -1 && !strcmp(*(pSyn->Arc[nArcNum].Value.pszStr), "+")) {
    /* 음운 축약과 불규칙을 고려해 주어야 한다 */
    strcat(pszPhrase, "시");
  }
  /* 시제 */
  nTense = 0;
  nArcNum = GetArcNumber(pSyn, TENSE);
  if(nArcNum != -1) {
    /* 음운 축약과 불규칙을 고려해 주어야 한다 */
    pszStr = GetTenseMorph(*(pSyn->Arc[nArcNum].Value.pszStr));
    MergeHangulStr(pszPhrase, pszStr);
/*    strcat(pszPhrase, pszStr);*/
    nTense = GetFeatureNumber(pszStr);
  }
  return nTense;
}

/*
 *  입력   :  어미 형태 속성값
 *  출력   :  법(mood)에 대한 속성이면 그 법의 속성값, 아니면 NULL
 *  호출함 :
 *  호출됨 :
 *  설  명 :  어말 어미를 생성한다. (종결형, 비종결형)
 */
static int GetMoodFeatureNumber(pszFeatureValue)
char *pszFeatureValue;
{
  int nMoodFeature[] = { DECLM, IRROM, EXCLM, IMPRM, ALLWM, PRMSM, SGSTM, NULL };
  int nCnt;

  for(nCnt = 0; nMoodFeature[nCnt]; nCnt++)
    if(GetFeatureNumber(pszFeatureValue) == nMoodFeature[nCnt])
      return nMoodFeature[nCnt];
  return NULL;
}

/*
 *  입력   :  속성
 *  출력   :  nFeature가 보조용언 속성이면 참, 아니면 거짓
 *  호출함 :
 *  호출됨 :
 *  설  명 :  보조용언 속성인지 아닌지 판별한다
 */
static int IsAuxlFeature(nFeature)
int nFeature;
{
  int nAuxlFeature[] =
    { PRGRSS, STATE, DONOT, FORBID, CANNOT, BECOME, SERVCE, TRIAL,
      STRESS, PSSESS, CAUSAT, DESIRE, SHOULD, APPROV, NULL };
  int nCnt;

  for(nCnt = 0; nAuxlFeature[nCnt]; nCnt++)
    if(nFeature == nAuxlFeature[nCnt])
      return true;
  return false;
}

/*
 *  입력   :  통사정보 마디 포인터, 어절 문자열 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  통사 정보를 이용해서 한국어 보조용언을 생성한다.
 */
void GenerateAuxlPhrase(pSyn, pszPhrase)
NODE *pSyn;
char *pszPhrase;
{
  int nCnt;

  for(nCnt = 0; pSyn->Arc[nCnt].nFeature && nCnt < MAX_ARC_CNT; nCnt++) {
    if(IsAuxlFeature(pSyn->Arc[nCnt].nFeature))
      GetAuxlPhrase(pSyn->Arc[nCnt].nFeature, pszPhrase);
  }
}

/*
 *  입력   :  통사정보 마디 포인터, 어절 문자열 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  통사 정보를 이용해서 한국어 술어구를 생성한다.
 */
void GeneratePredPhrase(pSyn, pszPhrase)
NODE *pSyn;
char *pszPhrase;
{
  int nLen, nTense, nArc, nMood, nFeature;

  GetPrefixPhrase(pSyn, pszPhrase);                 /* 수동, 피동 정보  */
  GenerateAuxlPhrase(pSyn, pszPhrase);              /* 보조용언         */
  nArc = GetArcNumber(pSyn, EWFORM);
  if(nArc == -1)
    DispError("노드 구조가 잘못 되었습니다 [kg-korea :: GetEowPhrase", true);
  nMood = GetMoodFeatureNumber(pSyn->Arc[nArc].Value.pszStr[0]);
  if(nMood) { /* 종결어미 */
    GetPreEowPhrase(pSyn, pszPhrase);        /* 선어말 어미 정보 */
    GetEEowPhrase(pSyn, pszPhrase, nMood);
  }
  else {
    nFeature = GetFeatureNumber(pSyn->Arc[nArc].Value.pszStr[0]);
    if(nFeature == VMODI) {
      strcpy(pszPhrase, pSyn->Arc[nArc].Value.pszStr[0]);
      MergeHangulStr(pszPhrase, "이");
      return;
    }
    else if(nFeature == NMODI) {
      /* 추가 .... */
    }
    /* !!! 비종결형이면 어말어미와 시제를 보고 선어말어미를 결정한 후 비종결어미 결정 */
    nArc = GetArcNumber(pSyn, TENSE);
    if(nArc != -1) {
      nTense = GetFeatureNumber(*(pSyn->Arc[nArc].Value.pszStr));
      GetNEowPhrase(nFeature, pszPhrase, nTense);         /* 어말 어미 정보   */
    }
  }
}

/*
 *  입력   :  문자열 포인터
 *  출력   :  마지막 한글문자 - (실제로는 문자열 포인터), 없으면 -1;
 *  호출함 :
 *  호출됨 :
 *  설  명 :  한글 문자열 중에서 가장 마지막 글자(문자열)를 구한다.
 */
static char *GetLastKoreanChar(pszHangul)
char *pszHangul;
{
  int nLen;

  nLen = strlen(pszHangul);
  if(nLen >= 2) {
    return pszHangul + nLen-2;
  }
  return NULL;
}

/*
 *  입력   :  한글 한글자(문자열 포인터)
 *  출력   :  받침이 있으면 참, 없으면 거짓
 *  호출함 :
 *  호출됨 :
 *  설  명 :  받침이 있는 글자인지 알아낸다
 */
static int IsFinal(pszHangulChar)
char *pszHangulChar;
{
  unsigned int nKScode, nTGcode, n3rd;

  nKScode = (pszHangulChar[0] << 8);
  nKScode |= (pszHangulChar[1]) & 0x00ff;

  /*
   *  코드변환 :     KS완성형 --> 상용조합형
   */
  nTGcode = KS2TG(nKScode);

  n3rd = (nTGcode & 0x1F);         /* 종성 분리 */
  return (n3rd == FILL_LST) ? false : true;
}

/*
 *  입력   :  통사정보 마디 포인터, 어절 문자열 포인터, 조사 속성
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  통사 정보를 이용해서 한국어 명사상당어구를 생성한다.
 */
void GenerateRefPhrase(pSyn, pszPhrase, nCase)
NODE *pSyn;
char *pszPhrase;
int  nCase;
{
  int nArc, bFinal;
  char *pszTemp;

  nArc = GetArcNumber(pSyn, PLURAL);
  if(nArc != -1) {
    /* 좀 더 엄격한 제약조건을 기술해 주어야 하지 않을까? */
    if(pSyn->Arc[nArc].Value.pszStr[0][0], '+')
      strcat(pszPhrase, "들");
  }
  pszTemp = GetLastKoreanChar(pszPhrase);
  bFinal = IsFinal(pszTemp);
  GetCasePhrase(nCase, pszPhrase, bFinal);
}

/*
 *  입력   :  경로 스택, 해석 결과 마디 포인터, 결과를 담을 문자열 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  한 어절의 형태소를 생성한다.
 */
void GenerateKoreanPhrase(pnPathStack, pRootNode, pszPhrase, pszResultStr)
int *pnPathStack;                 /* 경로 스택                        */
NODE *pRootNode;                  /* 해석 결과의 뿌리 마디            */
char *pszPhrase;                  /* 이 어절의 기본 형태소            */
char *pszResultStr;               /* 생성 결과                        */
{
  NODE Syn, *pTempNode;
  int nCnt, nArcNum, nCase;
  static int nSynPath[] = { HEAD, SYN, 0 };

  ClearNode(&Syn);

  pTempNode = pRootNode;
  for(nCnt = 0; pnPathStack[nCnt] && nCnt < MAX_PATH_STACK_CNT; nCnt++) {
    if(pnPathStack[nCnt] == PRED) {
      NodeCopy(&Syn, GetNodePtr4List(pTempNode, nSynPath));
      GeneratePredPhrase(&Syn, pszPhrase);
      strcat(pszResultStr, pszPhrase);
      break;
    }
    else if(pnPathStack[nCnt] == REF) {
      NodeCopy(&Syn, GetNodePtr4List(pTempNode, nSynPath));
      nCase = (nCnt > 0) ? pnPathStack[nCnt-1] : 0;
      if(nCase) {
        GenerateRefPhrase(&Syn, pszPhrase, nCase);
        strcat(pszResultStr, pszPhrase);
      }
      break;
    }
    pTempNode = GetNextNode4PathStack(pTempNode, pnPathStack[nCnt]);
  }
  strcat(pszResultStr, " ");
}

/*
 *  입력   :  의미 정보를 가지는 마디 포인터, 결과를 담을 문자열 포인터
 *  출력   :  .
 *  호출함 :
 *  호출됨 :
 *  설  명 :  실제로 한국어 구문 및 형태소 생성기의 주 함수.
 */
void GenerateKoreanSentence(pSemNode, pRootNode, pszResultStr)
NODE *pSemNode;
NODE *pRootNode;
char *pszResultStr;
{
  int nCnt, nDepth;

  InitPathStack();
  /* 통사 정보 탐색 경로와 각 어절의 기본 형태소를 구한다 */
  GetPathStackAndPhrase(pSemNode->Arc, pszPhrase);
  /* 경로 스택의 최대 갯수 또는 스택의 첫번째 내용이 0이 것까지 */
  for(nCnt = 0; nCnt < MAX_PATH_STACK_CNT  && nPathStack[nCnt][0]; nCnt++) {
    GenerateKoreanPhrase(nPathStack[nCnt], pRootNode, pszPhrase[nCnt], pszResultStr);
  }
}

/* ------------------------------------------------------------------------- */

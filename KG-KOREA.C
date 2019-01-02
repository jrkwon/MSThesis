#define DEBUG

/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-korea.c
 *  �Լ�(��)  :
 *  ���� ���� :  �ѱ��� ����, ���¼� ����
 *  ���� ��   :  1993. 09. 16
 *  ���� ��   :  �� �� ��
 *
 *  ���۱� (C) 1993 �Ѿ���б� ������Ű��а� ���п� �ΰ����ɿ�����
 *  �� ���α׷��� ���� ��� �Ǹ��� ���۱��ڰ� �����ϴ�.
 *
 *
 *  [+] �밡���� ǥ���
 *  -----------------------------------------------------
 *   ���ξ�     ��
 *  -----------------------------------------------------
 *   c          char
 *   by         unsigned char (BYTE)
 *   n          short int or int
 *   x          short int (�׷��� ��ǥ x��ǥ)
 *   y          short int (�׷��� ��ǥ y��ǥ)
 *   i          int
 *   b          int (BOOL)
 *   w          unsigned int (WORD)
 *   h          unsigned int (WORD) (HANDLE)
 *   dw         unsigned long int (DWORD)
 *   fn         Function (�Լ� ������)
 *   s          Character Array (NULL�� ���� �ʿ� ����)
 *   sz         Character String (NULL�� ������)
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
 *  �ؼ� ��� �Ӽ� ��������, ��� ������ �ǹ� ������ �̿���,
 *  �ѱ��� ���¼Ҹ� �����ϴ� �˰����� 1.00 ��
 *
 *  1. �ǹ������� �ѱ��� ����� �µ��� �����Ѵ�.
 *  2. SEM ���𿡼� �� �ǹ����������� ��θ� ��� ���ÿ� �����Ѵ�.
 *
 *     (��) SEM    (SUBJ     (PREN    (PRED   �׸���)
 *                                    (SUBJ   (REF    ö��))
 *                           )
 *                  .............
 *          ö��   : SUBJ - PREN - SUBJ - REF - NULL
 *          �׸��� : SUBJ - PREN - PRED - NULL
 *          .........
 *  3. �� ��� ������ �̿��Ͽ�, �� �ǹ������� �ش��ϴ� ��������� Ž���Ѵ�.
 *     �� �� �� �ǹ������� ǰ�翡 ���� ó������� �ٸ���.
 *     (��) ü��
 *          ��� : ���꼺 + ���� + (~��������������)  = '-��'
 *          �ǹ� : �ݼӼ��� �����ϴ� ������ ����
 *     (��) ���
 *          ��� : �������, �λ缺 ��������, ��� ���� ����
 *          �ǹ� : ..
 *     ....
 *
 */

/*
 *  ��� ���� Ž�� ��θ� ����
 */
int nPathStack[MAX_PATH_STACK_CNT][MAX_PATH_STACK_DEPTH];
int nPathStackCnt;
int nPathStackDepth;

/*
 *  �� ������ �⺻ ���¼Ҹ� ������ ���ڿ� ������ �迭
 */
char *pszPhrase[MAX_PATH_STACK_CNT];            /* String of End Of Word */

/*
 *  �Է�   :  .
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��� ���ÿ� ���õ� �������� �ʱ�ȭ
 */
void InitPathStack()
{
  nPathStackCnt = nPathStackDepth = 0;
  memset(nPathStack, NULL, sizeof(nPathStack));
}

/*
 *  �Է�   :  �Ӽ�
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������ ��� �߿��� nFeature�� ��� ������ ....
 */
static int GetSentenceOrder(int nFeature)
{
  /* ��� ���� ���Ͽ��� �о� �;���...
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
 *  �Է�   :  ���� ���� ������, ���� ���� ������
 *  ���   :  .
 *  ȣ���� :  GetFeatureNumber
 *  ȣ��� :
 *  ��  �� :  ������ �Ӽ����� ���Ѵ�.
 */
static int SortFunc(pArcA, pArcB)
ARC *pArcA;
ARC *pArcB;
{
  return GetSentenceOrder(pArcA->nFeature) - GetSentenceOrder(pArcB->nFeature);
}

/*
 *  �Է�   :  �ǹ� ������ ������ ���� ������ (Sem)
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  Sem���� �ѱ��� ����� �µ��� �����Ѵ�.
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
 *  �Է�   :  ���� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������ ���� ������ ã�� ���� ��� ������ ���Ѵ�.
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
      DispError("��� ������ �ִ� ���̸� �ʰ��ϼ̽��ϴ�\n", true);
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
        DispError("��� ������ �ִ� ������ �ʰ��ϼ̽��ϴ�\n", true);
      return;
    }
  }
}

/*
 *  �Է�   :  ���� ������, �Ӽ� ����Ʈ�� ������ ���� �迭�� ������
 *  ���   :  �Ӽ� ����Ʈ�� ���� ã�ư� ���� ������
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  pnList�� ���� ���� ������ ���� �������� �� ���� �����͸� �����ش�
 */
NODE *GetNodePtr4List(pNode, pnList)
NODE *pNode;
int *pnList;
{
  int nCnt, nArcNum;

  for(nCnt = 0; nCnt < MAX_PATH_STACK_DEPTH && pnList[nCnt]; nCnt++) {
    nArcNum = GetArcNumber(pNode, pnList[nCnt]);
    if(nArcNum == -1)
      DispError("���� ������ �߸� �Ǿ����ϴ�\n", true);
    else
      pNode = pNode->Arc[nArcNum].pNode;
  }
  if(nCnt == MAX_PATH_STACK_DEPTH)
    DispError("��� ������ �ִ� ���̸� �ʰ� �ϼ̽��ϴ�\n", true);
  return pNode;
}

/*
 *  �Է�   :  ����������, ���� ���������͸� ã�� ���� �Ӽ�
 *  ���   :  ��ν����� ���� ã�ư� ���� ����������
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��ν��ÿ� ���� �ش缺���� ��������� ã�´�.
 *            SUBCAT�� ���� �߿��� nFeature�� ��ġ�ϴ� �Ӽ��� �ִٸ�
 *            ���� ������, �ƴϸ� HEADD���� ������ ����.
 */
static NODE *GetNextNode4PathStack(pNode, nFeature)
NODE *pNode;
int  nFeature;
{
  int nArc;
  NODE *pTempNode;

  nArc = GetArcNumber(pNode, SUBCAT);
  if(nArc == -1)
    DispError("SUBCAT������ �����ϴ�. ��� ������ �߸��Ǿ����ϴ�. [kg-korea::GetNextNode4PathStack]", true);
  pTempNode = pNode->Arc[nArc].pNode;
  nArc = GetArcNumber(pTempNode, nFeature);
  if(nArc == -1) {
    nArc = GetArcNumber(pTempNode, HEADD);
    if(nArc == -1)
      DispError("HEADD������ �����ϴ�. ��� ������ �߸��Ǿ����ϴ�. [kg-korea::GetNextNode4PathStack]", true);
  }
  return pTempNode->Arc[nArc].pNode;
}

/* �������� ---> */
struct Tense2Morph {
  char *pszTense;      /* ���� �Ӽ��� */
  char *pszMorph;      /* ������ �ش��ϴ� ��� ��� ���¼� */
} Tense2Morph[] = {
  { "PRESNT",   ""       }, { "RECOLL",   "��"     },
  { "FUTURE",   "��",    }, { "PAST",     "��"     },
  { "PPAST",    "����",  }, { "FUTUREC",  "�ڴ�"   },
  { "PASTREC",  "����",  }, { "PASTFUT",  "����"   },
  { "PASTREC",  "����",  }, { "PASTFUT",  "����"   },
};

/*
 *  �Է�   :  ������ �ش��ϴ� �Ӽ���
 *  ���   :  ������ �����ϴ� ��� ���
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���� �Ӽ����� �����ϴ� ���������̸� ���Ѵ�
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
 *  �Է�   :  ���� ������, �������� ���ڿ��� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���ξ� ó��
 */
void GetPrefixPhrase(pSyn, pszPhrase)
NODE *pSyn;
char *pszPhrase;
{
  int nArcNum;

  nArcNum = GetArcNumber(pSyn, PASSIV);
  if(nArcNum != -1 && !strcmp(*(pSyn->Arc[nArcNum].Value.pszStr), "+")) {
    /* ���� ���� �ұ�Ģ�� ������ �־�� �Ѵ� */
    /* ������ �˻��ؼ�, � ���̻縦 ������ �ϴ���... */
    strcat(pszPhrase, "��");
  }
}

/*
 *  �Է�   :  ������� ���� ������, �������� ���ڿ� ������
 *  ���   :  ���� ��� ��̰� �پ����� �� �Ӽ���, �ƴϸ� 0
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��� ��� ������ �̿��ؼ�, ���¼� ����
 *            ���� ��� ��̰� �پ������� ���� ������ ���� �߿���
 *            �������̸� ������ �� �ʿ��� ��찡 �ֱ� �����̴�.
 */
int GetPreEowPhrase(pSyn, pszPhrase)
NODE *pSyn;
char *pszPhrase;
{
  int nArcNum, nTense;
  char *pszStr;

  /* ��ü ���� : '-��-' */
  nArcNum = GetArcNumber(pSyn, SHONOR);
  if(nArcNum != -1 && !strcmp(*(pSyn->Arc[nArcNum].Value.pszStr), "+")) {
    /* ���� ���� �ұ�Ģ�� ������ �־�� �Ѵ� */
    strcat(pszPhrase, "��");
  }
  /* ���� */
  nTense = 0;
  nArcNum = GetArcNumber(pSyn, TENSE);
  if(nArcNum != -1) {
    /* ���� ���� �ұ�Ģ�� ������ �־�� �Ѵ� */
    pszStr = GetTenseMorph(*(pSyn->Arc[nArcNum].Value.pszStr));
    MergeHangulStr(pszPhrase, pszStr);
/*    strcat(pszPhrase, pszStr);*/
    nTense = GetFeatureNumber(pszStr);
  }
  return nTense;
}

/*
 *  �Է�   :  ��� ���� �Ӽ���
 *  ���   :  ��(mood)�� ���� �Ӽ��̸� �� ���� �Ӽ���, �ƴϸ� NULL
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  � ��̸� �����Ѵ�. (������, ��������)
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
 *  �Է�   :  �Ӽ�
 *  ���   :  nFeature�� ������� �Ӽ��̸� ��, �ƴϸ� ����
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������� �Ӽ����� �ƴ��� �Ǻ��Ѵ�
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
 *  �Է�   :  ������� ���� ������, ���� ���ڿ� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��� ������ �̿��ؼ� �ѱ��� ��������� �����Ѵ�.
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
 *  �Է�   :  ������� ���� ������, ���� ���ڿ� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��� ������ �̿��ؼ� �ѱ��� ����� �����Ѵ�.
 */
void GeneratePredPhrase(pSyn, pszPhrase)
NODE *pSyn;
char *pszPhrase;
{
  int nLen, nTense, nArc, nMood, nFeature;

  GetPrefixPhrase(pSyn, pszPhrase);                 /* ����, �ǵ� ����  */
  GenerateAuxlPhrase(pSyn, pszPhrase);              /* �������         */
  nArc = GetArcNumber(pSyn, EWFORM);
  if(nArc == -1)
    DispError("��� ������ �߸� �Ǿ����ϴ� [kg-korea :: GetEowPhrase", true);
  nMood = GetMoodFeatureNumber(pSyn->Arc[nArc].Value.pszStr[0]);
  if(nMood) { /* ������ */
    GetPreEowPhrase(pSyn, pszPhrase);        /* ��� ��� ���� */
    GetEEowPhrase(pSyn, pszPhrase, nMood);
  }
  else {
    nFeature = GetFeatureNumber(pSyn->Arc[nArc].Value.pszStr[0]);
    if(nFeature == VMODI) {
      strcpy(pszPhrase, pSyn->Arc[nArc].Value.pszStr[0]);
      MergeHangulStr(pszPhrase, "��");
      return;
    }
    else if(nFeature == NMODI) {
      /* �߰� .... */
    }
    /* !!! ���������̸� ���̿� ������ ���� �����̸� ������ �� �������� ���� */
    nArc = GetArcNumber(pSyn, TENSE);
    if(nArc != -1) {
      nTense = GetFeatureNumber(*(pSyn->Arc[nArc].Value.pszStr));
      GetNEowPhrase(nFeature, pszPhrase, nTense);         /* � ��� ����   */
    }
  }
}

/*
 *  �Է�   :  ���ڿ� ������
 *  ���   :  ������ �ѱ۹��� - (�����δ� ���ڿ� ������), ������ -1;
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �ѱ� ���ڿ� �߿��� ���� ������ ����(���ڿ�)�� ���Ѵ�.
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
 *  �Է�   :  �ѱ� �ѱ���(���ڿ� ������)
 *  ���   :  ��ħ�� ������ ��, ������ ����
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��ħ�� �ִ� �������� �˾Ƴ���
 */
static int IsFinal(pszHangulChar)
char *pszHangulChar;
{
  unsigned int nKScode, nTGcode, n3rd;

  nKScode = (pszHangulChar[0] << 8);
  nKScode |= (pszHangulChar[1]) & 0x00ff;

  /*
   *  �ڵ庯ȯ :     KS�ϼ��� --> ���������
   */
  nTGcode = KS2TG(nKScode);

  n3rd = (nTGcode & 0x1F);         /* ���� �и� */
  return (n3rd == FILL_LST) ? false : true;
}

/*
 *  �Է�   :  ������� ���� ������, ���� ���ڿ� ������, ���� �Ӽ�
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��� ������ �̿��ؼ� �ѱ��� �������� �����Ѵ�.
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
    /* �� �� ������ ���������� ����� �־�� ���� ������? */
    if(pSyn->Arc[nArc].Value.pszStr[0][0], '+')
      strcat(pszPhrase, "��");
  }
  pszTemp = GetLastKoreanChar(pszPhrase);
  bFinal = IsFinal(pszTemp);
  GetCasePhrase(nCase, pszPhrase, bFinal);
}

/*
 *  �Է�   :  ��� ����, �ؼ� ��� ���� ������, ����� ���� ���ڿ� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �� ������ ���¼Ҹ� �����Ѵ�.
 */
void GenerateKoreanPhrase(pnPathStack, pRootNode, pszPhrase, pszResultStr)
int *pnPathStack;                 /* ��� ����                        */
NODE *pRootNode;                  /* �ؼ� ����� �Ѹ� ����            */
char *pszPhrase;                  /* �� ������ �⺻ ���¼�            */
char *pszResultStr;               /* ���� ���                        */
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
 *  �Է�   :  �ǹ� ������ ������ ���� ������, ����� ���� ���ڿ� ������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������ �ѱ��� ���� �� ���¼� �������� �� �Լ�.
 */
void GenerateKoreanSentence(pSemNode, pRootNode, pszResultStr)
NODE *pSemNode;
NODE *pRootNode;
char *pszResultStr;
{
  int nCnt, nDepth;

  InitPathStack();
  /* ��� ���� Ž�� ��ο� �� ������ �⺻ ���¼Ҹ� ���Ѵ� */
  GetPathStackAndPhrase(pSemNode->Arc, pszPhrase);
  /* ��� ������ �ִ� ���� �Ǵ� ������ ù��° ������ 0�� �ͱ��� */
  for(nCnt = 0; nCnt < MAX_PATH_STACK_CNT  && nPathStack[nCnt][0]; nCnt++) {
    GenerateKoreanPhrase(nPathStack[nCnt], pRootNode, pszPhrase[nCnt], pszResultStr);
  }
}

/* ------------------------------------------------------------------------- */
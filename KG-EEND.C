/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-eend.c
 *  �Լ�(��)  :
 *  ���� ���� :  �ѱ��� ������ ���������� ������ ����
 *  ���� ��   :  1993. 09. 23
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

/*
 *  �ѱ��� ������ ������ ������ ���� Ver 1.00
 *
 *    +----- ����� �Ӽ�, ������ �Ӽ�, ���� �Ӽ����� ����
 *    |      ǰ�簡 �ƴ϶�, ��� �Ӽ� �߿� ����� �Ӽ�, ������ �Ӽ�
 *    |      �־ �̸� ǥ��...
 *    |         +-------- ����, ���簡 �ƴ� ��
 *    |         |      +------ ��, �ǹ�, ��ź, ����, ���, ���, û��
 *    |         |      |    +----- ���� ����, �η� ����, ���� ����
 *    |         |      |    |      ���� ����, �η� ����, ���� ����
 *    |         |      |    |           +-----  ��������� �ٸ� ���¸�
 *    |         |      |    |           |       ó���ϱ� ���� �÷���
 *    |         |      |    |           |       (-����, -�´� ó��)
 *    |         |      |    |           |           +- �ٸ� ���°� ������ ��
 *    |         |      |    |           |           |  ������ �Ѱ����� ����Ѵ�.
 *    |         |      |    |           |           |  ó������� ���� ���Ѵ�.
 *  ==+=========+======+====+===========+===========+========================
 *    ǰ��Ӽ�  ����   ��   ������    ��̺���    �����������¼�
 *  =========================================================================
 *    OTHERS   PRESNT  DECLM LOWER1      1           �´�
 *    OTHERS   PRESNT  DECLM LOWER2      0           ��
 *    OTHERS   PRESNT  DECLM LOWER3      0           ��
 *  <�߰� ����>
 *  ADJNAT     PRESNT  DECLM LOWER1      0           ��
 *  <�߰� ����>
 *  COPULA     PRESNT  DECLM LOWER1      0           ��
 *  <�߰� ����>
 *  ------------------------------------------------------------------------
 *
 *  �� OTHERS  : (ADJNAT -) && (COPULA -) or ~(PRESNT)
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
 *  ������ ������ ǥ
 */
EEOW_TABLE EEndOfWord[MAX_EEOW_CNT];

/*
 *  �Է�   :  �����̸�
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������ ǥ ������ �о�д�
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
    printf("�� ������ ǥ (%s)�� �н��ϴ�\n", pszFileName);
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
 *  �Է�   :  ǰ��Ӽ�, ����, ��, �����Ī
 *  ���   :  ã���� �ش� ��ȣ, ��ã���� -1
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �����̸� ǥ���� ã�Ƽ� �� ��ȣ�� �����ش�.
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
 *  �Է�   :  ������� ����������, �������ڿ�, ��
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �����̸� ���Ѵ�.
 */
void GetEEowPhrase(pSyn, pszPhrase, nMood)
NODE *pSyn;
char *pszPhrase;
int  nMood;
{
  int nArcNum, nCnt, nCat, nTense, nHonor;

  /*
   * ǰ�� �Ӽ� ���ϱ� (ADJNAT, COPULA, OTHERS)
   */
  nCat = OTHERS;  /* ������ */
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
   *  ���� ���ϱ� (TENSE, OTHERS)
   */
  nTense = PRESNT; /* ������ */
  nArcNum = GetArcNumber(pSyn, TENSE);
  if(nArcNum != -1) {
    nTense = GetFeatureNumber(pSyn->Arc[nArcNum].Value.pszStr[0]);
    if(nTense != PRESNT)
      nTense = OTHERS;
  }
  /*
   *  ��� ���� ���ϱ� (LOWER1, LOWER2, LOWER3, HIGHR1, HIGHR2, HIGHR3)
   */
  nHonor = LOWER1; /* ������ */
  nArcNum = GetArcNumber(pSyn, OHONOR);
  if(nArcNum != -1) {
    nHonor = GetFeatureNumber(pSyn->Arc[nArcNum].Value.pszStr[0]);
  }

  /*
   *  ���� �Ӽ��� ���� �����̸� ���Ѵ�.
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
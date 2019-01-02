/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-nend.c
 *  �Լ�(��)  :
 *  ���� ���� :  �ѱ��� �������� ���������� �������� ����
 *  ���� ��   :  1993. 09. 28
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
 *  �ѱ��� �������� ������ ������ ���� Ver 1.00
 *
 *    +----- �������� ����, (������̿� ���Ӿ�̸� ��� ����)
 *    |            +------------- �ϰ��(����)
 *    |            |    +-------- ������(�̷�)
 *    |            |    +    +--- ȸ���()
 *    |            |    |    |     +-------  ��������� �ٸ� ���¸�
 *    |            |    |    |     |         ó���ϱ� ���� �÷���
 *    |            |    |    |     |           +-- �������� ���¼�
 *    |            |    |    |     |           |
 *  ==+============+====+====+=====+===========+==========================
 *    �������     ��   ��   ��    ��̺���    �����������¼�
 *  ======================================================================
 *    SMPLAR       1    1    0     0           ��
 *    ORDRAR       0    0    0     0           ����
 *    RSLTAR       0    0    0     1           �
 *    SMLTAR       0    0    0     1           �鼭
 *    IMMDET       0    0    0     0           �ڸ���
 *    <�߰� ����>
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
 *  �������� ������ ǥ
 */
NEOW_TABLE NEndOfWord[MAX_NEOW_CNT];

/*
 *  �Է�   :  �����̸�
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �������� ǥ ������ �о�д�
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
    printf("�� �������� ǥ (%s)�� �н��ϴ�\n", pszFileName);
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
 *  �Է�   :  �������̼Ӽ�
 *  ���   :  ã���� �ش� ��ȣ, ��ã���� -1
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �������̸� ǥ���� ã�Ƽ� �� ��ȣ�� �����ش�.
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
 *  �Է�   :  ������� ����������, ����� ���� ���ڿ� ������, ����
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �������̸� ���Ѵ�.
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
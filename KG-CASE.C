/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-case.c
 *  �Լ�(��)  :
 *  ���� ���� :  ����Ӽ����κ��� ���� ���繮�ڿ��� ���Ѵ�.
 *  ���� ��   :  1993. 10. 01
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
 *  �ѱ��� ���� ������ ������ ���� Ver 1.00
 *
 *    +----- ���� �Ӽ�
 *    |            +------ ��ħ����, ��ħ����, ��ħ����
 *    |            |       (FINALZ)  (FINALO)  (FINALX)
 *    |            |            +--- �����ϸ鼭 ���ȭ�� �ʿ������� ���� �÷���
 *    |            |            |              +-- ���� ���¼�
 *    |            |            |              |
 *  ==+============+============+==============+==========================
 *    ��������     ��ħ         ���纯ȭ       ���� ���¼�
 *  ======================================================================
 *    SUBJ         FINALX       0              ��
 *    SUBJ         FINAL0       0              ��
 *    OBJ          FINALX       0              ��
 *    OBJ          FINAL0       0              ��
 *    .........
 *    <�߰� ����>
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

/* ���� ������ ��ħ ������ ������ ��쿡 �ʿ� */
/*     ��ħ����, ��ħ����, ��ħ����           */
enum { FINALZ,   FINALO,   FINALX };
static char *szFinal[] = { "FINALZ", "FINALO", "FINALX", "" };

static char szWord[MAX_STR_LEN];

/*
 *  ���� ������ ǥ
 */
CASE_TABLE CaseTable[MAX_CASE_CNT];

/*
 *  �Է�   :  ��ħ���� ���ڿ�
 *  ���   :  ��ħ���� ��ȣ, �����ϸ� -1
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��ħ���� ���ڿ����� ��ħ���� ��ȣ�� ���Ѵ�.
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
 *  �Է�   :  �����̸�
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���� ǥ ������ �д´�.
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
    printf("�� ���� ǥ (%s)�� �н��ϴ�\n", pszFileName);
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
 *  �Է�   :  ���� �Ӽ�
 *  ���   :  ã���� �ش� ��ȣ, ��ã���� -1
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���� ǥ���� ã�Ƽ� �� ��ȣ�� �����ش�.
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
 *  �Է�   :  ���� �Ӽ�, ����� ���� ���ڿ�, ��������
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���縦 �����ؼ� ��� ���ڿ��� �ٿ��ش�.
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
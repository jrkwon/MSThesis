/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-auxl.c
 *  �Լ�(��)  :
 *  ���� ���� :  �������Ӽ����� ������� ���¼Ҹ� ���Ѵ�.
 *  ���� ��   :  1993. 10. 02
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
 *  �ѱ��� ������� ������ ������ ���� Ver 1.00
 *
 *    +----- ������� �Ӽ�
 *    |            +------ ���������̰� ��ȯ�� �ʿ������� ���� �÷���
 *    |            |
 *    |            |                           +-- ����������+�������
 *    |            |                           |
 *  ==+============+===========================+==========================
 *    �������     ��̺�ȭ                    �������
 *  ======================================================================
 *    PRGRSS       0                           ��_�ִ�
 *    STATE        1                           ��_�ִ�
 *    DONOT        0                           ��_�ʴ�
 *    FORBID       0                           ��_����
 *    .........
 *    <�߰� ����>
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
 *  ������� ������ ǥ
 */
AUXL_TABLE AuxlTable[MAX_AUXL_CNT];

/*
 *  �Է�   :  �����̸�
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������� ǥ ������ �д´�.
 */
void ReadAuxlTable(pszFileName, bView)
char *pszFileName;
int bView;
{
  char szFeature[MAX_AUXL_LEN], szTrans[MAX_AUXL_LEN], szAuxl[MAX_AUXL_LEN];
  char *pszStr, *pTemp;
  int nCnt, nAns;

  if(bView) {
    printf("�� ������� ǥ (%s)�� �н��ϴ�\n", pszFileName);
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
 *  �Է�   :  ������� �Ӽ�
 *  ���   :  ã���� �ش� ��ȣ, ��ã���� -1
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������� ǥ���� ã�Ƽ� �� ��ȣ�� �����ش�.
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
 *  �Է�   :  ������� �Ӽ�, ����� ���� ���ڿ�
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ��������� �����ؼ� ��� ���ڿ��� �ٿ��ش�.
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

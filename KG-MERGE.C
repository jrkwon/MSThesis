/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-merge.c
 *  �Լ�(��)  :
 *  ���� ���� :  ��� ���(�Ǵ� ü��� ����) ���� ���� ��������
 *  ���� ��   :  1993. 10. 04
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

#include <string.h>
#include "kg-merge.h"
#include "kg-node.h"
#include "kg-code.h"
#include "kg-type.h"

/*
void (*fnIrregular[])(char *pszStr1, char *pszStr2) = {
  Sirregular, Dirregular, Birregular, REUirregular, Uirregular,
  YEOirregular, GEOirregular, NEOirregular, REOirregular, Hirregular
};
*/

static char szChar[3];

/*
 * �ڵ庯ȯ�ϴ� Ƚ���� ���̱⺸�ٴ�, ���α׷� �������̽���
 * ������ �� �ְ� �ϱ� ���� �ʿ��� ������ �ڵ庯ȯ�� �Ѵ�.
 */
/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *GetFirstHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast;
/*  char szChar[3]; */

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = FILL_MID;
  nLast  = FILL_LST;
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, FIRST_CODE);
  szChar[0] = (nKScode >> 8) & 0x00ff;
  szChar[1] = (nKScode & 0x00ff);
  szChar[2] = NULL;
  return szChar;
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *FallFirstHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast, nKind;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = FILL_1ST;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = (nTGcode & 0x1f);
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKind = FULL_CODE;
  if(nMid == FILL_MID)
    nKind = LAST_CODE;
  else if(nLast == FILL_LST)
    nKind = MID_CODE;
  nKScode = TG2KS(nTGcode, nKind);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *GetMidHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast;
/*  char szChar[3]; */

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = FILL_1ST;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = FILL_LST;
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, MID_CODE);
  szChar[0] = (nKScode >> 8) & 0x00ff;
  szChar[1] = (nKScode & 0x00ff);
  szChar[2] = NULL;
  return szChar;
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *FallMidHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast, nKind;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = FILL_MID;
  nLast  = (nTGcode & 0x1f);
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKind = FULL_CODE;
  if(nFirst == FILL_1ST)
    nKind = LAST_CODE;
  else if(nLast == FILL_LST)
    nKind = FIRST_CODE;
  nKScode = TG2KS(nTGcode, nKind);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *GetLastHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast;
/*  char szChar[3]; */

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = FILL_1ST;
  nMid   = FILL_MID;
  nLast  = (nTGcode & 0x1f);
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, LAST_CODE);
  szChar[0] = (nKScode >> 8) & 0x00ff;
  szChar[1] = (nKScode & 0x00ff);
  szChar[2] = NULL;
  return szChar;
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *FallLastHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast, nKind;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = FILL_LST;
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKind = FULL_CODE;
  if(nFirst == FILL_1ST)
    nKind = MID_CODE;
  else if(nMid == FILL_MID)
    nKind = FIRST_CODE;
  nKScode = TG2KS(nTGcode, nKind);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
void EUinsert(pszChar1, pszChar2, pszInsBuf)
char *pszChar1;
char *pszChar2;
char *pszInsBuf;
{
  static char *pszHanEle[] = { "��", "��", "��", "��", "��", "", "��", "��" };
  char *pszTemp;
  unsigned nEleCode;
  int nCnt;

  if(strcmp(GetLastHanCharElement(pszChar1), "��")) {
    nEleCode = (pszChar2[0] << 8);
    nEleCode |= (pszChar2[1]) & 0x00ff;
    if(!strcmp("��", pszChar2) || !strcmp("��", pszChar2)) {
      strcpy(pszInsBuf, "��");
      return;
    }
    if(!IsKSsingle(nEleCode))
      return;

    pszTemp = (char *)GetFirstHanCharElement(pszChar2);
    for(nCnt = 0; pszHanEle[nCnt][0]; nCnt++) {
      if(!strcmp(pszTemp, pszHanEle[nCnt])) {
        strcpy(pszInsBuf, "��");
        return;
      }
    }
  }
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
void EUfalling(pszChar1, pszChar2)
char *pszChar1;
char *pszChar2;
{
  if(!strcmp(GetMidHanCharElement(pszChar1), "��")) {
    if(!strcmp(GetMidHanCharElement(pszChar2), "��")) {
      FallMidHanCharElement(pszChar1);
    }
  }
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
void Rfalling(pszChar1, pszChar2)
char *pszChar1;
char *pszChar2;
{
  static char *pszHanEle[] = { "��", "��", "��", "��", "" };
  int nCnt;

  if(!strcmp(GetLastHanCharElement(pszChar1), "��")) {
    for(nCnt = 0; pszHanEle[nCnt][0]; nCnt++) {
      if(!strcmp(GetFirstHanCharElement(pszChar2), pszHanEle[nCnt])) {
        FallLastHanCharElement(pszChar1);
      }
    }
  }
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
void VocalHarmony(pszChar1, pszChar2)
char *pszChar1;
char *pszChar2;
{
  static char *pszNegaNeu[] = {
    "��", "��", "��", "��", "��", "��", "��",
    "��", "��", "��", "��", "��", "��", ""
  };
  static char *pszTmp;
  int nCnt;

  if(!strcmp(pszChar2, "��")) {
    pszTmp = GetMidHanCharElement(pszChar1);
    for(nCnt = 0; pszNegaNeu[nCnt][0]; nCnt++) {
      if(!strcmp(pszTmp, pszNegaNeu[nCnt])) {
        strncpy(pszChar2, "��", 2);
        return;
      }
    }
  }
  else if(!strcmp(pszChar2, "��")) {
    pszTmp = GetMidHanCharElement(pszChar1);
    for(nCnt = 0; pszNegaNeu[nCnt][0]; nCnt++) {
      if(!strcmp(pszTmp, pszNegaNeu[nCnt])) {
        strncpy(pszChar2, "��", 2);
        return;
      }
    }
  }
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
void SoundShrink(pszChar1, pszChar2, pszInsBuf)
char *pszChar1;
char *pszChar2;
char *pszInsBuf;
{
  char *pszTmp;

  pszTmp = (pszInsBuf[0] == NULL) ? pszChar2 : pszInsBuf;
  if(!strcmp(GetLastHanCharElement(pszChar1), "")) {
    if(!strcmp(GetMidHanCharElement(pszChar1), "��")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "��")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "��", MID_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
   else if(!strcmp(GetMidHanCharElement(pszChar1), "��")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "��")) {
        MakeHanChar(pszChar1, "��", MID_CODE);
        MakeHanChar(pszChar1, GetLastHanCharElement(pszTmp), LAST_CODE);
        pszTmp[0] = NULL;
      }
    }
    else if(!strcmp(GetMidHanCharElement(pszChar1), "��")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "��")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "��", MID_CODE);
        MakeHanChar(pszTmp, pszChar1, FIRST_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
    else if(!strcmp(GetMidHanCharElement(pszChar1), "��")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "��")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "��", MID_CODE);
        MakeHanChar(pszTmp, pszChar1, FIRST_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
    else if(!strcmp(GetMidHanCharElement(pszChar1), "��")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "��")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "��", MID_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
  }
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *MakeHanChar(pszChar, pszEle, nKind)
char *pszChar;
char *pszEle;
int  nKind;
{
  unsigned nTGcode, nKScode, nEleCode;
  int nFirst, nMid, nLast, nTmp;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = (nTGcode & 0x1f);
  nEleCode = (pszEle[0] << 8);
  nEleCode |= (pszEle[1]) & 0x00ff;
  if(IsKSsingle(nEleCode)) {
    nTmp = KS2ElementTG(nEleCode, nKind);
  }
  else {
    nTmp = KS2TG(nEleCode);
  }

  if(nKind == FIRST_CODE) {
    nFirst = (nTmp >> 10) & 0x1f;
  }
  else if(nKind == MID_CODE) {
    nMid   = (nTmp >> 5) & 0x1f;
  }
  else if(nKind == LAST_CODE) {
    nLast  = (nTmp & 0x1f);
  }

  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, FULL_CODE);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
void MergeHangulChar(pszChar1, pszChar2, pszInsBuf)
char *pszChar1;
char *pszChar2;
char *pszInsBuf;
{
  char *pszTmp, *pszLast;

  pszTmp = (pszInsBuf[0] == NULL) ? pszChar2 : pszInsBuf;
  if(!strcmp(GetLastHanCharElement(pszChar1), "")) {
    if(!strcmp(GetFirstHanCharElement(pszTmp), "��")
       || !strcmp(GetFirstHanCharElement(pszTmp), "")) {
      MakeHanChar(pszChar1, pszTmp, LAST_CODE);
      pszTmp[0] = NULL;
    }
    else {
      pszLast = GetLastHanCharElement(pszTmp);
      MakeHanChar(pszChar1, pszLast, LAST_CODE);
      pszTmp[0] = NULL;
    }
  }
}

/*
 *  ü��� ���縦 ���̴µ� ������.
 */
/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *AttachHangulStr(pszStr1, pszStr2)
char *pszStr1;
char *pszStr2;
{
  char szBuf1[3], szBuf2[3], szStr1[MAX_STR_LEN], szStr2[MAX_STR_LEN];
  char szResult[MAX_STR_LEN], szInsBuf[MAX_STR_LEN];
  unsigned nKScode, nTGcode;
  int nLen;

  strcpy(szStr1, pszStr1);
  strcpy(szStr2, pszStr2);

  szInsBuf[0] = NULL;
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szBuf1[0] = szStr1[nLen-2], szBuf1[1] = szStr1[nLen-1], szBuf1[2] = NULL;
  szBuf2[0] = szStr2[0], szBuf2[1] = szStr2[1], szBuf2[2] = NULL;

  EUinsert(szBuf1, szBuf2, szInsBuf);       /* �� '��'����      */
  MergeHangulChar(szBuf1, szBuf2, szInsBuf);/* �� �ڼ��ռ�      */

  sprintf(szResult, "%s%s%s", szBuf1, szInsBuf, szBuf2);
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szStr1[nLen-2] = NULL;
  strcat(szStr1, szResult);
  strcat(szStr1, szStr2+2);
  strcpy(pszStr1, szStr1);
  return pszStr1;
}

/*
 *  ����� ��� ��̸� �����ϰ�(?) �ٿ��ִ� �˰����� Ver 1.00
 *                   * ������ ǥ���� ��̺��� �÷��װ� ���� ��
 *
 *  �� ó�����߿� ���ԵǴ� �����̳� �ұ�Ģ Ȱ�� ����� ����� ������
 *     �ڼҵ��� ���� szInsBuf������ �����ϰ�
 *     �� ������ ���ڰ� ����ִٸ�, ��̺κ��� ����ϰ� �ϰ� ó���Ѵ�.
 * 1. '��'����
 *    ������� '��'�̿��� ��ħ�� ����,
 *    ��̽����� '��,��,��,��,��,��'(��̰� ������ ���ڰ� �ƴ� �� �ڼҶ��
 *    ��ħ�̶� ����)�̸�, ���� '��'����
 * 2. '��'Ż��
 *    ��� '��'�� ������ '-��'�� �����ϴ� ��̾տ��� '��'Ż��
 * 3. '��'Ż��
 *    ������� ��ħ�� '��'�̰�, ��̽����� '��,��,��,��'�� �� '��'Ż��
 * 4. ������ȭ
 *    ���ڿ�2�� '��'�� �����ϰ�,
 *    ('-��/-��' �ΰ��� ���°� ������ ���� ������ '-��'�� ����Ѵ�)
 *     ���ڿ�1�� ��� �Ҹ��� ��������, �߼������̸�
 *    '��' -> '��'�� �ٲ��ش�.
 * 5. �ұ�Ģ Ȱ��ó��
 *    �� ���ұ�Ģ : '-��', '-��' �տ��� '��'Ż��
 *    �� ���ұ�Ģ : '-��', '-��' �տ��� '��'�� '��'��
 *    �� ���ұ�Ģ : '-��', '-��' �տ��� '��'�� '��/��'
 *                  �� �߼������� ���������� ������... (��+�� -> �����)
 *    �� ���ұ�Ģ : '-��', '-��' �տ��� ��������� '��'�� Ż���ϰ�
 *                 � ������ �ι�° ������ ��ħ���� '��'�� ÷��
 *                 (�帣 + �� -> �ꤩ + �� -> �귯)
 *    �� ��ұ�Ģ : '-��', '-��' �տ��� '��'Ż�� ('Ǫ��'�ϳ� ��)
 *    �� ���ұ�Ģ : '-��' �տ��� ��̰� '-��'�� �ٲ��.
 *                 ('�ϴ�'����)
 *    �� �Ŷ�ұ�Ģ : ��̰� '-�ƶ�'���� '�Ŷ�'�� �ٲ�
 *    �� �ʶ�ұ�Ģ : ��̰� '-�ƶ�'���� '�ʶ�'�� �ٲ�
 *                �� �Ŷ�, �ʶ� �ұ�Ģ���� ������¼� ��ü�� �ʿ��ϴ�..
 *                   ���ۺκп��� �˻��ؾ� �Ѵ�.
 *    �� ���ұ�Ģ : ��� '��'�� '��'�� �ٲ�
 *                  (�̸���, ������, Ǫ���� ��)
 *    �� ���ұ�Ģ :
 *       �� ������� ��ħ '��'�� Ż��
 *          �ʼ��� ����('��'�� ������ �����Ƿ� ����)���� ����
 *          (�Ķ� + �� -> �Ķ�)
 *       �� ��� ��̰� ��� ���Ѵ�.
 *          �ʼ��� ���� �Ǵ� �������� '��'�̸�
 *          ������� ��ħ '��'Ż���ϰ� (�Ķ� -> �Ķ�)
 *          ������� ������ '��' -> ��'�� �ٲ��, ����� ù���� Ż���Ѵ�.
 *          (�Ķ� + �Ƽ� -> �ķ���)
 * 6. �������
 *    ���ڿ�1�� �������� ������(�߼��� �ְ�, ������ FILL CODE)
 *    ���ڿ�2�� �������� �����ϸ�(�ʼ��� '��'�Ǵ� FILL CODE)
 * 7. �ڼ��ռ�
 *    (5.�ʹ� ��Ÿ��) �ΰ��� ���ڸ� �ռ��Ѵ�. (������ �ٸ� �ǹ�)
 *    �� + ���ϴ� -> ��ϴ� (�� '-���ϴ�'���� ������ ����߱� ����)
 */
/*
 *  �Է�   :
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :
 */
char *MergeHangulStr(pszStr1, pszStr2/*, nIrregular*/)
char *pszStr1;
char *pszStr2;
/* int  nIrregular; */
{
  char szBuf1[3], szBuf2[3], szStr1[MAX_STR_LEN], szStr2[MAX_STR_LEN];
  char szResult[MAX_STR_LEN], szInsBuf[MAX_STR_LEN];
  unsigned nKScode, nTGcode;
  int nLen;

  if(pszStr2[0] == NULL)
    return pszStr1;
  strcpy(szStr1, pszStr1);
  strcpy(szStr2, pszStr2);

  szInsBuf[0] = NULL;
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szBuf1[0] = szStr1[nLen-2], szBuf1[1] = szStr1[nLen-1], szBuf1[2] = NULL;
  szBuf2[0] = szStr2[0], szBuf2[1] = szStr2[1], szBuf2[2] = NULL;

  EUinsert(szBuf1, szBuf2, szInsBuf);       /* �� '��'����      */
  EUfalling(szBuf1, szBuf2);                /* �� '��'Ż��      */
  Rfalling(szBuf1, szBuf2);                 /* �� '��'Ż��      */
  VocalHarmony(szBuf1, szBuf2);             /* �� ������ȭ      */
/*fnIrregular[nIrregular](szBuf1, szBuf2);*//* �� �ұ�Ģ ó��   */
  SoundShrink(szBuf1, szBuf2, szInsBuf);    /* �� �������      */
  MergeHangulChar(szBuf1, szBuf2, szInsBuf);/* �� �ڼ��ռ�      */

  sprintf(szResult, "%s%s%s", szBuf1, szInsBuf, szBuf2);
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szStr1[nLen-2] = NULL;
  strcat(szStr1, szResult);
  if(strlen(szStr2) >= 2)
    strcat(szStr1, szStr2+2);
  strcpy(pszStr1, szStr1);
  return pszStr1;
}

/* ------------------------------------------------------------------------- */
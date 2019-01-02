/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-merge.h
 *  �Լ�(��)  :
 *  ���� ���� :  ��� ���(�Ǵ� ü��� ����)�� ���տ��� ��Ÿ���� �������� ó��
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

#ifndef _KG_MERGE_H_
#define _KG_MERGE_H_

char *GetFirstHanCharElement(char *pszChar);
char *FallFirstHanCharElement(char *pszChar);
char *GetMidHanCharElement(char *pszChar);
char *FallMidHanCharElement(char *pszChar);
char *GetLastHanCharElement(char *pszChar);
char *FallLastHanCharElement(char *pszChar);
void EUinsert(char *pszChar1, char *pszChar2, char *pszInsBuf);
void EUfalling(char *pszChar1, char *pszChar2);
void Rfalling(char *pszChar1, char *pszChar2);
void VocalHarmony(char *pszChar1, char *pszChar2);
void SoundShrink(char *pszChar1, char *pszChar2, char *pszInsBuf);
char *MakeHanChar(char *pszChar, char *pszEle, int nEle);
void MergeHangulChar(char *pszChar1, char *pszChar2, char *pszInsBuf);
char *MergeHangulStr(char *pszStr1, char *pszStr2/*, int nIrregular*/);

#endif

/* ------------------------------------------------------------------------- */

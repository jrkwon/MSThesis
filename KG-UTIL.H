/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-util.h
 *  �Լ�(��)  :
 *  ���� ���� :
 *  ���� ��   :  1993. 09. 15
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

#ifndef _KG_UTIL_H_
#define _KG_UTIL_H_

void DispError(char *pszMsg, int bCritical);
void DispErrorF(int bCritical, char *pszFormat, ... );
void *MemAlloc(unsigned int wSize);
void *ClearMemAlloc(int nEle, unsigned int wSize);

#endif

/* ------------------------------------------------------------------------- */
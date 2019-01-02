/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-util.c
 *  �Լ�(��)  :
 *  ���� ���� :
 *  ���� ��   :  1993. 09. 14
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
#include <stdarg.h>
#ifdef __TURBOC__
#include <alloc.h>
#else
#include <malloc.h>
#endif
#include "kg-util.h"
#include "kg-node.h"

/*
 *  �Է�   : ���� ���ڿ�, ġ���� �������� �ƴ���
 *  ���   : .
 *  ȣ���� : .
 *  ȣ��� : .
 *  ��  �� : �Ϲ����� ���� ǥ�� �� ����Ѵ�.
 */
void DispError(pszMsg, bCritical)
char *pszMsg;
int bCritical;
{
  printf(pszMsg);
  if(bCritical) {
    printf("\n�� ���������� ���α׷� ��ħ. �ΰ����� ������ �����\n");
    exit(-1);
  }
}

/*
 *  �Է�   : ġ���� �������� �ƴ���, ��� ����
 *  ���   : .
 *  ȣ���� : .
 *  ȣ��� : .
 *  ��  �� : �Ϲ����� ���� ǥ�� �� ����Ѵ�.
 */
void DispErrorF(int bCritical, char *pszFormat,  ... )
/*
int bCritical;
char *pszFormat;
*/
{
  va_list arg;
  char szStr[MAX_STR_LEN];

  va_start(arg, pszFormat);
  vsprintf(szStr, pszFormat, arg);
  DispError(szStr, bCritical);
  va_end(arg);
}

/*
 *  �Է�   : �Ҵ��� �޸� ũ��
 *  ���   : �������� (success or fail)
 *  ȣ���� : .
 *  ȣ��� : .
 *  ��  �� : �޸� ������ ���α׷� ���� �ߴ� ó���� ������ �޸� �Ҵ� �Լ�.
 */
void *MemAlloc(wSize)
unsigned int wSize;
{
  void *pPtr;

  pPtr = (void *)malloc(wSize);
  if(!pPtr) {
    DispError("�޸� ����......", 1);
  }
  return pPtr;
}

/*
 *  �Է�   : wSize ����, �Ҵ��� �޸� ũ��
 *  ���   : �������� (success or fail)
 *  ȣ���� : .
 *  ȣ��� : .
 *  ��  �� : �޸� ������ ���α׷� ���� �ߴ� ó���� ������ �޸� �Ҵ� �Լ�.
 *           ������ �Ҵ�Ǵ� �޸� = nEle * wSize Bytes
 */
void *ClearMemAlloc(nEle, wSize)
int nEle;
unsigned int wSize;
{
  void *pPtr;

  pPtr = calloc(nEle, wSize);
  if(!pPtr) {
    DispError("�޸� ����......", 1);
  }
  return pPtr;
}

/* ------------------------------------------------------------------------- */

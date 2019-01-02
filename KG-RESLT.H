/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-reslt.h
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

#ifndef _KG_RESLT_H_
#define _KG_RESLT_H_

#include "kg-node.h"

/*
 *  ���� ���� 1.00 ��
 *
 *  ( (POS      "�����")       ���ּ��� ǥ�ġ�
 *    (CAT      NOUNP)           ��
 *    (HEAD     (SYN    PRPRNN)  // PRoPeR NouN - Name ; ����̸� ��������
 *    ......
 *  )
 */

void ReadResultNode(char *pszFileName, NODE *pResultNode, int bView);

#endif

/* ------------------------------------------------------------------------- */
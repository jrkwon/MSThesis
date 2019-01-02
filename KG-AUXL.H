/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :
 *  �Լ�(��)  :  kg-auxl.h
 *  ���� ���� :  ������� �Ӽ����� ������� ���¼Ҹ� ���Ѵ�
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

#ifndef _KG_AUXL_H_
#define _KG_AUXL_H_

#include "kg-node.h"

/*
 *  �ѱ��� ������� �������� �� �׸��� ����
 */
#define MAX_AUXL_LEN          (MAX_STR_LEN/5)

/*
 *  ��������� �ִ� ����
 */
#define MAX_AUXL_CNT             20

/*
 *  ��������� �����ϴµ� �ϳ��� ���ڸ� �ʿ��ϴ�.
 *
 *  1. ������� �Ӽ�
 *     PRGRSS, STATE, DONOT, FORBID, CANNOT, PASSIV, ........
 */
/*
 *  ������� �������� ���������̿� ��������� �������� ����Ѵ�.
 *  �ֳ��ϸ�, Ư���� ������𿡴� Ư���� ������ �����̸��� ���� �����̴�.
 */
/*
 *  �ѱ��� ������� ������ ���� ����
 */
typedef struct casetable_t {
  int  nFeature;                     /* ������� �Ӽ���            */
  int  bTrans;                       /* ���������̰� ���ϴ���..  */
  char szAuxl[MAX_AUXL_LEN];         /* �������                   */
} AUXL_TABLE;                        /* ����������               */

void ReadAuxlTable(char *pszFileName, int bView);
int FindAuxlPhrase(int nFeature);
void GetAuxlPhrase(int nFeature, char *pszPhrase);

#endif

/* ------------------------------------------------------------------------- */

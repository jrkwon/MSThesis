/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :
 *  �Լ�(��)  :  kg-case.h
 *  ���� ���� :  ������ �Ӽ����� ���� ���繮�ڿ��� ���Ѵ�
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

#ifndef _KG_CASE_H_
#define _KG_CASE_H_

#include "kg-node.h"

/*
 *  �ѱ��� ���� ������ ���� �������� �� �׸��� ����
 */
#define MAX_CASE_LEN          (MAX_STR_LEN/5)

/*
 *  �ѱ��� ���� ���� (�ִ� ������ �˳��ϰ� ��Ҵ�)
 */
#define MAX_CASE_CNT             200

/*
 *  ���縦 �����ϴµ� �ʿ��� ���ڴ� ũ�� �ΰ����̴�.
 *
 *  1. ���� �Ӽ�
 *     SUBJ, SUBJ2, OBJ, OBJ2, VOC, PREN, TOPIC, INDEP, .....
 *
 *  2. ��ħ�� �ִ��� �������� ���� ����
 *     �Ϻ� ������� �ձ����� ��ħ�� �ִ��� �������� ����
 *     �� ���°� �ٸ��� (��/��, ��/��, ��/��)
 */

/*
 *  �ѱ��� ���� ������ ���� ����
 */
typedef struct casetable_t {
  int  nFeature;                     /* ���� �Ӽ���                */
  int  nFinal;                       /* ��ħ�䱸 ����(����, ��, ��)*/
  int  bTrans;                       /* ü��� ���簡 ����������.. */
  char szCase[MAX_CASE_LEN];         /* ����                       */
} CASE_TABLE;                        /* ���� ����                  */

void ReadCaseTable(char *pszFileName, int bView);
int FindCasePhrase(int nFeature, int bFinal);
void GetCasePhrase(int nFeature, char *pszPhrase, int bFinal);

#endif

/* ------------------------------------------------------------------------- */
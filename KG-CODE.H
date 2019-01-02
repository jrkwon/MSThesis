/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :
 *  �Լ�(��)  :  kg-code.h
 *  ���� ���� :
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

#ifndef _KG_CODE_H_
#define _KG_CODE_H_

/*
 *  ��� ������ �ʼ�, �߼�, ������ ä�� �ڵ�
 */
enum fillcode_t { FILL_1ST = 1, FILL_MID = 2, FILL_LST = 1 };

/*
 *  TG2KS �Լ��� ���޵Ǵ� ��������� �ڵ尡 �ѱ� ������ ��, �� ������ ����
 *
 *        FULL_CODE   :  ���ڰ� �ƴϴ�.
 *        FIRST_CODE  :  �ʼ����� ����   <-- �� ���� ����� �Ѵ�.
 *        MID_CODE    :  �߼����� ����
 *        LAST_CODE   :  �������� ����
 *        �� ���� �ٲٸ� �ȵ�~~~~
 */
enum codekind_t { FIRST_CODE, MID_CODE, LAST_CODE, FULL_CODE };

int      IsKSsingle(unsigned nKScode);
unsigned TG2KS(unsigned nTGcode, int nKind);
unsigned KS2TG(unsigned nKScode);
unsigned KS2ElementTG(unsigned nKScode, int nKind);
void     SplitHangulCharElement(unsigned nKScode, unsigned *pnKScode1, unsigned *pnKScode2);

#endif

/* ------------------------------------------------------------------------- */

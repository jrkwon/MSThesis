/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-file.h
 *  �Լ�(��)  :
 *  ���� ���� :  ���� ������ ���� ���� ����
 *  ���� ��   :  1993. 09. 25
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

#ifndef _KG_FILE_H_
#define _KG_FILE_H_

/*
 *  �ؼ� ��� ������ �ּ���; �� �߰��� �͵� �ȴ�.
 */
#define IsComment(pszStr)    ((*(pszStr) == '/') && (*((pszStr)+1) == '/'))

/*
 *  ǥ �ڷ� ������ �ּ��� ǥ�� (#); �� �� ���� �տ����� ��ȿ
 */
#define IsTableComment(szStr)   (szStr[0] == '#')


/* ���� �Ӹ� �κ� */
enum { RESULT_HEADER, EEOW_HEADER, NEOW_HEADER, CASE_HEADER, AUXL_HEADER };

extern char *szFileHeader[];

/* ���Ͽ��� ���� ���� ���۳����� ���� ������ */
extern char *pszCurPtr;

int  OpenDataFile(char *pszFileName);
void CloseDataFile(void);
char *ReadLine(void);
int  SkipSpace(void);
char *GetWord(char *pszBuf);
void CheckFileHeader(char *pszFileHeader);

#endif

/* ------------------------------------------------------------------------- */
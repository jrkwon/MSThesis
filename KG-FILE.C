/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-file.c
 *  �Լ�(��)  :
 *  ���� ���� :  ������ ���� ���� ������ ����.
 *  ���� ��   :  1993. 09. 26
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
 *  �� ���� ���� �Լ��� ���ٸ�  �ѹ��� �� ���� ���ϸ��� �ٷ� �� �ִ�.
 *  �ϳ��� ������ �������� ������ �� �ݰ� �ٽ� �ٸ� ������ ����� �Ѵ�.
 */

#include <stdio.h>
#include "kg-node.h"
#include "kg-file.h"
#include "kg-type.h"

/*
 *  �� ���� �ִ� ����
 *  �� �ؼ���� ������ �б� ���� �˳��ϰ� ��Ҵ�.
 */
#define MAX_LINE_LEN        MAX_STR_LEN*4

char *szFileHeader[] = {
  "[�ؼ����]", "[������]", "[��������]", "[����]", "[�������]"
};
char *pszCurPtr;                            /* szLineBuf������ ���� ������ */

static char szLineBuf[MAX_LINE_LEN];          /* ������ �о�鿩 ���� ���� */
static int  bFileOpen;                    /* ������ ���������� ���� �÷��� */
static FILE *pfData;                             /* �ڷ������� ���� ������ */

/*
 *  �Է�   :  ���� �̸�
 *  ���   :  ����(success) �Ǵ� ����(fail)
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ������ �б� �Ӽ����� ����
 */
int OpenDataFile(pszFileName)
char *pszFileName;
{
  if(bFileOpen)
    DispErrorF(true, "(%s) ���� ���� ���� !\n����� ������ ���� �ݾ��ֽʽÿ� [kg-file.c::OpenDataFile]", pszFileName);
  pfData = fopen(pszFileName, "r");
  if(!pfData) {
    fprintf(stderr, "%s : �ڷ� ������ �����ϴ�.\n", pszFileName);
  }
  *(pszCurPtr = szLineBuf) = NULL;
  bFileOpen = true;
  return pfData ? success : fail;
}

/*
 *  �Է�   :  .
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �ڷ� ������ �ݴ´�.
 */
void CloseDataFile()
{
  bFileOpen = false;
  fclose(pfData);
}

/*
 *  �Է�   :  .
 *  ���   :  �о���� ���� ���ڿ� ������
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �ڷ� ���Ͽ��� ������ �о� ���δ�.
 */
char *ReadLine()
{
  *(pszCurPtr = szLineBuf) = NULL;
  return fgets(szLineBuf, MAX_LINE_LEN, pfData);
}


/*
 *  �Է�   :  .
 *  ���   :  �����ϸ� success, ���� ���� �����ϸ� fail
 *  ȣ���� :  ReadLine, IsComment(��ũ��)
 *  ȣ��� :
 *  ��  �� :  ������ �ǳ� �ڴ�, �� ���̶��, ���� ���� �о���̰�
 *            �ű⿡�� �ٽ� ������ �ǳ� �ڴ�.
 */
int SkipSpace()
{
  while( true ) {
    while(IsComment(pszCurPtr)) {
      ReadLine();
    }
#ifdef __TURBOC__
    while(isspace((unsigned char)*pszCurPtr)) {
      ++pszCurPtr;
    }
#else
    while(isspace(*pszCurPtr)) {
      ++pszCurPtr;
    }
#endif
    while(IsComment(pszCurPtr)) {
      ReadLine();
    }
    if(*pszCurPtr != NULL) {
      return success;
    }
    if(ReadLine() == NULL) {
      return fail;
    }
  }
}

/*
 *  �Է�   :  ����� ���� ���ڿ� ������.
 *  ���   :  .
 *  ȣ���� :  SkipSpace
 *  ȣ��� :
 *  ��  �� :  ������ ���ڿ� �����Ϳ��� �� �ܾ �д´�.
 */
char *GetWord(pszBuf)
char *pszBuf;
{
  char *pszTemp;

  pszTemp = pszBuf;
  SkipSpace();
  while (true) {
#ifdef __TURBOC__
    if(isspace((unsigned char)*pszCurPtr) || *pszCurPtr == ')') {
#else
    if(isspace(*pszCurPtr) || *pszCurPtr == ')') {
#endif
      *pszTemp =  NULL;
      SkipSpace();
      return pszBuf;
    }
    *pszTemp++ = *pszCurPtr++;
  }
}

/*
 *  �Է�   :  .
 *  ���   :  .
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  ���� �Ӹ��κ��� �˻� �Ѵ�
 */
void CheckFileHeader(pszFileHeader)
char *pszFileHeader;
{
  if(SkipSpace() == fail)
    DispErrorF(true, "���� �Ӹ��� �־�� �մϴ� (%s)\n", pszFileHeader);
  if(!strncmp(pszCurPtr, pszFileHeader, strlen(pszFileHeader)))
    ReadLine();
  else
    DispErrorF(true, "�߸��� ���� �Ӹ� (%s)�Դϴ�\n", pszFileHeader);
}


/* ------------------------------------------------------------------------- */
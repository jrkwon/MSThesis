/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-main.c
 *  �Լ�(��)  :
 *  ���� ���� :  ������ �� �Լ�
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

#include <stdio.h>
#include "kg-node.h"
#include "kg-type.h"
#include "kg-ftr.h"

#ifndef __LARGE__
#error Complile at large memory model in MS-DOS
#endif

char szEEOWTableFileName[] = "kg-eend.dat";
char szNEOWTableFileName[] = "kg-nend.dat";
char szCaseTableFileName[] = "kg-case.dat";
char szAuxlTableFileName[] = "kg-auxl.dat";

char szTitle[]
 = "The Korean Sentence Generator �ң���-�� (C) 1993 Copyright\n\
Department of Electronic Communication Engineering Hanyang University\n\
Artificial Intellegent Lab. Natural Language Processing Group\n\n\
�ѱ��� ���� ������ ��-2\n\
���۱� 1993 (��) �Ѿ���б� ������Ű��а� �ΰ����ɿ�����\n\n";

char szHelp[] = "���� : kg-rock <�����̸�> [����]\n\n\
  ���� v: �߰����� ����\n\n";

/*
 *  �Է�   :  �ؼ������ ���� ���� �̸�
 *  ���   :
 *  ȣ���� :
 *  ȣ��� :
 *  ��  �� :  �ؼ� ��� ������ �о�鿩 �ѱ��� ������ �Ѵ�.
 */
int main(nArgc, pszArgv)
int   nArgc;
char *pszArgv[];
{
  NODE Node, Sem, *pTempNode;
  char *pszResultFile;
  char szResultStr[MAX_STR_LEN];
  int nArcNum, bView;

  if(nArgc != 2 && nArgc != 3) {
    fprintf(stderr, szTitle);
    fprintf(stderr, szHelp);
    return false;
  }

  fprintf(stderr, szTitle);
  bView = (pszArgv[2][0] == 'v') ? true : false;
  pszResultFile = pszArgv[1];

  ReadEEndOfWordTable(szEEOWTableFileName, bView);
  ReadNEndOfWordTable(szNEOWTableFileName, bView);
  ReadCaseTable(szCaseTableFileName, bView);
  ReadAuxlTable(szAuxlTableFileName, bView);

  szResultStr[0] = NULL;
  ClearNode(&Node);
  ReadResultNode(pszResultFile, &Node, bView);

  ClearNode(&Sem);
  nArcNum = GetArcNumber(&Node, HEAD);
  if(nArcNum == -1)
    DispError("�߸��� ���� �����Դϴ�. [kg-main.c :: main]", true);
  pTempNode = Node.Arc[nArcNum].pNode;

  nArcNum = GetArcNumber(pTempNode, SEM);
  if(nArcNum == -1)
    DispError("�߸��� ���� �����Դϴ�. [kg-main.c :: main]", true);

  NodeCopy(&Sem, pTempNode->Arc[nArcNum].pNode);

  SortSemNode(&Sem);
  GenerateKoreanSentence(&Sem, &Node, szResultStr, bView);

  printf("\n\n�� �ѱ��� ��������Դϴ�.");
  printf("\n\n%s\n", szResultStr);
  return true;
}

/* ------------------------------------------------------------------------- */

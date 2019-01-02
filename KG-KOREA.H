/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-korea.h
 *  함수(들)  :
 *  파일 설명 :
 *  만든 날   :  1993. 09. 17
 *  만든 이   :  권 재 락
 *
 *  저작권 (C) 1993 한양대학교 전자통신공학과 대학원 인공지능연구실
 *  이 프로그램에 대한 모든 권리는 저작권자가 가집니다.
 *
 *
 *  [+] 헝가리식 표기법
 *  -----------------------------------------------------
 *   접두어     뜻
 *  -----------------------------------------------------
 *   c          char
 *   by         unsigned char (BYTE)
 *   n          short int or int
 *   x          short int (그래픽 좌표 x좌표)
 *   y          short int (그래픽 좌표 y좌표)
 *   i          int
 *   b          int (BOOL)
 *   w          unsigned int (WORD)
 *   h          unsigned int (WORD) (HANDLE)
 *   dw         unsigned long int (DWORD)
 *   fn         Function (함수 포인터)
 *   s          Character Array (NULL로 끝날 필요 없다)
 *   sz         Character String (NULL로 끝난다)
 *  -----------------------------------------------------
 *
 */

#ifndef _KG_KOREA_H_
#define _KG_KOREA_H_

#define  MAX_PATH_STACK_DEPTH   25
#define  MAX_PATH_STACK_CNT     25

void InitPathStack(void);
void SortSemNode(NODE *pNode);
void GetPathStackAndPhrase(ARC *pArc, char **ppszPhrase);
NODE *GetNodePtr4List(NODE *pNode, int *pnList);
char *GetTenseMorph(char *pszStr);
void GetPrefixPhrase(NODE *pSyn, char *pszPhrase);
int GetPreEowPhrase(NODE *pSyn, char *pszPhrase);
void GenerateAuxlPhrase(NODE *pSyn, char *pszPhrase);
void GeneratePredPhrase(NODE *pSyn, char *pszPhrase);
void GenerateRefPhrase(NODE *pSyn, char *pszPhrase, int nCase);
void GenerateKoreanPhrase(int *pnPathStack, NODE *pRootNode, char *pszPhrase, char *pszResultStr);
void GenerateKoreanSentence(NODE *pSemNode, NODE *pRootNode, char *pszResultStr);

#endif

/* ------------------------------------------------------------------------- */

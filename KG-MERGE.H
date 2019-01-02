/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-merge.h
 *  함수(들)  :
 *  파일 설명 :  어간과 어미(또는 체언과 조사)의 결합에서 나타나는 음운현상 처리
 *  만든 날   :  1993. 10. 04
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

#ifndef _KG_MERGE_H_
#define _KG_MERGE_H_

char *GetFirstHanCharElement(char *pszChar);
char *FallFirstHanCharElement(char *pszChar);
char *GetMidHanCharElement(char *pszChar);
char *FallMidHanCharElement(char *pszChar);
char *GetLastHanCharElement(char *pszChar);
char *FallLastHanCharElement(char *pszChar);
void EUinsert(char *pszChar1, char *pszChar2, char *pszInsBuf);
void EUfalling(char *pszChar1, char *pszChar2);
void Rfalling(char *pszChar1, char *pszChar2);
void VocalHarmony(char *pszChar1, char *pszChar2);
void SoundShrink(char *pszChar1, char *pszChar2, char *pszInsBuf);
char *MakeHanChar(char *pszChar, char *pszEle, int nEle);
void MergeHangulChar(char *pszChar1, char *pszChar2, char *pszInsBuf);
char *MergeHangulStr(char *pszStr1, char *pszStr2/*, int nIrregular*/);

#endif

/* ------------------------------------------------------------------------- */


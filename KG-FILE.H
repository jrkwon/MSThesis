/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-file.h
 *  함수(들)  :
 *  파일 설명 :  사전 따위를 위한 파일 관리
 *  만든 날   :  1993. 09. 25
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

#ifndef _KG_FILE_H_
#define _KG_FILE_H_

/*
 *  해석 결과 파일의 주석문; 줄 중간에 와도 된다.
 */
#define IsComment(pszStr)    ((*(pszStr) == '/') && (*((pszStr)+1) == '/'))

/*
 *  표 자료 파일의 주석문 표식 (#); 그 줄 제일 앞에서만 유효
 */
#define IsTableComment(szStr)   (szStr[0] == '#')


/* 파일 머리 부분 */
enum { RESULT_HEADER, EEOW_HEADER, NEOW_HEADER, CASE_HEADER, AUXL_HEADER };

extern char *szFileHeader[];

/* 파일에서 읽은 한줄 버퍼내에서 현재 포인터 */
extern char *pszCurPtr;

int  OpenDataFile(char *pszFileName);
void CloseDataFile(void);
char *ReadLine(void);
int  SkipSpace(void);
char *GetWord(char *pszBuf);
void CheckFileHeader(char *pszFileHeader);

#endif

/* ------------------------------------------------------------------------- */

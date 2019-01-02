/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :
 *  함수(들)  :  kg-case.h
 *  파일 설명 :  조사의 속성에서 실제 조사문자열을 구한다
 *  만든 날   :  1993. 10. 01
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

#ifndef _KG_CASE_H_
#define _KG_CASE_H_

#include "kg-node.h"

/*
 *  한국어 조사 생성을 위한 사전에서 한 항목의 길이
 */
#define MAX_CASE_LEN          (MAX_STR_LEN/5)

/*
 *  한국어 조사 갯수 (최대 갯수는 넉넉하게 잡았다)
 */
#define MAX_CASE_CNT             200

/*
 *  조사를 결정하는데 필요한 인자는 크게 두가지이다.
 *
 *  1. 조사 속성
 *     SUBJ, SUBJ2, OBJ, OBJ2, VOC, PREN, TOPIC, INDEP, .....
 *
 *  2. 받침이 있는지 없는지에 대한 정보
 *     일부 조사들은 앞글자의 받침이 있는지 없는지에 따라서
 *     그 형태가 다르다 (이/가, 을/를, 은/는)
 */

/*
 *  한국어 조사 생성용 사전 구조
 */
typedef struct casetable_t {
  int  nFeature;                     /* 조사 속성값                */
  int  nFinal;                       /* 받침요구 형태(무관, 유, 무)*/
  int  bTrans;                       /* 체언과 조사가 합쳐지는지.. */
  char szCase[MAX_CASE_LEN];         /* 조사                       */
} CASE_TABLE;                        /* 조사 사전                  */

void ReadCaseTable(char *pszFileName, int bView);
int FindCasePhrase(int nFeature, int bFinal);
void GetCasePhrase(int nFeature, char *pszPhrase, int bFinal);

#endif

/* ------------------------------------------------------------------------- */

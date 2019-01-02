/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :
 *  함수(들)  :  kg-auxl.h
 *  파일 설명 :  보조용언 속성으로 보조용언 형태소를 구한다
 *  만든 날   :  1993. 10. 02
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

#ifndef _KG_AUXL_H_
#define _KG_AUXL_H_

#include "kg-node.h"

/*
 *  한국어 보조용언 사전에서 한 항목의 길이
 */
#define MAX_AUXL_LEN          (MAX_STR_LEN/5)

/*
 *  보조용언의 최대 갯수
 */
#define MAX_AUXL_CNT             20

/*
 *  보조용언을 결정하는데 하나의 인자만 필요하다.
 *
 *  1. 보조용언 속성
 *     PRGRSS, STATE, DONOT, FORBID, CANNOT, PASSIV, ........
 */
/*
 *  보조용언 사전에는 보조연결어미와 보조용언의 통합형을 등록한다.
 *  왜냐하면, 특정한 보조용언에는 특정한 보조적 연결어미만이 오기 때문이다.
 */
/*
 *  한국어 보조용언 생성용 사전 구조
 */
typedef struct casetable_t {
  int  nFeature;                     /* 보조용언 속성값            */
  int  bTrans;                       /* 보조연결어미가 변하는지..  */
  char szAuxl[MAX_AUXL_LEN];         /* 보조용언                   */
} AUXL_TABLE;                        /* 보조용언사전               */

void ReadAuxlTable(char *pszFileName, int bView);
int FindAuxlPhrase(int nFeature);
void GetAuxlPhrase(int nFeature, char *pszPhrase);

#endif

/* ------------------------------------------------------------------------- */


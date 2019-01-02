/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-nend.h
 *  함수(들)  :
 *  파일 설명 :  한국어 비종결어미 생성을 위한 사전 관리
 *  만든 날   :  1993. 09. 28
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

#ifndef _KG_NEOW_H_
#define _KG_NEOW_H_

#include "kg-node.h"

/*
 *  한국어 비종결어미 생성을 위한 사전에서 한 항목의 길이
 */
#define MAX_NFIELD_LEN          (MAX_STR_LEN/5)

/*
 *  한국어 비종결어미의 갯수 (최대 갯수는 넉넉하게 잡았다)
 */
#define MAX_NEOW_CNT             200

/*
 *  비종결어미를 결정하는데 필요한 인자는 크게 두가지이다.
 *
 *  1. 비종결어미 속성
 *     단순 나열, 순차 나열, 결과 나열, .... 이유, 원인, ...목적, 필요...
 *
 *  2. 시제
 *     시제 정보는 어미결합제약 정보와 함께 시제에 대응하는 선어말어미를
 *     붙여주어야 하는지를 결정한다.
 *     한국어를 해석한 결과라면 당연히 시제선어말어미와 결합제약이 있는
 *     어미에는 시제선어말어미가 붙지 않겠지만, 영어 따위의 기타 외국어
 *     를 해석한 결과라면, 이 시제정보가 살아있을 수도 있다
 *     따라서, 비종결어미 생성에서 어미결합제약 정보는 중요하다.
 *     [어미 결합제약]
 *     -었-, -겠-, -더-
 *     위의 시제어미가 이 비종결어미와 결합가능한지에 대한 정보
 */

/*
 *  한국어 비종결어미 생성용 사전 구조
 */
typedef struct eowtable_t {
  int  nFeature;                     /* 비종결어미 속성값          */
  int  nEOT;                         /* 었                         */
  int  nGET;                         /* 겠                         */
  int  nDEO;                         /* 더                         */
  int  bTrans;                       /* 어미자체가 변하는가        */
  char szNEndOfWord[MAX_NFIELD_LEN]; /* 비종결어미                 */
} NEOW_TABLE;                        /* Non End Of Word Table      */

void ReadNEndOfWordTable(char *pszFileName, int bView);
int FindNEowPhrase(int nFeature);
void GetNEowPhrase(int nFeature, char *pszPhrase, int nTense);

#endif

/* ------------------------------------------------------------------------- */

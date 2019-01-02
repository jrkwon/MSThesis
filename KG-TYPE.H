/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-type.h
 *  함수(들)  :
 *  파일 설명 :
 *  만든 날   :  1993. 09. 15
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

#ifndef _KG_TYPE_H_
#define _KG_TYPE_H_

#ifndef true
#define true    1
#define false   0
#endif

#ifndef on
#define on      1
#define off     0
#endif

#ifndef success
#define success 1
#define fail    0
#endif

#endif

/* ----------------------------------------------------------------------- */
/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :
 *  함수(들)  :  kg-code.h
 *  파일 설명 :
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

#ifndef _KG_CODE_H_
#define _KG_CODE_H_

/*
 *  상용 조합형 초성, 중성, 종성의 채움 코드
 */
enum fillcode_t { FILL_1ST = 1, FILL_MID = 2, FILL_LST = 1 };

/*
 *  TG2KS 함수로 전달되는 상용조합형 코드가 한글 낱자일 때, 그 낱자의 종류
 *
 *        FULL_CODE   :  낱자가 아니다.
 *        FIRST_CODE  :  초성만이 전달   <-- 이 경우는 없어야 한다.
 *        MID_CODE    :  중성만이 전달
 *        LAST_CODE   :  종성만이 전달
 *        ※ 순서 바꾸면 안돼~~~~
 */
enum codekind_t { FIRST_CODE, MID_CODE, LAST_CODE, FULL_CODE };

int      IsKSsingle(unsigned nKScode);
unsigned TG2KS(unsigned nTGcode, int nKind);
unsigned KS2TG(unsigned nKScode);
unsigned KS2ElementTG(unsigned nKScode, int nKind);
void     SplitHangulCharElement(unsigned nKScode, unsigned *pnKScode1, unsigned *pnKScode2);

#endif

/* ------------------------------------------------------------------------- */


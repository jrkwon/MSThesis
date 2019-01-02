/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-merge.c
 *  함수(들)  :
 *  파일 설명 :  어간과 어미(또는 체언과 조사) 결합 때의 음운현상
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

#include <string.h>
#include "kg-merge.h"
#include "kg-node.h"
#include "kg-code.h"
#include "kg-type.h"

/*
void (*fnIrregular[])(char *pszStr1, char *pszStr2) = {
  Sirregular, Dirregular, Birregular, REUirregular, Uirregular,
  YEOirregular, GEOirregular, NEOirregular, REOirregular, Hirregular
};
*/

static char szChar[3];

/*
 * 코드변환하는 횟수를 줄이기보다는, 프로그램 인터페이스를
 * 쉽게할 수 있게 하기 위해 필요할 때마다 코드변환을 한다.
 */
/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *GetFirstHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast;
/*  char szChar[3]; */

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = FILL_MID;
  nLast  = FILL_LST;
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, FIRST_CODE);
  szChar[0] = (nKScode >> 8) & 0x00ff;
  szChar[1] = (nKScode & 0x00ff);
  szChar[2] = NULL;
  return szChar;
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *FallFirstHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast, nKind;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = FILL_1ST;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = (nTGcode & 0x1f);
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKind = FULL_CODE;
  if(nMid == FILL_MID)
    nKind = LAST_CODE;
  else if(nLast == FILL_LST)
    nKind = MID_CODE;
  nKScode = TG2KS(nTGcode, nKind);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *GetMidHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast;
/*  char szChar[3]; */

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = FILL_1ST;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = FILL_LST;
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, MID_CODE);
  szChar[0] = (nKScode >> 8) & 0x00ff;
  szChar[1] = (nKScode & 0x00ff);
  szChar[2] = NULL;
  return szChar;
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *FallMidHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast, nKind;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = FILL_MID;
  nLast  = (nTGcode & 0x1f);
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKind = FULL_CODE;
  if(nFirst == FILL_1ST)
    nKind = LAST_CODE;
  else if(nLast == FILL_LST)
    nKind = FIRST_CODE;
  nKScode = TG2KS(nTGcode, nKind);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *GetLastHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast;
/*  char szChar[3]; */

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = FILL_1ST;
  nMid   = FILL_MID;
  nLast  = (nTGcode & 0x1f);
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, LAST_CODE);
  szChar[0] = (nKScode >> 8) & 0x00ff;
  szChar[1] = (nKScode & 0x00ff);
  szChar[2] = NULL;
  return szChar;
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *FallLastHanCharElement(pszChar)
char *pszChar;
{
  unsigned nTGcode, nKScode;
  int nFirst, nMid, nLast, nKind;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = FILL_LST;
  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKind = FULL_CODE;
  if(nFirst == FILL_1ST)
    nKind = MID_CODE;
  else if(nMid == FILL_MID)
    nKind = FIRST_CODE;
  nKScode = TG2KS(nTGcode, nKind);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
void EUinsert(pszChar1, pszChar2, pszInsBuf)
char *pszChar1;
char *pszChar2;
char *pszInsBuf;
{
  static char *pszHanEle[] = { "ㄴ", "ㄹ", "ㅂ", "ㅗ", "ㅁ", "", "오", "시" };
  char *pszTemp;
  unsigned nEleCode;
  int nCnt;

  if(strcmp(GetLastHanCharElement(pszChar1), "ㄹ")) {
    nEleCode = (pszChar2[0] << 8);
    nEleCode |= (pszChar2[1]) & 0x00ff;
    if(!strcmp("오", pszChar2) || !strcmp("시", pszChar2)) {
      strcpy(pszInsBuf, "으");
      return;
    }
    if(!IsKSsingle(nEleCode))
      return;

    pszTemp = (char *)GetFirstHanCharElement(pszChar2);
    for(nCnt = 0; pszHanEle[nCnt][0]; nCnt++) {
      if(!strcmp(pszTemp, pszHanEle[nCnt])) {
        strcpy(pszInsBuf, "으");
        return;
      }
    }
  }
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
void EUfalling(pszChar1, pszChar2)
char *pszChar1;
char *pszChar2;
{
  if(!strcmp(GetMidHanCharElement(pszChar1), "ㅡ")) {
    if(!strcmp(GetMidHanCharElement(pszChar2), "아")) {
      FallMidHanCharElement(pszChar1);
    }
  }
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
void Rfalling(pszChar1, pszChar2)
char *pszChar1;
char *pszChar2;
{
  static char *pszHanEle[] = { "ㄴ", "ㅂ", "ㅅ", "오", "" };
  int nCnt;

  if(!strcmp(GetLastHanCharElement(pszChar1), "ㄹ")) {
    for(nCnt = 0; pszHanEle[nCnt][0]; nCnt++) {
      if(!strcmp(GetFirstHanCharElement(pszChar2), pszHanEle[nCnt])) {
        FallLastHanCharElement(pszChar1);
      }
    }
  }
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
void VocalHarmony(pszChar1, pszChar2)
char *pszChar1;
char *pszChar2;
{
  static char *pszNegaNeu[] = {
    "ㅓ", "ㅔ", "ㅕ", "ㅖ", "ㅚ", "ㅜ", "ㅝ",
    "ㅞ", "ㅟ", "ㅠ", "ㅡ", "ㅢ", "ㅣ", ""
  };
  static char *pszTmp;
  int nCnt;

  if(!strcmp(pszChar2, "아")) {
    pszTmp = GetMidHanCharElement(pszChar1);
    for(nCnt = 0; pszNegaNeu[nCnt][0]; nCnt++) {
      if(!strcmp(pszTmp, pszNegaNeu[nCnt])) {
        strncpy(pszChar2, "어", 2);
        return;
      }
    }
  }
  else if(!strcmp(pszChar2, "았")) {
    pszTmp = GetMidHanCharElement(pszChar1);
    for(nCnt = 0; pszNegaNeu[nCnt][0]; nCnt++) {
      if(!strcmp(pszTmp, pszNegaNeu[nCnt])) {
        strncpy(pszChar2, "었", 2);
        return;
      }
    }
  }
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
void SoundShrink(pszChar1, pszChar2, pszInsBuf)
char *pszChar1;
char *pszChar2;
char *pszInsBuf;
{
  char *pszTmp;

  pszTmp = (pszInsBuf[0] == NULL) ? pszChar2 : pszInsBuf;
  if(!strcmp(GetLastHanCharElement(pszChar1), "")) {
    if(!strcmp(GetMidHanCharElement(pszChar1), "ㅗ")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "ㅏ")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "ㅚ", MID_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
   else if(!strcmp(GetMidHanCharElement(pszChar1), "ㅚ")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "ㅓ")) {
        MakeHanChar(pszChar1, "ㅙ", MID_CODE);
        MakeHanChar(pszChar1, GetLastHanCharElement(pszTmp), LAST_CODE);
        pszTmp[0] = NULL;
      }
    }
    else if(!strcmp(GetMidHanCharElement(pszChar1), "ㅜ")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "ㅓ")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "ㅝ", MID_CODE);
        MakeHanChar(pszTmp, pszChar1, FIRST_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
    else if(!strcmp(GetMidHanCharElement(pszChar1), "ㅣ")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "ㅓ")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "ㅕ", MID_CODE);
        MakeHanChar(pszTmp, pszChar1, FIRST_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
    else if(!strcmp(GetMidHanCharElement(pszChar1), "ㅜ")) {
      if(!strcmp(GetMidHanCharElement(pszTmp), "ㅡ")) {
        FallMidHanCharElement(pszChar1);
        MakeHanChar(pszTmp, "ㅜ", MID_CODE);
        strncpy(pszChar1, pszTmp, 2);
        pszTmp[0] = NULL;
      }
    }
  }
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *MakeHanChar(pszChar, pszEle, nKind)
char *pszChar;
char *pszEle;
int  nKind;
{
  unsigned nTGcode, nKScode, nEleCode;
  int nFirst, nMid, nLast, nTmp;

  nKScode = (pszChar[0] << 8);
  nKScode |= (pszChar[1]) & 0x00ff;
  nTGcode = KS2TG(nKScode);
  nFirst = (nTGcode >> 10) & 0x1f;
  nMid   = (nTGcode >> 5) & 0x1f;
  nLast  = (nTGcode & 0x1f);
  nEleCode = (pszEle[0] << 8);
  nEleCode |= (pszEle[1]) & 0x00ff;
  if(IsKSsingle(nEleCode)) {
    nTmp = KS2ElementTG(nEleCode, nKind);
  }
  else {
    nTmp = KS2TG(nEleCode);
  }

  if(nKind == FIRST_CODE) {
    nFirst = (nTmp >> 10) & 0x1f;
  }
  else if(nKind == MID_CODE) {
    nMid   = (nTmp >> 5) & 0x1f;
  }
  else if(nKind == LAST_CODE) {
    nLast  = (nTmp & 0x1f);
  }

  nTGcode = 0x8000 + (nFirst << 10) + (nMid << 5) + nLast;
  nKScode = TG2KS(nTGcode, FULL_CODE);
  pszChar[0] = (nKScode >> 8) & 0x00ff;
  pszChar[1] = (nKScode & 0x00ff);
  pszChar[2] = NULL;
  return pszChar;
}

/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
void MergeHangulChar(pszChar1, pszChar2, pszInsBuf)
char *pszChar1;
char *pszChar2;
char *pszInsBuf;
{
  char *pszTmp, *pszLast;

  pszTmp = (pszInsBuf[0] == NULL) ? pszChar2 : pszInsBuf;
  if(!strcmp(GetLastHanCharElement(pszChar1), "")) {
    if(!strcmp(GetFirstHanCharElement(pszTmp), "ㅇ")
       || !strcmp(GetFirstHanCharElement(pszTmp), "")) {
      MakeHanChar(pszChar1, pszTmp, LAST_CODE);
      pszTmp[0] = NULL;
    }
    else {
      pszLast = GetLastHanCharElement(pszTmp);
      MakeHanChar(pszChar1, pszLast, LAST_CODE);
      pszTmp[0] = NULL;
    }
  }
}

/*
 *  체언과 조사를 붙이는데 쓸란다.
 */
/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *AttachHangulStr(pszStr1, pszStr2)
char *pszStr1;
char *pszStr2;
{
  char szBuf1[3], szBuf2[3], szStr1[MAX_STR_LEN], szStr2[MAX_STR_LEN];
  char szResult[MAX_STR_LEN], szInsBuf[MAX_STR_LEN];
  unsigned nKScode, nTGcode;
  int nLen;

  strcpy(szStr1, pszStr1);
  strcpy(szStr2, pszStr2);

  szInsBuf[0] = NULL;
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szBuf1[0] = szStr1[nLen-2], szBuf1[1] = szStr1[nLen-1], szBuf1[2] = NULL;
  szBuf2[0] = szStr2[0], szBuf2[1] = szStr2[1], szBuf2[2] = NULL;

  EUinsert(szBuf1, szBuf2, szInsBuf);       /* ① '으'삽입      */
  MergeHangulChar(szBuf1, szBuf2, szInsBuf);/* ⑦ 자소합성      */

  sprintf(szResult, "%s%s%s", szBuf1, szInsBuf, szBuf2);
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szStr1[nLen-2] = NULL;
  strcat(szStr1, szResult);
  strcat(szStr1, szStr2+2);
  strcpy(pszStr1, szStr1);
  return pszStr1;
}

/*
 *  용언의 어간과 어미를 적당하게(?) 붙여주는 알고리즘 Ver 1.00
 *                   * 사전에 표시한 어미변경 플래그가 참일 때
 *
 *  ※ 처리도중에 삽입되는 모음이나 불규칙 활용 결과로 생기는 별도의
 *     자소들은 따로 szInsBuf변수에 저장하고
 *     이 변수에 글자가 들어있다면, 어미부분을 대신하게 하고 처리한다.
 * 1. '으'삽입
 *    어간말음이 'ㄹ'이외의 받침을 갖고,
 *    어미시작이 'ㄴ,ㄹ,ㅂ,오,시,ㅁ'(어미가 완전한 글자가 아닌 한 자소라면
 *    받침이라도 무관)이면, 모음 '으'삽입
 * 2. '으'탈락
 *    어간이 'ㅡ'로 끝나고 '-아'로 시작하는 어미앞에서 'ㅡ'탈락
 * 3. 'ㄹ'탈락
 *    어간말음의 받침이 'ㄹ'이고, 어미시작이 'ㄴ,ㅂ,ㅅ,오'일 때 'ㄹ'탈락
 * 4. 모음조화
 *    문자열2가 '아'로 시작하고,
 *    ('-아/-어' 두가지 형태가 가능한 것은 사전에 '-아'만 기술한다)
 *     문자열1의 가운데 소리가 음성모음, 중성모음이면
 *    '아' -> '어'로 바꿔준다.
 * 5. 불규칙 활용처리
 *    ① ㅅ불규칙 : '-아', '-으' 앞에서 'ㅅ'탈락
 *    ② ㄷ불규칙 : '-아', '-으' 앞에서 'ㄷ'이 'ㄹ'로
 *    ③ ㅂ불규칙 : '-아', '-으' 앞에서 'ㅂ'이 '오/우'
 *                  ※ 중성모음은 음성모음과 가까운가봐... (돕+니 -> 도우니)
 *    ④ 르불규칙 : '-아', '-으' 앞에서 어간말음에서 'ㅡ'가 탈락하고
 *                 어간 끝에서 두번째 글자의 받침으로 'ㄹ'이 첨가
 *                 (흐르 + 아 -> 흘ㄹ + 아 -> 흘러)
 *    ⑤ 우불규칙 : '-아', '-으' 앞에서 'ㅜ'탈락 ('푸다'하나 뿐)
 *    ⑥ 여불규칙 : '-아' 앞에서 어미가 '-여'로 바뀐다.
 *                 ('하다'동사)
 *    ⑦ 거라불규칙 : 어미가 '-아라'에서 '거라'로 바뀜
 *    ⑧ 너라불규칙 : 어미가 '-아라'에서 '너라'로 바뀜
 *                ※ 거라, 너라 불규칙만이 어미형태소 전체가 필요하다..
 *                   시작부분에서 검사해야 한다.
 *    ⑨ 러불규칙 : 어미 '아'가 '러'로 바뀜
 *                  (이르다, 누르다, 푸르다 뿐)
 *    ⑩ ㅎ불규칙 :
 *       ㉠ 어간말음의 받침 'ㅎ'이 탈락
 *          초성이 자음('ㅇ'은 음가가 없으므로 빼고)으로 시작
 *          (파랗 + ㄴ -> 파란)
 *       ㉡ 어간과 어미가 모두 변한다.
 *          초성이 모음 또는 음가없는 'ㅇ'이면
 *          어간말음의 받침 'ㅎ'탈락하고 (파랗 -> 파라)
 *          어간말음의 모음이 '아' -> 애'로 바뀌고, 어미의 첫음이 탈락한다.
 *          (파랗 + 아서 -> 파래서)
 * 6. 모음축약
 *    문자열1이 모음으로 끝나고(중성이 있고, 종성은 FILL CODE)
 *    문자열2가 모음으로 시작하면(초성이 'ㅇ'또는 FILL CODE)
 * 7. 자소합성
 *    (5.와는 배타적) 두개의 글자를 합성한다. (축약과는 다른 의미)
 *    자 + 습니다 -> 잡니다 (∵ '-습니다'만을 사전에 등록했기 때문)
 */
/*
 *  입력   :
 *  출력   :
 *  호출함 :
 *  호출됨 :
 *  설  명 :
 */
char *MergeHangulStr(pszStr1, pszStr2/*, nIrregular*/)
char *pszStr1;
char *pszStr2;
/* int  nIrregular; */
{
  char szBuf1[3], szBuf2[3], szStr1[MAX_STR_LEN], szStr2[MAX_STR_LEN];
  char szResult[MAX_STR_LEN], szInsBuf[MAX_STR_LEN];
  unsigned nKScode, nTGcode;
  int nLen;

  if(pszStr2[0] == NULL)
    return pszStr1;
  strcpy(szStr1, pszStr1);
  strcpy(szStr2, pszStr2);

  szInsBuf[0] = NULL;
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szBuf1[0] = szStr1[nLen-2], szBuf1[1] = szStr1[nLen-1], szBuf1[2] = NULL;
  szBuf2[0] = szStr2[0], szBuf2[1] = szStr2[1], szBuf2[2] = NULL;

  EUinsert(szBuf1, szBuf2, szInsBuf);       /* ① '으'삽입      */
  EUfalling(szBuf1, szBuf2);                /* ② '으'탈락      */
  Rfalling(szBuf1, szBuf2);                 /* ③ 'ㄹ'탈락      */
  VocalHarmony(szBuf1, szBuf2);             /* ④ 모음조화      */
/*fnIrregular[nIrregular](szBuf1, szBuf2);*//* ⑤ 불규칙 처리   */
  SoundShrink(szBuf1, szBuf2, szInsBuf);    /* ⑥ 모음축약      */
  MergeHangulChar(szBuf1, szBuf2, szInsBuf);/* ⑦ 자소합성      */

  sprintf(szResult, "%s%s%s", szBuf1, szInsBuf, szBuf2);
  nLen = strlen(szStr1);
  if(nLen < 2)
    return false;
  szStr1[nLen-2] = NULL;
  strcat(szStr1, szResult);
  if(strlen(szStr2) >= 2)
    strcat(szStr1, szStr2+2);
  strcpy(pszStr1, szStr1);
  return pszStr1;
}

/* ------------------------------------------------------------------------- */

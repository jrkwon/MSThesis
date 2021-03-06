/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-eend.h
 *  함수(들)  :
 *  파일 설명 :  한국어 종결어미 생성을 위한 사전 관리
 *  만든 날   :  1993. 09. 23
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

#ifndef _KG_EEOW_H_
#define _KG_EEOW_H_

#include "kg-node.h"

/*
 *  한국어 종결어미 생성을 위한 사전에서 한 항목의 길이
 */
#define MAX_EFIELD_LEN          (MAX_STR_LEN/5)

/*
 *  한국어 종결어미의 갯수 (최대 갯수는 넉넉하게 잡았다)
 *
 *  높임(6가지), 법(동사 (3+4(시제 x))가지, 형용사 3가지, 지정사 3가지), 시제(2가지)
 *  (6 x 3) x 2 + (6 x 3) x 2 + (6 x 3) x 2 + 6 x 4 = 156
 */
#define MAX_EEOW_CNT             200

/*
 *  종결어미를 결정하는데는 크게 네개의 인자가 있다.
 *
 *  1. 품사 비슷한 거... 뭐라고 할까....
 *     형용사속성인 경우, 지정사속성인 경우, 이 둘모두가 아닌 경우가 있다.
 *     형용사와 동사 또는 지정사(시스템에서는 품사로 설정하지 않았다)등의
 *     [품사]로 하지 않은 이유는 다음과 같은 경우 때문이다.
 *     '먹-' + (HOPE +) = '먹고 싶-'
 *     '먹다'는 동사이지만 '-고 싶'이 붙고 나면, 형용사('싶다'는 보조형용사)
 *     로 활용하게 된다. 이 경우, 품사를 [동사 → 형용사]로 하는 것은
 *     별로 바람직하지 않은 것 같아(왜 그런진 나도 몰라, 그냥... 속성값을
 *     바꾼다는 것이 단일화 개념에 합당하지 않은 거 같아서 말이지)
 *
 *  2. 시제...
 *     현재와 현재 아닌 것으로 나눈다.
 *     이렇게 하는 이유는, 현재 아닌 경우(과거, 미래)에는
 *     시제 선어말어미가 붙고, 여기에 종결어미가 붙게되는데
 *     이때의 종결어미는 딱 하나로 결정된다.
 *     하지만, 현재의 경우에는 좀 문제가 복잡해 진다.
 *     예를 들어, (ADJNAT -) && (COPULA -) ; 동사속성 && 지정사속성
 *     이고, 현재시제에 평서형, 상대높임이라면, 종결어미는
 *     '-ㄴ다', '-는다' 둘중에 하나다.
 *     먹 + -는다 = 먹는다
 *     자 + -ㄴ다 = 잔다
 *     살 + -ㄴ다 = 산다   ('살-'에서 어간 말음 '-ㄹ'이 탈락하고, '-ㄴ다'가 붙는다)
 *     ※ 일반적으로 미래 시제를 나타내는 선어말어미를 '-겠-'으로 보는데
 *        나는 여기에 동의 할 수 없다.
 *        실제로 한국어에는 미래시제를 명시적으로 나타내는 형태소는 존재하지
 *        않는다(서정수 : 국어문법의 연구)는 입장에 동의하며
 *        굳이 미래시제 형태소를 지적한다면 '-ㄹ 것이다'를 택하는 쪽이 더
 *        합리적이다.
 *        '-겠-'의 경우 추측 또는 의지를 나타내는 통사정보로 본다.
 *
 *  3. 법 (Mood)
 *     평서법, 의문법, 감탄법
 *     명령법, 허락법, 약속법, 청유법   (이 네가지는 동사, 현재에만 존재)
 *
 *  4. 상대높임
 *     [해라, 해, 하게, 하오, 해요, 합니다] 의 6단계로 이루어진다.
 *     크게 나눈다면, [해라, 해, 하게]가 낮춤말이고 [하오, 해요, 합니다]가 높임말이다.
 *     오른쪽으로 갈수록 높임의 정도가 높아진다.
 *     해라       : 아주 낮춤
 *     해         : 두루 낮춤
 *     하게       : 예사 낮춤
 *     하오       : 예사 높임
 *     해         : 두루 높임
 *     합니다     : 아주 높임
 *     ※ '하옵니다'는 현대어에는 거의 쓰이지 않으므로 논외로 한다.
 */

/*
 *  한국어 종결어미 생성용 사전 구조
 */
typedef struct eowtable_t {
  int  nCat;                         /* (ADJCNT +), (COPULA +), () */
  int  nTense;                       /* 현재, 현재 아닌 것         */
  int  nMood;                        /* 법 (평서, 의문, 감탄...)   */
  int  nHonor;                       /* 상대높임(해라, 해, 하게..) */
  int  bTrans;                       /* 어미자체가 변하는가        */
  char szEEndOfWord[MAX_EFIELD_LEN]; /* 종결어미                   */
} EEOW_TABLE;                        /* End End Of Word Table      */

void ReadEEndOfWordTable(char *pszFileName, int bView);
int  FindEEowPhrase(int nCat, int nTense, int nMood, int nHonor);
void GetEEowPhrase(NODE *pSyn, char *pszPhrase, int nMood);

#endif

/* ------------------------------------------------------------------------- */

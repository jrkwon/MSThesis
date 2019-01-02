/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-node.h
 *  함수(들)  :
 *  파일 설명 :  속성구조를 나타내는 자료구조
 *  만든 날   :  1993. 09. 13 ~ 14
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

#ifndef _KG_NODE_H_
#define _KG_NODE_H_

/*
 *  속성구조를 나타내는 자료 구조 1.00 판
 *
 *  뿌리 마디 (root node)
 *    1   2   3   4               MAXARC
 *  +-------------------......-------+
 *  |   |   |   |   |            |   |
 *  +-------------------......-------+
 *    |   |   |   |            |   |
 *    v   v   v   v     .....  v   v
 *
 *   속성값(MAXFVALUE만큼의 갯수를 가질 수 있다. 이들 사이에
 *   AND, OR, NONE의 관계가 있을 수 있다),또는
 *   root node와 똑같은 구조의 마디
 *
 *   ( (POS     "그가 학생임을 이제야 알았습니다")
 *     (HEAD    (SYN    (TENSE  PAST)
 *               .....
 *              )
 *              (SEM    (PRED   "알다")
 *                      (SUBJ   "그")
 *                      .....
 *              )
 *      ....
 *    )
 *
 *  POS 의 속성값은 "그가...알았습니다"라는 문자열이고,
 *  HEAD 의 속성값은 SYN, SEM등이 들어있는 또 다른 마디구조이다.
 */

/*
 *  마디 구조에서 상수값 정의
 */
#define MAX_ARC_CNT     8       /* 한 노드당 최대 가지 수              */
#define MAX_FVALUE_CNT  5       /* 최대 갯수의 속성값                  */

/*
 *  내부에서 다룰 문자열의 최대 길이
 */
#define MAX_STR_LEN   250

/*
 *  속성값 사이의 관계
 */
#define NONE_REL        0       /* 관계 없음                            */
#define AND_REL         1       /* AND 관계                             */
#define OR_REL          2       /* OR 관계                              */

/*
 *  속성값 구조체
 */
typedef struct value_t {
  int  nRelation;               /* 관계 (NONE, AND, OR)                 */
  char *pszStr[MAX_FVALUE_CNT]; /* 메모리 할당 후 문자열을 저장         */
  char *pszPtr[MAX_FVALUE_CNT]; /* 다른 문자열의 포인터를 가리킴        */
} VALUE;

/*
 *  가지(아크) 구조체
 *  속성값 또는 또 다른 마디포인터 둘 중 하나만 쓰인다.
 *  속성값이 없으면, 또 다른 마디 포인터를 가리키고 있는 것이고,
 *  마디포인터를 가리키고 있으면, 속성값을 지시하고 있는 것이다.
 */
typedef struct arc_t {
  int           nFeature;       /* 속성                                 */
  VALUE         Value;          /* 속성값                               */
  struct node_t *pNode;         /* 또 다른 마디 포인터                  */
} ARC;

/*
 *  마디 구조체
 *  열개의 가지를 갖는 구조로 되어있고, 가지들 사이에 관계를
 *  설정할 수 있다
 */
typedef struct node_t {
  int  nRelation;
  ARC  Arc[MAX_ARC_CNT];
} NODE;

void ClearNode(NODE *pNode);
int GetFeatureNumber(char *pszFeatureStr);
int GetCategoryNumber(char *pszCategoryStr);
int GetRelationNumber(char *pszRelationStr);
int GetArcNumber(NODE *pNode, int nFeature);
int GetArcListNumber(NODE *pNode, int *pnList);
void PrintNode(NODE *pNode);
char *GetFeatureValue(NODE *pNode, int *pnList, int nNum);
int GetFeature(NODE *pNode, int *pnList);
int CheckFeature(NODE *pNode, int *pnList, int nFeature);

#endif

/* ------------------------------------------------------------------------- */


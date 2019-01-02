/*
 *
 *  기획      :  한국어 생성기
 *  파일 이름 :  kg-ftr.c
 *  함수(들)  :  .
 *  파일 설명 :  속성, 속성값에 대한 자료만 들어 있음
 *  만든 날   :  1993. 09. 14
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

#include <stdio.h>
#include "kg-ftr.h"

/*
 *  속성에 대응하는 속성문자열
 */
char *pszFeature[] = {
/*
 * 0           1           2           3           4
 *"12345678", "12345678", "....
 */
  /* 0 */
  "",         "POS",      "CAT",      "HEAD",     "VAL",
  "SUBCAT",   "",         "",         "",         "",
  /* 10 */
  "SYN",      "EWFORM",   "DECLM",    "IRROM",    "EXCLM",
  "IMPRM",    "ALLWM",    "PRMSM",    "SGSTM",    "",
  /* 20 */
  "PRENPR",   "PRENPA",   "PRENFU",   "COPULZ",   "",
  "",         "",         "",         "",         "",
  /* 30 */
  "SMPLAR",   "ORDRAR",   "RSLTAR",   "SMLTAR",   "IMMDET",
  "REASON",   "CAUSEA",   "CAUSEN",   "INTROD",   "CONCSA",

  "CONCSN",   "ACKNWL",   "GUSACK",   "GUSNON",   "IFEXPL",
  "IFRSTR",   "IFCPST",   "IFCPRS",   "IFNONI",   "RESULT",

  "OPPOST",   "INTENS",   "COURSE",   "DBTPST",   "DBTPRS",
  "DBTRCL",   "DBTGUS",   "STOPPT",   "THSAME",   "NNINTF",

  "ADDDTO",   "DEEPER",   "PURPSE",   "NEEDTO",   "",
  "",         "",         "",         "",         "",
  /* 70 */
  "AUXLAA",   "AUXLGE",   "AUXLJI",   "AUXLGO",   "GENCON",
  "",         "",         "",         "",         "",
  /* 80 */
  "OHONOR",   "LOWER1",   "LOWER2",   "LOWER3",   "HIGHR1",
  "HIGHR2",   "HIGHR3",   "",         "",         "",
  /* 90 */
  "TENSE",    "PRESNT",   "RECOLL",   "FUTURE",   "PAST",
  "PPAST",    "FUTUREC",  "PASTREC",  "PASTFUT",  "PASTFUTR",
  /* 100 */
  "GUESS",    "INTEN",    "SHONOR",   "",         "",
  "",         "",         "",         "",         "",
  /* 110 */
  "PRGRSS",   "STATE",    "DONOT",    "FORBID",   "CANNOT",
  "PASSIV",   "BECOME",   "SERVCE",   "TRIAL",    "STRESS",

  "PSSESS",   "CAUSAT",   "DESIRE",   "SHOULD",   "APPROV",
  "",         "",         "",         "",         "",
  /* 130 */
  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",

  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",

  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",

  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",

  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",

  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",

  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",
  /* 200 */
  "ADJNAT",   "COPULA",   "PLURAL",   "",         "",
  "",         "",         "",         "",         "",
  /* 210 */
  "IRRGLA",   "REGULA",   "UEFALL",   "RFALL",    "UEINST",
  "SIRGL",    "DIRGL",    "BIRGL",    "RUEIRG",   "UEIRGL",

  "YEOIRG",   "GEOIRG",   "NEOIRG",   "REOIRG",   "HIRGL",
  "",         "",         "",         "",         "",

  /* 230 */
  "NNFORM",   "NORMLN",   "PRPRNN",   "PRPRNP",   "PRPRNT",
  "PRPRNB",   "PRPRNA",   "PRPRNE",   "DEPNDN",   "NOUNZ",

  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",
  /* 250 */
  "PRFORM",   "PRSNPR",   "DIRMAT",   "DIRLOC",   "",
  "",         "",         "",         "",         "",
  /* 260 */
  "NBFORM",   "NUMBER",   "CARDNL",   "ORDNL",    "",
  "",         "",         "",         "",         "",
  /* 270 */
  "PPFORM",   "SUBJ",     "SUBJ2",    "OBJ",      "OBJ2",
  "VOC",      "PREN",     "",         "",         "",
  /* 280 */
  "TOPIC",    "INDEP",    "NONSEL",   "NONSPC",   "FROM",
  "SELECT",   "SPCL",     "OFCAUS",   "NOMORE",   "INDICT",
  /* 290 */
  "EXPAND",   "DISSAT",   "EMPH",     "EACH",     "SURE",
  "UNIFOR",   "TO",       "TOO",      "FOLLOW",   "TOGETH",
  /* 300 */
  "",         "",         "",         "",         "",
  "",         "",         "",         "",         "",
  /* 310 */
  "SPLOC",    "TMLOC",    "STLOC",    "SRC",      "GOAL",
  "TOOL",     "QUAL",     "CHANGE",   "CMPSMP",   "CMPEQL",
  /* 320 */
  "CMPSAM",   "CMPTHN",   "QUADIR",   "QUAIND",   "CAUSE",
  "",         "",         "",         "",         "",
  /* 330 */
  "VBFORM",   "TVERB",    "ITVERB",   "AUXVER",   "",
  "",         "",         "",         "",         "",
  /* 340 */
  "AJFORM",   "NATADJ",   "DIRADJ",   "AUXADJ",   "",
  "",         "",         "",         "",         "",
  /* 350 */
  "PNFORM",   "NATPRE",   "DIRPRE",   "NUMPRE",   "",
  "",         "",         "",         "",         "",
  /* 360 */
  "AVFORM",   "NATADV",   "DIRADV",   "NOTADV",   "STTADV",
  "CNJADV",   "",         "",         "",         "",
  /* 370 */
  "ECFORM",   "EMOECL",   "WILECL",   "ETCADV",   "",
  "",         "",         "",         "",         "",
  /* 380 */
  "SEM",      "PRED",     "REF",      "PRENEW",   "ADVEW",
  "VMODI",    "NMODI",    "",         "",         "",
  /* 390 */
  "SELF",     "",         "",         "",         "",
  "",         "",         "",         "",         "",
  /* 400 */
  "HEADD",    "",         "",         "",         "",
  "",         "",         "",         "",         "",
  /* 410 */
  "STATE",    "OTHERS",
  NULL
};

/*
 *  품사에 대응하는 품사 문자열
 */
char *pszCategory[] = {
  "",      "NOUNP", "PRONP", "NMRLP", "POSTP", "VERBP",
  "ADJBP", "AUXLP", "ADVBP", "PRENP", "EXCLP", "EOWRD",
  NULL
};

/*
 *  관계에 대응하는 관계 문자열
 */
char *pszRelation[] = {
  "NONE_REL", "AND_REL", "OR_REL", NULL
};

/*
 *  입력   :  속성
 *  출력   :  속성 문자열
 *  호출함 :  .
 *  호출됨 :  .
 *  설  명 :  속성에 대응하는 속성문자열을 구한다.
 */
char *Feature2Str(nFeature)
int nFeature;
{
  return pszFeature[nFeature];
}

/* ------------------------------------------------------------------------- */

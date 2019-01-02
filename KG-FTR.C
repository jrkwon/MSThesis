/*
 *
 *  ��ȹ      :  �ѱ��� ������
 *  ���� �̸� :  kg-ftr.c
 *  �Լ�(��)  :  .
 *  ���� ���� :  �Ӽ�, �Ӽ����� ���� �ڷḸ ��� ����
 *  ���� ��   :  1993. 09. 14
 *  ���� ��   :  �� �� ��
 *
 *  ���۱� (C) 1993 �Ѿ���б� ������Ű��а� ���п� �ΰ����ɿ�����
 *  �� ���α׷��� ���� ��� �Ǹ��� ���۱��ڰ� �����ϴ�.
 *
 *
 *  [+] �밡���� ǥ���
 *  -----------------------------------------------------
 *   ���ξ�     ��
 *  -----------------------------------------------------
 *   c          char
 *   by         unsigned char (BYTE)
 *   n          short int or int
 *   x          short int (�׷��� ��ǥ x��ǥ)
 *   y          short int (�׷��� ��ǥ y��ǥ)
 *   i          int
 *   b          int (BOOL)
 *   w          unsigned int (WORD)
 *   h          unsigned int (WORD) (HANDLE)
 *   dw         unsigned long int (DWORD)
 *   fn         Function (�Լ� ������)
 *   s          Character Array (NULL�� ���� �ʿ� ����)
 *   sz         Character String (NULL�� ������)
 *  -----------------------------------------------------
 *
 */

#include <stdio.h>
#include "kg-ftr.h"

/*
 *  �Ӽ��� �����ϴ� �Ӽ����ڿ�
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
 *  ǰ�翡 �����ϴ� ǰ�� ���ڿ�
 */
char *pszCategory[] = {
  "",      "NOUNP", "PRONP", "NMRLP", "POSTP", "VERBP",
  "ADJBP", "AUXLP", "ADVBP", "PRENP", "EXCLP", "EOWRD",
  NULL
};

/*
 *  ���迡 �����ϴ� ���� ���ڿ�
 */
char *pszRelation[] = {
  "NONE_REL", "AND_REL", "OR_REL", NULL
};

/*
 *  �Է�   :  �Ӽ�
 *  ���   :  �Ӽ� ���ڿ�
 *  ȣ���� :  .
 *  ȣ��� :  .
 *  ��  �� :  �Ӽ��� �����ϴ� �Ӽ����ڿ��� ���Ѵ�.
 */
char *Feature2Str(nFeature)
int nFeature;
{
  return pszFeature[nFeature];
}

/* ------------------------------------------------------------------------- */
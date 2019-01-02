/*
 *   ¦¬a‰b + ¥¡¹¡¬a
 *
 *   ¥¡¹¡¬aµÁ ‰iÐs·¡ §¡Ša¸â ¸a·A¡¶…
 *   ¦¬a‰b¹¡¬aµÁ ¥¡¹¡¬aµÁ· ‰iÐs·i  e—i´á¥¡¸a.
 *
 *   1993‘e 6¶© 11·©
 *
 *   Ðe´·”ÐbŠa ¸å¸aÉ·¯¥‰·Ðb‰Á ·¥‰·»¡“wµeŠ¯©
 */

/*
 *   1) Ïa¡‹aœ‘ Š¹¡
 *
 *   1. ¥¡¹¡¬a—i·i ¢…¬á Ìa·©µA ¥¡‰ÅÐa‰¡ ‹a ¥¡¹¡¬a—i·i ·ª´á¬á ¬á¡ ‰iÐs¯¡Ç¥”a.
 *   2. ‹a ‰i‰Á“e ‹a· ÑÁ¡e·a¡ Â‰bÐe”a.
 *   3. ‰i‰ÁŸi ¸á¸wÐa‰¡ ¯¼·a¡e ¸»¡Ð··i ·¡¶wÐe”a.
 *
 *   2) ¦¬a‰b¹¡¬a Ìa·©· Š¹¡
 *
 *   1. [¦¬a‰b] Ÿi Ìa·©· ˆa¸w Àõº‰µA ý“e”a.
 *   2. ‹a ”a·q¦Èá ˆb ¦¬a‰b¹¡¬aŸi Ðe º‰µA Ðaa³¢ °á ý“e”a.

 *   3) ¥¡¹¡¬a Ìa·©· Š¹¡
 *
 *   1. [¥¡¹¡¬a] Ÿi Ìa·©· ˆa¸w Àõº‰µA ý“e”a.
 *   2. ‹a ”a·q¦Èá ˆb ¥¡¹¡¬aŸi Ðe º‰µA Ðaa³¢ °á ý“e”a.
 */

#include <stdio.h>
#include <string.h>

#define  MAX_BUF_SIZE     80             /* Ðeº‰· ÂA” ‹©·¡ */
#define  MAX_LINES        50             /* Ìa·©· ÂA” ˆ•® */
#define  FILE_BO_ID       "[¥¡¹¡¬a]"     /* ¥¡¹¡¬a Ìa·© ¯¢¥i¸a */
#define  FILE_BU_ID       "[¦¬a‰b]"     /* ¦¬a‰b¹¡¬a Ìa·©· ¯¢¥i¸a */

enum tf_t { false, true };
enum success_fail_t { fail, success };

char bojo_file_name[15];
char busa_file_name[15];

/*
 *  ¬é¡w : ÑÅ‰w¬é¸÷ ¬wÈŸi Â‰bÐe”a.
 *  ·¥¸a : ´ô”a
 *  •©Ÿ± : ´ô”a
 */

void print_config(void)
{
  fprintf(stderr, "* ¥¡¹¡¬a 2ˆ ¸ó­¢ ÑwÈ  e—i‹¡ (¸á) 1993  Ðe´·” ¸åÉ·‰Á ·¥‰·»¡“wµeŠ¯©\n\n");
  fprintf(stderr, "Bojosa file name    : %s\n", bojo_file_name);
  fprintf(stderr, "Busa gyuck name     : %s\n", busa_file_name);
  fprintf(stderr, "Maximum buffer size : %d\n", MAX_BUF_SIZE);
  fprintf(stderr, "Maximum number      : %d\n", MAX_LINES);
}

/*
 *  ¬é¡w : ¸aža Ìa·©·i µe”a.
 *  ·¥¸a : ÑÂ¸w¸aŸi Í¡ÐqÐa“e ¸ažaÌa·©· ·¡Ÿq.
 *  •©Ÿ± : ¬÷‰· -> Ìa·© Í¡·¥Èá, ¯©Ì -> NULL
 */

FILE *open_data_file(char *datafile)
{
  FILE *fp;

  fp = fopen(datafile, "r");
  if(!fp) {
    fprintf(stderr, "Ìa·© %s“e ¡µ Àx‰V”a. ™¡“e ¡µ µi‰V”a.\n", datafile);
    return NULL;
  }
  return fp;
}

/*
 *  ¬é¡w : ¦¬a‰b ¹¡¬a + ¥¡¹¡¬aŸi ‰iÐsÐe ÑwÈŸi  e—e”a.
 *  ·¥¸a : ‹¡¥¥ ¥¡¹¡¬aˆa ¸á¸w–E Ìa·©· Ìa·©Í¡·¥Èá
 *  •©Ÿ± : ´ô·q
 */
void make_result(FILE *fbusa, FILE *fbojo)
{
  char buf1[MAX_LINES][MAX_BUF_SIZE];
  char buf2[MAX_LINES][MAX_BUF_SIZE];
  char id[MAX_BUF_SIZE], tmp_buf[MAX_BUF_SIZE];
  int i, j, cnt1, cnt2;

  /* Ìa·© ¯¢¥i¸a ÑÂ·¥ */
  fgets(id, MAX_BUF_SIZE, fbusa);
  if(strncmp(FILE_BU_ID, id, strlen(FILE_BU_ID))) {
    fprintf(stderr, "Ìa·© %s ·¡ [¦¬a‰b] Ìa·©  x¡??\n", busa_file_name);
    return;
  }
  fgets(id, MAX_BUF_SIZE, fbojo);
  if(strncmp(FILE_BO_ID, id, strlen(FILE_BO_ID))) {
    fprintf(stderr, "Ìa·© %s ·¡ [¥¡¹¡¬a] Ìa·©  x¡??\n", bojo_file_name);
    return;
  }

  /* ¦¬a‰b¹¡¬aŸi ¡¡– ·ª´á—i·¥”a */
  for(i = 0; i < MAX_LINES; i++) {
    fgets(buf1[i], MAX_BUF_SIZE, fbusa);
    if(feof(fbusa)) {
      break;
    }
    if(strlen(buf1[i])) /*  a»¡ b· \n ¢…¸a »¡¶‹¡ */
      buf1[i][strlen(buf1[i])-1] = NULL;
    fprintf(stderr, "%4d º‰·i ·ª´ö´á¶a...\r", i);
  }
  if(i == MAX_LINES) {
    fprintf(stderr, "º‰ ®ˆa á¢  g´a¶a\n¯©Ì....\n");
    return;
  }
  fprintf(stderr, "¬÷‰·.... ¡¡– %4dˆŸi ·ª´ö´á¶a.\n", i);
  cnt1 = i;  /* ·ª´á—i·¥ ¦¬a‰b¹¡¬a· ˆ•® */

  /* ¥¡¹¡¬aŸi ¡¡– ·ª´á—i·¥”a */
  for(i = 0; i < MAX_LINES; i++) {
    fgets(buf2[i], MAX_BUF_SIZE, fbojo);
    if(feof(fbojo)) {
      break;
    }
    if(strlen(buf2[i])) /*  a»¡ b· \n ¢…¸a »¡¶‹¡ */
      buf2[i][strlen(buf2[i])-1] = NULL;
    fprintf(stderr, "%4d º‰·i ·ª´ö´á¶a...\r", i);
  }
  if(i == MAX_LINES) {
    fprintf(stderr, "º‰ ®ˆa á¢  g´a¶a\n¯©Ì....\n");
    return;
  }
  fprintf(stderr, "¬÷‰·.... ¡¡– %4dˆŸi ·ª´ö´á¶a.\n", i);
  cnt2 = i;  /* ·ª´á—i·¥ ¥¡¹¡¬a· ˆ•® */

  /* ‰iÐsÐe ÑwÈŸi ÑÁ¡eµA Â‰bÐe”a */
  for(i = 0; i < cnt1; i++) {
    for(j = 0; j < cnt2; j++) {
      if(i != j) {
        sprintf(tmp_buf, "%s + %s\n", buf1[i], buf2[j]);
        printf("%s", tmp_buf);
      }
    }
  }
}

void main(int argc, char *argv[])
{
  FILE *fbojo, *fbusa;

  if(argc != 3) {
    fprintf(stderr, "Ìa·©·¡Ÿq·i °á´¡»¡¶a.. ¬a¶w¤ó·e¶a..\n");
    fprintf(stderr, "BUSA-BOJ <¦¬a‰b¹¡¬a Ìa·©·¡Ÿq> <¥¡¹¡¬a Ìa·©·¡Ÿq>\n");
    return;
  }
  strcpy(busa_file_name, strupr(argv[1]));
  strcpy(bojo_file_name, strupr(argv[2]));
  fbusa = open_data_file(busa_file_name);
  fbojo = open_data_file(bojo_file_name);
  print_config();
  if(fbojo && fbusa) {
    make_result(fbusa, fbojo);
  }
}
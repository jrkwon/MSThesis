/*
 *   ¥¡¹¡¬a + ¥¡¹¡¬a
 *
 *   –ˆ· ¥¡¹¡¬a¡Ÿ¡ ‰iÐsÐa“e ‰w¶Ÿi ¡¡– ŠÐ¥¡¸a
 *
 *   1993‘e 6¶© 1·©
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
 *   2) ¥¡¹¡¬a Ìa·©· Š¹¡
 *
 *   1. [¥¡¹¡¬a] Ÿi Ìa·©· ˆa¸w Àõº‰µA ý“e”a.
 *   2. ‹a ”a·q¦Èá ˆb ¥¡¹¡¬aŸi Ðe º‰µA Ðaa³¢ °á ý“e”a.
 */

#include <stdio.h>
#include <string.h>

#define  MAX_BUF_SIZE     40             /* ¥¡¹¡¬a· ÂA” ‹©·¡ */
#define  MAX_BOJOSA_NO    50             /* ¥¡¹¡¬a· ÂA” ˆ•® */
#define  FILE_ID          "[¥¡¹¡¬a]"     /* Ìa·© ¯¢¥i¸a */

enum tf_t { false, true };
enum success_fail_t { fail, success };

char data_file_name[15];

/*
 *  ¬é¡w : ÑÅ‰w¬é¸÷ ¬wÈŸi Â‰bÐe”a.
 *  ·¥¸a : ´ô”a
 *  •©Ÿ± : ´ô”a
 */

void print_config(void)
{
  fprintf(stderr, "* ¥¡¹¡¬a 2ˆ ¸ó­¢ ÑwÈ  e—i‹¡ (¸á) 1993  Ðe´·” ¸åÉ·‰Á ·¥‰·»¡“wµeŠ¯©\n\n");
  fprintf(stderr, "Data file name      : %s\n", data_file_name);
  fprintf(stderr, "Maximum buffer size : %d\n", MAX_BUF_SIZE);
  fprintf(stderr, "Maximum number      : %d\n", MAX_BOJOSA_NO);
  fprintf(stderr, "File identification : %s\n\n", FILE_ID);
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
 *  ¬é¡w : –ˆ· ¥¡¹¡¬aŸi ‰iÐsÐe ÑwÈŸi  e—e”a.
 *  ·¥¸a : ‹¡¥¥ ¥¡¹¡¬aˆa ¸á¸w–E Ìa·©· Ìa·©Í¡·¥Èá
 *  •©Ÿ± : ´ô·q
 */
void make_bojosa(FILE *fp)
{
  char buf[MAX_BOJOSA_NO][MAX_BUF_SIZE];
  char id[MAX_BUF_SIZE], tmp_buf[MAX_BUF_SIZE];
  int i, j, cnt;

  /* Ìa·© ¯¢¥i¸a ÑÂ·¥ */
  fgets(id, MAX_BUF_SIZE, fp);
  if(strncmp(FILE_ID, id, strlen(FILE_ID))) {
    fprintf(stderr, "Ìa·© %s ·¡ [¥¡¹¡¬a] Ìa·©  x¡??\n");
    return;
  }

  /* ¥¡¹¡¬aŸi ¡¡– ·ª´á—i·¥”a */
  for(i = 0; i < MAX_BOJOSA_NO; i++) {
    fgets(buf[i], MAX_BUF_SIZE, fp);
    if(feof(fp)) {
      break;
    }
    if(strlen(buf[i])) /*  a»¡ b· \n ¢…¸a »¡¶‹¡ */
      buf[i][strlen(buf[i])-1] = NULL;
    fprintf(stderr, "%4d º‰·i ·ª´ö´á¶a...\r", i);
  }
  if(i == MAX_BOJOSA_NO) {
    fprintf(stderr, "¥¡¹¡¬a ˆ•®ˆa á¢  g´a¶a\n¯©Ì....\n");
    return;
  }
  fprintf(stderr, "¬÷‰·.... ¡¡– %4dˆŸi ·ª´ö´á¶a.\n", i);
  cnt = i;  /* ·ª´á—i·¥ ¥¡¹¡¬a· ˆ•® */

  /* ‰iÐsÐe ÑwÈŸi ÑÁ¡eµA Â‰bÐe”a */
  for(i = 0; i < cnt; i++) {
    for(j = 0; j < cnt; j++) {
      if(i != j) {
        sprintf(tmp_buf, "%s + %s\n", buf[i], buf[j]);
        printf("%s", tmp_buf);
      }
    }
  }
}

void main(int argc, char *argv[])
{
  FILE *fp;

  if(argc == 1) {
    fprintf(stderr, "Ìa·©·¡Ÿq·i °á´¡»¡¶a.. ¬a¶w¤ó·e¶a..\n");
    fprintf(stderr, "MK_BOJO <¥¡¹¡¬a Ìa·©·¡Ÿq>\n");
    return;
  }
  strcpy(data_file_name, strupr(argv[1]));
  fp = open_data_file(data_file_name);
  print_config();
  if(fp) {
    make_bojosa(fp);
  }
}
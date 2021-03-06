/*
 *   ���a�b + �����a
 *
 *   �����a�� �i�s�� ���a�� �a�A����
 *   ���a�b���a�� �����a���� �i�s�i �e�i�ᥡ�a.
 *
 *   1993�e 6�� 11��
 *
 *   �e�����b�a ��aɷ�����b�� �������w�e����
 */

/*
 *   1) �a���a�� ����
 *
 *   1. �����a�i�i ���� �a���A �����a�� �a �����a�i�i ����� �ᝡ �i�s��ǥ�a.
 *   2. �a �i���e �a�� ���e�a�� �b�e�a.
 *   3. �i���i ��w�a�� ���a�e ����з�i ���w�e�a.
 *
 *   2) ���a�b���a �a���� ����
 *
 *   1. [���a�b] �i �a���� �a�w �����A ���e�a.
 *   2. �a �a�q���� �b ���a�b���a�i �e ���A �a�a�� �� ���e�a.

 *   3) �����a �a���� ����
 *
 *   1. [�����a] �i �a���� �a�w �����A ���e�a.
 *   2. �a �a�q���� �b �����a�i �e ���A �a�a�� �� ���e�a.
 */

#include <stdio.h>
#include <string.h>

#define  MAX_BUF_SIZE     80             /* �e���� �A�� ���� */
#define  MAX_LINES        50             /* �a���� �A�� ���� */
#define  FILE_BO_ID       "[�����a]"     /* �����a �a�� ���i�a */
#define  FILE_BU_ID       "[���a�b]"     /* ���a�b���a �a���� ���i�a */

enum tf_t { false, true };
enum success_fail_t { fail, success };

char bojo_file_name[15];
char busa_file_name[15];

/*
 *  ��w : �ŉw��� �wȁ�i �b�e�a.
 *  ���a : ���a
 *  ���� : ���a
 */

void print_config(void)
{
  fprintf(stderr, "* �����a 2�� �� �wȁ �e�i�� (��) 1993  �e���� ��ɷ�� �������w�e����\n\n");
  fprintf(stderr, "Bojosa file name    : %s\n", bojo_file_name);
  fprintf(stderr, "Busa gyuck name     : %s\n", busa_file_name);
  fprintf(stderr, "Maximum buffer size : %d\n", MAX_BUF_SIZE);
  fprintf(stderr, "Maximum number      : %d\n", MAX_LINES);
}

/*
 *  ��w : �a�a �a���i �e�a.
 *  ���a : �¸w�a�i ͡�q�a�e �a�a�a���� ���q.
 *  ���� : ���� -> �a�� ͡����, ��́ -> NULL
 */

FILE *open_data_file(char *datafile)
{
  FILE *fp;

  fp = fopen(datafile, "r");
  if(!fp) {
    fprintf(stderr, "�a�� %s�e �� �x�V�a. ���e �� �i�V�a.\n", datafile);
    return NULL;
  }
  return fp;
}

/*
 *  ��w : ���a�b ���a + �����a�i �i�s�e �wȁ�i �e�e�a.
 *  ���a : ���� �����a�a ��w�E �a���� �a��͡����
 *  ���� : ���q
 */
void make_result(FILE *fbusa, FILE *fbojo)
{
  char buf1[MAX_LINES][MAX_BUF_SIZE];
  char buf2[MAX_LINES][MAX_BUF_SIZE];
  char id[MAX_BUF_SIZE], tmp_buf[MAX_BUF_SIZE];
  int i, j, cnt1, cnt2;

  /* �a�� ���i�a �·� */
  fgets(id, MAX_BUF_SIZE, fbusa);
  if(strncmp(FILE_BU_ID, id, strlen(FILE_BU_ID))) {
    fprintf(stderr, "�a�� %s �� [���a�b] �a�� �x��??\n", busa_file_name);
    return;
  }
  fgets(id, MAX_BUF_SIZE, fbojo);
  if(strncmp(FILE_BO_ID, id, strlen(FILE_BO_ID))) {
    fprintf(stderr, "�a�� %s �� [�����a] �a�� �x��??\n", bojo_file_name);
    return;
  }

  /* ���a�b���a�i ���� ����i���a */
  for(i = 0; i < MAX_LINES; i++) {
    fgets(buf1[i], MAX_BUF_SIZE, fbusa);
    if(feof(fbusa)) {
      break;
    }
    if(strlen(buf1[i])) /* �a���b�� \n ���a ������ */
      buf1[i][strlen(buf1[i])-1] = NULL;
    fprintf(stderr, "%4d ���i ������a...\r", i);
  }
  if(i == MAX_LINES) {
    fprintf(stderr, "�� ���a �ᢁ �g�a�a\n��́....\n");
    return;
  }
  fprintf(stderr, "����.... ���� %4d���i ������a.\n", i);
  cnt1 = i;  /* ����i�� ���a�b���a�� ���� */

  /* �����a�i ���� ����i���a */
  for(i = 0; i < MAX_LINES; i++) {
    fgets(buf2[i], MAX_BUF_SIZE, fbojo);
    if(feof(fbojo)) {
      break;
    }
    if(strlen(buf2[i])) /* �a���b�� \n ���a ������ */
      buf2[i][strlen(buf2[i])-1] = NULL;
    fprintf(stderr, "%4d ���i ������a...\r", i);
  }
  if(i == MAX_LINES) {
    fprintf(stderr, "�� ���a �ᢁ �g�a�a\n��́....\n");
    return;
  }
  fprintf(stderr, "����.... ���� %4d���i ������a.\n", i);
  cnt2 = i;  /* ����i�� �����a�� ���� */

  /* �i�s�e �wȁ�i ���e�A �b�e�a */
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
    fprintf(stderr, "�a�����q�i �ᴡ���a.. �a�w��e�a..\n");
    fprintf(stderr, "BUSA-BOJ <���a�b���a �a�����q> <�����a �a�����q>\n");
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
/*
 *   �����a + �����a
 *
 *   ������ �����a���� �i�s�a�e �w���i ���� ��Ё���a
 *
 *   1993�e 6�� 1��
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
 *   2) �����a �a���� ����
 *
 *   1. [�����a] �i �a���� �a�w �����A ���e�a.
 *   2. �a �a�q���� �b �����a�i �e ���A �a�a�� �� ���e�a.
 */

#include <stdio.h>
#include <string.h>

#define  MAX_BUF_SIZE     40             /* �����a�� �A�� ���� */
#define  MAX_BOJOSA_NO    50             /* �����a�� �A�� ���� */
#define  FILE_ID          "[�����a]"     /* �a�� ���i�a */

enum tf_t { false, true };
enum success_fail_t { fail, success };

char data_file_name[15];

/*
 *  ��w : �ŉw��� �wȁ�i �b�e�a.
 *  ���a : ���a
 *  ���� : ���a
 */

void print_config(void)
{
  fprintf(stderr, "* �����a 2�� �� �wȁ �e�i�� (��) 1993  �e���� ��ɷ�� �������w�e����\n\n");
  fprintf(stderr, "Data file name      : %s\n", data_file_name);
  fprintf(stderr, "Maximum buffer size : %d\n", MAX_BUF_SIZE);
  fprintf(stderr, "Maximum number      : %d\n", MAX_BOJOSA_NO);
  fprintf(stderr, "File identification : %s\n\n", FILE_ID);
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
 *  ��w : ������ �����a�i �i�s�e �wȁ�i �e�e�a.
 *  ���a : ���� �����a�a ��w�E �a���� �a��͡����
 *  ���� : ���q
 */
void make_bojosa(FILE *fp)
{
  char buf[MAX_BOJOSA_NO][MAX_BUF_SIZE];
  char id[MAX_BUF_SIZE], tmp_buf[MAX_BUF_SIZE];
  int i, j, cnt;

  /* �a�� ���i�a �·� */
  fgets(id, MAX_BUF_SIZE, fp);
  if(strncmp(FILE_ID, id, strlen(FILE_ID))) {
    fprintf(stderr, "�a�� %s �� [�����a] �a�� �x��??\n");
    return;
  }

  /* �����a�i ���� ����i���a */
  for(i = 0; i < MAX_BOJOSA_NO; i++) {
    fgets(buf[i], MAX_BUF_SIZE, fp);
    if(feof(fp)) {
      break;
    }
    if(strlen(buf[i])) /* �a���b�� \n ���a ������ */
      buf[i][strlen(buf[i])-1] = NULL;
    fprintf(stderr, "%4d ���i ������a...\r", i);
  }
  if(i == MAX_BOJOSA_NO) {
    fprintf(stderr, "�����a �����a �ᢁ �g�a�a\n��́....\n");
    return;
  }
  fprintf(stderr, "����.... ���� %4d���i ������a.\n", i);
  cnt = i;  /* ����i�� �����a�� ���� */

  /* �i�s�e �wȁ�i ���e�A �b�e�a */
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
    fprintf(stderr, "�a�����q�i �ᴡ���a.. �a�w��e�a..\n");
    fprintf(stderr, "MK_BOJO <�����a �a�����q>\n");
    return;
  }
  strcpy(data_file_name, strupr(argv[1]));
  fp = open_data_file(data_file_name);
  print_config();
  if(fp) {
    make_bojosa(fp);
  }
}
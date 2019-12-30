#ifndef __SAOL_ARRAY_LIB_H_INCLUDED__
#define __SAOL_ARRAY_LIB_H_INCLUDED__

void ini(char *arg);
void addr(char *arg);
void shr(char *arg);
void shl(char *arg);
void show_elm(char *arg);
void show_arr(char *arg);
void comment(char *arg);
void filler(char *arg);
void int_mode(char *arg);
void char_mode(char *arg);
void sum(char *arg);
void subt(char *arg);
void mult(char *arg);
void idiv(char *arg);
void cla(char *arg);
void pstart(char *arg);
void pend(char *arg);
void assig(char *arg);
void notassig(char *arg);
void andf(char *arg);
void orf(char *arg);
void iter(char *arg);
void predf(char *arg);
void unpred(char *arg);
void swap(char *arg);

int is_empty(char *word);
int is_kw(char *word);
void exec(int arr_index, char *arg);

#endif

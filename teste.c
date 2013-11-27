/* 
 * Teste da nova chamada de sistema
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int pid;
  char op;

  printf("Digite o pid do processo: ");
  scanf(" %d", &pid);
  printf("Adicionar (1) ou remover (0) da lista dos imortais? ");
  scanf(" %d" , &op);
  int r = syscall(351, pid, op); 
  printf("Retorno da chamada de sistema: %d.n", r);
  return r;
}
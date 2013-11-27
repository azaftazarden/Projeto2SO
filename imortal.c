#include <linux/unistd.h>
#include <linux/linkage.h>
//modifica linux-3.12/kernel/signal.c:2909
int contador_imortais = 0;
int lista_imortais[100];


/* Definicao: sys_imortal faz com que um processo nao possa ser morto (sinal SIGKILL)
 * parametros: 	int pid = pid do processo a ser imortalizado
 * 		char op	= 1 para por um processo na lista dos imortais
 * 			  0 para tirar um processo da lista
 * retorno:	0 em caso de sucesso
 * 		1 em caso de erro
 * erros:	remover um processo que nao esta na lsita
 * 		adicionar um processo com a lista cheia (maximo de 100 processos)
 */
asmlinkage long sys_imortal(int pid, char op) {
  int i;
  int j;
  
  //lista cheia
  if(contador_imortais==100) return 1;
  //operador invalido
  if(op!=0 && op!=1) return 1;
  
  for(i=0; i<contador_imortais; i++){
      if(pid==lista_imortais[i]){
	//caso adicionar um processo que ja esta na lista
	if(op==1){
	  return 0;
	}else{
	  //remove o processo encontrado e volta todos os processos uma posicao na fila
	  for(j=i; j<contador_imortais-1; j++){
	    lista_imortais[j]=lista_imortais[j+1];
	  }
	  contador_imortais--;
	  return 0;
	}
      }
  }
  
  //processo nao encontrado
  if(op==1){
    lista_imortais[contador_imortais++] = pid;
    return 0;
  }else{
    return 1;
  }
  
  return 0;
}
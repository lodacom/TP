#include <stdio.h>
#include <stdlib.h>

int main(){
  
  int a = 10;
  int b = 25;
  int *p = &b;
  int *pp = &a;

  printf("a = %d\n", a);
  printf("b = %d\n", b);
  printf("&a = %d\n", &a);
  printf("&b = %d\n", &b);
  printf("p = %d\n", p);
  printf("pp = %d\n\n", pp);

  printf("*(&(*(*(&p)))) = %d\n", *(&(*(*(&p)))));
  printf("*(p+1) = %d\n", *(p+1));
  printf("*(*(&p)+1) = %d\n", *(*(&p)+1));
  printf("*(*(&pp)-1) = %d\n", *(*(&pp)-1));
  printf("*(&(*(*(&p)))+1) = %d\n", *(&(*(*(&p)))+1));

  return 0;
}

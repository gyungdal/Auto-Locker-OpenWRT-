#include <stdio.h>

void main(){
  char* temp = "192.168.1.201    0x1         0x2         d8:cb:8a:ef:7d:0e     *        br-lan";
  char* ip = (char*)malloc(sizeof(char) * 40);
  char* mac = (char*)malloc(sizeof(char) * 40);
  sscanf(temp, "%s %*s %*s %s %*s %*s", ip, mac);
  printf("%s %s", ip, mac);
}

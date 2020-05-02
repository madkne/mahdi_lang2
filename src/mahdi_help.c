
#include <Mahdi/system.h>


//************************************************
void MHELP_usage() {
  printf("usage for Mahdi: mahdi [option] --OR-- mahdi [pack-name] [arg]...\n");
  printf("Try 'mahdi -h' for more information.\n");
}
//************************************************
void MHELP_version() {
  printf("%s - %s(#%i)\n", VERSION_NAME, VERSION, VERSION_NUMBER);
}
//************************************************
void MHELP_info() {
  printf("%s\n", APP_NAME);
  printf("VERSION:%s-%s(#%i)\n", VERSION_NAME, VERSION, VERSION_NUMBER);
  printf("BUILD:%s(%s) [%s-%s]\n", OS_BUILD, OS_ARCH, BUILD_DATE, BUILD_TIME);
  printf("LICENCE:%s\n", LICENCE);
  printf("COMPILER:%s-%s\n", C_COMPILER_NAME, C_COMPILER_STD);
  printf("CREATOR:%s[%s-%s]\n", LANGUAGE_CREATOR, FIRST_BUILD, BETA_LBUILD);
  printf("TRUST:%i%%\n", TRUST_LEVEL);
}
//************************************************
void MHELP_main() {
  printf("\t In The Name Of ALLAH\n\t----------------------\n");
  printf("%s %s(#%i)-%s\n",
         APP_NAME, VERSION_NAME, VERSION_NUMBER, VERSION);
  printf("usage: mahdi [option] --OR-- mahdi [pack-name] [arg]...\n");
  printf("Options:\n");
  printf("-v	:Display mahdi version information\n");
  printf("-i	:Display information about MAHDI. \n\n");
  printf("-h	:Display information about anything. \n\n");
  printf("-------------------------------------\n");
  printf("%s\n", SLOGAN);
  printf("See '%s' for more details.\n", OFFICIAL_WEBSITE);
}


#include <Mahdi/system.h>


// *********************************************
void TEST_main(){

    // debug("hello world\n");
  //=>if programmer debug is enabled, then display main source and utf8 structures
  if (is_programmer_debug >= 3){
    COM_print_struct(PRINT_MAIN_SOURCE_ST);
    COM_print_struct(PRINT_UTF8_ST);
    COM_print_struct(PRINT_TOKENS_SOURCE_ST);
  }

  //  String ss = 0;
  //  str_init(&ss, "Hello Amin.");
  //  printf("encode:%s\n>>>%s\n>>>%s$\n", ss, MPLV1_encode(ss),MPLV1_decode(MPLV1_encode(ss)));
  //  console_color_reverse();
  //  printf("Hello World:%s\n",argv[1]);
  //  console_color_reset();
  //  printf("Hello World:%s\n",argv[1]);
    //  print_struct(PRINT_CONDITION_LEVEL_ST);
    //	print_magic_macros(CONFIG_MAGIC_MACRO_TYPE);
  //  print_struct(PRINT_UTF8_ST);

  // printf("PPP:%s\n",RUNKIT_get_firstitem_listormap("[{'q1':[6,89],'q2':8+3}]"));
  // printf("\033[1;31m bold red text \033[0m\n");
  // int32 o[]={5,7,9};
  // I32_array_reset(o);
  // printf("fffff:%i,%i,%i\n",o[0],o[1],o[2]);
  // int32 fg[5]={9,91,92,93,94};
  // printf("DDDDDD:%i\n",CH_search_index(words_splitter,'f'));
  // map* st=0;
  // map* en=0;
  // _map_push(&st,&en,"H1","hello...");
  // _map_push(&st,&en,"H2","Amin");
  // _map_push(&st,&en,"H3","Delavar");
  // _map_popleft(&st,&en);
  // _map_popleft(&st,&en);
  // map j=_map_popleft(&st,&en);
  // printf("map is:%s=>%s\n",j.key,_map_print(st));
  // printf("CCCC:%i\n",STR_last_indexof("HelloHel","He"));
    // printf("string:%s\n",RUNKIT_calc_boolean_exp("false and not true or not false"));
    // StrList eee=0;
    // Boolean iss=false;
    // uint32 ee=RUNKIT_simplify_define_vars("def g=pkg('hello',56)",&eee,&iss);
    // printf("DDDD:%s\n",RUNKIT_calculate_listormap("{\"q\"+\"1\":[5,8*2,5^2],\"q2\"-\"2\":[7+3,7]}","number"));
    // printf("SSSSS:%s\n",COM_get_Mahdi_dir_path());
  TEST_memory();
}
// *************************************
void TEST_memory(){
  // LintList l=0;
  // LLIST_append(&l,0,67);
  // _mpoint_append('c',"Hello",true,l,0,1);
  VM_show(0);

}
// *************************************

void TEST_inheritance(){
  // //=>if programmer debug is enabled, then show all structs
  // if(is_programmer_debug>=2){
  //   COM_print_struct(PRINT_UTF8_ST);
  //   COM_print_struct(PRINT_IMPORT_ST);
  //   COM_print_struct(PRINT_CONFIG_ST);
  //   COM_print_struct(PRINT_PACK_ST);
  //   COM_print_struct(PRINT_FUNC_ST);
  //   COM_print_struct(PRINT_DATA_TYPES_ST);
  //   COM_print_struct(PRINT_STRU_ST);
  //   COM_print_struct(PRINT_INSTRU_ST);
  //   COM_print_struct(PRINT_FUNC_PACK_PARAMS_ST);
  //   COM_print_struct(PRINT_MODULE_PACKFUNCS_ST);
  // }
}
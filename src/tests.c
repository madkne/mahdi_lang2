
#include <Mahdi/system.h>


// *********************************************
void TEST_main(){

  // test debug function
  //debug("hello world\n");
  //-------------------------------------
  //=>if programmer debug is enabled, then display main source and utf8 structures
  if (is_programmer_debug >= 3){
    // COM_print_struct(PRINT_MAIN_SOURCE_ST);
    // COM_print_struct(PRINT_UTF8_ST);
    COM_print_struct(PRINT_TOKENS_SOURCE_ST);
    COM_print_struct(PRINT_DATA_TYPES_ST);
  }
  //-------------------------------------
  // test regex pattern splitter
  // StrList pat = 0;
  // uint32 pat_len = COM_regex_pattern_splitter("[package?].[class?].[function]([params*,]){[index?]}",&pat);
  // debug("pattern:%s",SLIST_print(pat,pat_len));
  //-------------------------------------
  //=> test regex parser with source tokens
  // int i=174;
  // map *result = PARSE_regex(&i,"class[name]([parent?])");
  // debug("regex_result:%s",_map_print(result));


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
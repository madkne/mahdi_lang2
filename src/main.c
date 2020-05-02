#include <Mahdi/system.h>

//************************************************prototypes
Boolean INTR_start();

void INTR_init();

uint8 interpreter_mode = 0;

//************************************************
int main(int argc, char **argv) {
  //=>time of start program
  AppStartedClock = clock();
  AppStartedTime = STR_from_Longint(CALL_unix_time());
  //=>this is real mahdi interpreter!
  is_real_mahdi = true;
  //=>init exceptions list
  EXP_init();
  //=>get Argvs,analyze it
  //=>save program command
  program_command=argv[0];
  //=>no any argv, show help usage
  if (argc < 2) {
    MHELP_usage();
  }
  //=>-v argv, show help version 
  else if (argv[1][0] == '-' && argv[1][1] == 'v') {
    MHELP_version();
    interpreter_mode = 'v';
  }
  //=>-i argv, show help info  
  else if (argv[1][0] == '-' && argv[1][1] == 'i') {
    MHELP_info();
    interpreter_mode = 'i';
  } 
  //=>-h argv, show mhelp (with params)
  else if (argv[1][0] == '-' && argv[1][1] == 'h') {
    MHELP_main();
    interpreter_mode = 'h';
  }
  //=>if any argv that start with '-', then error! 
  else if (argv[1][0] == '-') {
    EXP_print_error(0, "unknown_opt", "stdin", argv[1], 0, "main");
    MHELP_usage();
  }
  //=>if argv not an option, check for exist a file 
  else {
    //=>get argv as program package name
    STR_init(&program_package, argv[1]);
    //=>store arguments of program
    if (argc > 2){
      for (int ii = 2; ii < argc; ++ii)
        SLIST_append(&program_argvs, argv[ii], argvs_len++);
    }
    //=>start mahdi interpreter and get status of it in end
    Boolean ret = INTR_start();
    interpreter_mode = 's';
    if (!ret)
      EXP_print_error(0, "bad_exit", "stdin", 0, 0, "main");
  }
  // run main test, if in programmer debug mode
  if(is_programmer_debug>0){
    TEST_main();
  }

  //=>time of end program
  COM_exit(EXIT_NORMAL);
  return 0;
}
//************************************************
Boolean INTR_start() {
  //-----------------------init interpreter
  STR_init(&interpreter_level, "init");
  INTR_init();
  // //-----------------------parsing source codes
  // STR_init(&interpreter_level, "parse");
  // Boolean ret0 = IMPORT_run();
  // //printf("VVVVVV:%i\n",ret0);
  // if (!ret0) return false;
  // //-----------------------solve inherits packages
	// if(entry_table.need_inheritance){
	// 	STR_init(&interpreter_level, "inherit");
	// 	Boolean ret1 =INHERIT_run();
  //   if (!ret1) return false;
	// }
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
  // //-----------------------meaning&running instructions
  // STR_init(&interpreter_level, "runtime");
  // Boolean ret3 = APP_start();
  // if (!ret3) return false;
  // //=>show virual memory entries
  // if (is_programmer_debug > 0) {
  //   VM_show(0);
  // }
//   //-----------------------free memory
//   str_init(&interpreter_level, "free");
return true;
}

//************************************************
void INTR_init() {
  //=>init data defined
  DEF_init();
  //=>init virtual memory
  VM_init();
  //=>init built-in functions
  // BUILT_init();
  // //=>init importer
  // IMPORT_init();
  //********************
  //get_basic_system_info()
}

//************************************************
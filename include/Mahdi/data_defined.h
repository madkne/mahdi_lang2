//
// Created by madkne on 2019.10.24
//

#ifndef __MAHDI_DATA_DEFINED_H
#define __MAHDI_DATA_DEFINED_H  1

//******************************data values
clock_t AppStartedClock;
String AppStartedTime;
String program_root;
String interpreter_level;
String interpreter_path;
String interpreter_tmp_path;
String os_separator;
uint8 MAX_INT_LEN;
uint8 MAX_FLOAT_LEN;
uint8 max_estimate_divide_huge;
uint8 max_float_estimate_huge_X0;
String new_line_char;
String os_tmp_dir;
uint32 BufferSize;
String hostname;
String os_version;
Longint os_total_memory;
Longint os_total_disk;
Boolean is_real_mahdi;
String program_command;
StrList program_argvs;
uint32 argvs_len;
//******************************config values
uint8 is_programmer_debug;
// String logfile_path;
int8 errors_mode;
int8 warnings_mode;
uint8 max_steps_estimate_huge;
uint32 max_decimal_has_huge;
// // Boolean safe_mode;
// // Boolean optimize_mode;
// Boolean debug_mode;
// // String bytecode_path;
// Boolean build_mode;
// String buildfile_path;

//******************************
// #if WINDOWS_PLATFORM == true
// HINSTANCE mahdi_modules_instance[100];
// #elif LINUX_PLATFORM == true
// void * mahdi_modules_instance[100];
// #endif

uint32 errcodes[MAX_ERROR_CODES];
uint8 errcodes_len;
String exceptions_group[16];
String exceptions_type[4];

// String package_zones[2];
// String method_attributes[2];
// String keywords[26];
// // String keywords_out[13];
// String block_instructions[6];
// uint8 single_operators[7];
// String comparative_operators[6];
// String alloc_operators[8];
// String boolean_operators[2];
// String basic_types[3];
// uint8 golden_bytes[5];
// uint8 token_splitters[11];
// uint8 words_splitter[16];
// uint8 sub_types[6];
// String control_chars[5];
// StrList installed_modules;
// uint32 installed_modules_len;

//****************************exceptions_list struct
typedef struct exceptions_list_struct {
  uint32 id;
  int8 type;
  uint8 group;
  String lbl;
  String text;

  struct exceptions_list_struct *next;
} exli;
//****************************virtual memory
//runtime
typedef struct var_memory_struct {
    Longint id;
    Longint pointer_id;
    Longint package_id;
    Longint block_id;//(0:global vars or class vars or func direct vars)
    Longint func_id;//(0:global vars or class vars)
    Longint func_index;//(for recursion)
    Longint lambda_id;
    Longint lambda_index;//(for lambda threading and nesting lambdas)
    Longint class_id;//(0:global vars in outer or inner of global functions)
    Longint class_index;//(for loop same init classes)
    Longint type_id;
    Boolean is_private;
    uint8 flag;
    String  name;
  struct var_memory_struct *next;
} Mvar;
// ----------------------------------
typedef struct pointer_memory_struct {
    Longint id;
    uint8 type;
    //('i':int , 'f':float , 'h':huge , 's':string , 'u':utf8 , 'b':boolean , 'p':Pointer To Mpoint , 'v':Pointer To Mvar )
    String raw;//(for int,float,huge,string,utf8)
    Boolean bool;//(for boolean)
    LintList items;//(for mpoint,mvar)
    StrList keys; //(for mpoint)
    Longint items_len;
    struct pointer_memory_struct *next;
} Mpoint;
//static
Mpoint *hash_pointers[HASH_MEM_SIZE];
Mpoint *hash_pointers_end[HASH_MEM_SIZE];
Longint hash_pointers_len[HASH_MEM_SIZE];
//****************************built_in_funcs struct
typedef struct built_in_funcs_struct {
  uint32 id;
  String func_name;
  String params;
  uint8 params_len;

  struct built_in_funcs_struct *next;
} bifs;
//****************************entry_table struct
struct entry_table_struct {
    // exceptions struct
    exli *exli_start;
    exli *exli_end;
    Longint exceptions_count;
    // virtual memory struct
    Mvar *var_memory_start;
    Mvar *var_memory_end;
    Mpoint *pointer_memory_start;
    Mpoint *pointer_memory_end;
    Longint var_mem_id;
    Longint var_mem_len;
    Longint pointer_mem_id;
    Longint pointer_mem_len;
    // built-in functions struct
    bifs *bifs_start;
    bifs *bifs_end;
    uint32 bifs_len;
    // program package source files
    String program_package;
    StrList program_sources;
    uint32 program_sources_len;
};
struct entry_table_struct entry_table;


//*************************************************************
//*********************public functions************************
//*************************************************************

void DEF_init();


#endif //__MAHDI_DATA_DEFINED_H

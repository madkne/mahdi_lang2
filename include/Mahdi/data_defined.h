//
// Created by madkne on 2019.10.24
//

#ifndef __MAHDI_DATA_DEFINED_H
#define __MAHDI_DATA_DEFINED_H  1

//******************************data values
clock_t AppStartedClock;
String AppStartedTime;
String project_root;
String stdin_source_path;
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
uint64 os_total_memory;
uint64 os_total_disk;
Boolean is_real_mahdi;
String program_command;
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
// StrList program_argvs;
// uint32 argvs_len;
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
// // //****************************entry_table struct
struct entry_table_struct {
    exli *exli_start;
    exli *exli_end;
    Longint exceptions_count;


//   imin *import_start;
//   imin *import_end;
//   Longint import_id;
//   uint32 import_active_count;

//   coin *config_start;
//   coin *config_end;
//   Longint config_id;

//   soco *soco_main_start;
//   soco *soco_main_end;
//   String current_source_path;
//   Longint soco_main_count;

//   soco *soco_tokens_start;
//   soco *soco_tokens_end;
//   Longint soco_tokens_count;

//   utst *utst_start;
//   utst *utst_end;
//   Longint utf8_strings_id;



//   Boolean debug_is_run;
//   Boolean debug_is_next;

//   Mvar *var_memory_start;
//   Mvar *var_memory_end;
//   Mpoint *pointer_memory_start;
//   Mpoint *pointer_memory_end;
//   Longint var_mem_id;
//   Longint var_mem_len;
//   Longint pointer_mem_id;
//   Longint pointer_mem_len;

//   int8 next_break_inst;
//   uint32 break_count;

//   rrss current;
//   //=>parsing global vars
//   Boolean need_inheritance;
//   //=>runtime global vars
//   String Rsrc;
//   Longint return_fin;
//   uint32 Rline;
//   Boolean is_stop_APP_controller, is_next_inst_running, is_occur_error_exception;
//   //=>list of all source paths
//   StrList sources_list;
//   uint32 sources_len;

//   StrList post_short_alloc;
//   uint32 post_short_alloc_len;

};
struct entry_table_struct entry_table;



#endif //__MAHDI_DATA_DEFINED_H

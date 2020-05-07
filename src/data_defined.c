

#include <Mahdi/system.h>

String interpreter_level = 0;

String program_root = 0;

String main_source_name = 0;

String interpreter_path = 0; //=>mahdi dir path, if not real mahdi
String interpreter_tmp_path = 0; //mahdi-root/tmp-dir
String os_separator = 0; //char_to_str(OS_SEPARATOR);
uint8 MAX_INT_LEN = 0;

uint8 MAX_FLOAT_LEN = 0;

uint8 max_estimate_divide_huge = 8;

uint8 max_float_estimate_huge_X0 = 4;

String new_line_char = "\n";

String os_tmp_dir = 0;

uint32 BufferSize = 4096;

String hostname = 0;

String os_version = 0;

String program_command=0;

Longint os_total_memory = 0; //in bytes
Longint os_total_disk = 0; //in bytes
Longint max_size_id = 0;

Boolean is_real_mahdi = false;

StrList program_argvs = 0;
uint32 argvs_len = 0;

//*************************defualt for config entries
int8 errors_mode = ERROR_ID;
int8 warnings_mode = WARNING_ID;
uint8 is_programmer_debug = 3; //0:no_debug,1:lower_debug(memory),2:medium_debug(parser),3:high_debug(sources,tokens)
uint8 max_steps_estimate_huge = 8;
uint32 max_decimal_has_huge = 10;
Boolean safe_mode = true;
Boolean optimize_mode = false;
Boolean overwrite_builtin_mode = false;
Boolean debug_mode = false;
String logfile_path = 0;
String bytecode_path = 0;
Boolean build_mode = false;
String buildfile_path = 0;
//*************************
String exceptions_group[] = {
    "ImportError",          //0 (parser)
    "MahpackError",         //1 (parser)
    "SyntaxError",          //2 (parser)
    "InterruptedError",     //3 (runtime)
    "ValueError",           //4 (runtime,parser)
    "NotExistError",        //5 (runtime)
    "RuntimeError",         //6 (runtime)
    "IOError",              //7 (runtime)
    "NotAccessError",       //8 (runtime)
    "OSError",              //9 (runtime)
    "OverflowError",        //10 (runtime)
    "TypeError",            //11 (runtime)
    "FloatingPointError",   //12 (runtime)
    "CommandError",         //13 (init)
    "DebuggerError",        //14 (runtime)
    "BuilderError"          //15 (runtime)
};
uint8 errcodes_len=MAX_ERROR_CODES;
String exceptions_type[4] = {"CANCEL", "FATAL", "ERROR", "WARNING"};

// for parsing
uint8 token_splitters[13] = {' ', '(', ')', '=', '[', ']', '{', '}', ';', ',',':','.','>'};

// String package_zones[2]={"@private","@public"};
// String method_attributes[2]={"override","static"};


String keywords[26] = {"func","class","package","override","static","true","false","if","elif","else","choose","and","or","not","next","break","loop","num","str","bool","lambda","manage","return","this","import","config"};
uint8 single_operators[7] = {'+', '-', '*', '/', '%', '^','|'};
// // String keywords_out[13] = {"func", "true", "false", "null", "if", "elif", "else", "loop", "manage", "next", "break","return", "import"};

// String block_instructions[6] = {"loop", "if", "elif", "else", "manage","choose"};

// //uint8 keywords_splitter[5] = {':', ' ', '{', '=', '('};


// String comparative_operators[6] = {"==", ">=", "<=", ">", "<", "!="};

// String alloc_operators[8] = {"+=", "-=", "*=", "/=", "%%=", "^=", ":=", "|="};

// String boolean_operators[2] = {"and", "or"};

// String basic_types[3] = {"string", "number", "boolean"};

// uint8 golden_bytes[] = {7, 11, 27, 127, 223};


// uint8 words_splitter[16] = {':', ' ', '{', '=', '(', ',', '.', '[', ']', '}', ')', ';','-','<','>','!'};

// uint8 sub_types[6] = {'b','s','u','i','f','h'};

// String control_chars[5] = {"\\n", "\\t", "\\", "\\\\", "\\b"};


// Mpoint *hash_pointers[HASH_MEM_SIZE] = {0};

// //=>list of imported modules path
// StrList installed_modules = 0;
// uint32 installed_modules_len = 0;

//*************************************************************
//*********************public functions************************
//*************************************************************

void DEF_init() {
  //=>init program root directory
  program_root = CALL_pwd();
  //=>init max_int ,max_float
  MAX_INT_LEN = INT_USED_BYTES * 2;
  MAX_FLOAT_LEN = (FLOAT_USED_BYTES * 2) - 2;
  //=>get mahdi path
  os_separator = CH_to_string(OS_SEPARATOR);
  
  //=>if main mahdi interpreter, not app host!
  if (is_real_mahdi) {
    //=>get tmp dir path of mahdi interpreter
    interpreter_tmp_path = PATH_join(COM_get_Mahdi_dir_path(),"tmp");
    //=>check for exist tmp dir of mahdi interpreter
    if (fopen(PATH_join(interpreter_tmp_path, "TMPDIR"), "r") == NULL) {
      CALL_mkdir(interpreter_tmp_path,true);
      fopen(PATH_join(interpreter_tmp_path, "TMPDIR"), "w");
    }
  }
  //=>init packages list
  entry_table.pack_start = 0;
  entry_table.pack_end = 0;
  entry_table.pack_id = 1;
  //=>init program package sources
  entry_table.program_package_id = 0;
  entry_table.program_sources = 0;
  entry_table.program_sources_len = 0;
  //=>append program package to packages list
  entry_table.program_package_id = _pack_init(entry_table.program_package);
  //=>no need to inherit level,YET!
  entry_table.need_inheritance = false;
  // debug("fffff:%s\n%s\n%s\n",interpreter_path,interpreter_tmp_path,project_root);
  //=>init import sources list
  entry_table.imso_start = 0;
  entry_table.imso_end = 0;
  entry_table.import_id = 1;
  //=>init data types list
  entry_table.datas_start = 0;
  entry_table.datas_end = 0;
  entry_table.datas_id = 1;
  //=>init function headers list
  entry_table.fuhs_start = 0;
  entry_table.fuhs_end = 0;
  entry_table.func_id = 1;
  //=>init basic data_types
  _datas_append(BASIC_DATA_TYPE,"str",0,0);
  _datas_append(BASIC_DATA_TYPE,"num",0,0);
  _datas_append(BASIC_DATA_TYPE,"bool",0,0);
  _datas_append(BASIC_DATA_TYPE,"lambda",0,0);

}
//*************************************************************
//*******************source_code functions*********************
//*************************************************************
void _soco_append(uint8 type, uint32 line,String code,Longint source_id) {
  //=>init vars
  soco *q;
  if(!(q = (soco *) COM_alloc_memory(sizeof(soco)))) return ;
  //=>assign items
  q->line = line;
  STR_init(&q->code, code);
  q->source_id = source_id;
  q->next = 0;
  //soco_main
  if (type == MAIN_SOURCE_CODE) {
    if (entry_table.soco_main_start == 0) {
      entry_table.soco_main_start = entry_table.soco_main_end = q;
    } else {
      entry_table.soco_main_end->next = q;
      entry_table.soco_main_end = q;
    }
    entry_table.soco_main_count++;
  }
  //soco tokens
  else if (type == TOKENS_SOURCE_CODE) {
    if (entry_table.soco_tokens_start == 0)
      entry_table.soco_tokens_start = entry_table.soco_tokens_end = q;
    else {
      entry_table.soco_tokens_end->next = q;
      entry_table.soco_tokens_end = q;
    }
    entry_table.soco_tokens_count++;
  }
}

//*************************************************************
void _soco_clear(uint8 type) {
  //soco_main
  if (type == MAIN_SOURCE_CODE && entry_table.soco_main_start > 0) {
    entry_table.soco_main_count = 0;
    soco *tmp1;
    entry_table.soco_main_end = entry_table.soco_main_start;
    entry_table.soco_main_start = 0;
    for (;;) {
      tmp1 = entry_table.soco_main_end;
      entry_table.soco_main_end = entry_table.soco_main_end->next;
      free(tmp1);
      if (entry_table.soco_main_end == 0) break;
    }
  } else if (type == TOKENS_SOURCE_CODE && entry_table.soco_tokens_start > 0) {
    entry_table.soco_tokens_count = 0;
    soco *tmp1;
    entry_table.soco_tokens_end = entry_table.soco_tokens_start;
    entry_table.soco_tokens_start = 0;
    for (;;) {
      tmp1 = entry_table.soco_tokens_end;
      entry_table.soco_tokens_end = entry_table.soco_tokens_end->next;
      free(tmp1);
      if (entry_table.soco_tokens_end == 0) break;
    }
  }
}
//*************************************************************
soco _soco_get(uint8 type, uint32 ind) {
  soco ret = {0, 0, 0};
  uint32 ii = 0;
  soco *tmp1;
  //soco_main
  if (type == MAIN_SOURCE_CODE) {
    tmp1 = entry_table.soco_main_start;
  }
    //soco_tokens
  else if (type == TOKENS_SOURCE_CODE) {
    tmp1 = entry_table.soco_tokens_start;
  }
  for (;;) {
    if (ii++ == ind) {
      ret = *tmp1;
      break;
    }
    tmp1 = tmp1->next;
    if (tmp1 == 0) break;
  }

  return ret;
}
//*************************************************************
//******************utf8_strings functions*********************
//*************************************************************
void _utst_append(utst s) {
  utst *q;
  if(!(q = (utst *) COM_alloc_memory(sizeof(utst)))) return ;
  //=>assign items
  q->id = s.id;
  q->max_bytes_per_char = s.max_bytes_per_char;
  USTR_init(&q->utf8_string, s.utf8_string);
  q->line = s.line;
  q->next = 0;
  //=>set node pointers
  if (entry_table.utst_start == 0)
    entry_table.utst_start = entry_table.utst_end = q;
  else {
    entry_table.utst_end->next = q;
    entry_table.utst_end = q;
  }
}
//*************************************************************
Longint _utst_add(uint32 line, UString str, uint8 max_bytes) {
  if (max_bytes == 0)max_bytes = USTR_max_bytes(str, false);
  utst tmp1 = {++entry_table.utf8_strings_id, line, str, max_bytes};
  _utst_append(tmp1);
  return entry_table.utf8_strings_id;
}
//*************************************************************
utst _utst_get_by_label(String s) {
  utst ret = {0, 0, 0, 0,0};
  Longint uid = STR_to_Longint(STR_substring(s, UTF8_ID_LBL_LEN, 0));
  if (uid == 0)return ret;
  utst *tmp1 = entry_table.utst_start;
  for (;;) {
    if (tmp1->id == uid) {
      return (*tmp1);
    }
    tmp1 = tmp1->next;
    if (tmp1 == 0) break;
  }
  return ret;
}

//*************************************************************
//***********************map functions*************************
//*************************************************************
void _map_push(map **map_start,map **map_end, String key,String value) {
  //=>search for key in map
  map *st = (*map_start);
  if (st != 0){
    for (;;) {
      if (STR_equal(st->key, key)){
        SLIST_append(&st->items,value,st->items_len++);
        return;
      }
      st = st->next;
      if (st == 0) break;
    }
  }
  //=>if not exist, append it to map!
  map *q;
  if(!(q = (map *) COM_alloc_memory(sizeof(map)))) return ;

  STR_init(&q->key, key);
  q->items = 0;
  q->items_len = 0;
  SLIST_append(&q->items,value,q->items_len++);

  q->next = 0;

  if ((*map_start) == 0) {
    (*map_start) = (*map_end) = q;
  } else {
    (*map_end)->next = q;
    (*map_end) = q;
  }
}
//*************************************************************
uint32 _map_get_items(map *map_start,String key,StrList *items) {
  map *st = map_start;
  if (st == 0) return 0;
  for (;;) {
    if (STR_equal(st->key, key)){
      SLIST_init(items,st->items,st->items_len);
      return st->items_len;
    }
    st = st->next;
    if (st == 0) break;
  }
  return 0;
}
//*************************************************************
String _map_get_first_item(map *map_start,String key) {
  map *st = map_start;
  if (st == 0) return 0;
  for (;;) {
    if (STR_equal(st->key, key)){
      if(st->items_len>0) return st->items[0];
      return 0;
    }
    st = st->next;
    if (st == 0) break;
  }
  return 0;
}
//*************************************************************
map _map_index(map *map_start,uint32 ind) {
  map *st = map_start;
  map null={0,0,0};
  uint32 index=0;
  if (st == 0) return null;
  for (;;) {
    if (index==ind)return *(st);
    index++;
    st = st->next;
    if (st == 0) break;
  }
  return null;
}
//*************************************************************
String _map_print(map *map_start){
  map *st = map_start;
  if (st == 0) return 0;
  String ret="<";
  for (;;) {
    ret=STR_multi_append(ret," ",st->key,": ",SLIST_print(st->items,st->items_len)," ",0);
    st = st->next;
    if (st == 0) break;
    ret=CH_append(ret,',');
  }
  return CH_append(ret,'>');
}

//*************************************************************
//*********************packages functions**********************
//*************************************************************
Longint _pack_init(String pack_name){
  pack *q;
  if(!(q = (pack *) COM_alloc_memory(sizeof(pack)))) return 0;
  q->id = ++entry_table.pack_id;

  STR_init(&q->name, pack_name);
  q->next = 0;
  if (entry_table.pack_start == 0)
    entry_table.pack_start = entry_table.pack_end = q;
  else {
    entry_table.pack_end->next = q;
    entry_table.pack_end = q;
  }
  return entry_table.pack_id;
}
//*************************************************************
//*******************data_types functions**********************
//*************************************************************
Longint _datas_append(uint8 type,String name,Longint pack_id,String inherit) {
  datas *q;
  if(!(q = (datas *) COM_alloc_memory(sizeof(datas)))) return 0;
  q->id = ++entry_table.datas_id;

  q->type = type;
  STR_init(&q->name, name);
  q->pack_id = pack_id;
  STR_init(&q->inherit, inherit);
  q->next = 0;
  if (entry_table.datas_start == 0)
    entry_table.datas_start = entry_table.datas_end = q;
  else {
    entry_table.datas_end->next = q;
    entry_table.datas_end = q;
  }
  return entry_table.datas_id;
}
//*************************************************************
// datas _datas_search(String name,Longint id,Boolean name_or_id) {
//   datas null = {0, 0, 0, 0, 0};
//   //printf("!!!!!SSSSS:%s\n",name);
//   datas *st = entry_table.datas_start;
//   if (st == 0) return null;
//   for (;;) {
//     if (name_or_id && STR_equal(st->name, name)) return (*st);
//     else if (!name_or_id && st->id==id) return (*st);
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }
//*************************************************************
//***************function headers functions********************
//*************************************************************
Longint _fuhs_append(Longint pack_id,Longint class_id,String name,StrList params,uint32 params_len,IntList attrs,uint32 line,Longint source_id){
  fuhs *q;
  if(!(q = (fuhs *) COM_alloc_memory(sizeof(fuhs)))) return 0;
  q->id = ++entry_table.func_id;

  q->pack_id = pack_id;
  q->class_id = class_id;
  STR_init(&q->name, name);
  SLIST_init(&q->params,params,params_len);
  q->params_len = params_len;
  q->is_simplified = false;
  ILIST_init(&q->func_attrs,attrs,MAX_FUNCTION_ATTRIBUTES);
  q->param_types = 0;
  q->param_defaults = 0;
  q->line = line;
  q->source_id = source_id;

  q->next = 0;
  if (entry_table.fuhs_start == 0)
    entry_table.fuhs_start = entry_table.fuhs_end = q;
  else {
    entry_table.fuhs_end->next = q;
    entry_table.fuhs_end = q;
  }

  return entry_table.func_id;
}


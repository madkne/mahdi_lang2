

#include <Mahdi/system.h>

String interpreter_level = 0;

String project_root = 0;

String program_package = 0;

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
uint8 is_programmer_debug = 2;
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


// String package_zones[2]={"@private","@public"};
// String method_attributes[2]={"override","static"};


// String keywords[26] = {"func","pack","override","static","true","false","if","elif","else","choose","and","or","not","next","break","loop","def","number","string","boolean","manage","return","self","this","import","config"};

// // String keywords_out[13] = {"func", "true", "false", "null", "if", "elif", "else", "loop", "manage", "next", "break","return", "import"};

// String block_instructions[6] = {"loop", "if", "elif", "else", "manage","choose"};

// //uint8 keywords_splitter[5] = {':', ' ', '{', '=', '('};
// uint8 single_operators[7] = {'+', '-', '*', '/', '%', '^','|'};

// String comparative_operators[6] = {"==", ">=", "<=", ">", "<", "!="};

// String alloc_operators[8] = {"+=", "-=", "*=", "/=", "%%=", "^=", ":=", "|="};

// String boolean_operators[2] = {"and", "or"};

// String basic_types[3] = {"string", "number", "boolean"};

// uint8 golden_bytes[] = {7, 11, 27, 127, 223};

// uint8 token_splitters[11] = {' ', '(', ')', '=', '[', ']', '{', '}', ';', ',',':'};

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
  //=>init project_root
  project_root = CALL_pwd();
  //=>init max_int ,max_float
  MAX_INT_LEN = INT_USED_BYTES * 2;
  MAX_FLOAT_LEN = (FLOAT_USED_BYTES * 2) - 2;
  //=>get mahdi path
  os_separator = CH_to_string(OS_SEPARATOR);
  
  //=>if main mahdi interpreter, not app host!
  if (is_real_mahdi) {
    //=>get tmp dir path of mahdi interpreter
    interpreter_tmp_path = STR_multi_append(COM_get_Mahdi_dir_path(), os_separator, "tmp", os_separator, 0, 0);
    //=>check for exist tmp dir of mahdi interpreter
    if (fopen(STR_append(interpreter_tmp_path, "TMPDIR"), "r") == NULL) {
      CALL_mkdir(interpreter_tmp_path,true);
      fopen(STR_append(interpreter_tmp_path, "TMPDIR"), "w");
    }
  }
//   // printf("fffff:%s\n%s\n%s\n",interpreter_path,interpreter_tmp_path,project_root);
//   //=>init mahdi_modules_instance
//   for (uint32 i = 0; i < max_mahdi_modules_instance_len; i++) {
//     mahdi_modules_instance[i] = 0;
//   }
//   //=>init import struct
//   entry_table.import_start = 0;
//   entry_table.import_id = 1;
//   entry_table.import_active_count = 0;
//   //=>init config struct
//   entry_table.config_start=0;
//   entry_table.config_end=0;
//   entry_table.config_id=1;
//   //=>init utf8 struct
//   entry_table.utst_start = 0;
//   entry_table.utf8_strings_id = 1;
//   //=>init source code struct
//   entry_table.soco_main_count = 0;
//   entry_table.soco_tokens_count = 0;
//   entry_table.soco_tokens_start = 0;

}

// //*************************************************************
// //***************predefined_methods functions******************
// //*************************************************************
// prme predefined_methods[8]={
//   {1,"_init_","unknown",0},
//   {2,"_plus_","package","package"},
//   {3,"_minus_","package","package"},
//   {4,"_len_",0,"number"},
//   {5,"_str_",0,"string"},
//   {6,"_equal_","package","boolean"},
//   {7,"_empty_",0,"boolean"},
//   {8,"_del_",0,0},
// };
// //*************************************************************
// int32 _prme_search(String funcname){
//   uint32 len=(sizeof(predefined_methods)/sizeof(prme));
//   for (uint32 i = 0; i < len; i++){
//     prme tmp=predefined_methods[i];
//     if(STR_equal(tmp.name,funcname)) return i;
//   }
//   return -1;
// }
// //*************************************************************
// //*******************config_inst functions*********************
// //*************************************************************
// Longint _coin_append(String type,String name,String value,uint32 line,uint32 source_index) {
//   coin *q;
//   q = (coin *) malloc(sizeof(coin));
//   if (q == 0) return 0;
//   q->id = ++entry_table.config_id;
//   STR_init(&q->name,name);
//   STR_init(&q->value,value);
//   STR_init(&q->type,type);
//   q->line = line;
//   q->source_index = source_index;
//   q->next = 0;
//   if (entry_table.config_start == 0) {
//     entry_table.config_start = entry_table.config_end = q;
//   } else {
//     entry_table.config_end->next = q;
//     entry_table.config_end = q;
//   }
//   return entry_table.config_id;
// }
// //*************************************************************
// //*******************source_code functions*********************
// //*************************************************************
// void _soco_append(uint8 type, uint32 line,String code) {
//   soco *q;
//   q = (soco *) malloc(sizeof(soco));
//   if (q == 0) return;
//   q->line = line;
//   STR_init(&q->code, code);
//   q->next = 0;
//   //soco_main
//   if (type == MAIN_SOURCE_CODE) {
//     //printf("QW!!!:%s,%i,%s\n", s.code, entry_table.soco_main_start, q->code);
//     if (entry_table.soco_main_start == 0) {
//       entry_table.soco_main_start = entry_table.soco_main_end = q;
//     } else {
//       entry_table.soco_main_end->next = q;
//       entry_table.soco_main_end = q;
//     }
//     entry_table.soco_main_count++;
//   }
//     //soco tokens
//   else if (type == TOKENS_SOURCE_CODE) {
//     if (entry_table.soco_tokens_start == 0)
//       entry_table.soco_tokens_start = entry_table.soco_tokens_end = q;
//     else {
//       entry_table.soco_tokens_end->next = q;
//       entry_table.soco_tokens_end = q;
//     }
//     entry_table.soco_tokens_count++;
//   }
// }

// //*************************************************************
// void _soco_clear(uint8 type) {
//   //soco_main
//   if (type == MAIN_SOURCE_CODE && entry_table.soco_main_start > 0) {
//     entry_table.soco_main_count = 0;
//     soco *tmp1;
//     entry_table.soco_main_end = entry_table.soco_main_start;
//     entry_table.soco_main_start = 0;
//     for (;;) {
//       tmp1 = entry_table.soco_main_end;
//       entry_table.soco_main_end = entry_table.soco_main_end->next;
//       free(tmp1);
//       if (entry_table.soco_main_end == 0) break;
//     }
//   } else if (type == TOKENS_SOURCE_CODE && entry_table.soco_tokens_start > 0) {
//     entry_table.soco_tokens_count = 0;
//     soco *tmp1;
//     entry_table.soco_tokens_end = entry_table.soco_tokens_start;
//     entry_table.soco_tokens_start = 0;
//     for (;;) {
//       tmp1 = entry_table.soco_tokens_end;
//       entry_table.soco_tokens_end = entry_table.soco_tokens_end->next;
//       free(tmp1);
//       if (entry_table.soco_tokens_end == 0) break;
//     }
//   }
// }
// //*************************************************************
// soco _soco_get(uint8 type, uint32 ind) {
//   soco ret = {0, 0, 0};
//   uint32 ii = 0;
//   soco *tmp1;
//   //soco_main
//   if (type == MAIN_SOURCE_CODE) {
//     tmp1 = entry_table.soco_main_start;
//   }
//     //soco_tokens
//   else if (type == TOKENS_SOURCE_CODE) {
//     tmp1 = entry_table.soco_tokens_start;
//   }
//   for (;;) {
//     if (ii++ == ind) {
//       ret = *tmp1;
//       break;
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }

//   return ret;
// }
// //*************************************************************
// //***********************map functions*************************
// //*************************************************************
// void _map_push(map **map_start,map **map_end, String key,String value) {
//   map *q;
//   q = (map *) malloc(sizeof(map));
//   if (q == 0) return;
//   STR_init(&q->key, key);
//   STR_init(&q->value, value);
//   q->next = 0;
//   if ((*map_start) == 0) {
//     (*map_start) = (*map_end) = q;
//   } else {
//     (*map_end)->next = q;
//     (*map_end) = q;
//   }
// }
// //*************************************************************
// String _map_get(map *map_start,String key) {
//   map *st = map_start;
//   if (st == 0) return 0;
//   for (;;) {
//     if (STR_equal(st->key, key)) return st->value;
//     st = st->next;
//     if (st == 0) break;
//   }
//   return 0;
// }
// //*************************************************************
// map _map_index(map *map_start,uint32 ind) {
//   map *st = map_start;
//   map null={0,0,0};
//   uint32 index=0;
//   if (st == 0) return null;
//   for (;;) {
//     if (index==ind)return *(st);
//     index++;
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// String _map_print(map *map_start){
//   map *st = map_start;
//   if (st == 0) return 0;
//   String ret="{";
//   for (;;) {
//     ret=STR_multi_append(ret," ",st->key,": \"",st->value,"\" ");
//     st = st->next;
//     if (st == 0) break;
//     ret=CH_append(ret,',');
//   }
//   return CH_append(ret,'}');
// }
// //*************************************************************
// map _map_popleft(map **map_start,map **map_end){
//   map ret = {0, 0, 0};
//   map *tmp1 = (*map_start);
//   if (tmp1 == 0) return ret;
//   ret.key = (*tmp1).key;
//   ret.value = (*tmp1).value;
//   //=>if exist just one item
//   if ((*map_start)->next==0) {
//     free(tmp1);
//     (*map_start) = (*map_end) = 0;
//   }
//   //=>else exist more items
//   else {
//     (*map_start)=(*map_start)->next;
//     free(tmp1);
//   }
//   return ret;
// }
// //*************************************************************
// //***************stru_to_in_struct functions*******************
// //*************************************************************
// void _stoi_empty(stoi s[], uint32 size) {
//   for (uint32 i = 0; i < size; i++) {
//     s[i].id = 0;
//     s[i].is_active = false;
//     s[i].is_inline = false;
//     s[i].stru_pars = 0;
//   }
// }
// //*************************************************************
// //****************block_structures functions*******************
// //*************************************************************
// void _blst_append(blst s) {
//   blst *q;
//   q = (blst *) malloc(sizeof(blst));
//   if (q == 0) return;
//   q->func_id = s.func_id;
//   q->stru_id = s.stru_id;
//   q->pack_id=s.pack_id;
//   q->type = s.type;
//   q->line = s.line;
//   q->is_simplified=s.is_simplified;
//   q->source_id = s.source_id;
//   q->params_len = s.params_len;
//   q->func_attrs=0;
//   q->inherit=0;
//   q->params=0;
//   STR_init(&q->label, s.label);
//   SLIST_init(&q->params, s.params, s.params_len);
//   q->next = 0;
//   //blst_func
//   if (s.type == FUNC_BLOCK_ID) {
//     q->id = ++entry_table.func_id;
//     ILIST_init(&q->func_attrs,s.func_attrs,MAX_FUNCTION_ATTRIBUTES);
    
//     if (entry_table.blst_func_start == 0)
//       entry_table.blst_func_start = entry_table.blst_func_end = q;
//     else {
//       entry_table.blst_func_end->next = q;
//       entry_table.blst_func_end = q;
//     }
//   }
//   //blst_pack
//   else if (s.type == PACK_BLOCK_ID) {
//     STR_init(&q->inherit, s.inherit);
//     q->id = ++entry_table.pack_id;
//     if (entry_table.blst_pack_start == 0)
//       entry_table.blst_pack_start = entry_table.blst_pack_end = q;
//     else {
//       entry_table.blst_pack_end->next = q;
//       entry_table.blst_pack_end = q;
//     }
//   }
//   //blst_stru
//   else {
//     q->id = ++entry_table.stru_id;
//     if (entry_table.blst_stru_start == 0)
//       entry_table.blst_stru_start = entry_table.blst_stru_end = q;
//     else {
//       entry_table.blst_stru_end->next = q;
//       entry_table.blst_stru_end = q;
//     }
//   }
// }
// //*************************************************************
// blst *_blst_filter(blst *start,uint8 type,Longint pack_id,Longint func_id){
//   //=>init vars
//   blst *filter_start=0;
//   blst *filter_end=0;
//   if (start == 0) return 0;
//   for (;;) {
//       if(start->type==type && start->pack_id==pack_id && (func_id==0 || start->func_id==func_id)){
//           blst *q;
//           q = (blst *) malloc(sizeof(blst));
//           if (q == 0) return 0;
//           q->id=start->id;
//           q->pack_id=start->pack_id;
//           q->func_id=start->func_id;
//           q->stru_id=start->stru_id;
//           q->type=start->type;
//           STR_init(&q->label,start->label);
//           STR_init(&q->inherit,start->inherit);
//           SLIST_init(&q->params,start->params,start->params_len);
//           q->params_len=start->params_len;
//           q->is_simplified=start->is_simplified;
//           ILIST_init(&q->func_attrs,start->func_attrs,MAX_FUNCTION_ATTRIBUTES);

//           q->line=start->line;
//           q->source_id=start->source_id;
//           q->next = 0;
//           if (filter_start == 0)
//             filter_start = filter_end = q;
//           else {
//             filter_end->next = q;
//             filter_end = q;
//           }
//       } 
//       start = start->next;
//       if (start == 0) break;
//   }
//   return filter_start;
// }
// //*************************************************************
// void _blst_print(String head,blst *blst_start){
//   blst *st = blst_start;
//   if (st == 0) return;
//   printf("BLST[%s]:\n",head);
//   for (;;) {
//     printf("\t[id:%li,typ:%i,pid:%li,fid:%li,sid:%li]:%s:%s\t%s[line:%i]\n",st->id, st->type,st->pack_id,st->func_id, st->stru_id,ILIST_print(st->func_attrs,MAX_FUNCTION_ATTRIBUTES),st->label,SLIST_print(st->params,st->params_len),st->line);
//     st = st->next;
//     if (st == 0) break;
//   }
//   printf("---------------------\n");
// }
// //*************************************************************
// blst * _blst_delete_by_id(Longint id,blst *blst_start,Boolean *is_success) {
//   (*is_success)=false;
//   blst *last_node=0;
//   if (blst_start == 0)return 0;
//   blst *tmp1 = blst_start;
//   if (tmp1 == 0) return 0;
//   for (;;) {
//     if(tmp1->id==id){
//       //=>if just one node
//       if(tmp1->next==0 && last_node==0){
//         blst_start=0;
//       }
//       //=>if last node
//       if(tmp1->next==0){
//         last_node->next=0;
//       }
//       //=>if first node
//       else if(tmp1==blst_start){
//         blst_start=tmp1->next;
//       }
//       //=>if middle node
//       else{
//         last_node->next=tmp1->next;
//       }
//       free(tmp1);
//       (*is_success)=true;
//       break;
//     }
//     last_node=tmp1;
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return blst_start;
// }
// //*************************************************************
// blst _blst_get_by_id(blst *start,Longint id) {
//   blst null = {0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0};
//   blst *tmp1 = start;
//   //------------------
//   for (;;) {
//     if (id == tmp1->id) {
//       return (*tmp1);
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// //*******************data_types functions**********************
// //*************************************************************
// void _datas_append(Longint pack_id,uint8 type,String name) {
//   datas *q;
//   q = (datas *) malloc(sizeof(datas));
//   if (q == 0) return;
//   q->id = ++entry_table.datas_id;

//   q->type = type;
//   q->pack_id=pack_id;
//   STR_init(&q->name, name);
//   q->next = 0;
//   if (entry_table.datas_start == 0)
//     entry_table.datas_start = entry_table.datas_end = q;
//   else {
//     entry_table.datas_end->next = q;
//     entry_table.datas_end = q;
//   }
// }
// //*************************************************************
// datas _datas_search(String name,Longint pack_id,Boolean name_or_packid) {
//   datas null = {0, 0, 0, 0, 0};
//   //printf("!!!!!SSSSS:%s\n",name);
//   datas *st = entry_table.datas_start;
//   if (st == 0) return null;
//   for (;;) {
//     if (name_or_packid && STR_equal(st->name, name)) return (*st);
//     else if (!name_or_packid && st->pack_id==pack_id) return (*st);
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// //***************instructions_order functions******************
// //*************************************************************
// void _inor_append(inor s) {
//   inor *q;
//   q = (inor *) malloc(sizeof(inor));
//   if (q == 0) return;
//   q->pid=s.pid;
//   q->fid = s.fid;
//   q->sid = s.sid;
//   q->order = s.order;
//   q->next = 0;
//   entry_table.inor_count++;
//   if (entry_table.inor_start == 0) {
//     entry_table.inor_start = entry_table.inor_end = q;
//   } else {
//     entry_table.inor_end->next = q;
//     entry_table.inor_end = q;
//   }
// }

// //*************************************************************
// uint32 _inor_get(Longint pid, Longint fid, Longint sid) {
//   inor *tmp1 = entry_table.inor_start;
//   if (tmp1 == 0) return 0;
//   for (;;) {
//     if (tmp1->pid == pid && tmp1->fid == fid && tmp1->sid == sid) {
//       return tmp1->order;
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return 0;
// }

// //*************************************************************
// void _inor_set(Longint pid, Longint fid, Longint sid, uint32 order) {
//   //=>init vars
//   uint32 index = 0;
//   Boolean is_exist = false;
//   //search and check for exist
//   inor *tmp1 = entry_table.inor_start;
//   if (tmp1 != 0) {
//     for (;;) {
//       index++;
//       if (tmp1->pid==pid && tmp1->fid == fid && tmp1->sid == sid) {
//         is_exist = true;
//         break;
//       }
//       tmp1 = tmp1->next;
//       if (tmp1 == 0) break;
//     }
//   }
//   //=>set order if not exist
//   if (!is_exist) {
//     inor tmp2 = {pid,fid, sid, order, 0};
//     _inor_append(tmp2);
//   } 
//   //=>if exist, just update its
//   else {
//     uint32 ind = 0;
//     inor *tmp1 = entry_table.inor_start;
//     for (;;) {
//       ind++;
//       if (ind == index) {
//         tmp1->order = order;
//         break;
//       }
//       tmp1 = tmp1->next;
//       if (tmp1 == 0) break;
//     }
//   }
// }

// //*************************************************************
// //******************instructions functions*********************
// //*************************************************************
// void _instru_append(instru s) {
//   instru *q;
//   q = (instru *) malloc(sizeof(instru));
//   if (q == 0) return;
//   q->id = entry_table.inst_id++;
//   q->pack_id=s.pack_id;
//   q->func_id = s.func_id;
//   q->stru_id = s.stru_id;
//   q->order = s.order;
//   q->line = s.line;
//   q->type = s.type;
//   q->source_id = s.source_id;
//   STR_init(&q->code, s.code);
//   q->next = 0;
//   if (entry_table.instru_start == 0)
//     entry_table.instru_start = entry_table.instru_end = q;
//   else {
//     entry_table.instru_end->next = q;
//     entry_table.instru_end = q;
//   }
// }
// //*************************************************************
// instru _instru_get_by_id(Longint id) {
//   instru null = {0, 0, 0, 0, 0, 0, 0, 0,0,0};
//   instru *st = entry_table.instru_start;
//   if (st == 0) return null;
//   for (;;) {
//     if (st->id == id) {
//       return (*st);
//     }
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// //*****************inherit_package functions*******************
// //*************************************************************
// void _inpk_append(Longint parent_id,String parent_name,Longint inherit_id,String inherit_name) {
//   inpk *q;
//   q = (inpk *) malloc(sizeof(inpk));
//   if (q == 0) return;
//   q->parent_id=parent_id;
//   q->inherit_id = inherit_id;
//   q->is_done=false;
//   q->is_processing=false;
//   STR_init(&q->inherit_name,inherit_name);
//   STR_init(&q->parent_name,parent_name);
//   q->next = 0;
//   entry_table.inpk_id++;
//   if (entry_table.inpk_start == 0) {
//     entry_table.inpk_start = entry_table.inpk_end = q;
//   } else {
//     entry_table.inpk_end->next = q;
//     entry_table.inpk_end = q;
//   }
// }
// //*************************************************************
// inpk _inpk_get_by_done(Boolean is_done) {
//   inpk null = {0, 0, 0, 0, 0,0};
//   inpk *st = entry_table.inpk_start;
//   if (st == 0) return null;
//   for (;;) {
//       if(!st->is_processing && st->is_done==is_done){
//           return (*st);
//       }
//       st = st->next;
//       if (st == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// Boolean _inpk_set_done(Longint inherit_id) {
//   inpk *st = entry_table.inpk_start;
//   if (st == 0) return false;
//   for (;;) {
//       if(st->inherit_id==inherit_id){
//           st->is_done=true;
//           st->is_processing=false;
//           return true;
//       }
//       st = st->next;
//       if (st == 0) break;
//   }
//   return false;
// }
// //*************************************************************
// Boolean _inpk_set_processing(Longint inherit_id) {
//   inpk *st = entry_table.inpk_start;
//   if (st == 0) return false;
//   for (;;) {
//       if(!st->is_processing && st->inherit_id==inherit_id){
//           st->is_processing=true;
//           return true;
//       }
//       st = st->next;
//       if (st == 0) break;
//   }
//   return false;
// }
// //*************************************************************
// inpk _inpk_search(Longint inherit_id,Longint parent_id,Boolean parent_or_not) {
//   inpk null = {0, 0, 0, 0, 0,0};
//   inpk *st = entry_table.inpk_start;
//   if (st == 0) return null;
//   for (;;) {
//       if(!st->is_processing && !parent_or_not && st->inherit_id==inherit_id){
//           return (*st);
//       } else if(!st->is_processing && parent_or_not && st->parent_id==parent_id){
//           return (*st);
//       }
//       st = st->next;
//       if (st == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// //****************func_pack_params functions*******************
// //*************************************************************
// void _fpp_append(fpp s) {
//   fpp *q;
//   q = (fpp *) malloc(sizeof(fpp));
//   if (q == 0) return;
//   q->id=entry_table.fpp_id++;
//   q->type = s.type;
//   q->refid=s.refid;
//   q->porder=s.porder;
//   q->is_private=s.is_private;
//   q->is_static=s.is_static;
//   q->is_reference=s.is_reference;
//   q->line=s.line;
//   q->source_id=s.source_id;
//   STR_init(&q->pname, s.pname);
//   STR_init(&q->ptype, s.ptype);
//   STR_init(&q->pvalue, s.pvalue);
//   q->next = 0;
//   if (entry_table.fpp_start == 0)
//     entry_table.fpp_start = entry_table.fpp_end = q;
//   else {
//     entry_table.fpp_end->next = q;
//     entry_table.fpp_end = q;
//   }
// }
// //*************************************************************
// /**
//  * get type and refid and collect all parameters of a function or attributres of a package, create a new linked list and return its start pointer
//  * @author madkne
//  * @version 1.1
//  * @since 2020.1.1
//  */ 
// fpp *_fpp_filter(uint8 type,Longint refid){
//   //=>init vars
//   fpp *filter_start=0;
//   fpp *filter_end=0;
//   fpp *st = entry_table.fpp_start;
//   if (st == 0) return 0;
//   for (;;) {
//       if(st->type==type && st->refid==refid){
//           fpp *q;
//           q = (fpp *) malloc(sizeof(fpp));
//           if (q == 0) return 0;
//           q->id=st->id;
//           q->type = st->type;
//           q->refid=st->refid;
//           q->porder=st->porder;
//           q->is_private=st->is_private;
//           q->is_static=st->is_static;
//           q->is_reference=st->is_reference;
//           q->line=st->line;
//           q->source_id=st->source_id;
//           STR_init(&q->pname, st->pname);
//           STR_init(&q->ptype, st->ptype);
//           STR_init(&q->pvalue, st->pvalue);
//           q->next = 0;
//           if (filter_start == 0)
//             filter_start = filter_end = q;
//           else {
//             filter_end->next = q;
//             filter_end = q;
//           }
//       } 
//       st = st->next;
//       if (st == 0) break;
//   }
//   return filter_start;
// }
// //*************************************************************
// void _fpp_print(String head,fpp *fpp_start){
//   fpp *st = fpp_start;
//   if (st == 0) return;
//   printf("FPP[%s]:\n",head);
//   for (;;) {
//     printf("\t[id:%li,typ:%i,refid:%li,ord:%i]:%s|%s|%s\t[priv:%i,stat:%i,ref:%i,line:%i]\n",st->id, st->type,st->refid,st->porder, st->pname,st->ptype,st->pvalue,st->is_private,st->is_static,st->is_reference,st->line);
//     st = st->next;
//     if (st == 0) break;
//   }
//   printf("---------------------\n");
// }
// //*************************************************************
// Boolean _fpp_change_by_id(Longint id,String field,String value){
//   fpp *st = entry_table.fpp_start;
//   if (st == 0) return false;
//   for (;;) {
//     if(st->id==id){
//       if(STR_equal(field,"pname")){
//         STR_init(&st->pname,value);
//         return true;
//       }else if(STR_equal(field,"ptype")){
//         STR_init(&st->ptype,value);
//         return true;
//       }else if(STR_equal(field,"pvalue")){
//         STR_init(&st->pvalue,value);
//         return true;
//       }
//       break;
//     }
//     st = st->next;
//     if (st == 0) break;
//   }
//   return false;

// }
// //*************************************************************
// fpp * _fpp_delete_by_id(Longint id,fpp *fpp_start,Boolean *is_success) {
//   (*is_success)=false;
//   fpp *last_node=0;
//   if (fpp_start == 0)return 0;
//   fpp *tmp1 = fpp_start;
//   if (tmp1 == 0) return 0;
//   for (;;) {
//     if(tmp1->id==id){
//       //=>if just one node
//       if(tmp1->next==0 && last_node==0){
//         fpp_start=0;
//       }
//       //=>if last node
//       if(tmp1->next==0){
//         last_node->next=0;
//       }
//       //=>if first node
//       else if(tmp1==fpp_start){
//         fpp_start=tmp1->next;
//       }
//       //=>if middle node
//       else{
//         last_node->next=tmp1->next;
//       }
//       free(tmp1);
//       (*is_success)=true;
//       break;
//     }
//     last_node=tmp1;
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return fpp_start;
// }
// //*************************************************************
// //******************utf8_strings functions*********************
// //*************************************************************
// void _utst_append(utst s) {
//   utst *q;
//   q = (utst *) malloc(sizeof(utst));
//   if (q == 0) return;
//   q->id = s.id;
//   q->max_bytes_per_char = s.max_bytes_per_char;
//   USTR_init(&q->utf8_string, s.utf8_string);
//   q->line = s.line;
//   q->next = 0;
//   if (entry_table.utst_start == 0)
//     entry_table.utst_start = entry_table.utst_end = q;
//   else {
//     entry_table.utst_end->next = q;
//     entry_table.utst_end = q;
//   }
// }
// //*************************************************************
// Longint _utst_add(uint32 line, UString str, uint8 max_bytes) {
//   if (max_bytes == 0)max_bytes = USTR_max_bytes(str, false);
//   utst tmp1 = {++entry_table.utf8_strings_id, line, str, max_bytes};
//   _utst_append(tmp1);
//   return entry_table.utf8_strings_id;
// }
// //*************************************************************
// utst _utst_get_by_label(String s) {
//   utst ret = {0, 0, 0, 0,0};
//   Longint uid = STR_to_Longint(STR_substring(s, UTF8_ID_LBL_LEN, 0));
//   if (uid == 0)return ret;
//   utst *tmp1 = entry_table.utst_start;
//   for (;;) {
//     if (tmp1->id == uid) {
//       return (*tmp1);
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return ret;
// }
// //*************************************************************
// //**************record_runtime_states functions****************
// //*************************************************************
// void _rrss_append(rrss s) {
//   rrss *q;
//   q = (rrss *) malloc(sizeof(rrss));
//   if (q == 0) return;
//   q->id=++entry_table.rrss_id;
//   q->pid=s.pid;
//   q->pin=s.pin;
//   q->sid = s.sid;
//   q->fid = s.fid;
//   q->fin = s.fin;
//   q->parent_rrss = s.parent_rrss;
//   q->order = s.order;
//   q->next = 0;
//   if (entry_table.rrss_start == 0) {
//     entry_table.rrss_start = entry_table.rrss_end = q;
//   } else {
//     entry_table.rrss_end->next = q;
//     entry_table.rrss_end = q;
//   }
// }
// //*************************************************************
// rrss _rrss_get_by_fin(Longint fin){
//   rrss null={0,0,0,0,0,0,0,0,0};
//   rrss *st = entry_table.rrss_start;
//   if (st == 0) return null;
//   for (;;) {
//     if(st->fin==fin){
//       return (*st);
//     }
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// rrss _rrss_null(){
//   rrss null = {0, 0, 0, 0, 0,0,0,0,0};
//   return null;
// }
// //*************************************************************
// //**************modules_packs_funcs functions******************
// //*************************************************************
// Boolean _mpfu_append(uint32 mod_id,uint32 pack_id,String func_name,Boolean is_static,String params_name,String params_type,String params_default,String params_ref,uint32 params_len,String returns_type,uint32 returns_len) {
//   //=>init vars
//   mpfu *q;
//   StrList prefs=0;

//   q = (mpfu *) malloc(sizeof(mpfu));
//   if (q == 0) return false;
//   q->mod_id = mod_id;
//   q->pack_id=pack_id;
//   STR_init(&q->func_name, func_name);
//   q->is_static=is_static;
//   if(CH_split(params_name,';',&q->params_name,true)!=params_len) return false;
//   if(CH_split(params_type,';',&q->params_type,true)!=params_len) return false;
//   if(CH_split(params_default,';',&q->params_default,false)!=params_len) return false;
//   if(CH_split(params_ref,';',&prefs,true)!=params_len) return false;
//   for (uint32  i = 0; i < params_len; i++){
//     ILIST_append(&q->params_ref,STR_to_int32(prefs[i]),i);
//   }
//   q->params_len = params_len;
//   if(CH_split(returns_type,';',&q->returns_type,true)!=params_len) return false;
//   q->returns_len = returns_len;
//   q->id = ++entry_table.mpfu_id;
//   q->next = 0;
//   if (entry_table.mpfu_start == 0) {
//     entry_table.mpfu_start = entry_table.mpfu_end = q;
//   } else {
//     entry_table.mpfu_end->next = q;
//     entry_table.mpfu_end = q;
//   }
//   return true;
// }







// //*************************************************************
// utst get_utst(long_int id) {
//   utst ret = {0, 0, 0, 0};
//   utst *tmp1 = entry_table.utst_start;
//   for (;;) {
//     if (tmp1->id == id) {
//       ret = *tmp1;
//       break;
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return ret;
// }
// //*************************************************************
// utst get_utst_by_string(String s) {
//   utst nil = {0, 0, 0};
//   uint32 len = str_length(s);
//   String val = 0;
//   if (len > 2 && s[0] == '\"' && s[len - 1] == '\"') {
//     val = str_substring(s, 1, len - 1);
//   } else {
//     str_init(&val, s);
//   }
//   //------------
// //   printf("OOOOO1:%s,%s,%i\n", s, val, str_is_int32(val));
//   if (str_is_int32(val)) {
//     int32 utst_id = str_to_int32(val);
// //    print_struct(PRINT_UTF8_ST);
// //    printf("OOOOOO2:%i\n", utst_id);
//     utst ut = get_utst((long_int) utst_id);//TODO:
//     return ut;
//     //printf("UTT:%s=>%s,%i\n", s, utf8_to_unicode_str(ut.utf8_string), ut.max_bytes_per_char);
//     //utf8_str_print("UTF8", ut.utf8_string, false);
//   } else
//     return nil;

// }


// //*************************************************************
// Boolean edit_soco(uint8 type, uint32 line, String new_data) {
//   soco *tmp1;
//   //soco_main
//   if (type == 1)tmp1 = entry_table.soco_main_start;
//     //soco_tokens
//   else if (type == 2)tmp1 = entry_table.soco_tokens_start;
//   for (;;) {
//     if (tmp1->line == line) {
//       (*tmp1).code = new_data;
//       return true;
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }

//   return false;
// }



// //*************************************************************
// blst search_lbl_func(String lbl, str_list params, uint32 par_len) {
//   blst null = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//   blst *tmp1;
//   tmp1 = entry_table.blst_func_start;
//   //------------------
//   for (;;) {
//     if (par_len == tmp1->params_len && str_equal(tmp1->lbl, lbl) &&
//         str_list_equal(tmp1->params, tmp1->params_len, params, par_len)) {
//       return (*tmp1);
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return null;
// }

// //*************************************************************
// blst search_lbl_stru(String lbl) {
//   blst null = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//   blst *tmp1;
//   tmp1 = entry_table.blst_stru_start;
//   if (lbl == 0 || lbl[0] != '@')return null;
//   //------------------
//   for (;;) {
//     if (str_equal(tmp1->lbl, lbl)) {
//       return (*tmp1);
//     }
//     tmp1 = tmp1->next;
//     if (tmp1 == 0) break;
//   }
//   return null;
// }



// //*************************************************************
// datas get_datas(long_int id) {
//   datas null = {0, 0, 0, 0, 0, 0};
//   datas *st = entry_table.datas_start;
//   if (st == 0) return null;
//   for (;;) {
//     if (st->id == id) return (*st);
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }






// //*************************************************************
// instru get_instru_by_params(long_int fid, long_int sid, uint32 order) {
//   instru null = {0, 0, 0, 0, 0, 0, 0, 0};
//   instru *st = entry_table.instru_start;
//   if (st == 0) return null;
//   for (;;) {
//     if (st->func_id == fid && st->stru_id == sid && st->order == order) {
//       return (*st);
//     }
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }
// //*************************************************************
// instru get_instru_by_source(String source_file, uint32 source_line) {
//   instru null = {0, 0, 0, 0, 0, 0, 0, 0};
//   instru *st = entry_table.instru_start;
//   if (st == 0) return null;
//   for (;;) {
//     if (st->line == source_line && str_equal(utf8_to_bytes_string(source_paths[st->source_id]), source_file)) {
//       return (*st);
//     }
//     st = st->next;
//     if (st == 0) break;
//   }
//   return null;
// }





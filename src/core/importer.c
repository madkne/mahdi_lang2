#include <Mahdi/system.h>



Boolean IMPORT_find_package_sources(){
    //=>init vars
    StrList sources = 0;
    StrList subdirs = 0;
    uint32 sources_len = 0;
    uint32 subdirs_len = 0;
    //=>get all files of program root
    sources_len = CALL_list_dir(program_root,'f',&sources);
    //=>get all files of sub_directories
    subdirs_len = CALL_list_dir(program_root,'d',&subdirs);
    //=>iterate all sub directories
    for(uint32 i = 0; i < subdirs_len; i++){
        StrList sub_sources = 0;
        uint32 sub_sources_len = CALL_list_dir(PATH_join(program_root,subdirs[i]),'f',&sub_sources);
        //=>append sub sources to sources list
        for (uint32 j = 0; j < sub_sources_len; j++){
            SLIST_append(&sources,PATH_join(subdirs[i],sub_sources[j]),sources_len++);
        }
    }

    //=>iterate and find source packages in all source files
    for (uint32 i = 0; i < sources_len; i++){
        //=>check for '.mah' extensions
        if(!STR_equal(PATH_extract_extension(sources[i]),"mah")) continue;
        // debug(sources[i]);
        String package_name = IMPORT_get_file_package(PATH_join(program_root, sources[i]));
        //=>check for same package name
        if(STR_equal(package_name,entry_table.program_package)){
            //=>append to program sources list
            SLIST_append(&entry_table.program_sources,sources[i],entry_table.program_sources_len++);
        }
    }
    
    // debug("all sources:%s \tdirs:[%s]",SLIST_print(sources,sources_len),SLIST_print(subdirs,subdirs_len));
    debug("program sources : %s",SLIST_print(entry_table.program_sources,entry_table.program_sources_len));

    // check if program sources is empty
    if(entry_table.program_sources_len == 0){
        EXP_print_error(0,"not_import_sources",0,entry_table.program_package,0,"IMPORT_find_package_sources");
        return false;
    }
    return true;
}
//******************************************************
String IMPORT_get_file_package(String path){
    // debug("path:%s",path);
    //=>check if file exist and open it
    FILE *fp = UTF_file_open(path, "r");
    if (fp == NULL){
        EXP_set_errcode(NOT_OPEN_FILE_ERRC);
        return 0;
    }
    //=>init vars
    int32 status = 1;
    Boolean is_multiple_comment = false;
    String package_name = 0;
    //=>read line by line until get EOF or error!
    while (status >= 0){
        //=>init vars
        UString chars;
        uint32 size = 0;
        String buffer = 0;
        //=>reading line by line from file in utf8
        status = UTF_read_line(fp, &chars, &size);
        // USTR_print("RRTT",chars,true);
        //=>if status code is -10 (can not read an utf8 char)
        if (status == -10){
            EXP_set_errcode(NOT_OPEN_FILE_ERRC);
            return 0;
        }
        //=>convert utf8 to ansi string
        String code_line = USTR_to_bytes_str(chars);
        //=>free memory every read line from file
        free(chars);
        //=>trim space code line
        code_line = STR_trim_space(code_line);
        //=>if line length after is null,then ignore it!
        if (code_line == 0) continue;
        //=>get line length
        uint32 line_size = STR_length(code_line);
        //=>iterate all line chars
        for (uint32 i = 0; i < line_size; i++){
            //=>check is line comment,then ignore it
            if (i + 1 < line_size && code_line[i] == '/' && code_line[i + 1] == '/'){
                break;
            }
            //=>check is multi line comments
            if (i + 1 < line_size){
                //=>if start multi comment with '/*'
                if (code_line[i] == '/' && code_line[i + 1] == '*'){
                    is_multiple_comment = true;
                }
                //=>if end multi comment with '*/'
                else if (code_line[i] == '*' && code_line[i + 1] == '/'){
                    is_multiple_comment = false;
                    i += 1;
                    continue;
                }
            }
            //=>if line is multi comment, then ignore
            if (is_multiple_comment) continue;
            //=>append char to buffer
            buffer = CH_append(buffer, code_line[i]);
        }
        //=>trim again buffer
        buffer = STR_trim_space(buffer);
        //=>if buffer is null, then ignore
        if (buffer == 0) continue;
        //=>check if buffer is package declaration
        if(STR_indexof(buffer,"package",0) != -1){
            //=>normalize line code
            String pkg_code = STR_trim_space(STR_substring(buffer,8,0));
            pkg_code = STR_trim_space(STR_replace(pkg_code,";",0,-1));
            //=>set package name
            STR_init(&package_name,pkg_code);
            // debug("package name:%s",pkg_code);
        }
        //=>just should read first code line of file to find package name!
        break;
    }
    //=>close file
    fclose(fp);

    return package_name;
}
//******************************************************
Boolean IMPORT_start(){

    //=>init vars
    uint32 success_imports = 0;
    //=>clear source code list
    _soco_clear(MAIN_SOURCE_CODE);
    //=>iterate all package source files
    for (uint32 i = 0; i < entry_table.program_sources_len; i++){
        //=>generate path from source
        String path = PATH_join(program_root,entry_table.program_sources[i]);
        //=>append source to import sources list and get its id
        Longint source_id = _imso_append('f',entry_table.program_package_id,path, 0, 0, 0, 0);
        //=>open file and fill soco struct
        if(IMPORT_open_file(path,source_id)){
            success_imports++;
        }
    }
    // if success import sources is less than program sources
    //TODO:
    //=>check if success import sources is zero!
    if(success_imports == 0) return false;

    return true;
}

//******************************************************
/**
 * get an import node struct by file type and fill source code and utf8 strings struct
 * @author madkne
 * @version 1.0
 * @since 2020.5.3
 * @param String path
 * @param Longint source_id
 * @return Boolean : if failed or success to complete read file
 */ 
Boolean IMPORT_open_file(String path,Longint source_id) {
    //=>check if file exist and open it
    FILE *fp = UTF_file_open(path, "r");
    if (fp == NULL){
        EXP_print_error(0, "not_open_file", 0, path,0, "IMPORT_open_file");
        return false;
    }
    //printf("WWWWWWWW:%s\n",ascii_path);
    //=>init vars
    int32 status = 1;
    Longint line_number = 0;
    Boolean is_multiple_comment = false;
    Boolean is_multiple_str = false;
    //=>used for multiline strings
    UString glob_buffer = 0, glob_collect = 0; 
    while (status >= 0){
        //=>init vars
        UString chars;
        uint32 size = 0;
        String optimize = 0;
        Boolean is_str = false;
        UString buffer = 0;
        UString collect = 0;
        uint8 max_bytes = 1;
        //----------------restore buffer,collect,is_str
        //=>if multiple string, then set before collected strings to buffer and set is_str
        if (is_multiple_str){
          is_multiple_str = false;
          is_str = true;
          USTR_init(&buffer, glob_buffer);
          USTR_init(&collect, glob_collect);
        }
        //=>reading line by line from file in utf8
        status = UTF_read_line(fp, &chars, &size);
        // USTR_print("RRTT",chars,true);
        //=>if status code is -10 (can not read an utf8 char)
        if (status == -10){
          EXP_print_error(0, "file_not_support_utf8", 0, path, "","IMPORT_open_file");
          return false;
        }
        //=>increase line number
        line_number++;
        //=>trim space code line
        UString code_line = USTR_trim_space(chars);
        //=>if line length after is null,then ignore it!
        if (code_line == 0){
            continue;
        }
        //=>get line length
        uint32 line_size = USTR_length(code_line);
        //=>iterate all line chars, detect utf8 strings
        for (uint32 i = 0; i < line_size; i++){
          //=>check if this line is can multi line string, if last line has '\'
          if (is_str && i + 1 == line_size && code_line[i] == '\\'){
            is_multiple_str = true;
            USTR_init(&glob_buffer,buffer);
            USTR_init(&glob_collect,collect);
            break;
          }
          //=>check is line comment,then ignore it
          if (!is_str && i + 1 < line_size && code_line[i] == '/' && code_line[i + 1] == '/'){
            break;
          }
          //=>check is multi line comments
          if (!is_str && i + 1 < line_size){
            //=>if start multi comment with '/*'
            if (code_line[i] == '/' && code_line[i + 1] == '*')
              is_multiple_comment = true;
            //=>if end multi comment with '*/'
            else if (code_line[i] == '*' && code_line[i + 1] == '/'){
              is_multiple_comment = false;
              i += 1;
              continue;
            }
          }
          //=>if line is multi comment, then ignore
          if (is_multiple_comment){
            continue;
          }
          //=>check line has string
          if ((code_line[i] == '\"' || code_line[i] == '\'') && (i == 0 || code_line[i - 1] != '\\')){
            //=>convert single quotation to double quotation
            if (code_line[i] == '\''){
              code_line[i] = '\"';
            }
            is_str = BOOL_switch(is_str);
            //=>if is string(start of string)
            if (is_str){
              max_bytes = 1;
              collect = 0;
              buffer = UCH_append(buffer, (uint32)'\"');
            }
            //=>if not string(end of string)
            else{
              //=>get max bytes needs per char of string
              max_bytes = USTR_max_bytes(collect, true);
              //printf("XXXX:%i,%s\n",max_bytes,utf8_to_bytes_string(collect));
              //=>if string is unicode and not english!
              if (max_bytes > 1){
                //=>add utf8 string to utst linkedlist and get its id
                Longint utf8_id = _utst_add(line_number, collect, max_bytes);
                collect = 0;
                UString ss;
                //=>generate a label replacement utf8 string by its id
                STR_to_utf8(&ss, STR_append(UTF8_ID_LABEL, STR_from_Longint(utf8_id)));
                //=>remove first quotation of string (just a utf8 label)
                buffer = USTR_substring(buffer, 0, USTR_length(buffer) - 1);
                buffer = USTR_append(buffer, ss);
                // printf("OOOO:%s\n",str_from_long_int(entry_table.utf8_strings_id));
              }
              //=>if string is english
              else{
                buffer = USTR_append(buffer, collect);
                collect = 0;
              }
            }
          }
          //printf("WW@@@:%c\n",code_line[i]);
          //=>if char of line is in string, append it! 
          if (is_str && (collect != 0 || code_line[i] != '\"')){
            collect = UCH_append(collect, code_line[i]);
            uint8 tmp12 = UTF_need_bytes((uint8)code_line[i]);
          }
          //=>if char of line is space and not in string, then ignore it
          if (!is_str && i > 0 && code_line[i - 1] == ' ' && code_line[i] == ' '){
            continue;
          }
          //=>if char is '"', then igonre it
          else if (code_line[i] == '\"' && max_bytes > 1) continue;
          //=>if char of line on in string, append it to buffer
          else if (!is_str){
            buffer = UCH_append(buffer, code_line[i]);
          }
        }
        //=>if not multiple string
        if (!is_multiple_str){
          //=>trim again buffer
          buffer = USTR_trim_space(buffer);
          //=>if buffer is null, then ignore
          if (buffer == 0) continue;
          //=>convert buffer to String
          for (uint32 i = 0; i < USTR_length(buffer); i++){
            //=>if still rest any utf8 char, then ERROR!
            if (!IS_ONE_BYTE(buffer[i])){
              // printf("ERR:%i\n", buffer[i]);
              EXP_print_error(line_number, "bad_place_using_utf8", 0, USTR_to_bytes_str(buffer), 0,"IMPORT_open_file");
              return false;
            }
            //=>convert utf8 chars to ascii chars
            optimize = CH_append(optimize, (uint8)buffer[i]);
          }
          // optimize=utf8_to_str(buffer);
          //=>store code line to source_code struct
          //utf8_str_print("Optimize",buffer,true);
          //printf("optimize:%s\n",optimize);
          _soco_append(MAIN_SOURCE_CODE,(uint32)line_number, optimize,source_id);
        }
        //=>free memory every read line from file
        free(chars);
    }
    //=>free memory related reading source file
    free(glob_buffer);
    free(glob_collect);
    //=>close file
    fclose(fp);
    //=>return success imported 
    return true;
}




//*************************************************************
//*******************import_inst functions*********************
//*************************************************************
Longint _imso_append(uint8 type,Longint pack_id,String path,StrList objects,uint32 objects_len,uint32 line,Longint source_id) {
  imso *q;
  if(!(q = (imso *) COM_alloc_memory(sizeof(imso)))) return 0;
  q->id = ++entry_table.import_id;
  q->type = type;
  q->pack_id = pack_id;
  STR_init(&q->path,path);
  q->line = line;
  SLIST_init(&q->objects,objects,objects_len);
  q->objects_len = objects_len;
  q->source_id = source_id;
  q->next = 0;
  if (entry_table.imso_start == 0) {
    entry_table.imso_start = entry_table.imso_end = q;
  } else {
    entry_table.imso_end->next = q;
    entry_table.imso_end = q;
  }

  return entry_table.import_id;
}
//*************************************************************
imso _imso_get(Longint id) {
  imso ret = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  imso *tmp1 = entry_table.imso_start;
  for (;;) {
    if (tmp1->id == id) {
      ret = *tmp1;
      break;
    }
    tmp1 = tmp1->next;
    if (tmp1 == 0) break;
  }
  return ret;
}

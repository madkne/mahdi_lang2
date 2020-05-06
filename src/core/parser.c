#include <Mahdi/system.h>


//=>global variables
Longint Aline = 0; //=>current line number
Longint Apath = 0; //=>current source id
String Spath = 0; //=>current source path
// Boolean is_in_func = false;
// Boolean is_in_class=false;
//=>detect and get tokens like '@private' in class
uint8 pack_zone=_PARSER_PUBLIC_METHOD_ATTR;
//=>get tokens like 'override','static' in class
int32 class_method_attrs[MAX_FUNCTION_ATTRIBUTES];
uint8 class_method_attrs_len=0;
//=>store end parse_pars count on end
// int8 end_of_class=false;
// int8 end_of_func=false;
uint16 parse_pars = 0;
// uint8 block_id = 0; //=>index of is_in_block
// Longint cur_class_id = 0;
// Longint cur_func_id = 0;
// Longint cur_block_id = 0;
// Longint cur_lambda_id = 0;
// Boolean is_inline_block = false;
cycle cycles[MAX_INTO_IN_STRUCTURES];
int32 cur_cycle = -1;
//******************************************************
/**
 * analyze and parse source code, first get its tokens and then analyze ana manage tokens, finally fill all parsing data structures like blst,imso,...
 * @author madkne
 * @version 1.1
 * @since 2020.5.3
 * @return Boolean : if success analyzing or faild
 */ 
Boolean PARSE_start(){
    //=>clear all tokens of source code
    _soco_clear(TOKENS_SOURCE_CODE);
    //=>get tokens of source code
    PARSE_get_tokens();
    //=>init vars
    uint8 state = _PARSER_PACKAGE_STATE;
    //=>insert first cycle
    _cycle_insert(0,0,0,0,false);
    //=>start parsing codes token by token
    for (uint32 i = 0; i < entry_table.soco_tokens_count; i++) {
        //=>get token
        soco token_item = _soco_get(TOKENS_SOURCE_CODE, i);
        //=>get code token and its line
        String Acode= 0;
        STR_init(&Acode,token_item.code);
        Aline = token_item.line;
        Apath = token_item.source_id;
        STR_init(&Spath , _imso_get(Apath).path);
        //=>count pars
        if (STR_CH_equal(Acode, '{')) {
            parse_pars++;
            //=>if in class, then set it
            if (state == _PARSER_CLASS_STATE) {
                // is_in_class = true;
                // end_of_class = parse_pars-1;
                state = _PARSER_PACKAGE_STATE;
            }
            // //=>if in function, then set it
            // else if (state == _PARSER_FUNC_STATE) {
            //     is_in_func = true;
            //     end_of_func = parse_pars-1;
            //     state = _PARSER_PACKAGE_STATE;
            // }
            // //=>if in block, then set it 
            // else if (state == _PARSER_BLOCK_STATE && block_id > 0) {
            //     /*is_in_stru[block_id - 1].is_active = true;
            //     is_in_stru[block_id - 1].stru_pars = parse_pars - 1;*/
            //     state = _PARSER_PACKAGE_STATE;
            // }
        } else if (STR_CH_equal(Acode, '}')) {
            parse_pars--;
            //=>if end of class
            if(cycles[cur_cycle].start_pars == parse_pars){
                //=>return back top cycle
                _cycle_remove();
            }
            //=>if end of function
            // if (end_of_func==parse_pars) {
            //     end_of_func=0;
            //     is_in_func = false;
            //     cur_func_id = cur_block_id = 0;
            // }
            //=>if end of structure
            // if (block_id > 0) {
                // uint8 c = block_id;
                // for (;;) {
                // c--;
                // //printf("FFFF:%i,%i\n",c,is_in_stru[0].stru_pars);
                // if (is_in_stru[c].is_active && is_in_stru[c].stru_pars == parse_pars) {
                //     is_in_stru[c].is_active = false;
                //     is_in_stru[c].stru_pars = 0;
                //     break;
                // }
                // if (c == 0) break;
                // }
                // cur_stru_id = PARSER_get_last_active_is_in_stru_id();
            // }
        }
        //=>if token is class keyword
        if (state == 0 && STR_equal(Acode, "class")) {
            //if in another class
            if (cycles[cur_cycle].class_id > 0) {
                String name = 0;
                STR_init(&name, _soco_get(TOKENS_SOURCE_CODE, i + 1).code);
                EXP_print_error(Aline, "define_class_in", Spath, name, 0, "PARSE_start");
                break;
            }
            //=>reset class vars
            pack_zone=_PARSER_PUBLIC_METHOD_ATTR;
            ILIST_reset(class_method_attrs,MAX_FUNCTION_ATTRIBUTES);
            class_method_attrs_len=0;
            state = _PARSER_CLASS_STATE;
            PARSE_manage_class(&i);
            continue;
        }
        //=>if is in a class and out of any functions
        // if(cur_class_id>0 && cur_func_id==0){
        //     Boolean exist=false;
        //     if(class_method_attrs_len==3) pack_method_attrs_len=0;
        //     //=>check for zone methods in package
        //     if(STR_equal(Acode,"@public")){
        //         class_zone = _PARSER_PUBLIC_METHOD_ATTR;
        //         exist=true;
        //     }else if(STR_equal(Acode,"@private")){
        //         class_zone = _PARSER_PRIVATE_METHOD_ATTR;
        //         exist=true;
        //     }
        //     //=>get method attributes
        //     else if(STR_equal(Acode,"override")){
        //         pack_method_attrs[pack_method_attrs_len++]=OVERRIDE_METHOD_FATTR;
        //         exist=true;
        //     }
        //     else if(STR_equal(Acode,"static")){
        //         pack_method_attrs[pack_method_attrs_len++]=STATIC_METHOD_FATTR;
        //         exist=true;
        //     }
        //     if(exist) continue;
        // }
        //=>if token is import keyword
        // if (state == 0 && STR_equal("import", Acode)) {
        //     i++;
        //     PARSER_manage_import(&i);
        //     continue;
        // }
        
        // //=>if token is func keyword
        // if (state == 0 && STR_equal(Acode, "func") && i + 3 < entry_table.soco_tokens_count) {
        //     //if is_in_func
        //     if (is_in_func) {
        //         String name = 0;
        //         STR_init(&name, _soco_get(TOKENS_SOURCE_CODE, i + 1).code);
        //         EXP_print_error(Aline, "define_func_in", entry_table.current_source_path, name, 0, "PARSER_analyze_source_code");
        //         break;
        //     }
        //     state = 1;
        //     i++;
        //     PARSER_manage_function(&i);
        //     continue;
        // }
        // //=>if token is a if,elif,loop,... keywords 
        // if (state == 0 && STR_search(block_instructions, Acode,StrArraySize(block_instructions))) {
        //     state = 2;
        //     i++;
        //     if (STR_equal(Acode, "else"))i--;
        //     is_inline_stru = false;
        //     PARSER_manage_structure(&i, Acode);
        //     //=>if stru is inline
        //     if (is_inline_stru) {
        //         is_in_stru[block_id - 1].is_inline = true;
        //         is_in_stru[block_id - 1].is_active = true;
        //         //        printf("FFDDDD:%s\n", Acode);
        //         state = 0;
        //     }
        //     continue;
        // }
        //=>if token is package attribute
        // if (state == 0 && is_in_pack && !is_in_func && STR_equal(Acode, "def") && i + 2 < entry_table.soco_tokens_count) {
        //     i++;
        //     PARSER_manage_package_attributes(&i);
        //     continue;
        // }
        //=>else if token is part of normal instructions
        // if (state == 0 && !STR_CH_equal(Acode, '{') && !STR_CH_equal(Acode, '}') && !STR_CH_equal(Acode, ';')) {
        //     PARSER_manage_instruction(&i);
        // }
        //=>manage inline stru
        // if (block_id > 0 && !STR_CH_equal(Acode, ';')) {
        // uint8 c = block_id;
        // for (;;) {
        //     c--;
        //     if (is_in_stru[c].is_inline && is_in_stru[c].is_active) {
        //     is_in_stru[c].is_active = false;
        //     is_in_stru[c].is_inline = false;
        //     //println("GGGG:", is_in_stru[c].id)
        //     break;
        //     }
        //     if (c == 0) break;
        // }
        // cur_stru_id = PARSER_get_last_active_is_in_stru_id();
        // }
    }

}


//******************************************************
/**
 * get i pointer of token index in source code and detect class header and append it to blst struct
 * @author madkne
 * @version 1.1
 * @since 2020.5.6
 * @param i : (pointer) index of token 
 * @return void
 */
void PARSE_manage_class(uint32 *i) {
    //=>init vars
    map *mapi = 0;
    // debug("class_pointer:%i",*i);
    //=>parse class header by regex
    mapi = PARSE_regex(i,_PARSER_CLASS_HEADER);
    // debug("class header: %s",_map_print(mapi));
    //=>get vars of class header
    String class_name = _map_get_first_item(mapi,"name");
    String class_inherit = _map_get_first_item(mapi,"parent");
    //=>verify class name
    if(class_name == 0 || !COM_is_valid_name(class_name,false)){
        EXP_print_error(Aline,"invalid_name_block",Spath,class_name,0,"PARSE_manage_class");
        return;
    }
    //=>if exist inherit class
    if(class_inherit != 0){
        entry_table.need_inheritance=true;
    }
    //=>append to datas struct
    _datas_append(CLASS_DATA_TYPE,class_name,class_inherit);
    
}
//******************************************************
map *PARSE_regex(uint32 *i,String pattern){
    //=>init vars
    StrList pat = 0;
    map *start = 0;
    map *end = 0;
    int32 pat_ind = -1;
    uint32 pat_ind_len = 0;
    uint8 pat_multiple_split = '0';
    Boolean pat_is_optional = false;
    Boolean next_pat_ind = true;
    String pat_var_name = 0;
    //=>split pattern items
    uint32 pat_len = COM_regex_pattern_splitter(pattern,&pat);
    //=>iterate from i index of tokens list
    for (; *i < entry_table.soco_tokens_count; (*i)++) {
        //=>if go to next pattern index
        if(next_pat_ind){
            //=>reset vars
            next_pat_ind = false;
            pat_multiple_split = '0';
            pat_is_optional = false;
            pat_var_name = 0;
            //=>if not have more items
            if(pat_ind+1 == pat_len) break;
            //=>increase pattern items index (next item)
            pat_ind++;
            //=>get length of pattern item
            pat_ind_len = STR_length(pat[pat_ind]);
            // debug("pat item:%s[%i/%i]",pat[pat_ind],pat_ind,pat_len);
            //=>check for pattern item (is var,is multiple var,..)
            if(pat[pat_ind][0] == '[' && pat[pat_ind][pat_ind_len-1] == ']'){
                //=>check is multiple var
                if(STR_indexof(pat[pat_ind],"*",0) != -1){
                    StrList ret = 0;
                    CH_split(pat[pat_ind],'*',&ret,false);
                    pat_var_name = STR_substring(ret[0],1,0);
                    pat_multiple_split = ret[1][0];
                }
                //=>check is optional var
                else if(STR_indexof(pat[pat_ind],"?",0) != -1){
                    pat_is_optional = true;
                    pat_var_name = STR_substring(pat[pat_ind],1,pat_ind_len-1);
                }
                //=>check is normal var
                else{
                    pat_var_name = STR_substring(pat[pat_ind],1,pat_ind_len-1);
                }
            }
        }
        //-----------------------
        //=>get token
        soco token_item = _soco_get(TOKENS_SOURCE_CODE, *i);
        //=>check if pattern item, is var!
        if(pat_var_name != 0){
            // debug("pat var:%s;%s (%i)",pat_var_name,token_item.code,*i);
            //=>if var is multiple
            if(pat_multiple_split != '0'){
                //=>check if pat item not have any matches
                if(pat_ind+1 < pat_len && STR_equal(pat[pat_ind+1],token_item.code)){
                    next_pat_ind = true;
                    (*i)--;
                }else{
                    String value = 0;
                    for (; *i < entry_table.soco_tokens_count; (*i)++) {
                        //=>get token
                        soco token_item = _soco_get(TOKENS_SOURCE_CODE, *i);
                        //=>check if is a splitter
                        if(STR_CH_equal(token_item.code,pat_multiple_split)){
                            break;
                        }
                        //=>check if match by next pat item
                        else if(pat_ind+1 < pat_len && STR_equal(pat[pat_ind+1],token_item.code)){
                            next_pat_ind = true;
                            (*i)--;
                            break;
                        }
                        //=>append tokens to value
                        value = STR_append(value,token_item.code);
                    }
                    //=>append value to map
                    _map_push(&start,&end,pat_var_name,value);
                    debug("var multiple:{%s}=%s",pat_var_name,value);
                }
                
            }
            //=>if var is optional
            else if(pat_is_optional){
                //=>check if match by next pat item
                if(pat_ind+1 < pat_len && STR_equal(pat[pat_ind+1],token_item.code)){
                    next_pat_ind = true;
                    (*i)--;
                }
                //=>append value to map
                else{
                    _map_push(&start,&end,pat_var_name,token_item.code);
                    debug("var optional:{%s}=%s",pat_var_name,token_item.code);
                }
            }
            //=>if var is normal
            else{
                //=>append value to map
                _map_push(&start,&end,pat_var_name,token_item.code);
                debug("var normal:{%s}=%s",pat_var_name,token_item.code);
                next_pat_ind = true;
            }
        }
        //=>if pattern item is exact string
        else if(STR_equal(pat[pat_ind],token_item.code)) {
            next_pat_ind = true;
            debug("exact:%s (%i)",token_item.code,*i);
        }
    }
    //=>return map struct list
    return start;
}
//******************************************************
/**
 * split every code line of main source code and append these as tokens, these tokens can parsed later!
 * @author madkne
 * @version 1.2
 * @since 2020.5.4
 * @return void
 */ 
void PARSE_get_tokens() {
    //=>init vars
    Boolean is_string = false, is_valid_func = false;
    String word = 0;
    int8 pars = 0, acol = 0, bras = 0; //pars:(),acol:{},bras:[]
    //=>iterate nodes of source code
    for (uint32 ii = 0; ii < entry_table.soco_main_count; ii++) {
        //=>get code line of source code
        soco source_code = _soco_get(MAIN_SOURCE_CODE, ii);
        //=>get code and line number
        String inst = source_code.code;
        uint32 line = source_code.line;
        Longint src_id = source_code.source_id;
        // debug("line:%i,code:%s",line,inst);
        acol = 0;
        //=>iterate code line chars
        for (uint32 i = 0; i < STR_length(inst); i++) {
            //=>check is string
            if (inst[i] == '\"' && (i == 0 || inst[i - 1] != '\\')) {
                is_string = BOOL_switch(is_string);
            }
            //=>if not in string
            if(!is_string){
                switch (inst[i]){
                    //=>count pars    
                    case '(':
                        pars++;
                        if (pars == 1) is_valid_func = false;
                        //=>if last word, is valid name, can be a function or class name
                        if (pars == 1 && entry_table.soco_tokens_count > 0 && COM_is_valid_name(word, false)) {
                            is_valid_func = true;
                        }
                        break;
                    case ')': pars--; break;
                    //=>count acol
                    case '{': acol++; break;
                    case '}': acol--; break;
                    //=>count bras
                    case '[': bras++; break;
                    case ']': bras--; break;
                }
            }
            //=>append to buffer and word
            if (!is_string && (CH_search(token_splitters, inst[i],ChArraySize(token_splitters)) || i + 1 == STR_length(inst))) {
                //=>get length of code line
                uint32 instlen=STR_length(inst);
                //=>simicolon is last word of an inst
                Boolean is_simi = false;
                //=>complete word at end of inst
                if (i + 1 == instlen && !CH_search(token_splitters, inst[i],ChArraySize(token_splitters))) {
                    word = CH_append(word, inst[i]);
                    is_simi = true;
                }
                //=>check if at end of a valid function name
                if (pars == 0 && is_valid_func && (inst[i] == ')')) {
                    is_simi = true;
                    is_valid_func = false;
                }
                //=>check if last char of inst is ),},]
                if (i + 1 == instlen && (inst[i] == ')' || inst[i] == '}' || inst[i] == ']') && pars == 0 && acol == 0) {
                    is_simi = true;
                }
                //=>trim word and if not null, append it as a token
                word = STR_trim_space(word);
                if (word != 0) {
                    _soco_append(TOKENS_SOURCE_CODE, line,word,src_id);
                }
                //=>append any separator char as a token
                if ((inst[i] != ' ' && i + 1 != instlen) ||
                    (i + 1 == instlen && CH_search(token_splitters, inst[i],ChArraySize(token_splitters)))) {
                    _soco_append(TOKENS_SOURCE_CODE, line,CH_to_string(inst[i]),src_id);
                }
                //=>if end of inst, then append a ';' as a token
                if (is_simi) {
                    _soco_append(TOKENS_SOURCE_CODE, line,";",src_id);
                }
                //**********************
                word = 0;
                continue;
            }
            //=>create a word until next char be a separator char like space,;,... 
            else {
                word = CH_append(word, inst[i]);
            }
        }
    }
}

//*************************************************************
//**********************cycle functions************************
//*************************************************************
void _cycle_insert(Longint class_id,Longint func_id,Longint lambda_id,Longint block_id,Boolean block_inline){
    //=>check for cycles index overflow
    if(cur_cycle+1 >= MAX_INTO_IN_STRUCTURES){
        //TODO:error
        return;
    }
    //=>init vars
    Longint parent_lambda_id;
    Longint parent_block_id;
    uint32 start_pars = parse_pars;
    //=>get parent info, if exist!
    if(cur_cycle >= 0){
        parent_block_id = cycles[cur_cycle].block_id;
        parent_lambda_id = cycles[cur_cycle].lambda_id;
    }
    //=>increase current cycles index
    cur_cycle++;
    //=>fill fields
    cycles[cur_cycle].class_id = class_id;
    cycles[cur_cycle].func_id = func_id;
    cycles[cur_cycle].parent_lambda_id = parent_lambda_id;
    cycles[cur_cycle].parent_block_id = parent_block_id;
    cycles[cur_cycle].lambda_id = lambda_id;
    cycles[cur_cycle].block_id = block_id;
    cycles[cur_cycle].block_inline = block_inline;
    cycles[cur_cycle].start_pars = start_pars;
}
//*************************************************************
void _cycle_remove(){
    //=>check for cycles index underflow
    if(cur_cycle-1 < 0){
        //TODO:error
        return;
    }
    //=>decrease current cycles index
    cur_cycle--;
}
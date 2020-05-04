#include <Mahdi/system.h>


//=>define parser regex expressions for parsing quickly codes
String parser_regex_expressions[7] = {
    "package[name]",
    "class[name]([parent?])",
    "[attrs* ]func[name]([params*,])",
    "[name]([params?])",
    "import[type]:[name*,]:[objects*,]",
    "config[name]=[value]",
    "[instruction];"
};
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
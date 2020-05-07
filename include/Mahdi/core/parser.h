//
// Created by madkne on 2020.5.3
//

#ifndef __MAHDI_PARSER_H
#define __MAHDI_PARSER_H  1


// -----------------------------
#define _PARSER_PACKAGE_STATEMENT       "package[name]"
#define _PARSER_CLASS_HEADER            "class[name]([parent?])"
#define _PARSER_FUNCTION_HEADER         "func[name]([params*,])"
#define _PARSER_BLOCK_HEADER            "[name]([params?])"
#define _PARSER_IMPORT_STATEMENT        "import[type]:[name*,]:[objects*,]"
#define _PARSER_CONFIG_STATEMENT        "config[name]=[value]"
#define _PARSER_INSTRUCTION_STATEMENT   "[instruction];"
// -----------------------------
#define _PARSER_PUBLIC_METHOD_ATTR      1
#define _PARSER_PRIVATE_METHOD_ATTR     2
#define _PARSER_OVERRIDE_METHOD_ATTR    3
#define _PARSER_STATIC_METHOD_ATTR      4
#define _PARSER_INIT_METHOD_ATTR        5
// -----------------------------
#define _PARSER_PACKAGE_STATE           0
#define _PARSER_CLASS_STATE             1
#define _PARSER_FUNC_STATE              2
#define _PARSER_BLOCK_STATE             3
#define _PARSER_LAMBDA_STATE            4
// -----------------------------
Boolean PARSE_start();
void PARSE_manage_class(uint32 *i);
void PARSE_manage_function(uint32 *i);
void PARSE_manage_import(uint32 *i);

void PARSE_get_tokens();
map *PARSE_regex(uint32 *i,String pattern,String end_str);

//*************************************************************
//**********************cycle functions************************
//*************************************************************
void _cycle_insert(Longint class_id,Longint func_id,Longint lambda_id,Longint block_id,Boolean block_inline);
void _cycle_remove();



#endif /*__MAHDI_PARSER_H*/
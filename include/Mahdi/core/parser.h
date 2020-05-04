//
// Created by madkne on 2020.5.3
//

#ifndef __MAHDI_PARSER_H
#define __MAHDI_PARSER_H  1

String parser_regex_expressions[7];
// -----------------------------
#define _PARSER_PACKAGE_STATEMENT       0
#define _PARSER_CLASS_HEADER            1
#define _PARSER_FUNCTION_HEADER         2
#define _PARSER_BLOCK_HEADER            3
#define _PARSER_IMPORT_STATEMENT        4
#define _PARSER_CONFIG_STATEMENT        5
#define _PARSER_INSTRUCTION_STATEMENT   6
// -----------------------------
Boolean PARSE_start();
void PARSE_get_tokens();



#endif /*__MAHDI_PARSER_H*/
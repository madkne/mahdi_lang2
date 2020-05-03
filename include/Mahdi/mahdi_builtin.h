
//
// Created by madkne on 2019.10.29
//

#ifndef __MAHDI_BUILTIN_H
#define __MAHDI_BUILTIN_H  1

void BUILT_init();
//******************************defines
#define _BUILT_LEN                1
#define _BUILT_TYPEOF             2
#define _BUILT_SUBTYPEOF          3
#define _BUILT_EXEC               4
#define _BUILT_RAISE              5
#define _BUILT_DEL                6
#define _BUILT_NIL                7
#define _BUILT_TOSTR              8
#define _BUILT_TONUM              9
#define _BUILT_ISNUM              10
#define _BUILT_ISARRAY            11
#define _BUILT_STACKPARAMS        12


//=>bifs functions
void _bifs_append(uint32 id,String func_name, String params);
bifs _bifs_get_by_name(String fname);

#endif /*__MAHDI_BUILTIN_H*/
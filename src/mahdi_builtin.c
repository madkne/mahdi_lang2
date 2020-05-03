#include <Mahdi/system.h>

//***********************************
void BUILT_init()
{
    _bifs_append(0, 0, 0);
    /**
   * a=true|'sample'|45.4|var[0]|{'a':0,'b':1}|[4,7,5] : value
   * aa=bool[?,..]|str[?,..]|num[?,..]|class[?,..] : var
   */
    //----------------------------------mahdi functions(builtins/mahdi)
    _bifs_append(_BUILT_LEN, "len", "aa"); //=>[..]
    _bifs_append(_BUILT_TYPEOF, "typeof", "aa"); //=>[..]
    _bifs_append(_BUILT_SUBTYPEOF, "subtypeof", "aa"); //=>[..]
    _bifs_append(_BUILT_EXEC, "exec", "str"); //=>[..]
    _bifs_append(_BUILT_RAISE, "raise", "str;num"); //[..]
    _bifs_append(_BUILT_DEL, "del", "aa"); //=>[..]
    _bifs_append(_BUILT_NIL, "nil", "aa"); //=>[..]
    _bifs_append(_BUILT_TOSTR, "tostr", "aa|a"); //=>[..]
    _bifs_append(_BUILT_TONUM, "tonum", "str"); //=>[..]
    _bifs_append(_BUILT_ISNUM, "isnum", "str"); //=>[..]
    _bifs_append(_BUILT_ISARRAY, "isarray", "aa|a"); //=>[..]
    _bifs_append(_BUILT_STACKPARAMS, "stackparams", 0); //=>[..]
}

//*************************************************************
//****************built_in_funcs functions*********************
//*************************************************************
void _bifs_append(uint32 id, String func_name, String params){
    //=>init vars
    bifs *q;
    uint8 par_len = 0, ret_len = 0;
    //=>get malloc
    if(!(q = (bifs *) COM_alloc_memory(sizeof(bifs)))) return;
    q->id = id;
    //=>get params count
    par_len = CH_search_count(params, ';',STR_length(params));
    q->params_len = par_len;
    STR_init(&q->func_name, func_name);
    STR_init(&q->params, params);
    q->next = 0;
    //entry_table.bifs_len++;
    if (entry_table.bifs_start == 0){
        entry_table.bifs_start = entry_table.bifs_end = q;
    }
    else{
        entry_table.bifs_end->next = q;
        entry_table.bifs_end = q;
    }
}
//*************************************************************
bifs _bifs_get_by_name(String fname){
    bifs null = {0, 0, 0, 0, 0};
    uint32 ii = 0;
    bifs *tmp1=entry_table.bifs_start;
    if(tmp1==0) return null;
    for (;;) {
        if (STR_equal(tmp1->func_name,fname)) {
            return (*tmp1);
        }
        tmp1 = tmp1->next;
        if (tmp1 == 0) break;
    }

    return null;
}

#include <Mahdi/system.h>

void VM_init()
{
    //=>init global memory vars states
    entry_table.var_memory_start = 0;
    //entry_table.pointer_memory_start = 0;
    entry_table.var_mem_id = 1;
    entry_table.pointer_mem_id = 5;
    entry_table.var_mem_len = 0;
    entry_table.pointer_mem_len = 0;
    //=>append first entry to mvar as null
    _mvar_append(0, 0, 0, 0, 0, 0, 0, 0, 0, false, 0, 0, 0);
    //=>append first entry to mvar as null
    _mpoint_append('0', 0, false, 0, 0, 0);
    //tmp return pointer vars
    //   Mpoint tmp3 = {RETURN_TMP_POINTER_ID, 0, 'v'};
    //   append_Mpoint(tmp3);
}

//*************************************************************
/**
 * display Mvar,Mpoint or both in console by details based on wh
 * @param wh {uint8}
 * @author madkne
 * @sinc 2020.5.2
 * @version 1.1
 */
void VM_show(uint8 wh){
    // if (wh == 40){
    //     wh = 0;
    // }
    //=>if not is programmer debug mode, then return
    if (is_programmer_debug == 0)
    {
        return;
    }
    //*************show var_memory
    printf("-------------------------\n");
    if (wh == 0 || wh == 1 || wh == 3)
    {
        printf("*****var_memory*****\n");
        for (Longint i = 0; i < entry_table.var_mem_len; i++)
        {
            Mvar st = _mvar_get(i);
            if (wh != 3 && st.name == 0)
            {
                continue;
            }
            printf("%i::VAR(id:%i,pack:%i,[fid:%i,fin:%i],[cid:%i,cin:%i],[lid:%i,lin:%i],bid:%i,pointer:%i,type:%i)\n\t%s,{flag:%c,private:%i}\n=====================\n", i, st.id,st.package_id, st.func_id, st.func_index, st.class_id, st.class_index, st.block_id, st.pointer_id, st.type_id, st.name, st.flag, st.is_private);
        }
    }
    //*************show pointer_memory
    if (wh == 0 || wh == 2)
    {
        printf("*****pointer_memory*****\n");
        for (uint32 i = 0; i < HASH_MEM_SIZE; i++)
        {
            if (hash_pointers[i] == 0)
                continue;
            Mpoint *tmp1 = hash_pointers[i];
            for (;;)
            {
                printf("%i::POINTER(id:%i,Type:%c)raw:%.50s;bool:%i,items_len:%li=>%s\n", i, tmp1->id, tmp1->type, tmp1->raw,tmp1->bool,(*tmp1).items_len,LLIST_print(tmp1->items,tmp1->items_len));
                tmp1 = tmp1->next;
                if (tmp1 == 0)
                    break;
            }
        }
    }
    printf("-------------------------\n");
}

//*************************************************************
//***********************mvar functions************************
//*************************************************************
/**
 * get all attributes of mvar except id, and create an entry in mvar linkedlist
 * @return success var_id {Longint} last entry id that added to mvar
 * @return faild 0
 * @author madkne
 * @since 2020.5.2
 * @version 1.0
 */
Longint _mvar_append(
    Longint package_id, Longint block_id, 
    Longint func_id, Longint func_index,
    Longint lambda_id,Longint lambda_index, 
    Longint class_id, Longint class_index, 
    Longint type_id, Boolean is_private, Longint pointer_id, uint8 flag, String name){
    //=>init vars
    Mvar *q = 0;
    if(!(q = (Mvar *) COM_alloc_memory(sizeof(Mvar)))) return 0;

    q->id = ++entry_table.var_mem_id;
    q->pointer_id = pointer_id;
    q->package_id = package_id;
    q->block_id = block_id;
    q->func_id = func_id;
    q->func_index = func_index;
    q->class_id = class_id;
    q->class_index = class_index;
    q->lambda_id = lambda_id;
    q->lambda_index = lambda_index;
    q->type_id = type_id;
    q->is_private = is_private;
    q->flag = flag;
    STR_init(&q->name, name);
    q->next = 0;
    entry_table.var_mem_len++;
    if (entry_table.var_memory_start == 0)
        entry_table.var_memory_start = entry_table.var_memory_end = q;
    else
    {
        entry_table.var_memory_end->next = q;
        entry_table.var_memory_end = q;
    }
    return entry_table.var_mem_id;
}
//*************************************************************
Mvar _mvar_get(Longint i){
    Mvar null = {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 , false, 0, 0, 0};
    Longint counter = 0;
    Mvar *tmp1 = entry_table.var_memory_start;
    for (;;)
    {
        if (i == counter)
            return (*tmp1);
        tmp1 = tmp1->next;
        counter++;
        if (tmp1 == 0)
            break;
    }
    return null;
}

//*************************************************************
//**********************mpoint functions***********************
//*************************************************************
uint32 _mpoint_hash_index(Longint id)
{
    return (uint32)(id % HASH_MEM_SIZE);
}
//*************************************************************
Longint _mpoint_append(uint8 type, String raw,Boolean bool,LintList items,StrList keys,Longint items_len)
{
    //create Mpoint struct
    Mpoint *q = 0;
    if(!(q = (Mpoint *) COM_alloc_memory(sizeof(Mpoint)))) return 0;

    q->id = ++entry_table.pointer_mem_id;
    q->type = type;
    STR_init(&q->raw, raw);
    q->bool = bool;
    
    LLIST_init(&q->items,items,items_len);
    // debug("gggg:%s\n",LLIST_print(q->items,items_len));
    SLIST_init(&q->keys,keys,items_len);
    q->items_len = items_len;
    q->next = 0;
    //get hash_pointers index
    uint32 hash_index = _mpoint_hash_index(q->id);
    //append to hash_pointers entry
    entry_table.pointer_mem_len++;
    if (hash_pointers[hash_index] == 0)
        hash_pointers[hash_index] = hash_pointers_end[hash_index] = q;
    else
    {
        hash_pointers_end[hash_index]->next = q;
        hash_pointers_end[hash_index] = q;
    }
    return entry_table.pointer_mem_id;
}

//*************************************************************
void _mpoint_delete(Longint id)
{
    Mpoint *first = 0;
    uint32 hash_index = _mpoint_hash_index(id);
    Mpoint *last = hash_pointers[hash_index];
    uint32 counter = 0;
    for (;;)
    {
        if (last->id == id)
        {
            Mpoint *next = last->next;
            free(last);
            if (counter == 0 || first == 0)
                hash_pointers[hash_index] = next; //if was first node
            else
                first->next = next;
            if (next == 0)
                hash_pointers_end[hash_index] = first; //if was last node
            break;
        }
        first = last;
        last = last->next;
        if (last == 0)
            break;
        counter++;
    }
    entry_table.pointer_mem_len--;
}

//*************************************************************
Mpoint _mpoint_get(Longint id)
{
    Mpoint null = {0, 0, 0, 0};
    uint32 hash_index = _mpoint_hash_index(id);
    Mpoint *tmp1 = hash_pointers[hash_index];
    //printf("!!!!!!:%i,%i,%i\n",id,hash_index,hash_pointers[hash_index]);
    if (tmp1 == 0)
        return null;
    for (;;)
    {
        if (id == tmp1->id)
            return (*tmp1);
        tmp1 = tmp1->next;
        if (tmp1 == 0)
            break;
    }
    return null;
}
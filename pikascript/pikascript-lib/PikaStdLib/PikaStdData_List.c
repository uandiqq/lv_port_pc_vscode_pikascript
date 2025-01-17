#include "PikaStdData_List.h"
#include "BaseObj.h"
#include "PikaObj.h"
#include "PikaStdData_Tuple.h"
#include "dataStrs.h"

void PikaStdData_List_append(PikaObj* self, Arg* arg) {
    __vm_List_append(self, arg);
}

void PikaStdData_List_set(PikaObj* self, int i, Arg* arg) {
    PikaList* list = obj_getPtr(self, "list");
    if (PIKA_RES_OK != list_setArg(list, i, arg)) {
        obj_setErrorCode(self, 1);
        obj_setSysOut(self, "Error: index exceeded lengh of list.");
    }
}

void PikaStdData_List___setitem__(PikaObj* self, Arg* __key, Arg* __val) {
    PikaStdData_List_set(self, obj_getInt(self, "__key"),
                         obj_getArg(self, "__val"));
}

void PikaStdData_List___init__(PikaObj* self) {
    __vm_List___init__(self);
}

char* PikaStdLib_SysObj_str(PikaObj* self, Arg* arg);
char* PikaStdData_List___str__(PikaObj* self) {
    Arg* str_arg = arg_newStr("[");
    PikaList* list = obj_getPtr(self, "list");

    int i = 0;
    while (PIKA_TRUE) {
        Arg* item = list_getArg(list, i);
        if (NULL == item) {
            break;
        }
        if (i != 0) {
            str_arg = arg_strAppend(str_arg, ", ");
        }
        char* item_str = PikaStdLib_SysObj_str(self, item);
        if (arg_getType(item) == ARG_TYPE_STRING) {
            str_arg = arg_strAppend(str_arg, "'");
        }
        str_arg = arg_strAppend(str_arg, item_str);
        if (arg_getType(item) == ARG_TYPE_STRING) {
            str_arg = arg_strAppend(str_arg, "'");
        }
        i++;
    }

    str_arg = arg_strAppend(str_arg, "]");
    obj_setStr(self, "_buf", arg_getStr(str_arg));
    arg_deinit(str_arg);
    return obj_getStr(self, "_buf");
}

void PikaStdData_List_reverse(PikaObj* self) {
    PikaList* list = obj_getPtr(self, "list");
    list_reverse(list);
}

PikaObj* PikaStdData_List___add__(PikaObj* self, PikaObj* others) {
    PikaObj* res = newNormalObj(New_PikaStdData_List);
    PikaStdData_List___init__(res);
    PikaList* list_res = obj_getPtr(res, "list");
    PikaList* list1 = obj_getPtr(self, "list");
    PikaList* list2 = obj_getPtr(others, "list");
    for (size_t i = 0; i < list_getSize(list1); i++) {
        Arg* arg = list_getArg(list1, i);
        list_append(list_res, arg);
    }
    for (size_t i = 0; i < list_getSize(list2); i++) {
        Arg* arg = list_getArg(list2, i);
        list_append(list_res, arg);
    }
    return res;
}

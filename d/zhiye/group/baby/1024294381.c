// automake group room , Mon Jun 17 14:58:34 2002
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","[1;37mÄı[1;35mÏã[1;37mÓ×ÖÉÔ°[0;0m");
set("long","ÕâÊÇÒ»Ëù[1;37màïàï[0;0m´´°ìµÄ[1;35mÓ×ÖÉÔ°[0;0m£¬Ğ¡ÅóÓÑÃÇÒªÈëÑ§£¬ÇëÏÈÌî±íµÇ¼Ç£¬²¢½»ÄÉ±¨
Ãû·ÑÒ»Ç§¶§[1;33m»Æ½ğ[0;0m»òÕßÒ»°ÙÕÅ[1;32mÒ¼ÇªÁ½ÒøÆ±[0;0m£¬ÁªÏµÈË£º[1;37mbaby[0;0m
    ¸½×¢£ºÈç±¨Ãû²»»ñÅú×¼£¬±¨Ãû·ÑË¡²»ÍË»¹¡£
[0;0m");
set("exits",([
"southeast":"/d/group/entry/hhshulin5.c","west":__DIR__"1024295444.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,"/d/group/obj/door.c":1,
]));
set("indoors","[1;37mÄı[1;35mÏã[1;37m¸ó[0;0m");
set("group1","baby");
set("group2","[1;37mÄı[1;35mÏã[1;37m¸ó[0;0m");
setup();
setup_var();
}

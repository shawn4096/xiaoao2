// automake group room , Mon Jun 17 23:07:46 2002
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","·¿¼ä");
set("long","ÕâÊÇÒ»×ù¸Õ¸Õ½¨ÔìºÃ£¬»¹Ã»ÓĞ·ÛË¢µÄ·¿Îİ¡£
");
set("exits",([
"down":__DIR__"1024325985.c",
]));
set("indoors","[1;37mÄı[1;35mÏã[1;37m¸ó[0;0m");
set("group1","baby");
set("group2","[1;37mÄı[1;35mÏã[1;37m¸ó[0;0m");
setup();
setup_var();
}

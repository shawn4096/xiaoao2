// automake group room , Mon Jun 17 23:04:28 2002
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","ʯ·");
set("long","����һ���ոս���ã���û�з�ˢ��ʯ·��
");
set("exits",([
"east":__DIR__"1024296001.c","up":__DIR__"1024326268.c",
]));
set("outdoors","[1;37m��[1;35m��[1;37m��[0;0m");
set("group1","baby");
set("group2","[1;37m��[1;35m��[1;37m��[0;0m");
setup();
setup_var();
}

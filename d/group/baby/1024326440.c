// automake group room , Mon Jun 17 23:07:46 2002
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","����");
set("long","����һ���ոս���ã���û�з�ˢ�ķ��ݡ�
");
set("exits",([
"down":__DIR__"1024325985.c",
]));
set("indoors","[1;37m��[1;35m��[1;37m��[0;0m");
set("group1","baby");
set("group2","[1;37m��[1;35m��[1;37m��[0;0m");
setup();
setup_var();
}

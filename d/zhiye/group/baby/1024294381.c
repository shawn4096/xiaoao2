// automake group room , Mon Jun 17 14:58:34 2002
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","[1;37m��[1;35m��[1;37m����԰[0;0m");
set("long","����һ��[1;37m����[0;0m�����[1;35m����԰[0;0m��С������Ҫ��ѧ���������Ǽǣ������ɱ�
����һǧ��[1;33m�ƽ�[0;0m����һ����[1;32mҼǪ����Ʊ[0;0m����ϵ�ˣ�[1;37mbaby[0;0m
    ��ע���籨��������׼��������ˡ���˻���
[0;0m");
set("exits",([
"southeast":"/d/group/entry/hhshulin5.c","west":__DIR__"1024295444.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,"/d/group/obj/door.c":1,
]));
set("indoors","[1;37m��[1;35m��[1;37m��[0;0m");
set("group1","baby");
set("group2","[1;37m��[1;35m��[1;37m��[0;0m");
setup();
setup_var();
}

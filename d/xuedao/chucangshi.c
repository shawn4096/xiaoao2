// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_yandu(string arg);
void create()
{
        set("short","������");
        set("long",@LONG
Ѫ���ŵĴ������֮�أ�ǽ�Ƕ�����������ף���֪�����ʲô
������һ�Ե�ľ�����ϰڷ��˲��ٵ���������˻ҳ���
LONG );
        set("exits",([
                "west"   : __DIR__"lingwushi",
                //"north" : __DIR__"shufang",
        ]));
       set("objects",([            
				"d/xuedao/obj/qingkejiudai"   : 1,
				"d/xuedao/obj/pinang"   : 1,
				"clone/weapon/tiejili"   : 5,
		   		"d/xuedao/obj/dusha"   : 1,

        ]));
	
        setup();
        replace_program(ROOM);
}

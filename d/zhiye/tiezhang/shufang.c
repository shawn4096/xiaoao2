//shufang.c �鷿
#include <ansi.h>

inherit ROOM;
void create()
{
          set("short","�鷿");
          set("long",@LONG
����һ���鷿�����ڳ������ڶ������徭������һЩ�����书�鼮���Թ�
���ư�����Ķ���
LONG
    );

           set("indoors","���ư�");
           set("exits",([
"south": __DIR__"zoulang-2",
]));

            set("objects",([
__DIR__"obj/brush_book": 1,
]));
            set("no_clean_up", 0);
            set("coor/x",-340);
  set("coor/y",-240);
   set("coor/z",10);
   setup();
}

int init()
{
	add_action("do_fan","search");

}
int do_fan(string arg)
{	
	object me=this_player();
	object book;
	if (me->query("family/family_name")!="���ư�"||!me->query("quest/tz/dichuan"))
	{
		return notify_fail("�㲢�����Ƶմ����ӣ������ư��ҷ�ʲô��\n");
	}
	if (!arg || arg!="�鼮")
	{
		return notify_fail("��Ҫ����ʲô��\n");
	}
	if (random(me->query("kar"))>25)
	{
	
		message_vision(HIC"$N�ߵ����ǰ�棬�Ӹ����书�ؼ��з���������ĳ��һ���飬����һ�������ķ���\n"NOR,me);
		book=new("d/tiezhang/obj/xinfa1");
		book->move(me);
		return 1;
	}else {

		message_vision(HIY"$N�������죬��Ȼ����һ���������ļ������н�������Ʒ��ĳ嶯��\n"NOR,me);
		me->start_busy(2);

		return 0;
	}

}
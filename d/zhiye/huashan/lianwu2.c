// Room: /d/huashan/lianwu2.c
// Date: Look 99/03/25
#include <ansi.h>
#include <room.h>
inherit ROOM;
int ning_come(object me);
void create()
{
        set("short", "���䳡");
        set("long", @LONG
���ǻ�ɽ�ɵ����䳡������ʯǽ�ϴ���һ�������ƺۼ�����ש�ѱ��ȳ�
һ������ӡ��
LONG
        );
        set("no_sleep_room","1");

	 set("objects",([
		__DIR__"npc/shidaizi" : 1,
	 ]));
        set("exits",([
		"south" : __DIR__"wuqiku",
		"west" : __DIR__"celang2",
	 ]));
	 set("outdoors", "��ɽ" );
        set("coor/x",100);
  set("coor/y",-10);
   set("coor/z",80);
   setup();
}

void init()
{ 
	object ning;
	object me=this_player();

    if (me->query_temp("wushuang/askning1"))
    {
		call_out("ning_come",5,me);
    }
}

int ning_come(object me)
{
        message_vision(HIC"$Nվ�����䳡���У�����һƬ�ռţ�ʩ����ʦ�������Ķ��̿�����,��ʱ��һ����ӰƮȻ������\n"NOR,me);
		if (!present("ning zhongze",environment(me)))
		{
			new("/d/huashan/npc/ningzhongze.c")->move(environment(me));
		}
		return 1;

}
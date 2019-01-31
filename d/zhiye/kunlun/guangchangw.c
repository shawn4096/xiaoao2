#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_strike(string arg);
void create()
{
	  set("short", "�㳡��");
	  set("long",@long
������һ��ƽƽ�����Ĵ�㳡���㳡���������ɵĵ�����ϰ�䣬������Ȼ
�ǹ㳡�������ȥ���������ˣ���������ɽ��·���������㳡���ϰڷ���һ
�ŵ�����׮(zhuang),������˺����޵棬�߲�½�룬�ƺ���͸�˲��ٵ���Ѫ
��Ȼ�����˾����ڴ���ϰȭ�����¡�
long);
	  set("exits",([
             "northeast" : __DIR__"shanlu04",
             "east" : __DIR__"guangchang",
          ]));
          set("objects",([
	       __DIR__"npc/kl-dizi3" :  1,
          ]));
        set("item_desc", ([
                "zhuang" : "һ�žŸ�����׮���ų�һ�ţ�����������Ӻ��޻���\n�е������ڻ�ȭ��da������Щ����׮��\n"]));

          set("outdoors", "����");
          setup();
}

void init()
{
	add_action("do_strike","cuff");
	add_action("do_strike","da");
}

int do_strike(string arg)
{
	object me=this_player();

	int level, jinglicost;

	level = me->query_skill("cuff", 1);
	if (!arg||arg!="zhuang")
		return notify_fail("��Ҫ����ʲô��\n");
	
	jinglicost = level / 3 + random(level / 3);
	
	if (me->query("jingli") <= jinglicost)
	{
			write("��̫���ˣ���ЪЪ�ɣ�\n");
			return 1;
	}
		me->receive_damage("jingli", jinglicost);
		if (level < 100) 
		{
			message_vision("$N���˿������������ƣ���ȭ������׮�ϻ�ȥ��\n", me);
			me->improve_skill("cuff", me->query_int() / 3);
		}
		else
			message_vision("$N΢һ�˾���������׮���ɣ����ľ׮��$P�����Ѿ��޷�����ˡ�\n", me);
		return 1;
}
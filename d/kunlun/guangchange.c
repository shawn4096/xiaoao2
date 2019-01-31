#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_tiao(string arg);

void create()
{
	  set("short", "�㳡��");
	  set("long",@long
������һ��ƽƽ�����Ĵ�㳡���㳡���������ɵĵ�����ϰ�䣬������Ȼ
�ǹ㳡�������ȥ���������ˣ���������ɽ��·���㳡һ�����������ߵʹ���
���ȵ�÷��׮(zhuang)����Ȼ�Ǹ����е�����ϰ�����ȷ�֮����
long);
	  set("exits",([
               "northwest" : __DIR__"shanlu04",
               "west" : __DIR__"guangchang",
          ]));
          set("objects",([
                CLASS_D("kunlun") + "/yulingzi" : 1,
				__DIR__"npc/kl-dizi3" :  2,
          ]));
		  set("item_desc", ([
                "zhuang" : "��÷��״������������һ��ľ׮��\n�е���������Щ׮����Ծ(tiao)��\n"]));

          set("outdoors", "����");
          setup();
}

void init()
{
	add_action("do_tiao","tiao");
	add_action("do_tiao","jump");
}

int do_tiao(string arg)
{
	object me=this_player();

	int level, jinglicost;

	level = me->query_skill("leg", 1);
	if (!arg||arg!="zhuang")
		return notify_fail("���ϴ�����Ҫ��ʲô��\n");
	
	jinglicost = level / 3 + random(level / 3);
	
	if (me->query("jingli") <= jinglicost)
	{
			write("��̫���ˣ���ЪЪ�ɣ�\n");
			return 1;
	}
		me->receive_damage("jingli", jinglicost);
		if (level < 100) 
		{
			message_vision("$N���˿���������÷��׮���ɵ͵�������һȦ���о������ȷ���Щ�ջ�\n", me);
			me->improve_skill("leg", me->query_int() / 4);
		}
		else
			message_vision("$N΢һ�˾�������Ծ��÷��׮�ϣ���ϧ��$P�����Ѿ��޷�����ˡ�\n", me);
		return 1;
}
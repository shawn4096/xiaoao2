// Room: /u/jpei/thd/njwest.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
����һ��С���������ڡ����Ӻ�С��������һƬ�ž��С��ϱ���Լ����
����һ���󽭡�
LONG
	);
	set("no_clean_up", 0);
	set("outdoors","ţ�Ҵ�");

	set("exits", ([
		"northwest": __DIR__"road2.c",
		"east": __DIR__"njroad1.c",
	]) );

   set("coor/x",80);
   set("coor/y",-360);
   set("coor/z",0);
   setup();
}


int init()
{
	object me,bing;
	me=this_player();
	if (me->query_temp("quest/���Ӣ�۴�/��ѩ����/yestongyin")) 
	{
		message_vision(YEL"��ʱ��$Nֻ������ӿ��һ��Ⱥʿ�������ڵ�����ɱ���ӣ�\n"NOR,me);
		message_vision(YEL"$N�ۼ��ֳ����ң���ͼȰ��(quanzu)��\n"NOR,me);

		if (!objectp(bing=present("song bing",this_object())))
		{
			bing=new("d/thd/niujia/npc/songbing");
			bing->move("d/thd/niujia/njwest");
		}
		me->set_temp("quest/���Ӣ�۴�/��ѩ����/findsongbing",1);
		me->delete_temp("quest/���Ӣ�۴�/��ѩ����/yestongyin");
		add_action("do_quanzu","quanzu");

	}
}
int do_quanzu()
{
	object me,bing;
	me=this_player();
	bing=present("song bing",this_object());
	if (!me->query_temp("quest/���Ӣ�۴�/��ѩ����/findsongbing")) 
	{
		return notify_fail("��ҪȰ��ʲô��\n");
	}
	message_vision(HIW"$N�����ĳ�������ͼȰ�����ֲб�����Ϊ��������Щ�α����������$N��\n"NOR,me);
	tell_object(me,HIG"\n\n��ֻ�о�����������Ϊ����˱��ɣ���Ȼ����������ɱ�ˣ����ɻ������ǣ����̶Խ������������\n"NOR); 
	bing->kill_ob(me);
	me->set_temp("quest/���Ӣ�۴�/��ѩ����/quanzu",1);
	call_out("do_check",10,me);
	return 1;
}
int do_check(object me)
{
	object bing;
	if (!me) return notify_fail("���α�����ɱ������ʧ�ܣ�\n");
	if (file_name(environment(me))!="/d/thd/niujia/njwest")
	{
		return notify_fail("��Ϊ�α������ϣ�ʵ�����ã��������ܣ�\n");
	}
	if (!objectp(bing=present("song bing",this_object())))
	{
		message_vision(HIC"��հ����Ϊ���������α�ɱ�������������СԺ���������ĵ�ŭ������\n"NOR,me);
		message_vision(HIC"���Ȼ��ʶ��������һ����һ����ı����Ҫ�Ͻ���ȥ����Ҫ������\n"NOR,me);
		message_vision(HIC"�����룬����һ���˾Ͷ�һ��������������Ȼ�����ˣ��躰�Ϲ����һ����֡���\n"NOR,me);
		me->set("quest/���Ӣ�۴�/��ѩ����/killsongbing",1);
		me->set_temp("quest/���Ӣ�۴�/��ѩ����/killsongbing",1);
		return 1;
	}
	
	call_out("do_check",1,me);
}

int valid_leave(object me, string dir)
{
       if (me->query_temp("quest/���Ӣ�۴�/��ѩ����/quanzu"))
       {
		   if (me->is_fighting())
			   return notify_fail(RED"\n�α������ȵ��������ߡ�һ����ס�㣬�㾹Ȼ�޷��뿪��\n"NOR);
		   if (present("song bing",this_object()))
			   return notify_fail(RED"\n�α������ȵ��������ߡ�һ����ס�㣬�㾹Ȼ�޷��뿪��\n"NOR);
			if(me->query_condition("killer")) 
			   return notify_fail(RED"\n��ô�����ģ��������wiz�ɡ�\n"NOR);
			return ::valid_leave(me, dir);
		}
		return 1;
}


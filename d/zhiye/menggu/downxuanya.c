// Room: /d/menggu/downxuanya.c

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "������");
	set("long", @LONG
���͵�ɽ�±���,Į���ຮ�ķ�ɳ��ʴ,ɽ�¸��ǹ⻬�վ�.������
��ƽƽ��ɽʯ�����,����ɫ��ɽʯ��������,ֱ������еİ������.
��ͷ��ɫ�Ĵ��Χ����ɽ�±ߵ�һ���������С����Ͽ�ȥ��ɽ�¶���
��Ϊ�վ���
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/baidiao.c" : 2,
]));
	set("outdoors", "menggu");
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
	 // "up" : __DIR__"xuanya1",
	  "east" : __DIR__"xiaolu",
	]));

	setup();
	replace_program(ROOM);
}

void init()
{
	object me;
	me=this_player();
	add_action("do_climb", "climb");
	if (me->query_temp("jyg/askma")
		&&me->query_temp("jyg/askstt"))
	{
		message_vision(HIC"$N�������������˵��ɽ���£����ϣ�ȴ��ɽ�¶��ͣ���Ϊ��Ҫ��\n"+
			"���в������ˤ�����¶�������Ը�ⰴ�����ڵ�����˵ȥ��ϰ�����ݾ���ô��(decide)\n"NOR,me);
		me->delete_temp("jyg/askma");
		me->delete_temp("jyg/askstt");
		me->set_temp("jyg/xuanyadown",1);
		add_action("do_decide","decide");
	}
}
int do_decide()
{
	object me;
	me=this_player();

	if (me->query_temp("jyg/xuanyadown"))
	{
		tell_object(this_player(),"�����������ϰ�������£�һ������������ݵİ��\n");
		me->set_temp("jyg/start",1);
		me->delete_temp("jyg/xuanyadown");
		me->start_busy(2);
	}
	return 1;
}

int do_climb(string arg)
{
	object me = this_player();
	int gain,cost;

	if(me->is_busy())
		return notify_fail("�㻹��æ���ء�\n");

	if( me->query_skill("dodge") < 135 && arg == "up" )
		return notify_fail("�����������¶���ڣ����Ṧ��������ôҲ������ȥ��\n");

	cost = ( 300-me->query_dex()*me->query_skill("dodge")/20 )/10;
	if ( cost<10 )cost = 10;
	cost = cost * 3;

	if( me->query("jing") < 30)
		return notify_fail("���۵�ʵ���������ˡ�\n");

	me->start_busy( 1 );

	me->add("jing",-cost);

	if( arg != "up" )
		return notify_fail("���Ѿ�վ��ɽ�µ��£��Ǹ�����û������\n");

	gain = me->query("con",1)*2;
	gain *= 3;

	if ( me->query_skill("dodge") > 300 ) gain /= 2;

	me->improve_skill( "dodge",gain/2+random( gain ) );
	if( me->query_skill( "jinyan-gong",1) > 0 )
		me->improve_skill( "jinyan-gong",random( gain ) );


	if(arg == "up" )
	{
		message_vision( HIY"\n$N�����������ٸ���һ����������ȥ��\n"NOR, me);
		me->move(__DIR__"xuanya1");
		message_vision( HIY"\n$Nսս����������ȥ��\n"NOR, me);
		me->improve_skill( "dodge",(gain+random( gain ))/2 );
		me->add("jing",-cost);
		return 1;
	}
	
  return notify_fail("�Ǹ�����û������\n");
}



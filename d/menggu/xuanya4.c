//Cracked by Kafei
// road: /zhongnan/xuanya4.c
// by sdong 08/98

inherit ROOM;
#include <ansi.h>
int do_climb(string arg);

void create()
{
		  set("short",HIC"����"NOR);
		  set("long",@LONG
�ٽ��¶���ɽ���վ����ʣ���ʱ�����¶����������±߻����˰���
��ѩ��ɽ�����ͻ��һ���ʯ��˳��������չ,��˵�ɽ�ƶ���,�˼ʺ�
����ɽ���С��ͻ����ɽ��(shanyan)�´���һ���������ֵ�ӥ��֮����
������ȥ������ƽ��ãã��һ���޾���ɳĮ��ʧ����ߣ�Զ��˵������
����֮�⣬��ֻ�޴�ĺڵ��ڿ��������������ƺ�������ʲô��
LONG);

		  set("item_desc",(["shanyan" :
YEL"�˵�����ͻ������ʯ�£���Ȼ��һ���ǳ����ӥ��������
��ֻ�׵����ڲ�ס���У���׵������ʳ�����ٳ��ڡ�\n"NOR,]));
		  set("exits",([
		//	"up": __DIR__"fengdong",
		//"west": __DIR__"bingdong",
							 ])
			  );
		set("cost",4);
		set("outdoors", "menggu");
		setup();
}

void init()
{
	add_action("do_climb", "climb");
}


int do_climb(string arg)
{
	object me = this_player();
	int gain,cost;

	if(me->is_busy())
		return notify_fail("�㻹��æ���ء�\n");


	cost = ( 300-me->query_dex()*me->query_skill("dodge")/20 )/10;
	
	if ( cost<10 )cost = 10;
	cost *= 2;

	if( me->query("jing") < 30)
		return notify_fail("���۵�ʵ���������ˡ�\n");
	if(arg == "up" )
	{
		message_vision( HIY"\n$N�����������ٸ���һ����������ȥ��\n"NOR, me);
		me->move(__DIR__"yading");
		message_vision( HIY"\n$N����������\n"NOR, me);
		me->improve_skill( "dodge",(gain+random( gain ))/2 );
		if( me->query_skill( "jinyan-gong",1) > 0 )
			me->improve_skill( "jinyan-gong",random( gain ) );
		me->add("jing",-cost);
		return 1;
	}
	else if(arg == "down" )
	{
		message_vision( HIY"\n$N�����������ٸ���С�Ľ���������ȥ��\n"NOR, me);
		me->move(__DIR__"xuanya3");
		message_vision( HIY"\n$N����������\n"NOR, me);
		return 1;
	}
	return 1;
}





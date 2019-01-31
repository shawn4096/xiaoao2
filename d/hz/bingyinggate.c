// Room: /d/suzhou/bingyinggate.c
// Last Modified by winder on May. 15 2001
#include <ansi.h>

inherit ROOM;
string look_mugan();

void create()
{
	set("short", "��Ӫ����");
	set("long", @LONG
����վ�ڱ�Ӫ���ſڣ������һ�ż�ª��Ӫ�������Կ��������Ʒ�
�Ĺٱ����ڲ�������ʱ�ش����ź������ϰ����ǲ������ڴ˹ۿ��ģ���
��øϿ��߿�����Ӫ��������һ��ľ��(mugan)����������˷������׼�
����ռ��������ʿ�����䱸ɭ�ϡ�
LONG
	);
	set("outdoors","����");
	set("exits", ([
		"south" : __DIR__"bingying",
		"north" : __DIR__"qsddao3",
	]));
	set("objects", ([
		"/d/city/npc/bing" : 4,
	]));
	set("item_desc",([
		"mugan" : (:look_mugan:),
	]));
	//set("no_clean_up",0);
	set("shouji",10);
	setup();
	replace_program(ROOM);
}
int init()
{
	object me;
	me=this_player();
	add_action("do_han","han");
	add_action("do_han","ma");
	add_action("do_han","jiaozhen");
}

int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("guan bing", environment(me))) && 
		dir == "south")
		return notify_fail("�ٱ���ס�����ȥ·��\n");
	if (dir == "south"
		&&me->query_temp("quest/���Ӣ�۴�/�����߹�/getshouji"))
	{
		return notify_fail("���͵���׼������ᣬ�ѵ�����Ͷ������\n");
	}
	return ::valid_leave(me, dir);
}

string look_mugan()
{
	object me;
	me=this_player();
	if (!me->query("quest/���Ӣ�۴�/��ѩ����/over"))
		message_vision(HIR"$Ņͷ��ȥ��ȴ����ľ���Ϲ�����һ����Ѫ���ܵķ����׼�!\n"NOR,me);
	else if (me->query_temp("quest/���Ӣ�۴�/�����߹�/hzdatan")&&query("shouji"))
	{
		message_vision(HIY"$Ņͷ��ȥ����Ȼ����ľ���������Ź�Х����׼���\n����ǰһ��ȾƵľ���������Ŀ�����˿�ȴ�˹���;���㲻����������!\n"NOR,me);
		message_vision(HIC"$N�޲�����������ľ����ȥ����"HIY"��Х����׼�"HIC"�����˵����Ǿ�����Ӫ֮�أ�����䱸ɭ�ϣ��޷�����!\n"NOR,me);
		me->set_temp("quest/���Ӣ�۴�/�����߹�/lookgan",1);
		me->delete_temp("quest/���Ӣ�۴�/�����߹�/hzdatan");
		add_action("do_pa","pa");
		add_action("do_pa","climb");
	}
	return "ľ���Ϲ��˺ܶ��׼������˵ؽ䱸ɭ��,ֻ�е������ϲ�������и��\n";
}
//����ȡ�׼�
int do_pa(string arg)
{
	object me,ob,bing;
	
	mixed *local;
	local = localtime(time() * 60);

	me=this_player();
	if (!arg||arg!="mugan")
	{
		return notify_fail("��û�µ���������ѧ�ڹ�ô��\n");
	}
	if(local[2] >6 && local[2] < 18)
	{
		write(WHT"������Զ�����а������ƣ�ľ����ʿ���䱸ɭ�ϣ������޴����֣�\n"
			"������ֻ�е�ҹ��ҹ���˾���ʱ����л������֡�\n"NOR);
		return 1;
	}
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/lookgan"))
	{
		return notify_fail("����Ե�޹����˵�Ϲת��ʲô��\n");
	}
	if (me->query_skill("dodge",1)<300)
	{
		return notify_fail("����Ṧ̫�����300�����������������ľ�ˣ�\n");
	}
	//if (query("shouji")<1)
	//{
		//return notify_fail("ľ���ϵ��׼��Ѿ�������ȡ���ˣ�\n");
	//}

	tell_object(me,HIW"��˳�����ľ������ȥ��С��ȡ�¹�Х����׼��պ�,������������\n"NOR);
	tell_object(me,HIR"�������˺�������˭��ץ�ѵ�����\n"NOR);
	ob=new("d/hz/obj/shouji");
	ob->move(me);
	//add("shouji",-1);

	if (!objectp(bing=present("jinguo gaoshou",this_object())))
	{
		//write("1");
		bing=new("d/thd/niujia/npc/jinguogaoshou");
		//write("2");
		bing->move(this_object());

	}
	bing->kill_ob(me);
	me->delete_temp("quest/���Ӣ�۴�/�����߹�/lookgan");
	me->set_temp("quest/���Ӣ�۴�/�����߹�/getshouji",1);
	return 1;
}
//��Ǻ����ɱ�����
int do_han(string arg)
{
	object me;
	me=this_player();
	if (!arg||arg!="�����")
	{
		return notify_fail("��Ҫ��˭����");
	}
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/maihead"))
	{
		return notify_fail("�㿴������ϵ��׼������м��ȷߺ�,�ƺ�������Щ��û�����䲻�������������Щ�ź���\n");
	}
	
	message_vision(HIC"������һƬ̹����Ψһʣ�±���һ�£����������ȵ���������£����⹷�������ҳ�����!\n"NOR,me);
	message_vision(HIC"���˰��죬�����Ҳû�����������зߺޣ�����Ӳ��!\n"NOR,me);
	me->apply_condition("killer",10);
	me->set_temp("quest/���Ӣ�۴�/�����߹�/hanhua",1);
	
	me->delete_temp("quest/���Ӣ�۴�/�����߹�/getshouji");
	return 1;
}
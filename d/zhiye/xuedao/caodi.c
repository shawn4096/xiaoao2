// Room: /d/huashan/shulin2.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;
string *dongwu=({"lu","tu","pig","zhangzi","ying"});  
void create()
{
        set("short", HIG"�̲ݵ�"NOR);
        set("long", @LONG
����ǰ��Ȼ���ʣ�����ɽ�ȵ����Ȼ��һ���̲ݵأ�����Ƭ��ѩ����
��ѩɽ���Ȼ������̵أ�ʵ�˺������������Ϊ����ɽ�����ܣ��赲�˺�
����ʹ�ô˵��¶Ⱦ�Ȼ�������ط��߲��٣��̵������в��ٶ������������ڵ�
�����ź��ټ���Ե�ʣ����Զ��˲������¡�
LONG);

        set("exits", ([
              //  "east" : __DIR__"shulin3",
              //  "south" : __FILE__,
                "west" : __DIR__"shulin1",
                "north" : __DIR__"wangyougu",
        ]));

        set("outdoors", "xuedao");
		//set("");
        set("coor/x",40);
		set("coor/y",100);
		set("coor/z",0);
		setup();
}
int init()
{
	add_action("do_find","find");
	add_action("do_find","xunzhao");
	add_action("do_find","search");

}

int do_find(string arg)
{
	object me,ob;
	
	me=this_player();
	if (!arg||arg!="����")
	{
		return notify_fail("����Ѱ��ʲô��!\n");

	}
	if (!me->query_temp("xuedao/askdalie")&&!me->query_temp("xuedao/askcaixue"))
	{
		return notify_fail("��˫���ڲݵ���������ȥ���ƺ���Ѱ��ʲô����!\n");
	}
	if (me->query_temp("xuedao/liewu/findok"))
	{
		return notify_fail("���Ѿ�������������Ͽ�Ϲ�ȥ����!\n");
	}
	if ((objectp(ob=present("meihua lu",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("ye zhu",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("ye ying",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("ye tu",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("zhang zi",environment(me)))&&ob->query("owner")==me->query("id")))
	{
		return notify_fail("�����Ѿ������ɱ�������ˣ������Ͻ�ɱ�����⣿!\n");

	}
	message_vision(HIY"$N����˵غ�С������۾������������Ѱ�����\n"NOR,me);
	
	if (random(me->query("kar"))>15)
	{
		me->start_busy(3);
		message_vision(HIW"ͻȻ��$N����Զ������һ�����������������ʱ���д�ϲ��\n"NOR,me);
		me->set_temp("xuedao/liewu/findok",1);
		call_out("liewu_come",2+random(1),me);
		return 1;
	}else {

		message_vision(CYN"$N���˰��죬���������ֿտգ����ǻ�����\n"NOR,me);
	
	}
	me->start_busy(2+random(2));
	return 1;
}
int liewu_come(object me)
{
	object ob,animal;
	string dw,msg;
	if (!me) return;
	dw=dongwu[random(sizeof(dongwu))];
	animal=new("d/xuedao/npc/"+dw+".c");
	msg=animal->query("long");
	animal->set("long",msg+"����"+me->query("name")+"�����ֵ����\n");
	animal->set("owner",me->query("id"));
	animal->set("combat_exp",(int)me->query("combat_exp")*5/4);
	animal->set("max_qi",(int)me->query("qi")*5/4);
	animal->set("eff_qi",(int)me->query("qi")*5/4);
	animal->set("max_jing",(int)me->query("qi")*5/4);
	animal->set("eff_jing",(int)me->query("jing")*5/4);
	animal->add_temp("apply/damage",10);

	animal->move(environment(me));
	message_vision(HIR"��ʱ����Ȼ�ڲݴ��дܳ�һͷ"+HIR+animal->query("name")+HIR"��ǰ��ȥ��\n"NOR,me);
	message_vision(HIC"$N��æ����ͷ����׷ȥ��\n"NOR,me);
	me->delete_temp("xuedao/liewu/findok");

	return 1;
}


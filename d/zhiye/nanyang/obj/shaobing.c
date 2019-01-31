// shaobing.c
// By sohu@xojh ������

#include <ansi.h>

inherit ITEM;
int do_eat(string arg);
#define XKX_QUEST2 "quest/������/������/"

void create()
{
	set_name("�ձ�", ({ "shao bing", "bing", "shaobing" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "rice");
		set("long", "һ����Ӻõ��ձ���������������ģ��������ˡ�\n");
		set("no_give", 1);
		set("no_drop", 1);
		set("no_steal", 1);
		set("lingpai",1);
		set("no_get",1);
	}
	setup();
}
void init()
{
	//add_action("do_eat","eat");
	add_action("do_eat","yao");
}

int do_eat(string arg)
{
	object me,ob;
	me=this_player();
	if (!arg||arg!="�ձ�")
	{
	   return notify_fail("��Ҫ��ʲô��");
	}
	if (me->query("quest/������/������/findxtl"))
	{
	   return notify_fail("���Ѿ��õ��������������˷Ѿ���");
	}
	if (me->query_temp("quest/������/������/helpshi")
		&&this_object()->query("lingpai")
		&&this_object()->query("owner")==me->query("id"))
	{
		message_vision(HIC"��æµ���죬ȷʵ��Щ���������ձ���ҧ����ȥ��˭֪��Ȼ���������ݣ�\n"NOR,me);
		message_vision(HIC"�������Ǹ�Ӳ��һ������Ȼ����һö���������\n"NOR,me);
		
		ob=new("d/motianya/obj/xuantielingpai");
		ob->set("owner",me->query("id"));
		ob->set_temp(XKX_QUEST2+"findxtl",1);
		ob->move(me);
		this_object()->add("lingpai",-1);
		me->set(XKX_QUEST2+"findxtl",1);
		me->delete_temp("quest/������/������");
		
		message_vision(HBYEL+HIW"$N��Ե�ɺϣ����ֲ��õ���л�̿͵������\n"NOR,me);
		call_out("leave",1,me);
		return 1;
	}
	message_vision(CYN"���������Ǹ��ձ������˼��ڣ�\n"NOR,me);
	return 1;

}
int leave()
{
	object min,shi,qigai,me;
	me=this_player();
	if (!me) return;

	message_vision(HIC"��ʱ����Ȼһ������������˵����������������֣��ҿ����������ˣ������߰ɡ�\n"NOR,me);
	message_vision(HIC"һ�����ݵ���Ӱ˲��������ǰ��ץ���Ǹ�С��ؤ���������ݼ���ʧ������\n"NOR,me);
	message_vision(HIC"����ׯ�򸾴��һ�����ȵ����������Ǹ����ӣ������漴��æ׷�Ϲ�ȥ����\n"NOR,me);

	if (objectp(min=present("min rou",environment(me))))
	{
		if (min)
		{
			destruct(min);
		}
	}
	if (objectp(shi=present("shi qing",environment(me))))
	{
		if (shi)
		{
			destruct(shi);
		}
	}
	if (objectp(qigai=present("xiao qigai",environment(me))))
	{
		if (qigai)
		{
			destruct(qigai);
		}
	}

   return 1;
}
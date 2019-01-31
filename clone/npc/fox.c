// fox.c

inherit NPC;
#include <ansi.h>

void create()
{
	set_name(HIG"��β���"NOR, ({ "jiuwei linghu","linghu", "fox" }) );
	set("race", "Ұ��");
	set("age", 3);
	set("long", "һֻ�����ë�ľ�β���,һ˫���۾�����գ���������˵���Ƶá�\n");

	set("str", 32);
	set("dex", 1360);
	set_skill("dodge", 1360);
	set("combat_exp", 5360000);
	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("chat_chance", 60);
	set("chat_msg", ({
		(: this_object(), "random_move" :),
		"��β�������ҡ��ҡͷ��\n",
		"��β�����Զ���������ĵ�һЦ���ƺ����ǳ�Ū��\n",
		"��β���������ҡ��ҡβ�ͣ����ǲ�мһ�ˡ�\n",
		"��β���������ץ��ץ�Լ��Ķ��䡣\n" }) );

	set_temp("apply/attack", 100);
	set_temp("apply/armor", 300);
	setup();
}
/*
int accept_object(object who, object ob)
{
	if( ob->id("bone") ) {
		set_leader(who);
		message("vision", name() + "���˵���������������\n", environment());
		return 1;
	}
}*/
int init()
{
	add_action("do_zhuo","zhuo");
	add_action("do_kill","kill");
}

int do_zhuo(string arg)
{
	object me=this_player();
	
	if (!arg||arg!="��β���")
	{
		return notify_fail("��Ҫ׽ʲô��\n");
	}
	message_vision(HIY"$N������ͼȥ׽��ֻ��β�����\n"NOR,me);
	//ֻ�����ô��ھ��鲢ָ�㣬����ץס
	if (random(me->query_dex(1))>30 && me->query_temp("quest/shendiao/��ѩ�����/yingok"))
	{
		message_vision(HIC"$Nһ�ѽ�ץס��β�����β�ͣ�����ֻС��׽ס��\n"NOR,me);
		message_vision(HIC"$N�������õĽ̻壬��������ɱ����С�ޣ��������غ�ȡ��Ѫ���㹻��\n"NOR,me);
		
		me->set_temp("anran/caixue",1);
		//destruct(this_object());
		this_object()->move(me);
		return 1;
	}else message_vision(HIR"��β����������ݣ��������ߣ����߱߻�ͷ������üŪ�ۣ����ǳ�Ū��\n"NOR,me);
	return 1;
}
//��ʱ��գ��³���
/*
int do_kill()
{
	object me=this_player();
	object ying;
	if (!objectp(ying=present("ying gu",environment(me))))
	{
		ying=new("clone/npc/yinggu");
		ying->move(environment(me));		
	}
	ying->kill_ob(me);

	destruct(this_object());
	return 1;	

}*/
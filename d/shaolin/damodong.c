// Room: /d/shaolin/damodong.c
// Date: YZC 96/01/19

inherit ROOM;
#include <ansi.h>

int do_canwu(string arg);

void create()
{
	set("short", "��Ħ��");
	set("long", @LONG
�����Ǵ�Ħ�Ŷ��������ǰ������ɮ�������Ħ���������£����˷�ˮ
���أ���ס�������޵��ӣ��������ڣ����������·������ǧ�겻��֮����
��Ħ��ʦ���ڴ���������һ��ʮ�꣬�ڼ��������Կɿ��������ʱ�Ĵ���
��̬�������ϵļ�����Ƭ�⣬���п���һ�
LONG
	);

	set("exits", ([
		"out" : __DIR__"bamboo1",
	]));

	set("coor/x",40);
	set("coor/y",520);
	set("coor/z",150);
	setup();
}

void init()
{
	object me = this_player();

	if ((int)me->query_temp("bamboo/count") == 14 
	&&  (int)me->query_skill("dodge", 1) >= 30 
	&&  (int)me->query_skill("dodge", 1) <= 100 
	&&  present("bamboo", me) )
	{
		me->receive_damage("jing", 20);
		me->improve_skill("dodge", me->query("int"));
	}
	if (me->query_temp("yzc/askxuancheng"))
	{
		add_action("do_canwu","canwu");	
	}
	add_action("do_mianbi","mianbi");	
}

int do_mianbi()
{
	int i,j,x,y;
	object me = this_player();
	i = (int)me->query("shen");
	j = me->query("combat_exp");
	y = me->query_skill("yijin-jing",1);
	x = me->query_skill("buddhism",1);

	if ( me->is_busy() ) return notify_fail("����æ����,���龲��������\n");

	me->start_busy(random(2));
	if (me->query("jing") < 100)
		return notify_fail("�㾫���㱣���Ҫ��Ϣ�ˡ�\n");
	me->receive_damage("jing", 50+random(50));
	if (x >= 200)
		if (i < 0) {
			me->add("shen",1000+random(5000));
			message_vision("$N����Ŵ�Ħ�����ߵ�ʯ�ڵ�����˼�����ã���������\n", me);
			me->set_temp("sl_mianbi",1);
			return 1;
		} else if ( i > 0) {
			me->add("shen",-1000-random(5000));
			me->set_temp("sl_mianbi",2);
			message_vision("$N����Ŵ�Ħ�����ߵ�ʯ�ھ�����˼���ã���������\n", me);
			return 1;
		}
	message_vision("$N����Ŵ�Ħ�����ߵ�ʯ�ڳ�˼��һ�ᣬ�������Խ��Խ�ң����ɵ�վ��������\n", me);
	return 1;
}

int do_canwu(string arg)
{
	object me=this_player();
	int i;
	i=random(me->query("kar"));
	if (!me->query_temp("yzc/askxuancheng"))
	{
		return notify_fail("����Ե�޹ʣ����˲���ʲô��\n");
	}
	if (!arg||arg!="һָ��")
	{
		return notify_fail("��Ҫ����ʲô��\n");
	}
	if (time()-me->query("quest/sl/yzc/time")<86400)
	{
		return notify_fail("������Ҳ̫�ڿ���ˣ�\n");
	}
	if (me->query("quest/sl/yzc/pass"))
	{
		return notify_fail("���Ѿ�ͨ����Ħ��Ħͼ��������һָ���İ��\n");
	}
	if(i>=25)
	{
		tell_object(me,HIG"\n��ƽ�ľ������������δ�ʦ��ָ�㣬��һָ�������������ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIC"\n������δ�ʦ�������Ҫ�������в�����������ת������\n"NOR);       
		tell_object(me,HIW"\n�������˼·�𽥺�ʯ���ϵĻ���˴˺�Ӧ��������Ҫ�ں�Ϊһ�����ơ�\n"NOR); 
		tell_object(me,HIC"\n��������ã���������һָ���ھ���Ȼ�ᵽ���ޣ�һ����ȻĪ�����ھ���\n"+
							"������߽��������о���ƽʱ������ת��ɬ֮��ȫȻ������Բת����֮��\n"+
							"������������:��������˭��������ͷ���ع���������ڹ�����ˣ���Ħ������Բͨ��\n"NOR);
		tell_object(me,HIR"\n��ϲ�㣬���Ѿ���һָ���İ��غʹ�Ħͼ���ںϣ��ڻ��ͨ��\n"NOR); 
		me->set("quest/sl/yzc/pass",1);
		log_file("quest/yizhichan", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������һָ���ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/sl/yzc/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/sl/yzc/fail",1);
		me->set("quest/sl/yzc/time",time());
		
		tell_object(me,HIY"�������죬�ķ����ң����Ѿ�����������һָ������������ȫȻ����Ҫ�졣\n\n"NOR);
		
		log_file("quest/yizhichan", sprintf("%8s(%8s) ��������һָ������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/sl/yzc/fail"),i,me->query("combat_exp")) );
	}
	me->start_busy(2);
	return 1;

}
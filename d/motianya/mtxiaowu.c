// mtxiaowu.c ľ��
#include <ansi.h>

inherit ROOM;
#define XKX_QUEST1 "quest/������/Ħ����/"

void create()
{
        set("short", "ľ��");
        set("long", @TEXT
������һ����С��ľ�ݣ����з���һЩ���߰���ļҾߣ�ǽ�Ǳ�
����һ�����õ�С������һ��Ӣ��������������������ȥ���ƺ���ʲ
ô���£���ʱ�ķ���������̾...... 
TEXT );

       set("exits", ([
           "west" : __DIR__"mtdating",
       ]));

       set("objects",([
           __DIR__"npc/shizhongyu" : 1,
       ]));

       setup();       
}

void init()
{

	add_action("do_jiejiu","jiejiu");
}

int do_jiejiu(string arg)
{
	object me,shi,min;
	me=this_player();

	if (!arg||arg!="ʯ����")
	{
		return notify_fail("��Ҫ���˭��");
	}
	if (!me->query_temp(XKX_QUEST1+"yihuo"))
	{
		return notify_fail("���ʯ������Ե�޹ʣ��������Ͳ�����Ϲ����\n");
	}
	message_vision(RED"����$N��ʯ�����ɰ�Ĺ����У����������������һ����\n��ԭ���ҵĺ����������������ץ���ˣ����������ߣ���\n"NOR,me);
	message_vision(RED"\n���ⴳ��������Ӱ��һ�������£�һ�������£����ǽ����˳ƺڰ�˫����ʯ������򸾡���\n"NOR,me);
	if (!objectp(shi=present("shi qing",environment(me))))
	{
		shi=new("d/motianya/npc/shiqing");
		shi->move(environment(me));
	}
	if (!objectp(min=present("min rou",environment(me))))
	{
		min=new("d/motianya/npc/minrou");
		min->move(environment(me));
	}
	shi->kill_ob(me);
	min->kill_ob(me);
	if (objectp(shi)&&objectp(min)&&objectp(me))
		call_out("do_wuhui",6+random(6),me,shi,min);
	return 1;
}
int do_wuhui(object me,object shi,object min)
{
	if (!shi)
	{
		tell_object(me,"ʯ�屻��ʧ��ɱ����ʯ�������ܲ���������ʧ�ܣ��´�������\n");
		me->delete_temp("quest/������/Ħ����");
		return 1;

	}
	if (!min)
	{
		tell_object(me,"���ᱻ��ʧ��ɱ����ʯ�������ܲ���������ʧ�ܣ��´�������\n");
		me->delete_temp("quest/������/Ħ����");

		return 1;

	}
	if (!me) 
	{	
		tell_object(me,"���Լ�׳���ˣ�����ʧ�ܣ��´�������\n");
		return 1;
	}
	message_vision(HIR"\n\n\nʯ�����Ȼ��һ������ס�֣��Լ��ˣ����������ô���ˣ���\n"NOR,me);
	shi->remove_all_enemy();
	shi->start_busy(2);
	min->remove_all_enemy();
	min->start_busy(2);

	me->remove_all_enemy();
	me->start_busy(2);

	call_out("do_huangwu",3+random(4),me);
	return 1;
}
int do_huangwu(object me)
{
	object shi,min,yu;
	message_vision(HIY"$N����ʯ����Ľ��ܷ���֪��ԭ�����λ����ʯ������������\n"NOR,me);
	message_vision(HIY"ʯ����ԭ��������ׯ��ʯ����������ӣ�һֱ׷Ѱ�����ҵ��˵أ�\n������Ϊ"+me->query("name")+"Ҫ���Լ����Ӳ������ų��֣�ԭ����һ����ᣡ\n"NOR,me);
	message_vision(HIR"\n\n$N��ʯ��������Լ�����һ���뿪��������ζ�ӳ¡�\n"NOR,me);

	message_vision(HIR"\n\n$N�п������޳�����Ȼ����˵����ۣ���������������˻���û����أ�\n"NOR,me);
	message_vision(YEL"\n\n���������Ȼ�ȥ����������֪һ����˵��\n"NOR,me);
	me->set(XKX_QUEST1+"over",1);
	me->set("quest/������/time",time());
	me->set("quest/������/exp",me->query("combat_exp"));

	me->delete_temp("quest/������/Ħ����");
	if (objectp(shi=present("shi qing",environment(me))))
	{
		destruct(shi);
	}
	if (objectp(min=present("min rou",environment(me))))
	{
		destruct(min);
	}
	if (objectp(yu=present("shi zhongyu",environment(me))))
	{
		destruct(yu);
	}

	message_vision(HBYEL+HIW"\n\n��ϲ$N����ˡ������С�����ϵ��һ֮��Ħ����ƪ��\n"NOR,me);
	message_vision(HIC"\n\n�Ѿ�Զȥ��ʯ�����Զ��������������пգ���������ׯ���ͣ���\n"NOR,me);

	return 1;
}
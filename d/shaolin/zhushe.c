// Room: /d/shaolin/zhushe.c
// Date: YZC 96/01/19
// Dat:  Cleansword 96/02/20

inherit ROOM;
#include <ansi.h>

string look_stone();
string look_pig();

/* (move stone) ����ʯ������������һϢ����������������
��շ�ħȦǰ��ε��߷�(western)��˵��ͷһ�ᣬ���ˡ������
ѧ���ڹ���������ѧ�ڹ���(life heal)֮������������һ������
����˵�������߷�(news)�����Ҹ�֪���Թ��߷����ڳ���Ī����
δ��˵��δ������ˡ�����Լ��ҳ��δ�����ͷ��������ȥ��
������һ��ש���Ͽ̳��Թ��߷�����*/


void create()
{
	set("short", "����");
	set("long", @LONG
���Ǽ����õ�ũ�����ᡣȦ�����ż�ͷ����(pig)������Ѿ��ɺ��ˣ�����
Ҳ��ʼ��ù���á����ںö���û���������ڵķ�㣬������������һ�ɶ������
�Ƕ���һ���ʯ��(stone)�����а��˸ߡ�
LONG
	);

	set("exits", ([
		"southeast" : __DIR__"houshan",
	]));

	set("item_desc",([
		"stone"		:	(: look_stone :),
		"pig"		:	(: look_pig :),
	]));

	set_temp("available",1);

	setup();
}

void init()
{
	add_action("do_move", "move");
	add_action("do_weizhu", "wei");
	add_action("do_weizhu", "weishi");
}

int do_move(string arg)
{
//	string dir;
	object me,ob;

	if( !arg || arg=="" || !query_temp("available") ) return 0;

	if( arg=="stone" && query_temp("available")) {
		write("��������ʯ��һ���ذῪ��ͻȻ�����������Ÿ�����һϢ������ !\n\n");
	        delete_temp("available");
	}


	me = new(__DIR__"npc/lao-qiao",1);
	me->move(__DIR__"zhushe");

	ob = this_player();	

	message_vision("���˶϶�������˵��: ��������������...��������ɽ����...��
��������...������...������...�����ϣ�����...��������......\n\n", ob);

	message_vision("�������촽���˶����ƺ�����˵Щʲ�ᣬȴ��������֧�������˹�ȥ��\n", ob);

	me->unconcious();

	remove_call_out("fainting");
	call_out("fainting", 20, me, ob);

	return 1;
}

void fainting(object me, object ob)
{

	if ( (int)me->query("qi") <= 50 ) 
	{
		message_vision("���������������˹�����˵��: л...л......��\n",ob);
		me->die();
	}
	else
	{
		message_vision("\n���������˹�����˵��: ����������������������......��·��ש......\n\n",ob);
		message_vision("˵���Դ�������ش�����ȥ......",ob);
		me->die();
	}

	return;
}

string look_stone()
{
	return "����һ���ʯ�飬����ǽ�űߣ���֪����ʲ���ó���\n";
}
string look_pig()
{
	return "һͷ�ݹ���᾵����ܾ�û�����ˣ������ߺߵؽУ���������ʳ������(weishi)���ǡ�\n";
}

int do_weizhu(string arg)
{
	object me,shi;
	me=this_player();

	if (!arg||arg!="��")
		return notify_fail("��Ҫιʳʲô���\n");
	if (me->is_busy()||me->is_fighting())
		return notify_fail("������æµ�У�\n");
	if (!me->query_temp("sljob/weizhu/askqiao"))
		return notify_fail("��ͷ���������˵ģ������ιʳ������ҧ�㣿\n");
	if (me->query_temp("sljob/weizhu/over"))
		return notify_fail("��ͷ���Ѿ�ι���ˣ����Ի�ȥ���Ǵ��轻���ˣ�\n");
	if (!objectp(shi=present("zhu shi",me)))
		return notify_fail("������û����ʳ���޷�ι�����ǣ�\n");
	if (random(2))
	{
		message_vision(HIC"$N������ʳ������������Ҫ��һ�ף������������֮�У����ﺰ�����������ǣ��԰ɣ���\n"NOR,me);

	}else {
				message_vision(YEL"$N������ʳ�����ﺰ��������`````````````����\n"NOR,me);

	}
	shi->add("food_remaining",-1);
	me->add_busy(1);
	me->add_temp("sljob/weizhu/times",1);
	me->add("jingli",-1-random(10));
	if (!shi->query("food_remaining"))
	{
		message_vision(HIY"$N�����һ����ʳ������ۣ�����������ǳ����ģ��·���ͷ���˲��٣���\n"NOR,me);
		write("��ͷ�������Ѿ�ι���ˣ����Ի�ȥ�����ˣ�\n");
		if (shi)
		{
			destruct(shi);
		}
		me->set_temp("sljob/weizhu/over",1);
	}
	return 1;
}
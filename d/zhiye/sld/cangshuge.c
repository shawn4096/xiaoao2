#include <ansi.h>
inherit ROOM;
string look_miji();

void create()
{
        set("short", "�����");
        set("long", @LONG
�����������̵��Ӵ�������似����ѧ�Ĳ���ص㣬¥��
���������������(shujia)����Ϊҩֲѧ����ҩѧ���似ѧ��ҩ
��ѧ���ؼ�(miji)���е��ǹ�������ģ���Щ��Ȼ�������ġ�
LONG);
        set("exits", ([
                "south" : __DIR__"tz",
        ]));
        set("objects", ([
            __DIR__"obj/yaoli1" : 1,
			__DIR__"obj/yaoli2" : 1,
			__DIR__"obj/duyaojing" : 1,
        ]));
		set("item_desc",([
				//"ʯ��" : "����������౻������������(hit)������ӡ����\n",
				"miji" : (:look_miji:),
		]));
		set("hook_count1",1);
		set("hook_count2",1);
		set("leg_count",1);
		set("hand_count",1);
		set("dagger_count",1);
        setup();
        replace_program(ROOM);
}
int init()
{
	add_action("do_find",({"find","search"}));
}
string look_miji()
{
	tell_object(this_player(),HIC"�似���ؼ���\n"NOR
		+"	����������(�ϲ�)��\n"
		+"	�������ȷ���Ҫ��\n"
		+"	���̿�ذ��Ҫ����\n"
		+"	����˿����Ҫ��\n"
		+"	����������(�²�)��\n"
		+"ע�⣺����ͨ��search shujia�õ�����ؼ���\n"NOR);
	return "";
}

int do_find(string arg)
{
	object me,ob;
	string msg;
	me=this_player();

	if (!arg)
	{
		return notify_fail("��Ҫ��Ѱʲô��\n");
	}
	if (me->query("family/family_name")!="������")
	{
		return notify_fail("�㲻�������̵�������������\n");
	}
	if (me->query("party/gongji")<500)
	{
		return notify_fail("������ɹ���ֵ����500���޷����ɶһ������ؼ���\n");
	}
	if (arg=="shujia")
	{
		msg=HIC"$N���������ϸ�鿴��Ŀǰ����ϴ��ڵ�ѧ�ؼ��У�\n"NOR;
		msg=HIC"ע�⣻ÿ����ȥ�����ؼ���Ҫ���ɹ���ֵ500�㡣\n"NOR;
		if (query("hook_count1")>0)
		{
			msg+=MAG"\n<���������ϲ�>\n"NOR;
		}
		if (query("hook_count2")>0)
		{
			msg+=HIW"\n�����������²ᡷ\n"NOR;
		}
		if (query("leg_count")>0)
		{
			msg+=HIG"\n�������ȷ���Ҫ��\n"NOR;
		}
		if (query("dagger_count")>0)
		{
			msg+=HIG"\n���̿�ذ��Ҫ����\n"NOR;
		}
		if (query("hand_count")>0)
		{
			msg+=HIG"\n����˿����Ҫ��\n"NOR;
		}

		message_vision(msg,me);

		return notify_fail("���������������Ѱһ�����鼮�ܶ࣬��֪������ҪѰ���Ǳ��飿\n");
	}
	
	me->add("party/gongji",-500);

	if (arg=="�̿�ذ��Ҫ��")
	{
		if (query("dagger_count")<1) 
			return notify_fail("�̿�ذ��Ҫ���Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/sld/obj/dagger_book1");
		ob->move(me);
		message_vision(HIC"$N������г��һ���̿�ذ��Ҫ�������뻳�У�\n"NOR,me);
		add("dagger_count",-1);
		return 1;
	}
	if (arg=="�����ȷ���Ҫ")
	{
		if (query("leg_count")<1) 
			return notify_fail("�����ȷ���Ҫ�Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/sld/obj/leg_book");
		ob->move(me);
		message_vision(HIC"$N������г��һ�������ȷ���Ҫ�����뻳�У�\n"NOR,me);
		add("leg_count",-1);
		return 1;
	}
	if (arg=="��˿����Ҫ")
	{
		if (query("hand_count")<1) 
			return notify_fail("��˿����Ҫ�Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/sld/obj/hand_book1");
		ob->move(me);
		message_vision(HIC"$N������г��һ����˿����Ҫ�����뻳�У�\n"NOR,me);
		add("hand_count",-1);
		return 1;
	}

	if (arg=="���������ϲ�")
	{
		if (query("hook_count1")<1) 
			return notify_fail("���������ϲ��Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/sld/obj/hook_book1");
		ob->move(me);
		message_vision(HIC"$N������г��һ�����������ϲᣬ���뻳�У�\n"NOR,me);
		add("hook_count1",-1);
		return 1;
	}
	if (arg=="���������²�")
	{
		if (query("hook_count2")<1) 
			return notify_fail("���������²��Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/sld/obj/hook_book2");
		ob->move(me);
		message_vision(HIC"$N������г��һ�����������²ᣬ���뻳�У�\n"NOR,me);
		add("hook_count2",-1);
		return 1;
	}
	
	return notify_fail("��Ҫ��Ѱʲô�鼮��\n");

}
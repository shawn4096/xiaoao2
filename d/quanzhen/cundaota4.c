#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�������");
        set("long", @LONG
�����Ǵ���������������ݵ�����͵��˾�ͷ��ǽ���Ͽ�
�ż�������(window)������������������������������˵ظ�
Զ������������ϴ������������������������ж���Ҳ�в�
�ٵ��������ܷ������(shujia)�ϵĸ����似�͵��ؾ��䡣
LONG);
        set("exits", ([
                "eastdown" : __DIR__"cundaota3",
        ]));
        set("objects", ([
                __DIR__"npc/zhangjing" : 1,
				__DIR__"obj/dadaojue1" : 1,
				__DIR__"obj/dadaojue2" : 1,
        ]));

        set("item_desc", ([
                "window": HIW "\n�������Ʈ�����ƺ���һ���־Ϳ���ץסһƬ��\n" NOR,
			    "shujia": HIW "\n��������ϰ����˸��ֵ��Ҿ���������Ҳ���Ӳ����书�ؼ���\n" NOR,

        ]));

        set("dj_count",1);
		set("tg_count",1);
		set("ys_count",1);
        setup();
        replace_program(ROOM);
}
int init()
{
	add_action("do_search","search");
	add_action("do_search","find");

}
int do_search(string arg)
{
	object me,ob;
	string msg;
	me=this_player();

	if (!arg)
	{
		return notify_fail("��Ҫ��Ѱʲô��\n");
	}
	if (me->query("family/family_name")!="ȫ���"||!me->query("quest/qz/dichuan"))
	{
		return notify_fail("�㲻��ȫ��մ���������������\n");
	}
	if (me->query("party/gongji")<500)
	{
		return notify_fail("������ɹ���ֵ����500���޷����ɶһ������ؼ���\n");
	}
	if (arg=="shujia")
	{
		msg=HIC"$N���������ϸ�鿴��Ŀǰ����ϴ��ڵ�ѧ�ؼ��У�\n"NOR;
		msg=HIC"ע�⣻ÿ����ȥ�����ؼ���Ҫ���ɹ���ֵ500�㡣\n"NOR;
		if (query("dj_count")>0)
		{
			msg+=MAG"\n<������������ᣩ>\n"NOR;
		}
		if (query("tg_count")>0)
		{
			msg+=HIW"\n<ͬ�齣��>\n"NOR;
		}
		if (query("ys_count")>0)
		{
			msg+=HIG"\n<���������ʮ�ľ����ϲᣩ>\n"NOR;
		}
		message_vision(msg,me);

		return notify_fail("���������������Ѱһ�����鼮�ܶ࣬��֪������ҪѰ���Ǳ��飿\n");
	}
	//ͬ�齣����quest����
	me->add("party/gongji",-500);

	if (arg=="ͬ�齣��")
	{
		if (!me->query("quest/qz/tgjf/pass"))
			return notify_fail("����δ��ùۿ�ͬ�齣���Ļ��ᣬ��Ǹ��\n");	
		if (query("tg_count")<1) 
			return notify_fail("ͬ�齣���Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/quanzhen/obj/tonggui_jianpu");
		ob->move(me);
		message_vision(HIC"$N������г��һ��<ͬ�齣��>�����뻳�У�\n"NOR,me);
		add("tg_count",-1);
		return 1;
	}

	if (arg=="�����"||arg=="������ؼ�"||arg=="�ؼ�")
	{
		if (query("dj_count")<1) 
			return notify_fail("������Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/quanzhen/obj/dadaojue3");
		ob->move(me);
		message_vision(HIC"$N������г��һ������������뻳�У�\n"NOR,me);
		add("dj_count",-1);
		return 1;
	}
	if (arg=="���������"||arg=="���������ʮ�ľ�")
	{
		if (query("ys_count")<1) 
			return notify_fail("����������Ȿ�ؼ��Ѿ�����ȡ���ˣ�\n");
		ob=new("d/quanzhen/obj/yusuojue1");
		ob->move(me);
		message_vision(HIC"$N������г��һ����������������뻳�У�\n"NOR,me);
		add("ys_count",-1);
		return 1;
	}
	return notify_fail("��Ҫ��Ѱʲô�鼮��\n");

}
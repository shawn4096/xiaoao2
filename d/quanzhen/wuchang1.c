#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�䳡");
        set("long", @LONG
������ȫ��̵����䳡�����µ���ש�����̵���������ȴ
��֪����˭�ȳ��˼�ʮ�����СС�İ��ӡ����ĳ����������
�����µ��е��������Ṧ���䳡��Ե��һ�ŵͰ�ľ׮(zhuang)
���������е�����Ծ���ݡ�
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "south" : __DIR__"wuchang2",
                "north" : __DIR__"houtang2",
                "southeast" : __DIR__"xiuxishi",
        ]));
		set("item_desc", ([
                "zhuang" : HIG "\n����һ�Ŵ������µ�÷��׮�������ڵ��ϡ�����"
                          "����������ϰ�Ṧ\n�ģ���������Ŵ�(tiao)�򿴡�\n" NOR,

        ]));

        setup();
        replace_program(ROOM);
}

void init()
{
        add_action("do_tiao", "tiao");
    //  add_action("do_cuff", "ci");
}

int do_tiao(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill=me->query_skill("dodge", 1);
		e_skill=c_skill*c_skill*c_skill;

		if (!arg) return notify_fail("��Ҫ������!\n");
		if (arg!="zhuang") return notify_fail("�������ȸԾ!\n");

        message_vision(HIG "$N" HIG "����һԾ�������ߵʹ����ľ׮�ϣ�շת��Ų��\n" NOR, me);
        qi_cost = 25;
		if (c_skill>100)
		{
			tell_object(me, HIC "����һ�ݣ���Ծľ׮��������ء�\n" NOR);
			return 1;
		}
		if (e_skill/10>me->query("combat_exp"))
		{
			tell_object(me, HIC "�������ޣ��޷��������������Ṧ�ˡ�\n" NOR);
			return 1;
		}

        if (me->query("jingli") > qi_cost)
        {
                
				if (c_skill < 100 && e_skill/10< me->query("combat_exp"))
				{
                	me->improve_skill("dodge", 1 + random(me->query("dex")));
					me->receive_damage("jingli", qi_cost);
					tell_object(me, HIC "��ԡ������Ṧ�������µ�����\n" NOR);
				}
				else
				{
                 me->receive_damage("jingli", qi_cost);
				 tell_object(me, HIC "�������ޣ��޷��������������Ṧ�ˡ�\n" NOR);
				}
        }
		else tell_object(me, HIC "�㾫�����㣬�޷����������������ˡ�\n" NOR);
        return 1;
}

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�䳡");
        set("long", @LONG
������ȫ��̵����䳡�����µ���ש�����̵�������������ƽ��
�䳡��һ��һ���ŵļ��ӵ�װ���ٵ�ɳ��(shadai)���в��ٵ�������
�����ȹ��Ļ���������
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "north" : __DIR__"wuchang1",
                "east"  : __DIR__"xiuxishi",
                "south" : __DIR__"wuchang3",
                "southeast" : __DIR__"shantang",
        ]));
		set("item_desc", ([
                "shadai" : HIC "\n����һ���ŵ�ľ�ܵ�װ����ʮ��ɳ����Ϊ���е����ճ�"
                          "����������ϰ�����ȷ���\n�ģ������������(ti)�򿴿���\n" NOR,

        ]));

      //  set("for_family", "ȫ���");

        setup();
        replace_program(ROOM);
}

void init()
{
        add_action("do_ti", "ti");
}

int do_ti(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill=me->query_skill("leg", 1);
		e_skill=c_skill*c_skill*c_skill;

		if (!arg) return notify_fail("��Ҫ��˭��!\n");
		if (arg!="shadai") return notify_fail("�����һ���������!\n");
		
        message_vision( "$N����һԾ��һ������������������ɳ����\n" NOR, me);
        
		qi_cost = 25;
		if (c_skill>100)
		{
			tell_object(me, HIC "����һ�ߣ�ɳ������Զ����\n" NOR);
			return 1;
		}
		if (e_skill/10>me->query("combat_exp"))
		{
			tell_object(me, HIC "�������ޣ��޷��������������ȷ��ˡ�\n" NOR);
			return 1;
		}

        if (me->query("jingli") > qi_cost)
        {
                
				if (c_skill < 100 && e_skill/10< me->query("combat_exp"))
				{
                	me->improve_skill("leg", 1 + random(me->query("dex")));
					me->receive_damage("jingli", qi_cost);
					tell_object(me, HIC "��ԡ������ȷ��������µ�����\n" NOR);
				}else
				{
                 me->receive_damage("jingli", qi_cost);
				 tell_object(me, HIC "�������ޣ��޷��������������ȷ��ˡ�\n" NOR);
				}
        }
		else tell_object(me, HIC "�㾫�����㣬�޷����������������ˡ�\n" NOR);
        return 1;
}

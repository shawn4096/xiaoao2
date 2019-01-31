#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������ȫ��̵��������ķ��䡣����������״��������ǰ
խ�����Ϊ���Σ����߰�Բ������ȴ��������״��ԭ������
ȫ��̶��е������ң�ǰխ���ƣ����ʹָ����Բ�н�������
���ڡ����������ż��������õ�ľ�ˣ����ż���ɳ�� (bag)��
ֽ��(paper)��
LONG);

        set("exits", ([
                "south" : __DIR__"houtang2",
                "north" : __DIR__"chanfang2",
        ]));
        set("item_desc", ([
                "paper" : YEL "\n����һ������ţƤֽ�ᣬ����������ǽ�ϡ�����"
                          "����������\n�Ʒ��ģ���������Ŵ�(pai)�򿴡�\n" NOR,

                "bag"   : WHT "\n����һ����ɳ�����������ǳ���ʵ��������ר����"
                          "����ϰȭ��\n�ģ��������(da)�����Կ���\n" NOR,
        ]));
        set("for_family", "ȫ���");
        setup();
}

void init()
{
        add_action("do_strike", "pai");
        add_action("do_cuff", "da");
}

int do_cuff(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill=me->query_skill("cuff", 1);
		e_skill=c_skill*c_skill*c_skill;
		if (!arg) return notify_fail("��Ҫ��ʲô��!\n");
		if (arg!="bag") return notify_fail("����ȭ�������������!\n");

		message_vision(HIY "$N" HIY "��ȭ���Ĵ���ɳ��������ȭͷ΢΢"
                       "��Щʹ��\n" NOR, me);
        qi_cost = 25;
		if (c_skill>100)
		{
			tell_object(me, HIC "��ʹȭ�������ɰ�ɳ���ķɡ�\n" NOR);
			return 1;
		}
		if (e_skill/10>me->query("combat_exp"))
		{
			tell_object(me, HIC "�������ޣ��޷�������������ȭ���ˡ�\n" NOR);
			return 1;
		}

        if (me->query("jingli") > qi_cost)
        {
                
				if (c_skill < 100 && e_skill/10< me->query("combat_exp"))
				{
                	me->improve_skill("cuff", 1 + random(me->query("str")));
					tell_object(me, HIC "��ԡ�����ȭ���������µ�����\n" NOR);
				}else

                me->receive_damage("jingli", qi_cost);
        }
        return 1;
}

int do_strike(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill = me->query_skill("strike", 1);
		e_skill=c_skill*c_skill*c_skill;
		
		if (!arg) return notify_fail("��Ҫ��ʲô��!\n");
		if (arg!="paper") return notify_fail("����ȭ�������������!\n");

        message_vision(HIY "$N" HIY "����һ����������һ���ͻ���ţƤ"
                       "ֽ�ᡣ\n" NOR, me);
        qi_cost = 25;
		if (c_skill>100)
		{
			tell_object(me, HIC "������磬��ֽ���ɢ�ˡ�\n" NOR);
			return 1;
		}
		if (e_skill/10>me->query("combat_exp"))
		{
			tell_object(me, HIC "�������ޣ��޷��������������Ʒ��ˡ�\n" NOR);
			return 1;
		}

        if (me->query("jingli") > qi_cost)
        {
                if (c_skill < 100 && e_skill/10< me->query("combat_exp"))
				{
	                me->improve_skill("strike", 1 + random(me->query("str")));
					tell_object(me, HIC "��ԡ������Ʒ��������µ�����\n" NOR);
				}
                me->receive_damage("jingli", qi_cost);
        } 
        return 1;
}

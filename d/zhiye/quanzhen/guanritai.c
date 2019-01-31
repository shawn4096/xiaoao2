inherit ROOM;
#include <ansi.h>


int do_zhan(string arg);
void create()
{
        set("short", "����̨");
        set("long", @LONG
����������ɽ�ϵĹ���̨����֪�ĳ��Ĵ���������������
�����ƽ̨��������հ�ճ��������������ɽ�Ʒǳ���������
��һ��������(cliff)���������°���Ʈ�����治֪���ںξ���
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "north" : __DIR__"shijie9",
        ]));
        set("objects",([
                __DIR__"npc/youke" : 1,
                __DIR__"npc/xiangke" : 1,
        ]));
		
		set("item_desc", ([
                "cliff" : HIG"\n��������ɽ����̨��Ϊ�վ�֮����������������Ԩ������һ�˵��Ŷ��������μ�Ϊ�ն�\n"+
								"ɽ��ɽ���Х��������˵���ţ�����˫����վ��Ҳ��һ�ֺ��˲���ı��£���˵����������һ\n"+
								"���ڴ˵��Ŷ���������ҹ�ڼ��籩���״򲻶����Դ��������Ⱥ���������(duli)��ϰ������\n" NOR,
								]));

        setup();
        replace_program(ROOM);
}

void init()
{
        add_action("do_zhan", "duli");
}

int do_zhan(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill=me->query_skill("leg", 1);
		e_skill=c_skill*c_skill*c_skill;

		if (!arg) return notify_fail("��Ҫ������!\n");
		if (arg!="cliff") return notify_fail("��һ���𼦶�������!\n");
		
        message_vision(HIG "$N" HIG "����һԾ����ͼ�𼦶���վ�����±��ϡ�\n" NOR, me);
        
		qi_cost = 50;
		if (c_skill<100)
		{
			tell_object(me, HIC "������̫ǳ�������ϴ���һ�ɿ�磬���㴵��ԭ�ء�\n" NOR);
			return 1;
		}
		if (c_skill>220)
		{
			tell_object(me, HIC "����һ�ݣ��𼦶���������վ�Ƕ�����˿������\n" NOR);
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


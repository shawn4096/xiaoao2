inherit SNAKE;
#include <ansi.h>

void create()
{
        set_name(HIG "����" NOR, ({ "mang she", "mang", "she" }));
        set("long", HIG "����һֻ����ֱ�������ų���о�Ĵ����ߡ�\n" NOR);

        set("age", 6);
        set("str", 50);
        set("dex", 20);
        set("con", 50);
	set("max_qi", 5000);
	set("max_jing", 5000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("combat_exp", 300000);

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 50,
                "maximum": 50,
                "supply" : 1,
        ]));

        set("power", 45);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/quarry/item/shepi");

        set_temp("apply/force", 200);
        set_temp("apply/parry", 200);
        set_temp("apply/dodge", 200);
        set_temp("apply/attack", 180);
        set_temp("apply/defense", 180);
        set_temp("apply/unarmed_damage", 220);
        set_temp("apply/armor", 220);

        setup();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she" && arg!="mang she") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");

	return notify_fail("��������̫���ִ��޷���Ϊ���ȡ�\n");
}

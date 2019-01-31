#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name(HIC "�˻���" NOR, ({ "caihua she", "caihua", "she" }));
        set("long", HIC "����һֻ�����ĵĲ˻��ߣ�ͷ������Բ�Ρ�\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 16);
	set("max_qi", 200);
	set("max_jing", 200);
        set("combat_exp", 1000);

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 50,
                "maximum": 50,
                "supply" : 1,
        ]));

        set("power", 8);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/unarmed_damage", 50);

        setup();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she" && arg!="caihua she") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");
	return notify_fail("�˻���Ұ��̫С���������Ժܲ���ܻ�Ϊ�ȡ�\n");
}

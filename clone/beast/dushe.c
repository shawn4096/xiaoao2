#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name(HIG "����" NOR, ({ "du she", "du", "she" }));
        set("long", HIG "һ֧�������ŵĶ�������������ض����㡣\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 25);
        set("max_qi", 500);
        set("max_ging", 500);
        set("combat_exp", 5000);

        set("snake_poison", ([
                "level"   : 80,
                "remain"  : 20,
                "maximum" : 20,
                "perhit"  : 10,
                "supply"  : 1,
        ]));

        set("power", 12);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 50);
        set_temp("apply/defense", 100);
        set_temp("apply/unarmed_damage", 50);

        setup();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

        if (arg!="snake" && arg!="du she") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");
	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N���ְ�ס���ߵ�ͷ�������ḧ���ߴ磬���������дʣ�Ƭ�̼佫�߻�Ϊһ�����ȡ�\n",
		me,);
	        ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
	return 1;
}

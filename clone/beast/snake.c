//snake.c

inherit SNAKE;

void create()
{
	set_name("�ڹھ���", ({ "black snake", "she" }) );
	set("race", "Ұ��");
	set("age", 20);
	set("long", "һֻ��Ȼ������������,����Ҫһ�ڰ������¡�\n");
	set("attitude", "aggressive");
        set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 500);
	set("max_jing", 500);
	set("str", 86);
	set("con", 80);
	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
	set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 50,
                "maximum": 50,
                "supply" : 1,
        ]));

	set("combat_exp", 1000000);

	set_temp("apply/attack", 85);
	set_temp("apply/damage", 80);
	set_temp("apply/armor", 88);
	set_temp("apply/defence",80);

	setup();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");

	return notify_fail("�ڹھ�������̫���ִ��޷���Ϊ���ȡ�\n");
}

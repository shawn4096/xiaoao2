// Npc: /d/tianshan/npc/lu.c
// By Linux

inherit NPC;

void create()
{
        
	set_name("Ұӥ", ({ "ye ying", "ying" }) );
        set("race", "Ұ��");
        set("age", 2);
        set("long", "һֻ�߿հ����Ұӥ����������ɽ����ζ��\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "ͷ��", "����", "צ��", "β��" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 3000);

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 10);
		set_temp("apply/defence",30);
		set_temp("apply/armor",10);
		set("chat_chance", 3);
      	set("chat_msg", ({
           //   (: random_walk :),
      	}) );

        setup();
}
int kill()
{
	object me;
	me=this_player();
	if (this_object()->query("owner")!=me->query("id"))
	{
		return notify_fail("�㲻��ɱ���˵����\n");
	}
}
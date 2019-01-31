// Npc: /d/tianshan/npc/lu.c
// By Linux

inherit NPC;

void create()
{
        
	set_name("野狼", ({ "ye lang", "lang","wolf" }) );
        set("race", "野兽");
        set("age", 2);
        set("long", "一只瘦骨嶙峋的狼，正凶狠地盯住你看。\n");
        //set("attitude", "aggressive");
		set("attitude", "peaceful");
		set("qi",1000);
		set("max_qi",1000);
		set("eff_qi",1000);
		set("jingli",500);
		set("max_jingli",500);
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "头部", "身体", "爪子", "尾巴" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 100000+random(50000));

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
		return notify_fail("你不能杀别人的猎物！\n");
	}
}
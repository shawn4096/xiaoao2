// shiwei.c 带刀侍卫
// Modify by Looklove@SJ fixed bug 2000/9/8

inherit NPC;
#include <ansi.h>

void create()
{
	set_name("皇宫侍卫", ({ "huanggong shiwei", "shiwei", "wei" }));
	set("gender", "男性");
	set("age", random(20) + 30);
	set("str", 25);
	set("dex", 16);
	set("long", "他是大理皇宫侍卫，手握长剑，目视前方，真是威风凛凛。\n");
	set("combat_exp", 4750000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("strike", 350);
	set_skill("force", 350);
	set_skill("blade", 350);
	set_skill("dodge", 350);
	set_skill("parry", 350);
    set_skill("duanjia-jianfa",350);
	set_skill("sword",350);
    set_skill("qingyan-zhang",350);

	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 30);
    map_skill("sword","duanjia-jianfa");
	map_skill("parry","duanjia-jianfa");
	prepare_skill("strike","qingyan-zhang");
	set("neili", 4000); 
	set("max_neili", 4000);
	set("eff_jingli", 2000);
	set("jingli", 2000);
	
	setup();
	carry_object("/clone/weapon/sword")->wield();
	carry_object("/clone/armor/armor")->wear();
}

void init()
{
	object ob;
	::init();
	ob=this_player();
	if (ob->query("family/family_name")=="天龙寺") return;

	if (interactive(ob = this_player()) &&
	ob->query_condition("killer")) {
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}

void kill_ob(object me)
{
	object ob;
	int i;

	::kill_ob(me);
	if (!is_killing(me->query("id")))
		return;
	for (i = 1; i <= 4; i++)
		if (objectp(ob = present("huanggong shiwei "+i))
		&& !ob->is_killing(me->query("id")))
			ob->kill_ob(me); 
}

int accept_fight(object me)
{
	command("say 竟敢和大理皇宫侍卫过不去，今天算你倒霉。\n");
	if (!is_killing(me->query("id")))
		me->add_condition("killer", 15);
	kill_ob(me);
	return 1;
}

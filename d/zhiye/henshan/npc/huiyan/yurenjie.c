#include <ansi.h>
inherit NPC;
void greeting(object ob);
int accept_fight(object ob);
void create()
{
	seteuid(getuid());
	set_name("于人杰", ({ "yu renjie", "yu","renjie" }));
	set("long", "他一身飘逸的白色长衫，风流儒雅。\n");
	set("nickname", HIG "青城四秀" NOR);
	set("gender", "男性");
	set("age", 37);
	set("attitude", "peaceful");
	set("shen_type", -1);

       set("per", 23);
	set("str", 25);
	set("int", 24);
	set("con", 25);
	set("dex", 26);

	set("qi", 11000);
	set("max_qi", 11000);	
	set("combat_exp", 6800000);
	set("score", 40000);

	set("jing", 3800);
	set("max_jing", 3800);
		set("jingli", 4800);
	set("max_jingli", 4800);
	set("eff_jingli", 4800);

	set("neili", 21000);
	set("max_neili", 21000);
	set("jiali", 200);
	set_skill("sword", 400);
	set_skill("dodge",400);
	set_skill("parry", 400);
	set_skill("force", 400);
	set_skill("lingxu-bu", 400);
	set_skill("songfeng-jian", 400);
	set_skill("qingyun-shou", 400);
	set_skill("hand", 400);

	map_skill("dodge", "lingxu-bu");
	map_skill("parry", "songfeng-jian");
	map_skill("hand", "qingyun-shou");
	map_skill("sword", "songfeng-jian");

    set("chat_chance_combat", 50);

    set("chat_msg_combat", ({
                (: perform_action, "sword.songfeng" :),
    }) );

	set("chat_chance", 40);

	setup();
	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver",40);
}


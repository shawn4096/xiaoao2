// NPC: /d/huashan/npc/gaogenming.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("高根明", ({ "gao genming", "gao", "genming" }));
	set("nickname", "市井豪杰");
	set("long",
"高根明身材较胖，是一个小贩，手里总是拿着一杆秤，他在\n"
"同门中排行第五，是华山派年轻一代中的好手。\n");
	set("gender", "男性");
	set("age", 28);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("per", 20);
	set("str", 28);
	set("int", 24);
	set("con", 20);
	set("dex", 20);

	set("max_qi", 3000);
	set("max_jing", 1800);
	set("neili", 3000);
	set("max_neili", 3000);
	set("eff_jingli", 1800);


	set("jiali", 150);
	set("combat_exp", 5000000);
	set("score", 5000);

	set_skill("force", 200);
	set_skill("dodge", 200);
	set_skill("parry", 200);
	set_skill("sword", 200);
	set_skill("cuff", 200);
	set_skill("huashan-qigong", 200);
	set_skill("huashan-jianfa", 200);
	set_skill("huashan-shenfa", 200);
	set_skill("poyu-quan", 200);
	//set_skill("zhengqi-jue", 100);

	map_skill("force", "huashan-qigong");
	map_skill("parry", "huashan-jianfa");
	map_skill("dodge", "huashan-shenfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("cuff", "poyu-quan");

	prepare_skill("cuff", "poyu-quan");

	create_family("华山派", 14, "弟子");

	setup();
	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
       
        if (ob->query("shen") < 10000 ) {
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严,不足10k不要来找我。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
        }
		 if (ob->query("gender") =="女性" ) {
			command("say 师妹跟我说了，凡是女弟子都只能找她，你还是去找她吧。");
		return;
        }
       
        command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
        command("chat* 脸上浮现出一丝笑容，对着"+ob->query("name")+"笑道：我华山定将成为五岳之首。");
        command("recruit " + ob->query("id"));
        ob->set("quest/huashan","气宗");
}

// NPC: /d/huashan/npc/liangfa.c
// Date: Look 99/03/25

#include <ansi.h>

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("梁发", ({ "liang fa", "liang", "fa" }));
	set("nickname", "闭嘴佛");
	set("long", 
"梁发身材高瘦，长的有点木呐，但人确极精明，他在\n"
"同门中排行第三，是华山派年轻一代中的好手。\n");
	set("gender", "男性");
	set("age", 29);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("per", 23);
	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);
	
	set("max_qi", 5000);
	set("max_jing", 3800);
	set("neili", 5000);
	set("max_neili", 5000);
	set("eff_jingli", 3800);

	set("jiali", 50);
	set("combat_exp", 4000000);
	set("score", 4000);

	set_skill("force", 180);
	set_skill("huashan-qigong", 180);
	set_skill("dodge", 180);
	set_skill("parry", 180);
	set_skill("sword", 180);
	set_skill("cuff", 180);
	set_skill("strike", 180);
	set_skill("hunyuan-zhang", 180);
	set_skill("huashan-jianfa", 180);
	set_skill("poyu-quan", 180);
	set_skill("huashan-shenfa", 180);
	//set_skill("zhengqi-jue", 100);

	map_skill("force", "huashan-qigong");
	map_skill("dodge", "huashan-shenfa");
	map_skill("parry", "huashan-jianfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("cuff", "poyu-quan");
	map_skill("strike", "hunyuan-zhang");

	prepare_skill("cuff", "poyu-quan");

	create_family("华山派", 14, "弟子");

	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}
void attempt_apprentice(object ob)
{
       
        if (ob->query("shen") < 10000 ) {
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严,不足10k不要来找我。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
        }
       
        command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
        command("chat* 脸上浮现出一丝笑容，对着"+ob->query("name")+"笑道：我华山定将成为五岳之首。");
        command("recruit " + ob->query("id"));
        ob->set("quest/huashan","气宗");
}
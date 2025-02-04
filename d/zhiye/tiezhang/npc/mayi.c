// Npc: /u/zqb/tiezhang/npc/mayi.c
// Date: zqb 97/06/17

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
void create()
{
    set_name(HIY"麻衣大长老"NOR, ({
    "mayi zhanglao",
    "mayi",
    "zhanglao",
	}));
	set("long",
    "他是一个年约六旬的老者，满头花发，两鬓斑白。乃是铁掌帮大长老\n"
    "他两侧的太阳穴高高鼓起，微闭的双目中时而闪过凌厉的眼神，\n"
	"太阳穴高高坟起，似乎身怀绝技。\n"
	);

	set("gender", "男性");
	set("attitude", "peaceful");

	set("age", 60);
	set("shen_type", 1);
	set("str", 28);
	set("int", 23);
	set("con", 23);
	set("dex", 28);
	set("max_qi", 25000);
	set("max_jing", 4000);
	set("max_jingli", 6000);

	set("neili", 20000);
	set("max_neili", 20000);
	set("jiaji", 200);
	set("combat_exp", 4500000);
	set("score", 10000);

	set_skill("force", 350);
	set_skill("guiyuan-tunafa", 350);
	set_skill("dodge", 350);
	set_skill("shuishangpiao", 350);
	set_skill("strike", 350);
	set_skill("tiezhang-zhangfa", 350);
	set_skill("parry", 350);
	set_skill("axe", 350);
	set_skill("lietian-fu", 350);
	set_skill("liuye-daofa", 350);
	set_skill("blade", 350);

	map_skill("force", "guiyuan-tunafa");
	map_skill("dodge", "shuishangpiao");
	map_skill("strike", "tiezhang-zhangfa");
	map_skill("parry", "tiezhang-zhangfa");
	map_skill("blade", "liuye-daofa");
	map_skill("axe", "lietian-fu");
	prepare_skill("strike","tiezhang-zhangfa");
	
	create_family("铁掌帮", 15, "首席大长老");
	
	setup();
}

void attempt_apprentice(object ob)
{
      object me  = this_object();
      mapping fam = ob->query("family");

        if(!fam || fam["family_name"] != "铁掌帮"){
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
                }
        if ((int)ob->query("shen") > -500000) {
                command("hehe");
                command("say 铁掌帮可不收心慈手软的人做弟子，少于500k负神别来烦我。\n");
                return;
                }
        if(fam["master_name"] == "裘千仞"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"已是帮主亲传弟子，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
                return;
                }
        if(fam["master_name"] == "上官剑南"){
                command("ah");
                command("say 上官帮主不是早已故世多年了嘛？");
                command("say "+RANK_D->query_respect(ob)+"原来是老帮主关门弟子啊，失敬。"+RANK_D->query_self(me)+"怎敢再收你为徒？");
                return;
                }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) <= 150) {
                command("say 要学更为高深的武功，必须有高深的内功修为,150。");
                command("say " + RANK_D->query_respect(ob)+"是否还应该在归元吐纳法上多下点功夫？");
                return;
                }
                command("say 好吧，我就收下你了。希望你苦练铁掌帮神功，将之发扬光大。\n");
                command("recruit " + ob->query("id"));
                ob->set("is/tiezhang",1);
                ob->set("class","brigand");
}
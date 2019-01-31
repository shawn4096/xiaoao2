// da.c
#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("司马大", ({ "sima da", "sima", "da"}));
        set("long", 
"这大汉身材魁梧之极，巨人般的身体在走动
时，脚步声极之沉重，整个地板都为之震动。\n");
        set("title",HIY"日月神教  "GRN"青龙堂舵主"NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
       
        set("max_qi", 2000);
        set("max_jing", 1000);
	      set("eff_jingli", 1000);
        set("jiali", 50);
        set("combat_exp", 800000);

        set_skill("dodge",140);
        set_skill("literate", 120);
        set_skill("huanmo-wubu",140);
        set_skill("tianmo-gong",140);
        set_skill("strike", 140);
        set_skill("tianmo-zhang", 140);        
        set_skill("force",140);
        set_skill("parry",140);
	      set_skill("blade", 140);
	      set_skill("tianmo-dao", 140);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmo-gong");
	      map_skill("parry", "tianmo-dao");
	      map_skill("blade", "tianmo-dao");
	      map_skill("strike", "tianmo-zhang");
	      prepare_skill("strike", "tianmo-zhang"); 
	      create_family("日月神教", 9, "弟子");       
        setup();

	carry_object(BINGQI_D("blade"))->wield();
	carry_object(MISC_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") > 0 ){
        command("say 你不够心狠手辣，且心地不纯，我不收你！");
        return;
        }
	 if(ob->query("family")){
        command("say 你已有名师，来此何干！");
        return;
        }
     command("haha");
	 command("say 好吧，为了光大日月神教，我就收下你了。");
     command("recruit " + ob->query("id"));
}

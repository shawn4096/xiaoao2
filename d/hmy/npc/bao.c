// bao.c
#include <ansi.h>
inherit F_MASTER;

inherit NPC;

void create()
{
	set_name("鲍大楚", ({ "bao dachu", "bao", "dachu"}));
        set("long", "一个身材瘦削的老者，依相貌根本看不出他是身怀绝艺的高手。\n");
        set("title",HIY"日月神教  "RED"朱雀堂堂主"NOR);
        set("gender", "男性");
        
	    set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 27);
        set("int", 27);
        set("con", 27);
        set("dex", 30);
        
        set("max_qi", 3000);
        set("max_jing", 2200);
	      set("eff_jingli", 2200);
	      set("max_neili", 4000);
        set("jiali", 50);
        set("combat_exp", 2700000);

        set_skill("parry", 400);
		set_skill("tianmo-jue", 200);
        set_skill("dodge", 400);
        set_skill("force", 400);
        set_skill("strike", 400);
        set_skill("literate", 200);
        set_skill("huanmo-wubu",400);
	    set_skill("tianmo-gong", 400);
	    set_skill("tianmo-zhang", 400);
     
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
	      map_skill("parry", "tianmo-zhang");
	      map_skill("strike", "tianmo-zhang");
	      prepare_skill("strike", "tianmo-zhang");
	      create_family("日月神教", 9, "弟子");

        setup();

	carry_object(MISC_D("cloth"))->wear();          
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") >-50000){
        command("say 你不够心狠手辣，且心地不纯，我不收你！");
        return;
        }
	 if(ob->query_skill("tianmo-gong",1)<150){
        command("say 你的天魔功功力不够，你要继续努力！");
        return;
	 }
     if(ob->query_skill("tianmo-jue",1)<150){
        command("say 你的天魔诀不够，你要继续努力！");
        return;
	 }
	 
     command("haha");
	 command("say 好吧，为了光大日月神教，我就收下你了。");
     command("recruit " + ob->query("id"));
}

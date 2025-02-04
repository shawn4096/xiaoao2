// chou.c 
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("仇松年", ({ "chou songnian", "chou",}));
        set("nickname", "长发头陀");        
        set("long", "这头陀长发垂肩，头上戴着一个闪闪发光的铜箍，束着长发。\n");
        set("title",HIY"日月神教  "RED"朱雀堂旗主"NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 32);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        
        set("max_qi", 2700);
        set("max_jing", 1800);
	      set("eff_jingli", 1800);
        set("jiali", 50);
        set("combat_exp", 1500000);
        set("shen", 5000);

        set_skill("dodge",180);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("force", 200);
        set_skill("strike", 200);
        set_skill("literate", 130);
        set_skill("huanmo-wubu",190);
		 set_skill("tianmo-jue",190);
	      set_skill("tianmo-gong", 200);
	      set_skill("tianmo-zhang", 190);
     
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
     if(ob->query("shen") > 0 ){
        command("say 你不够心狠手辣，且心地不纯，我不收你！");
        return;
        }
    if(ob->query_skill("tianmo-gong",1) < 120 ){
        command("say 你的天魔功不足120，找我也学不了！");
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

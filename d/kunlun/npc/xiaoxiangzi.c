// xiaoxiangzi.c
#include <ansi.h>
inherit NPC;

void create()
{
	object ob;
	set_name("潇湘子", ({ "xiaoxiang zi", "xiaoxiang", "zi"}));
        set("long", 
"潇湘潇湘子本来是湘西名宿,名字虽然飘逸，但其人的相貌却犹如僵尸，
武功更是以僵尸为形,师出湘西门僵尸门。\n");
        set("title",HIY"蒙古三杰  "GRN"湘西名宿"NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
       
        set("max_qi", 20000);
        set("max_jing", 5000);
	      set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 9800000);

        set_skill("dodge",450);
        set_skill("literate", 220);
        set_skill("huanmo-wubu",450);
        set_skill("tianmo-gong",450);
        set_skill("strike", 450);
        set_skill("tianmo-zhang",450);        
        set_skill("force",450);
        set_skill("parry",450);
	    set_skill("club", 450);
	    set_skill("tianmo-gun", 450);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
		map_skill("parry", "tianmo-gun");
	    map_skill("club", "tianmo-gun");
	    map_skill("strike", "tianmo-zhang");
	    prepare_skill("strike", "tianmo-zhang"); 
	   // create_family("日月神教", 9, "弟子");
	   set("chat_chance_combat", 85);
		set("chat_msg_combat", ({
  		(: perform_action, "club.gunying" :),
  		(: perform_action, "club.luanwu" :),
		(: perform_action, "strike.feiwu" :),
		(: exert_function, "tianmo" :),			
		(: exert_function, "jieti" :),
		}));
        setup();
	//weapon=new("/clone/weapon/club/kusangbang");
	//weapon->wield();
	if(clonep()) {
		ob = unew("/clone/weapon/club/kusang-bang");
		if(ob) {
		ob->move(this_object());
		ob->wield();
		}
	}
	//carry_object(BINGQI_D("club"))->wield();
	carry_object(MISC_D("cloth"))->wear();
}

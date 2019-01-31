#include <ansi.h>
//inherit F_MASTER;
inherit NPC;
void create()
{
      
	set_name("黄伯流", ({ "huang boliu", "huang", "boliu"}));
	set("nickname", "银髯蛟");        
        set("long", 
		"他一部白须，直垂至胸，精神却甚矍铄。。\n");
        set("title","圣姑门下");
        set("gender", "男性");
        
	set("age", 70);
	set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 23);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        
        set("max_qi", 2500);
        set("max_jing", 1500);
        set("eff_jingli", 1500);
        set("jiali", 50);
        set("combat_exp", 2700000);
     
        set_skill("parry",270);
        set_skill("dodge",270);
        set_skill("force",270);
        set_skill("strike",270);
        set_skill("literate", 100);      
        set_skill("huanmo-wubu",270);
        set_skill("tianmo-gong",270);
        set_skill("tianmo-zhang",270);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-zhang");
        map_skill("strike", "tianmo-zhang");
        prepare_skill("strike", "tianmo-zhang");
        
	      create_family("日月神教",9,"弟子");
        setup();
}
/*

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
*/
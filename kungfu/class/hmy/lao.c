// lao.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
      
	set_name("老头子", ({ "lao touzi", "lao", "touzi",}));
	set("nickname", "黄河老祖");    
	set("title", "圣姑门下");
	set("long", "此人身材极之肥胖，远看有如一大肉球般，可身法却极之轻灵，动作如闪电般迅速。\n");
	set("gender", "男性");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen", 10000);
	set("str", 22);
	set("int", 25);
	set("con", 21);
	set("dex", 40);
        
	set("max_qi", 5300);
	set("max_jing", 3400);
	set("eff_jingli", 3400);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("shen", -4000);

	set_temp("apply/attack", 150);
	set_temp("apply/defence", 140);

	set_skill("tianmo-dao",250);
	set_skill("blade", 250);
	set_skill("dodge",250);
	set_skill("huanmo-wubu", 250);
	set_skill("force", 250);
	set_skill("literate", 100);
	set_skill("tianmo-gong", 250);
	set_skill("parry", 250);
	//set_skill("tianmo-zhang", 250);
	//set_skill("strike", 250);
	
	map_skill("parry", "tianmo-dao");
	map_skill("blade", "tianmo-dao");
	 map_skill("dodge", "huanmo-wubu");
	 map_skill("force", "tianmo-gong");
	//map_skill("strike", "tianmo-zhang");
	//prepare_skill("strike", "tianmo-zhang");
	setup();
	create_family("日月神教",9,"弟子");
	carry_object(BINGQI_D("blade"))->wield();
	carry_object("/clone/misc/cloth")->wear();        
}
void attempt_apprentice(object ob)
{
     if(ob->query("int") < 25 ){
        command("say 你一看就傻头傻脑的，悟性这么低，连20悟性都不到，我收你何用？！");
        return;
        }
/*	 if(ob->query("gender") =="女性" ){
        command("say 女弟子很是麻烦，我看你还是去寻找下蓝凤凰看看，听说她正在招收女弟子？！");
        return;
        }
	 	// if(!ob->query("family") || ob->query("family/family_name")!="日月神教" ){
	 if(ob->query("family/family_name")!="日月神教" ){
        command("say 你已有名师，来此何干!！");
        return;
        }*/
	if(ob->query("gender") =="无性" ){
        command("say 你这种不男不女的货色来拜我为师？！");
        return;
        }
     command("haha");
	 command("say 好吧，为了光大日月神教，我就收下你了。");
     command("recruit " + ob->query("id"));
}
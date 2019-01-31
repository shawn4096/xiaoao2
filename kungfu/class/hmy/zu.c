// zu.c

#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("祖千秋", ({ "zu qianqiu", "zu",}));
        set("nickname","黄河老祖");
		set("title","圣姑门下");
        set("long", 
"只见他面皮焦黄，双目无神，疏疏落落有几根
胡子，身材颇瘦削，却挺着个大肚子。\n");
        set("age", 80);        
        set("gender", "男性");
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 6800);
		set("qi", 6800);
		set("jing", 5300);
        set("max_jing", 5300);
        set("neili", 7000);
        set("max_neili", 7000);
		set("eff_jingli", 4700);
		set("jingli", 4700);
        set("jiali", 50);
        set("combat_exp", 200000);
        set("shen", -2000);

		set_temp("apply/attack", 140);
		set_temp("apply/defence", 140);

        set_skill("tianmo-zhang",250);
		set_skill("strike", 250);
        set_skill("dodge",250);
		set_skill("huanmo-wubu", 250);
		set_skill("parry", 250);
		set_skill("force", 250);
		set_skill("literate", 100);
		set_skill("tianmo-gong", 250);

        map_skill("strike", "tianmo-zhang");
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
		map_skill("parry", "tianmo-zhang");
		prepare_skill("strike", "tianmo-zhang");
		create_family("日月神教",9,"弟子");

        setup();
		carry_object("/clone/misc/cloth")->wear();
}
void attempt_apprentice(object ob)
{
     if(ob->query("str") < 25 ){
        command("say 你天魔掌需要高的臂力，你臂力不足25，我不收你！");
        return;
        }
	 if(!ob->query("family") || ob->query("family/family_name")!="日月神教" ){
        command("say 你已有名师，来此何干！");
        return;
        }
	/* if(ob->query("gender") =="女性" ){
        command("say 女弟子很是麻烦，我看你还是去寻找下蓝凤凰看看，听说她正在招收女弟子？！");
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
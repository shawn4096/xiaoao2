// xiaoxiangzi.c
#include <ansi.h>
inherit NPC;

void create()
{
	object ob;
	set_name("尹克西", ({ "yin kexi", "yin", "kexi"}));
        set("long", 
"尹克西是波斯大贾，专精珠宝，相貌高鼻深目，曲发黄须，虽然是个胡人，
身上穿的却是汉服，颈悬明珠，腕带玉镯，珠光宝气。他祖孙三代在汴梁、
长安、太原等地贩卖珠宝，所以才取了个中国姓名叫作尹克西。\n");
        set("title",HIY"蒙古三杰  "HIG"波斯大贾"NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        set("shen",1000000);

        set("max_qi", 20000);
        set("max_jing", 5000);
	      set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 9800000);
		set("class","bonze");

        set_skill("dodge",450);
		set_skill("buddhism",200);
        set_skill("literate", 220);
        set_skill("huanmo-wubu",450);
        set_skill("tianmo-gong",450);
        set_skill("strike", 450);
        set_skill("tianmo-zhang",450);        
        set_skill("force",450);
        set_skill("parry",450);
	    set_skill("whip", 450);
		set_skill("poison", 150);
	    set_skill("cihang-bian", 450);
		set_skill("kurong-changong", 350);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
		map_skill("parry", "cihang-bian");
	    map_skill("whip", "cihang-bian");
	    map_skill("strike", "tianmo-zhang");
	    prepare_skill("strike", "tianmo-zhang"); 
	   // create_family("日月神教", 9, "弟子");
	   set("chat_chance_combat", 85);
		set("chat_msg_combat", ({
  		(: perform_action, "whip.cibei" :),
  		(: perform_action, "strike.kuaigong" :),
		(: perform_action, "strike.feiwu" :),
		(: exert_function, "tianmo" :),			
		(: exert_function, "jieti" :),
		}));
        setup();
	//weapon=new("/clone/weapon/club/kusangbang");
	//weapon->wield();
	if(clonep()) {
		ob = unew("/clone/weapon/whip/jinlong-bian");
		if(ob) {
		ob->move(this_object());
		ob->wield();
		}
	}
	//carry_object(BINGQI_D("club"))->wield();
	carry_object(MISC_D("cloth"))->wear();
}

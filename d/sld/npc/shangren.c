// shangren.c 商人

inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("商人", ({ "shang ren", "shang", "ren" }) );
	set("gender", "男性" );
	set("age", 34);
	set("long",
		"这位商人正笑咪咪地来回忙著，还不时招呼着过往的客人。\n");
	set("combat_exp", 300000000);
	set("attitude", "peaceful");
	    set("per",15);
        set("shen", 10000000);
        set("str", 1300);
        set("int", 125);
        set("con", 1270);
        set("dex", 1209);
        set("no_skill", 1);
		set("no_fight",1);
        set("no_steal",1);
		set("no_ansuan",1);
        
		set("max_qi", 5000000); 
        set("max_jing", 300000);
        set("neili", 500000);
        set("max_neili", 500000);
        set("jingli", 20000);
        set("eff_jingli", 20000);
        set("jiali", 1000);
        set_skill("parry", 1800);
        set_skill("dodge", 1800);
		set_skill("taiji-quan",1800);
        set_skill("cuff", 1800);
		map_skill("cuff","taiji-quan");
		map_skill("parry","taiji-quan");
        prepare_skill("cuff","taiji-quan");
		set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                
                (: perform_action, "cuff.dongjing" :),
              
                (: perform_action, "cuff.an" :),
                (: perform_action, "cuff.yinyang" :),
                (: perform_action, "cuff.gangrou" :),
               

                (: perform_action, "cuff.zhannian" :),
                
                (: perform_action, "cuff.luanhuan" :),
                (: perform_action, "cuff.ji" :)
        }));
	set("rank_info/respect", "商人");
	set("vendor_goods", ({
		(["name": __DIR__"obj/shengzi","number" : 3000]),
		(["name": MISC_D("fire"),"number" : 5000]),
	}));
        setup();
	add_money("coin", 90);
	carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void die()
{
	object ob;
	
	
	if (!query_temp("living"))
	{
		ob = new("/d/sld/npc/shangren");
		
		
		   ob->move("/d/sld/haitan");
	}
	::die();
}

// fengtiannan.c
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("凤天南", ({ "feng tiannan", "feng" }));
        set("long", "这人正是五虎门掌门人南霸天凤天南。
只见他上唇留着两撇花白小髭，约莫五十来岁年纪，右腕戴一只汉玉镯，
左手拿着一个翡翠鼻烟壶，俨然是个养尊处优的大乡绅模样，实不似个
坐地分赃的武林恶霸，只是脚步凝稳，双目有威，多半武功高强。
\n");
        set("gender", "男性" );
	set("attitude", "peaceful");
        set("age", 55);
        set("no_get", "凤天南对你而言太重了。\n");
        set("unique", 1);
	set("shen", -10000);

	set("str", 30);
        set("int", 20);
        set("con", 10);
        set("dex", 20);

	set("max_qi",22500);
        set("max_jing",6500);
        set("neili",23500);
        set("max_neili",3500);

        set("jingli",2200);
        set("eff_jingli",5200);
        set("jiali",200);   
		set("combat_exp", 9800000);
       
       set_skill("staff", 460);
       set_skill("cuff", 460);
       set_skill("force",460);
       set_skill("dodge",460);
       set_skill("parry",460);
       set_skill("wushang-dali",480);
       set_skill("qingmang-jianfa", 480);
      
       map_skill("staff", "wushang-dali");
       map_skill("parry", "wushang-dali");
       map_skill("dodge", "qingmang-jianfa");
	   set("chat_chance_combat", 100);
	   set("chat_msg_combat", ({
			(: perform_action, "staff.dali" :),

		}));

       setup();
       carry_object(ARMOR_D("cloth"))->wear();
       carry_object(BINGQI_D("gangzhang"))->wield();
       carry_object("/d/foshan/obj/yaoshi");
}

void init()
{	
	object ob; 
	ob = this_player();
	::init();
	if( interactive(ob))
	{
		if (ob->query_temp("xd/laoseng/killfeng"))
		{
			message_vision(HIR"凤天南喝道，“既然好事被撞破了，那就纳命来”！\n"NOR,ob);
			this_object()->kill_ob(ob);
		}
		remove_call_out("greeting");
		call_out("greeting", 1, ob);		
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
          this_object()->kill_ob(ob);        
}

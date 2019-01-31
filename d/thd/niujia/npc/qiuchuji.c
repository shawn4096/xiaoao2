// qiu.c 丘处机
// Modified By action@SJ 2008/8/12
// Update By action@SJ 2009/2/21

#include <ansi.h>
inherit NPC;
void create()
{
	set_name("丘处机", ({"qiu chuji", "qiu"}));
	set("long",
                "他就是江湖上人称‘长春子’的丘处机丘真人，他方面大耳，\n"
                "满面红光，剑目圆睁，双眉如刀，相貌威严，平生疾恶如仇。\n");
	set("title","全真七子之二");
	set("gender", "男性");
	set("age", 26);
	set("nickname",HIM"长春子"NOR);
	set("shen_type",1);
	set("attitude", "peaceful");

	set("str", 50);
	set("int", 55);
	set("con", 50);
	set("dex", 50);

	      set("max_qi", 48000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);

			set("jingli", 7000);
		
        set("eff_jingli", 7000);

			set("combat_exp", 12000000);
        set_skill("force", 480);
        set_skill("xiantian-gong", 480);
        set_skill("sword", 480);
        set_skill("quanzhen-jianfa",480);
        set_skill("dodge", 480);
        set_skill("jinyan-gong", 480);
        set_skill("parry", 480);
        set_skill("strike", 480);
        set_skill("haotian-zhang", 480);
        set_skill("literate", 250);
		
//set_skill("hand",220);

		set_skill("tiangang-beidouzhen",480);
 
		//set_skill("finger", 220);
        set_skill("taoism",200);
	    set_skill("medicine", 200);
        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("strike", "haotian-zhang");
		map_skill("parry", "quanzhen-jianfa");

        prepare_skill("strike","haotian-zhang");
        
	      create_family("全真教", 2, "弟子");
/*
	      set("inquiry", ([               
                "剑诀" : (: qzjf_jianjue :),
			   "七星绝命剑" : (: qixing :),
                           ]));		       
                    
*/
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
					(: exert_function, "wuqi" :),
					(: exert_function, "yusuo" :),
        }));
        	setup();
	carry_object("/d/wudang/obj/greenrobe")->wear();
	carry_object("/clone/weapon/sword")->wield();
	add_money("silver",50);
}

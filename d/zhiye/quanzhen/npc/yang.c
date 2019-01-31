// yang.c 杨过
// By River 98.8

#include <ansi.h>
//#include "yang.h"
inherit NPC;
//inherit F_MASTER;

void create()
{
	set_name("杨过",({"yang guo","yang","guo"}));
	set("title",HIW"古墓侠侣"NOR);
	set("nickname",HIY"神雕大侠"NOR);
	set("long", "他就是名满天下的杨过。虽断一臂但仍遮不去一脸的英雄豪气。\n");
	set("age", 39);
	set("attitude", "peaceful");
	set("gender", "男性");
	set("shen", 10000);
	set("per", 36);
	set("str", 40);
	set("int", 35);
	set("con", 40);
	set("dex", 35);

        set("max_qi", 50000);
        set("max_jing", 7000);
        set("neili", 58500);
        set("eff_jingli", 7500);
        set("max_neili", 58500);
        set("jiali", 100);
        set("combat_exp", 15800000);
        set("unique", 1);

        set_skill("sword",550);

		set_skill("qimen-bagua",150);
		
set_skill("dodge",500);
        set_skill("strike",550);
        set_skill("force", 550);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);

		set_skill("yunu-jianfa", 500);
		//
set_skill("finger",140);
        set_skill("literate", 350);
        set_skill("xiantian-gong", 220);
		//
set_skill("hamagong",300);
        set_skill("medicine",120);
        //set_skill("jingmai-xue", 80);
        set_skill("yunu-shenfa", 500);
        set_skill("xuantie-jianfa", 550);
        set_skill("anran-zhang", 550);
        set_skill("quanzhen-jianfa",500);
        set_skill("tianluo-diwang", 500);
        set_skill("yunu-xinjing",550);
        set_skill("jiuyin-zhengong",220);
        set_skill("meinu-quanfa",500);

		map_skill("force", "yunu-xinjing");        
        map_skill("sword","xuantie-jianfa");
        map_skill("dodge", "yunu-shenfa");
        map_skill("parry", "anran-zhang");        
        map_skill("hand", "tianluo-diwang");
        map_skill("strike", "anran-zhang");        
        prepare_skill("strike","anran-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
		(: exert_function, "xinjing" :),
		//(: pfm_haichao :),
		(: perform_action, "strike.anran":),
		(: perform_action, "strike.jishi":),
			(: perform_action, "strike.qiren":),
			(: perform_action, "strike.shengyou":),
			(: perform_action, "strike.tuoni":),
			(: perform_action, "strike.wuse":),
			
	}));

	//create_family("古墓派",3,"男主人");
/*
	set_temp("apply/damage", 70);
	set_temp("apply/dodge", 60);
	set_temp("apply/attack", 60);
	set_temp("apply/armor", 70);
*/
	
        set("inquiry", ([
		"古墓" : "那日华山与众英雄诀别后和龙儿隐居于此已有数年，不闻世事，能与\n"+
			"龙儿在此长伴一世，此身足矣！",
		"小龙女" : "龙儿乃我爱妻，你问她做甚？",
		////"玄铁剑" : (: ask_sword :),
		//"玄铁剑法" : (: ask_sword :),
       // "武功"  : (: ask_skill :),
		//"郭靖"  : (: ask_guojing :),
		//"黄蓉"  : (: ask_huangrong :),
		//"郭芙"  : (: ask_guofu :),
		//"淑女剑"  : (: ask_shunv :),
	//	"黯然销魂掌"  : (: ask_anranzhang :),
		//"蒙哥"  : (: ask_mengge :),
		////"剑法"  : (: ask_skill1 :),
		////"内功"  : (: ask_skill2 :),

	]));

    setup();
	//carry_object(BINGQI_D("sword/gangjian"));
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object("/d/gumu/obj/pao1")->wear();
}

// NPC zhangwuji.c 张无忌
// Modify By River@SJ 99.6

#include <ansi.h>
#include "zhangwuji.h";
inherit NPC;
inherit F_MASTER;
string ask_book();
string ask_qishang();
string ask_shu();
string ask_me();
int ask_hdg();
string ask_ling();
string ask_getling();
string ask_fel();
string ask_jiuyang();
string ask_xinfa();
int ask_shlf();
int pfm_zhen();
int pfm_chan();
int pfm_yi();
int pfm_qishang();
int pfm_tougu();
int pfm_tisha();
int pfm_duanhun();
int ask_hu_quest();
int ask_hu();
int ask_ronghe();
int ask_qsqzj();

void create()
{
	object weapon;
	set_name("张无忌",({"zhang wuji","zhang","wuji"}));
	set("title",HIY"明教第三十四代教主"NOR);
	set("long", "他就是明教的第三十四代教主。脸上带着英资勃发的笑容。\n");
	set("age", 25);
	set("per", 32);
	set("attitude", "friendly");
	set("shen", 40000);
	set("str", 35);
	set("int", 30);
	set("con", 50);
	set("dex", 30);

	set("max_qi", 50000);
	set("max_jing", 7500);
	set("neili", 50000);
	set("eff_jingli", 7500);
	set("max_neili", 50000);
	set("jiali", 150);
	set("combat_exp", 15000000);
	set("unique", 1);
	set("no_bark",1);
	set("mj/qkdny/ronghe",1);
	set("mj/jiuyang/pass",3);
	set("mj/quest/yzs",1);
	//set("",1);


	set_skill("sword", 550);
	set_skill("dodge", 550);
	set_skill("force", 550);
	set_skill("dagger", 550);
	set_skill("strike", 550);
	set_skill("hanbing-mianzhang", 550);
	set_skill("piaoyi-shenfa", 550);
	set_skill("tiyunzong", 550);
	set_skill("shenghuo-lingfa", 550);
	set_skill("jiuyang-shengong", 550);
	set_skill("lieyan-dao", 550);
	set_skill("blade", 550);
	set_skill("liehuo-jian", 550);
	set_skill("taiji-jian", 550);
	set_skill("taiji-quan", 550);
	set_skill("parry", 550);
	set_skill("cuff", 550);
	set_skill("qiankun-danuoyi", 550);
	set_skill("qishang-quan", 550);
	set_skill("literate", 350);
	set_skill("medicine", 250);
	//set_skill("xiaoyao-jian", 550);
    //set_skill("medicine", 550);
	//set_skill("shenghuo-shengong", 550);
	//set_skill("shenghuo-fumozhen", 550);
	//set_skill("yingzhua-shou", 550);
	//set_skill("hand", 550);

	map_skill("force", "jiuyang-shengong");
	map_skill("cuff","qishang-quan");
	map_skill("dagger","shenghuo-lingfa");
	map_skill("sword","taiji-jian");
	map_skill("dodge", "tiyunzong");
	map_skill("blade", "lieyan-dao");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("parry", "qiankun-danuoyi");
	prepare_skill("cuff","qishang-quan");

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: pfm_hua :),
		//	(: pfm_hua :),
		(: pfm_tisha :),
		(: pfm_qishang :),
		(: pfm_tougu :),
		(: pfm_yi :),
		//(: pfm_zhen :),
		(: pfm_duanhun :),
	}));

	create_family("明教",34,"教主");
/*
	set("inquiry", ([
		"波斯明教" : "我中土明教源于波斯明教，已有几百年厉史了，昔日小昭离我而去，\n"+
			"任波斯教主，不知她可好？吾心中常思念她，唉......",
		//"圣火令" : "圣火令是我明教的圣物，但已失落多年。",
		"谢逊" : "义父的踪迹，我是不会随便对人讲的。",
		"鲜于通"  : (: ask_hu_quest :),
		"胡青牛"  : (: ask_hu :),
		"蝴蝶谷"  : (: ask_hdg :),
		"秘籍"  : (: ask_book :),
		"七伤拳经"  : (: ask_qishang :),
		"七伤拳谱" : (: ask_shu :),
		"圣火令" : (: ask_me :),
		"铸令" : (: ask_ling :),
		"玄铁令" : (: ask_getling :),
		"乾坤大挪移神功" : (: ask_ronghe :),
		//"九阳神功" : (: ask_jiuyang :),
	    "圣火心法" : (: ask_xinfa :),
		"圣火令法绝技" : (: ask_shlf :),
		"七伤拳总决" : (: ask_qsqzj :),

		"赏善罚恶令" : (: ask_fel :),
	]));

	set_temp("apply/damage", 90);
	set_temp("apply/dodge", 90);
	set_temp("apply/attack", 90);
	set_temp("apply/armor", 90);
*/	
	setup();

	if (clonep()){
		if( sizeof(filter_array(children(BINGQI_D("shangshan_ling")), (: clonep :))) > 0 )
			weapon = new(BINGQI_D("tieling"));
		else if( sizeof(filter_array(children(BINGQI_D("fae_ling")), (: clonep :))) > 0 )
			weapon = new(BINGQI_D("tieling"));
		else weapon = unew(BINGQI_D("sf_ling"));
		if (!weapon) weapon = new(BINGQI_D("tieling"));
		carry_object(BINGQI_D("sword"));
		weapon->move(this_object());
		weapon->wield();
		carry_object("/d/mingjiao/obj/white-cloth")->wear();
	}
}

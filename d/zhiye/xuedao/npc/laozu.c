// laozu.c 血刀老祖
// by iceland

#include <ansi.h>

inherit NPC;

void create()
{
	object weapon;
	set_name("血刀老祖", ({ "xuedao laozu", "laozu","xuedaolaozu" }));
	set("long",@LONG
他身材高瘦，眼窝深陷，一双眼睛射出凶狠的光芒，令人不敢直视。他在江湖
中以残忍好色而著称，曾凭一手血刀经的功夫斗败无数中原的武林豪杰。
LONG
	);
	set("title", HIR "血刀门掌门" NOR);
	set("gender", "男性");
	set("class", "huanxi");
	set("age", 65);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("str", 35);
	set("int", 30);
	set("con", 35);
	set("dex", 35);
	set("max_qi", 52100);
	set("eff_jing", 9600);
	set("max_jing",9600);
	set("max_jingli",8600);
	set("eff_jingli", 8600);
	set("no_bark",1);
	set("book",1);

	set("neili", 32500);
	set("max_neili", 32500);
	set("jiali", 250);
	set("combat_exp", 12500000);
	set("score", 500000);
	set("unique", 1);
	set("quest/xd/xddf/huaxue/pass",1);
	set("quest/xd/xddf/pizhi/pass",1);
	set("quest/xd/xdj/xuedao/pass",1);
	set("quest/xd/jglts/jingang/pass",1);
	set("quest/xd/xddf/chilian/pass",1);

	set_skill("huanxi-chan", 200);
	set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuedao-daofa", 520);
	set_skill("dodge", 500);
	set_skill("xueying-dunxing", 500);
	set_skill("strike", 500);
	set_skill("hongsha-zhang", 500);
	set_skill("hand", 500);
	set_skill("lansha-shou", 500);
	set_skill("blade",520);
	set_skill("xuedao-jing",500);
	set_skill("parry", 500 );
	set_skill("jingang-liantishu", 500 );
	
//	map_skill("blade", "xuedao-daofa");
	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("hand", "lansha-shou");
	map_skill("parry", "jingang-liantishu");
	map_skill("strike", "hongsha-zhang");
	map_skill("blade", "xuedao-daofa");

	prepare_skill("hand","lansha-shou");
	prepare_skill("strike","hongsha-zhang");

	create_family("血刀门", 4, "掌门");
	set("class", "huanxi");
	set("chat_chance", 2);
	set("chat_msg", ({
		"血刀老祖抬起头，若有所思的自言自语：“月亮快圆了，得下山杀个人祭祭刀了。”\n",
		"血刀老祖恨恨的说：“什么时候再入中原，再闹个天翻地覆！”\n",
		"血刀老祖咬牙切齿，眼露凶光的说：“下次来个斩草除根，一个活口也不留！”\n",
		"血刀老祖自言自语道：“年纪大了，体力可一点也不含糊。”言下甚为得意。\n",
	}) );
	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: exert_function, "yuxue" :),
		(: exert_function, "xuedao" :),
		(: exert_function, "xuesha" :),
		(: perform_action, "blade.chuanxin" :),
		(: perform_action, "blade.liuxing" :),
		(: perform_action, "blade.shendao" :),
		(: perform_action, "blade.chilian" :),
		(: perform_action, "blade.bafang" :),
		(: perform_action, "blade.huaxue" :),
		(: perform_action, "blade.pizhi" :),
		(: perform_action, "blade.jixue" :),

	}));

	setup();
	carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();
	if (clonep()){
		weapon = unew("clone/weapon/blade/xuedao");
		if(!weapon)weapon=new(BINGQI_D("xinyuedao"));
		weapon->move(this_object());
		weapon->wield();
	}
	//add_money("gold",5);
}

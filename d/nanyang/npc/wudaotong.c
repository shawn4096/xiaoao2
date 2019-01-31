// wudaotong.c 吴道通
// sohu@xojh

#include <ansi.h>
inherit NPC;
string ask_tieling();

void create()
{
	set_name("吴道通", ({ "wu daotong", "tanzhi", "you" }) );
	set("gender", "男性");
	//set("nickname",HIW"铁头人"NOR);
	//set("title","聚贤庄少庄主");
	set("age", 40);
	set("long","他就是武林名宿，判官笔大家。\n");
	set("combat_exp", 9600000);
	set("shen_type", 1);
    set("attitude", "peaceful");
	set("unique", 1);

	set("str", 28);
	set("con", 26);
	set("int", 30);
	set("dex", 24);
	set("per", 13);

	set("max_qi", 19000);
	set("max_jing", 6000);
	set("neili", 19000);
	set("eff_jingli", 6000);
	set("max_neili", 19000);

	set_skill("force", 450);
	set_skill("qiantian-yiyang", 450);
	set_skill("qingyan-zhang", 450);
	set_skill("dodge", 450);
		set_skill("literate", 300);

	set_skill("strike", 450);
	set_skill("brush", 450);
	set_skill("yingou-bifa", 450);
	set_skill("parry", 450);
	set_skill("shaolin-shenfa", 450);
	map_skill("parry", "yingou-bifa");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("brush", "yingou-bifa");
	map_skill("force","qiantian-yiyang");
	map_skill("strike", "qingyan-zhang");
	prepare_skill("strike", "qingyan-zhang");
	set("inquiry", ([
	//	"玄铁令"	:	(: ask_tieling :),		
	]));
	set("chat_chance_combat", 80);
     
	set("chat_msg_combat", ({
		(: exert_function, "yiyang" :),
		(: perform_action, "brush.caoshu" :),
		(: perform_action, "brush.kaishu" :),
		(: perform_action, "brush.shigu" :),
	}));

	setup();
	carry_object(("clone/weapon/brush"))->wield();

	carry_object(MISC_D("jinduan"))->wear();
	carry_object(ARMOR_D("shoes"))->wear();
}

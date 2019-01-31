// youxun.c
#include <ansi.h>
inherit NPC;

void create()
{
	set_name("游迅", ({ "you xun", "xun","you"}));
	set("nickname", "滑不留手");        
        set("long", "这人头顶半秃，一部黑须，肥肥胖胖，满脸红光，神情十分和蔼可亲。\n");
        set("gender", "男性");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 27);
	set("int", 25);
	set("con", 21);
	set("dex", 34);
        
	set("max_qi", 12000);
	set("qi", 12000);
        set("max_jing", 4200);
	set("jing", 4200);
        set("neili", 6700);
        set("max_neili", 6700);
	set("eff_jingli", 5000);
	set("jingli", 5000);
        set("jiali", 150);
        set("combat_exp", 3000000);
        set("shen", -2500);

		set_temp("apply/attack", 40);
		set_temp("apply/defence", 40);

        set_skill("parry",230);
        set_skill("force",230);        
        set_skill("dodge",230);
        set_skill("strike", 230);
        set_skill("tianmo-zhang", 240);
        set_skill("literate", 100);
        set_skill("huanmo-wubu",230);
		set_skill("tianmo-gong", 230);	
		set_skill("tianmo-jian", 230);
		set_skill("sword", 230);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmo-gong");
		map_skill("sword", "tianmo-jian");
		map_skill("parry", "tianmo-jian");
		map_skill("strike", "tianmo-zhang");
		prepare_skill("strike", "tianmo-zhang");
        setup();
		carry_object("/clone/weapon/changjian")->wield();
		carry_object("/clone/misc/cloth")->wear();        
}

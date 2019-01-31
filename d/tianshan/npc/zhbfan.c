// Npc: /d/tianshan/npc/zhubfan.c
// By Linux

#include <ansi.h>
inherit NPC;

void create()
{
	object ob;
	set_name("׿����", ({ "zhuo bufan", "zhuo", "bufan"}));
	set("long",  "����������������ƮƮ����Ŀ���㣬�����ǡ�����׿������\n");
	set("gender", "����");
	set("title","һ�ֻ۽���");
	set("per",25);
        set("age", 56);
        set("shen_type",0);
        set("unique", 1);
	    set("attitude", "peaceful");
      
        set("str", 25);
        set("int", 35);
        set("con", 50);
        set("dex", 40);
		set("jiali",200);

        set("qi", 32000);
        set("max_qi", 32000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 34000);
        set("eff_jingli", 5000);
        set("max_neili", 34000);
        set("jiali", 200);
	    set("combat_exp", 94000000);

        set_skill("force",460);
        set_skill("dodge",460);
        set_skill("parry",460);
        set_skill("hand",460);
        set_skill("strike",460);
        set_skill("sword",460);

        set_skill("zhemei-shou",460);          //��ң��÷��(hand)
        set_skill("liuyang-zhang",460);        //��ɽ������(strike)(unarmed)
        set_skill("yueying-wubu",460);       //ƾ���ٷ�(dodge)
        set_skill("bahuang-gong",460);        //�˻�����Ψ�Ҷ���(force)
	    set_skill("tianyu-qijian",460);     //��ɽ����(sword)
	    set_skill("literate", 150);

        map_skill("force", "bahuang-gong");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "tianyu-qijian");
	    map_skill("sword", "tianyu-qijian");
		set("chat_chance_combat", 80);
		set("chat_msg_combat", ({
			(: perform_action, "hand.zhemei" :) ,
			(: perform_action, "strike.baihong" :) ,
			(: perform_action, "sword.jianmang" :) ,
			(: perform_action, "sword.fengwu" :) ,
			(: perform_action, "sword.piaomiao" :) ,
			(: exert_function, "duzun" :) ,
			
		}));      
        prepare_skill("hand","zhemei-shou");
        prepare_skill("strike","liuyang-zhang");

	    setup();

        add_money("silver",10+random(2));
        if (clonep()) {
		ob = unew(BINGQI_D("sword/zhougong-jian"));
		if (!ob) ob = unew(BINGQI_D("changjian"));
		ob->move(this_object());
		ob->wield();
		carry_object(ARMOR_D("cloth"))->wear();
	}       
	call_out("remove_ob", 200, this_object());
}

int remove_ob(object ob)
{
	if(!ob) return 1;
	tell_room(environment(ob), "\n"+HIR+ ob->query("name")+"˵�����������ܾ�ս���Ҹ���ˣ�\n" NOR,({  }));
	destruct(ob);
	return 1;
}

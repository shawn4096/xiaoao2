// maguangzuo.c 马光佐

#include <ansi.h>
inherit NPC;
//int greeting(object me,object ob);

void create()
{
        set_name("马光佐", ({ "ma guangzuo", "ma", "guangzuo" }) );
        set("gender", "男性");   
        set("age", 37);
        set("long","身高八尺，粗手大脚，脸带傻笑，双眼木然。\n");
        set("combat_exp", 26300000);
        set("shen_type", -1);
        set("attitude", "heroism");
        //set("unique", 1);

        set("str", 35);
        set("con", 26);
        set("int", 20);
        set("dex", 24);
        set("per", 13);

        set("max_qi", 15900);
		set("eff_qi",15900);
        set("max_jing", 5600);
		set("eff_jing",5600);
        set("neili", 15900);
		set("jingli",5600);
		set("max_jingli",5600);
        set("eff_jingli", 5600);
        set("max_neili", 15900);        

        set_skill("force", 260);  
        set_skill("tianmo-gong", 260);
        set_skill("club", 260);
        set_skill("dodge", 260);
        set_skill("strike", 260);
        set_skill("tianmo-zhang", 260);
        set_skill("parry", 260);
        set_skill("tianmo-gun", 260);
        set_skill("huanmo-wubu", 260);
        map_skill("parry", "tianmo-gun");
		map_skill("club", "tianmo-gun");

        map_skill("dodge", "huanmo-wubu");
        map_skill("strike", "tianmo-zhang");
        map_skill("force","tianmo-gong");
        prepare_skill("strike", "tianmo-zhang");
      	set("chat_chance_combat", 65);
		set("chat_msg_combat", ({
			(: perform_action, "club.gunying" :),
			(: perform_action, "club.luanwu" :),
			(: perform_action, "club.zhenfeng" :),
			(: exert_function, "tianmo" :),
			(: exert_function, "jieti" :),
		}));

        setup();        
		carry_object("/clone/weapon/gun")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
/*
int init()
{
	object ob, me;
	me=this_player();
	ob=this_object();
	
    ::init();
    if( interactive(me) && me->query_temp("qz/shouwei/target")=="马光佐")  
    {
		remove_call_out("greeting");
        call_out("greeting", 1, me,ob);
    }

}

int greeting(object me,object ob)
{
        object weapon;
        string my_id, type, type1;
        int i;
        	
        if(!me) destruct(ob);
        my_id = me->query("id");
        //weapon = ob->query_temp("weapon"); 
          
        i = me->query("max_pot") - 60-random(10);
        
		if(i < 460) i = 460;
        ob->set("combat_exp", me->query("combat_exp")/4*5);
      
        ob->set_skill("force", i);
        ob->set_skill("strike", i);
        ob->set_skill("dodge", i);
        ob->set_skill("parry", i);
		ob->set_skill("club", i);
        ob->set_skill("huanmo-wubu", i);
        ob->set_skill("tianmo-gong", i);  
        ob->set_skill("tianmo-gun", i);     
        ob->set_skill("tianmo-zhang", i); 
        ob->set("max_qi", me->query("max_qi")/3*2); 
        ob->set("max_jing", me->query("max_jing")/3*2); 
        ob->set("max_neili", me->query("max_neili")/3*2);
        ob->set("jiali", ob->query_skill("force",1)/3);
        ob->reincarnate(); 
        ob->set("eff_jing", me->query("eff_jing")/3*2);
        ob->set("jingli", me->query("jingli")/3*2);
        ob->set("neili", me->query("max_neili")/3*2);
        ob->set("qi", me->query("max_qi")/3*2);
        command("stare " + me->query("id"));
		command("say 小子纳命来！\n");
        command("kill "+me->query("id"));
		command("set wimpy 100");
		command("set wimpycmd yun jieti\yun tianmo\perform club.gunying\perform club.luanwu\perform club.zhengfeng");
		//command("");
		ob->set("victim", me->query("id"));
        return 1;
}
*/
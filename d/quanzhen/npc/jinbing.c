//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
inherit FIGHTER;
#include "skill.h"
void copy_name(object ob);
void create()
{
  set_name("金兵", ({ "jin bing", "bing" }));
	set("gender", "男性");
	set("long", "这人就是完颜洪烈派到中原的黑衣护卫金兵，来此完成秘密使命。\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", -1);
	set("unique", 1);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("strike", 300);
	set_skill("cuff",300); 
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("kunlun-zhang",300);
	set_skill("xuantian-wuji",300);
	
	map_skill("force","xuantian-wuji");
	map_skill("cuff","zhentian-quan");
	map_skill("strike","kunlun-zhang");
	map_skill("dodge","taxue-wuhen");
	map_skill("parry","zhentian-quan");
	
  prepare_skill("cuff", "zhentian-quan");
  prepare_skill("strike", "kunlun-zhang");
  
	set("combat_exp", 2000000);
	set("max_qi", 30000);
	set("max_jing", 3000);
	set("max_neili", 5000);
	set("eff_jingli",3000);
	set("qi",30000);
	set("jing",3000);
	set("jingli",3000);
	set("neili", 5000);

	setup();  
	if (!random(3))
	   add_money("gold", random(2)+1);
    carry_object("/clone/armor/junfu.c")->wear();

}
void init()
{
    object me, ob,ling;  
    int i;    
    ::init();

	me=this_player();
    ob = this_object();
	//若相遇非自己id不能触发
    if(!me) return;
	
	if(environment(me)!=environment(ob)) return;
    

	if(ob->query_temp("target")!=me->query("id")) return;
	
	
   	if (!me->query_temp("qzjob/jianxi")) return;
	

	i=me->query("max_pot");
	if(i<350) i=350;
	
	i=i-100;	
	
	//特殊武功和门派标记
	if(ob->query("type_speical"))
		ob->set("party",ob->query("type_speical"));  
    else
		ob->set("party",str_menpai[random(sizeof(str_menpai))]);  	  
	//复制门派武功
	ob->copy_menpai(({ob->query("party")}),1,random(2),20+random(80));	//复制npc的门派武功，				
	ob->copy_state();				//根据门派更新npc 的一些状态
	
	//超级npc
	if (query_temp("qzjx/super"))
	{
		i=i+10+random(30);
	}else i=i; //普通npc
	
	//设置门派武功等级
	set("long",query("long")+"这是玩家"+me->query("name")+"要追杀的金国奸细!\n");
	
	ob->set_skills_level(i);
	
	if(ob->query("type_speical"))
		ob->set("combat_exp",me->query("combat_exp")*5/4);
    else
		ob->set("combat_exp",me->query("combat_exp")); 
	ob->set("max_neili",me->query("max_neili"));
  	ob->set("max_jingli",me->query("max_jingli"));
  	ob->set("max_qi",me->query("max_qi")*3/2);
  	ob->set("max_jing",me->query("max_jing"));
	ob->set("neili",query("max_neili")*3/2);
	ob->set("jingli",query("max_jingli")*3/2);
	ob->set("eff_jingli",query("max_jingli")*3/2);
	ob->set("qi",query("max_qi"));
	ob->set("eff_qi",query("max_qi"));
	ob->set("jing",query("max_jing")*3/2);
	ob->set("eff_jing",query("max_jing")*3/2);
	//ob->set_skill("wuxing-zhen",290);
	//自动销毁由applycondition完成
	
	//判断
	if (interactive(me)
		&& objectp(ling=present("chongyang ling",me))
		&& ling->query("owner")==me->query("id")
		&& me->query_temp("qzjob/jianxi")
		&& ob->query_temp("target")==me->query("id"))
	{
		//copy_name(me);
		message_vision(YEL"$n忽然一把将$N身上的"+ling->query("name")+YEL"偷走！然后拉下面罩，原来正是你要追杀的金兵间隙！\n"NOR,me,ob);
		copy_name(ob);
		
		ling->move(ob);
		ling->set_temp("target",ob->query("id"));
		
		ob->set_temp("setok",1);
		remove_call_out("check");
		call_out("check",2, me);

	}
}

void check(object ob)
{

	if (!query_temp("setok")) return;

	if (ob->query("id") != query_temp("target")) 
	{
		ob->remove_enemy(this_object());
		ob->remove_killer(this_object());
		this_object()->remove_enemy(ob );
		this_object()->remove_killer(ob );
		tell_object(ob, "这不是尹志平让你追杀的奸细。\n");
		return;
	}
	tell_object(ob,query("name")+RED"喋喋怪笑不断，既然发现了，那就纳命来吧！\n"NOR);
	::kill_ob(ob);

}



//死亡标记
void die()
{
	object me,ob,ling;
	ob=this_object();
	

	me = ob->query_temp("last_damage_from");
	
	if(objectp(present(me,environment(ob))))
	{
	  	me->set_temp("qzjob/killover",1);
		
		if (objectp(ling=present("chongyang ling",ob)))
		{
			ling->set_temp("killer",me->query("id"));
			ling->set("long",ling->query("long")+"\n你成功杀死了金国奸细:"+ob->query("name"));
			if (ob->query_temp("qzjx/super"))
				ling->set_temp("super",1);
		}
	}

	::die();
}
//给金兵一个名字
void copy_name(object ob)
{
	mapping name;
	int i;

	i = random(3)+ 1;

	name = RNAME_D->get_random_name(i);

	if (!ob) return;
		
	set_name(name["name"], name["id"]);		
    //超级npc会显示名字
	if ( ob->query_temp("qzjob/superjx"))
	{		
		message_vision(CYN"\n$N伸手拉掉面罩，大喝一声：老子坐不改名，行不改姓，"+name["name"]+"是也。\n"NOR, this_object());
	}

}	
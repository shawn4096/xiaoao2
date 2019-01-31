//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
inherit FIGHTER;
#include "skill.h"
int clonenpc(object me);
void create()
{
  set_name("金兵探子", ({ "jinbing tanzi", "jinbing", "bing", "tanzi" }));
	set("gender", "男性");
	set("long", "这人就是大金国派到中原的探子，来此完成秘密探听中原的使命。\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", -1);
	set("unique", 1);

	set_skill("force", 350);
	set_skill("dodge", 350);
	set_skill("parry", 350);
	set_skill("strike", 350);
	set_skill("cuff",350); 
	set_skill("taxue-wuhen",350);
	set_skill("zhentian-quan",350);
	set_skill("kunlun-zhang",350);
	set_skill("xuantian-wuji",350);
	
	map_skill("force","xuantian-wuji");
	map_skill("cuff","zhentian-quan");
	map_skill("strike","kunlun-zhang");
	map_skill("dodge","taxue-wuhen");
	map_skill("parry","zhentian-quan");
	
  prepare_skill("cuff", "zhentian-quan");
  prepare_skill("strike", "kunlun-zhang");
  
	set("combat_exp", 2000000);
	set("max_qi", 35000);
	set("max_jing", 3500);
	set("max_neili", 5000);
	set("eff_jingli",3500);
	set("qi",35000);
	set("jing",3500);
	set("jingli",3500);
	set("neili", 5000);

	setup();  
	if (!random(5))
	   add_money("gold", random(2)+1);
    carry_object("/clone/armor/junfu.c")->wear();

}
int clonenpc(object me)
{
    object ob;  
    int i;    
   

	//me=this_player();
	write("1111");
    ob = this_object();
	//若相遇非自己id不能触发
    if(!me) return 0;
		write("221");

	if(environment(me)!=environment(ob)) return 0;
    	write("331");


	//if(ob->query_temp("target")!=me->query("id")) return;
	
	
   //	if (!me->query_temp("qzjob/jianxi")) return;
	

	i=me->query("max_pot");
	
	i=i-100;
	if(i<350) i=350;

	//write("1111\n");
	//特殊武功和门派标记
//	if(ob->query("type_speical"))
		//ob->set("party",ob->query("type_speical"));  
  //  else
	//	ob->set("party",str_menpai[random(sizeof(str_menpai))]);  	  
	//复制门派武功
	
	//ob->copy_menpai(({ob->query("party")}),1,random(2),20+random(80));	//复制npc的门派武功，				
	//ob->copy_state();				//根据门派更新npc 的一些状态
	
	//超级npc
	//if (query_temp("qzjx/super"))
	//{
		//i=i+10+random(30);
	//}else i=i; //普通npc
	
	//设置门派武功等级
	set("long",query("long")+"这是玩家"+me->query("name")+"要追杀的金国探子!\n");
	
	//ob->set_skills_level(i);
	
	if(ob->query("type_speical"))
		ob->set("combat_exp",me->query("combat_exp"));
    else
		ob->set("combat_exp",me->query("combat_exp")*2/3); 
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

	ob->set_temp("setok",1);
		//remove_call_out("check");
	//	call_out("check",1, me);
	
	return 1;
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
		tell_object(ob, "这不是你要追杀的金国探子。\n");
		return;
	}
	tell_object(ob,query("name")+RED"喋喋怪笑不断，全真教原来在秘密演练阵法，那就纳命来吧！\n"NOR);
	::kill_ob(ob);

}


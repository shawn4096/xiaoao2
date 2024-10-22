//标准战士文件 from Campsun
//target 为 player's id 必须项
inherit NPC;

#include <skills_pfm.h>
#include <ansi.h>
#include <r_name.h>

string *str_menpai = ({ "wd","hs","ss","gm","gb","tz","dls","mr","sld","em","mj","thd","tls","sl","kl","rysj","xxdf","ljg","xy","qzj","9y"});

void setparty(int p,int lv,int exp)
{
	object me = this_object();
	if (p>=7)
	{
		str_menpai=str_menpai-({"9y","hmg","pxj","jsj","xx"});	
		if(!random(20)) str_menpai=str_menpai+({"9y"});							
	 	if(!random(25)) str_menpai=str_menpai+({"hmg"});
    	if(!random(15)) str_menpai=str_menpai+({"pxj"});
	    if(!random(15)) str_menpai=str_menpai+({"jsj"});
	    if(!random(5)) str_menpai=str_menpai+({"xx"});
	}
	
	switch( p ){
		case 1:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),0,1,10);				
			me->set("jiali",0);
			set_skills_level(lv - 10 - random(15));
			set_temp("apply/armor", 20);
			me->set("combat_exp",exp);
		break;
		case 2:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),0,1,20);
			me->set("jiali",20);
			set_temp("apply/armor", 30);
			set_skills_level(lv - 5 - random(10));
			me->set("combat_exp",exp);
		break;
		case 3:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(2),1,30);
			me->set("jiali",40);
			set_skills_level(lv - random(10));
			set_temp("apply/armor", 40);
			me->set("combat_exp",exp + random(50000));
		break;
		case 4:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(2),1,40);
			me->set("jiali",60);
			set_skills_level(lv);
			set_temp("apply/armor", 60);
			me->set("combat_exp",exp + random(100000));
		break;
		case 5:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(3),1,50);
			me->set("jiali",80);
			set_skills_level(lv + 5 + random(5));
			set_temp("apply/armor", 80);
			me->set("combat_exp",exp + random(200000));
		break;
		case 6:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(3),1,60);
			me->set("jiali",100);
			set_skills_level(lv + 10 + random(10));
			set_temp("apply/armor", 100);
			me->set("combat_exp",exp + random(300000));
		break;
		case 7:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(3),1,70);
			me->set("jiali",120);
			set_skills_level(lv + 20 + random(20));
			set_temp("apply/armor", 120);
			me->set("combat_exp",exp + random(500000));
		break;
		case 8:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(3),1,80);
			me->set("jiali",140);
			set_skills_level(lv + random(20));
			set_temp("apply/armor", 140);
			me->set("combat_exp",exp + random(1000000));
		break;
		case 9:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(4),1,90);
			me->set("jiali",160);
			set_skills_level(lv + random(30));
			set_temp("apply/armor", 160);
			me->set("combat_exp",exp + random(1500000));
		break;
		case 10:
			copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(4),1,100);
			me->set("jiali",200);
			set_skills_level(lv + random(50));
			set_temp("apply/armor", 200);
			me->set("combat_exp",exp + random(2000000));			
           break;
        case 11:
                   copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(4),1,110);
                   me->set("jiali",250);
                   set_skills_level(lv + random(80));
                   set_temp("apply/armor", 250);
                   me->set("combat_exp",exp + random(2500000)); 
		break;	
		default :
		           copy_menpai(({str_menpai[random(sizeof(str_menpai))]}),random(4),1,110);
                   me->set("jiali",250);
                   set_skills_level(lv + random(80));
                   set_temp("apply/armor", 250);
                   me->set("combat_exp",exp + random(2500000)); 		
		break;
	}	
	if (me->query("family/family_name") == "星宿派")
		me->set("env/xx_poison","内敛");
	
	get_npc_name();
	set("long", me->query("long")+"此人看上去师承"+HIY+me->query("family/family_name")+NOR+"，擅长使用"+HIC+to_chinese(me->query("f_w_skill"))+NOR+"伤敌！\n" );
}

int checking(object me, object ob)
{
	if(!me || !ob) return 0;
	if((!me->query("qi") >= me->query("max_qi")/2) && (me->query_temp("cure") < 2)){
		 me->add("qi",me->query("max_qi")/4);
		 me->add_temp("cure",1);
		 tell_room(environment(me), me->query("name")+"深深的吸了口气，脸色顿时好了许多。\n", ({me}));
	}
	if(!me->query_temp("weapon") && !me->is_busy() && !me->is_perform())
	{
		me->map_skill("parry",me->query("nw_parry"));
		me->set("chat_msg_combat", query("u_f_pfm") + query("u_pfm"));                                 //出空手pfm
	}
	if(me->query_temp("weapon") && !me->is_busy() && !me->is_perform())
	{
		me->map_skill("parry",me->query("w_parry"));
		me->set("chat_msg_combat", query("u_f_pfm") + query("u_w_pfm"));
	}
	
	//else 
		
	if(ob->is_fighting(me)){
		// remove_call_out("checking");
		// call_out("checking", 1, me, ob);
		 return 1;
	}
	else if(!me->is_killing(ob->query("id"))){
		 ob->kill_ob(me);
		// remove_call_out("checking");
		// call_out("checking", 1, me, ob);
		 return 1;
	}
	
	return 1;
}

void kill_ob(object ob)
{
	object obj,pp;
	obj = this_object();
		
	if(!obj->query_temp("target"))
	{
		::kill_ob(ob);
		return;
	}
	pp = find_player(obj->query_temp("target"));
	if(!ob) return;
	if((obj->query_temp("target") != ob->query("id") && !query("can_guard_ob")  )
	 && !ob->query("env/invisibility") && objectp(pp) ){
		tell_room(environment(obj), obj->query("name")+"嚷嚷道：走远点，老子正忙着呢。！\n", ({obj}));
		obj->remove_enemy(ob);
        	ob->remove_killer(obj);
		return;
	}
	::kill_ob(ob);
	ob->kill_ob(obj);
}

int do_kill(object ob)
{
	object me;
	int lv,exp,b_exp,p;
	
	if(!ob) return 0;
	
	me = this_object();
	lv = (int)ob->query("max_pot");
	lv = lv-100;
	exp = ob->query("combat_exp");
	b_exp = 300000;
	p = random(3)+1;
  if (ob->query_temp("wd/wd_bonus")) p = ob->query_temp("wd/wd_bonus");             //add by campsun 


	set("max_qi",ob->query("max_qi") + ob->query("max_qi"));
	set("max_jing", ob->query("max_jing") + ob->query("max_jing"));
	set("max_neili", ob->query("max_neili") + ob->query("max_neili"));
	set("max_jingli", ob->query("max_jingli") + ob->query("max_jingli"));
	
	copy_state();
	
	//set("max_neili",(query_skill("force")-query_temp("apply/force"))*8 + exp/1000 + query_temp("apply/neili"));
	//set("max_jingli",query_skill("force")*8);
	
	set("neili",query("max_neili"));
	set("jingli",query("max_jingli"));
	set("eff_jingli",query("max_jingli"));
	set("qi",query("max_qi"));
	set("eff_qi",query("max_qi"));
	set("jing",query("max_jing"));
	set("eff_jing",query("max_jing"));

	if ( random (100) == 1 && exp > 1000000)
	me->set("double_attack", 1);
	
	me->delete("chat_msg");
	ob->kill_ob(me);
	//这里不能加，否则会导致npc异常情况
	//remove_call_out("checking");
	//call_out("checking", 1, me, ob);
}


//拷贝玩家状态 by renlai
void copy_player(object ob)
{
	object me;
	int lv,exp,b_exp,p;
	
	if(!ob) return 0;
	
	me = this_object();
	lv = (int)ob->query("max_pot");
	lv = lv-100;
	exp = ob->query("combat_exp");
	b_exp = 300000;
	p = random(3)+1;
  if (ob->query_temp("wd/wd_bonus")) p = ob->query_temp("wd/wd_bonus");             //add by campsun 


	set("max_qi",ob->query("max_qi") + ob->query("max_qi"));
	set("max_jing", ob->query("max_jing") + ob->query("max_jing"));
	set("max_neili", ob->query("max_neili") + ob->query("max_neili"));
	set("max_jingli", ob->query("max_jingli") + ob->query("max_jingli"));
	
	copy_state();
	
	//set("max_neili",(query_skill("force")-query_temp("apply/force"))*8 + exp/1000 + query_temp("apply/neili"));
	//set("max_jingli",query_skill("force")*8);
	
	set("neili",query("max_neili"));
	set("jingli",query("max_jingli"));
	set("eff_jingli",query("max_jingli"));
	set("qi",query("max_qi"));
	set("eff_qi",query("max_qi"));
	set("jing",query("max_jing"));
	set("eff_jing",query("max_jing"));	
	
	//日月job降低
	if (!ob->query_temp("ry/ry_job"))
	{
	
	if (lv>450) {	
	add_temp("apply/defense", 100);
	add_temp("apply/armor", 100);
	add_temp("apply/damage", 100);
	}
	else
	{
		//add_temp("apply/defense", 50);
	    //add_temp("apply/armor", 50);	   
	}
	}
	else
	{
		//add_temp("apply/defense", 150);
	    //add_temp("apply/armor", 150);
        //add_temp("apply/damage", 150);		
	}

	if ( random (100) == 1 && exp > 1000000)
	me->set("double_attack", 1);	
	me->delete("chat_msg");	
}



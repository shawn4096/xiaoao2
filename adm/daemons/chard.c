// chard.c
// From ES2
// Modified by Xiang@XKX
// By Spiderii@ty 加入一个描述，看上去更江湖些。。
//添加buff函数 by renlai
#include <ansi.h>
#include <worker.h>

//worker.h need modify
//clone/npc/maker.c

#define HUMAN_RACE "/adm/daemons/race/human"
#define BEAST_RACE "/adm/daemons/race/beast"
#define MONSTER_RACE "/adm/daemons/race/monster"
#define BASE_WEIGHT 40000


int removebuff(object me,string buffname,int buffvalue,string tempmark,int msg);
int removefightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg);

void create() { seteuid(getuid()); }

int sum(int n,int d)
{
        return (n*(2*10+(n-1)*d)/2);
}

void setup_char(object ob)
{
	string race;
	mapping my;
	int weight;

	my = ob->query_entire_dbase();
	if(!stringp(race = my["race"])) {
		race = "人类";
		my["race"] = race;
	}

	switch (race) {
		case "妖魔":
			MONSTER_RACE->setup_monster(ob);
			break;
		case "野兽":
			BEAST_RACE->setup_beast(ob);
			break;
		case "人类":
		default:
			HUMAN_RACE->setup_human(ob);
	}

	// avoid excess neili
	if (userp(ob)) {
		if (ob->query_skill("force") > ob->query_skill("force", 1)) {
			int i = ob->query_skill("force")*10 + my["age"]*20 + my["combat_exp"]/1000 + my["query_neili"];

			if (my["max_neili"] > i)
				my["max_neili"] = i;
			if (my["max_jingli"] > ob->query_skill("force") * 8)
			     	my["max_jingli"] = (int)ob->query_skill("force") * 8;
		}
		if (my["neili"] > my["max_neili"])
		     	my["neili"] = my["max_neili"];

		my["eff_jingli"] += my["max_jingli"];
		if (my["jingli"] > my["eff_jingli"])
		     	my["jingli"] = my["eff_jingli"];

		if( my["max_neili"] > 0 ) my["max_qi"] += my["max_neili"] / 4;
		if( my["max_jingli"] > 0 ) my["max_jing"] += my["max_jingli"] / 4;
	}
	if (undefinedp(my["jing"]))
		my["jing"] = my["max_jing"];

	if (undefinedp(my["qi"]))
		my["qi"] = my["max_qi"];

	if (undefinedp(my["eff_jing"]) || my["eff_jing"] > my["max_jing"])
		my["eff_jing"] = my["max_jing"];

	if (my["jing"] > my["eff_jing"])
	     	my["jing"] = my["eff_jing"];

	if (undefinedp(my["eff_qi"]) || my["eff_qi"] > my["max_qi"])
		my["eff_qi"] = my["max_qi"];

	if (my["qi"] > my["eff_qi"])
	     	my["qi"] = my["eff_qi"];

	if (!userp(ob) && race == "人类") {
		if (undefinedp(my["max_neili"]))
			my["max_neili"] = ob->query_skill("force") * 10 + my["age"]*20 + my["combat_exp"]/1000;
		if(undefinedp(my["neili"]))
		     	my["neili"] = my["max_neili"];
		if(undefinedp(my["max_jingli"]))
		     	my["max_jingli"] = ob->query_skill("force") * 8;
		if(undefinedp(my["eff_jingli"]))
		     	my["eff_jingli"] = my["max_jingli"];
		if(undefinedp(my["jingli"]))
		     	my["jingli"] = my["eff_jingli"];
		if(undefinedp(my["jiali"]))
		     	my["jiali"] = ob->query_skill("force")/4;
	}

	if (undefinedp(my["shen"])) {
		if (userp(ob))
			my["shen"] = 0;
		else
			my["shen"] = my["shen_type"] * my["combat_exp"] / 100;
	}

	if (!ob->query_max_encumbrance() || userp(ob))
		ob->set_max_encumbrance(BASE_WEIGHT + (my["str"]-10)*2500 + (ob->query_str(1)-my["str"])*3000);

	if (!ob->query_weight() || userp(ob)) {
		weight = my["age"] - 14;
		if (weight > 6)
			weight = 6;
		if (weight < 0)
			weight = 0;
		weight *= 2500;
		weight += BASE_WEIGHT + (my["str"]-10)*2500 - (my["dex"]-15)*1000 - (my["con"]-15)*1000;
		if (my["gender"] == "女性")
			weight = weight * 8 / 10;
		if (weight < 500)
			weight = 500;
		if(userp(ob) && weight < 25000 )
			weight = 25000;

		ob->set_weight(weight);
	}
	
	ob->reset_action();
}

// 1...5
private int get_wpar_qua(object me,object target)
{
	int qua = 1;
	int i;
	i = random(100);
	if(i>30 && !random(3)) qua+=1;
	if(i>60 && !random(4)) qua+=1;
	if(i>80 && !random(5)) qua+=1;
	if(i>90 && !random(6)) qua+=1;
	/*
	不要和富源挂钩好些
	if(me->query_kar()>15 && !random(3)) qua+=1;
	if(me->query_kar()>20 && !random(4)) qua+=1;
	if(me->query_kar()>25 && !random(5)) qua+=1;
	if(random(me->query_kar())>20 && !random(6)) qua+=1;
	*/
	return qua;
}

varargs object make_corpse(object victim, object killer)
{
	 int i;
        mapping pmap;
        object weapon;
        string skill,skill_type,die_msg;

	object corpse, *inv;
	object zhuanji;
	int lostkar=15;
			
	if(objectp(killer) && userp(killer)) lostkar += 5;
			
	if( victim->is_ghost() ) {
		inv = all_inventory(victim);
		inv->owner_is_killed(killer);
		inv -= ({ 0 });
		i = sizeof(inv);
		while(i--) inv[i]->move(environment(victim));
		return 0;
	}
// By Spiderii@ty
 if( objectp(killer))
       { 
        pmap = killer->query_skill_prepare();
        if( objectp(weapon = killer->query_temp("weapon")) )
              skill_type = weapon->query("skill_type");
        else if ( sizeof(pmap) == 0) skill_type = "unarmed";
        else if ( sizeof(pmap) == 1) skill_type = (keys(pmap))[0];
        else if ( sizeof(pmap) == 2) 
        {
         if ( (keys(pmap))[0] >= (keys(pmap))[1] )
              skill_type = (keys(pmap))[0];
         else skill_type = (keys(pmap))[1];
        }
        skill=killer->query_skill_mapped(skill_type);
       }

       if(!stringp(skill))
       die_msg = "从尸体上的累累伤痕来看，具体的死因——"+HIB"“不详”"NOR;
       else die_msg = "从尸体上的累累伤痕来看，分明是精通“"+HIR
                    +to_chinese(skill)+NOR"”绝技的江湖高手所为";

	corpse = new(CORPSE_OB);
	corpse->set_name( victim->query("name") + "的尸体", ({ "corpse", "shi ti" }));
       corpse->set("long", victim->long()
                + "然而，" + gender_pronoun(victim->query("gender")) 
                + "已经死了，只剩下一具尸体静静地躺在这里。\n"+die_msg+"。\n");

	corpse->set("age", victim->query("age"));
	corpse->set("gender", victim->query("gender"));
	corpse->set("race", victim->query("race"));
	corpse->set("victim_name", victim->query("name"));
	corpse->set("victim_id", victim->query("id"));
	corpse->set("victim_user", userp(victim));
	corpse->set("victim_exp", victim->query("combat_exp"));
	corpse->set("victim_shen", victim->query("shen"));
	corpse->set("victim_family", victim->query("family"));
	corpse->set("no_quest", victim->query_temp("no_quest"));
	if (victim->query_temp("faint_by"))
		corpse->set("kill_by", victim->query_temp("faint_by"));
	else
		corpse->set("kill_by", killer);

	victim->set_temp("die_by_from",corpse->query("kill_by"));

	corpse->set_weight(victim->query_weight());
	corpse->set_max_encumbrance(victim->query_max_encumbrance());
	corpse->move(environment(victim));

	// Don't let wizard left illegal items in their corpses.
	if( !wizardp(victim) ) {
		inv = all_inventory(victim);
		inv->owner_is_killed(killer);
		inv -= ({ 0 });
		i = sizeof(inv);
		while(i--) {
			if (inv[i]->query("embedded"))
				inv[i]->delete("embedded");
			
			if(userp(victim) && inv[i]->query("save_id"))
			{
				if(victim->query("kar") > random(lostkar)) continue;
			}
													
			if (inv[i]->query("equipped")=="worn") {
				if (inv[i]->move(corpse) && !inv[i]->wear())
					inv[i]->move(environment(victim));
			} else
				inv[i]->move(corpse);
		}
	}
	/*
	if(!objectp(victim))                 
		message("wizard:linux", "victim.......\n", users());
	if(!objectp(killer))                 
		message("wizard:linux", "killer.......\n", users());
	//add by ciwei for random weapon or armor
	
	if(objectp(victim) 
		&& !userp(victim)
		//&& !wizardp(victim) 
		&& objectp(killer) //&& !killer->is_robot()
		//&& ((killer->query_condition("job_busy") 
		//&& victim->query("combat_exp") > killer->query("combat_exp"))
		//||(userp(victim) && victim->query("combat_exp") > 1000000))
		//&& !random(20)
		//&& random(killer->query_kar()+killer->query_int()) > 40
		 )
	{
		object item;
		int qua;
		object npc;
		string type; string* types;
		string material;string* materials;
		string* status;
		int wporar = random(2);
		int level;
		
		//Type
		types = wporar?keys(WEAPON_MAP):keys(ARMOR_MAP);
		type = types[random(sizeof(types))];
		
		//Qua
		qua = get_wpar_qua(killer,victim);
		
		//Material
		materials=wporar?keys(MDESC_WEAPON):keys(MDESC_ARMOR);
		material=materials[10-(qua*2-random(2))];
		
		//Npc
		npc = new(NPC_D("maker"));
		
		npc->set_skill(wporar?"duanzao":"zhizao",random(qua*40));
		
		//Add by Linux 11-05-2004
		//level
		level = qua -1 - random(2);
		if (level < 0) level = 0;

		//Status
		status = ({});
		WORKER_D->get_status(npc,3,level,0,wporar?"weapon":"armor");
		if(npc->query("material_props"))
		{
			mapping temp = npc->query("material_props");
			if(mapp(temp)) status = copy(values(temp));
		}
		
		//Qua Modify
		if(wporar) qua -= 1;
		
		npc->set_name(""+victim->query("name")+"",({""+victim->query("id")+""}));
		//Worker
		if(wporar) item = WORKER_D->make_weapon(npc,type,qua,material,0,status);
		else item = WORKER_D->make_armor(npc,type,qua,material,0,status);
		
		if(item)
		{
			item->set("tmp_owner",getuid(killer));
			item->delete_owner();
			item->move(environment(corpse));
			tell_object(killer,"你眼中一亮看到" + victim->query("name")
				+ "的身边掉落一"+item->query("unit")+item->query("name")+"。\n");
		}
		if(npc) destruct(npc);
	}
	//The End
	*/
//add by linux
	if ( !wizardp(victim) && objectp(killer) 
		&& ( killer->query_condition("job_busy") || userp(victim) ) ) //killer is job_busy or victim is player 
	{
		//zhuanji system 
		if ( !random(20)
		&& killer->query("combat_exp") < victim->query("combat_exp")
		&& random(killer->query_kar()+killer->query_int()) > 40 
		&& victim->query("combat_exp") > 100000	)
		{
			zhuanji = new("/clone/gift/zhuanji");
			zhuanji->set("owner",killer->query("id"));
			zhuanji->set("gift_target",killer->query("id"));
			zhuanji->move(environment(corpse)); 

			tell_object(killer,"你恍惚看到" + victim->query("name") 
				+ "的行囊里露出一张纸片，似乎有一页密密麻麻的文章。\n");
		}
		//zhuanji end		
		//career system
		else if(random(100)==5 
		&& killer->query("combat_exp") < victim->query("combat_exp")){			
			int type = random(2)+1;
			int lvl = type==1?killer->query_skill("duanzao",1):killer->query_skill("zhizao",1);
			int d = lvl / 4;
			int n = random(11)+1;
			int randnum = random(sum(n,d));
			int j = 1;
			int level = 1;
			
			if (sum(6,d) < randnum)
        		{
                		j = 7;
                		while (sum(j,d) < randnum)
                        		if(random(5)) j++;
        		}
        		else {
                		while (sum(j,d) < randnum)
                        		if(random(5)) j++;
        		}
        		//message("wizard:ciwei",sprintf("n:%d d:%d lvl:%d randnum:%d j:%d\n",n,d,lvl,randnum,j),users() );
        		level = j -1;
        		if(random(125)==0) level++;
        		if(killer->query("combat_exp")*3>victim->query("combat_exp")*2 && level>6 )
        			level = 6;
        		switch(type){
				case 1:zhuanji = new("/d/zhiye/obj/kuangshi");break;
				case 2:zhuanji = new("/d/zhiye/obj/buliao");break;
				//case 3:mater = new(OBJ_DIR+"othermaterial");break;//已经限制level hehe
				//case 4:mater = new(OBJ_DIR+"zhongzi");break;
				//case 5:mater = new(OBJ_DIR+"book");break;
				default:break;
			}
			if(zhuanji){
				if(zhuanji->set_level(level)){
					zhuanji->set("owner",getuid(killer));
					zhuanji->move(environment(corpse));
					tell_room(environment(corpse),"你眼中一亮看到" + victim->query("name") 
					+ "的身边掉落一件事物。\n");
				}
				else destruct(zhuanji);
			}		
		}
		//career end
		// Added by mxzhao 2004/03/29
		// 暂时关闭，过几天开
		else if (killer->query("combat_exp") >= 100000 
			&& victim->query("combat_exp") >= killer->query("combat_exp") 
                    && random(killer->query_kar()) >= 10 
                    && (random(1000) + 1)%100 == 0 
			&& random(100) > 90) 
		{
			object obj = new("/clone/gift/loseletter");
			
			if (objectp(obj))
			{
				tell_object(killer, "一阵风吹过，从" + victim->name() 
					+ "的行囊里吹起一样东西。\n你眼疾手快，飞身将它抓住了。\n");

				tell_room(environment(corpse), "一阵风吹过，从" 
					+ victim->name() + "的行囊里吹起一样东西。\n" 
					+ killer->name() + "眼疾手快，飞身将它抓住了。\n", ({ killer }));

				obj->move(killer);
			}
		}
		// End
	}
//end
/*
	corpse->set("long", victim->long(1)
		+ "然而，" + gender_pronoun(victim->query("gender"))
		+ "已经死了，只剩下一具尸体静静地躺在那里。\n");
*/
	return corpse;
}


//有两类，1是定时的buff，到时结束(战斗前)
//2是随时检测buff，战斗或者切换技能则消失(战斗中)
//多组buff用|分割字串表示 比如cuff|sword|parry
int addbuff(object me,string buffname,int buffvalue,int bufftime,string tempmark,string msg)
{
	string* bufflist;
	int i;
	if (!objectp(me)) return 0;	
	
	if (me->query_temp(tempmark)) return 0;//避免反复叠加
	
	//单个的buff
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,buffvalue);//添buff   
	}
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++)
		{
		 
		 me->add_temp("apply/"+bufflist[i],buffvalue);//添buff  
			
		}		
	}
	
     if (tempmark) me->set_temp(tempmark,1);//添加临时标记	
		
	 call_out("removebuff",bufftime,me,buffname,buffvalue,tempmark,msg);
	 return 1;
}

//消除buff
int removebuff(object me,string buffname,int buffvalue,string tempmark,int msg)
{
	string* bufflist;
	int i;
	
	if (!me) return;
	
	//单个
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,-buffvalue);//消除buff   
	}
	//多个
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],-buffvalue);//消除buff  
			
		}		
	}
	
	
	if (tempmark) me->delete_temp(tempmark);
	if (msg) message_vision(msg+"\n"NOR, me);	//显示信息
	return 1;
}


//CHAR_D->addfightbuff

//战斗buff
// me, buffname,buffvalue,cout,skillslist,tempmark,msg
int addfightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg)
{
	string* bufflist;	
	int i;
	if (!objectp(me)) return 0;	
	if (!me->is_fighting()) return 0;//非战斗不能加
	if (me->query_temp(tempmark)) return 0;//避免反复叠加	
		
	//单个的buff
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,buffvalue);//添buff   
	}
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],buffvalue);//添buff  
			
		}		
	}

    if (tempmark) me->set_temp(tempmark,1);//添加临时标记
   
    call_out("removefightbuff",1,me,buffname,buffvalue,count,skilllist,tempmark,msg);	
	return 1;	
}

int removefightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg)
{
	string* bufflist;
	string* sk;
	int i;
	  
	 if (!me) return;
	 
	  //技能判断 taiji-quan|cuff
	if (skilllist && (strsrch(skilllist,"|") !=-1))
	{
		
		sk=explode(skilllist,"|");	
      if (sk[1] && sk[0])
	  {		  
	  if (me->query_skill_mapped(sk[1]) && me->query_skill_mapped(sk[1]) != sk[0]) 
	     {	        
	    count=0;
	     }
	  }
          else log_file("char_bufferror",sprintf("%-19sbuff出错:%8s %-5s %s",me->detail_name(),skilllist),me);
	
	}	
	
	if (!me->is_fighting()|| count<1)
	{	
	//单个
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,-buffvalue);//消除buff   
	}
	//多个
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],-buffvalue);//消除buff  
			
		}		
	}
    if (tempmark) me->delete_temp(tempmark);
	if (msg) message_vision(msg+"\n"NOR, me);	//显示信息
    me->add("neili", - (100 + random(100)));	//扣除内力
	return 1;
	}
	else
	{
		count--;
		call_out("removefightbuff",1,me,buffname,buffvalue,count,skilllist,tempmark,msg);
	}
}

// Modified by snowman@SJ 22/08/2000.
// 在YuJ增加无食水减jing,qi的基础上，屏蔽对newbie的影响。
// Modified by snowman@SJ 13/04/2001
// heal 中增加对apply/xxx 的支持。
// add apply/re_xx Ciwei@SJ
// Modified by lsxk@hsbbs for 第一届比武大会 2007/11/23
// Modified by spiderii@ty 补充sjsz小漏洞

#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <move.h>

int ghost = 0;

nosave mapping extra_listener = ([]);

int is_ghost() { return ghost; }

void set_ghost(int i) { ghost=i; }

mapping query_extra_listener()
{
	return extra_listener;
}

void register_relay_listener(string type)
{
	object ob;

	ob = previous_object();
	if (!ob) return;	
	if (arrayp(extra_listener[type])) {
		if (member_array(ob, extra_listener[type]) >=0) return;
		extra_listener[type] += ({ ob });
	} else
		extra_listener[type] = ({ ob });
}

void remove_relay_listener(string type)
{
	object ob;

	ob = previous_object();
	if (!ob) return;
	if (arrayp(extra_listener[type])) {
		if (member_array(ob, extra_listener[type]) == -1) return;
		extra_listener[type] -= ({ ob });
	}
}

varargs int receive_damage(string type, int damage, mixed who)
{
	int val;

	if( damage < 0 ) damage = 0;

	if( type!="jing" && type!="qi" && type!="jingli" && type!="neili")
		error("F_DAMAGE: 伤害种类错误。\n");

//added by snowman for some shadow npcs' hit
	if (who) set_temp("last_damage_from", who);
	if( objectp(who) ){
		 if(objectp(who->query("master_user/user")) )
			set_temp("last_damage_from", who->query("master_user/user"));
		add_temp("combat_been_damage/"+type,damage);
	}

	val = query(type) - damage;

	if( val < 0 ) val = -1;
	set(type, val);

	set_heart_beat(1);
	//write("damage="+damage);
	return damage;
}

varargs int receive_wound(string type, int damage, mixed who)
{
	int val;

	if (damage < 0) damage = 0;
	if (type!="jing" && type!="qi" && type!="neili")
		error("F_DAMAGE: 伤害种类错误。\n");

//added by snowman for some shadow npcs' hit
	if (who) set_temp("last_damage_from", who);
	if( objectp(who) ){
		 if(objectp(who->query("master_user/user")) )
			set_temp("last_damage_from", who->query("master_user/user"));
		add_temp("combat_been_wound/"+type,damage);
	}

	if (type == "neili") val = query("max_" + type) - damage;
	else val = query("eff_" + type) - damage;

	val += query_temp("apply/" + type);
	if (val < 0) val = -1;
	if (val < 0 && type == "neili") val = 0;
	if (query(type) > val && type != "neili") set(type, val);
	val -= query_temp("apply/" + type);

	if (type == "neili") set("max_" + type, val);
	else set("eff_" + type, val);

	set_heart_beat(1);

	return damage;
}

int receive_heal(string type, int heal)
{
	int val;

	if (heal < 0 ) heal = 0;
	if (type!="jing" && type!="qi" && type!="jingli")
		error("F_DAMAGE: 恢复种类错误。\n");

	val = query(type) + heal;
	if (val > query("eff_" + type) + query_temp("apply/" + type))
		val = query("eff_" + type) + query_temp("apply/" + type);

	set(type, val);

	return heal;
}

int receive_curing(string type, int heal)
{
	int max, val;

	if (heal < 0) heal = 0;
	if (type!="jing" && type!="qi")
		error("F_DAMAGE: 恢复种类错误。\n");

	val = query("eff_" + type) + heal;
	max = query("max_" + type);

	if (val > max)
		val = max;
	set( "eff_" + type, val);
	return heal;
}

void unconcious()
{
	object me = this_object(), defeater;
	int i;

	if (!living(me)) return;
	if (wizardp(me) && query("env/immortal")) return;

	if (objectp(defeater = query_temp("last_damage_from")))
		COMBAT_D->winner_reward(defeater, me);

	me->remove_all_enemy();
	set_temp("faint_by", defeater);

	tell_object(me, HIR "\n你只觉得头昏脑胀，眼前一黑，接着什么也不知道了……\n\n" NOR);
	

	if ((i = query("jing")) < 0) i = 0;
	set("jing", i/2);
	if ((i = query("qi")) < 0) i = 0;
	
	command("hp");
	me->disable_player(" <昏迷不醒>");
	
	//这里加个npc 残血，避免杀半天 by renlai
	if (query("qi")>100) i=200;
		
	set("qi", i/2);
	if ((i = query("jingli")) < 0) i = 0;
	set("jingli", i-i/4);
	//added by snowman
	if ((i = query("neili")) < 0) i = 0;
	set("neili", i/2);	
	

	set_temp("block_msg/all", 1);
	COMBAT_D->announce(me, "unconcious");

	call_out("revive", 30 + random(60 - query("con")));
	// grin YUJ@SJ 2001-05-08 06-03
	if (userp(me) && previous_object()) {
		set("no_get", "你刚想动手，对方似乎动了一下。\n");
		set("no_get_from", 1);
	} else if (userp(me)) {
		set("no_get", "对方还没有完全昏迷，等等再背吧。\n");
		call_out("delete", 10, "no_get");
	}
}

varargs void revive(int quiet)
{
	object me = this_object();

	remove_call_out("revive");
					
	// grin YUJ@SJ 2001-06-03
	if (userp(me)) {
		delete("no_get");
		delete("no_get_from");
	}
	// changed environment(environment()) into environment()->is_character(), by snowman
	while( environment()->is_character() ) me->move(environment(environment()));
	me->enable_player();
	if (!quiet) {
		COMBAT_D->announce(me, "revive");
		delete_temp("block_msg/all");
		tell_object(me, HIY "\n一股暖流发自丹田流向全身，慢慢地你又恢复了知觉……\n\n" NOR);
		command("hp");
		if (query_temp("unconcious") && query_temp("unconcious") != environment()) move(environment(), 1);
		if (environment()) environment()->relay_revive(me);
		//When revive delete this temp by Ciwei@SJ
		delete_temp("faint_by");
	} else delete_temp("block_msg/all");
	
	delete_temp("unconcious");
}

void die()
{
	object corpse;
	object me = this_object();
	mixed killer, npc_killer, poison_by;
   //object *sjsz_obj = deep_inventory(me); //这里会导致死亡异常，关闭 by renlai
   

   int db_exp, t, j;

	if (!living(me)) revive(1);
	else delete_temp("faint_by");

	// added by snowman@SJ 27/11/2000
	if( is_ghost() ) return;
	
	if (arrayp(extra_listener["die"])) 
	{
		int temp,ret=0;
		extra_listener["die"] -= ({ 0 });
		if (sizeof(extra_listener["die"])){
			for(int i=0;i<sizeof(extra_listener["die"]);i++)
			{
				temp = extra_listener["die"][i]->relay_listener(me, "die");
				ret = temp?temp:ret;
			}
		}
		if(ret) return;
	}//run the listener here 
	
	if( wizardp(me) && query("env/immortal") )
	{
		return;
	}

//这里取消了试剑山庄的判断 by renlai

	COMBAT_D->announce(me, "dead");
	command("hp");

	if (!(killer = query_temp("last_damage_from")))
	{
		if ((npc_killer = query_temp("faint_by")))
			killer=npc_killer;
		else
		killer = "莫名其妙地";
	}

	npc_killer = query_temp("faint_by");
	if ( me->query("job_npc")) {
		if ( objectp(npc_killer) && userp(npc_killer)){
			npc_killer->set("kill_job_npc/time", time());
			npc_killer->set("kill_job_npc/target", me->name());
			npc_killer->add_condition("killer", 90);
			log_file("static/JOBNPC", 
				sprintf("%8s%-10s杀死了%8s。", 
					npc_killer->name(1),
					"("+npc_killer->query("id")+")",
					me->name(),
				), npc_killer
			);
		}
		if ( objectp(killer) && userp(killer) && killer != npc_killer){
			killer->set("kill_job_npc/time", time());
			killer->set("kill_job_npc/target", me->name());
			killer->add_condition("killer", 90);
			log_file("static/JOBNPC", 
				sprintf("%8s%-10s杀死%8s。", 
					killer->name(1),
					"("+killer->query("id")+")",
					me->name(),
				), killer
			);
		}
		if ( killer != npc_killer && objectp(killer) && objectp(npc_killer) && userp(killer))
			command("chat "+npc_killer->name()+"("+capitalize(npc_killer->query("id"))+")和"+killer->name()+"("+capitalize(killer->query("id"))+")你们竟敢杀我，我做鬼也不会放过你们。");
		else {
			if ( objectp(killer) && userp(killer))
				command("chat "+killer->name()+"("+capitalize(killer->query("id"))+")你竟敢杀我，我做鬼也不会放过你。");
			if ( objectp(npc_killer) && userp(killer))
				command("chat "+npc_killer->name()+"("+capitalize(npc_killer->query("id"))+")你竟敢杀我，我做鬼也不会放过你。");
		}
	}
       poison_by = query_temp("last_poison_from");

 	// Added 特殊死亡
 	if (userp(me) && me->query_temp("special_die") && objectp(killer) && killer->query_temp("special_die"))
 		INTERJOB_D->special_die(killer, me);
	else if (userp(me) && me->query_temp("special_die") && objectp(poison_by) && poison_by->query_temp("special_poison"))
 		INTERJOB_D->special_die(poison_by, me);
       else if (!environment()->query("no_death")) {
		COMBAT_D->killer_reward(killer, me);

		// Clear all the conditions by death.
		// if the user using db_exp,this condtiion don't clear
		db_exp = me->query_condition("db_exp");
		me->clear_condition();
		if (db_exp > 0)
			me->apply_condition("db_exp",db_exp);
		
		if( objectp(corpse = CHAR_D->make_corpse(me, killer)) ) {
			corpse->move(environment());
			if( userp(me) && GROUP_D->is_group_fight(me)==1 )
				corpse->set("group_war",1);
		}
                if (environment() && !environment()->is_character() ) environment()->die(me);
		//added by Ciwei@SJ
	}
	else log_file("no_death", sprintf("%O %O\n", me, environment()));
	
		if (!(query_temp("last_damage_from")))
	{
		//if (query_temp("faint_by"))
		//	set_temp("last_damage_from", query_temp("faint_by"));
		//else
		set_temp("last_damage_from", "莫名其妙地");
	}//add by renlai
	

	me->remove_all_killer();
	all_inventory(environment())->remove_killer(me);

	me->dismiss_team();
	if (userp(me)) {
		if (me->is_busy()) {
			me->start_busy(1, 2);
			me->interrupt_me();
		}
		set("jing", 1); set("eff_jing", 1);
		set("qi", 1); set("eff_qi", 1);
		if (!environment()->query("no_death")) {
			ghost = 1;
			me->save();
			me->move(DEATH_ROOM);
			DEATH_ROOM->start_death(me);
		}
	} else destruct(me);
}

int max_food_capacity() { return query("str")*3+query("con")*7; }

int max_water_capacity() { return query("str")*3+query("con")*7; }

void reincarnate()
{
	ghost = 0;
	set("eff_jing", query("max_jing") + query_temp("apply/jing"));
	set("eff_qi", query("max_qi") + query_temp("apply/qi"));
	set("jingli", query("eff_jingli") + query_temp("apply/jingli"));
	set("jing", query("eff_jing"));
	set("qi", query("eff_qi"));
	set("neili", query("max_neili") + query_temp("apply/neili"));
	set("food", max_food_capacity());
	set("water", max_water_capacity());
}

int heal_up()
{
	int update_flag, i,t;
	object me = this_object();
	mapping my;
	t = me->query("vip/vip_time") - time();

	if (ghost || environment()->query("no_update")) return 0;
	update_flag = 0;

	my = query_entire_dbase();
	if ( my["food"] > max_food_capacity()+50 )
		my["food"] = max_food_capacity()+50;
	if ( my["water"] > max_water_capacity()+50 )
		my["water"] = max_water_capacity()+50;

	if (my["water"] > 0 && random(my["con"] + 20) < 25)  { my["water"]--; update_flag++; }
	if (my["food"] > 0 && random(my["con"] + 20) < 25) { my["food"]--; update_flag++; }
	if (me->is_busy() ) return update_flag;
	if (userp(me) && !wizardp(me)) {
		if( my["water"] < 1 ) {
                     if (t > 0) {
			message("system", HIG "\n你很久没喝水了, 还好你是贵宾用户 ...\n书剑·笑傲站送你一瓶矿泉水，你连忙一口喝了下去！\n\n" NOR,
				this_object());
			message("vision","只见"+my["name"]+"拿出一瓶矿泉水, 仰起头就狠狠地喝了一口!\n",
				environment(this_object()),this_object());
				my["water"]=max_water_capacity();
			}
			else {
			message_vision("$N渴得眼冒金星，全身无力。\n", me);
			if (random(3)) me->start_busy(5);
			else if (me->query("age") > 16) {
				receive_wound("jing", 10);
				me->set_temp("last_damage_from", "脱水时间太长渴");
			}
			return update_flag;
		}
		switch(my["water"]){
			case 50:
			case 40:
			case 30:
			case 20:
			case 10:
				message_vision(HIY"$N舔了舔干裂的嘴唇，看来是很久没有喝水了。\n"NOR, me);
		}
	}
	}	
	i = my["con"] / 3 + my["max_jingli"] / 10;
	if(me->query_temp("apply/re_jing")) i += i * (me->query_temp("apply/re_jing"))/100;
	if (me->is_fighting()) i /= 3;
	my["jing"] += i;
	if (my["jing"] >= my["eff_jing"] + me->query_temp("apply/jing")) {
		my["jing"] = my["eff_jing"] + me->query_temp("apply/jing");
		if( my["eff_jing"] < my["max_jing"] ) {
			my["eff_jing"]++;
			update_flag++;
		}
	} else update_flag++;

	i = my["con"] / 3 + my["max_neili"] / 10;
	if(me->query_temp("apply/re_qi")) i += i * (me->query_temp("apply/re_qi"))/100;
	if (me->is_fighting()) i /= 3;
	my["qi"] += i;
	if (my["qi"] >= my["eff_qi"] + me->query_temp("apply/qi")) {
		my["qi"] = my["eff_qi"] + me->query_temp("apply/qi");
		if( my["eff_qi"] < my["max_qi"] ) {
			my["eff_qi"]++;
			update_flag++;
		}
	} else update_flag++;

	if (userp(me) && !wizardp(me)) {
		if( my["food"] < 1 ) {
                     if (t > 0) {
			message("system", HIY "\n你很久没吃饭了, 还好你是贵宾用户 ...\n书剑·笑傲站给你一块牛肉干, 你狠狠地咬了两口, 觉得好过了一点 ...\n\n" NOR,
				this_object());
			message("vision","只见"+my["name"]+"拿出一块牛肉干, 狠狠地咬了两口!\n",
				environment(this_object()),this_object());
				my["food"]=max_food_capacity();
			}
			else {
			message_vision("$N饿得头昏眼花，直冒冷汗。\n", me);
			if (random(3)) me->start_busy(5);
			else if( me->query("age") > 16) {
				receive_wound("qi", 10);
				me->set_temp("last_damage_from", "太久没有进食饿");
			}
			return update_flag;
		}
		switch(my["food"]){
			case 50:
			case 40:
			case 30:
			case 20:
			case 10:
				message_vision(HIY"突然一阵“咕咕”声传来，原来是$N的肚子在叫了。\n"NOR, me);
		}
	}
	}	
	if (my["jingli"] < my["eff_jingli"] + me->query_temp("apply/jingli")) {
		i = my["con"] / 2 + me->query_skill("force", 1) / 3;
		if(me->query_temp("apply/re_jingli")) i += i * (me->query_temp("apply/re_jingli"))/100;
		if (me->is_fighting()) i /= 3;
		my["jingli"] += i;
		if (my["jingli"] > my["eff_jingli"] + me->query_temp("apply/jingli"))
			my["jingli"] = my["eff_jingli"] + me->query_temp("apply/jingli");
		update_flag++;
	}

	if (my["neili"] < my["max_neili"] + me->query_temp("apply/neili")) {
		i = me->query_skill("force", 1) / 2 + my["con"];
		if(me->query_temp("apply/re_neili")) i += i * (me->query_temp("apply/re_neili"))/100;
		if (me->is_fighting()) i /= 3;
		my["neili"] += i;
		if (my["neili"] > my["max_neili"] + me->query_temp("apply/neili"))
			my["neili"] = my["max_neili"] + me->query_temp("apply/neili");
		update_flag++;
	}

	if (my["neili"] > (my["max_neili"]+me->query_temp("apply/neili"))*2) {
		if (!me->query_temp("pending/exercise"))
			my["neili"] = (my["max_neili"] + me->query_temp("apply/neili")) * 2;
		update_flag++;
	}

	return update_flag;
}


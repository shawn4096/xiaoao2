// zongzi.c
// update by renlai 增加内容

#define CHANCE 2   //普通触发吃到特殊物品的百分比为 2%

#include <ansi.h>

inherit ITEM;

string long();

void create()
{
	int i,j, size;
	string name, id, id1,bonus;

	string *first_name=({HIR+"红枣",YEL+"鲜肉",HIY+"豆沙"});
	string *first_id=({"hongzao","xianrou","dousha"});	
	string third_name="粽"+NOR;
	string third_id="zong";
	string *bonuslist=({"combat_exp","gold","max_neili","pot ential"});

	size = sizeof(first_name);
	i = random(size);
	name = first_name[i];
	id = first_id[i];
	
	name += third_name;
	id1 = third_id;
	
	size=0;
	size= sizeof(bonuslist);
	j=0;
	j = random(size);
	bonus=bonuslist[j];	

	set_name(name, ({id+" "+id1,id,id1}));
	set_weight(500);
	set("bonus",bonus);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", (: long :));
		set("unit", "只");
		set("no_drop", 1);
		set("no_cun", 1);
		set("no_give", 1);        
		set("value", 2000);
		
	}
	setup();
}

void init()
{
	object me = this_player(), ob;

	if ( environment() == me ) {		
		add_action("do_eat", "fu");
	}

	//if ( !query("date_item")) return;

	//if ( query("owner") == getuid(me) )	return;

	//ob = find_player(query("owner"));

	//if ( ! ob) return;
/*
	if ( ob->query_temp("die_by_from") == me){
		ob->delete_temp("die_by_from");
		CHANNEL_D->do_channel( this_object(), "rumor",sprintf("%s弄到了一颗%s！", me->name(1), query("name")));
		set("owner", getuid(me));
		set("eat_time", uptime());
		
	}*/
	return;

}

string long()
{
	string str;

	str = query("name")+"("+capitalize(query("id"))+")\n";
	str += "一颗"+query("name")+"，服用(fu)以后，有";
	switch(query("bonus")) {
		case "combat_exp":	str +="增加实战经验";	break;
		case "gold":	    str +="得到金子";	break;
		case "max_neili":	str +="加大内力";	break;
		case "potential":	str +="增加潜能";	break;
		default:		str +="一定";		break;
	}
	str += "的功效。\n";
	return str;
}

int do_eat(string arg)
{
	object me = this_player();
    object obj;
   int i, max, lvl;
	string str;
	if (!id(arg)) return 0;

	if ( me->is_busy() || me->is_fighting()) 
		return notify_fail("你正忙着呢。\n");

	//if ( query("owner") != getuid(me))
	//	return notify_fail("你从什么地方得到的？\n");	
	
	
	//添加通宝物品 by renlai
	
	
	//都增加双倍
	
	if(!mapp(me->query_conditions_by_type("db_exp"))) me->apply_condition("db_exp", 10000);
	   else me->add_condition("db_exp", 10000);	
	
	//低等级玩家送不可交易的内容，高等级玩家送玉
	
		if( me->query("combat_exp") > 5000000 ) {
			 
			message_vision(HIW"$N刚放进嘴里一咬，只听“咯嘣”一声，咬碎一颗牙齿！\n"NOR,me);
			obj = new("/clone/zhiye/othermaterial");			
			
			obj->set_level(6,random(2)?1:2);
			obj->move(me);			
			obj->set("date_item",1);
			CHANNEL_D->do_channel( this_object(), "rumor",sprintf("有人看到%s从粽子里吃到了一块%s！", me->name(1), obj->query("name")));
			message_vision(HIR"$N把嘴里的“异物”拿出来定睛一看，原来是块"HIC"美玉"HIR"！\n"NOR,me);
			destruct(this_object());
			log_file("job/shijian", sprintf("%8s%-10s食用得到%6s。\n",me->name(1),"("+getuid(me)+")",obj->query("name")), me);
			return 1;
		}	

		str = HIW"$N吃下一颗"+query("name")+HIW"，顿时觉得浑身为之一振，增加了";
		switch(query("bonus")) {
		case "combat_exp":			
				i = 10000 + random(2000);
			    me->add("combat_exp", i);
			    log_file("job/shijian", sprintf("%8s%-10s食用%6s，得到%4d点经验。\n",me->name(1),"("+getuid(me)+")",query("name"),i), me);
			    str += chinese_number(i)+"点实战经验。\n"NOR;
			break;
		case "gold":
			i = 1000000;
			me->add("balance",1000000);
			str += MONEY_D->money_str(1000000)+"两黄金。\n"NOR;
			break;
		case "max_neili":
			i = random(50) + 50;
			max = (me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000;
			if ( (me->query("max_neili") - 100 ) < max )
				me->add("max_neili", i);
			str += chinese_number(i)+"点最大内力。\n"NOR;
			break;
		case "potential":
			i = 100000;
			me->add("potential", i);			
			str += chinese_number(i)+"点潜能。\n"NOR;
			break;
		default :
			   i = 10000 + random(2000);
			    me->add("combat_exp", i);
			    log_file("job/shijian", sprintf("%8s%-10s食用%6s，得到%4d点经验。\n",me->name(1),"("+getuid(me)+")",query("name"),i), me);
			    str += chinese_number(i)+"点实战经验。\n"NOR;
	}
	
	message_vision(str, me);
	"/adm/daemons/emoted"->do_emote(me,"taste");
	if (query("date_item")) CHANNEL_D->do_channel( this_object(), "rumor",sprintf("有人看到%s服下了一颗%s！", me->name(1), query("name")));
    destruct(this_object());	
	return 1;
}


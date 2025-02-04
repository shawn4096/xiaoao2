// danwan.c
// update by lsxk@hsbbs 增加内容

#define CHANCE 2   //普通触发吃到特殊物品的百分比为 2%

#include <ansi.h>

inherit ITEM;

string long();

void create()
{
	int i,j, size;
	string name, id, id1,bonus;

	string *first_name=({HIR+"赤",YEL+"橙",HIY+"黄",HIG+"绿",HIC+"青",HIB+"蓝",MAG+"紫",HIY+"金",HIW+"银",WHT+"玉",HIM+"仙",CYN+"飞"});
	string *first_id=({"chi","cheng","huang","lv","qing","lan","zi","jin","yin","yu","xian","fei"});
	string *second_name=({"水","竹","石","肌","砂","林","龙","虎","豹","凤"});
	string *second_id=({"shui","zhu","shi","ji","sha","lin","long","hu","bao","feng"});
	string *third_name=({"丸"+NOR,"丹"+NOR});
	string *third_id=({"wan", "dan"});
	string *bonuslist=({"combat_exp","max_jingli","max_neili","potential"});

	size = sizeof(first_name);
	i = random(size);
	name = first_name[i];
	id = first_id[i];

	size = sizeof(second_name);
	i = random(size);
	name += second_name[i];
	id += second_id[i];

	size = sizeof(third_name);
	i = random(size);
	name += third_name[i];
	id1 = third_id[i];
	
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
		set("unit", "颗");
		set("no_drop", 1);
		set("no_give", 1);
		set("sjsz_item", 1);
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

	if ( ! query("secret_obj")) return;

	if ( query("owner") == getuid(me) )
		return;

	ob = find_player(query("owner"));

	if ( ! ob) return;

	if ( ob->query_temp("die_by_from") == me){
		ob->delete_temp("die_by_from");
		CHANNEL_D->do_channel( this_object(), "rumor",sprintf("%s弄到了一颗%s！", me->name(1), query("name")));
		set("owner", getuid(me));
		set("eat_time", uptime());
		
	}
	return;

}

string long()
{
	string str;

	str = query("name")+"("+capitalize(query("id"))+")\n";
	str += "一颗"+query("name")+"，服用(fu)以后，有";
	switch(query("bonus")) {
		case "combat_exp":	str +="增加实战经验";	break;
		case "max_jingli":	str +="提高精力";	break;
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
	string* items = ({
		__DIR__"ebook",		
		__DIR__"moligen",
		__DIR__"pearl",
		__DIR__"youtan",		
	});

	if (!id(arg)) return 0;

	if ( me->is_busy() || me->is_fighting()) 
		return notify_fail("你正忙着呢。\n");

	if ( query("owner") != getuid(me))
		return notify_fail("你从什么地方得到的？\n");

	if ( query("secret_obj") && query("eat_time") + 900 > uptime())
		return notify_fail("时候未到，你现在还不适合吃。\n");
	
	
	
	//添加通宝物品 by renlai
	
	if(this_object()->query("sjsz_item")){
		
		if(random(100)< CHANCE)
		{
			message_vision(HIW"$N刚放进嘴里一咬，只听“咯嘣”一声，咬碎一颗牙齿！\n"NOR,me);
			obj = new(items[random(sizeof(items))]);		
			obj->move(me);
			CHANNEL_D->do_channel( this_object(), "rumor",sprintf("有人看到%s在试剑山庄弄到了一枚%s！", me->name(1), obj->query("name")));
			message_vision(HIR"$N把嘴里的“丹丸”拿出来定睛一看，原来是"HIC+obj->query("name")+HIR"！\n"NOR,me);			
			destruct(this_object());
			log_file("job/shijian", sprintf("%8s%-10s食用得到%6s。\n",me->name(1),"("+getuid(me)+")",obj->query("name")), me);
			return 1;			
		}		
		
		
		
		
		if(random(100)< CHANCE ||(wizardp(me)&&me->query("env/digyu"))){
			message_vision(HIW"$N刚放进嘴里一咬，只听“咯嘣”一声，咬碎一颗牙齿！\n"NOR,me);
			obj = new("/clone/zhiye/othermaterial");
			//增加转生天赋解谜系的加成概率  by lsxk@hsbbs
			lvl = random(100+(int)me->query("relife/quest/txqr")/2);
			//本来是1%概率，现在再增加难度。  by lsxk@hsbbs
			if((!random(115-(int)me->query("relife/quest/txqr"))&&!random(3)) || (wizardp(me) && me->query("env/dig")=="lvl6")){
				obj->set_level(6,random(2)?1:2);
				obj->move(me);
			}
			else if(lvl>90 || (wizardp(me) && me->query("env/dig")=="lvl5")){
				obj->set_level(5,random(2)?1:2);
				obj->move(me);
			}
			else if(lvl>85 || (wizardp(me) && me->query("env/dig")=="lvl4")){
				obj->set_level(4,random(2)?1:2);
				obj->move(me);
			}
			else if(lvl>45 || (wizardp(me) && me->query("env/dig")=="lvl3")){
				obj->set_level(4,random(2)?1:2);
				obj->move(me);
			}
			else{
				obj->set_level(4,random(2)?1:2);
				obj->move(me);
			}
			//打上试剑山庄出产标记。 by lsxk@hsbbs
			obj->set("sjsz_item",1);
			CHANNEL_D->do_channel( this_object(), "rumor",sprintf("有人看到%s在试剑山庄弄到了一块%s！", me->name(1), obj->query("name")));
			message_vision(HIR"$N把嘴里的“丹丸”拿出来定睛一看，原来是块"HIC"玉石"HIR"！\n"NOR,me);
			destruct(this_object());
			log_file("job/shijian", sprintf("%8s%-10s食用得到%6s。\n",me->name(1),"("+getuid(me)+")",obj->query("name")), me);
			return 1;
		}

		//添加吃出矿石和布料几率
		if(random(100)< CHANCE || (wizardp(me)&&(me->query("env/digkuang")||me->query("env/digbu")))){
			if(wizardp(me)&&me->query("env/digkuang")){
				message_vision(HIW"$N刚放进嘴里一咬，只听“咯嘣”一声，咬碎一颗牙齿！\n"NOR,me);
				obj = new("/clone/zhiye/kuangshi");
				obj->set("kuang_des",1);
			}
			else if(wizardp(me)&&me->query("env/digbu")){
				message_vision(HIG"$N仔细观察着这颗丹丸，发现他竟然被被包裹着一层事物！\n"NOR,me);
				obj = new("/clone/zhiye/buliao");
				obj->set("bu_des",1);
			}
			else{
				if(random(2)){
					message_vision(HIW"$N刚放进嘴里一咬，只听“咯嘣”一声，咬碎一颗牙齿！\n"NOR,me);
					obj = new("/clone/zhiye/kuangshi");
					obj->set("kuang_des",1);
					}
					else{
						message_vision(HIG"$N仔细观察着这颗丹丸，发现他竟然被被包裹着一层事物！\n"NOR,me);
						obj = new("/clone/zhiye/buliao");
						obj->set("bu_des",1);
					}
				}
				lvl = random(100+(int)me->query("relife/quest/txqr")/2);
				if(wizardp(me) && me->query("env/dig")=="lvl11"){
					obj->set_level(11);
					obj->move(me);
				}
				else if(random((lvl>99?100:lvl))>90 || (wizardp(me) && me->query("env/dig")=="lvl10")){
					obj->set_level(10);
					obj->move(me);
				}
				else if((!random(115-(int)me->query("relife/quest/txqr"))&&!random(3)) || (wizardp(me) && me->query("env/dig")=="lvl9")){
					obj->set_level(9);
					obj->move(me);
				}
				else if((lvl>97&&!random(3)) || (wizardp(me) && me->query("env/dig")=="lvl8")){
					obj->set_level(8);
					obj->move(me);
				}
				else if((lvl>96 && !random(2)) || (wizardp(me) && me->query("env/dig")=="lvl7")){
					obj->set_level(7);
					obj->move(me);
				}
				else if(lvl>88 || (wizardp(me) && me->query("env/dig")=="lvl6")){
					obj->set_level(6);
					obj->move(me);
				}
				else if(lvl>70 || (wizardp(me) && me->query("env/dig")=="lvl5")){
					obj->set_level(5);
					obj->move(me);
				}
				else if(lvl>55 || (wizardp(me) && me->query("env/dig")=="lvl4")){
					obj->set_level(4);
					obj->move(me);
				}
				else if(lvl>40 || (wizardp(me) && me->query("env/dig")=="lvl3")){
					obj->set_level(4);
					obj->move(me);
				}
				else if(lvl>20 || (wizardp(me) && me->query("env/dig")=="lvl2")){
					obj->set_level(4);
					obj->move(me);
				}
				else{
					obj->set_level(4);
					obj->move(me);
				}
				//打上试剑山庄出产标记。 by lsxk@hsbbs
				obj->set("sjsz_item",1);
				if(obj->query("kuang_des")){
					CHANNEL_D->do_channel( this_object(), "rumor",sprintf("有人看到%s在试剑山庄弄到了一块%s！", me->name(1), obj->query("name")));
					message_vision(HIR"$N把嘴里的“丹丸”拿出来定睛一看，原来是块"HIB"矿石"HIR"！\n"NOR,me);
				}
				else if(obj->query("bu_des")){
				CHANNEL_D->do_channel( this_object(), "rumor",sprintf("有人看到%s在试剑山庄弄到了一卷%s！", me->name(1), obj->query("name")));
					message_vision(HIR"$N将这层事物小心剥了下来，这竟然一茧"HIW"布料"HIR"！\n"NOR,me);
				}
				destruct(this_object());
				log_file("job/shijian", sprintf("%8s%-10s食用得到%6s。\n",me->name(1),"("+getuid(me)+")",obj->query("name")), me);
				return 1;
			}
		}

		str = HIW"$N吃下一颗"+query("name")+HIW"，顿时觉得浑身为之一振，增加了";
		switch(query("bonus")) {
		case "combat_exp":
			if ( query("secret_obj") )
				i = 4000 + random(2000);
			else
				i = 110 + random(80);

			if(!query("secret_obj") && query("sjsz_item"))
				i = i * 5 / 2;
			me->add("combat_exp", i);
			log_file("job/shijian", sprintf("%8s%-10s食用%6s，得到%4d点经验。\n",me->name(1),"("+getuid(me)+")",query("name"),i), me);
			str += chinese_number(i)+"点实战经验。\n"NOR;
			break;
		case "max_jingli":
			i = random(2) + 1;
			me->add("max_jingli", i);
			me->add("eff_jingli", i);
			str += chinese_number(i)+"点最大精力。\n"NOR;
			break;
		case "max_neili":
			i = random(2) + 1;
			max = (me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000;
			if ( (me->query("max_neili") - 100 ) < max )
				me->add("max_neili", i);
			str += chinese_number(i)+"点最大内力。\n"NOR;
			break;
		case "potential":
			i = random(16) + 22;
			me->add("potential", i);			
			str += chinese_number(i)+"点潜能。\n"NOR;
			break;
		default :
			return notify_fail("有问题，请向管理员汇报。\n");
	}
	message_vision(str, me);
	"/adm/daemons/emoted"->do_emote(me,"taste");
	if ( query("secret_obj"))
		CHANNEL_D->do_channel( this_object(), "rumor",sprintf("有人看到%s服下了一颗%s！", me->name(1), query("name")));
	destruct(this_object());
	return 1;
}

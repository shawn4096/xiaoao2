// taskd.C for tasks.
// 15.03.99 by snowman@SJ
// Modified by snowman@SJ 03/09/2000

///kungfu/class/gaibang/wu.c -> /tmp/ciwei/job/wu.c 成功。
///d/xingxiu/obj/di.c -> /tmp/ciwei/job/di.c 成功。
///d/xingxiu/npc/ding.c -> /tmp/ciwei/job/ding.c 成功。
// zuo.c zuo.h

/*
用法: get_quest(this_player(), shen type(int), job type(string), family name(string))
shen type is either 1 for +shen npcs or -1 for -shen npcs,
传回是 mapping：
	["id"] = target 的 ID,
	["name"] = taget 的名字,
	["last_id"] = 上个target的id，以免重复,
	["time"] = 最后时间限制,
	["exp_reward"] = EXP 奖励,
	["pot_reward"] = POT 奖励,
	["type"] = 种类，比如 "杀", "请", "找"...,
	["family"] = 门派名，如果不给family，将等于player自己的门派名,
	["place"] = 地点，target目前的所在地.

 PS: get_time(quest["time"]) 将传回中文的时间限制.
*/

#include <job_mul.h> 
#include <get_place.h>
#include <ansi.h>

inherit F_SAVE;

#include <regions.h>

#define STUFFS	 	DATA_DIR + "task_stuffs"

private int check(object ob, object me, string fam, string type, int shen, string gender);
private int quest_reward(int exp, int texp);
string get_regions(string str);

mapping stuffs = ([ ]);
nosave string *st;

void create()
{
	seteuid(getuid());
	if( !restore() && !mapp(stuffs) )
		stuffs = ([]);
	st = keys(stuffs);
}

string query_save_file()
{
	return STUFFS;
}

mapping query_stuffs()
{
	return stuffs;
}

int set_stuff(string name, mapping etc)
{
	if (!undefinedp(stuffs[name]))
		return 0;
	stuffs[name] = etc;
	save();
	return 1;
}

int delete_stuff(string name)
{
	if (undefinedp(stuffs[name]))
		return 0;
	map_delete(stuffs, name);
	save();
	return 1;
}

string query_all_stuffs()
{
	string str = "";
	int i;
	i = sizeof(st);
	while(i--)
		str += sprintf(" %-30s  奖励：%d\n", st[i]+"("+stuffs[st[i]]["id"]+")", stuffs[st[i]]["reward"]);
	return str;
}

nosave int my_exp, quest_time;
nosave string last_id;

mapping get_quest(object me, int shen, string type, string family, string gender)
{
	object target, *living;
	int i,j;

	if(!family || !stringp(family))
		family = me->query("family/family_name");

	if(type == "找"){
		if( !stuffs || sizeof(stuffs) < 1) return 0;
		i = random(sizeof(st));
		j = stuffs[st[i]]["reward"];
		return ([
			"id":	   stuffs[st[i]]["id"],
			"name":	 st[i],
			"time":	 TIME_TICK +(j*50*60),
			"exp_reward":  j,
			"pot_reward":  j/5 + random(j/10),
			"type":	 type,
			"family":family,
		]);
	}

	if (!shen || !intp(shen))  shen = 0;
	shen = SGN(shen);

	if(!type || !stringp(type)) type = "杀";

	if(gender !="女" && gender !="男" && gender !="无性")
		gender = "无";

	my_exp = me->query("combat_exp");
	last_id = me->query_temp("quest/last_id");
	if ((quest_time = uptime()) < 180)
		quest_time = 180;
	living = filter_array(livings(), "check", this_object(), me, family, type, shen, gender);

	if (!living || sizeof(living) <= 0)
		return 0;

	i = random(sizeof(living));
	target = living[i];

	if(!objectp(target) || !stringp(target->query("id")))
		return 0;       // no target at all or cant get target's id.

	i = quest_reward(me->query("combat_exp"), target->query("combat_exp")); // get the rewards.

	if (type == "请")
		i += random(i/10);

	target->set_temp("last_quest_time", quest_time);
	return ([
		"id":		(string)target->query("id"),
		"name":		(string)target->name(1),
		"time":		TIME_TICK+(i*30*60),
		"exp_reward":	i,
		"pot_reward":	i/5 + random(i/10),
		"type":		type,
		"family":	family,
		"place":	get_place(base_name(environment(target)))+environment(target)->query("short"),
	]);
}

nosave string *no_kill_list = ({"mu ren","wang furen","jin ren","yin ren","zhong shentong","zhu cong","hou junji","shi qingshan","xuedao laozu","jiao zi","lu gaoxuan"});

private int check(object ob, object me, string fam, string type, int shen, string gender)
{
	object room;
	string room_name;

	reset_eval_cost();
	if (type == "送")
		my_exp = 0;

	if (!objectp(ob)
	|| userp(ob)
	|| ob->query("chat_msg")		// add by Yuj@SJ to void random_move NPC 2000-08-30
	|| ob->query("env/invisibility")
	|| ob->query("no_quest")
	|| ob->query("job_npc") 
	|| ob->query_temp("last_quest_time") > quest_time - 180	// 间隔三分钟 YUJ@SJ 2001-11-01
	|| member_array(ob->query("id"), no_kill_list) != -1  // special npcs, like zhong shentong, attacker, biaoshi etc.
	|| ob->query("id") == last_id
	|| ob->query("race") !="人类"
	|| ob->query("family/family_name") == fam
	|| ob->query("have_master")
	|| strsrch(base_name(ob), "/d/") != 0
	|| !objectp(room=environment(ob))
	|| room->query("no_fight")
	|| room->query("quest")
	|| strsrch(room_name = base_name(room),"/d/") != 0
	|| ob->query("startroom") != room_name	// improve by Yuj@SJ to void job NPC 2001-11-25
	|| strsrch(room_name, "/d/group") == 0
	|| strsrch(room_name, "/d/wizard/") == 0
	|| strsrch(room_name, "/d/wuguan/") == 0
	|| strsrch(room_name, "/d/death/") == 0
	|| ob->query("combat_exp") > my_exp/2*3
	|| ob->query("combat_exp") < my_exp/3*2
	)
		return 0;

	if (intp(shen) && (ob->query("shen") > 0 && shen > 0
	|| ob->query("shen") < 0 && shen < 0))
		return 0;
	if(gender != "无" && ob->query("gender") != gender) return 0;

	switch(type){
		case "请": if(ob->query("attitude")=="aggressive") return 0;
		case "送": if(strsrch(room_name,"/d/dali") == 0) return 0;
		default : return 1;
	}
}

private int quest_reward(int exp, int texp)     // need a better form here.
{
        int i = 5, j = 2;

	if( exp < texp/3*2 ) return 0;

        i *= (texp * 100 / exp);

	return i/j;
}

int is_target(object corpse, object me)
{
	mapping quest;

	if ( !mapp(quest = me->query_temp("quest"))) return 0; // didnt get the job

	if ( quest["time"] < TIME_TICK) return -3; // time up.

	if ( quest["type"] != "杀") return -1;  // job type is not killing

	if ( corpse->query("id") != "corpse"
	&& corpse->query("id") != "shouji") return 0;// it's not a corpse or head.

	if ( corpse->query("victim_id") != quest["id"]
	|| corpse->query("victim_name") != quest["name"]
	|| corpse->query("kill_by") != me)
		return -2;      // killed wrong person.

	if ( corpse->query("victim_user")) return -4;   // killed a player.
	else return 1;
}

string get_time(int i)
{
	return CHINESE_D->chinese_date(i);
}

// Modified by mxzhao 2004/05/04
string get_regions(string str)
{
	string arg = ""; 
	string *place = explode(str, "/");

	switch (place[0])
	{
	case "area":
		arg = area_names[place[1]] + region_names[place[2]];
		break;
	case "cmds":
		if (!(arg = sub_region_names[place[2]]))
		{
			arg = region_names[place[1]];
		}
		break;
	case "d":
		if (place[1] == "group" || place[1] == "zhiye") 
		{
			object room;

			if(!(room = find_object(str)))
			{
				room = load_object(str);
			}

			if (room)
			{
				if (room->query("outdoors"))
				{
					arg = room->query("outdoors");
				}
				else if (room->query("indoors"))
				{
					arg = room->query("indoors");
				}
			}
		}
		else
		{
			if (!(arg = sub_region_names[place[2]]))
			{
				arg = region_names[place[1]];
			}
		}
		break;
	default:
		break;
	}

	return arg?strip(arg):"";
}
//string get_regions(string str)
//{
//	string arg, *place = explode(str, "/");
//	object room;
//
//	if( place[0] == "d" || place[0] =="cmds") 
//	{
//		if ( place[0] == "d" && place[1] == "group") {
//			if(!( room = find_object(str)))
//				room = load_object(str);
//
//			if ( !room || (!room->query("outdoors") && !room->query("indoors"))) 
//				arg = "";
//			else
//				arg = room->query("outdoors")?room->query("outdoors"):room->query("indoors");
//		}
//		else {
//			arg = sub_region_names[place[2]];
//			if (!arg)
//				arg = region_names[place[1]];
//		}
//	} else if( place[0] == "area" )
//		arg = area_names[place[1]] + region_names[place[2]];
//
//	if( arg )
//		return strip(arg);
//
//	return "";
//}
// End

void give_reward(object me, mapping quest, int shen, int extra,mixed giver,string job)
{
	int exp, pot;
	if(!me || !mapp(quest)) return;

	exp = quest["exp_reward"];
	pot = quest["pot_reward"];

	if(extra){
		exp += extra;
		pot += extra;
	}
	if ( exp > 350 ) exp = 330 + random(20);
	
	exp = me->add_exp_combat(exp,giver,job);
	/*
        if (me->query("registered")==3){
			exp = exp * GBWU_JOB_MUL * VIP_MUL /10000;
            		pot = pot * GBWU_JOB_MUL * VIP_MUL /10000;
		}
		else
		{
			exp = exp * GBWU_JOB_MUL /100;
           		pot = pot * GBWU_JOB_MUL /100;
		}
	me->add("combat_exp", exp);
	*/
	me->add("potential", pot);
	if(me->query("potential") > me->query("max_pot"))
		me->set("potential", me->query("max_pot"));
	tell_object(me, HIY"你觉得脑中豁然开朗，增加了"+chinese_number(pot)+"点潜能和"+chinese_number(exp)+"点经验！\n"NOR);
	if(shen)
		me->add("shen", shen * quest["exp_reward"] * 3);
	me->delete_temp("quest");
	me->set_temp("quest/last_id", quest["id"]);
	me->set_temp("quest/exp_reward", exp);
	me->set_temp("quest/pot_reward", pot);
}

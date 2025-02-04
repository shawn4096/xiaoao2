// natured.c
// added reclaim and unique find. by snowman 28/10/1999
// optimized by Yuj 19991112

#include <ansi.h>
#include <mudlib.h>
#include <localtime.h>

// #define TIME_TICK (time()*60)
#define ANTIROBOT "/clone/npc/antirobotnew"
#define CALLOUT_TICK 30
#define DECLARE_FILE "/data/declare.txt"
#define TIME_TICK1 ((time()-900000000)*60)
nosave int current_day_phase, current_month;
mapping *day_phase;
string daytime = "";

string *month_time = ({
	"春天悄悄地走来了，",
	"春风轻轻地拂过你的脸庞，",
	"天气逐渐变暖了，",
	"已经是初夏时节了，",
	"知了的叫声让你感觉到了盛夏的气息，",
	"天气变得非常闷热，",
	"虽然是秋天了，天气还是有些热，",
	"中秋佳节快到了，",
	"一阵秋风吹来，卷起了地上的落叶，",
	"秋去冬来，",
	"寒风凛冽，",
	"快到年关了，",
});
string *month_desc = ({
	"这是一个初春的",
	"这是一个早春二月的",
	"这是一个阳春三月的",
	"这是一个初夏的",
	"这是一个盛夏的",
	"这是一个仲夏的",
	"这是一个初秋的",
	"这是一个秋日的",
	"这是一个深秋的",
	"这是一个初冬的",
	"这是一个隆冬的",
	"这是一个寒冬的",
});

mapping *read_table(string file);
void init_day_phase();

//取得当前的月份
int query_month()       
{ 
	mixed *local;
	local = localtime(TIME_TICK);
	return (local[LT_MON]+1);	
}

/*void create()
{
	seteuid(getuid());
	day_phase = read_table("/adm/etc/nature/day_phase");
	init_day_phase();
}
*/

void create()
{	
	string get_month, get_day;
	mixed *local;
	seteuid(getuid());
	local = localtime(TIME_TICK1);
	get_day = CHINESE_D->chinese_number(local[1]);
	get_month = CHINESE_D->chinese_number(local[4]);
	switch(get_month)
	{
		//spring weather
		case "三":
		case "四":
		case "五":
		     switch(random(2))
		     {
			case 0:
			   day_phase = read_table("/adm/etc/nature/spring_rain");
			   break;
			case 1:
			   day_phase = read_table("/adm/etc/nature/spring_sun");
			   break;
			case 2:
			   day_phase = read_table("/adm/etc/nature/spring_wind");
			   break;
		     }
		     break;
		//summer weather
		case "六":
		case "七":
		case "八":
		     switch(random(2))
		     {
			case 0:
			   day_phase = read_table("/adm/etc/nature/summer_rain");
			   break;
			case 1:
			   day_phase = read_table("/adm/etc/nature/summer_sun");
			   break;
			case 2:
			   day_phase = read_table("/adm/etc/nature/summer_wind");
			   break;
		     }
		     break;
		//autumn weather
		case "九":
		case "十":
		case "十一":
		     switch(random(2))
		     {
			case 0:
			   day_phase = read_table("/adm/etc/nature/autumn_rain");
			   break;
			case 1:
			   day_phase = read_table("/adm/etc/nature/autumn_sun");
			   break;
			case 2:
			   day_phase = read_table("/adm/etc/nature/autumn_wind");
			   break;
		     }
		     break;
		//winter weather
		case "十二":
		case "一":
		case "二":
		     switch(random(2))
		     {
			case 0:
			   day_phase = read_table("/adm/etc/nature/winter_rain");
			   break;
			case 1:
			   day_phase = read_table("/adm/etc/nature/winter_sun");
			   break;
			case 2:
			   day_phase = read_table("/adm/etc/nature/winter_wind");
			   break;
		     }
		     break;
		default:
		     day_phase = read_table("/adm/etc/nature/day_phase");
	}
	switch(get_day)
	{
		case "一月一日":
		     day_phase = read_table("/adm/etc/nature/spring");
		     break;
//		case "五月五日":
//		case "七月七日":
//		case "八月十五日":
//		case "九月九日":
//		case "十二月八日":
	}
//	day_phase = read_table("/adm/etc/nature/day_phase");
	init_day_phase();
}

void init_day_phase()
{
	mixed *local;	
	int i, t;

	// Get minutes of today.
	local = localtime(TIME_TICK);
	t = local[2] * 60 + local[1];
	current_month = local[4];

	// Find the day phase for now.
	for( i=0; i < sizeof(day_phase); i++)
		if( t >= day_phase[i]["length"] )
			t -= (int)day_phase[i]["length"];
		else break;

	current_day_phase = i;
	daytime = day_phase[current_day_phase]["event_fun"];

	// MUD 运行时间久了，时间会有偏差，这里是调整程序，每小时执行一次
	// Modify by Yu Jue 98-8-20
	i = time();
	remove_call_out("init_day_phase");
	call_out("init_day_phase", 3600 - i % 3600);

	// check reboot
	//改成每隔5天重启一次 by renlai
	
	local = localtime(i);
     //local[6] == 1 &&
	 //432000是5天
	 //先改15天看看
	if (uptime() > 15*3600*24) {
		if (local[2] < 8) {
			if (find_call_out("update_day_phase") != -1)
				message("channel",
					"\n\t"+CHINESE_MUD_NAME+"将在北京时间八点至九点之间自动重新启动。\n\n", users()
				);
		} else if (local[2] < 13)
			"/cmds/common/reboot"->main(this_object(), "10");
	}
	
	

	// Since in our time scale, 1 minute == 1 second in RL, so we don't need
	// any conversion before using this number as call_out dalay, if you
	// changed the time scale, be sure to convert it.
	remove_call_out("update_day_phase");
	call_out("update_day_phase",
	day_phase[current_day_phase]["length"] - t);
	//remove_call_out("test_robot");
	//call_out("test_robot", 20+random(CALLOUT_TICK));
	remove_call_out("find_unique");
	call_out("find_unique", 60+random(CALLOUT_TICK));
	// 公告频道，定时发布信息
	//	remove_call_out("declare_channel");
	//	call_out("declare_channel",1200);
}

void declare_channel()
{
	string s_declare,txt;
	int line=1,i,totle=0,j,k;
	mapping *obj=({ });

	call_out("declare_channel",1200);

	while( s_declare = read_file(DECLARE_FILE,line,1) ) {
		if( sscanf( s_declare, "文本：%s权值：%d",	txt,i ) == 2 ) {
			obj += ({ (["txt": txt, "weight": i]) });
			totle += i;
		}

		line ++;
	}

	if( totle == 0 ) return;
	j=random(totle)+1;
	i=0;k=0;
	while(i+obj[k]["weight"]<j) {
		i+=obj[k]["weight"];
		k++;
	}
	message("channel:declare", HIY "\n【信息】"+ obj[k]["txt"]+"\n" NOR,users());
	return;
}

string query_daytime(){ return daytime; }

int is_night()
{
	switch(daytime){
		case "event_night":
		case "event_midnight":
			return 1;
		default: return 0;
	}
}

void update_day_phase()
{
	current_day_phase = (++current_day_phase) % sizeof(day_phase);
	if( !undefinedp(day_phase[current_day_phase]["event_fun"]) )
		call_other(this_object(), day_phase[current_day_phase]["event_fun"]);
	message("outdoor:vision", day_phase[current_day_phase]["time_msg"] + "\n" NOR, users());
	daytime = day_phase[current_day_phase]["event_fun"];
	remove_call_out("update_day_phase");
	call_out("update_day_phase", day_phase[current_day_phase]["length"]);

}

void event_noon()
{
        object *ob;
        object env;
        int    ic;
        int    con;
        int    month;
        string ill, msg;
        int    i;

        if (random(4)) return;
        switch(month = query_month())
        {
        case 3: case 4: case 5:
                ill = "ill_kesou";
                msg = HIG + "忽然喉头一阵痕痒，你感觉似乎要咳嗽了。\n" + NOR;
                ic  = 5;
                break;
        case 6: case 7: case 8:
                ill = "ill_zhongshu";
                msg = HIG+"突然你胸臆之间一阵翻腾，你中暑了。\n" + NOR;
                ic  = 5;
                break;
        case 9: case 10: case 11:
                ill = "ill_shanghan";
                msg = HIG+"陡的你打了个冷战，头昏沉沉的，你得伤寒病了。\n"+NOR;
                ic  = 5;
                break;
        case 12: case 1: case 2:
                ill = "ill_dongshang";
                msg = HIG+"你肢体末端一阵僵直，看来你被冻伤了。\n"+NOR;
                ic  = 0;
                break;
        }

        if (random(4) == 0)
        {
                ill = "ill_fashao";
                msg = HIG+"你偶感风寒，竟而发起烧来。\n"+NOR;
        }

        ob = users();
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! objectp(env = environment(ob[i]))) continue;
                if (! env->query("outdoors")) continue;
                if (! living(ob[i])) continue;
                if ( ob[i]->query("combat_exp") < 20000) continue;
                con = ob[i]->query_con();
                con = con / 2 + random(con);
                switch (ill)
                {
                case "ill_shanghan":
                case "ill_dongshang":
                        con += ob[i]->query_temp("apply/warm") +
                               env->query_temp("warm");
                        break;

                case "ill_zhongshu":
                        con -= ob[i]->query_temp("apply/warm") +
                               env->query_temp("warm");
                        break;
                }

                if (con + ic < 40 && !random(10))
                {
                       //ob[i]->apply_condition(ill, 30 - con);
                        ob[i]->apply_condition(ill, 60 - con);
                        //message("wizard:anger",sprintf("id:%s,type:%s\n",ob[i]->query("id"),ill), ob);
                        tell_object(ob[i], msg);
                }
        }
}

string ppl;



int filtdata(object ob)
{
	reset_eval_cost();
	if (!clonep(ob) || ob->is_character() || !ob->query("unique") || !environment(ob))
		return 0;
	return 1;
}

void find_unique() // Reclaim and find unique stuffs.
{
	object where;
	mixed *obs;
	string str;
	int i;

	remove_call_out("find_unique");
	call_out("find_unique", 120+random(CALLOUT_TICK));
	reclaim_objects();
	obs = filter_array(objects(), (: filtdata :));

	i = sizeof(obs);
	if(!i) return;
 //不要自动 reclaim，这样有错误也发现不了。
	i = sizeof(obs);
	while (i--)
	if (!environment(obs[i]) && !interactive(obs[i]) && !obs[i]->query_temp("body_ob")) {
		reset_eval_cost();
		destruct(obs[i]);
		obs -= ({ 0 });
		i = sizeof(obs);
	}

	if(!obs || sizeof(obs) < 1 ) return;

	where = environment(obs[i=random(i)]);

	if (environment(where))
		while(environment(where)->is_character())
			where = (environment(where));

	if (where->is_character()) {
		if (!environment(where))
			str = sprintf("%O", where);
		else
			str = TASK_D->get_regions(base_name(environment(where)));
		if (str == "")
			str = "中原";
		str = (!random(10)?where->query("name"):"有人")+"带着"+obs[i]->name(1)+ "在"+ str + "一带出现！";
	}
	else if(where->query("short"))
		str = "据说"+obs[i]->name(1)+ "好象藏在"+ TASK_D->get_regions(base_name(where)) + where->query("short") + "附近！";
	
	if(!str) return;
	
	CHANNEL_D->do_channel(this_object(), "rumor", str);
}

// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
void event_sunrise()
{
	int i = localtime(TIME_TICK)[4];

	if (i != current_month) {
		message("outdoor:vision", month_time[i], users());
		current_month = i;
	}
}

string outdoor_room_description()
{
	return "　　" + sprintf(
		day_phase[current_day_phase]["desc_msg"],
		month_desc[current_month]) + "。\n" NOR;
}

string game_time()
{
	return CHINESE_D->chinese_date(TIME_TICK);
}

// This function is to read a regular type of data table for day_phase and
// etc.
mapping *read_table(string file)
{
	string *line, *field, *format;
	mapping *data;
	int i, rn, fn;

	line = explode(read_file(file), "\n");
	data = ({});
	for(i=0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !pointerp(field) ) {
			field = explode( line[i], ":" );
			continue;
		}
		if( !pointerp(format) ) {
			format = explode( line[i], ":" );
			continue;
		}
		break;
	}

	for( rn = 0, fn = 0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !fn ) data += ({ allocate_mapping(sizeof(field)) });
		sscanf( line[i], format[fn], data[rn][field[fn]] );
		fn = (++fn) % sizeof(field);
		if( !fn ) ++rn;
	}
	return data;
}

mapping *query_day_phase() { return day_phase; }
 

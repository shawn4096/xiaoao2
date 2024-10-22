// time.c
// yuj@sj 加上世界范围的时间，和夏令时间，天才设计
// 增加vip显示 LinuX@SJ

#include <ansi.h>
#include <mudlib.h>


string Ctime(int t)
{
	string ts = ctime(t);

	ts = " "+ts[0..2]+ts[19..23]+"-"+ts[4..6]+"-"+ts[8..9]+ts[10..18];
	ts = replace_string(ts, "Sun", "星期日");
	ts = replace_string(ts, "Mon", "星期一");
	ts = replace_string(ts, "Tue", "星期二");
	ts = replace_string(ts, "Wed", "星期三");
	ts = replace_string(ts, "Thu", "星期四");
	ts = replace_string(ts, "Fri", "星期五");
	ts = replace_string(ts, "Sat", "星期六");
	ts = replace_string(ts, "Jan", "一月");
	ts = replace_string(ts, "Feb", "二月");
	ts = replace_string(ts, "Mar", "三月");
	ts = replace_string(ts, "Apr", "四月");
	ts = replace_string(ts, "May", "五月");
	ts = replace_string(ts, "Jun", "六月");
	ts = replace_string(ts, "Jul", "七月");
	ts = replace_string(ts, "Aug", "八月");
	ts = replace_string(ts, "Sep", "九月");
	ts = replace_string(ts, "Oct", "十月");
	ts = replace_string(ts, "Nov", "十一月");
	ts = replace_string(ts, "Dec", "十二月");
	return ts;
}

string SYDtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 9 || lt[4] < 2)
	  || (lt[4] == 9 && lt[3] - 24 > lt[6])	// Last Sunday
	  || (lt[4] == 2 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}

string NZtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 9 || lt[4] < 2)
	  || (lt[4] == 9 && lt[3] > lt[6])	// First Sunday
	  || (lt[4] == 2 && lt[3] - 5 < lt[6])	// First Sunday on or after 5
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}

string NAtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 3 && lt[4] < 9)
	  || (lt[4] == 3 && lt[3] > lt[6])	// First Sunday
	  || (lt[4] == 9 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}

string EUtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 2 && lt[4] < 9)
	  || (lt[4] == 2 && lt[3] - 24 > lt[6])	// Last Sunday
	  || (lt[4] == 9 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}
void do_vip(object me)
{
	int t,t1;
	int this_week = time()/86400/7;
	int end_time = 1106452800; //January 23, 2005, 12:00 pm
	string site;
	
	site = lower_case(INTERMUD_MUD_NAME);

	if((me->query("vip/vip_time") > 1104508800) && end_time - time() > 0 && !me->query("vip/redeem") && site=="ln") //1104508800 January 1, 2005, 12:00 am
	{
		t1 = me->query("vip/vip_time") - time();
		write(sprintf(HIY"您的上次贵宾%s，为了补偿辽宁站前段时间的当机损失，特增加你贵宾15天。\n"NOR,
		(t1>0)?("剩余时间："+CHINESE_D->chinese_time(t1)):"已经到期"));	
		
		if (t1>0)
			me->add("vip/vip_time",15*24*3600);
		else
			me->set("vip/vip_time",time()+15*24*3600);
		me->set("vip/redeem",1);//标记
		log_file("static/REDEEM",
				sprintf("%s 获得贵宾补偿。\n",me->query("id")));
	}
		
	t = me->query("vip/vip_time") - time();
	if ( t > 0 && t < 86400)
			write (HIY+"贵宾剩余时间：" +BLINK+HIR+CHINESE_D->chinese_time(t) + "，请及时续费。\n"+NOR);
	else if (t > 0)
			write (HIY"贵宾剩余时间：" +NOR+CHINESE_D->chinese_time(t) + "。\n");
	else if ((int)me->query("vip/vip_start_time") != 0)
			write(HIY"贵宾系统提示："NOR"您的贵宾有效期已经到期，请及时续费。\n");
	else {
			//me->delete("");
			write (HIY"贵宾系统提示："NOR"您目前不是贵宾，如何成为贵宾请看( help vip )。\n");
	}
	if ( t > 0 && (me->query("registered") < 3 )) {
		me->set("registered",3);
		write (HBRED+HIY"您的贵宾已经激活！\n"NOR);
	}

	if ( t < 0 && (me->query("registered") > 2 )) {
        me->set("registered",2);
		write( HBRED+HIY"您的贵宾已经到期，系统已经自动取消您的贵宾！\n"NOR);
		if (me->query("m-card-vip"))
		{
			me->delete("m-card-vip");
			write(HIC"注意，现在已经取消你的月卡贵宾身份。\n"NOR);
			
		}
		if (me->query("y-card-vip"))
		{
			me->delete("y-card-vip");
			write(HIC"注意，现在已经取消你的年卡贵宾身份。\n"NOR);
			
		}
		if (me->query("buyvip"))
		{
			me->set("vip/vip_start_time",time());    
			me->set("vip/vip_time",time());   
			me->add("vip/vip_time",3*365*24*3600);
			write(HIC"注意，现在你的终身贵宾身份将自动生效，不受影响。\n"NOR);
			
		}
               
    }
	if ((int)me->query("vip/vip_start_time") != 0)
		write (HIY"贵宾生效时间："+ NOR+CHINESE_D->chinese_date(me->query("vip/vip_start_time"),1) +"。\n");	
	else
		write (HIY"贵宾生效时间："NOR"您没有贵宾生效时间记录。\n");
		
	//For all Bug By Ciwei@SJ
	while(me->query("ggs/left_time")>10*3600)
		me->add("ggs/left_time",-10*3600);
	
        if (me->query("registered") >= 3 && me->query("ggs/started") && me->query("ggs/start_time")){
		t = time()-(int)me->query("ggs/start_time");
		//me->set("ggs/left_time",me->query("ggs/left_time") - t);
		
		if (t>10*3600) t=0;
		
		if (me->query("ggs/left_time") < 0 ) //防止bug
			me->set("ggs/left_time",0);
		
		write (HIY"鬼谷算术状态："NOR+"已经使用"+CHINESE_D->chinese_time(t) +",本周还可以使用"+CHINESE_D->chinese_time(me->query("ggs/left_time") -t) +"。\n");	
	}
        else if(me->query("registered") < 3)
		write (HIY"鬼谷算术状态："NOR+"你不是贵宾，不能使用鬼谷算术，如何成为贵宾请看( help vip )。\n");	
	else if(this_week > me->query("ggs/last_week")) 
		write (HIY"鬼谷算术状态："NOR+"当前你没有进行鬼谷算术，本周还可以使用十个小时。\n");		
	else
		write (HIY"鬼谷算术状态："NOR+"当前你没有进行鬼谷算术，本周还可以使用"+CHINESE_D->chinese_time(me->query("ggs/left_time")) + "。\n");	
	
}

int modify = 0;

int main(object me, string arg)
{
	int t;
	if (!wizardp(me) || !arg) {
		int GMT = time() + localtime(0)[8] + modify;

		write("现在是书剑"+ NATURE_D->game_time() + "。\n");
		write("您参与游戏的主机北京时间是" + Ctime(GMT+28800) + "\n");
		write("                悉尼时间是" + SYDtime(GMT+36000) + "\n");
		write("      奥克兰、惠灵顿时间是" + NZtime(GMT+43200) + "\n");
		write("      温哥华、洛杉矶时间是" + NAtime(GMT-28800) + "\n");
		write("        多伦多、纽约时间是" + NAtime(GMT-18000) + "\n");
		write("    柏林、罗马、巴黎时间是" + EUtime(GMT+3600) + "\n");
		
		t = me->query_temp("online_time");
		if (t > 0) write("您已经连续玩了"+CHINESE_D->chinese_time(t)+"。\n");
		t = me->query("online_total");
		if (t > 0) write("你最近玩了"+CHINESE_D->chinese_time(t)+"。\n");
	
		do_vip(me);
	} else if (arg != "-cond") {
		int i;

		if (sscanf(arg, "%d", i) == 1) {
			modify += i;
			//save();
			write(ctime(time() + localtime(0)[8] + 28800 + modify) + "\n");
			return 1;
		}
		me = LOGIN_D->find_body(arg);
		if (!me) return notify_fail("没有这个玩家。\n");
	}


	return 1;
}

int help(object me)
{
 	write(@HELP
指令格式: time

这个指令让你(你)知道现在的时辰和您的游戏贵宾情况和上次贵宾生效时间记录。

HELP
    );
    return 1;
}

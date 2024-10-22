// fingerd.c

// Modified by mxzhao 2004/02/18
// LinuX@SJ 2004/02/28
// 增加贵宾时间显示，精确到秒，贵宾为USER_OB保存，不在是LOGIN_OB

#include <ansi.h>
#include <net/dns.h>
#include <mudlib.h>

void create()
{
	seteuid( getuid() );
}

string age_string(int time)
{
	int month, day, hour, min, sec;

	sec = time % 60;
	time /= 60;
	min = time % 60;
	time /= 60;
	hour = time % 24;
	time /= 24;
	day = time % 30;
	month = time / 30;
	return (month?month + "m":"") + (day?day + "d":"") +
	(hour?hour + "h":"") + min + "m";
}

int sort(object ob1, object ob2)
{
	if (!interactive(ob1)) return -1;
	if (!interactive(ob2)) return 1;
	return strcmp(query_ip_number(ob1), query_ip_number(ob2));
}

string user_list(object *ob, int flag)
{
	object me;
	string msg;
	string ipname;
	
	int i;
	
	if (! ob || ! sizeof(ob))
		return "没有任何符合条件的玩家。\n";
	
	me = this_player();
	msg = "┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n" +
		WHT HBBLU "姓名          帐号          年龄          发呆                     连线                \n" NOR +
		"┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n";
	for(i = 0; i < sizeof(ob); i++)
	{
		if (me && ! me->visible(ob[i]))
		{
			continue;
		}
		if(!ob[i] || !ob[i]->query_temp("link_ob")) continue;
		// Modified by mxzhao 2004/05/18 -->>
		//ipname = wiz_level(me) > 4 ? (query_ip_number(ob[i]) + "("+IP_D->ip2name(query_ip_number(ob[i]))+")") : "--------";
		ipname = ((ob[i]->query_temp("link_ob"))->query_temp("last_from"));
		ipname = wiz_level(me)>4?ipname: "--------";
		// Modified by mxzhao 2004/05/18 <<--
		msg = sprintf("%s%s%-14s%s%-14s%-14s%s%-7s" NOR "%s\n",
			msg, (ob[i]->name() != ob[i]->name(flag) ? HIM : NOR),
			ob[i]->name(flag), NOR, ob[i]->query("id"),
			age_string( (int)ob[i]->query("mud_time")), 
			(interactive(ob[i]) ? ((query_idle(ob[i]) >= 120) ? HIG : NOR) : ob[i]->query("doing") == "closed" ? HIY : HIR),
			(interactive(ob[i]) ? (query_idle(ob[i]) + "s") : ob[i]->query("doing") == "closed" ? "闭关" : "断线"), ipname);
	}
	
	msg += "┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n";
	return msg;
}

string finger_all()
{
	object me = this_player();
	object *ob;
	string msg;
	string ipname;
	int i;

	ob = filter_array(objects(), (: userp :));
	ob = sort_array(ob, (: sort :));
	msg = "";
	if (!wizardp(me) || wiz_level(me) < 3)  // player finger wizard以下不能查看玩家IP
	{
		for(i=0; i<sizeof(ob); i++) {
			if (!me->visible(ob[i])) continue;
			msg += sprintf("%-14s%-14s%-14s\n",
				ob[i]->query("name"), ob[i]->query("id"),
				!interactive(ob[i])?"断线中":query_idle(ob[i]) + "s");
		}
		return "◎" + MUD_NAME + "◎\n" +
		"┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n"
		+ "姓名          帐号          发呆\n" +
		"┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n"
		+ msg +
		"┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n";
	}
	else          // wizard finger
	{
		for (i=0;i<sizeof(ob);i++)
			if (me->visible(ob[i])) break;
		
		if(ob[i]&&ob[i]->query_temp("link_ob"))
		{		
		ipname = ((ob[i]->query_temp("link_ob"))->query_temp("last_from"));
												
		msg += sprintf("%s%-13s%-14s%-14s%-7s%-=50s\n",
			environment(ob[i])?" ":"*",
			ob[i]->query("name"), ob[i]->query("id"),
			age_string(ob[i]->query("mud_time")),
			!interactive(ob[i])?"断线中":query_idle(ob[i]) + "s",
			// Modified by mxzhao 2004/05/18 -->>			
			ipname);
			// Modified by mxzhao 2004/05/18 <<--
			////query_ip_name(ob[i])+"("+IP_D->ip2name(query_ip_number(ob[i]))+")");
		}
		for(i=i+1; i<sizeof(ob); i++) 
		{
			if (!me->visible(ob[i]) ) continue;
			if(!ob[i] || !ob[i]->query_temp("link_ob")) continue;
			ipname = ((ob[i]->query_temp("link_ob"))->query_temp("last_from"));
			msg += sprintf("%s%-13s%-14s%-14s%-7s%-=50s\n",
				environment(ob[i])?" ":"*",
				ob[i]->query("name"), ob[i]->query("id"),
				age_string(ob[i]->query("mud_time")),
				!interactive(ob[i])?"断线中":query_idle(ob[i]) + "s",
				query_ip_number(ob[i]) && query_ip_number(ob[i]) == query_ip_number(ob[i-1])?
				// Modified by mxzhao 2004/05/18 -->>
				//"地址同上":query_ip_name(ob[i])+"("+IP_D->ip2name(query_ip_number(ob[i]))+")");
				"地址同上":ipname);
				// Modified by mxzhao 2004/05/18 -->>
		}
		return "◎ " + MUD_NAME + HIW"档案\n"NOR +
		"┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n"
		HIC" 姓名         帐号          年龄          发呆   连线\n"NOR +
		"┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n"
		+ msg +
		"┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n"
		"* 表示登录中\n";
	}
}

string reg(int i)
{
	if (i < 2)
		return "未注册";
	if (i == 2)
		return "免费用户";
	return "贵宾用户";
}

string finger_user(string name)
{
	object me = this_player(), ob, body;
	string msg;
	object user;
//	mixed *info;
	int public_flag;
	int last_on = strlen(name);
	int birthday;
	int days;
	
	object *uob;
	int same;
	if (INTERMUD_MUD_NAME != "SJ" && INTERMUD_MUD_NAME != "SJTX" )
	{
		while (last_on--) if (name[last_on] < 'a' || name[last_on] > 'z')
		return name+"是什么东东？\n";
	}
	if (name == "guest") 
	{
		return "访客有什么好看的？\n";
	}
	
	user = new(USER_OB);
	if (!user) 
	{
		write("现在可能有人正在修改使用者物件的程序。\n\n");
		return 0;
	}

	seteuid(name);
	export_uid(user);
	seteuid(getuid());
	
	if(!user->restore()) 
	{
		destruct(user);
		return "没有这个玩家耶。\n";
	}

	user->set_name(user->query("name"), ({ name}));

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if (!ob->restore()) 
	{
		destruct(ob);
		return "没有这个玩家。\n";
	}

	last_on = ob->query("last_on");
/*
	if (!ob->query("login_fail") && !objectp(body = LOGIN_D->find_body(name))) {
		info = get_dir(DATA_DIR + "login/" + name[0..0] + "/" + name + ".o", -1);
		if (info[0][2] > last_on) last_on = info[0][2];
	}
*/
	if (objectp(body = LOGIN_D->find_body(name))) 
	{
		public_flag = body->query("env/public")?1:0;
		birthday = body->query("birthday");
		if (me == body) public_flag = 1;
	} 
	else 
	{
		body = LOGIN_D->make_body(ob);
		if (!body->restore()) 
		{
			destruct(ob);
			destruct(body);
			destruct(user);
			return "没有这个玩家。\n";
		}

		public_flag = body->query("env/public")?1:0;
		birthday = body->query("birthday");
		destruct(body);
	}
	if (!wizardp(me) && !me->id(name)) 	// player finger
	{
		msg = HIC"\n╭─ 玩家档案 ──────────────────╮\n";
		msg +=  sprintf(
			"│"WHT"英文代号  ：%-36s"HIC"│\n"
			"│"WHT"原始姓名  ：%-28s"HIR"%s"HIC"│\n"
			"│"WHT"权限等级  ：%-28s"HIR"%s"HIC"│\n"
//			"│"WHT"E-mail地址：%-36s"HIC"│\n"
			"│"WHT"注册情况  ：%-28s"HIR"%s"HIC"│\n"
			"│"WHT"上次退出  ：%-28s"HIR"%s"HIC"│\n",
			name,
			ob->query("name"),
			"  ▁▁  ",
			wiz_level(name)==5?"管理员":"玩家",
			"▕笑書▏",
//			public_flag?ob->query("email"):"不告诉你",
			reg(user->query("registered")),
			"▕傲劒▏",
			last_on&&!wiz_level(name)?ctime(last_on):"神出鬼没",
			"  ▔▔  "

		);
		msg += "╰────────────────────────╯\n"NOR;

		if (objectp(body = LOGIN_D->find_body(name)) && geteuid(body)==name)
			if (me->visible(body))
				msg += sprintf(" %s目前正在连线中。\n %s", body->name(1), body->long(1));
	} 
	else 	// wizard finger
	{
		// Modified by mxzhao 2004/05/18 -->>
		//string tmp = ob->query("last_from") + "", tmp1;
		string tmp1;
		// Modified by mxzhao 2004/05/18 <<--

		msg = HIC"\n╭─ 玩家档案 ──────────────────╮\n";

// Modified by mxzhao 2004/02/18
		{
			mixed ret = dbquery("select U_Site, Alivedays from Users "
				"where U_Username="+save_variable(name));

			if (sizeof(ret) == 1)
			{
				tmp1 = ret[0][0];
				days = ret[0][1];
			}
			else
			{
				tmp1 = "已经自杀";
				days = 0;
			}
		}

/*		{
			mixed mysql = db_connect("localhost", "mud", "root"), rows, res = ({ "已经自杀", 0 });

			if (intp(mysql)) {
				rows = db_exec(mysql, "select U_Site,Alivedays from " + INTERMUD_MUD_NAME + "_Users where U_Username="+save_variable(name));
				if (rows==1)
					res = db_fetch(mysql, 1);
				db_close(mysql);
			}
			tmp1 = res[0];
			days = res[1];
		}
*/
// End

		msg +=  sprintf(
			"│"WHT"英文代号  ：%-36s"HIC"│\n"
			"│"WHT"原始姓名  ：%-28s"HIR"%s"HIC"│\n"
			"│"WHT"权限等级  ：%-28s"HIR"%s"HIC"│\n"
			"│"WHT"E-mail地址：%-28s"HIR"%s"HIC"│\n"
			"│"WHT"注册情况  ：%-28s"HIR"%s"HIC"│\n",
//			ob->query("id")+"@"+tmp1+" "+days,
			ob->query("id"),
			ob->query("name"),
			"  ▁▁  ",		
			SECURITY_D->get_status(name),
			"▕笑書▏",			
			ob->query("email"),
			"▕傲劒▏",
			reg(user->query("registered")),
			"  ▔▔  "
		);
		msg += "╰────────────────────────╯\n"NOR;
		if (wizardp(me))
			msg += CHINESE_D->chinese_date(birthday, 1)+"\n";
		
		// Modified by mxzhao 2004/05/18 -->>
		//sscanf(tmp, "%s(%s)", tmp, tmp1);
		//msg += sprintf("上次连线地址：%s(%s)\n上次登录时间：%s\n", tmp,
		//	IP_D->ip2name(tmp1) ,last_on?CHINESE_D->chinese_date(last_on, 1):"无");
		if (wiz_level(me) > 2){
		msg += sprintf("上次连线地址：%s\n上次登录时间：%s\n", 
			ob->query("last_from"), last_on?CHINESE_D->chinese_date(last_on, 1):"无");
		}
		else
		{
		msg += sprintf("上次登录时间：%s\n", 
			last_on?CHINESE_D->chinese_date(last_on, 1):"无");	
		}
		// Modified by mxzhao 2004/05/18 -->>
		if (user->query("registered") == 3)
			msg += sprintf("贵宾剩余时间：%s\n", CHINESE_D->chinese_time(user->query("vip/vip_time") - time()));
		if( objectp(body = LOGIN_D->find_body(name)) && geteuid(body)==name ) 
		{
			if (me->visible(body)) 
			{
				object link_ob = body->query_temp("link_ob");

				if (wiz_level(me) > 2 )
				{
					msg += sprintf("%s%s前在%s，目前在%s\n",
						body->query("name")+"("+name+")",
						CHINESE_D->chinese_time(time()-last_on),
				// Modified by mxzhao 2004/05/18 -->>
						ob->query("last_from"), 
						objectp(link_ob)?link_ob->query_temp("last_from"):"断线中");
						//IP_D->ip2name(tmp1),
						//IP_D->ip2name(query_ip_number(body)));
				
				//msg += sprintf("%s目前正%s中。\n%s",
				//	me->id(name)?"你":body->name(1), 
				//	objectp(link_ob)?"从 " + link_ob->query_temp("last_from") + ":" 
				//	+ query_ip_rport(body) + " 连线":"断线", body->long(1));
				}
				else
				{
					msg += sprintf("%s目前正%s中。\n%s",
					me->id(name)?"你":body->name(1), 
					objectp(link_ob)?"连线":"断线", body->long(1));
	
				
				}
				// Modified by mxzhao 2004/05/18 <<--
			}
		} 

		if (wiz_level(me) > 2)
		{
			uob = filter_array(users(),
				(: query_ip_number($1) == $(query_ip_number(body)) :));

			same = sizeof(uob);
			if (same > 1)
			{
				msg += sprintf("该地址一共有 "HIY"%d"NOR" 位使用者。\n", same);
				if (previous_object() != find_object(user->query("id")))
					// I won't return the list if this is
                  	// called from a chat user
					msg += user_list(uob, 1);
			} 
		}
	}

	destruct(ob);
	destruct(user);
	return msg;
}

varargs string remote_finger_user(string name, int chinese_flag)
{
	object ob, body;
	string msg;

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() )
		return chinese_flag ? "没有这个玩家。\n" : "No such user.\n";
	if( chinese_flag ){
		msg = HIC"\n╭─ 玩家档案 ──────────────────╮\n";
		msg +=  sprintf("│"WHT"英文代号  ：\t%-34s"HIC"│\n│"WHT"姓    名  ：\t%-34s"HIC"│\n│"
			WHT"权限等级  ：\t%-34s"HIC"│\n│"WHT"E-mail地址：\t%-34s"HIC"│\n│"
			WHT"注册情况：\t%-34s"HIC"│\n│"WHT"上次退出：\t%-34s"HIC"│\n",
				ob->query("id"),
				ob->query("name"),
				SECURITY_D->get_status(name),
				ob->query("email"),
				ob->query("registered")>1?"已注册":"还未注册",
				ob->query("last_from"));
		msg += "╰───────────────────── SJ ─╯\n"NOR;
		msg += CHINESE_D->chinese_date(ob->query("last_on"), 1);
	 }
	else	msg =  sprintf(
		"\nName\t: %s\nStatus\t: %s\nEmail\t: %s\nLastOn\t: %s( %s )\n\n",
		capitalize(ob->query("id")),
		SECURITY_D->get_status(name),
		ob->query("email"),
		ob->query("last_from"),
		CHINESE_D->chinese_date(ob->query("last_on"), 1)
	);
	if( body = find_player(name) ) {
		if( !this_player() || this_player()->visible(body) )
			msg += chinese_flag ?
				("\n" + ob->query("name") + "目前正在线上。\n"):
				("\n" + capitalize(name) + " is currently connected.\n");
	}

	destruct(ob);
	return msg;
}

object acquire_login_ob(string id)
{
	object ob;

	if( ob = find_player(id) ) {
		// Check if the player is linkdead
		if( ob->query_temp("link_ob") )
			return ob->query_temp("link_ob");
	}
	ob = new(LOGIN_OB);
	ob->set("id", id);
	if (!ob->restore()) destruct(ob);
	return ob;
}

string get_killer()
{
	string msg = "";
	object *ob = filter_array(children(USER_OB), (: userp :));

	foreach (object item in ob)
		if (item->query_condition("killer") > 0)
			msg += sprintf("%-60s 时限：%s个时辰\n",
				item->short(1), chinese_number((item->query_condition("killer")+5)/6));
	if (msg == "")
		return "		  本城治安良好。\n";
	return "\n现在本城正在缉拿以下人犯：\n\n" + msg;
}
//新增函数 get_last_on()用于获得玩家上一次自动离线时候的时间
string get_last_on(string name)
{
	object ob;
	string msg;
	ob = new(LOGIN_OB);
	ob->set("id",name);
	if(!ob->restore()) return 0;
	msg = ob->query("last_on");
	destruct(ob);
	return msg;
}

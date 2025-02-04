#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string display_attr(int gift, int value);

void create() { seteuid(getuid()); }

string *age_color = ({
	CYN, YEL, HIY, HIG, HIC, HIR
});

int main(object me, string arg)
{
	object ob;
	mapping my, job;
	string line ,temp ,skill_type, title;
        int user_weapon;
	object weapon;
	int attack_points, dodge_points, parry_points;
        int canwu_exp, total_gifts, remain_gifts;
	if (!arg) ob = me;
	else if( !(ob=present(arg, environment(me))) ) {
		if (wizardp(me)) {
			if (!ob) ob = LOGIN_D->find_body(arg);
			if (!ob) ob = find_living(arg);
			if (!ob || !me->visible(ob)) return notify_fail("你要察看谁的状态？\n");
		}
		else return notify_fail("你要察看谁的状态？\n");
	}

	if( ob!=me && !wizardp(me) ) {
		if( userp(ob)
		  || !me->query("group/id")
		  || me->query("group/id") != ob->query("group/id")
		  || me->query("group/class") >= ob->query("group/class") )
			return notify_fail("你只能查看同帮派，且等级比你低的NPC的状态。\n");
	}

	my = ob->query_entire_dbase();
// add for temp title display
	my["title"] ? title = my["title"]: title = "无";
	
// 显示武器未打造的机会次数
        if (my["combat_exp"] < 500000) user_weapon = 0;
        else if (my["combat_exp"]  < 1000000 && !my["user_weapon_imbued"]) user_weapon = 1;
        else if ((my["combat_exp"]/1000000 - (int)my["user_weapon_imbued"])<0) user_weapon = 0;
        else if ((my["combat_exp"]/1000000 - (int)my["user_weapon_imbued"])==0) user_weapon = 1;
        else user_weapon = (my["combat_exp"]/1000000 - (int)my["user_weapon_imbued"])+1;
        user_weapon += my["imbue_reward"];
        //imbue_reward
                
	if (stringp(ob->query_temp("title")))
		title = ob->query_temp("title");

	line = "\n╭━━"HIW"【书剑个人资料卡】"NOR
		+(ob->query_temp("big5")?"繁":"简")+"体中文━━┳━━━━━━━━━━━━━━━━━━━╮\n";

	line += sprintf("┃称    谓：%-24s┃体  重：「%-28s┃\n",
		RANK_D->query_rank(ob),
		chinese_number(ob->query_weight()/500)+"斤」"
	);

	line += sprintf("┃头    衔：%-24s┃%-19s%-19s┃\n", title,
		"膂  力：「"+display_attr(my["str"], ob->query_str())+"」",
		"根  骨：「"+display_attr(my["con"], ob->query_con())+"」"
	);

	line += sprintf("┃姓    名：%-24s┃%-19s%-19s┃\n",
		(my["color"]?my["color"]:"")+my["name"]+NOR"("+capitalize(my["id"])+")",
		"身  法：「"+display_attr(my["dex"], ob->query_dex())+"」",
		"悟  性：「"+display_attr(my["int"], ob->query_int())+"」"
	);

	line += sprintf("┃外    号：%-24s┗━━━━━━━━━━━━━━━━━━━┫\n",
		my["nickname"]?my["nickname"]+NOR:"无"
	);

	line += sprintf("┃年    龄：%-26s生    辰：%-28s┃\n",
		age_color[my["day"]/5]+chinese_number(my["age"])+"岁"+(my["month"]?"又"+chinese_number(my["month"])+"个月":"")+NOR,
		CHINESE_D->chinese_date((my["birthday"] - 14*365*24*60) * 60)
	);

	if (objectp(weapon = ob->query_temp("weapon")) ) skill_type = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();

		if (!sizeof(prepare)) skill_type = "unarmed";
		else skill_type = keys(prepare)[0];
	}
	attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
	line += sprintf("┃性    别：%-26s攻：%-9s躲：%-9s架：%8s┃\n",
		my["gender"]+(ob->is_robot()?HIG"→机器人"NOR:""),
		"/cmds/std/look"->tough_level(attack_points, 0, 1),
		"/cmds/std/look"->tough_level(dodge_points, 0, 1),
		"/cmds/std/look"->tough_level(parry_points, 0, 1)
	);

	temp = ob->query("family/family_name")?"【"+my["family"]["family_name"]+"】":"【普通百姓】";
	temp += ob->query("family/master_name")?"【"+my["family"]["master_name"]+"】":"";
	line += sprintf("┃钱庄存款：%-26s师    承：%-28s┃\n",
		my["balance"]/10000?HIY BRED+chinese_number(my["balance"]/10000)+"锭黄金"NOR:"很少",
		HIW+temp+NOR
	);
		
	line += sprintf("┃书剑通宝：%-64s┃\n",
		my["SJ_Credit"]?HIG BGRN+chinese_number(my["SJ_Credit"])+"个"NOR:"无""",
	);


       canwu_exp    = ob->query("relife/exp_ext",1);
       total_gifts  = ob->query("relife/gifts/total",1);
       remain_gifts = ob->query("relife/gifts/now",1);

       line += sprintf("┃经验额外获取：%-18s参悟天赋：%-12s未分配天赋：%-8s┃\n",
	( ob->query("relife/exp_ext"))?HBMAG"〖百分之"+chinese_number(canwu_exp *5 )+"〗"NOR:"无""",
	( ob->query("relife/gifts/total"))?HBRED+chinese_number(total_gifts )+"点"NOR:"无""",
        ( ob->query("relife/gifts/now")  )?HBRED+chinese_number(remain_gifts)+"点"NOR:"无"""

	);



	line += "┠─────────────────────────────────────┨\n";

	if (my["divorce"]) temp = "婚姻：离异"+chinese_number(my["divorce"])+"次";
	else temp = "婚姻：未婚";
	if (mapp(my["marry"])) {
		if (ob->query("marry/name"))
			temp = (my["gender"]=="女性"?"夫君："HIR:"娇妻："HIG)
				+my["marry"]["name"]+"("+capitalize(my["marry"]["id"])+")" NOR;
	};
	line += sprintf("┃%-28s%-6s%-18d"NOR"综合评价：%-12d┃\n",
		temp,
		my["shen"] < 0?"戾气："HIR:"正气："HIC,
		(my["shen"] < 0?-1:1)*my["shen"],
		my["score"]
	);
                        if(ob->query("registered")<3) temp =HBCYN+HIY"免费玩家"NOR;
                              if(ob->query("registered")==3) temp =HBCYN+HIY"月卡贵宾"NOR;
                        if(ob->query("y-card-vip")) temp =HBMAG+HIY"年卡贵宾"NOR;
                        if(ob->query("buyvip")) temp =HBRED+HIW "荣誉终身贵宾"NOR;
	if (base_name(ob) == "/clone/user/user") {
                line += sprintf("┃注册：%-12s%-10s叛师：%-18s犯    规：%-12s┃\n",
                        temp,

                        my["no_pk"]?HIY BRED"→已洗手"NOR:""NOR,
                        my["betrayer"]?HIY+chinese_number(my["betrayer"])+"次"NOR:"无",
                        my["rules"]?HIR+chinese_number(my["rules"])+"次"NOR:"无",
                );

		line += sprintf("┃杀人：%-22s玩家：%-18s正当防卫：%-12s┃\n",
			my["MKS"]+my["PKS"]+my["FKS"]?HIY BBLU+chinese_number(my["MKS"] + my["PKS"] + my["FKS"])+"位"NOR:"无",
			my["PKS"]+my["FKS"]?HIY BBLU+chinese_number(my["PKS"] + my["FKS"])+"位"NOR:"无",
			my["FKS"]?HIY BRED+chinese_number(my["FKS"])+"位"NOR:"无"
		);

		//因为空着，所以加上打造兵器.:)
                line += sprintf("┃死亡：%-22s有效：%-18s打造机会：%-12s┃\n",
                        my["death_count"]?HIM+chinese_number(my["death_count"])+"次"NOR:"无",
                        my["death_times"]?HIM+chinese_number(my["death_times"])+"次"NOR:"无",
                        user_weapon?HIM+chinese_number(user_weapon)+"次"NOR:"无",
                        //HIM + user_weapon + NOR
                );
		line += sprintf("┃上次遇害：%-64s┃\n",
			(ob->query("last_death")?ob->query("last_death"):"还未遇害")
			+(ob->query("last_killer")?"「"+ob->query("last_killer")+"」":"")
		);
	}

	line += "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n";

        if (wiz_level(me)>3) {
		line += sprintf(" 容貌[%s] 福缘[%s] 纯朴[%s]",
			display_attr(my["per"], ob->query_per()),
			display_attr(my["kar"], ob->query_kar()),
			display_attr(my["pur"], my["pur"]));
		line += sprintf(" 攻击%d(+%d) 躲闪%d 防御%d(+%d)\n",
			attack_points/100, ob->query_temp("apply/damage"),
			dodge_points/100,
			parry_points/100, ob->query_temp("apply/armor"));
		if( base_name(ob) == "/clone/user/user" ){
			job = my["job_time"];
			if ( ! job) job = my;
			temp  = " 官府("+(job["官府"]?job["官府"]:"无")+")";
			temp += " 大理("+(job["大理"]?job["大理"]:"无")+")";
			temp += " 丐帮("+(job["丐帮"]?job["丐帮"]:"无")+")";
			temp += " 华山("+(job["华山"]?job["华山"]:"无")+")";
			temp += " 武当("+(job["武当"]?job["武当"]:"无")+")";
			temp += " 天地会("+(job["天地会"]?job["天地会"]:"无")+")\n";
			temp += " 报效国家("+(job["报效国家"]?job["报效国家"]:"无")+")";
			temp += " 星宿("+(job["星宿"]?job["星宿"]:"无")+")";
			temp += " 星宿叛徒("+(job["星宿叛徒"]?job["星宿叛徒"]:"无")+")";
			temp += " 星宿熬膏("+(job["星宿熬膏"]?job["星宿熬膏"]:"无")+")";
			temp += " 嵩山("+(job["嵩山"]?job["嵩山"]:"无")+")";
			temp += " 雪山("+(job["雪山"]?job["雪山"]:"无")+")";
			temp += " 少林("+(job["少林"]?job["少林"]:"无")+")\n";
			temp += " 明教("+(job["明教"]?job["明教"]:"无")+")";
			temp += " 慕容("+(job["慕容"]?job["慕容"]:"无")+")";
			temp += " 桃花岛("+(job["桃花岛"]?job["桃花岛"]:"无")+")";
			temp += " 抓蛇("+(job["抓蛇"]?job["抓蛇"]:"无")+")";
			temp += " 赵敏("+(job["赵敏"]?job["赵敏"]:"无")+")";
			line += sprintf(" 任务(数量)："+temp+"\n");
			if (my["mud_time"] >= 600) {
				line += sprintf(" 经验：%d 每十分钟：%.1f 在线时间：%s\n",
					my["combat_exp"], my["combat_exp"]/(my["mud_time"]/600.0),
					CHINESE_D->chinese_time(my["mud_time"]/600*600)
				);
			}
		}
	}
	if (my["mud_time"] >= 86400)
		line += sprintf(" 平均每天在线：%s\n",
			CHINESE_D->chinese_time(to_int(my["mud_time"]*400.0/(time()-my["birthday"])*216)>86400?86400:to_int(my["mud_time"]*400.0/(time()-my["birthday"])*216) )
		);
	write(line);
	return 1;
}

string display_attr(int gift, int value)
{
	string str;
	if (value > gift) str = HIY;
	else if (value < gift) str = CYN;
	return str + value + NOR + "/" + gift;
;
}
int help(object me)
{
write(@HELP
指令格式 : score
	   score <对象名称>            (巫师专用)

这个指令可以显示你或指定对象(含NPC)的基本资料。

see also : hp
HELP
);
	return 1;
}

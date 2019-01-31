// test.c
// 修改1:15为1:10 游戏计时和现实基本同步  by renlai
inherit F_CLEAN_UP;
#include <ansi.h>

#define		CON_DIR		"/kungfu/condition/"

string get_con_name(string coni)
{
	string name;
	
	switch (coni)
	{
		// 毒类
		case "cx_poison"    : name="摧心掌毒";break;
		case "7bug_poison"	: name = "七虫软筋散"; break;		
		case "bee_poison"	: name = "玉蜂毒"; break;
		case "bing_poison"	: name = "冰魄银针毒"; break;
		case "bt_poison"	: name = "怪蛇毒"; break;		
		case "cold_poison"	: name = "寒毒"; break;
		case "fs_poison"	: name = "腐尸毒"; break;
		case "hama_poison"	: name = "蟾蜍毒"; break;	

		case "hb_poison"	: name = "寒冰绵掌毒"; break;		
		case "huagu_poison"	: name = "化骨绵掌毒"; break;

		case "hot_poison"	: name = "火毒"; break;	
		case "lvbo_poison"	: name = "绿波香露奇毒"; break;						
		case "man_poison"	: name = "蔓陀萝花毒"; break;
		case "qianli_poison"	: name = "千里销魂散"; break;
		case "qtlh_poi"		: name = "青陀罗花毒"; break;
		case "qzhu_poison"	: name = "千蛛万毒手毒"; break;
		case "sanxiao"		: name = "三笑逍遥散毒"; break;
		case "sl_poison"	: name = "神龙毒"; break;
		case "snake_poison"	: name = "蛇毒"; break;	
		case "sxs_poison"	: name = "三笑散之毒"; break;	
		case "sy_poison"	: name = "大手印掌毒"; break;	
		case "tz_poison"	: name = "铁掌毒"; break;		
		case "xx_poison"	: name = "星宿掌毒"; break;
			
		case "xuanmin_poison"	: name = "玄冥神掌寒毒"; break;
		case "xiezi_poison"	: name = "蝎子毒"; break;
		case "warm_poison"	: name = "热毒"; break;
		case "wh_poison"	: name = "神龙五行毒"; break;	
		case "wugong_poison"	: name = "蜈蚣毒"; break;	
		case "wh_poison"	: name = "神龙五行毒"; break;	
		case "zhizhu_poison"	: name = "蜘蛛毒"; break;	
		case "flower_poison"	: name = "断肠花毒"; break;	

		// 伤类
		case "broken_arm"	: name = "断手"; break;
		case "dgb_ban_wound"	: name = "打狗棒脚伤"; break;
		case "fugu_poison"	: name = "化血腐骨粉"; break;
		case "dsy_poison"	: name = "大手印内伤"; break;		
		case "huagong"		: name = "化功大法内伤"; break;		
		case "hunyuan_hurt"	: name = "混元掌内伤"; break;
		case "hyd_condition"    : name = "火焰刀烧伤"; break;
		case "juehu_hurt"	: name = "虎爪绝户手伤"; break;
		case "neishang"		: name = "内伤"; break;
		case "nxsz_hurt"	: name = "凝血神爪内伤"; break;
		case "qiankun_wound"	: name = "弹指神通内伤"; break;
		case "qishang_poison"	: name = "七伤拳内伤"; break;
		case "ruanjin_poison"	: name = "软筋散毒"; break;
		case "yyz_hurt"		: name = "一阳指内伤"; break;
		case "yzc_qiankun"	: name = "一指禅内劲"; break;		
		case "xuegu_bieqi"	: name = "雪谷窒息"; break;		
		case "sys_anjin"	: name = "三阴手暗劲"; break;
        case "shengsi_poison"	: name = "生死符"; break;			

		// 忙类
		case "no_exert"		: name = "闭气"; break;
		case "no_perform"	: name = "封招"; break;
		case "no_force"		: name = "气息不匀";break;
	//	case "no_fight"		: name = "不能战斗";break;

		//生病类
		case "ill_fashao"	: name = "发烧"; break;
		case "ill_kesou"	: name = "咳嗽"; break;
		case "ill_shanghan"	: name = "伤寒"; break;
		case "ill_zhongshu"	: name = "中暑"; break;
		case "ill_dongshang"	: name = "冻伤"; break;	
       
        case "dhd_cd"	: name = "大还丹药性"; break;	   
//		// 药类
//		case "bonze_drug"	: name = "少林丹药"; break;
//		
//		// 其它
//		case "bonze_jail"	: name = "少林监狱"; break;
		case "job_busy"		: name = "任务繁忙状态"; break;
		case "was_busy"		: name = "万安寺任务繁忙状态"; break;
		case "gmd_busy"		: name = "光明顶任务繁忙状态"; break;
		case "gb_job_busy"		: name = "颂摩崖任务倒计时"; break;
		case "riyue_job"            : name = "日月复兴"; break;
		case "qzlz_job_busy"		: name = "全真抗金倒计时"; break;
		case "qzcy_job_busy"		: name = "全真采药任务忙碌"; break;
		case "qzsw_job_busy"		: name = "全真守卫任务忙碌"; break;
		case "mgrq_job_busy"		: name = "抗敌蒙古入侵倒计时"; break;
		case "mgrq_job"		: name = "抗敌蒙古入侵任务"; break;
		case "qzjob_jianxi"		: name = "执行全真锄奸任务"; break;
		case "qzjx_job_busy"		: name = "全真锄奸任务忙碌"; break;

		case "xykm_job_busy"		: name = "襄阳抗蒙倒计时"; break;
        case "hb_job_busy"           : name = "福州镖局护镖倒计时"; break;
        case "lfta_job"               : name = "妖气袭体"; break;
        case "zwf_job_busy"               : name = "夜探赵王府"; break;
        case "db_exp"               : name = "双倍经验"; break;
        case "xs_job"               : name = "雪山强抢美女"; break;
		case "wd_job"               : name = "武当锄奸"; break;
		case "wdks_job"               : name = "武当看守铜鼎"; break;
		case "xx_job"               : name = "星宿追杀叛徒"; break;		
		case "xddl_job"               : name = "血刀打猎"; break;
		case "xdjj_job"               : name = "血刀警戒"; break;
		case "xdzj_job"               : name = "血刀阻击"; break;
		case "xgjz_job"               : name = "血刀雪谷激战"; break;
//昆仑job
		case "klmy_job"               : name = "昆仑买药"; break;
		case "klzs_job"               : name = "昆仑追杀"; break;
		case "sldjob_xunshe"               : name = "神龙岛训蛇"; break;
		case "sldjob_zhongyao"             : name = "神龙岛种药"; break;
		case "sljob_qingwu"               : name = "少林打杂"; break;
		case "sl_yingke"             : name = "少林迎客"; break;
		case "sspixie_job"             : name = "嵩山辟邪剑谱"; break;

		case "fuben"               : name = "副本"; break;
		case "baozang_time"               : name = "宝藏寻宝"; break;
                default                 : name = "不详"; break;
	}
	
	return name;
}

int main(object me,string arg)
{
	object tar, conob;
	int i, p, h, b, m, d;
	string msg, coni, conn, contp,cont;
	mapping cons;
	
	
	
        if (!userp(me)) return 0;
        	seteuid(getuid(me));

        if (!arg) tar = me;
        else if (!objectp(tar = present(arg, environment(me)))) {
                if (wizardp(me) ) {
                        if (!tar) tar = LOGIN_D->find_body(arg);
                        if (!tar) tar = find_living(arg);
                        if (!tar) return notify_fail("你要察看谁的特殊状态？\n");
                        if (wiz_level(me) < wiz_level(tar))
                                return notify_fail("你要察看谁的特殊状态？\n");
                }
        }

        if (!wizardp(me) && me!=tar)
                return notify_fail("你要察看谁的特殊状态？\n");

        if (tar->is_corpse() || !tar->is_character())
                return notify_fail("那不是活物耶！\n");
		
//		if ( sizeof(tar->query_entire_conditions()) < 1 )
//		{
//			tell_object(me, (tar!=me?tar->name(1):"你")+"身上没有包括任何特殊状态。\n");
//			return 1;
//		}

		msg = (tar!=me?tar->name(1):"你")+"身上包含下列特殊状态：\n";
		msg += "┌────────────────────────┐
│状态名称约剩余时间      类别│
├────────────────────────┤\n";

		cons = tar->query_entire_conditions();
		
		p = 0;
		h = 0;
		b = 0;
		m = 0;
		d = 0;

		for ( i=0; i<sizeof(cons); i++ )
		{
			coni = keys(cons)[i];
			conn = get_con_name(coni);
                        if (conn == "不详")
				continue;
			if (values(cons)[i] <= 0){
				tar->clear_condition(coni);
				continue;
			}
                        if (values(cons)[i] < 9)
                                //cont = chinese_number(values(cons)[i]*15)+"秒";
							    cont = chinese_number(values(cons)[i]*10)+"秒";
							
			else
                                cont = chinese_number(values(cons)[i]*2/9)+"分";
			
			

			if ( !(conob = find_object(CON_DIR+coni+".c")) )
				conob = load_object(CON_DIR+coni+".c");
			
			if ( !conob )
			{
				//msg += sprintf("│%-48s│\n", "状态文件无法加载："+CON_DIR+coni+".c");
				continue;
			}

			switch (conob->query_type(me))
			{
				case "poison" : contp = HIB"毒"NOR; p++; break;
				case "hurt"   : contp = HIR"伤"NOR; h++; break;
				case "wound"  : contp = HIR"伤"NOR; h++; break;
				case "busy"   : contp = HIY"忙"NOR; b++; break;
				case "job"    : contp = HIY"忙"NOR; b++; break;
				case "drug"   : contp = HIG"药"NOR; d++; break;
				case "illness"   : contp = HIG"病"NOR; h++; break;
				default       : contp = WHT"时长"NOR; m++; break;
			}
			

			msg += sprintf("│%-16s%-24s%|4s│%s\n", conn, cont, contp, wizardp(me)?(coni+".c"):"");
		}

		msg += "└────────────────────────┘\n";
		if (wizardp(me)) msg += sprintf("%51s\n", sprintf("毒：%d伤：%d忙：%d药：%d其他：%d共：%d",
						 p, h, b, d, m, (p+b+h+d+m)));
		if ( (p+b+h+d+m) < 1 )
			tell_object(me, (tar!=me?tar->name(1):"你")+"身上没有包括任何特殊状态。\n");
		else
			tell_object(me, msg);
		if (tar->is_robot())
			tell_object(me, HIY+(tar!=me?tar->name(1):"你")+"被判断为机器人，赶快用robot命令召唤一个出来吧。\n"+NOR);
		else
			tell_object(me,"当前"+ (tar!=me?tar->name(1):"你")+"没有被判断为机器人。\n");
	
	
	return 1;

}

int help(object me)
{
        write(@HELP
指令格式： cond
           cond <对象名称>             (巫师专用)

这个指令可以显示你的中毒情况和受伤情况。

HELP
        );
        return 1;
}

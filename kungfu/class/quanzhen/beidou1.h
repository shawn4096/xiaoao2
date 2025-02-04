// Code of JHSH
// /d/zhongnan/beidou.h
// 天罡北斗阵
// sdong 08/15/98

#include <ansi.h>

//inherit F_DBASE;
inherit F_SSERVER;
string *position = ({
	HIC"天权"NOR,HIG"天枢"NOR,HIY"天璇"NOR,HIM"天玑"NOR,HIW"玉衡"NOR,HIB"开阳"NOR,HIR"摇光"NOR
});

string *sword = ({
	"剑尖颤了几颤，一招巧妙无比的「分花拂柳」，似左实右往空中刺去。",
	"使一招「琴心三叠」，身形向上飘起，手中剑虚虚实实幻出三点寒光射向空中。",
	"身形一转，猛然一式「罡风扫叶」，舞出满天剑影，挟着劲风向前扫去。",
	"仰天长笑，身形飘然而起，在半空中身子一旋，一式「狂歌痛饮」狂风般地击向空中。",
	"左手捏着剑诀，右足踏开一招“定阳针”向上斜刺。",
	"向前迈去一大步，使出「探海屠龙」，手中剑舞成一个光球，迅若奔雷击出。",
	"运力一抖剑，一时「马蹴落花」，剑幻出点点剑花，飘然刺出。",
	"手中剑一指，纵起丈余，一时「横行漠北」，雷霆般击出。",
	"身形向上飘起，突然一转身，头下脚上，手握剑，一招「絮坠无声」，无声无息地攻出。",
	"大喝一声，一招「白虹经天」，剑闪电般划出一道大圆弧劈下。",
	"忽然身形高高跃起，使出「浪迹天涯」，手中剑幻出漫天花瓣，迅如雷霆射出。"
});

string *zhen =  ({
	"天罡北斗阵法滚滚推动，攻势连绵不绝，瞬间将敌人围在垓心。",
	"天罡北斗阵气势宏大，前攻后击，连环相接，让人眼花撩乱，方寸顿失。",
	"只见天罡北斗阵暗合五行八卦之理，阵中人步法精妙，攻守配合得天衣无缝，威力之大，让人叹为观止。",
	"天罡北斗阵越缩越小，无形剑气象浪潮一般逼向中央，令人有窒息之感。"
});

int beidouzhen(object me);
int halt_beidouzhen(object me);
int do_beidouzhen(object ob);
//int beidouzhen(object me);
int halt_beidou(object me);
int stop_beidou();
int beidou_kill(object ob);
void init()
{
		  add_action("stop_beidou", "stop");
		  add_action("do_beidouzhen", "lianzhen");
		   add_action("beidou_kill", "beidou");
		//  add_action("do_beidouzhen2", "start2");
		   //add_action("do_beidou", "beidou"); //驱动北斗杀人
}
//检查此人的能力
int check_ob(object ob,object me)
{
	string ob_name;
	object weapon;
	if( !objectp(ob) )
	{
		return notify_fail("检查此人能力时候，可惜没有找到这个人。\n");
	}
	ob_name = ob->query("name");

	if ( !present( ob->query("id"), environment(me) ) )
	{
		return notify_fail("可惜"+ob_name+"不在这里。\n");
	}

	if ( ob->query("family/family_name") != "全真教" )
	{
		return notify_fail("可惜"+ob_name+"不是全真弟子，不会「天罡北斗阵」。\n");
	}
	if ( ob->query_skill("tiangang-beidouzhen",1) <350)
	{
		return notify_fail("可惜"+ob_name+"天罡北斗阵法不足350级，不会「天罡北斗阵」。\n");
	}
	if ( ob->query_skill("xiantian-gong",1) <350)
	{
		return notify_fail("可惜"+ob_name+"先天功不足350级，不会「天罡北斗阵」。\n");
	}

	if ( ob->query_skill("quanzhen-jianfa",1) <350 ||
	     ob->query("combat_exp",1)<4500000 ||
	     ob->query_skill("dodge",1) <350)
	{
		return notify_fail("可惜"+ob_name+"武功太差，达不到350级，无法演练「天罡北斗阵」。\n");
	}
	return 1;
}
//设置北斗大阵
void start_beidouzhen(object ob, int mypos,int beidou_time )
{
	//ob是对象，mypos是位置次序，beidou_time是攻击奖励值
	ob->set_temp("pending/beidou", 1);
	ob->set_temp("beidou_time", beidou_time*2);
	ob->set_temp("bd_pos", mypos);
	ob->set_temp("bd_power",beidou_time);
	ob->start_busy((: beidouzhen :), (:halt_beidou:));
}

//启动1
int do_beidouzhen(string arg)
{
	object ob,me = this_player(),weapon;
	int beidou_time,i,mypos=0,power;
	object where;
	string ob_name;
	string name1,name2,name3,name4,name5,name6;
	object ob1,ob2,ob3,ob4,ob5,ob6;

	seteuid(getuid());
	where = environment(me);
/*
	if (!me->query_temp("lianzhen/start"))
	{
		return notify_fail("你尚未启动大阵\n");
	}
	*/
	me->delete_temp("qz/yanlian/zhifu");
	me->delete_temp("lianzhen/start");
	if (me->is_busy() || me->query_temp("pending/beidouzhen"))
		return notify_fail("你现在正忙着呢。\n");

	if( !arg || sscanf(arg, "%s %s %s %s %s %s", name1,name2,name3,name4,name5,name6)!=6 )
		return notify_fail("「天罡北斗阵」要有七人组成。你要和谁摆「天罡北斗阵」？\n");

	if( (int)me->query_temp("pending/beidou") )
		return notify_fail("你正在摆「天罡北斗阵」。\n");

	ob_name = me->query("name");
	
	if ( me->query("family/family_name") != "全真教" )
	{
		return notify_fail("可惜你不是全真弟子，不会「天罡北斗阵」。\n");
	}

	if ( me->query_skill("quanzhen-jianfa",1) <450 ||
	     me->query("combat_exp",1)<4500000 ||
	     me->query_skill("dodge",1) <450)
		return notify_fail("可惜你武功太差，不会「天罡北斗阵」。\n");
	//检查第一个人
	if( !(ob1 = present(name1, environment(me)) ) )
		ob1 = find_player(name1);

	i = check_ob(ob1,me);
	if(  i !=1) return i;
	//检查第二个人
	if( !(ob2 = present(name2, environment(me)) ) )
		ob2 = find_player(name2);
	i = check_ob(ob2,me);
	if(  i !=1) return i;
//检查第三个人
	if( !(ob3 = present(name3, environment(me)) ) )
		ob3 = find_player(name3);
	i = check_ob(ob3,me);
	if(  i !=1) return i;
//检查第四个人
	if( !(ob4 = present(name4, environment(me)) ) )
		ob4 = find_player(name4);
	i = check_ob(ob4,me);
	if(  i !=1) return i;
//检查第五个人
	if( !(ob5 = present(name5, environment(me)) ) )
		ob5 = find_player(name5);
	i = check_ob(ob5,me);
	if(  i !=1) return i;
//检查第六个人
	if( !(ob6 = present(name6, environment(me)) ) )
		ob6 = find_player(name6);
	i = check_ob(ob6,me);
	
	if(  i !=1) return i;
//判断攻击力

	power = me->query_skill("force") + 
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query("str")+
               ob1->query("str")+
               ob2->query("str")+
               ob3->query("str")+
               ob4->query("str")+
               ob5->query("str")+
               ob6->query("str");
	power += me->query("dex")+
               ob1->query("dex")+
               ob2->query("dex")+
               ob3->query("dex")+
               ob4->query("dex")+
               ob5->query("dex")+
               ob6->query("dex");
	power = power / 140;


	if (power>50) power=50;
	if (power<18) power=18;
/*
	power = me->query_skill("xiantian-gong") + 
               ob1->query_skill("xiantian-gong")+
               ob2->query_skill("xiantian-gong")+
               ob3->query_skill("xiantian-gong")+
               ob4->query_skill("xiantian-gong")+
               ob5->query_skill("xiantian-gong")+
               ob6->query_skill("xiantian-gong");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query_skill("tiangang-beidouzhen")+ 
               ob1->query_skill("tiangang-beidouzhen")+
               ob2->query_skill("tiangang-beidouzhen")+
               ob3->query_skill("tiangang-beidouzhen")+
               ob4->query_skill("tiangang-beidouzhen")+
               ob5->query_skill("tiangang-beidouzhen")+
               ob6->query_skill("tiangang-beidouzhen");
	power = power / 30;*/

//建立串联体系表
	set_temp("ob1",me->query("id"));
	set_temp("ob2",ob1->query("id"));
	set_temp("ob3",ob2->query("id"));
	set_temp("ob4",ob3->query("id"));
	set_temp("ob5",ob4->query("id"));
	set_temp("ob6",ob5->query("id"));
	set_temp("ob7",ob6->query("id"));
	
	message_vision(HIM"$N突然身形移动，发动众全真弟子抢占位置，左边四人，右边三人，" 
		+ "摆的正是「天罡北斗阵」的阵法。\n"NOR, me);
//每一个id都启动天罡北斗阵法,设置标记
	start_beidouzhen(me,0,power);
	start_beidouzhen(ob1,1,power);
	start_beidouzhen(ob2,2,power);
	start_beidouzhen(ob3,3,power);
	start_beidouzhen(ob4,4,power);
	start_beidouzhen(ob5,5,power);
	start_beidouzhen(ob6,6,power);
	//me->set_temp("beidou/tianquan",);
	
	return 1;
}
//第二种模式 以,分割模式，组成七个人模式

int do_beidouzhen2(string arg)
{
	object ob,me,weapon;
	int beidou_time,i,mypos=0,power,bd_power;
	object here;
	string ob_name;
	string name0,name1,name2,name3,name4,name5,name6;
	object ob1,ob2,ob3,ob4,ob5,ob6;

	here = environment( this_player() );

	if( !arg || sscanf(arg, "%s,%s,%s,%s,%s,%s,%s", name0,name1,name2,name3,name4,name5,name6)!=7 )
		return notify_fail("「天罡北斗阵」需要有七人组成。你要和谁摆「天罡北斗阵」？\n");

	if( !(me = present(name0, here) ) )
	{
		message_vision( name0+"怎么不在？\n");
		return 0;
	}

	if( !(ob1 = present(name1, environment(me)) ) )
		ob1 = find_player(name1);
	i = check_ob(ob1,me);
	if(  i !=1) return i;

	if( !(ob2 = present(name2, environment(me)) ) )
		ob2 = find_player(name2);
	i = check_ob(ob2,me);
	if(  i !=1) return i;

	if( !(ob3 = present(name3, environment(me)) ) )
		ob3 = find_player(name3);
	i = check_ob(ob3,me);
	if(  i !=1) return i;

	if( !(ob4 = present(name4, environment(me)) ) )
		ob4 = find_player(name4);
	i = check_ob(ob4,me);
	if(  i !=1) return i;

	if( !(ob5 = present(name5, environment(me)) ) )
		ob5 = find_player(name5);
	i = check_ob(ob5,me);
	if(  i !=1) return i;

	if( !(ob6 = present(name6, environment(me)) ) )
		ob6 = find_player(name6);
	i = check_ob(ob6,me);
	if(  i !=1) return i;

	power = me->query_skill("force") + 
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query("str")+
               ob1->query("str")+
               ob2->query("str")+
               ob3->query("str")+
               ob4->query("str")+
               ob5->query("str")+
               ob6->query("str");
	power += me->query("dex")+
               ob1->query("dex")+
               ob2->query("dex")+
               ob3->query("dex")+
               ob4->query("dex")+
               ob5->query("dex")+
               ob6->query("dex");
	power = power / 140;

	if (power>50) power=50;
	if (power<18) power=18;

	here->set_temp("ob1",me->query("id"));
	here->set_temp("ob2",ob1->query("id"));
	here->set_temp("ob3",ob2->query("id"));
	here->set_temp("ob4",ob3->query("id"));
	here->set_temp("ob5",ob4->query("id"));
	here->set_temp("ob6",ob5->query("id"));
	here->set_temp("ob7",ob6->query("id"));
	
	message_vision(HIM"$N突然身形移动，发动众全真弟子抢占位置，左边四人，右边三人，" + "
                      正是摆的「天罡北斗阵」阵法。\n"NOR, me);

	start_beidouzhen(me,0,power);
	start_beidouzhen(ob1,1,power);
	start_beidouzhen(ob2,2,power);
	start_beidouzhen(ob3,3,power);
	start_beidouzhen(ob4,4,power);
	start_beidouzhen(ob5,5,power);
	start_beidouzhen(ob6,6,power);

	return 1;
}
//变异的北斗杀人 by sohu new design
int beidou_kill(object ob)
{
	object me,ob1,ob2,ob3,ob4,ob5,ob6;
	me=this_player();
	//判断北斗状态
	
	if (!objectp(ob=present(ob,environment(me))))
	{
		return notify_fail("你要杀的目标不在现场！\n");
	}
	//ob=find_player(arg);
	
	if (!ob||environment(ob)!=environment(me)) 
	{
		return notify_fail("你要杀的目标不在现场！\n");
	}
	if (me->is_fighting(ob))
	{
		return notify_fail("你正在驱动北斗大阵追杀此人！\n");
	}
	me->kill_ob(ob);
	ob->kill_ob(me);
	if (!objectp(ob1=present(query_temp("ob1"),environment(me)))) 
	{
		
		return notify_fail("天罡北斗阵组阵人员目标不在现场！\n");
	}
	if (!objectp(ob2=present(query_temp("ob2"),environment(me)))) 
	{
		
		return notify_fail("天罡北斗阵组阵人员目标不在现场！\n");
	}
	if (!objectp(ob3=present(query_temp("ob3"),environment(me)))) 
	{
		return notify_fail("天罡北斗阵组阵人员目标不在现场！\n");
	}
	if (!objectp(ob3=present(query_temp("ob3"),environment(me)))) 
	{
		return notify_fail("天罡北斗阵组阵人员目标不在现场！\n");
	}
	if (!objectp(ob4=present(query_temp("ob4"),environment(me)))) 
	{
		return notify_fail("天罡北斗阵组阵人员目标不在现场！\n");
	}
	if (!objectp(ob5=present(query_temp("ob5"),environment(me)))) 
	{
		return notify_fail("天罡北斗阵组阵人员目标不在现场！\n");
	}
	if (!objectp(ob6=present(query_temp("ob6"),environment(me)))) 
	{
		return notify_fail("天罡北斗阵组阵人员目标不在现场！\n");
	}
	ob1->kill_ob(ob);
	ob2->kill_ob(ob);
	ob3->kill_ob(ob);
	ob4->kill_ob(ob);
	ob5->kill_ob(ob);
	ob6->kill_ob(ob);
	/**/
	return 1;

}

//驱动北斗大阵去杀人 
int do_beidou(string arg)
{
	object ob,weapon,me = this_player();
	int beidou_time,i,mypos=0,power;
	object where;
	string ob_name;
	string name1,name2,name3,name4,name5,name6,name0;
	object ob0,ob1,ob2,ob3,ob4,ob5,ob6;

	seteuid(getuid());
	where = environment(me);

	if (me->is_busy() || me->query_temp("pending/beidouzhen"))
		return notify_fail("你现在正忙着呢。\n");


	if( !arg || sscanf(arg, "%s %s %s %s %s %s %s", name0,name1,name2,name3,name4,name5,name6)!=7 )
		return notify_fail("「天罡北斗阵」要有七人组成。你要和谁摆「天罡北斗阵」杀谁？ \n" + 
				     "beidou enemy name1 name2 name 3 name4 name 5 name 6\n");

	if( (int)me->query_temp("pending/beidou") )
		return notify_fail("你正在摆「天罡北斗阵」。\n");

	ob_name = me->query("name");
	if ( me->query("family/family_name") != "全真教" )
		return notify_fail("可惜你不是全真弟子，不会「天罡北斗阵」。\n");

	if ( me->query_skill("quanzhen-jianfa",1) <350 || 
	     me->query("combat_exp",1)<4500000 ||
	     me->query_skill("dodge") <450)
		return notify_fail("可惜你武功太差，不足350，不会「天罡北斗阵」。\n");
//攻击对象
	if( !(ob0 = present(name0, environment(me)) ) )
		return notify_fail("可惜你要杀的人不在这里！\n");

	if( !(ob1 = present(name1, environment(me)) ) )
		ob1 = find_player(name1);
	i = check_ob(ob1,me);
	if(  i !=1) return i;

	if( !(ob2 = present(name2, environment(me)) ) )
		ob2 = find_player(name2);
	i = check_ob(ob2,me);
	if(  i !=1) return i;

	if( !(ob3 = present(name3, environment(me)) ) )
		ob3 = find_player(name3);
	i = check_ob(ob3,me);
	if(  i !=1) return i;

	if( !(ob4 = present(name4, environment(me)) ) )
		ob4 = find_player(name4);
	i = check_ob(ob4,me);
	if(  i !=1) return i;

	if( !(ob5 = present(name5, environment(me)) ) )
		ob5 = find_player(name5);
	i = check_ob(ob5,me);
	if(  i !=1) return i;

	if( !(ob6 = present(name6, environment(me)) ) )
		ob6 = find_player(name6);
	i = check_ob(ob6,me);
	if(  i !=1) return i;

	power = me->query_skill("force") + 
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
	power += me->query_skill("sword")+ 
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
	power += me->query("str")+
               ob1->query("str")+
               ob2->query("str")+
               ob3->query("str")+
               ob4->query("str")+
               ob5->query("str")+
               ob6->query("str");
	power += me->query("dex")+
               ob1->query("dex")+
               ob2->query("dex")+
               ob3->query("dex")+
               ob4->query("dex")+
               ob5->query("dex")+
               ob6->query("dex");
	power = power / 140;

	if (power>50) power=50;
	if (power<18) power=18;

	set_temp("ob1",me->query("id"));
	set_temp("ob2",ob1->query("id"));
	set_temp("ob3",ob2->query("id"));
	set_temp("ob4",ob3->query("id"));
	set_temp("ob5",ob4->query("id"));
	set_temp("ob6",ob5->query("id"));
	set_temp("ob7",ob6->query("id"));
	
	start_beidouzhen(me,0,power);
	start_beidouzhen(ob1,1,power);
	start_beidouzhen(ob2,2,power);
	start_beidouzhen(ob3,3,power);
	start_beidouzhen(ob4,4,power);
	start_beidouzhen(ob5,5,power);
	start_beidouzhen(ob6,6,power);

	me->kill_ob(ob0);
	ob1->kill_ob(ob0);
	ob2->kill_ob(ob0);
	ob3->kill_ob(ob0);
	ob4->kill_ob(ob0);
	ob5->kill_ob(ob0);
	ob6->kill_ob(ob0);

	ob0->kill_ob(me);
	ob0->kill_ob(ob1);
	ob0->kill_ob(ob2);
	ob0->kill_ob(ob3);
	ob0->kill_ob(ob4);
	ob0->kill_ob(ob5);
	ob0->kill_ob(ob6);

	return 1;
}
//阵亡消失
void destruct_me(object me)
{
	destruct(me);
}
//检查有人离开的状况
void check_leaving(object me)
{
	string name = me->query("id");

	if( name == "qi zhicheng" ||
	    name == "shen zhifan" ||
	    name == "fang zhiqi" ||
	    name == "chen zhiyi" ||
	    name == "cui zhifang" )
	{
		object enemy = offensive_target(me);
		if( !objectp(enemy) && !me->is_busy() && !me->is_fighting() )
		{
			message_vision(HIY"\n$N作了个楫道：贫道先告退了！说完就快步离开了。\n"NOR, me);
			call_out("destruct_me",10,me);
			return;
		}

		call_out("check_leaving",5,me);
	}
}
//main 主程序
int beidouzhen(object me)
{
	object  where = environment(this_player());
	int beidou_time = (int)me->query_temp("beidou_time");
	object room, obj,enemy,weapon;
	int cost, bonus,mypos=me->query_temp("bd_pos");
	int power;
	object ob1,ob2,ob3,ob4,ob5,ob6,ob7;

//主角不在
	if( !(room = environment(this_player())) )
	{
		if(!objectp(weapon = me->query_temp("weapon"))
		||me->query_skill("sword")!="quanzhen-jianfa"
		||me->query_skill("parry")!="quanzhen-jianfa"
		|| (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIG"\n$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，" + 
					"退出「天罡北斗阵」。\n"NOR, me);
		}
		else
			message_vision(HIG"\n$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，" + 
					"退出「天罡北斗阵」。\n"NOR, me);
		
		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) 在 %d 秒内 Lianzhen 得到 %d 经验和 %d 潜能。\n", 
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		//tell_object(me,"本次七星大阵演练"+me->name(),+"得到"+me->query_temp("qz/jobexp")+);
		message_vision(HIY"$N本次大阵演练，共耗时"+chinese_number(time()-me->query_temp("qz/jobtime"))+"秒，共获得"+chinese_number(me->query_temp("qz/jobexp"))+"经验和"+chinese_number(me->query_temp("qz/jobpot"))+"点潜能！\n"NOR,me);
		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		//检查离开状况
		call_out("check_leaving",2,me);
		return 0;
	}

	enemy = offensive_target(me);
//大阵演练时间到了
	if ( beidou_time < 1 && 
	     !me->query_enemy()&& 
	     !objectp(enemy) && 
	     !me->is_busy() && 
	     !me->is_fighting() )
	{
		if(!objectp(weapon = me->query_temp("weapon")) 
		 ||me->query_skill("sword")!="quanzhen-jianfa"
		 ||me->query_skill("parry")!="quanzhen-jianfa"
		 || (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIG"\n$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，" + 
                                    "退出「天罡北斗阵」。\n"NOR, me);
		}
		else
			message_vision(HIG"\n$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，" + 
                                   "退出「天罡北斗阵」。\n"NOR, me);

		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) 在 %d 秒内 Lianzhen 得到 %d 经验和 %d 潜能。\n",
					ctime(time()),
					me->name(),
					getuid(me),
					time()- me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N本次大阵演练，共耗时"+chinese_number(time()-me->query_temp("qz/jobtime"))+"秒，共获得"+chinese_number(me->query_temp("qz/jobexp"))+"经验和"+chinese_number(me->query_temp("qz/jobpot"))+"点潜能！\n"NOR,me);

		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		call_out("check_leaving",10,me);

		return 0;
	}
//内力不够，精力不够
	if ( me->query("neili") < 60 || me->query("jingli")<50 )
	{
		if(!objectp(weapon = me->query_temp("weapon")) || 
		   (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIY"\n$N体力不支，只好身子向后一纵，使一招『收山式』，右拳划了一圈，" + 
					 "左掌往怀中一抱，退出「天罡北斗阵」。\n"NOR, me);
		}
		else
			message_vision(HIY"\n$N体力不支，只好身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，" + 
					 "往怀中一抱，退出「天罡北斗阵」。\n"NOR, me);

		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) 在 %d 秒内 Lianzhen 得到 %d 经验和 %d 潜能。\n",
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N本次大阵演练，共耗时"+chinese_number(time()-me->query_temp("qz/jobtime"))+"秒，共获得"+chinese_number(me->query_temp("qz/jobexp"))+"经验和"+chinese_number(me->query_temp("qz/jobpot"))+"点潜能！\n"NOR,me);

		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		call_out("check_leaving",2,me);
	
		return 0;
	}
//合作伙伴被打跑
	if( !(room->query_temp("ob1",1) &&
		objectp(ob1=present( room->query_temp("ob1",1),where) )  && 
		ob1->query_temp("beidou_time") &&
		objectp(ob2=present( room->query_temp("ob2",1),where) )  && 
		ob2->query_temp("beidou_time") &&
		objectp(ob3=present( room->query_temp("ob3",1),where) )  && 
		ob3->query_temp("beidou_time") &&
		objectp(ob4=present( room->query_temp("ob4",1),where) )  && 
		ob4->query_temp("beidou_time") &&
		objectp(ob5=present( room->query_temp("ob5",1),where) )  && 
		ob5->query_temp("beidou_time") &&
		objectp(ob6=present( room->query_temp("ob6",1),where) )  && 
		ob6->query_temp("beidou_time") &&
		objectp(ob7=present( room->query_temp("ob7",1),where) )  && 
		ob7->query_temp("beidou_time") ))
	{
		if(!objectp(weapon = me->query_temp("weapon")) || 
		   (string)weapon->query("skill_type") != "sword" )
		{
			message_vision(HIG"\n$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，" + 
					"退出「天罡北斗阵」。\n"NOR, me);
		}
		else
			message_vision(HIG"\n$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，" + 
					"退出「天罡北斗阵」。\n"NOR, me);
		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) 在 %d 秒内 Lianzhen 得到 %d 经验和 %d 潜能。\n", 
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N本次大阵演练，共耗时"+chinese_number(time()-me->query_temp("qz/jobtime"))+"秒，共获得"+chinese_number(me->query_temp("qz/jobexp"))+"经验和"+chinese_number(me->query_temp("qz/jobpot"))+"点潜能！\n"NOR,me);

		me->remove_all_enemy();
		me->delete_temp("pending/beidou");
		me->delete_temp("beidou_time");
		me->delete_temp("bd_pos");
		me->delete_temp("bd_power");
		room->delete_temp("ob1");
		room->delete_temp("ob2");
		room->delete_temp("ob3");
		room->delete_temp("ob4");
		room->delete_temp("ob5");
		room->delete_temp("ob6");
		room->delete_temp("ob7");
		call_out("check_leaving",2,me);

		return 0;
	}


	beidou_time = beidou_time-1;
	me->set_temp("beidou_time", beidou_time);
	bonus = random( ( me->query("int")+me->query("con")+25 ) / 30 ) + 
		 (me->query("int")+me->query("con")+25 ) / 30;
	if( bonus > 4 ) bonus = 4;

	//if( (int)me->query("potential") < me->query_potential_limit() )
	
	me->add("potential", random(bonus));
	me->add( "combat_exp", random(bonus));
//增加大阵演练
	if (me->query_skill("tiangang-beidouzhen",1) < me->query_skill("xiantian-gong",1))
	{
		me->improve_skill("tiangang-beidouzhen", me->query_int() + random(me->query("int") + me->query_skill("tiangang-beidouzhen",1) / 8));
	}
	me->add_temp("qz/jobpot", bonus);
    me->add_temp("qz/jobexp", bonus*3/2);

	enemy = offensive_target(me);

	power = me->query_temp("bd_power",1)*4;

	me->add_temp("apply/parry",power);
	me->add_temp("apply/armor",power);
//入阵后自身忙碌、闭气
	if( random(3)==1 )
	{
		tell_room(environment(me), HIR"\n" + zhen[(int)random(4)] +"\n"NOR, this_object());

		if( objectp(enemy) && objectp( present( enemy->query("id"),environment(me) )) )
			enemy->add_busy( 1+random(2) );
		if (!random(4))
			enemy->add_condition("no_exert",1);
	}

	if( objectp(enemy) && objectp( present( enemy->query("id"),environment(me) )) )
	{
		//if( random(5)==1 )
		//{
			if(random(2)==0)
				message_vision("\n" + position[mypos] + "位上的$N气沉丹田，暗运神功，" + 
						"猛然吐气开声，身形往前一纵, 但见", me);
			else message_vision("\n" + position[mypos] + "位上的$N挺身而出，步法精妙，" + 
						"长袖飘飘，攻势如虹。只见", me);
			
			me->add_temp("apply/damage",power/2);
			me->add_temp("apply/attack",power/2);
			COMBAT_D->do_attack(me, enemy, me->query_temp("weapon"),3);
			me->add_temp("apply/damage",-power/2);
			me->add_temp("apply/attack",-power/2);
			me->add("jingli", -15-random(15));
			me->add("neili", -20-random(20));
		//}
	}
	else
	{
		if ( random(6)==1 )
		{
			if( ( weapon = me->query_temp("weapon") )
				&& (string)weapon->query("skill_type") == "sword" )
			{
				message_vision("\n" + position[mypos] + "位上的$N"+ sword[random(10)]+"\n", me);
			}

			me->add("jingli", -15-random(10));
			me->add("neili", -20-random(15) );
		}
	}

	me->add_temp("apply/parry",-power);
	me->add_temp("apply/armor",-power);

	if (beidou_time > -1)
		return 1;

	me->delete_temp("pending/beidou");
	me->delete_temp("beidou_time");
	me->delete_temp("bd_pos", mypos);
//剑掉了
	if(!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword" )
	{
		message_vision(HIG"\n$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，" + 
				"退出「天罡北斗阵」。\n"NOR, me);

		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) 在 %d 秒内 Lianzhen 得到 %d 经验和 %d 潜能。\n", 
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file. 
		message_vision(HIY"$N本次大阵演练，共耗时"+chinese_number(time()-me->query_temp("qz/jobtime"))+"秒，共获得"+chinese_number(me->query_temp("qz/jobexp"))+"经验和"+chinese_number(me->query_temp("qz/jobpot"))+"点潜能！\n"NOR,me);

	}
	else
	{
		message_vision(HIG"\n$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，" + 
				"退出「天罡北斗阵」。\n"NOR, me);
		if (userp(me))
			log_file("job/qz-lianzhen",
				sprintf("[%s] %s(%s) 在 %d 秒内 Lianzhen 得到 %d 经验和 %d 潜能。\n",
					ctime(time()),
					me->name(),
					getuid(me),
					time()-me->query_temp("qz/jobtime"),
					me->query_temp("qz/jobexp"),
					me->query_temp("qz/jobpot") )); //add log file.    
		message_vision(HIY"$N本次大阵演练，共耗时"+chinese_number(time()-me->query_temp("qz/jobtime"))+"秒，共获得"+chinese_number(me->query_temp("qz/jobexp"))+"经验和"+chinese_number(me->query_temp("qz/jobpot"))+"点潜能！\n"NOR,me);

	}
	call_out("check_leaving",5,me);
	return 0;
}
//启动北斗阵
void restart (object me)
{
	start_beidouzhen(me, me->query_temp("bd_pos"), me->query_temp("beidou_time",1) );
}
//暂停北斗阵,和restart对应
int halt_beidou(object me)
{
	object weapon;
	int beidou_time = (int)me->query_temp("beidou_time",1);
	if (beidou_time > 0)
	{
		if( !living(me) ) return 1;

		if(random(2)==1)
		{
			message_vision(HIG"\n$N踉跄了一步，差点摔出北斗阵。\n"NOR, me);
		}
		else message_vision(HIG"\n$N被打的晃了几晃，不过又站稳了步子。\n"NOR, me);
		call_out("restart",4,me);
		return 1;
	}

	if(!objectp(weapon = me->query_temp("weapon"))
	   || (string)weapon->query("skill_type") != "sword" )
	{
		message_vision(HIG"\n$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，" + 
				"退出「天罡北斗阵」。\n"NOR, me);
	}
	else
		message_vision(HIG"\n$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，" + 
				"退出「天罡北斗阵」。\n"NOR, me);
	me->delete_temp("pending/beidou");
	me->delete_temp("beidou_time");
	me->delete_temp("bd_pos");
	me->delete_temp("bd_power");
	return 1;
}
//停止大阵
int stop_beidou()
{
	object weapon,me=this_player();
	if(!me->query_temp("pending/beidou"))
		return notify_fail("停什么？你不在运行「天罡北斗阵」。\n");
	if(!objectp(weapon = me->query_temp("weapon"))
	   || (string)weapon->query("skill_type") != "sword" )
	{
		message_vision(HIG"\n$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，" + 
				"退出「天罡北斗阵」。\n"NOR, me);
	}
	else
		message_vision(HIG"\n$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，" + 
				"退出「天罡北斗阵」。\n"NOR, me);
	me->remove_all_enemy();
	me->delete_temp("pending/beidou");
	me->delete_temp("beidou_time");
	me->delete_temp("bd_pos");
	me->delete_temp("bd_power");
	return 1;
}

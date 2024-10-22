// loseletter.c
//
// Created by mxzhao 2004/03/22

#include <ansi.h>
#include <job_mul.h>

inherit ITEM;

#define BASE_EXP   300
#define BASE_POT	400
#define BASE_MONEY	100

#define RAND_EXP   200
#define RAND_POT	600
#define RAND_MONEY	200

#define GET_EXP(exp)		(exp = (BASE_EXP + random(RAND_EXP)) * LOSELETTER_JOB_MUL/100)
#define GET_POT(pot)		(pot = (BASE_POT + random(RAND_POT)) * LOSELETTER_JOB_MUL/100)
#define GET_MONEY(money)	(money = BASE_MONEY + random(RAND_MONEY))
#define GET_ITEM(obj)		(obj = new(bonus_items[random(sizeof(bonus_items))]))

string do_look();
private int set_addressee();
private int do_send(string arg);

string *bonus_items = ({
	"/clone/medicine/renshen-guo", 
});


void create()
{
	set_name(YEL"失落的信笺"NOR, ({ "letter", "xin", "lose letter" }));

	set_weight(10);

	if(clonep())
	{
		set_default_object(__FILE__);
	}
	else
	{
		set("unit", "封");
		set("value", 0);
		set("material", "paper");
		set("no_drop",1);
	}

	set("long", (: do_look :));

	set_addressee();

	setup();
}

void init()
{
	object me = this_player();

	if (!query("bearer"))
	{
		message_vision("$N得到了一封" + name() + "。\n", me);
		set("bearer", me->query("id"));
	}

	if (me->query("id") == query("bearer"))
	{
		if (me->query("id") == query("addressee"))
		{
			set_addressee();
		}
		
		if (query("addressee"))
		{
			add_action("do_send", "songxin");
		}
	}

	if (!query("calldest"))
	{
		set("calldest", 1);
		call_out("dest", random(300) + 300);
	}
}

string do_look()
{
	object ob;

	string str = "这是一封大理国镇南王府送出的书信。\n"
		"信封纸色蜡黄，信舌用火漆封着。\n";

	string target = query("addressee");

	if (target && objectp(ob = find_player(target)))
	{
		str += "信封上写着：" + ob->short(1) 
			+ "\n看来是很重要的信笺，要抓紧时间把它送去。\n";
	}
	else
	{
		str += "信封上的字迹模糊不清，不知何人遗落到此处。\n";
	}

	return str;
}

private int set_addressee()
{
	object *list = filter_array(users(), 
		(: $1->query("combat_exp") > 100000
		&& !wizardp($1)
		&& environment($1)
		:));

	list -= ({ this_player() });

	if(sizeof(list) == 0)
	{
		delete("addressee");
		return 0;
	}

	set("addressee", list[random(sizeof(list))]->query("id"));

	return 1;
}

 int do_send(string arg)
{
	int exp, pot, money;
	int obexp, obpot, obmoney;

	object ob, obj, obobj;
	object me = this_player();

	if ( !arg || !objectp(ob = present(arg, environment(me))))
	{
		return notify_fail("你要送给谁？\n");
	}

	if ( query("addressee") != arg )
	{
		return notify_fail("这封信不是送给这个人的。\n");
	}

	if ( me->is_busy() || me->is_fighting() )
	{
		return notify_fail("你正忙着呢。\n");
	}


	if ( !living(ob) )
	{
		return notify_fail("看清楚点，那是活人吗？！\n");
	}

	if ( !userp(ob) )
	{
		return notify_fail("嘿嘿，想作弊？！\n");
	}

	me->add_busy(random(2));

	message_vision("$n将" + name() + "交给了$N。\n", ob, me);

	if (random(10)==0)
	{
		message_vision("$N狐疑地看着$n：「这信怎么落到你的手上？」\n"
			"$N上下打量了$n两眼：「你当真没有偷拆来看过？" 
			+ RANK_D->query_self(ob) + "可是有隐私权的。」\n", ob, me);
		
		EMOTE_D->do_emote(ob, "liar");

		message_vision("$N越想越生气，暴打了$n一顿，打得$n遍体鳞伤。\n", ob, me);

		GET_EXP(exp);

		exp = random(exp/2);

		tell_object(me, "你被" + ob->name() + "打成重伤，经验下降了" 
			+ chinese_number(exp) + "点。\n");

		exp = -exp;

		//me->add("combat_exp", exp);
		me->add_exp_combat(exp, ob, "丢失的信", 1);

		EMOTE_D->do_emote(me, "wuwu", me->query("id"));
	}
	else
	{
		int itemp;

		EMOTE_D->do_emote(ob, "touch", me->query("id"));

		message_vision("过了一会儿，$N才说道：「我等侯段王爷的消息多时，"
			"正在踌躇为何音讯全无，真是多谢这位" 
			+ RANK_D->query_respect(me) + "。」\n", ob, me);
		
		switch (random(100)%5)
		{
		case 0:
			itemp = random(10) + 1;
			message_vision("$N拆开信笺看了看，喜道：「我在大理国购买的福利彩票中了" 
				+ chinese_number(itemp) + "等奖啦！！！」\n", ob, me);
			EMOTE_D->do_emote(ob, "yeah");

			GET_MONEY(money);
			money /= itemp;
			money *= 10000;
			me->add("balance", money);

			GET_MONEY(obmoney);
			obmoney /= itemp;
			obmoney *= 10000;
			ob->add("balance", obmoney);

			tell_object(ob, "你获得了大理国福利彩票滚动奖金" 
				+ MONEY_D->money_str(obmoney) + "，奖金已汇入你的账户。\n");

			tell_object(me, "为了感谢你的拾「信」不昧，" + ob->name() 
				+ "给你的账户汇入了" + MONEY_D->money_str(money) + "。\n");
			break;
		case 1:
			itemp = random(100) + 1;
			message_vision("$N拆开信笺，上面写着：「您所购买的大理国天龙股份最近下跌了" 
				+ chinese_number(itemp) + "个百分点！！！」\n", ob);
			EMOTE_D->do_emote(ob, "xbc");
			message_vision("$N说道：「多谢这位" + RANK_D->query_respect(me) 
				+ "送信给我，我要赶紧去补仓了。」\n", ob);

			GET_POT(pot);
			pot = pot*itemp/100;
			if (pot < 0)
			{
				pot = 0;
			}
			me->add("potential", pot);

			tell_object(me, "你擦了擦额头上的汗，心想：「幸亏我没买那破股票，"
				"看这小子赔得本都快没了，还在那儿穷装。」\n"
				"你觉得自己特英明神武，顿时心胸舒畅，增加了" 
				+ chinese_number(pot) + "点潜能。\n");
			break;
		case 2:
			message_vision("$N拆开信笺看了看，大喜道：「我因为送信勤恳，"
				"已经被评选为大理年度劳动模范了！」\n", ob);

			EMOTE_D->do_emote(ob, "touch");

			message_vision("$N说道：「多谢这位" + RANK_D->query_respect(me) 
				+ "送信给我。」\n", ob);

			GET_EXP(exp);
			GET_POT(pot);
				
			//me->add("combat_exp", exp);
			exp = me->add_exp_combat(exp, ob, "丢失的信", 1);
			
			me->add("potential", pot);

			GET_EXP(obexp);
			GET_POT(obpot);
			//ob->add("combat_exp", obexp);
			obexp = ob->add_exp_combat(obexp, me, "丢失的信", 1);
			ob->add("potential", obpot);

			tell_object(ob, "你被评选为大理年度劳动模范，获得了" 
				+ chinese_number(obexp) + "点经验，" + chinese_number(obpot) + "点潜能。\n");
			
			tell_object(me, "你心想自己拾「信」不昧，在此基础上再加把劲，"
				"来年兴许也能评为光荣的劳动模范，不由精神大为振奋。\n"
				"你获得了" + chinese_number(exp) + "点经验，" 
				+ chinese_number(pot) + "点潜能。\n");
			break;
		case 3:
			message_vision("$N拆开信笺，皱眉读道：「您给大理国所投简历，"
				"已经我大理人事局第一次筛选而拒绝！\n"
				"您妄图行贿大理人事领导的行为已被彻查，贿物送回，"
				"我国保留追究法律责任权力……」\n", ob);
			
			EMOTE_D->do_emote(ob, "wait");

			GET_ITEM(obj);

			message_vision("$N恶狠狠得瞪了$n一眼，气鼓鼓的把信笺内封的贿赂用品『" 
				+ obj->name() + "』扔在地上。\n", ob, me);

			GET_EXP(obexp);
			GET_POT(obpot);
			//ob->add("combat_exp", obexp);
			obexp = ob->add_exp_combat(obexp, me, "丢失的信", 1);
			ob->add("potential", obpot);

			tell_object(ob, "你行贿求职失败，卧薪尝胆，重练武学，获得了" 
				+ chinese_number(obexp) + "点经验，" + chinese_number(obpot) + "点潜能。\n");

			tell_object(me, "你捡到了" + ob->name() + "扔掉的『" + obj->name() + "』。\n");

			obj->move(me);
			break;
		case 4:
			message_vision("$N拆开信笺，却惊讶的发现，里面还有一封信笺。\n"
				"$N不由一笑：「一定是哪个大头虾把给别人的信笺错装进给我的信封里了。」\n", ob, me);

			new(__FILE__)->move(ob);

			EMOTE_D->do_emote(ob, "thank ", me->query("id"));

			GET_EXP(exp);
			GET_POT(pot);
			
			//me->add("combat_exp", exp);
			exp = me->add_exp_combat(exp, ob, "丢失的信", 1);
			me->add("potential", pot);
			
			tell_object(me, "你因为自己拾「信」不昧，获得了" 
				+ chinese_number(exp) + "点经验，" + chinese_number(pot) + "点潜能。\n");
		default:
			break;
		}
	}

	log_file("job/loseletter",
		strip(sprintf("%s(%s)送" + name() + "给%s(%s)，"
		"奖励%s点经验%s点潜能%s，物品：%s。\n",
		me->query("name"),
		me->query("id"),
		ob->query("name"),
		ob->query("id"),
		chinese_number(exp),
		chinese_number(pot), 
		MONEY_D->money_str(money), 
		objectp(obj)?obj->name():"无"
		)), 
		me );
	
	if (obexp>0 || obpot>0 || obmoney>0 || objectp(obobj))
	{
		log_file("job/loseletter",
			strip(sprintf("%s(%s)从%s(%s)处收到" + name() + "，"
			"奖励%s点经验%s点潜能%s，物品：%s。\n",
			ob->query("name"),
			ob->query("id"),
			me->query("name"),
			me->query("id"),
			chinese_number(obexp),
			chinese_number(obpot), 
			MONEY_D->money_str(obmoney), 
			objectp(obobj)?obobj->name():"无"
			)), 
			me );
	}

	destruct(this_object());
	return 1;
}

void dest()
{
	object ob = environment(this_object());
	if (userp(ob))
	{
		tell_object(ob, "你想来想去，事不关己，高高挂起，何必为他人苦苦奔波。\n"
			"你乘人不注意，偷偷把" + this_object()->name() + "扔进了路边的草丛。\n");
	}

	destruct(this_object());
}


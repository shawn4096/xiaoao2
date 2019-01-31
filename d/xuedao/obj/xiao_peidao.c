//藏人配刀.c
//入门job的要件
#include <ansi.h>

inherit ITEM;
int do_gongji(object me);
int do_cairou(string arg);
void create()
{
	set_name("小配刀", ({ "xiao peidao", "peidao", "dao", "blade" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把藏人寻常配备在腰间的小弯刀，刀长三寸左右。\n"
			+"上面雕刻了藏文和装饰，最下方写了“血刀门”定制字样！\n"
			+"初期job是采血，无需杀猎物,可以caixue(caiji) xx，如caixue ye zhu。\n"
			+"如果是采肉job，杀死猎物，输入指令为cairou corpse\n"
			+"具体job执行情况请用指令chakan peidao\n");
		set("value", 1000);
		set("material", "iron");
	}
} 

int init()
{
	add_action("do_cairou","cairou");
	add_action("do_caixue","caixue");
	add_action("do_caixue","jixue");
	add_action("do_report","chakan");

}
int do_caixue(string arg)
{
	object me,ob,at;
	string arg1;
	me=this_player();
	
	if (!arg)
	{
		return notify_fail("你要对什么动物采血？");
	}
	if (me->query("combat_exp")>100000)
	{
		return notify_fail("你的经验值已经够高的了,超过100k，把这些低级任务让给师弟们去做吧！\n");
	}
	if (!me->query_temp("xuedao/askcaixue"))
	{
		return notify_fail("你无缘无故来此采什么血！\n");
	}
	/*
	switch (arg)
	{
		case : 野猪
			arg1==ye zhu;
			break;
		case : 梅花鹿
			arg1==ye zhu;
			break;
	}*/
	ob=present(arg,environment(me));

	if (!ob) return notify_fail("你要采集的动物不在此处!\n");
	
	if (ob->query("id")=="corpse")
		return notify_fail("你要采集的这具动物尸体肉已经腐烂，无法采集!\n");
	if (ob->query("owner")!=me->query("id"))
		return notify_fail("这不是你发现的猎物，你无法采集!\n");

	if (ob->query("name")=="梅花鹿")
	{
		message_vision(HIC"$N小心前行，潜伏在草丛中，瞄准了那头梅花鹿，以血刀独到的天外流星手法将小配刀飞了出去。\n"NOR,me);
		if (random(me->query("combat_exp"))>me->query("combat_exp")/3)
		{
			message_vision(HIR"小配刀正中那头梅花鹿，新鲜的血液立即注满了中空的血槽，然后掉了下来。\n"NOR,me);
			
		}else me->add_busy(2);
	
		this_object()->add("xuedao/caixue/luxue",1);

	}else if (ob->query("name")=="野猪")
	{
		message_vision(HIB"$N快速奔跑，跑到野猪前，拿出小配刀轻轻扎了一刀。\n"NOR,me);
		this_object()->add("xuedao/caixue/zhuxue",1);

	}else if (ob->query("name")=="野兔")
	{
		if (me->query_skill("jingang-liantishu",1)<10) return notify_fail("你的金刚炼体术太低，不足10级，无法施展血刀门独有法门！\n");
		if (random(me->query("combat_exp"))>me->query("combat_exp")/3)
		{			
			message_vision(HIY"$N运使血刀门内劲手法飞掷手中配刀,金刚炼体术力量爆发，一刀正中飞奔中的野兔。\n"NOR,me);

		}else me->add_busy(2);

		this_object()->add("xuedao/caixue/tuxue",1);

	}else if (ob->query("name")=="野鹰")
	{
		
		message_vision(HIR"$N蹲下身来，拿出小配刀开始从这头野鹰身上采下血肉来,随手放入身边的袋子中。\n"NOR,me);
		this_object()->add("xuedao/caixue/yingxue",1);

	}else if (ob->query("name")=="獐子")
	{
		message_vision(HIG"$N蹲下身来，拿出小配刀开始从这头獐子身上采下血肉来,随手放入身边的袋子中。\n"NOR,me);
		this_object()->add("xuedao/caixue/zhangzixue",1);

	}
	if (this_object()->query("xuedao/caixue/luxue")
		&&this_object()->query("xuedao/caixue/tuxue")
		&&this_object()->query("xuedao/caixue/yingxue")
		&&this_object()->query("xuedao/caixue/zhangzixue")
		&&this_object()->query("xuedao/caixue/zhuxue"))
	{
		message_vision(HIM"\n\n$N检查了下自己随身皮囊，发现已经采集齐了师傅交代的五种不同新鲜血液，可以回去复命了！\n"NOR,me);
		this_object()->set("xuedao/caixue/ok",1);
		me->set_temp("xuedao/caixue/ok",1);
		me->start_busy(1);
	}
	me->start_busy(1);
	message_vision("\n那头"+ob->query("name")+"受到了惊吓，立即遁走，$N将这血槽中的新鲜血液关注到随身的皮囊中！\n",me);

	destruct(ob);
	me->receive_damage("qi",10);
	me->receive_damage("jing",10);


	return 1;
	
}
int do_cairou(string arg)
{
	object me,ob,obb;
	me=this_player();
	
	if (!arg)
	{
		return notify_fail("你要对什么动物采肉？");
	}
	ob=present(arg,environment(me));
	
	if (!ob) return notify_fail("你要采集的动物尸体不在此处!\n");
	
	obb=ob->query("kill_by");

	if (obb->query("id")!=me->query("id"))
		return notify_fail("这不是你杀的猎物，你无法采肉！\n");
	if (!me->query_temp("xuedao/askdalie"))
	{
		return notify_fail("你无缘无故来此采什么血！\n");
	}

	if (me->query("combat_exp")>300000&&me->query("quest/xuedao/baishi/pass"))
	{
		return notify_fail("你的经验值已经够高的了，超过300k，把这些低级任务让给师弟们去做吧！\n");
	}

	if (ob->query("id")!="corpse")
		return notify_fail("你要采集的这具动物尸体肉已经腐烂，无法采集!\n");
	if (ob->query("name")=="梅花鹿的尸体")
	{
		message_vision(HIC"$N蹲下身来，拿出小配刀开始从这头梅花鹿身上采下血肉来，随手放入身边的袋子中。\n"NOR,me);
		this_object()->add("xuedao/cairou/lurou",1);

	}else if (ob->query("name")=="野猪的尸体")
	{
		message_vision(HIC"$N蹲下身来，拿出小配刀开始从这头野猪身上采下血肉来,随手放入身边的袋子中。\n"NOR,me);
		this_object()->add("xuedao/cairou/zhurou",1);

	}else if (ob->query("name")=="野兔的尸体")
	{
		message_vision(HIC"$N蹲下身来，拿出小配刀开始从这头野兔身上采下血肉来,随手放入身边的袋子中。\n"NOR,me);
		this_object()->add("xuedao/cairou/turou",1);

	}else if (ob->query("name")=="野鹰的尸体")
	{
		message_vision(HIC"$N蹲下身来，拿出小配刀开始从这头野鹰身上采下血肉来,随手放入身边的袋子中。\n"NOR,me);
		this_object()->add("xuedao/cairou/yingrou",1);

	}else if (ob->query("name")=="獐子的尸体")
	{
		message_vision(HIC"$N蹲下身来，拿出小配刀开始从这头獐子身上采下血肉来,随手放入身边的袋子中。\n"NOR,me);
		this_object()->add("xuedao/cairou/zhangzirou",1);

	}
	if (this_object()->query("xuedao/cairou/lurou")
		&&this_object()->query("xuedao/cairou/zhurou")
		&&this_object()->query("xuedao/cairou/turou")
		&&this_object()->query("xuedao/cairou/yingrou")
		&&this_object()->query("xuedao/cairou/zhangzirou"))
	{
		message_vision(HIM"\n\n$N检查了下自己随身袋子，发现已经采集齐了师傅交代的五种不同肉，可以回去复命了！\n"NOR,me);
		this_object()->set("xuedao/cairou/ok",1);
		me->set_temp("xuedao/cairou/ok",1);
		me->start_busy(1);
		if (me->query("combat_exp")>100000)
			do_gongji(me);
	}
	me->start_busy(1);
	message_vision("\n$N将这具体尸体的肉精华采集干净，随手将骨架扔到一边的草丛之中！\n",me);
	destruct(ob);

	return 1;
	
}
int do_gongji(object me)
{
	object ob;
	if (!random(4))
	{
		ob=new("d/xuedao/npc/xuebao");
		if (me->query("combat_exp")>260000)
			ob->set("combat_exp",me->query("combat_exp"));
		ob->set("max_qi",(int)me->query("qi")*3/2);
		ob->set("eff_qi",(int)me->query("qi")*3/2);
		ob->set("max_jing",(int)me->query("qi")*3/2);
		ob->set("eff_jing",(int)me->query("jing")*3/2);
		ob->move(environment(me));
		ob->kill_ob(me);	
		message_vision(RED"这时，忽然从草丛中窜出一条饥饿的雪豹，向你袭来！\n"NOR,me);
		return 1;

	}else if (random(4)>1)
	{
		ob=new("d/xuedao/npc/chailang");
		ob->set("combat_exp",me->query("combat_exp"));
		ob->set("max_qi",(int)me->query("qi")*3/2);
		ob->set("eff_qi",(int)me->query("qi")*3/2);
		ob->set("max_jing",(int)me->query("qi")*3/2);
		ob->set("eff_jing",(int)me->query("jing")*3/2);
		ob->move(environment(me));
		ob->kill_ob(me);	
		message_vision(RED"这时，忽然从草丛中窜出一条凶猛的豺狼，向你袭来！\n"NOR,me);
		return 1;
	} else {
		ob=new("d/xuedao/npc/zigou");
		ob->set("combat_exp",me->query("combat_exp"));
		ob->set("max_qi",(int)me->query("qi"));
		ob->set("eff_qi",(int)me->query("qi"));
		ob->set("max_jing",(int)me->query("qi"));
		ob->set("eff_jing",(int)me->query("jing"));
		ob->move(environment(me));
		ob->kill_ob(me);	
		message_vision(RED"这时，忽然从草丛中窜出一条瘦弱的豺狼，向你袭来！\n"NOR,me);
		return 1;

	}
}

int do_report(string arg)
{
	object me,ob,at;
	string msg;
	me=this_player();
	ob=this_object();
	
	if (!arg||arg!="peidao")
	{
		return notify_fail("你要查看什么？");
	}

	if (me->query_temp("xuedao/askcaixue") && query("job")=="采血")
	{
		msg="注意，你必须搜集齐了兔血、猪血、鹰血、獐子血、鹿血才算完成任务。\n"
			+"你正在执行采血任务：\n";
		if (ob->query("xuedao/caixue/luxue"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/caixue/luxue")+"滴鹿血。\n";
		}
		if (ob->query("xuedao/caixue/tuxue"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/caixue/tuxue")+"滴兔血。\n";
		}
		if (ob->query("xuedao/caixue/zhuxue"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/caixue/zhuxue")+"滴猪血。\n";
		}
		if (ob->query("xuedao/caixue/yingxue"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/caixue/yingxue")+"滴鹰血。\n";
		}
		if (ob->query("xuedao/caixue/zhangzixue"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/caixue/zhangzixue")+"滴獐子血。\n";
		}
		if (ob->query("xuedao/caixue/ok"))
		{
			msg+="你的采血工作已经完成了，赶紧回去交付吧。\n";

		}

		tell_object(me,msg);
		return 1;
	}
	if (me->query_temp("xuedao/askdalie")&& query("job")=="采肉")
	{
		msg="注意，你必须搜集齐了兔肉、猪肉、鹰肉、獐子肉、鹿肉才算完成任务。\n"
			+"你正在执行采肉任务：\n";
		if (ob->query("xuedao/cairou/lurou"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/cairou/lurou")+"块鹿肉。\n";
		}
		if (ob->query("xuedao/cairou/turou"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/cairou/turou")+"块兔肉。\n";
		}
		if (ob->query("xuedao/cairou/zhurou"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/cairou/zhurou")+"块猪肉。\n";
		}
		if (ob->query("xuedao/cairou/yingrou"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/cairou/yingrou")+"块鹰肉。\n";
		}
		if (ob->query("xuedao/cairou/zhangzirou"))
		{
			msg+="你已经搜集了"+ob->query("xuedao/cairou/zhangzirou")+"块獐子肉。\n";
		}
		if (ob->query("xuedao/cairou/ok"))
		{
			msg+="你的采肉工作已经完成了，赶紧回去交付吧。\n";

		}
		tell_object(me,msg);
		return 1;
	}
	
	return notify_fail("你目前没有任何job\n");
	
}
// zhushao
// 98.8.5  by emnil
// 10/6/2001 by augx@sj

#include <ansi.h>
inherit ITEM;
int she_come(object me,object ob);

void create()
{
	set_name(HIB"翠竹笛"NOR, ({ "cuizhu di","di","zhudi" }) );
	set("long",HIY"这是一只用灵蛇岛独自产的翠玉竹雕刻的笛子，此笛子主要来驯蛇使用。\n"
		"可以通过如下指令来达到训练蛇的目的！\n"NOR
		HIG"zhaoshe  ：此指令是在一个地方招引蛇过来指令。此指令暂时限定在灵蛇岛区域\n"
		"此指令最好在有蛇的房间内，否则远程引蛇时间较长！\n"NOR
		HIC"qushe   : (qushe xx)训练蛇驱使蛇的动作(出口方向，如 qushe east ,驱蛇向右方向走)。\n"NOR
		HIR"anfu :（anfu xx）对于处于暴躁和攻击你的蛇的安抚功能,让其恢复正常\n"NOR
		HIG"fangshe  ：(fangshe xx)把蛇放走。\n"NOR
		HIM"需要注意的是，训蛇失败会导致蛇对你的攻击,适当备用蛇药或雄黄是很重要的！\n"NOR);
	set("unit", "只");
	set("weight", 50);
	set("no_sell",1);
	set("no_get",1);
	set("no_steal",1);
	set("no_drop",1);
	//set("no_give",1);
	set("value", 1);
} 

void init()
{
	add_action("do_anfu","anfu");
	add_action("do_zhaoshe","zhaoshe");
	add_action("do_fangshe","fangshe");
	
	//add_action("do_nashe","nashe");
	//add_action("do_chushe","chushe");
	add_action("do_xunshe","qushe");
	//add_action("do_huti","huti");
	//add_action("do_gongji","gongji");
}
//找蛇

int do_zhaoshe(string arg)
{ 
	object me,ob,room;
	
	
	me = this_player();
	room=environment(me);
	if (!me->query_temp("sld/qushe/start"))
		return notify_fail("你拿出竹笛吹的呜哩哇啦，甚是乱弹琴！\n");
	
	if( me->query_temp("sld/qushe/zhaoshe") )
		return notify_fail("你已经找到你的蛇目标了呢！\n");
	
	if( (int)me->query_temp("sld/qushe/qushe") )
		return notify_fail("你正在训蛇中...。\n");
	
	if(!environment(me)->query("canfindsnake"))
		return notify_fail("你在这里找不到蛇。\n");
	
	if((int)me->query("jingli")<200)
		return notify_fail("你的精力不够200。\n");
	if((int)me->query_skill("shenlong-yaoli",1) < 100) 
		return notify_fail("你的神龙药理修为不够100级，不能招蛇。\n");
	if((int)me->query_skill("dulong-dafa",1) < 100) 
		return notify_fail("你的毒龙大法修为不够，不能驯蛇。\n");
	if((int)me->query_skill("poison",1) < 100) 
		return notify_fail("你的毒计修为不够，不能驯蛇。\n");
	if (me->is_busy()||me->is_fighting())
		return notify_fail("你正在忙碌，稍微休息下再吹。\n");
	if (room->query("outdoors")!="神龙岛")
	{
		return notify_fail("只有神龙岛区域才盛产毒蛇！\n");
	}
	if (me->is_busy()||me->is_fighting())
		return notify_fail("你正在忙碌中，无法寻找蛇。\n");
	
	message_vision(HIG"$N拿出竹笛，幽幽的吹了起来，声音有些刺耳，使人不自觉的觉得有些心中发瘆的感觉。\n"NOR,me);

	if (random(me->query("kar"))>10)
	{
			message_vision(HIY"\n\n竹笛幽幽，附近的蛇忽然昂首，闻声而动，向笛声处涌来。\n"NOR,me);
			if (!objectp(ob=find_object(me->query("id")+"'s xunshe")))
			
			ob=new("/d/sld/npc/obj/snake");
			me->set_temp("sld/qushe/zhaoshe",1);
			call_out("she_come",6+random(4),me,ob);

	}
	else message_vision(YEL"似乎远处传来一阵沙沙的声音.......似乎有蛇...但等了半天却是没到此处.....。\n"NOR,me);

	
	me->receive_damage("jingli",100+random(100));
	me->add_busy(5+random(2));
	
	return 1;	

}

int she_come(object me,object ob)
{
	int lvl,exp;
	
	if (!objectp(ob)) return notify_fail("你没有找到蛇。\n");
	
	ob->set("owner",me->query("id"));
	
	ob->set_name(me->query("name")+HIG"的训蛇"NOR, ({ me->query("id")+"'s xunshe","xunshe","she" }) );
	
	message_vision(HIG"\n$n"HIG"缓缓的爬来，昂着头，吐着蛇芯，围在$N的跟前三尺之处，盘起来，一动不动。\n"NOR,me,ob);

	exp = me->query("combat_exp"); 
	if( exp < 100000) exp = 100000;
	
	ob->set("combat_exp",exp);
	ob->set("long",ob->query("long")+HIC"这是玩家"+me->query("name")+HIC"所训练的宠物蛇！\n"NOR);
	ob->set("max_qi",me->query("max_qi"));
	ob->set("eff_qi",me->query("max_qi"));
	ob->set("qi",me->query("max_qi"));  
	ob->set("max_jing",me->query("max_jing"));
	ob->set("eff_jing",me->query("max_jing"));
	ob->set("jing",me->query("max_jing")); 
	
	ob->set("max_neili",me->query("max_neili"));
	ob->set("neili",me->query("max_neili"));
	ob->set("eff_jingli",me->query("eff_jingli"));
	ob->set("jingli",me->query("eff_jingli"));
	lvl = me->query("max_pot") - 100;
	ob->set_skill("force",lvl);
	ob->set_skill("dodge",lvl);
	ob->set_skill("parry",lvl);
	ob->set_skill("poison",lvl);
	ob->set_temp("apply/attack",lvl);
	ob->set_temp("apply/dodge",lvl);
	ob->set_temp("apply/parry",lvl);
	ob->set_temp("apply/force",lvl);
	ob->set_temp("apply/defense", lvl);
	ob->set_temp("apply/damage",(lvl/10)>20?(lvl/10):20);
	ob->set_temp("apply/armor", (lvl/3)>50?(lvl/3):50);
	//ob->set_temp();
	ob->move(environment(me));
	me->set_temp("sld/qushe/zhaoshe",1);
	this_object()->set_temp("sld/qushe/zhaoshe",1);
	return 1;

}
//驱赶蛇移动目标
int do_xunshe(string arg)  
{
	object me,ob,room;
	
	string dir,exit;
	int ap,dp,i,j;
	me = this_player();
	room=environment(me);
	//exit=room->query("exits");
	
	if( !me->query_temp("sld/qushe/zhaoshe") )
		return notify_fail("你没有找到蛇。\n");
 	if( !objectp(ob=present(me->query("id")+"'s xunshe",environment(me))) )
		return notify_fail("这没有你要找的蛇。\n");
	//ob就是目标蛇
	
	if (ob->query("owner")!=me->query("id"))
		return notify_fail("那不是你蛇，驱使不了。\n");
	
	ap=me->query_skill("qusheshu",1)*me->query_int()+me->query("combat_exp");
	dp=ob->query("combat_exp");
	
	if (me->is_busy()||me->is_fighting())
		return notify_fail("你正在忙碌中，无法驱蛇行走。\n");

	switch(arg) {
		case "e":	dir="east"; break;
		case "w":	dir="west"; break;
		case "n":	dir="north"; break;
		case "s":	dir="south"; break;
		case "ne":	dir="northeast"; break;
		case "nw":	dir="northwest"; break;
		case "se":	dir="southeast"; break;
		case "sw":	dir="southwest"; break;
		case "u":	dir="up"; break;
		case "d":	dir="down"; break;
		case "nu":	dir="northup"; break;
		case "eu":	dir="eastup"; break;
		case "su":	dir="southup"; break;
		case "wu":	dir="westup"; break;
		case "nd":	dir="northdown"; break;
		case "ed":	dir="eastdown"; break;
		case "sd":	dir="southdown"; break;
		case "wd":	dir="westdown"; break;
		case "out": dir="out"; break;
		//case "l":	dir="look"; break;
		default:	dir=arg; break;
	}
	if (!arg||!dir)
		return notify_fail("你要指挥蛇向何处去？。\n");
	
	exit=room->query("exits/"+dir);
	
	if (!exit) {
		return notify_fail("这个方向没有出路。\n");		
	}
	
	message_vision(HIB"$N平心静气，吹起翠竹笛，音调婉转起伏，试图驱使$n向"HIY+dir+HIB"的方向而去!\n"NOR,me,ob);
	
	if (random(ap)>dp/3)
	{
		me->set_temp("sld/qushe/qushe",1);
		me->start_busy(1);
		call_out("she_move",1+random(2),me,ob,dir);
	}else
	{
		message_vision(HIR"$n被笛声驱使良久，仿佛甚是不耐，凶性大发，转头一口咬向$N！\n"NOR,me,ob);
		ob->kill_ob(me);
		
	}
	//交付任务
	if (objectp(ob)&&ob->query_temp("qushe/ok"))
	{
		tell_object(me,HIY"这条$n看起来似乎有些累了，很是温顺的爬入你的袖口之中！\n"NOR,me,ob);
		ob->move(me);
	}
	return 1;  
}
//蛇移动指令
int she_move(object me,object ob,string arg)
{

	if (!me||!ob) return 0;
	
	message_vision(HIM"$n静静听着$N的指挥，似乎听懂了$N笛声的意思，按$N指挥的"HIY+arg+HIB"方向而去!\n"NOR,me,ob);
	me->add_temp("sld/qushe/times",1);
	
	me->improve_skill("qusheshu",me->query_int());
	ob->do_command(arg);
	return 1;
}
//安抚愤怒的蛇
int do_anfu(string arg)
{
	object me,ob;
	me=this_player();
	
	if (!arg) return notify_fail("你要安抚啥？");
	
	//if (objectp(ob=present(arg,environment(me))))
	ob=present(arg,environment(me));
	if (!ob) return notify_fail("你要吹笛安抚谁？\n");
	
	if (ob->query("id")!=me->query("id")+"'s xunshe")
	{
		return notify_fail("你只能安抚自己的训蛇！\n");
	}
	if (!ob->is_fighting())
	{
		return notify_fail("你的训蛇已经很温顺了！\n");
	}
	if (!random(10)) 
	{
		message_vision(HIW"$N吹奏起另外一曲调的旋律，$n"HIW"听了似乎依然暴躁不已！\n"NOR,me,ob);
		
	}else {
		message_vision(HIW"$N吹奏起另外一曲调的旋律，$n"HIW"听了后似乎有些安静下来！\n"NOR,me,ob);
		ob->remove_all_killer();
		me->improve_skill("qusheshu",me->query_int());
	}
	me->add_busy(1);
	return 1;
}

//放蛇
int do_fangshe(string arg)      
{
	object me,ob;
//	object * all;
	me = this_player();

	if (!arg) return notify_fail("你要放生什么宠物？");
	
	//if (objectp(ob=present(arg,environment(me))))
	ob=present(arg,me);
	
	if (!ob) return notify_fail("你的宠物不在你身上？\n");
	
	if (ob->query("owner")!=me->query("id"))
		return notify_fail("别乱动，没有受过你驯化的蛇不能乱放。\n");
	
	if( !me->query_temp("sld/qushe/zhaoshe")
		|| !me->query_temp("sld/qushe/qushe") )
		return notify_fail("你没有驱蛇成功，找不到合适的蛇放生。\n");	

	
	message_vision(HIG"$N轻轻的把"+ob->query("name")+HIG"放下，拍拍它的头，小蛇轻叫一声就窜回树林中去了。\n"NOR,me);
	destruct(ob);
//	me->delete_temp("sld/qushe");
//	me->delete_temp("sld");
	set("taskok",1);
	me->set_temp("sld/qushe/taskok",1);
	//标记笛子成功
	return 1;
}

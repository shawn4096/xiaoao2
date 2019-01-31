// qufengshu.c  驱蜂术
// cre by sohu@xojh 2014/9
// 模仿小龙女的驱使玉峰，和job有关

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
	object weapon;
	object ob,yfj;
	string msg;
	weapon=me->query_temp("weapon");
	
	if( !target ) target = offensive_target(me);

	if( !target
	|| !objectp(target)
	|| !living(target)
	||	!me->is_fighting(target)
	||	!target->is_character())
		return notify_fail("你要驱使玉蜂攻击谁？\n");
	
	if((int)me->query_skill("yunu-xinjing",1) < 200)
		return notify_fail("你玉女心经的功力不够，不能驱使玉蜂!\n");
	if(!me->query("quest/gm/ynxj/qufeng/pass") )
		return notify_fail("你只是听说过训蜂术这门奇艺,但却没有丝毫经验不能驱使玉蜂!\n");
	if((int)me->query_skill("force",1) < 200)
		return notify_fail("你的基本内功修为不够,不能驱使玉蜂!\n");

	if((int)me->query("neili") < 2000)
		return notify_fail("你内力现在不够, 不能驱使玉蜂! \n");
	if((int)me->query("neili") < 800)
		return notify_fail("你精力现在不够, 不能驱使玉蜂! \n");
	if(me->query_skill_mapped("force")!="yunu-xinjing")
		return notify_fail("你激发的内功不对,不能驱使玉蜂!\n");

	if(!present("yufeng jiang",me) && !me->query("quest/gumu/ynxj/pass"))
		return notify_fail("你身上没有带玉蜂蜜,不能驱使玉蜂!\n");
	
	if (me->query_skill("qufengshu",1)<50)
		return notify_fail("你的驱蜂术尚未修炼成熟，还是去找小龙女请教吧！\n");


	if( target->query_temp("ynxj/fengmi") )
		return notify_fail(target->name() + "身上已经被弹了蜂蜜！\n");

	message_vision(HBYEL+HIW"$N运转玉女心经，在内力催发下，玉峰浆发出一阵阵幽香，沁人心脾，向四周散发而去。\n"NOR,me);	
	
	
	if (random(me->query_dex(1))>target->query_dex(1)/2)
	{
		message_vision(HIG"$N轻轻弹出一点蜂蜜，以内力裹住，弹到$n身上。\n"NOR,me,target);
		target->set_temp("ynxj/fengmi",1);
		call_out("yufeng_come",1,me,target,environment(target));
	}
	else {
		message_vision(HIC"$n冷笑几声，内功向外一弹将这些蜂蜜弹掉。\n"NOR,me,target);
		me->add_busy(1);
	}
	me->add("neili",600);
	me->add("jingli",200);
	//if (me->query_skill("yunu-xinjing",1)<450) 
	me->start_exert(4,"驭峰术");
	
	return 1;
}

int yufeng_come(object me,object target,object env)
{
	int i,j;
	object yufeng,room;
	if (!me||!target) return 0;
	i=(int)me->query_skill("qufengshu",1)/50;
	
	//这里加个判断，如果不在战斗中，或者无目标就返回
if (!me->is_fighting() || !living(target) || environment(me) != env || environment(target) != env) 
{
	message_vision(HBYEL"由于失去了目标，玉峰纷纷散去。\n"NOR,me);
	return 0;
}

  if(present( "yu feng", environment(me)))
	  
  return 0;
	
	message_vision(HBYEL"忽然从远方传来一片密集的嗡嗡之声，竟然来了大批的玉峰,瞬间将$n围了起来！\n"NOR,me,target);
	
	target->apply_condition("bee_poison",1);	
	for (j=0;j<i;j++ )
	{
		room=environment(me);
		if (environment(me) == env && living(target))
		{
		   if (present("yufeng jiang",me) || me->query("quest/gumu/ynxj/pass")) 
		   {			   
		   yufeng=new("d/gumu/npc/bee3");			
		   yufeng->move(room);
		   yufeng->set_temp("ynxj/attackname",target->query("id"));
		   yufeng->set("owner",me->query("id"));
		   }
		   else return notify_fail("你的蜂蜜用完了。\n");
			   
		}
		else
		{
			return notify_fail("战斗已经结束,蜂群也散了。\n");
		}
	}
	return 1;
}

string exert_name(){ return HIY"驱蜂术"NOR; }

int help(object me)
{
   write(WHT"\n玉女心经之「"HIY"驱蜂术"WHT"」："NOR"\n");
   write(@HELP
	玉蜂乃是古墓一代由小龙女培育的一个独特蜂种
	不仅锋针具有剧毒，而且经小龙女训练后，更懂
	得左右包抄、前后合围等精妙阵势，以之御敌极
	为有效。金轮国师之徒霍都为上终南山向小龙女
	求亲，曾纠集众多亡命之徒前往古墓，小龙女便
	是用玉蜂驱赶众人。参悟玉女心经第一段后，可
	以凭借花香和强大的内功驱使白玉蜂。450级后取
	消busy
	
指令：exert qufeng
  
要求：
	最大内力要求 3500 以上；
	当前内力要求 2000 以上；
	当前精力要求 2000 以上；
	玉女心经等级 200 以上；
	驱蜂术等级需 200 以上；
	激发内功为玉女心经,
	需身带蜂蜜或蜂皇浆;	

HELP
   );
   return 1;
}

//modify By sohu@xojh
// xuesha.c 模仿老祖以血光慑人

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HBWHT+HIR"血  煞"NOR;}

int exert(object me, object target)
{

        int hits,i,skill;

        if( !target ) target = offensive_target(me);
		skill=me->query_skill("xuedao-jing",1);
		if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
        	return notify_fail("「血煞」只能对战斗中的对手使用。\n");
           
        if( (int)me->query_skill("xuedao-jing", 1) < 350 
        || (int)me->query_skill("huanxi-chan", 1) < 200 
        || (int)me->query_int() <=50 )
                return notify_fail("你修为还不够，还未能运用「血煞」！\n");
        if(!userp(me) )
                return notify_fail("你没有人性，乃是一个npc，算了吧！\n");
        if (!me->query("quest/xd/xdj/xuesha/pass"))
                return notify_fail("你尚未学会此招的运用法门！\n");
		if( me->query_skill("force", 1) < 350 )
                return notify_fail("你的内功修为火候未到，施展只会伤及自身！\n");
     
        if( me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为不足以运用「血煞」！\n");
        if( me->query("max_jingli") < 2500 )
                return notify_fail("你的最大精力修为不足以运用「血煞」！\n");
        if( me->query("neili") < 1000 )
                return notify_fail("你的内力不够，劲力不足以运用「血煞」！\n");

        if( me->query("jingli") < 500 )
                return notify_fail("你的精力有限，不足以运用「血煞」！\n");
        if( target->query_temp("xdj/xuesha"))
                return notify_fail("对方已经身中血煞精神伤害了");
        
		message_vision(HBRED+HIW"$P一阵喋喋怪笑，神情极为淫荡，用舌头舔了舔嘴唇，吧唧吧唧嘴，运转血刀经内功，对$n呼出一口气！\n" NOR, me , target);
        message_vision(HBRED+HIW"$n看$P如此邪恶，心中一凛，但觉的$N的神情极为阴森恐怖，心中忍不住打了个激灵！\n\n" NOR, me , target);
      		//蛤蟆功失效
 
        if( target->query_temp("hmg/nizhuan")){ 
           	message_vision("结果$P只觉$n招式怪异血煞无法成功！\n", me, target);
           	return 1;
        }
		//对九阴身法失效

        if( target->query_temp("jiuyin/fast")){
           	message_vision("结果$P只觉$n身形飘忽不定难以捉摸血煞无法成功！\n", me, target);
        	return 1;
        }
		if( target->query_temp("jyzj/jiuyang")){
           	message_vision("结果$P只觉$n一股刚猛至极的阳刚气传来，顿时破了这血煞！\n", me, target);
        	return 1;
        }

     			//对高僧失效

		if( (target->query_skill("buddhism", 1) > 200||target->query_skill("taoism", 1) > 200 ) && !target->is_killing(me->query("id")) ){
     		message_vision("结果$n佛法高深，血煞根本对$p没用！\n", me, target);
        	return 1;
        }
        if (target->query("gender")=="女性") 
        {
			if (me->query("per")>25)
			{
				i=5;
			}else if (me->query("per")>20)
			{
				i=4;
			}else i=3;
	
        }else i=2;

		if( random(me->query_int()) > target->query_int()/i )
		{
        	message_vision(HIB"结果$n受到$P的血煞的影响，原先的斗志顿然消失！\n", me , target);
       		target->remove_all_killer();
       		target->receive_damage("jing", me->query_int()*10, me);
       		target->receive_wound("jing", me->query_int()*3, me);
        	//target 防御下降
			if (!target->query_temp("xdj/xuesha"))
			{
				target->add_temp("apply/parry",-skill/2);
				target->add_temp("apply/dodge",-skill/2);
				target->set_temp("xdj/xuesha",skill);
				call_out("xdj_xuesha",1,target,skill/60);

			}

			if( !userp(target) )
        		target->add_busy(4); 
			else target->add_busy(2);

        	hits = random(60)+(me->query_dex()-target->query_dex())*5+(me->query("jingli")-target->query("jingli"))/20;
       		if (hits > 30)
			{
        		message_vision(HIR"$n受到$P血煞感应，越斗越是害怕，力气顿时无法凝聚! \n", me , target);
         		//target->apply_condition("xdj_poison", 3+random(3) );
         		target->apply_condition("no_perform", 3);
         		target->apply_condition("no_exert", 3);
         		target->set("jiali", 0);
         		me->start_busy(1);
        	}
        }
		me->add("neili",-300);
        me->add("jingli",-100);
        me->start_exert(5, "「血煞」");
        return 1;
}  
//消除血煞
int xdj_xuesha(object target)
{
	int skill;
	if (!target) return;
	skill=target->query_temp("xdj/xuesha");
	target->add_temp("apply/parry",skill/2);
	target->add_temp("apply/dodge",skill/2);
	target->delete_temp("xdj/xuesha");
	message_vision(HIW"$N激灵一抖，瞬间恢复自信，血煞影响彻底消失。\n"NOR,target);
	return;

}
int help(object me)
{
        write(RED"\n血刀经之"+HBWHT+HIR"「血煞」："NOR"\n\n");
        write(@HELP
	血刀经乃是青海黑教血刀门第一代掌门人血刀老祖所创，
	他号称武林第一邪派高手。主要原因就是因为这门奇特的
	内功和刀法相配，会产生意想不到的效果。
	
	「血煞」绝技乃是根据血刀经中所载邪恶招式所演化而来
	在进攻过程中不断发出淫笑之声以恐吓对方的心理，从而
	令对方投降或失去战斗力。源自老祖大雪谷一战。

	「血煞」这门武功甚是奇特，需要杀玩家来完成练胆的过
	程，杀害玩家越多，解开此门秘籍概率越大。
	
	注意：此招对身负蛤蟆功，九阴身法，九阳真经、佛法高
	深或修道高深人士失效，但对女人有特效，越是漂亮的女
	人中招的概率越大（克制美女），此招判断后天悟性。

	使用指令：yun xuesha
		
要求：
	当前内力要求 5000 以上；
	最大内力要求 1000 以上；
	最大精力要求 2500 以上；
	当前精力要求 1000 以上；
	基本内功等级 350  以上；
	血刀经功等级 350  以上；
	欢喜禅的等级 200 以上；
	当前悟性需求 50 以上；
	激发内功为血刀经；
	
HELP
        );
        return 1;
}


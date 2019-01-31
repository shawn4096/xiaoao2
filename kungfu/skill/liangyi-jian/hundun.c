//hundun.c 
//by sohu@xoojh 2016

#include <ansi.h>
inherit F_SSERVER;
void finish();
int perform(object me, object target)
{
        object weapon;
        int i=me->query_skill("liangyi-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用"HIG"混沌剑网"NOR"。\n");
        weapon = me->query_temp("weapon");
        if( !me->query("quest/kl/lyj/hundun/pass"))
                return notify_fail("你只是听过有这门绝技，无法施展出"HIG"混沌剑网"NOR"。\n");
		if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("parry") != "liangyi-jian"
            || me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("你手里没有剑，无法使用"HIG"混沌剑网"NOR"！\n");
        if( (int)me->query_skill("liangyi-jian", 1) < 500 )
                return notify_fail("你的正两仪剑法不够娴熟，无法施展出"HIG"混沌剑网"NOR"。\n");
        if( (int)me->query_skill("sword", 1) < 500 )
                return notify_fail("你的基本剑法不够娴熟，无法施展出"HIG"混沌剑网"NOR"。\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 500 )
                return notify_fail("你的玄天无极功不够娴熟，无法施展出"HIG"混沌剑网"NOR"。\n");
		if( me->query_temp("lyj/hundun") )
                return notify_fail("你的正在使用"HIG"混沌剑网"NOR"绝技。\n");
		if( me->query_skill_mapped("force")!="xuantian-wuji")
                return notify_fail("你激发的内功非玄天无极功，无法施展出"HIG"混沌剑网"NOR"。\n");
         
		if ( (int)me->query("max_neili") < 12500)
                return notify_fail("你的最大内力不够，无法施展出"HIG"混沌剑网"NOR"。\n");
        if ( (int)me->query("neili") < 1000)
                return notify_fail("你的真气不够，无法施展出"HIG"混沌剑网"NOR"。\n");
        if ((int)me->query("jingli") < 1000)
                return notify_fail("你的精力不够，无法施展出"HIG"混沌剑网"NOR"。\n");

        message_vision(HIB"\n$N"HIB"剑走无极，玄天无极功往复奔流，招式连绵不绝，把$n完全淹没在一团混沌剑意之中。\n"NOR, me,target);
        me->set_temp("lianhuan", 1);
		
		me->set_temp("lyj/hundun",1);
        me->add("neili", -100-random(100));
        me->add("jingli", -100);
        
		message_vision(HBBLU+HIW"$N手中的"+weapon->query("name")+HBBLU+HIW"如行云流水一般，向$n攻去,看似不重，却也蕴藏致命杀机！\n"NOR,me, target);
        message_vision(HBBLU+HIW"全身玄天无极功力运转，"+weapon->query("name")+HBBLU+HIW"上逐渐形成一层若隐若现的「混沌剑网」。！\n"NOR,me, target);

		me->add_temp("apply/attack",i/4);
		me->add_temp("apply/damage",i/5);
		me->add_temp("apply/sword",i/5);
	/*	
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		*/
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
	
		if (objectp(target)&&me->is_fighting())
				call_out("check_fight", 1, me, 1+i/30);
		else
			call_out("finish",1);
		return 1;
}
//附赠攻击

void remove_effect(object me)
{
         int i=me->query_skill("liangyi-jian",1);
         object target = offensive_target(me);
         if(!me) return;
		 
		 me->delete_temp("lianhuan");
         
		 if(!living(me)) return;
         
		 if (objectp(target)&&me->is_fighting()) 
		 {
             message_vision(HIB"\n\n$N"HIB"剑势如网交织逼至，从四方八面涌入，重重把$n前后左右紧夹。\n"+
				 "$n只觉得四周压力骤增，$N的「"HIG"混沌剑网"HIB"」已将$n团团围住！\n"NOR, me,target);
             me->set_temp("lianhuan", 5);
             me->set_temp("lianhuan2", 1);
			 target->add_busy(2);
			 target->set_temp("must_be_hit",1);
			 me->add_temp("apply/damage",i/5);
			 if(me->is_fighting(target) )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 if(me->is_fighting(target) )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 if(me->is_fighting(target) )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 target->delete_temp("must_be_hit");
			 me->add_temp("apply/damage",-i/5);
			 return;
		   }
   
}
void finish()
{
       int i;
	   object me = this_player();
	   if (!me) return;
       me->delete_temp("lianhuan"); 
       me->delete_temp("lianhuan2");

	   me->delete_temp("lyj/hundun");
	   i=me->query_skill("liangyi-jian",1);

	   me->add_temp("apply/attack",-i/4);
	   me->add_temp("apply/damage",-i/5);
	   me->add_temp("apply/sword",-i/5);
    
	   me->start_perform(5,"「"HIG"混沌剑网"NOR"」");
	   me->start_busy(1+random(2));

       message_vision(WHT"$N轻轻舒了一口气，混沌剑网逐渐消退，剑法恢复了自然。\n"NOR, me);
	   message_vision(HIB"\n$N"HIB"的"HIG"「混沌剑网」"HIB"绝技使完，$N衣衫飘飘，神采飞扬。\n"NOR, me);

	   return;
}


void check_fight(object me, int i)
{
    object weapon, target;
    int jl;

    if (!me ) return;
    
    target = offensive_target(me);
     
    if( !living(me) 
        || !target 
        || !me->is_fighting(target) 
        || !living(target)
        || environment(target)!=environment(me)
        || !me->query_temp("lianhuan"))
              call_out("finish",1);

    else if(me->query_skill_mapped("sword") != "liangyi-jian"){
                tell_object(me, HIR"你临时改换剑法，决定不再使用「"HIG"混沌剑网"NOR"」绝技。\n");
                call_out("finish",1);
				return;
                }
    else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
                tell_object(me, HIR"你临时改换武器，决定不再使用「"HIG"混沌剑网"NOR"」绝技。\n");
                call_out("finish",1);
				return;
                }
    else if ((int)me->query("neili") < 200 ){
                tell_object(me, HIR"你内力不济，只得缓缓收回「"HIG"混沌剑网"NOR"」。\n");
                call_out("finish",1);
				return;
                }
    else if ((int)me->query("jingli") < 100 ){
                tell_object(me, HIR"你体力不支，只得缓缓收回「"HIG"混沌剑网"NOR"」。\n");
                call_out("finish",1);
				return;
                }
    //else if(me->is_busy()) 
              //  call_out("check_fight", 1, me, i);
    
    else{
           me->add("neili", -180);
		   jl=100;
           jl= me->query_skill("liangyi-jian",1)+me->query_skill("xuantian-wuji",1);
           me->add("jingli", -30);
           message_vision(HBBLU+HIW"\n$N的剑气交织成网，层层叠叠，剑气弥漫，$n喘气如牛，行动迟缓，举步艰难。\n"NOR, me,target);
           if (jl<0 ) jl=100;
		   
		   if (random(me->query_skill("force",1)) > target->query_skill("force",1) /2 
               || random(me->query_dex(1)) > target->query_dex(1) /2  )
		   { 
               message_vision(HIC"\n$n只觉得自己周身被$N剑气缠绕，体内真气难以运转自如！\n"NOR, me,target);
               target->apply_condition("no_exert", 1);
			   message_vision(HIB"\n$n只觉得自己周身精力仿佛被一丝丝的抽了出来似得！\n"NOR, me,target);
			   if (target->query("jingli")>1200)
				   target->add("jingli",-200-random(1000));
				else target->set("jingli",0);
		
				target->add_busy(1+random(2));
				target->receive_damage("jing", -(jl+random(200)),me);
				if (target->query("neili")>1500)
					target->add("neili", -(jl+random(200))); 
				else target->set("neili",0);
          } 
		   me->add_temp("lianhuan",-1);                       
           i--;
          //最后关头，混沌出连招
		  if (me->query_temp("lianhuan")<=2 
			  && me->query_skill("liangyi-jian", 1) >500 
			  && !me->query_temp("lianhuan2")) 
			  remove_effect(me);  
		  //上面主要目的是奖励额外攻击
		  //else  
		  call_out("check_fight",2, me, i);
    }
}



string perform_name(){ return HBBLU+HIW"混沌剑网"NOR; }
int help(object me)
{
write(HIW"\n两仪剑法之"HBBLU+HIW"「混沌剑网」："NOR"\n\n");
write(@HELP
	混沌剑网是两仪剑法中绝招，将深厚内功通过剑意激发
	既有剑光凛冽之意，也有内劲激荡之形，最终形成一张
	大网，将对方层层包围在一片剑意的海洋中。不断消耗
	其精气，厉害非常。
	注意：本门功夫必须激发玄天无极功。一旦使用即为不
	死不休局面，完全靠此招式损耗敌人，切记切记。
	
	指令：perform sword.hundun

要求：
	最大内力要求 12500 点以上；
	当前内力要求 1000 点以上；
	当前精力要求 1000 点以上；
	两仪剑法等级 500 以上；
	玄天无极等级 500 以上；
	基本剑法等级 500 以上；
	激发剑法为两仪剑法；
	激发内功为玄天无极功；
	手拿剑类兵器。
HELP
);
return 1;
}


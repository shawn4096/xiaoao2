// feilun.c 飞轮，飞出去几个，手中留下2个
// 为了五衰，by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_DBASE;
inherit F_SSERVER;
void feilun_finish(object me);
void checking(object me, object target, int num);

string perform_name(){ return HBYEL+HIW"飞轮绝技"NOR; }

//string *falun=({ "金轮","银轮","铜轮","铅轮","铁轮"});
string *falun=({HIY"金轮"NOR,HIW"银轮"NOR,YEL"铜轮"NOR,WHT"铅轮"NOR,BLU"铁轮"NOR});
string fl;

int perform(object me, object target)
{
        object weapon, ob;
        int lv, damage,num;

        lv = (int)me->query_skill("xiangfu-lun", 1); 
        damage = lv + random(lv/2) + (int)me->query_skill("hammer",1);

		num=2+random(4);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                       return notify_fail("「飞轮绝技」只能对战斗中的对手使用。\n");

        if( me->query_temp("xfl/feilun"))
                       return notify_fail("你正在使用「飞轮绝技」！\n");
 
        if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "hammer"
          || me->query_skill_mapped("hammer") != "xiangfu-lun"
          || me->query_skill_mapped("parry") != "xiangfu-lun")
                 return notify_fail("你手里无轮，如何使用「飞轮绝技」？\n");
                 
        if((int)me->query("max_neili") < 5000 )
 
			return notify_fail("你的内力修为不够，无法使用「飞轮绝技」！\n");
        if( (int)me->query("neili") < 1000 )
 
			return notify_fail("你的内力不够！\n");
		if( (int)me->query("jingli") < 1000 ) 
			return notify_fail("你的精力不够！\n");
        if( me->query_skill("xiangfu-lun", 1) < 400 )

			return notify_fail("你的「降伏轮」等级不够，无法使用「飞轮绝技」！\n");
		if( me->query_skill("longxiang-boruo", 1) < 400 )
			return notify_fail("你的「龙象般若功」等级不够，无法使用「飞轮绝技」！\n");
        if( me->query_skill_mapped("force") !="longxiang-boruo" )
			return notify_fail("你激发的内功不对，无法使用「飞轮绝技」！\n");
        if( me->query_skill("hammer", 1) < 400 )
            return notify_fail("你的「基本锤法」等级不够，无法使用「飞轮绝技」！\n");
                 
        if( (int)me->query_str() < 70 )
            return notify_fail("你的先天臂力不足，「飞轮绝技」绝技对你来说几乎是太难了。\n");

        message_vision(HBYEL+HIW "\n$N将手中的"NOR+weapon->name()+HBYEL+HIW"飞出去"+num+"个，成旋转状以弧形飞向$n，使出「飞轮绝技」！"NOR"\n" NOR, me,target);
		message_vision(YEL "\n$N将余下的轮子执在手中，揉身而上，舞动起来，即可当锤砸，又可当盾牌，同时锋利的轮齿宛如刀匕！"NOR"\n" NOR, me,target);
        //me->start_perform(3+random(3), "「飞轮绝技」");
        ob = me->select_opponent();
        me->set_temp("xfl/feilun",lv);
		if (me->query_skill("xiangfu-lun",1)<450)
		{
			me->start_perform(1,"飞轮绝技");
		}
		me->add_temp("apply/attack",lv/4);
		me->add_temp("apply/hammer",lv/6);
		me->add_temp("apply/damage",lv/6);
	

		call_out("checking", 1, me, target,num);
		
        return 1;
}

void checking(object me, object target, int num)
{

       object weapon;
		int lvl;
		string *falun=({HIY"金轮"NOR,HIW"银轮"NOR,YEL"铜轮"NOR,WHT"铅轮"NOR,BLU"铁轮"NOR});
		
		if (!me) return;
		
		lvl=me->query_skill("xiangfu-lun",1)+me->query_skill("longxiang-boruo",1)/2;

		fl=falun[random(sizeof(falun))];
		
	
		if (num < 0 ||!objectp(target) || !me->is_fighting())
		{
		    feilun_finish(me);
			me->delete_temp("xfl/feilun");
			//message_vision(HIM"\n$N长吁一口气，将飞出去的"NOR+fl+HIM"陆续收回手中，飞轮绝技收功完毕！\n" NOR, me,target);
			return;
		}
        if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "hammer") {
                     //  tell_object(me, "\n你手中无轮，当下停止了「飞轮绝技」的运使。\n" NOR);
                       
					   feilun_finish(me);
                       me->delete_temp("xfl/feilun");
                       return;
        }
	    if (me->query_temp("xfl/feilun"))
	    {
	    
           message_vision(HIM"\n只见$N霹雳般一声断喝，运起龙象般若功，侧身猛然一拳硬生生击打在"NOR+fl+HIM"上，法轮方向猛的一转，直追向$n！\n" NOR, me,target);
           {             
				if (me->is_fighting(target))

					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                 me->add("neili", -random(400));

			}
		  }
 		   call_out("checking", 2, me,target,num-1); 
                                 
 }


void feilun_finish(object me)
{
        int lv;
		object weapon=me->query_temp("weapon");
        if ( !objectp( me ) ) return;
	//    lv=me->query_temp("xlf/feilun");
		lv = (int)me->query_skill("xiangfu-lun", 1); 
		me->add_temp("apply/attack",-lv/4);
		me->add_temp("apply/hammer",-lv/6);
		me->add_temp("apply/damage",-lv/6);
		me->delete_temp("xfl/feilun");
		if (weapon)
        		message_vision(HIM"\n$N一套「飞轮绝技」使完，"+weapon->query("name")+HIM"重又回到手中。\n"NOR, me);
		else  message_vision(HIM"\n$N一套「飞轮绝技」使完，但飞出去的轮子却不知遗落在何处。\n"NOR, me);

	
        //me->start_busy(2);
        me->start_perform(2,"飞轮绝技");
		return;
} 

int help(object me)
{
   write(YEL"\n降伏轮之「"HBYEL+HIW"飞轮绝技"YEL"」："NOR"\n");
   write(@HELP
	当年密宗金轮法王横扫西域，威镇草原，一手藏密金刚降伏轮
	使得出神入画！此「天人五衰」绝技乃法王得意之作，全由龙
	象之力以御气操作，法轮飞舞旋转，如飞龙降世，金刚开山！
	当世可挡之人寥寥无几！一招既出，招招连环。
	飞轮绝技乃是金轮法王当世不传之秘，将手中轮子飞出去数个
	然后手持几个轮子再近身攻击，远方的轮子遥相呼应，即可远
	攻，又可近身而战，即具有暗器的特点，又具有锤子和刀的特
	点。实乃降伏轮绝技的重要辅助技能。

	指令;perform hammer.feilun

要求：
	降伏轮法等级 400 级，
	基本锤法等级 400 级，
	龙象般若等级 400 级，
	最大内力需求 5000 以上，
	当前内力需求 1000 以上，
	当前精力需求 1000 以上，
	后天臂力要求 70  以上
	激发招架为降伏轮
	激发锤法为降伏轮
	激发内功为龙象般若
	
HELP
   );
   return 1;
}
/**/
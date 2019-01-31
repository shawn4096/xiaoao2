// jingangzhi.c 金刚指力 by sohu@xojh 2014.1 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp,skill,j;
        int damage;

        skill=me->query_skill("jingang-zhi",1);
   //     if (userp(me) && ! me->query("sl/jgz/pass"))
               // return notify_fail("你还没有受过高人指点，无法施展「金刚指力」。\n");
                        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「金刚指力」只能在战斗中对对手使用。\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("你必须空手才能使用「金刚指力」！\n");
        if (me->query_skill("force",1) < 450)
               return notify_fail("你的基本内功修为不够，不能使用这一绝技！\n");
		if (me->query_temp("jgz/nie"))
                return notify_fail("你正在使用金刚指力捏字诀诀这一绝技！\n");
		if (me->query_skill("finger",1) < 450)
                return notify_fail("你的基本指法修为不够，不能使用这一绝技！\n");
        if (me->query_skill("force",1) < 450)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");
        if (me->query("max_neili") < 9000)
                return notify_fail("你的最大内力的修为不够，不能使用这一绝技！\n");
		if (me->query("neili") < 3000)
                return notify_fail("你的当前内力的修为不够，不能使用这一绝技！\n");
        if (me->query_skill("jingang-zhi", 1) < 450)
                return notify_fail("你的大力金刚指修为不够，目前不能使用「金刚指力」！\n");

        if (me->query("jingli") < 1000)
                return notify_fail("你的体力不够，无法使用「金刚指力」！\n");
        if (me->query_skill_mapped("finger") != "jingang-zhi"||me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("你没有激发大力金刚指，不能使用「金刚指力」！\n");
        me->set_temp("jgz/nie",3);
		message_vision(HBRED+HIY"\n只见$N"HIY"使出大力金刚指「捏字诀」，伸出五指连攻三招，招招指向$n的四肢!\n"NOR,me, target);

	    if (me->query("class")!="bone")
	      j = to_int(skill/3.0 * skill/250.0); //200级飞跃一次
        else j=to_int(skill/5.0 * skill/250.0);
	    me->add_temp("apply/attack", j/2);
	    me->add_temp("apply/finger", j/2);
	    me->add_temp("apply/damage", j/3);

	   ap = me->query("combat_exp", 1) / 1000 * me->query_skill("finger",1);
	   dp = target->query("combat_exp", 1) / 1000 * target->query_skill("parry",1);
      
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);

	   if( random(ap + dp ) > dp) {
		 message_vision(HIR"结果$N一招得手，$n的手腕居然被$N捏了个正着！\n"NOR,me, target);
         message_vision(HIW"随着$n一声惨叫传来，同时传来一阵骨骼断裂的声音。显然已经为$N大力金刚指劲力所捏断！\n"NOR,me, target);
		 target->set_temp("must_be_hit", 1);
		 //target->receive_damage();
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		 target->delete_temp("must_be_hit");
         target->apply_condition("broken_arm",1+random(3)); 
		 me->add("neili", -300);
	   }
	   me->add_temp("apply/attack", -j/2);
	   me->add_temp("apply/finger", -j/2);
	   me->add_temp("apply/damage",-j/3);
	   me->add("neili", -400);
	   me->add("jingli", -150);
	   me->delete_temp("jgz/nie");
	   me->start_perform(4,"「金刚指力」");
	   me->start_busy(1+random(2));
	   return 1;
}
string perform_name(){ return HIY"金刚指力"NOR; }

int help(object me)
{
        write(HIG"\n大力金刚指之"+HIY"「金刚指力」："NOR"\n\n");
        write(@HELP
	大力金刚指乃是少林绝技。金刚门的祖师本是少林寺香积厨中一名在灶下
	烧火的火工头陀，因掌管香积厨的武僧性子甚是暴躁，故常遭其殴打，三
	年间被接连打得吐了三次血，便决意学武报复，又因有过人之智，得以在
	二十余年间偷学成极上乘的武功。后自忖自己的武功已胜过阖寺僧众，终
	在一年一度的中秋达摩堂大校中发难。他在大校上接连重创达摩堂九大弟
	子，更在与达摩堂首座苦智禅师较量时趁机将其击死，后又于当晚潜入寺
	中将香积厨中和自己有过过节的五位僧人一一使重手打死，随后逃至西域，
	开创金刚门一派。大力金刚指即为本门派最高武技。
	后来，火工头陀弟子在武当山上以此绝技大战张无忌，同时得知这位三弟
	子曾用此绝技和空性大师龙抓手以快破快，破了空性大师的龙抓手并杀了
	空性大师，可见此武功的厉害之处。
	捏字诀的要义是通过运使金刚指力，将对方手臂或脚踝捏断，从而造成对
	方受伤而动作失效状态。少林俗家有优势。

指令:perform finger.jingang

要求：
	当前内力 3000 以上；
	最大内力 9000 以上；
	当前精力 1000 以上；
	金刚指等级 400 以上；
	易筋经等级 400 以上；
	基本指法等级 400 以上；
	基本内功等级 400 以上；
	激发指法且备为金刚指；
	激发内功不限制。
HELP
        );
        return 1;
}
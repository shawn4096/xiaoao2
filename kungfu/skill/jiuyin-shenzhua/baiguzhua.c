// Code of JHSH
// Modified by haiyan@huaxia

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object report;
        int damage,lvl,lvl1,k,l,ap,dp;
        string str;

        if (!target ) target = offensive_target(me);

        if (!target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("「白骨抓」只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你手中拿着武器，如何使出「白骨抓」？\n");

        if ((lvl=(int)me->query_skill("jiuyin-shenzhua",1))< 450)
                return notify_fail("你的九阴神爪修为不够。\n");

        if ((lvl1=(int)me->query_skill("cuixin-zhang",1))< 450)
                return notify_fail("你的摧心掌修为不够。\n");

        if (userp(me) && !me->query("quest/jiuyin2/jybgz/pass"))
                return notify_fail("你尚未和梅超风请教，不会使用「白骨抓」这个绝招！\n");

        if (me->query("jiali") < 200)
                return notify_fail("你的出手这么轻，又何必痛下杀手呢？\n");
		if (me->query_skill_mapped("claw")!="jiuyin-baiguzhua"
			||me->query_skill_prepared("claw")!="jiuyin-baiguzhua")
                return notify_fail("你尚未激发九阴神爪。\n");

        if (me->query("neili")<=lvl*4) return notify_fail("你的内力不够！\n");

        if (me->query("jingli")<=lvl) return notify_fail("你的精力不够！\n");

        message_vision(HIW+BLU "\n$N突然凌空虚抓，右手随即疾伸如电。五根手指后发先至，带着嗤嗤的劲气扣向$n的天灵。\n"
			+"但是$N的出手招式却和以前大不相同，招式大开大合，更为精妙，威力陡增！\n" NOR, me,target);

        ap = me->query_skill("claw",1) + me->query_skill("force",1) + me->query_str()*10; 
        ap += me->query("jiali")*2/3;
        dp = target->query_skill("dodge",1) + target->query_skill("force",1) + target->query_con()*10; 

        me->add("neili", -lvl);
        if (!target->is_killing(me->query("id"))) target->kill_ob(me);

		if( me->query("shen") > -1000000 && me->query("PKS") < 10 )
			return notify_fail("你不够狠毒，无法使出「白骨抓」的绝技。\n");
		if(me->query("no_pk") )
			return notify_fail("你洗手玩家，无法使出「白骨抓」的绝技。\n");
        
		if (!living(target))
        {
                message_vision(HIR "只听噗的一声响，$N的五根手指已插入了$n的头顶。$n顿时气绝身亡！\n\n" NOR, me,target);
                target->die(me);
                return 1;
        }

        if (ap / 2 + random(ap) < dp )
		{  
                message_vision(CYN "$n自知无幸，不料$N功力尚浅，虽然一击命中，却已是强弩之末，再也无力按下去了。\n\n" NOR, me,target);
                me->add_busy(1);
                return 1;
        }

        if (ap / 2 + random(ap) > dp
			||random(me->query("combat_exp"))>target->query("combat_exp")/2
			|| !living(target)) 
        {
                damage = (lvl + lvl1)*2 + me->query_str()*me->query("jiali")*3/target->query_con();
                
				if (damage<=1000) 
                        message_vision(BLU "$n心知此招厉害，竭力向后闪躲。虽是堪堪避过，早已惊出了一身冷汗。\n\n" NOR, me,target);
                else {
                        if ((int)damage >= target->query("eff_qi")) 
                        {
                                message_vision(HIR "只听噗的一声响，$N的五根手指已插入了$n的头顶。\n\n" NOR, me,target);
                                target->receive_wound("qi",1,me);
                                target->die(me);
                                return 1;
                        }
                        message_vision(MAG "$n心知此招厉害，竭力向后闪躲。虽然避过了天灵要害，脸上却给抓了五道血痕。\n\n" NOR, me,target);
                        target->receive_wound("qi",damage,me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        message_vision("($N"+str+")\n", target);
                }
                target->add_busy(1+random(3));
                me->add("neili", -lvl);
                me->add_busy(1);
                return 1;
        }
        if (ap / 2 + random(ap) > dp * 3/2 || !living(target)){  
                damage=(2+random((me->query_str()*2+me->query("jiali"))/100))*lvl;
                if ((int)damage >= target->query("eff_qi")) {
                        message_vision(HIR "只听噗的一声响，$N的五根手指已插入了$n的头顶。\n\n" NOR, me,target);
                        target->die(me);
                        return 1;
                }
                if ((int)damage/target->query("eff_qi")*100>=50&&(int)damage/target->query("eff_qi")*100<100)
                        message_vision(HIR "只听唰的一声，$n的天灵盖已被扯下一大块头皮，顿时血流如注。\n\n" NOR, me,target);
                if ((int)damage/target->query("eff_qi")*100<50)
                        message_vision(HIR "只听哧的一声，$n的脑门已被抓出了五条鲜血淋漓的爪痕。\n\n" NOR, me,target);
                target->receive_wound("qi", damage, me);
                str = COMBAT_D->status_msg((int)target->query("eff_qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);
                target->start_busy(1+random(3));
                me->add("neili", -lvl*2);
                me->start_busy(4);
                return 1;
        }
        message_vision(HIC "$n早有提防，从容地向后退了半步，便已避开了$N的致命一击！\n\n" NOR, me,target);
        tell_object(me, HIR"你奋力一击，只道就此得手。不想却被对手轻易闪过，背后登时露出了极大的空门。\n\n"NOR);
        me->add_busy(2+random(3));
		me->start_perform(2,"");
        return 1;
}


string perform_name(){ return HBWHT+HIB"白骨爪"NOR; }

int help(object me)
{
        write(RED"\n九阴神爪之「白骨爪」："NOR"\n\n");
        write(@HELP
	九阴白骨爪乃是九阴真经下卷的功夫，为一代奇人
	黄裳搜集敌人武功所归纳，放在卷首，并标明了破
	解之法。陈玄风梅超风二人不明白上卷武功，只凭
	个人揣摩，把 “五指发劲，无坚不破，摧敌首脑，
	如穿腐土 ”理解成用人头骨练习这门功夫。但此功
	法威力不俗，加上伤人无数，也成就了这白骨爪的
	赫赫威名。
	
	白骨爪绝技，力透指间，贯穿头顶而过！这是杀人
	的狠招，洗手玩家无法施展。此招需向梅超风请教
	
	perform claw.baiguzhua

要求：  
	当前内力的需求 2500 以上；
	最大内力的需求 15000 以上；
	当前精力的需求 800 以上；
	九阴神爪的等级 450 以上；
	基本爪法的等级 450 以上；
	基本内功的等级 450 以上；
	激发爪法为九阴神爪；                
	备爪法为为九阴神爪；
	负神大于1M且杀人数不足10个无法使用;
	且手无兵器且非洗手玩家；	

HELP
        );
        return 1;
}

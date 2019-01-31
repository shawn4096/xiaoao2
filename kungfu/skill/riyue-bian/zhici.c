// This program is a part of XOJH MudLIB
// zhici.c 直刺诀，以深厚内力化鞭为枪

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

    //    if (userp(me) && ! me->query("can_perform/riyue-bian/shang"))
      //          return notify_fail("你还没有受过高人指点，无法施展「直刺诀」。\n");
                 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「直刺诀」只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force",1) < 200)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("riyue-bian", 1) < 200)
                return notify_fail("你的日月鞭法修为不够，目前不能使用直刺诀！\n");
        if (me->query_skill("buddhism", 1) < 150)
                return notify_fail("你的日月鞭法修为不够150，目前不能使用直刺诀！\n");

        if (me->query("neili") < 500)
                return notify_fail("你的真气不够，无法使用直刺诀！\n");
        if (me->query("jingli") < 500)
                return notify_fail("你的精力不够，无法使用直刺诀！\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你没有激发日月鞭法，不能使用直刺诀！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
		message_vision(HIY "$N" HIY "嘿然冷笑，手中的" + weapon->query("name") +
              HIY "一振，霎时变得笔直，如同流星一般飞刺向$n" + HIY "！\n"
				+"那" + weapon->query("name") +HIY "化成一条笔直的兵刃，如长矛，如杆棒，疾刺而至!\n" NOR,me,target);


        ap = me->query_skill("whip",1)+me->query_skill("riyue-bian",1);

        dp = me->query_skill("parry",1)+me->query_skill("dodge",1);

		me->add("jingli", -200); 

        if (random(ap)>dp / 3
			||random(me->query_skill("force",1))>target->query_skill("force",1)/2)
        {
               damage = ap+me->query_skill("force",1);
                damage=me->query_str()*damage/20;
				
				me->add("neili", -300); 

				target->receive_damage("qi",damage,me);
				target->receive_wound("qi",damage/2,me);

				if (me->query("env/damage"))
				{
					tell_object(me,WHT"你对"+target->query("name")+"造成"+damage+"的杀伤值!\n");
					tell_object(me,WHT"你对"+target->query("name")+"造成"+damage/2+"的伤害值!\n");
				}
                message_vision(HIR "只见$p" HIR "一声惨叫，" + weapon->query("name") + HIR "竟然插在$p" + HIR "的身上，直接对穿而过，鲜血飞溅数尺，惨不堪言！\n" NOR,me,target);
                                         
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
				message_vision( CYN "可是$p" CYN "运足内力，奋力挡住了$P" CYN "这神鬼莫测的一击！\n"NOR,me,target);
                me->start_busy(1 + random(2));

        }
		me->start_perform(3,"直刺诀");

        return 1;
}
string perform_name(){ return HIR"直刺诀"NOR; }

int help(object me)
{
	write(HIC"\n日月鞭「直刺诀」："NOR"\n");
	write(@HELP
	日月鞭是少林三大武器之一，乃是修炼到极高阳刚之意后的由刚化柔的武功
	此时少林内功以达内力返照空明，功力精纯，不露棱角的境界。越长越是灵
	动，越短功力越强。长短收缩，自由收发于心。张无忌救谢逊，孤身犯险，
	以一抵抗三大神僧，那一战固然成就了张无忌的威名，但同时，少林三老的
	日月鞭也名扬天下。
	直刺诀乃是以强大内功，运劲于鞭，灌注其中，有开山裂石之力，功力越强
	大，威力越大,一招毙敌。
	
	指令：perform whip.zhici

要求：	
	当前内力 500 以上； 
	当前精力 500 以上； 
	易筋经等级 200 以上；
	日月鞭法等级 200 以上；
	禅宗心法等级 150 以上；
	激发鞭法为日月鞭法；
	激发日月鞭法为招架；
	激发易筋经为内功；
	装备长鞭类兵器。     
HELP
	);
	return 1;
}




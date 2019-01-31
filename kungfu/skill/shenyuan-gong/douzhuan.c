// douzhuan.c 斗转

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

int exert(object me, object target)
{
        object weapon;
        object *obs;
        object der;
        string msg;
        int ap, dp;
        int damage;
        int i;

      //  if (userp(me) && ! me->query("quest/mr/syg/douzhuan/pass"))
        //        return notify_fail("你暂时还不会使用斗转诀。\n");

        me->clean_up_enemy();
        
		if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「斗转诀」只能对战斗中的对手使用。\n");
		if (me->query_skill_mapped("force")!="shenyuan-gong")
                return notify_fail("你的激发内功不是慕容神元功，不会使用星移绝招。\n");
		if (me->query_skill_mapped("parry")!="douzhuan-xingyi")
                return notify_fail("你的激发招架不是斗转星移，不会使用星移绝招。\n");

        if ((int)me->query_skill("douzhuan-xingyi", 1) < 450)
                return notify_fail("你的斗转诀不够娴熟，不会使用绝招。\n");
        if (!me->query("quest/mr/dzxy/pass"))
                return notify_fail("「斗转诀」是慕容绝世武技，你只听说过，但需向慕容老爷子请教，不会使用绝招。\n");

        if ((int)me->query_skill("shenyuan-gong", 1) < 450)
                return notify_fail("你的神元功修为还不到家，"
                                   "难以运用「斗转诀」。\n");

        if (me->query("neili") < 5000)
                return notify_fail("你现在真气不够，无法使用「斗转诀」。\n");

        if (!living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
		
		if (me->query("max_neili")<9000)
                return notify_fail("你的最大内力不够，无法使用「斗转诀」绝招。\n");
		if (me->query("neili")<5000)
                return notify_fail("你的当前内力不够，无法使用「斗转诀」绝招。\n");
		if (me->query("jingli")<1000)
                return notify_fail("你的当前精力不够，无法使用「斗转诀」绝招。\n");

		if (me->query_temp("syg/douzhuan"))
                return notify_fail("你正在运使斗转诀，无法连续使用「斗转诀」绝招。\n");

        weapon = target->query_temp("weapon");
        
		if (weapon && weapon->query("id") == "zhen")
                return notify_fail("对方手里拿的是一根小小的针，"
                                   "你没有办法施展「斗转诀」。\n");
		
        msg = HIM "$N" HIM "运起斗转「斗转诀」心法，内力自气海穴出，经由"
              "任督二脉奔流而出，形成气机巧妙的牵引着$n" HIM "的招式！\n";

        ap = me->query("combat_exp")/100000; 
        dp = target->query("combat_exp")/100000;

        der = 0;
        me->add("neili", -500);
		me->add("jingli", -500);
		
		me->set_temp("syg/douzhuan",1);
        if (random(ap) > dp/2)
        {
                // Success to make the target attack hiself
                msg += HIR "结果$p" HIR "一招击出，正好打在自己的"
                       "要害上，不禁一声惨叫，摔跌开去。\n" NOR;
                damage = target->query("max_qi");
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 4, me);
        } else
        if (ap * 11 / 20 + random(ap) < dp)
        {
                // The enemy has defense
                msg += CYN "然而$p" CYN "内功深厚，并没有被$P"
                       CYN "这巧妙的劲力所带动。\n" NOR;
				me->add_busy(1);
        } else
        if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
        {
                // No other enemy
                msg += HIC "结果$p" HIC "的招式莫名其妙的变"
                       "了方向，竟然控制不住！幸好身边没有别"
                       "人，没有酿成大祸。\n" NOR;
        } else
        {
                string name;
                // Sucess to make the target attack my enemy
                der = obs[random(sizeof(obs))];
                name = der->name();
                if (name == target->name()) name = "另一个" + name;
                msg += HIG "结果$p" HIG "发出的招式不由自主"
                       "的变了方向，突然攻向" + name + HIG "，不禁令" + 
                       name + HIG "大吃一惊，招架不迭！\n" NOR;
				//der->add_busy(1);
        }

        message_combatd(msg, me, target);

        if (der)
        {
                // Target attack my enemy
                
				for (i = 0; i < 1 + random(3); i++)
                {
                        if (!der->is_busy()) der->add_busy(1);
                        COMBAT_D->do_attack(der, der, der->query_temp("weapon"),3);
                }
        }
		//解开斗转星移绝技，则
		if (!me->query("quest/mr/dzxy/pass"))
			me->start_exert(1, "斗转诀");
		call_out("xingyi_back",3,me);
        return 1;
}
int xingyi_back(object me)
{
	if (!me) return 1;
	
	me->delete_temp("syg/douzhuan");
	message_vision(HIM"$N将斗转星移神功之斗转诀缓缓收功！\n"NOR,me);
	return 1;

}
string exert_name(){ return HIC"斗转诀"NOR; }

int help(object me)
{
    write(WHT"\n斗转星移之「"HIC"斗转诀"WHT"」："NOR"\n");
         write(@HELP
	「斗转星移」是为慕容世家家传绝学，以深厚的内力困扰对方
	的招式，并将这招攻击随机引向所指向的敌人。斗转诀是斗转
	星移的基本心法所体现，虽说尚达不到「以彼之道，还施彼身」
	的定向反击威力，但对敌仍有出其不意的效果。该招需要跟慕
	容博请教，解密斗转星移绝技方可使用。
	注意：对阵针类武器无法使用此绝技

指令：exert douzhuan

要求：
	最大内力 9000 以上；      
	当前内力 5000 以上；  
	当前精力 1000 以上；
	斗转星移 450  以上；
	神元功法 450  以上；
	激发招架为斗转星移；
	激发内功为神元功；

HELP
    );
        return 1;
}

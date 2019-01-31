// by sohu@xojh 2014.1
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp,skill;
        int damage;
        skill=me->query_skill("jingang-zhi",1);
     //   if (userp(me) && ! me->query("sl/jgz/pass"))
             //   return notify_fail("你还没有受过高人指点，无法施展「金刚伏魔决」。\n");
                        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「金刚伏魔决」只能在战斗中对对手使用。\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("你必须空手才能使用「金刚伏魔决」！\n");
        if (me->query_skill("force",1) < 400)
                return notify_fail("你的基本内功的修为不够，不能使用这一绝技！\n");
		if (me->query_temp("jgz/fumo"))
                return notify_fail("你正在使用金刚伏魔诀使用这一绝技！\n");
		if (me->query_skill("finger",1) < 400)
                return notify_fail("你的基本指法修为不够，不能使用这一绝技！\n");
        if (me->query_skill("force",1) < 400)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");
        if (me->query("max_neili") < 8000)
                return notify_fail("你的最大内力的修为不够，不能使用这一绝技！\n");
		if (me->query("neili") < 2000)
                return notify_fail("你的当前内力的修为不够，不能使用这一绝技！\n");
        if (me->query_skill("jingang-zhi", 1) < 400)
                return notify_fail("你的大力金刚指修为不够，目前不能使用「金刚伏魔决」！\n");

        if (me->query("neili") < 3000)
                return notify_fail("你的真气不够，无法使用「金刚伏魔决」！\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi"||me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("你没有激发大力金刚指，不能使用「金刚伏魔决」！\n");

        msg = HIR "$N" HIR "当下屏息凝神，双目盯住在$n"+HIR"脸上，内息暗暗转动，周身骨骼劈劈拍拍，不绝发出轻微的爆响之声。\n"+
              HIY "$n" + HIY "一愕，知道这是佛门正宗的最上武功，自外而内，不带半分邪气，乃是金刚伏魔神通！\n" NOR;
		message_vision(msg,me,target);
        me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/strength",skill/10);
        me->add_temp("apply/damage",skill/5);
		me->add_temp("apply/finger",skill/8);
        me->set_temp("jgz/fumo",skill);
		call_out("remove_effect",1,me,target,(int)skill);
       
        return 1;
}

void remove_effect(object me,object target,int count)
{
        int skill;
		object weapon=me->query_temp("weapon");
        if(!me||!living(me)) return;
        
		if(!me->is_fighting()
         || weapon
         || me->query_skill_mapped("finger") != "jingang-zhi"
         || me->query_skill_prepared("finger") != "jingang-zhi" 
         || count < 1 )
		{
          skill = me->query_temp("jgz/fumo");
         me->add_temp("apply/attack",-skill/3);
		 me->add_temp("apply/strength",-skill/10);
         me->add_temp("apply/damage",-skill/5);
		 me->add_temp("apply/finger",skill/8);
         me->delete_temp("jgz/fumo");
	     message_vision(HIY"$N使完「金刚伏魔决」,手指上劲力逐渐消失，威力大减。\n"NOR, me);
          return;
        }
        else {
          //me->start_perform(1,"「金刚伏魔诀」");
          call_out("remove_effect", 1, me,target, count-1);
        }

}              
string perform_name(){ return HIC"金刚伏魔诀"NOR; }

int help(object me)
{
        write(HIG"\n大力金刚指之"+HIC"「金刚伏魔诀」："NOR"\n\n");
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
	
	指令：perform finger.fumo

要求：
	当前内力 1500 以上；
	最大内力 3500 以上；
	当前精力 1000 以上；
	金刚指等级 400 以上；
	易筋经等级 400 以上；
	基本指法等级 400 以上；
	基本内功等级 400 以上；
	激发指法且备为金刚指；
	激发内功不限制。450后大飞。
HELP
        );
        return 1;
}
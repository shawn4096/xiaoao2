// feidao.c   胡家刀法之「飞刀诀」.
// Create by lsxk@hsbbs 2007/5/11
#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me);

string perform_name() {return HIW"飞刀诀"NOR;}

int perform(object me,object target)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("「飞刀诀」只能在战斗中使用。\n");

		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「飞刀诀」只能对战斗中的对手使用。\n");
        
		if ((int)me->query_skill("hujia-daofa", 1) < 350 )
                return notify_fail("你的胡家刀法不够娴熟，还用不来「飞刀诀」。\n");
		if (me->query_skill("blade",1)<350)
                return notify_fail("你的基本刀法不足350，怎能使用云龙三现？！\n");
		if (me->query_skill("force",1)<350)
                return notify_fail("你的基本内功不足350，怎能使用云龙三现？！\n");

        if (!weapon 
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("parry") != "hujia-daofa"
         || me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("你的武功运用不对，无法使用「飞刀诀」。\n");
    
        if ((int)me->query("neili") < 1500 )
                return notify_fail("你现在内力太弱，不能使用「飞刀诀」。\n");

        if ((int)me->query("jingli") < 1500 )
                return notify_fail("你现在精力太少，不能使用「飞刀诀」。\n");

        if ((int)me->query_temp("hjdf/fdj"))
                return notify_fail("你正在使用「飞刀诀」绝技。\n"); 


        message_vision(HIC "$N立时一声清喝，手中"+weapon->name()+HIC"招数一变,使出胡家刀法之「飞刀诀」绝技！\n"+
        "胡家刀法讲究的是一个“慢”字，待敌人出招后，寻敌人破绽而攻之，$N这路刀法使将出来，动作已然缓慢下来。\n"+
        "而以后每出一招便是攻向对手破绽之处，刀法之妙，乃绝千古也！\n"NOR, me);

        if (me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
        && me->query_temp("lqsg/lq")
        && me->query_skill_mapped("force") == "lengquan-shengong")
            message_vision(HIW"在$N的冷泉神功之「"HIB"冷泉"HIW"」绝技配合下，手中"+weapon->name()+HIW"隐隐地泛着白色。\n"NOR, me);
       
		if (me->query_skill("hujia-daofa",1)<450)
			me->start_perform(2,"「飞刀诀」");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("hujia-daofa", 1);
        me->add_temp("apply/blade",  skill/4);
        me->add_temp("apply/attack",  skill/4);
        me->set_temp("hjdf/fdj", 1);

        call_out("check_fight",1,me,target,weapon,(int)me->query_skill("hujia-daofa",1)/50);
        return 1;
}

void check_fight(object me,object target,object weapon,int amount)
{  
        object wep,wep2;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if(!me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || me->query_skill_mapped("blade") != "hujia-daofa"
         || !wep
		 || amount<0
         || weapon != wep )
           remove_effect(me);
        else {
			if (objectp(wep2=present("fei dao",me))&& !random(2))
			{
				message_vision(HIW"\n$N在辗转腾挪间，往来奔突，顺手从后背中抽出把"+wep2->query("name")+HIW"扔向$n！\n"NOR,me,target);
				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
				wep2->add_amount(-1);
				if ((int)wep2->query_amount()<1)
				{
					message_vision(HIC"你身上所带的"+wep2->query("name")+HIC"已经用完了！\n"NOR);
					destruct(wep2);
				}
			}
			call_out("check_fight", 1, me,target,weapon,amount--);
		}
}

private int remove_effect(object me)
{         
        int skill;
        skill = (int)me->query_skill("hujia-daofa", 1);
 
        me->add_temp("apply/blade",  -skill/4);
        me->add_temp("apply/attack",  -skill/4);
        me->delete_temp("hjdf/fdj");
        if(living(me) && !me->is_ghost())
           message_vision(HIW"$N一套「飞刀诀」使完，长吁了一口浊气。\n"NOR, me);
        return 0;
}

int help(object me)
{
   write(WHT"\n胡家刀法「"HIW"飞刀诀"WHT"」："NOR"\n");
   write(@HELP
	此「飞刀诀」虽为胡家刀法之初级招试，但却秉承了胡家刀法
	的精髓“以慢打快，寻敌破绽，后发制人”，使用时，能短时
	间内提高自身攻击力和命中率，但这并不是全部，只有当对手
	成功发动攻击后，才能真正显示出该招的威力！另若使用者会
	武林绝学冷泉神功之「冷泉」绝技，则相辅相成，威力惊人！
	
	指令：perform blade.feidao

要求：
	当前内力 1500 以上；
	当前精力 1500 以上； 
	胡家刀法 350 以上；
	基本刀法 350 以上；
	基本内功 350 以上；
	激发刀法为胡家刀法；
	激发招架为胡家刀法(有特效)

HELP
   );
   return 1;
}

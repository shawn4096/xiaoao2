// shendao.c  血刀经 [无影神刀]
// changed by cloudy@zt

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
 
string perform_name(){ return HIB"无影神刀"NOR; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg, weaname;
        int lvl,damage,i,ap,dp;
    
        if( !me->is_fighting() )
                return notify_fail("「无影神刀」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if((int)me->query_dex() < 15)
                return notify_fail("你的身法不够, 目前还不能使用这项绝技! \n");

        if((int)me->query_skill("dodge") < 100)
                return notify_fail("你的轻功修为不够, 不能使用「无影神刀」！\n");
 
        if((int)me->query_skill("xuedao-daofa",1) < 100)
                return notify_fail("你的血刀刀法修为不够， 目前不能使用「无影神刀」! \n");

        if((int)me->query_skill("xuedao-jing",1) < 100)
                return notify_fail("你的血刀经修为不够， 目前不能使用「无影神刀」! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你必须使用血刀经，才能使用「无影神刀」的绝技！\n");

        if( me->query_skill_mapped("force") != "shenzhao-jing" && me->query_skill_mapped("force") != "xuedao-dafa")
	    	  return notify_fail("你现在所使用的内功同「血刀经」向抵触，不能使出「无影神刀」的绝技！\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("你的内力修为不够！\n");
        if((int)me->query("neili")<600)
                return notify_fail("你的真气不够！\n"); 
        if((int)me->query("jingli")<200)
                return notify_fail("你的精力不够！\n"); 

        ob = me->select_opponent();

        //if( !userp(me) && userp(ob) )
          //      return notify_fail("「无影神刀」只能由玩家使用！\n");

        lvl = (int)me->query_skill("xuedao-jing",1);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
        msg = HIY "\n$N暗运血刀经中的高深功夫「无影神刀」，手中"NOR+weaname+HIY"宛如隐入到一片红芒之中！\n"NOR;
        message_vision(msg, me);

        me->add_temp("apply/blade", lvl/5);
        me->add_temp("apply/parry", lvl/5);
        me->add_temp("apply/dodge", lvl/5);

        if(lvl>350){
            i = 3;
            me->add_temp("apply/attack", lvl/3);
            me->add_temp("apply/damage", lvl/4);
            }
        else i=0;
		ap=me->query("combat_exp",1);
        dp=ob->query("combat_exp",);
		//me->query_skill("xuedao-jing",1)
        if (random(ap)>dp/2 || random(me->query_skill("blade",1))>ob->query_skill("parry",1)/3)
        {
			message_vision(HBYEL"\n$n为这片诡异的血光所迷惑，似乎闻到一股莫名的甜香，开始手忙脚乱起来。\n",me,ob);
			ob->start_busy((int)lvl/50);
			if(lvl >350)
		    ob->add_temp("apply/defense",-lvl/5);
			me->add_temp("apply/attack", lvl/3);
			if (present(ob,environment(me)) && me->is_fighting(ob))
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), i);
			ob->add_temp("apply/defense",lvl/5);
			me->add_temp("apply/attack", -lvl/3);
        }
		else 
	    {
			message_vision("\n$n看破$N的企图，冷哼一声，闪了开去。\n",me,ob);
            me->start_busy(random(2));

	    }
		
        me->add("neili", -100-random(100));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -80);
        me->start_busy(random(2));
        if (me->query_skill("xuedao-jing",1)<449)
        {
			me->start_perform(4,"无影神刀");
        }
		        
        me->add_temp("apply/blade",- lvl/5);
        me->add_temp("apply/parry",- lvl/5);
        me->add_temp("apply/dodge",- lvl/5);

        
        if(lvl>350){
            me->add("neili", -100-random(100));
            me->add_temp("apply/attack", -lvl/3);
            me->add_temp("apply/damage", -lvl/4);
        }
        if(me->query_temp("xuedao/yuxue")) {
            me->add_temp("apply/damage", -damage);
        }
        return 1;
}

int help(object me)
{
	write(HIR"\n血刀经刀法之「无影神刀」："NOR"\n\n");
        write(@HELP
说明：
	无影神刀乃是血刀老祖独门武技，变幻莫测的刀法绝技，巧妙
	的运转刀锋，使其产生出无数层层叠叠的幻影，用以迷惑对手。
	倘若对手勘破不透其中玄机，将会导致无暇进攻或是脱身。
	
指令: perform blade.wuying

要求：
	最大内力  1200 以上；
	当前内力  1000  以上；
	血刀大法  100  级以上；
	350级后小飞，
	450后成为起手式。

HELP
        );
        return 1;
}
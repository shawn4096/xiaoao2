// jiangmang.c 剑芒
//cre buy sohu@xojh 2014/10
//根据108岛中剑神的武功编写，揉入到ljg的老谜题中

#include <ansi.h>
#include <combat.h>     
#include <weapon.h>
inherit F_SSERVER;

string *name1 = ({
        "玉堂穴",
        "大横穴",
        "幽门穴",
        "章门穴",
        "晴明穴",
        "紫宫穴",
        "风池穴",
        "百汇穴",
        "太阳穴",
        "长强穴",
        "灵台穴"
});

void check_fight(object me, object target,object weapon, int amount);

int perform(object me, object target)
{       
        string msg, name, name2;
        int ap, dp,skill,amount;
        object weapon = me->query_temp("weapon");
        skill=me->query_skill("tianyu-qijian",1);
		amount=(int)skill/10;
        if (! target) target = offensive_target(me);
 
        if (! target || ! target->is_fighting(me))
                return notify_fail("「剑芒」只能对战斗中的对手使用。\n");

        
        if (userp(me) && !me->query("quest/ljg/tyqj/jianmang/pass"))
                return notify_fail("你还没有受过高人指点，无法施展「剑芒」。\n");
	
         if (me->query_temp("tyqj/jianmang"))
                return notify_fail("你正在使用「剑芒」攻击敌人了。\n");
                
        if (target->query("qi") <= 50)
                return notify_fail("你现在没有必要用「剑芒」攻击敌人了。\n");

        if (! weapon || weapon->query("skill_type") != "sword"
        ||  me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("你现在无法使用「剑芒」攻击敌人。\n");

      

        if ((int)me->query_skill("tianyu-qijian", 1) < 350 
            || (int)me->query_skill("sword", 1) < 350
            || (int)me->query_str() < 50 
            || (int)me->query_dex() < 50)  
                return notify_fail("你有的功夫还不够娴熟，不会使用「剑芒」。\n");

        if ((int)me->query_skill("force", 1) < 350)
                return notify_fail("你的基本内功修为不够，无法领悟「剑芒」的精髓。\n");


        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你的内力太弱，无法使用出「剑芒」！\n");
        
        if ((int)me->query("neili") < 1500)
                return notify_fail("你的真气不够！\n");
                
        name = name1[random(sizeof(name1))];    
        name2 = weapon->query("name");

        message_vision(HIG "\n$N右手剑锋一转，身子滴溜溜的打了半个圈子，手中" + name2 + HIG "一挺，剑尖上突然生出半尺吞吐不定的青芒!\n" +
              HIG "这道剑芒犹似长蛇般伸缩不定，$N脸露狞笑，丹田中提一口真气，青芒突盛，向$n胸口刺来。\n" NOR,me,target);
        me->add("neili", -200);
		me->add("jingli", -200);
		//weapon->set_temp("tyqj/jianmang",1);

        ap = me->query_skill("sword",1);
        dp = target->query_skill("dodge",1);
                   
       if (random(ap+dp) > dp 
			||random(me->query_skill("force",1))>target->query_skill("force",1)/2 )
        {                
                message_vision(HIR "\n\n结果被剑气刺中"+HIY+name+HIR"，$n只觉得全身气脉通道阻塞，真气立受干挠！\n"NOR,me,target);   
                if (!userp(target))
					target->add_busy(2 + random(4));
				else target->add_busy(2);
                
			
                me->set_temp("tyqj/jianmang", 1);
				me->add_temp("apply/sword",skill/5);
				me->add_temp("apply/attack",skill/4);
				me->add_temp("apply/damage",skill/10);
				call_out("check_fight",1,me,target,weapon,amount);
          
        } else 
        {
                me->start_busy(2);
                me->add("neili", -100);
                target->add("neili", -100);
                message_vision(HIY"\n$p大叫一声不好，全身用力一纵，顺势跳了开去。\n" NOR,me,target);
        }    
       
        return 1; 
}
void check_fight(object me, object target,object weapon, int amount)
{
        object weapon1;
		int skill,damage;
		
		if (!me) return;
		skill=me->query_skill("tianyu-qijian",1);
		weapon1=me->query_temp("weapon");
		damage=(int)skill*me->query_skill("force",1)/100;
		/*
		if (weapon1->query("id")!=weapon->query("id")
			||weapon1->query("name")!=weapon->query("name")
			||weapon1->query_temp("tyqj/jianmang")
			||weapon->query_temp("tyqj/jianmang"))
		{
			me->add_temp("apply/sword",-skill/5);
			me->add_temp("apply/attack",-skill/4);
			me->add_temp("apply/damage",-skill/10);
			me->delete_temp("tyqj/jianmang");
			weapon->delete_temp("tyqj/jianmang");
			message_vision(HIC"$N将手中的"+weapon->query("name")+HIC"挽了个剑花，长吁一口浊气，剑芒逐渐消失。",me);
			return;
		}*/

        if ( amount<1 || !me->is_fighting())
        {
			me->add_temp("apply/sword",-skill/5);
			me->add_temp("apply/attack",-skill/4);
			me->add_temp("apply/damage",-skill/10);
			me->delete_temp("tyqj/jianmang");
			//weapon->delete_temp("tyqj/jianmang");
			message_vision(HIG"$N将手中的"+weapon->query("name")+HIG"挽了个剑花，长吁一口浊气，剑芒逐渐消失。\n"NOR,me);
			return;
                
        }
		if (random(10)>5)
		{
			switch (random(2))
			{
				case 0:
					if (objectp(target)&&me->is_fighting()) {
						message_vision(HIR"$N这一剑出了全力，中途无法变招，刷的一声响，长剑刺中$n，深入尺许。$n“哇”的一声吐了一口鲜血。\n"NOR,me,target);
						target->receive_damage("qi",damage,me);
						target->receive_wound("qi",damage/4,me);
					}
					break;
				case 1:
					if (objectp(target)&&me->is_fighting()) {
						message_vision(HIY"$N"+weapon->query("name")+HIY"抖动，一招”天如穹庐”，跟着一招”白雾茫茫”，两招混一，向$n递去，要将$n圈在剑光之中。\n"NOR,me,target);
						target->add_busy(2);
					}
					break;
				case 2:
					if (objectp(target)&&me->is_fighting()) {
						message_vision(HIW"$N向$n凝视片刻，神气十分坚决，突然间刷的一声，挥动"+weapon->query("name")+HIW"，寒光闪动，嗤嗤嗤几声轻响。\n"NOR,me,target);
						message_vision(HIW"在这一霎眼之间，$N纵两剑，横两剑，连出四剑，冲$n以剑划了一个”井”字。\n"NOR,me,target);
						
						COMBAT_D->do_attack(me, target,weapon, 3);
						COMBAT_D->do_attack(me, target,weapon, 3);
						
					}
					break;
				default:break;

			}
		}
		call_out("check_fight",2,me,target,weapon,amount-1);
		return;
}
string perform_name(){ return HIC"剑芒"NOR; }

int help(object me)
{
    write(WHT"\n天羽奇剑之「"HIC"剑芒"WHT"」：\n");
         write(@HELP
	天羽奇剑乃是天山童姥绝学之一，因天山派
	渊源和逍遥派休戚相关，乃三大分支之一，
	所以天羽奇剑的意境含有天然的虚幻飘渺之
	意，看似风轻云淡，但其中却蕴藏无限杀机
		 
	天羽奇剑之剑芒绝技，乃是吸收一百零八岛
	岛主们的奇思妙想，由剑神卓不凡所钻研而
	大成，是天羽奇剑的空灵、多变体现，需要
	得到剑神卓不凡的传授方可使用。
	
	perform sword.jianmang

要求：
	基本内功等级 350 以上;
	天羽奇剑等级 350 以上；
	基本剑法等级 350 以上；
	基本轻功等级 350 以上；
	最大内力需求 5000 以上
	当前内力需求 1500  以上
	当前精力需求 1000  以上
	激发剑法为天羽奇剑；
	激发招架为天羽奇剑；
	手持剑类武器；
HELP
    );
        return 1;
}
 
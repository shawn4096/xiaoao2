// sanyin.c 三阴暗劲
// sohu@xojh


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int myexp, targexp, damage, skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("三阴暗劲只能对战斗中的对手使用。\n");

		if( me->query_temp("sys/sanyin") )
               return notify_fail("你正在施展三阴暗劲功！\n");
        if( objectp(weapon=me->query_temp("weapon"))&&weapon->query("skill_type")!="throwing" )
               return notify_fail("非暗器类不能施展三阴暗劲！\n");

        if( me->query_skill_mapped("hand") != "sanyin-shou" )
                return notify_fail("你所用的并非三阴手，不能施展三阴暗劲！\n");

        if( me->query_skill_prepared("hand") != "sanyin-shou" )
                return notify_fail("你所备的并非三阴手，不能施展三阴暗劲！\n");


        if( (int)me->query_skill("force",1) < 220 )
                return notify_fail("你基本内功修为太差，不能运用三阴暗劲！\n");
        if( me->query_skill("hand",1) < 220 )
                return notify_fail("你的基本手法修为太差，不能运用三阴暗劲！\n");
        if( me->query_skill("sanyin-shou",1) < 220 )
                return notify_fail("你三阴手修为太差，不能运用三阴暗劲！\n");

        if( me->query("neili") <= 800 )
                return notify_fail("你的内力不够使用三阴暗劲！\n");
        if( me->query("jingli") <= 500 )
                return notify_fail("你的精力不够使用三阴暗劲！\n");     

        message_vision(HIB"$N真气流转，运劲于双手，双手又红变白，由白变红，反复三次，逐渐恢复到平常。\n\n"NOR, me,target);
        message_vision(HIB"随即$N朗笑一声，挥手攻向$n,挥舞间劲气汹涌。\n\n"NOR, me,target);

        myexp = me->query("combat_exp")/10000;
        targexp = target->query("combat_exp")/10000;
        skill = me->query_skill("sanyin-shou",1);
        if (me->query("gender")!="女性")
		{
			message_vision(YEL"$N强行运使三阴手，但种因骨骼粗壮，施展不出三阴手的阴柔威力!\n"NOR,me);
			skill=skill/2;
		}
		me->add_temp("apply/damage", skill/5);
        
		me->add_temp("apply/hand", skill/5);
		me->add_temp("apply/attack", skill/3);
        
		me->set_temp("sys/sanyin", skill);
    //调用自己程序            
		call_out("remove_me",1,me);
		//如果解开攻敌策略，则会有攻击敌人的招式
        if(random(myexp)>targexp/2
			||me->query("quest/kl/sys/sanyin/pass")
			||random(me->query_skill("sanyin-shou",1))>target->query_skill("parry",1)/2) 
		{

                message_vision(HIW"$n眼见$n双手笼罩难以闪避，只得挺右手相抵，试图化解这招攻势。\n"NOR,me,target);
				message_vision(HIW"$n忽觉自己手腕“寸关穴”一痛，有三股暗劲涌入，呈波浪式状态冲击自己经脉。\n"NOR,me,target);

           
				if (!target->query_temp("sys/sanyin"))
				{
					if(target->query("neili")<skill*3) 
					{
							target->set("neili", 0);
					}else target->add("neili",-skill*3);
					target->add_temp("apply/armor", -skill/5);
					target->add_temp("apply/dodge", -skill/5);
					target->add_temp("apply/parry", -skill/3);
					target->set_temp("sys/sanyin",skill);
					target->apply_condition("sys_anjin",4);
					target->add_busy(3);                
					call_out("remove_target",1,target);
				}

        }                      
        else 
        {       
                me->add_busy(1);    
                message_vision(HIY "$p赶紧向後跃开数丈，躲开$P的攻击。\n" NOR, me, target);
                me->add("neili",-250);
                return 1;
        }
		return 1;
}

//自我恢复
int remove_me(object me)
{
	int skill;
	skill=me->query_temp("sys/sanyin");
	if ( !objectp(me) ) return 1;
        
	me->delete_temp("sys/sanyin");
	me->add_temp("apply/damage", -skill/5);
    me->add_temp("apply/hand", -skill/5);
	me->add_temp("apply/attack", -skill/3);
	message_vision(HIG"慢慢的，$N觉得漫散的内力又一丝丝地聚回丹田。\n\n"NOR,me);
    return 1;
}
//对象恢复
int remove_target(object target)
{
	int skill;
	if (!target) return 0;

	skill=target->query_temp("sys/sanyin");
	
        
	target->add_temp("apply/armor", skill/5);
	target->add_temp("apply/dodge", skill/5);
	target->add_temp("apply/parry", skill/3);
	
	target->delete_temp("sys/sanyin");

	message_vision(HIG"慢慢的，$N觉得被三阴手暗劲造成的暗伤渐渐恢复。\n\n"NOR,target);
    return 1;
}

string perform_name() {return HIB"三阴暗劲"NOR;}

int help(object me)
{
   write(WHT"\n三阴手之「"HIY"三阴暗劲"WHT"」："NOR"\n\n");
   write(@HELP
	三阴手是昆仑名宿灵清居士的成名绝技，后来这门
	功夫为灵清居士去芜存精，结合昆仑女弟子灵巧的
	特点和昆仑轻功的优势，将此门功夫打造成适合女
	性弟子适用的集暗器和手法暗劲于一体的门派绝技
	
	三阴暗劲不以力胜，以深厚的功力，在双方接触的
	瞬间在对方寸关穴处注入三道暗劲，以此伤敌。解
	密后会出现伤敌效果。女性弟子有优势。此招需要
	向班淑娴请教后威力全开。

	perform hand.sanyin
		
要求: 
	当前精力 500 以上；
	当前内力 800 以上；
	基本手法 220  以上；
	基本内功 220  以上；
	三阴手法 220  以上；
	激发手法为三阴手；
	内功不限；
	空手状态；

          
HELP
   );
   return 1;
}

//cre by sohu@xojh 2013
#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me,object target)
{
        object weapon;
        string msg;
        int i = me->query_skill("huifeng-jian",1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「灭剑」绝技只能对战斗中的对手使用。\n");
        if (!me->query("em/mie/pass"))
                return notify_fail("你尚未得到灭绝师太的传授，无法使用「灭剑」绝技！\n");
        if(me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("你的内功不是峨嵋心法，无法使用「灭剑」绝技！\n");
        if( me->query_skill("linji-zhuang", 1) < 350 )
                return notify_fail("你的内功还未练成，不能使用「灭剑」绝技！\n");
        if( me->query_skill("huifeng-jian", 1) < 350 )
                return notify_fail("你的剑法还未练成，不能使用「灭剑」绝技！\n");
        if (!objectp(weapon = me->query_temp("weapon")) 
			|| weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("你手里没有剑，无法使用「灭剑」绝技！\n");

        if(me->query_skill_mapped("parry") != "huifeng-jian")
                return notify_fail("你的招架功夫不对，无法使用「灭剑」绝技！\n");
        if(me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为不够，不能使用「灭剑」绝技！\n");
        if(me->query("neili") < 2000 )
                return notify_fail("你现在真气不足，不能使用「灭剑」绝技！\n");
        if(me->query("jingli") < 1500 )
                return notify_fail("你现在精力不足，不能使用「灭剑」绝技！\n");
        if(target->query_temp("em/mie"))
                return notify_fail("对方已经中了你的「灭剑」绝技！放手进攻吧。\n");
        if(me->query_skill("sword", 1) < 350 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用灭绝心法。\n");
		//if( !userp(me) )
              //  return notify_fail(me->query("name")+ "你一个npc用啥灭剑。\n");
        if( me->query_temp("em/mie") )
               return notify_fail(me->query("name") + "正在使用灭剑绝技。\n");
	
        msg = HBRED+YEL"$N飘身而起，使出回风拂柳剑「灭剑」绝技，顿时剑意空灵飘逸，似万千柳絮飞舞，又如和风阵阵拂过。\n"NOR;
        
        if(random(me->query("combat_exp"))>target->query("combat_exp")/3
			||random(me->query_int())>target->query_int()/2) {
                msg += HIG "结果$n大吃一惊，慌乱之下破绽迭出，被$N攻了个措手不及。\n" NOR;
                me->set_temp("em/mie",1);
				target->add_busy(2);
				if (me->query_skill("huifeng-jian",1)>350)
                  target->add_busy(1);
				if (me->query_skill("huifeng-jian",1)>450)
                  target->add_busy(1+random(2));
				if (me->query_skill("huifeng-jian",1)>550)
                  target->add_busy(1+random(2));
				if (me->query_skill("jiuyin-zhengong"))
				{
					//write("1111");
					msg += HBBLU+HIW "$N运起九阴真经上的内家功力，「灭剑」招式已无迹可寻,更见凌厉。\n"NOR;
					i+=me->query_skill("linji-zhuang",1)/3+me->query_skill("jiuyin-zhengong",1);
					target->apply_condition("no_exert",1+random(1));
					//i/=2;				
				}
				//对待明教弟子有额外杀伤
				if (target->query("family/family_name")=="明教"&&!userp(target))
				   i+=i/6;
				//洗脸后威力增加
				if (me->query("clas")=="bonze"&&me->query("gender")=="女性"&&me->query_per(1)>35)
				{
					i+=i/5;
				}
				if (!target->query_temp("em/mie"))
				{				
					target->add_temp("apply/attack", -i);
					target->add_temp("apply/parry", -i);
					target->add_temp("apply/dodge", -i);
					target->add_temp("apply/armor", -i);					
					target->set_temp("em/mie",i);
				}
                call_out("remove_effect", 1, target, i/100);
        }
        else {
                msg = msg + MAG "可是$n冷静非凡，丝毫不为这奇幻的招数所动，凝神抵挡，不漏半点破绽。\n" NOR;
				me->add_busy(1);
		}
        if (me->query_skill("huifeng-jian",1)<450)
        {
			me->start_perform(2+random(2),"「灭剑」绝技"); 
        }
		me->add("neili",-300);
		me->add("jingli",-200);

		me->delete_temp("em/mie");
		message_vision(msg, me, target);
        return 1;
}
void remove_effect(object target, int count)
{
        int i;
		if (!target) return;

		
	    i=target->query_temp("em/mie");
	 
		if (!target->query_temp("em/mie")) return;
		
        if (count<0)
		{
            tell_object(target, HIY"你逐渐恢复了身中「灭剑」绝技的正常状态。\n"NOR);
			//tell_object(me,target->query("name")+HIY"逐渐恢复了身中你所施展「灭剑」绝技的正常状态。\n"NOR);
            target->add_temp("apply/attack", i);
            target->add_temp("apply/dodge", i);
            target->add_temp("apply/parry", i);
			target->add_temp("apply/armor",i);

            target->delete_temp("em/mie");
			return;
        }
		call_out("remove_effect",1,target,count-3);
		return;
   
}

string perform_name(){ return HBRED+YEL"灭剑绝技"NOR; }

int help(object me)
{
        write(HBRED+HIY"\n回风拂柳剑之「灭剑绝技」："NOR"\n\n");
        write(@HELP
	回风拂柳剑乃是峨眉不传之秘，开山祖师郭襄因少年时期经历
	极为丰富，阅历非常深厚后来一生奇遇不断，结合家传武学，
	武功造诣极为深厚。后来因暗恋杨过不得，郁郁终生，四十岁
	后大彻大悟，出家为尼，开创峨眉武学--回风拂柳剑。
	传到峨嵋第三代掌门人灭绝师太手中，因各种原因，灭绝师太
	将回风拂柳剑发扬光大，更因师兄孤鸿子的不幸遭遇，使得灭
	绝师太独创了两门重要的绝技，灭剑和绝剑绝技。
	【灭剑绝技】凭借丰富战斗经验，可以有效压制对手，因灭绝
	师太不喜欢男子，对于忠诚于峨眉或熟读佛法的弟子有额外的
	赞许。若因缘巧合，习得峨眉绝学九阴真经速成篇，则本招威
	力更上一层楼,450级后大飞。注：清秀脱俗的女尼受灭绝师太
	格外青睐。
		
指令：perform sword.mie

要求：
	当前内力的需求 2000 以上；
	最大内力的需求 5000 以上；
	当前精力的需求 1500 以上；
	回风拂柳剑等级 350 以上；
	临济十二庄等级 350 以上；
	激发内功为临济十二庄；
	激发剑法为回风拂柳剑；
	激发招架为回风拂柳剑；
	手持剑类兵器。

HELP
        );
        return 1;
}



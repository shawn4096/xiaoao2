//cred by sohu@xojh 2013
#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me,object target)
{
        object weapon;
        string msg;
		int damage,p;
        int i = me->query_skill("huifeng-jian",1);
        weapon=me->query_temp("weapon");
        damage=i+me->query_skill("linji-zhuang",1);
		
        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「绝剑」绝技只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("你的内功不是峨嵋心法，无法使用「绝剑」绝技！\n");
        if( me->query_skill("linji-zhuang", 1) < 250 )
                return notify_fail("你的内功还未练成，不能使用「绝剑」绝技！\n");
        if( me->query_skill("huifeng-jian", 1) < 250 )
                return notify_fail("你的剑法还未练成，不能使用「绝剑」绝技！\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("你手里没有剑，无法使用「绝剑」绝技！\n");

        if(me->query_skill_mapped("parry") != "huifeng-jian")
                return notify_fail("你的招架功夫不对，无法使用「绝剑」绝技！\n");
        if(me->query("max_neili") < 2000 )
                return notify_fail("你的内力修为不够，不能使用「绝剑」绝技！\n");
        if(me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用「绝剑」绝技！\n");
        if(me->query("jingli") < 750 )
                return notify_fail("你现在精力不足，不能使用「绝剑」绝技！\n");
        if(me->query_temp("em/jue"))
                return notify_fail("你正在使用「绝剑」绝技！\n");
        if(me->query_skill("sword", 1) < 250 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用「绝剑」绝技。\n");

       

        msg = HIW "$N神情肃然，默念佛号，使出峨嵋"+RED"「绝剑」绝技"+HIW"，顿时$N手中的"+weapon->query("name")+HIW"腾起一股萧杀的意境。\n"NOR;
        me->set_temp("em/jue", 1);
        if(random(me->query_skill("dodge",1))>target->query_skill("dodge",1)/2
		||random(me->query_int(1))>target->query_int(1)/2
        ||random(me->query("combat_exp"))>target->query("combat_exp")/2) {
            			
            me->add_temp("apply/attack", i/2);
            me->add_temp("apply/damage",  i/4);
            me->add_temp("apply/sword",  i/2);
			if (target->query_temp("em/mie"))
            {
				msg = msg + CYN"$n只觉$N灭剑、绝剑配合异常绝妙，招式绵绵密密，不由压力大增。\n"NOR;
				damage+=damage*4;
            }
			if (me->query_skill("jiuyin-zhengong"))
			{
				msg = msg + BLU"$N将九阴真气附加在手持的剑上，威力倍增。\n"NOR;
				damage += damage/2;
			}
			if (target->query("family/family_name")=="明教"&&!userp(target))
			{
				damage+=damage/6;
			}
			//削弱npc威力
			if (!userp(me)&&me->is_fighting()&&damage>4000)
               damage=4000+random(damage-4000)/10;
			msg = msg + HIR "结果$n一不小心被$N一剑刺中，鲜血飞溅。\n" NOR;	
			//调整jue击穿的bug
			//if (damage>target->query("qi")) damage=target->query("qi")-10;
			
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/4,me);
            p = (int)target->query("qi")*100/(int)target->query("max_qi");
		    msg += COMBAT_D->damage_msg(damage, "瘀伤");
		    msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";		    
			message_vision(msg, me,target);
            if (objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/attack", -i/2);
            me->add_temp("apply/damage", -i/4);
            me->add_temp("apply/sword",  -i/2);
			           
			//if (objectp(target)&&object->is_fighting())
			if (me->query_skill("huifeng-jian",1)>350 && me->query("em/jue/pass") && objectp(target) && me->is_fighting(target))
				call_out("next1", 0, me, target, i);			
		
        }
        else
           {
			msg = msg + MAG "可是$n冷静非凡，凝神抵挡，躲开了这必杀的一击,但却吓得一身冷汗。\n" NOR;
            me->add_busy(1+random(1));	
            message_vision(msg, me,target);
		   }            
		    me->start_perform(1+random(3),"「绝剑」绝技"); 
        me->delete_temp("em/jue");
        return 1;
}

int next1(object me, object target, int i)
{
        string msg;
        int damage;
        object weapon;
        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
               // me->add_temp("apply/attack", -i/2);
               // me->add_temp("apply/damage",  -i/4);
               // me->add_temp("apply/sword",  -i/2);
                me->delete_temp("em/jue");
                return 0;
        }

        message_vision(HBRED+YEL "$N深吸一口气，运起峨嵋临济十二庄,配合「灭剑」心法,使出「绝剑」绝技！\n"NOR,me);
        me->add_temp("apply/attack", i/2);
        me->add_temp("apply/damage", i/4);
        me->add_temp("apply/sword",  i/2);
       // message_vision(msg, me, target);
        if((random(me->query("max_neili")) + me->query_int()*me->query_skill("force",1)/2) >(target->query("max_neili") + target->query_int()*target->query_skill("force",1)/2)/4 )
		{
                message_vision(HIW"$N灭剑、绝剑配合异常绝妙，回风拂柳剑威力大增,唰唰连发数招。\n"NOR,me);
                damage = me->query_skill("huifeng-jian",1);
                damage += me->query_skill("sword",1);
                damage += random(damage);

                target->add("neili",-(500+random(150)));
				target->receive_damage("qi",damage,me);
			    target->receive_wound("qi",damage/2,me);
                target->add_condition("no_exert",1+random(2));    // 灭剑、绝剑配合异常绝妙，不由压力大增
                target->add_condition("no_perform",1+random(2)); //中了第2个绝，才会有这效果。
               
                //COMBAT_D->report_status(target, random(2));
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                me->add("neili",-300);
                me->add("jingli",-100);
        } else {
                
                message_vision( CYN"$n临危不乱，脚下步法连变，闪躲开来。\n"NOR,me,target);
                me->add_busy(1+random(2));
        }
        me->add_temp("apply/attack", -i/2);
        me->add_temp("apply/damage", -i/4);
        me->add_temp("apply/sword",  -i/2);
        me->delete_temp("em/jue");        
        return 1;
}
string perform_name(){ return HBRED+HIW"绝剑绝技"NOR; }

int help(object me)
{
        write(WHT"\n回风拂柳剑之「绝剑」绝技："NOR"\n\n");
        write(@HELP
	回风拂柳剑乃是峨眉不传之秘，开山祖师郭襄因少年时期经历
	极为丰富，阅历非常深厚后来一生奇遇不断，结合家传武学，
	武功造诣极为深厚。后来因暗恋杨过不得，郁郁终生，四十岁
	后大彻大悟，出家为尼，开创峨眉武学--回风拂柳剑。
	传到峨嵋第三代掌门人灭绝师太手中，因各种原因，灭绝师太
	将回风拂柳剑发扬光大，更因师兄孤鸿子的不幸遭遇，使得灭
	绝师太独创了两门重要的绝技，灭剑和绝剑绝技。
	绝剑绝技凭借其丰富的战斗经验，和悟性以及身法优势，可以
	有效杀伤对手，因灭绝师太不喜欢男子，对于忠诚于峨眉或熟
	读佛法的弟子有额外的赞许。若因缘巧合，习得峨眉绝学九阴
	真经速成篇，则本招威力更上一层楼，350级小飞，450级后大
	飞。
	
	指令：perform sword.jue

要求：
	当前内力的需求 1000 以上；
	最大内力的需求 2000 以上；
	当前精力的需求 750 以上；
	回风拂柳剑等级 250 以上；
	临济十二庄等级 250 以上；
	激发内功为临济十二庄；
	激发剑法为回风拂柳剑；
	激发招架为回风拂柳剑；
	手持兵器。

HELP
        );
        return 1;
}



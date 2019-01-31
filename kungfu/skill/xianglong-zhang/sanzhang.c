//sanzhang.c 亢龙连环三掌，模仿萧峰 create by sohu@xojh


#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int ap,dp,damage;
        int i = me->query_skill("xianglong-zhang",1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「亢龙连环三掌」只能对战斗中的对手使用。\n");
        //非解密不得开
        if(me->query("xlz/sanzhao")!="pass")
                return notify_fail("你虽然听说过「亢龙连环三掌」，但是一直没有领悟其中诀窍，还不会运用！\n");

        if( me->query_skill("xianglong-zhang", 1) < 500 )
                return notify_fail("你的降龙掌还未练成，不能使用「亢龙连环三掌」！\n");

        if( me->query_skill("strike", 1) < 500 )
                return notify_fail("你的基本掌法还未练成，不能使用「亢龙连环三掌」！\n");

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("你手里有兵器，无法使用亢龙连环三掌！\n");
   
        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你现在无法使用「亢龙连环三掌」进行攻击。\n");  

        if(me->query_skill_mapped("parry") != "xianglong-zhang")
                return notify_fail("你的招架功夫不对，无法使用「亢龙连环三掌」！\n");
        if(me->query_str(1) < 80 )
                return notify_fail("你的有效臂力不够，不能使用「亢龙连环三掌」！\n");
        if(me->query("max_neili") < 10000 )
                return notify_fail("你的内力修为不够，不能使用「亢龙连环三掌」！\n");
        if(me->query("neili") < 2500 )
                return notify_fail("你现在真气不足，不能使用「亢龙连环三掌」！\n");
        if(me->query("jingli") <2500 )
                return notify_fail("你现在精力不足，不能使用「亢龙连环三掌」！\n");
         if(me->query_temp("xlz/sanzhang"))
                return notify_fail("你正在使用「亢龙连环三掌」！\n");
         damage=me->query_skill("xianglong-zhang",1)+me->query_skill("strike",1)+me->query_skill("force",1)+me->query_skill("huntian-qigong",1);
		 damage=damage*me->query_str()/10+random(damage);
         if ( damage > 6000 )
				damage = 6000 + (damage - 6000)/10;
		 me->set_temp("xlz/sanzhang1",damage);
         msg = HBRED+HIY"\n$N心中愤怒，当即大步迈出，左手一划，右手呼的一掌，便向$n击去，正是降龙十八掌的一招“亢龙有悔”!\n"+
			 "$N出掌之时，与$n相距尚有十五六丈，但说到便到，力自掌生之际，两人相距已不过七八丈。\n"NOR;
         

         //me->start_perform(2, "「亢龙连环三掌」");
         me->add_temp("apply/attack", me->query_skill("xianglong-zhang") /2);

		 me->add_temp("apply/damage", me->query_skill("xianglong-zhang") /4);
         me->set_temp("xlz/sanzhang", i);
         me->set_temp("xlz/hanglong",1);    
		 if (random(me->query_str(1)) > target->query_str(1)/3 
			 ||random(me->query("combat_exp")) > target->query("combat_exp")/3 
			 )
           {
			  msg+= HIC "\n$n只道天下武术之中，任你掌力再强，也决无一掌可击到五丈以外的。尽管$n素闻$N的大名，对$N决无半点小觑之心。\n"NOR;
			  msg+=HIW"然见$N在十五六丈之外出掌，万料不到此掌是针对自己而发,一时不察，顿觉手忙脚乱起来。\n"NOR;
			  target->receive_damage("qi", damage,me);
			  target->receive_wound("qi", damage/4,me);
			  if (!target->is_busy()) target->start_busy(1+random(2));
			  else target->add_busy(1+random(2));
			  msg += HBRED"\n$n为$N这招亢龙有悔劲力所笼罩，躲无可避，被逼无奈只得抬掌迎了上来这一掌。\n"NOR;
			  target->apply_condition("no_perform",1+random(2));
			
		  }else msg +=RED"\n$n周身内功随心而起，运功将$N的这一招厉害的招式抵消，心中暗凛，‘降龙十八掌’果然名不虚传。\n"NOR;
        message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/attack", -me->query_skill("xianglong-zhang") /2);
		
		me->add_temp("apply/damage", -me->query_skill("xianglong-zhang") /4);

        me->add("neili", -800);

        if (objectp(target)&& me->query_skill("xianglong-zhang", 1) > 450)
                next1(me, target, i);
        else {
                me->delete_temp("xlz/sanzhang");
				me->delete_temp("xlz/hanglong");
		}
        return 1; 
}

int next1(object me, object target, int i)
{
        string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("xlz/sanzhang");
                return 0;
        }
        msg = HBRED"\n殊不料$N一掌既出，身子已抢到离$n三四丈外，又是一招“亢龙有悔”，后掌推前掌，双掌力道并在一起，排山倒海的向$n压将过来。\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/1000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/1000;
	    msg += HIR"\n只一瞬之间，$n便觉气息窒滞，对方掌力竟如怒潮狂涌，势不可当，犹如是一堵无形的高墙，向自己身前疾冲而来。\n"NOR;
		me->set_temp("xlz/hanglong",1); 
		if((userp(target)&& random(ap + dp) > dp/2 )|| !userp(target)){
                msg += HIR"\n$n大惊之下，哪里还有余裕筹思对策，但知若是单掌出迎，势必臂断腕折，说不定全身筋骨尽碎，\n"NOR;
				//msg += HIR"$n百忙中双掌连划三个半圆护住身前，同时足尖着力，飘身后退。\n"NOR;
                damage = me->query_skill("xianglong-zhang",1)*3;

				damage += me->query_skill("strike")*3;
				
				damage += me->query_temp("xlz/sanzhang1");
                me->delete_temp("xlz/sanzhang1");
				me->set_temp("xlz/sanzhang2",damage);

		        if(damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                if (target->query("neili")>3500)
                    target->add("neili",-3500);
				else target->set("neili",10);
				//打空对方内力
                target->receive_damage("qi", damage, me);
                if(userp(me) && me->query("env/damage"))
        	       tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
        if(userp(target)&& target->query("env/damage"))
			       tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
        target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "内伤");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("xianglong-zhang") /2);

		me->add_temp("apply/damage", me->query_skill("xianglong-zhang") /4);

        //if(random(3))
			target->add_condition("no_exert", 1+random(2));
        if(random(3))
			target->add_condition("no_force", 1);
        if(!userp(target))    target->add_busy(2+random(2));
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("xianglong-zhang") /2);

		me->add_temp("apply/damage", -me->query_skill("xianglong-zhang") /4);

                me->add("neili",-800);
                me->add("jingli",-80);
                me->start_perform(3, "「亢龙连环三掌」");
        }
        else {
                msg += HIC"\n$n百忙中双掌连划三个半圆护住身前，同时足尖着力，飘身后退。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                //me->add_busy(random(1));
        }
		//me->start_perform(1, "「亢龙连环三掌」");
        if (objectp(target)&&me->query_skill("xianglong-zhang", 1) > 500)
                next2(me, target, i);
        else {
                me->delete_temp("xlz/sanzhang");
		        me->delete_temp("xlz/hanglong"); 
		}
        return 1; 
}

int next2(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("tz/sanzhang");
                return 0;
        }
        msg = HBMAG"\n就在$n疲于防守之际，$N跟着又是一招“亢龙有悔”，前招掌力未消，次招掌力又到！\n"
		      +HIY"$n不敢正面直撄其锋，右掌斜斜挥出，与$N掌力的偏势一触，但觉右臂酸麻，胸中气息登时沉浊。\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_str(1);
       if((userp(target)&& random(ap + dp) > dp/2 )|| !userp(target)){

                    damage = me->query_skill("xianglong-zhang",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += me->query_temp("xlz/sanzhang2");
					me->delete_temp("xlz/sanzhang2");

                if ( damage > 8000 )
					damage = 8000 + (damage -8000)/10;
				if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
                target->set_temp("xlz/sanzhang",me->query_skill("xianglong-zhang",1));
                target->add_temp("apply/attack", -me->query_skill("xianglong-zhang",1));
                target->add_temp("apply/dodge",  -me->query_skill("xianglong-zhang",1));
                target->add_temp("apply/parry", -me->query_skill("xianglong-zhang",1));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/4, me);
                msg += damage_msg(damage, "瘀伤");

                message_vision(msg, me, target);
        if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("xianglong-zhang") /2);

		me->add_temp("apply/damage", me->query_skill("xianglong-zhang") /4);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("xianglong-zhang") /2);

	    me->add_temp("apply/damage", -me->query_skill("xianglong-zhang") /4);
                me->add("neili",- 1000);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"「亢龙连环三掌」");
                call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$n当即乘势纵出三丈之外，唯恐敌人又再追击，竖掌当胸，暗暗凝气与掌上。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("tz/tiezhang");
		me->start_perform(5, "「亢龙连环三掌」");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", target->query_temp("xlz/sanzhang"));
        target->add_temp("apply/dodge", target->query_temp("xlz/sanzhang"));
        target->add_temp("apply/parry", target->query_temp("xlz/sanzhang"));
}

string perform_name(){ return HBRED+HIY"亢龙连环三掌"NOR; }
int help(object me)
{
        write(HBRED+HIY"\n降龙十八掌法之「亢龙连环三掌」："NOR"\n\n");
        write(@HELP 
	降龙十八掌乃是武林第一大帮丐帮的镇派两大绝技之一，讲究刚柔并济，当刚则刚，
	当柔则柔，轻重刚柔随心所欲，刚劲柔劲混而为一，劲力忽强忽弱，忽吞忽吐，从
	至刚之中生出至柔，天下阳刚第一，掌法之妙，天下无双，招招须用真力，说是外
	门武学中的巅峰绝诣，动作虽似简单无奇，但掌掌现神龙，招招威力无穷，招式简
	明而劲力精深的武功，精要之处，全在运劲发力，全凭劲强力猛取胜，当真是无坚
	不摧、无固不破，虽招数有限，但每出一掌均有龙吟虎啸之势、每出一招均具绝大
	的威力。
	降龙十八掌必须得到帮主的传授方可习得，而「亢龙三招」乃是降龙掌最终绝技之
	一，非深厚内力不得施展，需向萧峰请教方可习得。
	
	指令：perform strike.sanzhang

要求：	
	最大内力 10000 以上；
	当前内力 2500 以上；
	当前精力 2500 以上；
	降龙掌等级 500 以上；
	基本掌法需 500 以上；
	有效膂力 80 以上：
	激发掌法降龙掌；
	激发内功为混天气功；
	激发招架为降龙掌。
HELP
        );
        return 1;
}

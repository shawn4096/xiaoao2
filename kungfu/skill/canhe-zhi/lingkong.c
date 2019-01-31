// pfm canhe by sohu@xojh 2013

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int ap,dp;
        int i = me->query_skill("canhe-zhi",1) + me->query_skill("finger",1) /3 ;
        if (me->query("shenyuan/super"))
         i += me->query_skill("shenyuan-gong",1) /2;
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「凌空虚点」只能对战斗中的对手使用。\n");


        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你的内功不是神元功，无法使用「凌空虚点」！\n");


        if(!me->query("quest/mr/canhezhi/pass"))
                return notify_fail("你虽然听说过「凌空虚点」绝技，但是一直没有领悟其中诀窍，还不会运用！\n");

        if( me->query_skill("shenyuan-gong", 1) < 500 )
                return notify_fail("你的内功还未练成，不能使用「凌空虚点」！\n");

        if( me->query_skill("canhe-zhi", 1) < 500 )
                return notify_fail("你的指法还未练成，不能使用「凌空虚点」！\n");

        if( me->query_temp("weapon"))
                        return notify_fail("你手里拿着兵器，无法使用「凌空虚点」！\n");
   
        if (me->query_skill_prepared("finger") != "canhe-zhi"

			|| me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("你现在无法使用「凌空虚点」进行攻击。\n");  


        if(me->query("max_neili") < 9000 )
                return notify_fail("你的内力修为不够，不能使用「凌空虚点」！\n");
        if(me->query("neili") < 3000 )
                return notify_fail("你现在真气不足，不能使用「凌空虚点」！\n");
        if(me->query("jingli") < 2000 )
                return notify_fail("你现在精力不足，不能使用「凌空虚点」！\n");
        if(me->query_temp("chz/ch"))
                return notify_fail("你正在使用「凌空虚点」！\n");

        if(me->query_skill("finger", 1) < 500 )
                return notify_fail("你的基本指法不够娴熟，不能使用「凌空虚点」。\n");


        msg = HIY"\n$N突地拔地而起，凌空虚点三下，指风向$n激射而去，自上而下，挥洒自如!\n"NOR;
        msg += HIM"$N将自己从慕容博处领悟的参合指绝技的威力尽数发挥出来，第一指"+HIR"「参商两相隔」"+HIM",可谓当之披靡。\n"NOR;
        message_vision(msg, me, target);
        me->start_perform(3, "「凌空虚点」");

        me->set_temp("chz/ch", 1); //这个标记是为了触发参合指的auto
        me->add_temp("apply/attack", i );
        me->add_temp("apply/damage", i /3);  
		me->add_temp("apply/finger", i /3);  
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        me->add_temp("apply/attack", -i );
        me->add_temp("apply/damage", -i /3);
		 me->add_temp("apply/finger", -i /3);
        me->add("neili", -150);
        if (me->query_skill("shenyuan-gong", 1) > 350)
                next1(me, target, i);
        else 
                me->delete_temp("chz/ch");
        return 1;
}

int next1(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon,tweapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
		tweapon=target->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("chz/ch");
                return 0;
        }
        msg = HIC"\n$N继而冷笑一声，喝道：“第二指"HIM"「斗转带星移」"HIC"小心了！”凌空又出一指，\n"+
        "$n硬接下第一式已是力有不逮，这第二招如何也不敢硬碰,登时手忙脚乱，疲于招架，毫无还手之力!\n"NOR;

        message_vision(msg, me, target);
        
        ap = me->query("combat_exp") * me->query_str(1)/100000;
        dp = target->query("combat_exp") * target->query_dex(1)/100000;
       /* if (tweapon && random(me->query_skill("finger",1))>target->query_skill("parry",1)/3)
        {			
				message_vision(HIG"$N悠然一笑,食指灵动，一股劲气陡然而至，$n一个把持不住，手腕一麻。\n"+
					"手中的"+tweapon->query("name")+HIG"掉落在地。\n"NOR,me,target);
				tweapon->move(environment(me));
				target->add_busy(1+random(1));			
        }*/
        if (ap>dp/3 ||  random(me->query_int()) > target->query_int()/3){
                   message_vision(HIB"$n一个不防，为$N施展出的斗转星移劲力反击，登时受制。\n"NOR,me,target);
				   target->apply_condition("no_perform", 1+ random(2));
                   target->apply_condition("no_exert", 1+ random(2));
                   me->set("chz/ch",1);
                   me->add_temp("apply/attack", me->query_skill("shenyuan-gong")/2 );
                   me->add_temp("apply/damage", me->query_skill("shenyuan-gong")/4 );
                   target->add_temp("apply/attack", -80);
                   target->add_temp("apply/dodge", -80);
                   target->add_temp("apply/parry", -80);
               
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        if (me->is_fighting(target))
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        if (me->is_fighting(target))
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                  
            me->add_temp("apply/attack", -me->query_skill("shenyuan-gong")/2 );
            me->add_temp("apply/damage", -me->query_skill("shenyuan-gong") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"「凌空虚点」");
                //target->delete_temp("must_be_hit",1);
            call_out("back", 5 + random(me->query("jiali") / 20), target);               
        } 
        else {
                msg = msg + HIW "$n一个燕子翻身，弯腰向后方才堪堪避过。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
       if (me->query_skill("canhe-zhi", 1) > 450)
                next2(me, target, i);
        //me->delete_temp("chz/ch");
        return 1;
}

int next2(object me, object target, int i)

{
        string msg;
        int damage, ap,dp;
        object weapon,weapon1;

        if (!me) return 0;
        if(!target) return 0;
        weapon = me->query_temp("weapon");
        weapon1 = target->query_temp("weapon");

        if (weapon || !living(me) || !me->is_fighting(target))
         {
                me->delete_temp("chz/ch");
                return 0;
         }

         msg = HIB"\n紧跟着$N又一指隔空点出，正是一招"HIR"「剑气碧烟横」"HIB"指风如锥，连绵而至！\n"+
         "$n神情恍惚之下，但觉指风犀利，似乎有些神不守舍。\n"NOR;
        ap =me->query_skill("canhe-zhi",1);
        dp =target->query_skill("parry",1);
//这里除100000是为了防止exp数值过大的时候出现大数溢出


        if( random(ap)  > dp/2 ||  me->query("int",1) > 40)
        {
             if(weapon1) msg += HIG"$n只得将兵器横在当中一挡，却哪里抵挡得住？"HIW+weapon1->name()+HIG"当下被震飞，“啪”地一声插入地下。\n"NOR;
        
                damage =  me->query_skill("canhe-zhi",1)*3;
                damage += me->query_skill("finger")* 3;
                damage += random(damage);
             if ( damage > 8000 )
                        damage = 8000 + (damage - 8000)/10;

//绝对不能打爆。打爆了后面就出错了
             if ( damage >= target->query("qi",1) ) 
                        damage = target->query("qi",1) -1;
           	        
             if(weapon1) {      weapon1->unequip();
			                      weapon1->move(environment(target));
                     }
                target->start_busy(3);
                target->add("neili",-(300+random(150)));
                target->apply_condition("no_exert", 1+ random(2));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
//这句多余啦    msg += damage_msg(damage, "内伤");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));
            if(target){
                me->add_temp("apply/attack", me->query_skill("canhe-zhi") );
                me->add_temp("apply/damage", me->query_skill("canhe-zhi")  );
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

                me->add_temp("apply/attack", -me->query_skill("canhe-zhi") );
                me->add_temp("apply/damage", -me->query_skill("canhe-zhi") );
              }      
                me->add("neili",-200);
                me->add("jingli",-80);
              //target->delete_temp("must_be_hit",1);
        } 
        else {
                msg  += CYN"\n$n就地十八滚，危急之中躲过致命一击，狼狈之极。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                target->add_busy(random(2));
                
                me->add_temp("apply/attack", me->query_skill("canhe-zhi") /2);
                me->add_temp("apply/damage", me->query_skill("canhe-zhi") /2 );

                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                me->add_temp("apply/attack", -me->query_skill("canhe-zhi") /2);
                me->add_temp("apply/damage", -me->query_skill("canhe-zhi") /2);
                               
         }

                me->delete_temp("chz/ch");
//猛招就要CD长。嘿嘿哈哈
                me->start_perform(5, "「凌空虚点」");
}

void back(object target)
{
        object me = this_player();
        if (!target) return;
        target->add_temp("apply/attack", 80);
        target->add_temp("apply/dodge", 80);
        target->add_temp("apply/parry", 80);
        me->delete_temp("chz/ch");
}

string perform_name(){ return HIR"「凌空虚点」"NOR; }
int help(object me)
{
        write(HIG"\n参合指之"HIR"「凌空虚点」"NOR"\n\n");
        write(@HELP
	参合指乃是慕容不传之秘，当初慕容复为段誉的六脉神剑所败
	心灰意冷，后来已经出家的慕容博当场演示这参合指的凌空三
	击打，震慑当场。此招是参合指的终极绝学。需向慕容博请教

	perform finger.lingkong

要求：
	当前内力需要 3000 以上；
	最大内力需要 9000 以上；
	当前精力需要 2000 以上；
	参合指法等级 500  以上；
	神元功的等级 500  以上；
	基本指法等级 500  以上；
	激发指法且备为参合指；
	激发内功为神元功。
HELP
        );
        return 1;
}



#include <ansi.h>
#include <combat.h>
inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, club, i,ap,pp;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「超度极乐」只能对战斗中的对手使用。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "club" )
                return notify_fail("你手中无棍，怎能运用「超度极乐」？！\n");

/*
        if( me->query_temp("sl_chaodu") )
               return notify_fail("「超度极乐」是少林密技，太过刚猛有违天和，不可多用！\n");
*/
        if(me->query("menggu"))
                return notify_fail("你这种佛门败类，如何能够运用佛门神功。\n");

        if(me->query_temp("sl_leidong"))
               return notify_fail("你正在使用韦陀杵的「雷动九天」，全身内力已经灌注到手中兵器中，无暇他顾了。\n");

        if((int)me->query_skill("weituo-chu", 1) < 300 )
               return notify_fail("你「韦陀杵」修为还不够，还未能领悟「超度极乐」！\n");

        if((int)me->query_str()-(int)me->query_temp("apply/strength")<50)
               return notify_fail("你的膂力不够，无法用出「超度极乐」\n");

        if((int)me->query("con")+(int)me->query_skill("force",1)/10<50)
               return notify_fail("你的根骨不够，无法承受「超度极乐」的金刚大力。\n");

        if((int)me->query_skill("buddhism",1) < 150)
               return notify_fail("你禅宗修为还不够，还未能领悟「超度极乐」！\n");

        if((int)me->query_skill("jingang-quan",1) < 300)
               return notify_fail("「超度极乐」是以金刚大力发出，无坚不摧，你金刚拳修为尚浅吧?\n");

        if( me->query_skill("yijin-jing", 1) < 300 )
                return notify_fail("你的内功修为火候未到，施展只会伤及自身！\n");

        if( me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("你所用的内功与「超度极乐」心法相悖！\n");

        if (me->query_skill_mapped("club") != "weituo-chu"
         || me->query_skill_mapped("parry") != "weituo-chu")
                return notify_fail("你现在无法使用「超度极乐」进行攻击。\n");

        if( me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为不足，劲力不足以施展「超度极乐」！\n");

        if( me->query("neili") <= 2000 )
                return notify_fail("你的内力不够，劲力不足以施展「超度极乐」！\n");

        if( me->query("jingli") <= 1500 )
                return notify_fail("你的精力有限，不足以施展「超度极乐」！\n");

        message_vision(HIR"\n突然$N面露佛光：「超度极乐」，身形暴涨，如同韦陀尊者再世一般，右拳突出击在"+weapon->name()+HIR"当中，"+weapon->name()+HIR"被打的象流星一样飞向$n！\n" NOR, me,target);
       
/*
        weapon->move(environment(me));
        weapon->set("name", weapon->query("name")+"的碎片");
        weapon->unequip();
        weapon->set("value", 0);
        weapon->set("weapon_prop", 0);
*/
        damage = (int)me->query_skill("club") + (int)me->query_skill("buddhism",1);
        club = me->query_skill("club")/3;
        i = 10+random(me->query_skill("buddhism",1)/20);
        damage = damage*i;
        if(me->is_killer(target->query("id")))
                damage = damage *2/3;
        if(!target->is_killer(me->query("id")))
                damage = damage *2/3;
        if (wizardp(me))
                write(sprintf("damage = %d\n",damage));
        ap = COMBAT_D->skill_power(me,"club",SKILL_USAGE_ATTACK);
        pp = COMBAT_D->skill_power(target,"parry",SKILL_USAGE_DEFENSE);
        if(target->is_busy())
                pp /= 2;
        if(me->query("real_yjj"))
                {
                        damage *=2;
                        ap *= 2;
                        pp /= 2;
                }
//      me->set_temp("sl_chaodu",1);
        if(random(ap+pp)>pp)
        {
                me->add("neili", -1000);
                me->add("jingli", -800);
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2,me);
                message_vision(HIY"\n$n哪里见过这么刚猛霸道的招式,招架不及，被"+weapon->name()+HIY"击中，肋骨当即根根断裂！\n" NOR, me,target);
if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR); 
if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR); ;
                COMBAT_D->report_status(target);
                target->start_busy(2+random(1));
				target->set_temp("faint_by",me);//增加一个标记，避免莫名其妙死亡 by renlai
                
      //        call_out("remove_effect2", club*/3, me);
       }
       else {
                message_vision(HIY"\n$n眼见$N来势凶狠，不及招架，身体贴地滑行，倒滑出数丈，躲过了这致命一击！\n" NOR, me,target);
                me->add("neili", -1500);
                me->add("jingli", -800);
                
       //       call_out("remove_effect2", club*/3, me);
       }
    message_vision(HIY"\n$N飞身而起，反手将"+weapon->name()+HIY"抄到手中，顺势又挥出两棒！\n" NOR, me,target);
        if(!userp(me)) club = club / 2;
        me->add_temp("apply/attack", club);
        me->add_temp("apply/damage", club);

if(me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
if(me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/attack", -club);
        me->add_temp("apply/damage", -club);
                me->start_perform(4+random(2),"「超度极乐」");

       return 1;
}

/*
void remove_effect2(object me)
{
        if (!me) return;
        me->delete_temp("sl_chaodu");
        tell_object(me, HIG"\n你经过一段时间修心养性，又可以再使用「超度极乐」了。\n"NOR);
}
*/
 string perform_name(){ return HIY"超度极乐"NOR; }
int help(object me)
{
        write(
@HELP
超度极乐
       是佛门神功－－「韦陀杵」的特殊攻击，将手中兵器击出飞向对手。
       乃是「韦陀杵」的终极招式。
       需要韦驮杵350级
           易筋经350级
           配合大金刚拳使用
HELP
        );
        return 1;
}


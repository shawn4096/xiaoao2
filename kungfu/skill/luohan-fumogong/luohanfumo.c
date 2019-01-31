// By kingso

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

string exert_name() { return HBMAG HIY"罗汉伏魔"NOR; }

int exert(object me,object target)
{
     //  string msg;
       int i;
       if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
               return notify_fail("「罗汉伏魔」只能在战斗中使用。\n");

       
       if( (int)me->query_skill("luohan-fumogong",1) < 350 )
                return notify_fail("你的罗汉伏魔功还不够火候，使不出罗汉伏魔。\n");  
       if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("你的基本内功还不够火候，使不出罗汉伏魔。\n");  
       
       if( (int)me->query("jingli", 1) < 1500 )
                return notify_fail("你现在精力不够。\n");
       if( (int)me->query("neili", 1) < 2000 )
                return notify_fail("你现在内力不够。\n");
       if (me->query_temp("luohan/sp_fast"))
                return notify_fail("你正在使用罗汉伏魔。\n");

       //msg = 
           message_vision( HBMAG HIY "只见$N周身突然金芒紫气暴涨，大喝：“"HIG"罗汉伏魔！"HIY"周围顿时感觉到逼人的劲气迎面扑来，$n顿感自己被压制在一个无形的气场之中，连呼吸都困难！\n"NOR, me, target);


       me->add("neili", -(700+random(300)));
       me->add("jingli", -(100+random(50)));
       me->add("max_neili", - random(30));
    //   message_vision(msg, me);
       i = me->query_skill("force", 1)/10 + me->query_skill("luohan-fumogong",1)/20 + me->query_skill("dodge")/10;
       me->add_temp("apply/dexerity", -i/2);
       me->add_temp("apply/parry", -i/2);
    //   me->add_temp("apply/strength", i/2);
       me->add_temp("apply/damage", i);
       me->set_temp("luohan/sp_fast", i);
       me->set_temp("double_attack", 1);
        if( me->is_fighting(target) && (int)me->query_skill("luohan-fumogong",1) > 199 ) {
        me->add_temp("apply/attack", i*20);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       if( me->query("env/罗汉伏魔") == "伏魔" ){ 
       target->add_condition("luohan_hurt", random(i/2)); }
        me->add_temp("apply/attack", -i*20);
        }  
       if (me->query_skill("luohan-fumogong",1) < 300) me->start_exert(1, "罗汉伏魔");
       call_out("remove_effect", 1, me, i, i);
       return 1;
}
void remove_effect(object me, int count, int dex)
{
        if (!me) return;
        if( me->query_skill_mapped("force") != "luohan-fumogong" 
         || (!me->is_fighting() )
         || me->query("neili") < 100
         || count < 1){
                me->add("neili", - (25 + random(25)));
                me->add_temp("apply/dexerity", dex/2);
                me->add_temp("apply/parry", dex/2);
                me->add_temp("apply/damage", - dex);
              //  me->add_temp("apply/strength", -dex/2);
                me->delete_temp("luohan/sp_fast");
                me->delete_temp("double_attack");
                message_vision(HBMAG HIW"$N内力不济，真元损耗，罗汉伏魔诀渐渐收功。\n"NOR, me);
                return;
        }
        call_out("remove_effect", 1 , me, count -1, dex);
}

int help(object me)
{
        write(HIG"\n「罗汉伏魔」："NOR"\n");
        write(@HELP

        罗汉伏魔神功之罗汉伏魔诀，由于此招威力甚大，
        能够在战斗中提升自我的战力，同时以迅捷之势
        攻击对方，所以在使用时也会消耗一定的真元。        

        要求：  罗汉伏魔功等级 350 以上；
                基本内功等级 350 以上；
                set 罗汉伏魔 伏魔
                可在攻击型武功中增加伏魔内伤效果；
                每此使用消耗最大内力随机30点；
                
                
HELP
        );
        return 1;
}


// qianzhu.c 千蛛万毒
// by Lsxk@HSBBS

#include <ansi.h>

inherit F_SSERVER;

int perform_jigong(object,object);
int perform_normal(object,object);

string perform_name(){ return HIR"千"HIG"蛛"HIW"万"HIB"毒"NOR;}

int perform(object me, object target)
{
        string msg;

        if( !target ) target = offensive_target(me);
        
        if( !objectp(target) || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail("「千蛛万毒」绝招只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("qianzhu-wandushou", 1) < 150 )
                return notify_fail("你的千蛛万毒手功力还远远不够，无法使用「千蛛万毒」绝招！\n");

        if( me->query_temp("weapon") )
                return notify_fail("你必须空手才能使用「千蛛万毒」！\n");

        if (me->query_skill_prepared("hand") != "qianzhu-wandushou" )
            //|| me->query_skill_mapped("parry") != "qianzhu-wandushou")
                return notify_fail("你必须先将千蛛万毒手运用于手法之中才行。\n");

        if( (int)me->query("max_neili") < 2000 )
                return notify_fail("你的内力修为不足，使不出「千蛛万毒」绝招！\n");     

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的内力不足，使不出「千蛛万毒」绝招！\n");     

        if( (int)me->query_skill("hand", 1) < 150 )
                return notify_fail("你的手法不够娴熟，使不出「千蛛万毒」绝招！\n");

        if( me->query("env/千蛛万毒")=="疾攻"){
             perform_jigong(me,target);
        }
        else{
             msg= HIB "\n$N暗运千蛛万毒于双手，脸上蓝气时隐时现！\n"NOR;
             message_vision(msg, me, target); 
             perform_normal(me,target);
        }
    return 1;
}

int perform_jigong(object me,object target)
{
    int i,j,k;
    string msg;
    if( !target ) target = offensive_target(me);
    i = (int)me->query("per",1)/10;
    i = 4 - i; //越丑威力越大
    j = (int)me->query_skill("qianzhu-wandushou", 1)+(int)me->query_skill("poison", 1);
    k = (int)me->query_skill("hand", 1)/2;
    if (i>3) i=3;
    else if (i<1) i=1;
    if (wizardp(me))
        write("i is "+i+".\n");
    me->set_temp("qzwd_pfm", 1);
    me->add_temp("apply/attack", j+k);
    me->add_temp("apply/hand", k);
	me->add_temp("apply/damage", k/2);
    msg= HIR "\n$N暗运千蛛万毒功，将体内积蓄剧毒逼于双手处，喝道：“小心了！”，便是如急风暴雨般地攻向$n！\n"NOR;
    message_vision(msg, me, target);
    me->start_perform(4, "「千蛛万毒」");
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
    me->add_temp("apply/attack", -j-k);
    me->add_temp("apply/hand", -k);
	me->add_temp("apply/damage", -k/2);
    me->delete_temp("qzwd_pfm");
    return 1;
}

int perform_normal(object me,object target)
{
    int i=random(2)+1,j;
    if( !target ) target = offensive_target(me);
    if (me->is_fighting()
     && (int)me->query_skill("qianzhu-wandushou",1)>500
     && random(4)==2
     && me->query_skill_prepared("hand") == "qianzhu-wandushou"
     && me->query_skill_mapped("parry") == "qianzhu-wandushou"){
      perform_jigong(me,target);
      call_out("perform_normal",4,me,target);
      return 1;
    }
    if (me->is_fighting()
    && me->query_skill_prepared("hand") == "qianzhu-wandushou"
    && me->query_skill_mapped("parry") == "qianzhu-wandushou")
    {
      me->start_perform(i+1,"「千蛛万毒」");
      me->set_temp("qzwd_pfm2", 1);
      me->add_temp("apply/attack", (int)me->query_skill("qianzhu-wandushou", 1)/4);
      me->add_temp("apply/hand", (int)me->query_skill("hand", 1)/3);
      for(j=0;j<i;j++)
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)+1);
      call_out("perform_normal",i,me,target);
      me->delete_temp("qzwd_pfm2");
      me->add_temp("apply/attack", -(int)me->query_skill("qianzhu-wandushou", 1)/4);
      me->add_temp("apply/hand", -(int)me->query_skill("hand", 1)/3);
      return 1;
    }
    else
    message_vision(HIB"\n$N的千蛛万毒绝技使用完毕，长长地呼出了一口气！\n"NOR,me);
    return 1;

}

int help(object me)
{
   write(WHT"\n千蛛万毒手「"HIR"千"HIG"蛛"HIW"万"HIB"毒"WHT"」："NOR"\n");
   write(@HELP
   此招「千蛛万毒」有两种效果，可以通过SET来得到。
   1、set 千蛛万毒 疾攻  效果：向敌人发动强力连续攻击。
   2、unset 千蛛万毒 效果：持续性攻击对手，500级后将会融会贯通。

   要求：  内力 500 以上；
           最大内力 2000 以上； 
           千蛛万毒手 150 以上；
           基本手法 150 以上；
           空手备手法为千蛛万毒手。

HELP
   );
   return 1;
}

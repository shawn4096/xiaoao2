// fumo.c 大金刚拳 perform 金刚伏魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void check_fight(object me,int count);

int perform(object me, object target)
{
      string msg;                                   
      int improve,skill;
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("「金刚伏魔」只能在战斗中对对手使用。\n");
             
      if( objectp(me->query_temp("weapon")) )
         return notify_fail("你必须空手使用「金刚伏魔」！\n");
      
      if( skill=(int)me->query_skill("jingang-quan",1) < 350 )
         return notify_fail("你的大金刚拳不够娴熟，不会使用「金刚伏魔」！\n");
      
      if( (int)me->query_skill("yijin-jing",1) < 350 )
         return notify_fail("你的易筋经内功等级不够，不能使用「金刚伏魔」！\n");  
      if( (int)me->query_skill("cuff",1) < 350 )
         return notify_fail("你的基本拳法等级不够，不能使用「金刚伏魔」！\n");  
      if( (int)me->query_str() < 60 )
         return notify_fail("你的臂力不够强，不能使用「金刚伏魔」！\n");
      
      if( (int)me->query("max_neili") < 3500 )
         return notify_fail("你的内力太弱，不能使用「金刚伏魔」！\n");
      
      if( (int)me->query("neili") < 1500 )
         return notify_fail("你的内力太少了，无法使用出「金刚伏魔」！\n");   
                                                                                 
      if (me->query_skill_prepared("cuff") != "jingang-quan"
        || me->query_skill_mapped("cuff") != "jingang-quan")
                return notify_fail("你现在无法使用「金刚伏魔」进行攻击。\n");                                                                                 
      
      if( me->query_temp("fumo"))
          return notify_fail("你正在使用大金刚拳的特殊攻击「金刚伏魔」！\n");
       
      msg = HIR"$N突然全身骨骼作响，口中默念「金刚伏魔」，运起" +
               "易筋功，脸上一阵红色，全身好象有使不完的力量一样！\n" NOR;
      
      message_vision(msg, me, target); 
	  skill = me->query_skill("jingang-quan");
      if (me->query("quest/sl/yjj/powerup"))
      {
		  skill = me->query_skill("jingang-quan",1)+me->query_skill("yijin-jing",1)/2;
      }
	  
      improve = skill/5 + random(skill/5);
      if ( improve > 100 ) improve = 100 + random(improve-100) / 10;
      
	  me->add_temp("apply/strength", improve);
	  me->add_temp("apply/attack", improve*2);
	  me->add_temp("apply/cuff", improve);
	  me->add_temp("apply/damage", improve);
      me->set_temp("fumo", improve);  
      me->add("neili", - 300+ random(300));
      me->add("jingli", - 250);  
      call_out("check_fight", 1, me, skill/3);
      if (me->query_skill("jingang-quan",1)<449)
	  {
		  me->start_busy(2);
      }
      return 1;
}

void check_fight(object me,int count)
{
      int j;
      if (!me) return;
      if (me->query_temp("weapon")
       || me->query_temp("secondary_weapon")
       || me->query_skill_prepared("cuff") !="jingang-quan"){
        j = me->query_temp("fumo");
        me->add_temp("apply/strength", - j);
		me->add_temp("apply/attack", -j*2);
	    me->add_temp("apply/cuff", -j);
	    me->add_temp("apply/damage",-j);
        me->delete_temp("fumo");
        tell_object(me, HIR"你的「金刚伏魔」运功完毕，你的脸色好看多了。\n"NOR);
        return;
      }
      if (count < 1 || !me->is_fighting()) {
        j = me->query_temp("fumo");
        me->add_temp("apply/strength", - j);
		me->add_temp("apply/attack", -j*2);
	    me->add_temp("apply/cuff", -j);
	    me->add_temp("apply/damage",-j);
        me->delete_temp("fumo");
        tell_object(me, HIR"你的「金刚伏魔」运功完毕，你的脸色好看多了。\n"NOR);
        return;
      }
      else {
//        me->start_perform(1,"「金刚伏魔」");
        call_out("check_fight", 1, me, count-1);
      }
}

string perform_name(){ return HIR"金刚伏魔"NOR; }

int help(object me)
{
        write(HIB"\n大力金刚拳之「金刚伏魔」："NOR"\n");
        write(@HELP
		万法归宗，无非一空。禅宗修行重在调理内心，强化自我，以空为最高境界，而修行过重无时无刻不在和各种
		魔作斗争，既有外魔头又有内魔头，所谓降魔除魔，既需要内力又需要外力，内力在易筋经强身健体，外在金刚拳
		以金刚伏魔。本招乃少林七十二绝技中高深武学，非强大内力和高深的技艺难以施展。
				
		定位：空手绝杀配合技能之一，但因为需要强大功力，所以内力越高威力越大。

		要求：  
			最大内力需求 3500 以上；      
			当前内力需求 1500 以上；  
			般若掌等级   350  以上；
			基本拳法等级 350  以上；
			易筋经等级 350 以上；
			激发拳法为大力金刚拳；
			有效臂力不得小于60；
			且手无兵器；
			金刚伏魔450后飞跃，取消busy，可以和其他空手相配合，但需激发cuff。
			若解开易筋经第四段谜题，大金刚拳威力将再上一个台阶。
                
HELP
        );
        return 1;
}

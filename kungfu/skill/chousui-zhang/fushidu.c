// 腐尸毒
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
       object co;

       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("「腐尸毒」只能在战斗中对对手使用。\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("你必须空手才能使用「腐尸毒」！\n");

       if( (int)me->query_skill("chousui-zhang", 1) < 250 )
            return notify_fail("你的星宿毒掌还不够娴熟，使不出「腐尸毒」绝技。\n");

       if( (int)me->query_skill("huagong-dafa",1) < 250 )
            return notify_fail("你的化功大法修为不够，不能使用「腐尸毒」。\n");

       if((int)me->query_skill("poison",1)<200)
            return notify_fail("你积毒不够无法使用腐尸毒。\n"); 
       co=present("corpse",me);       

       if (!co)
           return notify_fail("你身上没有尸体，如何使用腐尸毒!\n");

       if (co->query("name")!="腐烂的男尸"
        && co->query("name")!="腐烂的女尸")
           return notify_fail("尸体没有腐烂，无法使用腐尸毒。\n");

       if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
           return notify_fail("你现在无法使用「腐尸毒」！\n");                                                                                 

       if( (int)me->query("max_neili") < 2500) 
           return notify_fail("你内力太弱，使不出「腐尸毒」。\n");      

       if( (int)me->query("neili") < 1500)
           return notify_fail("你现在真气太弱，使不出「腐尸毒」。\n");

       message_vision(BLU"\n$N一声阴笑，右手突出，挟起一具尸体掷出，一股死鱼烂肉的臭气弥漫四周，闻者欲呕！\n"NOR,me);
       
	   call_out("destroying", 1, co);
       
	   if (!target->is_killing(me))
          me->kill_ob(target);
       
	   me->add("neili", - (250 + me->query_skill("force",1)));
       
	   if( random(me->query("combat_exp")) > (int)target->query("combat_exp")* 3/5
        && me->query_str() > (int)target->query_str()/3*2)
	   { 
         message_vision(HIB"\n$n见此怪异的招数，手足无措，躲闪无及，只见散发着恶臭的尸体，正击在$n身上。\n"NOR, me, target);
         me->add("max_neili", -50);
		 if (userp(target))
			me->add_condition("killer", 90);
         target->set_temp("last_damage_from", "腐尸毒入脑");
         target->die();
         return 1;  
       }
       else if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/3
         || random(me->query_str()) > (int)target->query_str()/2)
	   {
          message_vision(HIB"\n$n见事不好，连忙纵身直起，腐尸从身下掠过，没有打中。\n"NOR,me,target);
          tell_object(target,HIB"\n你虽然及时避开了毒尸，但一股腥臭气入鼻，你已中了剧毒了。\n"NOR);
          me->add("max_neili", -70);
		  if (userp(target))
			 me->add_condition("killer", 15);
          target->apply_condition("fs_poison", random(3)+(me->query_skill("poison", 1)/10)+ target->query_condition("xx_poison"));
          me->start_busy(5);
          target->add_busy(1);
          return 1;
      }
      message_vision(HIB"\n$n胸有成竹，一声长啸，双掌连环劈出，把毒尸毒气荡向来路。\n"NOR,me,target);
      tell_object(me,HIB"\n不好，毒尸反弹向你，你虽然躲开，但毒气也侵入你的身体。\n"NOR);
      me->set_temp("last_damage_from", "腐尸毒入脑");
      me->receive_damage("qi", 2500);
      me->receive_wound("qi", 2500);
      me->add("max_neili", -100);
      me->apply_condition("fs_poison", random(3)+(me->query_skill("poison", 1)/10) +
           target->query_condition("xx_poison"));
      me->start_perform(10,"腐尸毒");
      return 1;
}

void destroying(object obj)
{
        destruct(obj);
}
string perform_name(){ return HIR"腐尸毒"NOR; }

int help(object me)
{
        write(HIR"\n抽髓掌之「腐尸毒」："NOR"\n\n");
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	抽髓掌乃是在战斗中，凭借深厚内功把体内存毒逼出借以伤敌的
	一门功夫。「腐尸毒」绝技是将毒素通过尸体投掷的方式伤敌人
	对方若不差或经验稍缺，当即毒气入脑，毒发而死，端的狠毒！

	perform strike.fushidu

要求：
	当前内力需求 1500 以上;
	最大内力需求 2500 以上；
	抽髓掌法等级 250 以上；
	化功大法等级 250 以上；
	基本掌法等级 250 以上；
	基本内功等级 250 以上;
	且手中无兵器，且手持腐烂毒尸。

        
HELP
        );
        return 1;
}
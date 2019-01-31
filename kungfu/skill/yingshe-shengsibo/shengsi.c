// huashan_shengsi.c

// yingshe-shengsibo perform 鹰蛇生死搏 

//by daidai 2005-10-07



#include <ansi.h>

#include <combat.h>



inherit F_SSERVER;



void remove_effect(object me);



string perform_name(){ return HIR"鹰"HIB"蛇"HIC"生死搏"NOR; }



int perform(object me, object target)
{
    int exp,exp1,busy,lvl,lvl1;
      if( !target ) target = offensive_target(me);
      if( !target || !me->is_fighting(target) )
           return notify_fail("「鹰蛇生死搏」只能在战斗中对对手使用。\n");        

      if( objectp(me->query_temp("weapon")) )
           return notify_fail("你必须空手使用「鹰蛇生死搏」！\n");     

      if( (int)me->query_skill("yingshe-shengsibo",1) < 200 )
            return notify_fail("你的鹰蛇生死搏不够娴熟，不会使用「鹰蛇生死搏」！\n");
	  if( (int)me->query_skill("hand",1) < 200 )
            return notify_fail("你的基本手法不够娴熟，不会使用「鹰蛇生死搏」！\n");
	  if( (int)me->query_skill("claw",1) < 200 )
            return notify_fail("你的基本爪法不够娴熟，不会使用「鹰蛇生死搏」！\n");

      if( (int)me->query_str() < 35 )

           return notify_fail("你的臂力不够35，不能使用「鹰蛇生死搏」！\n");

      if( (int)me->query("max_neili") < 3500 )
            return notify_fail("你的内力太弱，不能使用「鹰蛇生死搏」！\n");

      if( (int)me->query("neili") < 350 )
            return notify_fail("你的内力太少了，无法使用出「鹰蛇生死搏」！\n");   
      if (me->query_skill_prepared("hand") != "yingshe-shengsibo"
       && me->query_skill_prepared("claw") != "yingshe-shengsibo")
            return notify_fail("你现在无法使用「鹰蛇生死搏」进行攻击。\n");                                         
     if( me->query_temp("huashan_shengsi"))
            return notify_fail("你正在使用鹰蛇生死搏的特殊攻击「鹰蛇生死搏」！\n");

     if (target->is_busy()) return notify_fail("对方正自顾不暇，放胆攻击吧！\n");   

    message_vision( HIC"\n$N突然扑向$n，贴身疾攻，使出华山派留传百余年的绝技——七十二路“鹰蛇生死搏”！\n"
	                      +"这鹰蛇双式齐施，苍鹰矫矢之姿，毒蛇灵动之势，于一式中同时现出，迅捷狠辣，兼而有之。\n" NOR, me, target);
   
    message_vision( HIR"\n$N左手成鹰爪状，擒、拿、扭、勾，一套鹰抓擒拿手使得出神入化，神乎其技。\n" NOR, me, target);                                    
    exp=me->query("combat_exp");
    exp1=target->query("combat_exp");
    lvl=me->query_skill("claw");
    lvl1=target->query_skill("dodge");
    busy=3;
    busy=busy+random(lvl)/100;
    if(busy>8) busy=8;
    if( random(exp/100*lvl)>exp1/100*lvl1/4){
        message_vision( HIW"$n一不留神被$N抓住关节要害之处，顿时全身麻木，动弹不得。\n"NOR, me, target);
        if( wizardp(me)) tell_object(me,sprintf("busy=%d\n",busy));
        me->set_temp("huashan_shengsi",1);  
		//message_vision("你灵机一动施展出从鹰蛇相争中体悟的一招“大力鹰爪手”！", me, target); 
		me->add("neili", -350); 
		target->start_busy(2+random(3));
        message_vision(HIC "$N灵机一动施展出从鹰蛇相争中体悟的一招“大力鹰爪手”抓向$n的胸口大穴！\n" NOR, me,target);
        me->add_temp("apply/damage", me->query_skill("yingshe-shengsibo", 1)/6);
		me->add_temp("apply/attack", me->query_skill("yingshe-shengsibo", 1)/4);
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), userp(me)?3:1);	  
		if (random(10))
		{
		  message_vision(HIM "$N顺势又施展出鹰蛇相争中体悟的另外一招“灵蛇出洞”。两式齐出，威力顿时大增！\n" NOR, me,target);
		  me->add_temp("apply/hand", me->query_skill("yingshe-shengsibo", 1)/4);
		  target->add_busy(busy);		  
		  COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
		  COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
		  me->add_temp("apply/hand", -me->query_skill("yingshe-shengsibo", 1)/4);
		}
       	//me->start_busy(random(2));
        me->add_temp("apply/damage", -me->query_skill("yingshe-shengsibo", 1)/6);
		me->add_temp("apply/attack", -me->query_skill("yingshe-shengsibo", 1)/4);
        //call_out("remove_effect", me->query_skill("yingshe-shengsibo") / 10 + 2, me);
        me->delete_temp("huashan_shengsi");
        tell_object(me,MAG"\n你心知这套“鹰蛇生死搏”破绽颇多，力分而弱，不能多使，便悄悄地停止了使用。"NOR);
        message_vision(CYN"\n$N一套「鹰蛇生死搏」使用完毕，长长的吸了口气。\n"NOR, me);
      }
      else {
        message_vision( HIG"$n一个倒纵飞出丈外，敏捷地逃出了$N的攻击范围！\n"NOR, me, target);      
    // message_vision(msg, me, target);                    
        me->start_busy(2);
        me->add("neili", - 100);
        me->start_perform(3,"「鹰蛇生死搏」");   
	 }
      return 1;

}

void remove_effect(object me)
{
    if (!me) return;
    me->add_temp("apply/damage", -me->query_skill("yingshe-shengsi", 1)/10);
	me->add_temp("apply/attack", -me->query_skill("yingshe-shengsi", 1)/4);
    me->delete_temp("huashan_shengsi");
    tell_object(me,MAG"\n你心知这套“鹰蛇生死搏”破绽颇多，力分而弱，不能多使，便悄悄地停止了使用。"NOR);
    message_vision(CYN"\n$N一套「鹰蛇生死搏」使用完毕，长长的吸了口气。\n"NOR, me);

}


int help(object me)
{
        write(HIY"\n鹰蛇生死搏之「鹰蛇生死搏」："NOR"\n");
        write(@HELP
	鹰蛇生死搏绝技，是源自倚天屠龙记中，为华山派禁术
	是派中流传已达百余年的拳术，乃是左右两手分使鹰蛇
	双式拳术，共有七十二路。六大派围攻光明顶时，华山
	派当代掌门鲜于通曾以此技力斗明教教主张无忌。
	
	指令:perform hand.shengsi

要求：
	最大内力 3500 以上；      
	当前内力 500  以上；  
	鹰蛇生死搏等级 200 以上；
	基本手法的等级 200 以上；
	基本爪法的等级 200 以上；
	后天臂力为     35  以上
	激发且备爪法为鹰蛇生死搏；
	激发且备手法为鹰蛇生死搏；
	激发招架为鹰蛇生死搏；
	且手无兵器；
                
HELP
        );
        return 1;
}



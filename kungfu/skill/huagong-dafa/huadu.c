// huadu.c 化毒
// By Spiderii@ty更新效果
#include <ansi.h>

inherit F_CLEAN_UP;
void remove_effect(object me,int count);

int exert(object me)
{      
    int skill;
    skill = me->query_skill("huagong-dafa",1);
    if( !me->is_fighting() && (int)me->query_skill("huagong-dafa",1)<350 )
       return notify_fail("你只能在战斗中使用「化毒」！\n");

    if( (int)me->query_skill("huagong-dafa", 1) < 200 )
       return notify_fail("你的化功大法修为还不够！\n");

    if (me->query_skill_mapped("force") != "huagong-dafa")
       return notify_fail("其它内功有「化毒」吗？\n");

    if( (int)me->query_skill("poison", 1) < 200 )
        return notify_fail("你体内的毒素不够，无法使用「化毒」！\n"); 

    if( (int)me->query("max_neili") < 1500 )
        return notify_fail("你的内力修为这么差，还想使用「化毒」？\n");
    if( (int)me->query("neili") < 500 )
        return notify_fail("你的真气不够。\n");

    if( me->query_temp("hgdf_power"))
                return notify_fail("你已经在使用化毒技能了。\n");

     message_vision(BLU"$N运起星宿老仙独门内功化功大法，将体内蕴积的毒质慢慢化为真气，分散在四肢内。\n"NOR, me);
     if (me->query_skill("huagong-dafa",1)<450)
        me->start_busy(1);
	 else message_vision(BLU"只见$N的周身腾起了一层薄薄的浅蓝色云雾，随着$N的移动而不断向四周飘散。\n"NOR,me);
     
	 	 
	 me->add_temp("apply/strike", skill/4);
     me->add_temp("apply/attack", skill/4);
	 
	 if (me->query_skill("huagong-dafa")>349) {
	 
	 me->add_temp("apply/damage", skill/6);
	 }
	 //解开化功大法融合后发生质变	 
	 if (me->query("quest/hgdf/powerup"))
	 {
				 
	    me->add_temp("apply/strength", skill/15);
		me->add_temp("apply/damage", skill/6);
		me->add_temp("apply/attack", skill/6);
		message_vision(HBBLU+HIW"$N化功大法圆融贯通，真气流转不绝，一层若有若无的蓝绿色毒气覆盖在$N周身。\n"NOR, me);

	 }
	 me->add_temp("apply/armor_vs_force", me->query_skill("poison", 1)/3);
   
	 me->add("neili", -400);
      
	  me->set_temp("hgdf_power",skill);
	  me->set("hgdf_power",skill);//不用临时的，否则退出就丢失，无法回收了 by renlai
     
	 call_out("remove_effect", 1, me, skill/3);
     
	 if (me->query_skill("huagong-dafa",1)<350)
         me->start_exert(1, "化毒"); 
      
     return 1;
}

void remove_effect(object me, int count)
{
       int skill;
	   if (!me) return;
	   skill=me->query("hgdf_power");
       if( count < 1)
	   {          
			me->add_temp("apply/strike", -skill/4);
			me->add_temp("apply/attack", -skill/4);

			if (me->query_skill("huagong-dafa")>349)
				me->add_temp("apply/damage", -skill/6);
	 	 
			if (me->query("quest/hgdf/powerup"))
			{
				me->add_temp("apply/strength", -skill/15);
				me->add_temp("apply/damage", -skill/6);
				me->add_temp("apply/attack", -skill/6);

			}
			me->delete("hgdf_power");
			me->delete_temp("hgdf_power");

			me->add_temp("apply/armor_vs_force", -me->query_skill("poison", 1)/3);
			message_vision(BLU"$N运功化毒完毕，将真气化回毒质蕴积体内。\n"NOR, me);
			return;
        }
	   if (me->query("quest/hgdf/powerup"))
	  {
		 if (me->query_condition("xx_poison"))
		  {
			  me->clear_condition("xx_poison");
			  message_vision(BLU"$N深吸一口气，舔了下嘴唇，嘿然笑道，这星宿毒是大补之物啊！\n当下功力运转将体内所中的星宿剧毒化为内力。\n"NOR,me);
			  if (me->query_condition("xx_poison")*100<me->query("max_neili")*2-1)
				me->add("neili",me->query_condition("xx_poison")*100);
			  else me->set("neili",me->query("max_neili")*2-1);
		  }
	  }
       call_out("remove_effect", 1 , me ,count -1);
}
string exert_name(){ return HBBLU+HIW"化毒"NOR; } 
int help(object me)
{
	write(BLU"\n化功大法「化毒」："NOR"\n");
	write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	化功大法吸人内力，阴毒异常，江湖上人提起，无不谈虎色变。
	这化毒一式就是将平时积蓄于体内的剧毒以深厚内力催化于四肢
	乃是为了在与敌战斗中，起到辅助伤敌的作用！350后小飞，450
	后再次飞跃。解密化功大法的奥秘后，会出现终极飞跃。
	
	若解开化功大法的终极秘密，则此功夫威力彻底释放，大幅提升
	自身的攻击力和命中。同时，对于自己身中的星宿毒有转化为内
	力的神奇效果。且对于内功伤害有效抵消功效。
	
	注意：set 化功大法 散毒 效果具有随机攻击会让对方中毒效果

	指令：yun huadu

要求:
	化功大法 200 级；
	毒技等级 200 级；
	当前内力 500 点；
	最大内力 1000 点。
HELP
);
return 1;
}

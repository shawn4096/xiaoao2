//zhijian.c 指剑
//cre by sohu@xojh 2014
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill,improve,i;
        i=10-(int)me->query("yyz/degree");
        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「指剑」只能对战斗中的对手使用。\n");
        if( me->query("family/family_name") !="天龙寺" )
                return notify_fail("你没有得到大理一阳指真传，无法使出一阳指的无形「指剑」。\n");
        if( objectp(weapon = me->query_temp("weapon")))       
                return notify_fail("你手中拿武器，如何能够使出「指剑」？！\n");
		if (!me->query("quest/tls/zhijian/pass"))
		        return notify_fail("你虽然听说过大理一阳指「指剑」绝技，但却不会使用。\n");

        if( (int)me->query_skill("yiyang-zhi", 1) < 350 )
                return notify_fail("你的一阳指不够娴熟，无法使出「指剑」。\n");
                
        if( me->query_temp("yyz/zhijian"))
                return notify_fail("你正在使用「指剑」！\n");
		if( (int)me->query_skill("kurong-changong", 1) < 350 )
			if( (int)me->query_skill("qiantian-yiyang", 1) < 350 )
				return notify_fail("你的特殊内功火候不够，无法使出「指剑」！\n");
		if( me->query_skill_mapped("force") != "kurong-changong")
			if( me->query_skill_mapped("force") != "qiantian-yiyang")
				return notify_fail("你的现在使用的内功不对，无法使出「指剑」！\n");    

        if (me->query_skill_mapped("finger") != "yiyang-zhi"
         || me->query_skill_mapped("parry") != "yiyang-zhi" )
                return notify_fail("你现在无法使用「指剑」进行攻击。\n");

        if( me->query("max_neili") <= 3500 )
                return notify_fail("你的内力修为不足，劲力不足以施展「指剑」！\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("你的内力不够，劲力不足以施展「指剑」！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力有限，不足以施展「指剑」！\n");

        message_vision(HBYEL+HIW"$N运起一阳指劲气，伸出右手食指，出指可缓可快，缓时潇洒飘逸，快则疾如闪电，但着指之处，分毫不差。\n"+
		        "只见$N的指尖上隐隐闪烁着长约"+chinese_number(i)+HBYEL+HIW"寸的无形「指剑气」!\n"NOR, me);
        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        if (me->query_skill_mapped("force")=="kurong-changong")
		   skill =me->query_skill("kurong-changong",1)/4+me->query_skill("yiyang-zhi",1);
      	else if (me->query_skill_mapped("force")=="qiantian-yiyang")
		   skill =me->query_skill("qiantian-yiyang",1)/6+me->query_skill("yiyang-zhi",1);
		
	

		improve = skill/5;//原来是5
      	
		if ( improve > 180 ) improve = 180 + (int)random(improve-180) / 100;

        me->set_temp("yyz/zhijian", improve);

        me->add_temp("apply/damage", improve/2);
        me->add_temp("apply/finger", improve);
		me->add_temp("apply/attack", improve);
        me->add_temp("apply/strength", improve/5);

        call_out("remove_effect", 1,  me,improve);
        if (me->query_skill("yiyang-zhi",1)< 500) 
			me->start_perform(1, "「指剑」");
        return 1;
}

void remove_effect(object me,int count)
{
        int i;
		object weapon;
        if(!me) return;
		weapon=me->query_temp("weapon");
        if(!me->is_fighting()
         || weapon
         || me->query_skill_mapped("finger") != "yiyang-zhi"
         || me->query_skill_mapped("parry") != "yiyang-zhi"
         || count < 0 )
		{
          i = me->query_temp("yyz/zhijian");
          me->add_temp("apply/damage", -i/2);
		  me->add_temp("apply/finger", -i);
		  me->add_temp("apply/attack", -i);
          me->add_temp("apply/strength", -i/5);
          me->delete_temp("yyz/zhijian");
          message_vision(HBYEL+HIW"$N"HBYEL+HIW"使完一阳指指剑绝技，右手手指上的劲气逐渐消失，威力大减。\n"NOR, me);
		
  return;
        }
      
          //me->start_perform(1,"「指剑」");
		/*
		  if (!random(3)&&objectp(target))
		  {
			  switch (random(3))
			  {
				case 0:
					message_vision(HIW"$N凝气于指，一式「"HIR"破煞"HIW"」点出，但听得嗤的一声轻响，一股纯阳的内力直袭$n的胸口！\n"NOR,me,target);
					target->add_busy(1);
					break;
				case 1:
					message_vision(HIR"$N一阳指点出，「"HIW"惊神"HIR"」以纯阳内力，同时透入$n体内任脉紫宫穴、阴维脉大横穴、冲脉幽门穴、带脉章门穴和阴跤脉晴明穴！\n"NOR,me,target);
					target->add_condition("yyz_hurt",1);
					break;
				case 2:
					message_vision(HIC"$N踏前一步，出指「"HIY"截天"HIC"」劲气汹涌，隔空点向$n胸前“玉堂穴”，认穴竟无厘毫之差！！\n"NOR,me,target);
					target->receive_damage("jingli",200+random(500),me);
					break;

			  }
			 
		  }*/
          call_out("remove_effect", 2, me, count -1);
       
}              
string perform_name(){ return HBYEL+HIW"指剑"NOR; }

int help(object me)
{
        write(HIY"\n一阳指之"+HIW"「指剑」："NOR"\n\n");
        write(@HELP
	大理段氏以一阳指名扬天下，这一阳指既是运功后以右手食指点穴，
	出指可缓可快，缓时潇洒飘逸，快则疾如闪电，但着指之处，分毫
	不差。当与敌挣搏凶险之际，用此指法既可贴近径点敌人穴道，也
	可从远处欺近身去，一中即离，一攻而退，实为克敌保身的无上妙
	术。500后大飞，出家人因佛法精湛，心思宁静，比俗家略有优势。
	
	指令：perform finger.zhijian
	
要求：
	当前内力 1500 以上；
	最大内力 3500 以上；
	当前精力 1000 以上；
	一阳指等级   350 以上；
	乾天一阳等级 350 以上；
	基本指法等级 350 以上；
	激发指法为一阳指；
	激发招架为一阳指；
	激发内功为枯荣禅功或乾天一阳。
HELP
        );
        return 1;
}

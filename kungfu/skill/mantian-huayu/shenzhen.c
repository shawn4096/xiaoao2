// shenzhen.c 神针 
// By sohu 2014/6
#include <ansi.h>

inherit	F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
void remove_effect(object target);

string *xue_name1 =({
"劳宫穴","膻中穴","曲池穴","关元穴","至阳穴","中极穴","承浆穴","肩井穴"});
string *xue_name2 = ({
"百汇穴","幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴"});
string *xue_name3 = ({
"清灵穴","命门穴","风府穴","大雅穴","灵台穴","悬枢穴","气海穴","天突穴"});

int perform(object me,	object target)
{      object weapon = me->query_temp("weapon");
	int p,i,j,z;
	string name1,name2,name3;
	weapon = me->query_temp("weapon");
	name1 =	xue_name1[random(sizeof(xue_name1))];
	name2 =	xue_name2[random(sizeof(xue_name2))];
	name3 =	xue_name1[random(sizeof(xue_name3))];
	if( !target) target = offensive_target(me);
	if( !target || !me->is_fighting(target)	|| !living(target)
		    || environment(target)!=environment(me))
	   return notify_fail("没有战斗，何需消耗如此巨大的努力？\n"); 
	//if (!present("heixue shenzhen",me ))
	   //return notify_fail("没有黑血神针，即使幻化千手又有何用?!\n");
	
	if(!weapon || weapon->query("skill_type") != "throwing"	)
	   return notify_fail("你手中既无针状暗器，如何能使用这黑血神针绝技！\n");
	
	if( (int)me->query_skill("xinxing-dafa",1) < 150	)
       if( (int)me->query_skill("tianmo-gong",1) < 150	)
	   return notify_fail("你的特殊内功修为不足，无法施展黑血神针绝技！\n");
	if( (int)me->query_skill("mantian-huayu",1) < 150 )
	   return notify_fail("你的漫天花雨等级不够，无法领悟如此高深的武技！\n");
	if( (int)me->query_skill("force", 1) < 150 )
	   return notify_fail("你的基本内功修为不足，还不能意到气随！\n");
	if( (int)me->query_skill("throwing", 1)	< 150 )
	   return notify_fail("你的基本暗器修为不足，不能驾御如此复杂的手法！\n");
	if (me->query_skill_mapped("throwing") != "mantian-huayu")
	   return notify_fail("不激发漫天花雨如何使用黑血神针绝技？！\n");
	if (me->query_skill_mapped("parry") != "mantian-huayu")
	   return notify_fail("不激发漫天花雨绝技如何使用黑血神针？！\n");
	if( (int)me->query("neili") < 1500 )
	   return notify_fail("你的真气不足，不能使用黑血神针绝技！\n");
	if( (int)me->query("max_neili") < 1200 )
	   return notify_fail("你的内力不足，不能使用黑血神针绝技！\n");
	if( (int)me->query("jingli") < 300 )
	   return notify_fail("你的精力不足，不能使用黑血神针绝技！\n");
	if(target->query_temp("hmy/heixue"))
	   return notify_fail("对方已经被神针封住各处大穴，无需再多费手脚了！\n");

    i=me->query_skill("mantian-huayu",1)+me->query_skill("throwing",1)+me->query_skill("force",1);
    j=target->query_skill("parry",1)+target->query_skill("dodge",1)+me->query_skill("force",1);
	p = random(i/3);
	z = (i -j)/3;
	if ( z < 3 ) z = 3;
	if ( z > 12 ) z	=12;
      
     message_vision(HIB"\n突然$N一声清啸，双手从身上掏出一把黑色针，向外一抡，如同天女撒花似得撒向四周，将$n笼罩在内！\n"NOR,me,target);
	 
	 me->add("neili", -500);
	 me->add("jingli", -50);
	 //效果一：降低对方臂力和防御
    if (random((int)me->query("combat_exp",1)) > (int)target->query("combat_exp",1)/2 
		 ||random(me->query_dex(1))>target->query_dex(1)/3)
	{ 
      tell_object(me, MAG"你见一击奏效，压力骤减，当下不再顾虑，招招抢先！！\n"NOR);
      tell_object(target, MAG"激斗中，你突觉"RED+name1+MAG"、"RED+name2+MAG"和"RED+name3+MAG"同时一麻，一身功力顿散，四肢也开始麻木，刹时万念俱灰！！\n"NOR);
	  target->receive_damage("qi", i/3+p,me);
	 if (weapon->query("id")=="heixue shenzhen")
	   target->add_condition("heixue_poison",4+random(3));
	 target->add_busy(2);
	 if (!userp(target)) target->add_busy(3);

	 target->set_temp("hmy/heixue", 1);
	 target->set_temp("apply/strength", -(target->query("str", 1)/3));    
	 target->set_temp("apply/dexerity", -(target->query("dex", 1)/3));  
	 target->set_temp("apply/intelligence",	-(target->query("int", 1)/3));	  
	 target->set_temp("apply/constitution",	-(target->query("con", 1)/3));	
	 
	 target->apply_condition("no_perform", 1+random(2));
	 tell_object(me,	HIB"你见"+target->name()+"双眉突然深深一蹙，满脸痛楚，显是吃亏不少，顿时精神大振！\n"NOR);
	 tell_object(target, HIB"酣战中，你突觉"RED+name1+HIB"和"RED+name2+HIB"同时一麻，血脉顿时为之一塞，你连忙凝神聚气，气行周天，虽已无碍，却也是弄的额上见汗，知是吃亏不少。\n"NOR);

	 target->receive_damage("qi", i/3+p,me);	     
	 target->receive_wound("qi", i/6,me);	     

	 if (objectp(target))
	 	 target->start_call_out((:call_other,__FILE__,"remove_effect",target:),i/6); 
	 return 1;
	 }
	 else {
			message_vision(BLU"只见$p身形飘忽，诡异无比的避开了$N所发的数道夺命金光。\n"NOR,me, target);

			message_vision(HIM"$N不想对方竟只是微微一缓躲过这招，随即又纵身扑上，三针连发，呈品字形射向$n。\n"NOR,me,target);
			//tell_object(target, HIM"酣战中，你微觉"RED+name1+HIM"一麻，知是金针所伤，忙凝气冲关，虽伤处还有些疼痛，却已无大碍。\n"NOR);
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);			   
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);			   
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);			   

			me->start_busy(1);


		}	

	me->delete_temp("hmy/heixue");
	me->add("neili", -(100+random(50)));	
	me->add("jingli", -100);		
	me->start_perform(2, "「黑血神针」");	
	return 1;
	
}

void remove_effect(object target)
{
      if(!target) return;

      target->set_temp("apply/strength", target->query("str", 1)/3);    
	  target->set_temp("apply/dexerity", target->query("dex", 1)/3);  
	  target->set_temp("apply/intelligence",target->query("int", 1)/3);	  
	  target->set_temp("apply/constitution",target->query("con", 1)/3);	
      target->clear_condition("no_perform");
      target->delete_temp("qianshou");
      message_vision(WHT"只见$P长吸一口气，“噗噗”从身上逼出三枚金针，抑郁之气顿消。\n"NOR,target);
      tell_object(target,WHT"你顿觉穴道阻塞之苦全消，功行百脉，舒畅无比。\n"NOR);
	  return;
}
string perform_name(){ return HBBLU"黑血神针"NOR; }

int help(object me)
{
        write(HBBLU"\n漫天花雨之「黑血神针」："NOR"\n\n");
        write(@HELP
	魔教创制的一种剧毒暗器。施放时一丛黑针如雨般撒出，中者必死。
	正教中人闻之惊心。魔教长老曲洋为救刘正风，曾发出并未喂毒的
	黑血神针退敌！
	需要注意的是，必须身怀针状武器方能施展此招。黑血神针有特效。
	
	指令;perform throwing.shenzhen

要求：
	当前内力 1500 以上;
	最大精力 1200 以上；
	漫天花雨等级 150 以上；
	天魔功或吸星大法等级 150 以上；
	基本暗器等级 150 以上；
	基本内功等级 150 以上;
	激发暗器或招架为漫天花雨绝技；
	且手中持有针状兵器。

        
HELP
        );
        return 1;
}

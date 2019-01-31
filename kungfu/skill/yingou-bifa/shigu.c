//shigu.c 石鼓文
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int do_1(object me,object target);

string perform_name(){ return HIY"石鼓文"NOR; }

string *buwei = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
"涌泉穴","大锥穴","风府穴",
}); 
int perform(object me, object target)
{
      string msg; 
      int i, damage,p;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("你手里没有笔，无法写出石鼓文！\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("石鼓文只能在战斗中对对手使用。\n");
             
      if((int)me->query_skill("yingou-bifa",1) < 350 )
         return notify_fail("你的银钩笔法还不够娴熟，不会写石鼓文！\n");
       if((int)me->query_skill("brush",1) < 350 )
         return notify_fail("你的基本笔法还不够娴熟，不会写石鼓文！\n");     
      if((int)me->query_skill("literate",1) < 250 )
         return notify_fail("你的读书写字等级不够，不能写出石鼓文！\n");  
      if((int)me->query_int() < 50 )
         return notify_fail("你的悟性不够，不能写出石鼓文！\n");  
      if((int)me->query_skill("qiantian-yiyang",1) < 350 )
         return notify_fail("你的乾天一阳等级不够，不能写出石鼓文！\n");
      
      if((int)me->query("max_neili") < 4000 )
         return notify_fail("你的内力太弱，无法写出强劲有力的石鼓文! \n");
      
      if((int)me->query("neili") < 1000 )
         return notify_fail("你的内力太少了，写出的石鼓文无刚阳之气！\n");       

      if((int)me->query("jingli") < 500 )
         return notify_fail("你的精力太少了，写出的石鼓文无刚阳之气！\n");       
         
      if(me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("你激发不对，现在无法写出「石鼓文」！\n");

      i = random((int)(me->query_skill("yingou-bifa",1)/15));
      if(i < 1) i=1;
      if(i > 15) i=15;                                                                                 

      msg = HIY"$N忽然间笔法又变，运笔不似写字，却如拿了斧头在石头上凿打一般。这一路笔法是石鼓文，\n"+
               "那是春秋之际用斧凿刻在石鼓上的文字，此乃最古的大篆字。$n对这一路古篆果然只识得一两\n"+
               "个字，既不知对方书写何字，自然猜不到书法间架和笔画走势，登时难以招架。\n" NOR;

      me->add("neili", - 450);
      me->add("jingli", -100);

      if((random(me->query_skill("literate",1)) > target->query_skill("literate",1)/6)
       ||(random(me->query_skill("force",1)) > target->query_skill("force",1)/5)){
           //me->start_busy(1);
           target->start_busy(3);
           damage = (int)me->query_skill("yingou-bifa", 1);
           damage = damage + random(damage);
           damage = damage * i * 2 / 3;
           if (damage > 4000 ) damage = 4000+random(1000);
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/4,me);
           msg += MAG"$N一个字一个字篆将出来，文字固然古奥，而作为书法之基的银钩笔法也相应加强劲力。\n"+
                     "$N振笔挥舞，在空中连书三个古字，$n还想得到去认甚麽字，膝上穴道一麻，强吸一口气\n"+
                     "向膝间穴道冲去，$N笔来如电，跟著又是一点连环进招，$n不由自主地瘫倒在地上。\n"NOR;
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           msg += "( $n"+eff_status_msg(p)+" )\n";
		   message_vision(msg, me, target);
		   me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/4);
		   me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/5);
		   me->add_temp("apply/brush",me->query_skill("yingou-bifa",1)/5);

		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		   me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/4);
		   me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/5);
		   me->add_temp("apply/brush",-me->query_skill("yingou-bifa",1)/5);
           if (me->is_fighting(target)&& objectp(target)){
			  do_1(me,target);
		   }

       }
       else{
           msg += CYN"$P一字快过一字，笔锋掠过$p的身边，只觉得冷飕飕的，$p已无力去认$P所\n"+
                     "写何字，只得护住面门和身上各大要穴，突然臂上一麻，强吸一口气去冲穴道，\n"+
                     "总算勉力冲穴成功，但是手臂已酸麻无力，勉强能招架。\n"NOR;
           if( random(me->query("combat_exp", 1)) > target->query("combat_exp", 1)/ 2
            && me->is_fighting(target)
            && present(target,environment(me))){
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
              if (present(target,environment(me)) && me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
           }
           me->start_busy(2);
           if ( target->query("neili") > 400 ) target->add("neili",- random(200));
		   message_vision(msg, me, target);
       }
      
       me->start_perform(4,"「石鼓文」");
       return 1;
}
int do_1(object me,object target)
{
    object wp1,wp2;
	string name;
	name = buwei[random(sizeof(buwei))];
	wp1=me->query_temp("weapon");
	//wp2=target->query_temp("weapon");
	if (!wp1) return 0;
	
	if (!me||!target) return 0;
	
	message_vision(HIC"$N一个字一个字篆将出来，文字固然古奥，而作为书法之基的一阳指也相应加强劲力。\n"+
		"$N手中的"+wp1->query("name")+HIC"抖动，已在$n的"+HIR+name+HIC"上题了一个大篆,正是一个「尔」字！\n"NOR,me,target);
	message_vision(HIC"$n一看，茫然问道：「这是『网』字麽？」,$N笑道，这是一个『尔』字！\n"NOR,me,target);
	target->add_busy(2);
	me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/5);
	if (me->is_fighting(target)&& objectp(target)) 
		call_out("do_nai",1,me,target);
	return 1;

}
int do_nai(object me,object target)
{
    object wp1;
	string name;
	if (!me||!target) return 0;

	wp1=me->query_temp("weapon");
	if (!wp1) return 0;

	name = buwei[random(sizeof(buwei))];
	message_vision(CYN"$N随即伸出"+wp1->query("name")+CYN"又在$n的"+HIR+name+CYN"上写了一字。$n道：「这多半是『月』字？」$N摇头说道：「错了，那是『乃』字。」\n"NOR,me,target);
	me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/4);
	if (me->is_fighting(target)&& objectp(target)) 
		call_out("do_manyi",1,me,target);
	return 1;

}
int do_manyi(object me,object target)
{
    object wp2;
	string name,name2;
	if (!me||!target) return 0;

	wp2=target->query_temp("weapon");
	

	name = buwei[random(sizeof(buwei))];
	if (wp2) 
	{ 
		name2=wp2->query("name");
		message_vision(HIG"\n$n心神沮丧，挥舞"+name2+HIG"，要躲开$N的笔锋，不再让$N在"+name2+HIG"上题字，不料$N左掌陡然从侧面强攻，\n"
					+"$n忙伸掌抵敌，却给$N乘虚而入，又在"+name2+HIG"上又题了两字，只因写得急了，已非大篆，却是草书。\n"NOR,me,target);

	}
	else {
		
		message_vision(HIG"\n$n心神沮丧，挥舞双掌，企图要躲开$N的笔锋，不再让$N在"+HIR+name+HIG"上题字，不料$N左掌陡然从侧面强攻，\n"
					+"$n忙伸掌抵敌，却给$N乘虚而入，又在"+HIR+name+HIG"上又题了两字，只因写得急了，已非大篆，却是草书。\n"NOR,me,target);

	}
	
	
	message_vision(HIC"忽然喝道这两个字$n便识得了，脱口而出，叫道：「蛮夷！」！\n"NOR,me,target);
	me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/2);
    me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/2);
    me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/4);
    message_vision(HIY"$N哈哈大笑，叫道：不错，正是「尔乃蛮夷！」这四个字！\n"NOR,me);
	return 1;

}

int help(object me)
{
	write(HIC"\n银钩笔法之「石鼓文」绝技："NOR"\n");
	write(@HELP
	银钩笔法乃是一灯大师大弟子朱子柳的独门武技，因其状元出身
	且悟性高，所以拜师一灯大师后，武技突飞猛进，成为四大弟子
	中武功最高者。这门功夫厉害之处在于将一阳指和书法融合在一
	起，招式中夹杂着点穴，令人防不胜防。
	后来在大胜关与霍都一战，采用石鼓文绝技，以普通毛笔对战霍
	都，用篆体施展出「石鼓文」绝技，名扬天下。
	
指令：perform brush.shigu

要求：	
	最大内力 4000 以上；		
	当前内力 1000 以上；
	当前精力 500  以上；
	银钩笔法等级 350 以上；
	有效悟性 50 以上；
	读书写字等级 250 以上；
	激发笔法为银钩笔法
	激发招架为银钩笔法；
	手持笔类武器。
HELP
	);
	return 1;
}
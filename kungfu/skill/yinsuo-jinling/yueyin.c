// yufeng.c 银索金铃--「乐音绝技」
// By River
// Modified by darken@SJ

#include <ansi.h>
string perform_name(){ return HBBLU+HIW"乐音绝技"NOR; }
inherit F_SSERVER;
void check_fight(object me,object target,int count);
int perform(object me, object target)
{
        string msg ;
        object weapon,weapon1; 
        int i,ap,dp,busy;
      
        weapon = me->query_temp("weapon");

        if( !target )
             target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target))
             return notify_fail("「乐音绝技」只能对战斗中的对手使用。\n");
//需要增加解密环节
         if (!me->query("yueyin"))
			return notify_fail("「乐音绝技」需要跟小龙女请教方可使用。\n");
         if( !weapon 
         || me->query_skill_mapped("whip") != "yinsuo-jinling"
         || me->query_skill_mapped("parry") != "yinsuo-jinling"
         || weapon->query("skill_type") != "whip") 
             return notify_fail("你现在无法使用「乐音绝技」攻击对方。\n");

        if((int)me->query_skill("yunu-xinjing", 1)  < 350 )
             return notify_fail("你的玉女心经等级还不够，使不出「乐音绝技」。\n");

        if((int)me->query_skill("yinsuo-jinling",1) < 350 ) 
             return notify_fail("你的银索金铃还不够娴熟，不会使用「乐音绝技」。\n");

        if((int)me->query_skill("yunu-jianfa",1) < 350 ) 
             return notify_fail("你的玉女素心剑还不够娴熟，难以配合银索金铃的「乐音绝技」。\n");

        if((string)me->query_skill_mapped("sword") !="yunu-jianfa")
             return notify_fail("你必须将玉女素心剑作为你的剑法使用。\n");

        if((int)me->query("neili") < 2500)
             return notify_fail("你的内力不够用来「乐音绝技」。\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("你的精力不够用来「乐音绝技」。\n");

        if(me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("你所使用的内功不对。\n");

        if( target->query_temp("yueyin"))
             return notify_fail(target->name()+"被你的乐音所迷惑，你可以放胆攻击。\n");

        if( userp(me) && (string)me->query("family/family_name") != "古墓派")
             return notify_fail("你不是古墓派的传人，怎么会使用「乐音绝技」！\n"); 

        msg = HIW"\n$N手中"+weapon->name()+HIW"飘动，幻成一片竹雾，又发出玎玎声响，忽怎忽缓，忽轻忽响，竟尔如乐曲一般。\n"NOR;
        msg +=HIW"音乐乃依循天籁及人身自然节拍而组成，是故乐音则听之悦耳，嘈杂则闻之心烦。\n"NOR;
        message_vision(msg, me, target);
        me->add("neili", -500);
        me->add("jingli", -200);

        i = ((int)me->query_skill("yinsuo-jinling", 1)+(int)me->query_skill("yunu-xinjing", 1));
        // all 400级，大概这个地方应该是(400+400)/10 == 80?
        if(me->query("gender") !="女性")
         i /=6;
		else i/=3;
        weapon1 = target->query_temp("weapon");
        ap = me->query("combat_exp") * me->query_per();
        dp = target->query("combat_exp") * target->query_kar();
        //对方如果拿武器的话，夺下别人兵器，do_attack三次
		//如果有互搏的话，就拿自己兵器再do_attack三次
		if( weapon1 )							      
	    {
          if( random(ap) > dp /2
		      || !living(target))
		     {
           		msg = HIR"\n$N手中"+weapon->name()+HIR"如银蛇般四下游走，只闻叮当之声，$n手腕上中了一击，被迫放弃了手中的"+weapon1->name()+HIR"。\n"NOR;
                msg += HIR"$N顺势夺过$n的"+weapon1->name()+HIR"丢在地上，乘$n情急狼狈之际，左手握住"+weapon->name()+HIR"速攻三招。\n"NOR;
           		message_vision(msg, me, target);
    
                weapon1->unequip();
                weapon1->move(environment(target));
                target->add_busy(1);
           		me->add("neili", -200);
           		me->set_temp("juan", 1);
                me->add_temp("apply/damage", i);
                me->add_temp("apply/attack", i*2);
                me->add_temp("apply/dexerity", i);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="女性")?3:1);
           		if(present(target,environment(me))
			       && me->is_fighting(target))
                   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="女性")?3:1);
		        if(present(target,environment(me))
		        	&& me->is_fighting(target))
			       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="女性")?3:1);
           		
				if(me->query("double_attack")
				   && me->query("quest/hubo/pass")
			       && me->is_fighting(target))
			    {
        	     	message_vision(HIY"\n已经深深领悟双手互搏的精粹，随即$N右手"+weapon->name()+HIY"飞扬，宛如卷起一团白花，疾攻$n数招。\n"NOR, me, target);
             		if (present(target,environment(me)) && me->is_fighting(target))
                                   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="女性")?3:1);
        	     	if (present(target,environment(me)) && me->is_fighting(target))
                                   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="女性")?3:1);
        	     	if (present(target,environment(me)) && me->is_fighting(target))
				    {
             			if(random(me->query("combat_exp"))>target->query("combat_exp")/2)
						   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="女性")?3:1);
					    else
						    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
				    }
           		}
                me->add_temp("apply/damage", -i);
           		me->add_temp("apply/attack", -i*2);
           		me->add_temp("apply/dexerity", -i);
           		me->delete_temp("juan");
           		me->start_perform(5,"「乐音绝技」");
         	 }
         	else
		    {
         		msg =CYN"\n$n急忙大吼一声，发出一阵嘈音来冲散乐曲，霎时间两般声音交作，忽轻忽响，或高或低。\n"NOR;
           		message_vision(msg, me, target);
           		me->start_busy(1);
           		target->add("jingli", -60);
           		me->start_perform(3,"「乐音绝技」");
         	}
         	return 1;
        }
	// 如果对手不是用的兵器的话
        if((random(ap) > dp/2 || random(target->query("pur")) >= 20)
           && me->is_fighting(target)){
           msg =HIY"\n$n只听得铃声玎玎，起伏有致，有如乐曲，听了几下，下意识间竟要顺著乐音的节奏起舞。\n"NOR;
           message_vision(msg, me, target);
           me->add("neili", -200);
           target->set_temp("yueyin", i);
           target->add_temp("apply/dexerity", -i);
		   //target->add_temp("apply/parry", -i);
		   //target->add_temp("apply/defense", -i);
		   target->add("jing",-i);
//	   降80点身法？crazy?
           target->add_temp("apply/dodge", -i*2);
           if(wizardp(me))
           	   tell_object(me,sprintf("i = %d\n",i));
	   // 400级的时候，80/3 == 26
	   // random(26)+1
	   // 1-26个busy
	   // 好像有点多了吧？
	       busy = random(i/50)+1;
	       if(busy>10) 	busy = 10+(int)random(busy-10)/5;
           target->add_busy(busy);
           target->apply_condition("no_perform", 1+random(2));
           if (!me->query("quest/jiuyingm/pass"))
           {
			   me->start_perform(2,"「乐音绝技」");
           }
		   //else me->start_perform(,"「乐音绝技」");
           if (objectp(target)&&living(target))
            call_out("check_fight", 1, me, target, busy);
        }
        else{
           msg +=CYN"\n$n急忙大吼一声，发出一阵嘈音来冲散乐曲，霎时间两般声音交作，忽轻忽响，或高或低。\n"NOR;
           me->start_busy(1+random(1));
           message_vision(msg, me, target);
           target->add("jingli", -60);
           me->start_perform(3,"「乐音绝技」");
        }
        return 1;
}

void check_fight(object me,object target,int count)
{
        int j ;
        if(!target) return;
        j = target->query_temp("yueyin");
        if( !me
         || !me->is_fighting(target)
         || me->query_skill_mapped("whip") != "yinsuo-jinling"
         || !me->query_temp("weapon")
         || count -- < 1 ){
           target->add_temp("apply/dexerity", j );
           target->add_temp("apply/dodge", j*2 );
           //target->clear_condition("no_perform");
           if( target->is_busy()) target->start_busy(1);
           target->delete_temp("yueyin");
           message_vision(HIW"\n$N心情於瞬息之间接连数变，终于恢复了明智。\n\n"NOR, target);
           return ;
        }
        call_out("check_fight", 1, me, target, count);
}
int help(object me)
{
        write(WHT"\n银索金玲之"HBBLU+HIW"「乐音绝技」："NOR"\n");
        write(@HELP
	银索金铃乃是古墓独门武技，源自小龙女大战
	金轮法王和武林诸位英雄豪杰时的武技。银索
	乃是采用天山天蚕丝打造，极为坚韧，且阴柔
	无比，前端为一金色的铃铛，有干扰对方施展
	正常武技的功能。乐音绝技经由小龙女指点后
	方能使用，将古墓阴柔内力融入到银索中，催
	动索端的金玲，发出一阵阵杂音，干扰对方精
	力。尤其是漂亮的女性，对本武技的应用更是
	威力倍增，该武功判断容貌和身法。女性使用
	有优势。
		
	perform whip.yueyin
	
要求：
	最大内力要求 5000 以上；      
	当前内力要求 2500 以上；
	玉女心经等级 350 以上；
	银索金铃等级 350 以上；
	玉女身法等级 350 以上；
	激发基本鞭法为银索金铃；
	激发招架为银索金铃；
	激发内功为玉女心经；
	手持鞭类兵器，
	开了古墓九阴，再次飞跃；               
                
HELP
        );
        return 1;
}
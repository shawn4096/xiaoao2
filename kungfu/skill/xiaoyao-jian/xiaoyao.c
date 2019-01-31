// xiaoyao.c 逍遥剑法之 逍遥自在
// By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int i,j,damage,count,skill;
		object weapon,weapon2,tweapon,*inv;
		weapon=me->query_temp("weapon");
		//weapon2=present("sword",me);
        inv = all_inventory(me);
		skill=me->query_skill("xiaoyao-jian",1);
        
		for(count=0, i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "dagger") 
		   {
			   weapon2 = inv[i];
			   break;
		   }
        }
		
        if(!objectp(weapon) || !objectp(weapon2)||weapon2->query("skill_type")!="dagger" ||weapon->query("skill_type")!="sword")
		    return notify_fail("必须一手执剑，一手匕首，才能施展杨逍的逍遥剑诀绝技！\n");
        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("「逍遥剑诀」只能在战斗中使用。\n");       
        if( !objectp(me->query_temp("weapon")) )
               return notify_fail("手中无武器，如何能施展「逍遥剑诀」！\n");
        if( me->query_temp("xyjf/xiaoyao"))        
                return notify_fail("你正在使用「逍遥剑诀」？！\n");
		if( me->query("xyjf/jueji")!="pass")        
                return notify_fail("你虽然听说过逍遥剑诀，但尚未理解并不会使用「逍遥剑诀」？！\n");
        if((int)me->query_skill("sword", 1) < 350 )
                return notify_fail("你的基本剑法太低，无法使用「逍遥剑诀」。\n");  
        if((int)me->query_skill("xiaoyao-jian", 1) < 350 )
                return notify_fail("你的逍遥剑还不够娴熟，不能使出「逍遥剑诀」。\n");
        if (me->query_skill_mapped("parry") != "xiaoyao-jian"
           && me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("你的招架不对，又岂能使得「逍遥剑诀」？！\n");   
        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你的剑法不对，又岂能使得「逍遥剑诀」？！\n");   
	    if ( me->query("max_neili") < 3500 )
                return notify_fail("你内力修为太浅，无法使得「逍遥剑诀」！\n");                
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气不够，不能发出「逍遥剑诀」。\n");       
         if((int)me->query_skill("shenghuo-shengong", 1) < 350 )
                return notify_fail("你的圣火神功等级不够，不能应用「逍遥剑诀」。\n");       
    
        i=me->query_skill("sword",1)+me->query_skill("xiaoyao-jian",1)+me->query_skill("force",1);
        j=target->query_skill("parry",1)+target->query_skill("dodge",1)+target->query_skill("force",1);         
       
	    me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/5);
		me->add_temp("apply/sword",skill/5);

        message_vision(HIR"只见$N提足抬腿，突然之间倒退丈余，一转身，已在数丈之外，随即又倏然而至。从身上抽出一把"+weapon2->query("name")+HIR"\n"+
		  HIC"$N将手中的两把兵器武动起来，招式却是忽柔忽刚，变化无方,煞是好看。\n"NOR,me, target);
         me->add("neili", -600);
        // me->start_busy(2);
	 	if (random(me->query("combat_exp"))>target->query("combat_exp")/3)
		{	
			message_vision(HIY"$N手中两把武器彼此撞击，发出铿锵的杂音，$n一个冷不防立即为这杂音所扰。\n"NOR,me, target);
			target->receive_damage("jing",i/2,me);
			target->receive_wound("jing",i/6,me);
		    target->add_busy(2+random(1));
		}	
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	   //空手
	   if ( me->is_fighting(target) && me->query_skill("xiaoyao-jian", 1) > 300 ){
	      message_vision(MAG"只听得嗤嗤两响，$N溅起两粒小石子向$n射将过来，带着破空之声，直冲$n的诸身穴道。\n"+
			  HIY"却是$N以‘弹指神通’反运‘掷石点穴’的功夫。$n一不小心被石子弹中【"HIR"膻中穴"HIY"】。\n"NOR,me, target);
	     target->apply_condition("no_exert",2); 
		 weapon->unequip();
		 me->add_temp("apply/attack",i/6);
         me->add_temp("apply/damage",i/8);
		 target->add_busy(2);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		 me->add_temp("apply/attack",-i/6);
         me->add_temp("apply/damage",-i/8);
		 weapon->wield(); 
       }
	   //dagger
	   if ( me->is_fighting(target)&& me->query_skill("xiaoyao-jian", 1) > 350 ){
	 message_vision(HIG+"$N的两柄兵器在他手中根本既不像剑，又不像匕首，却见其在$N的双手间盘旋飞舞，忽而成剑。\n"+
		 "，忽而为峨眉刺。盘旋往复，间不容发，连续两招陆续刺向$n的周身。\n"NOR,me, target);
        target->receive_damage("qi",i*3,me);
        target->receive_wound("qi", i/8,me);
		weapon->unequip();
		weapon2->wield();
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		weapon2->unequip();
		weapon->wield();
        }
	//混合
	  if ( me->is_fighting(target) && me->query_skill("xiaoyao-jian", 1) > 350 ){
	     message_vision(HIW+"$N纵身而上，双手挥舞，忽而左手剑作短枪刺、打、缠、拍，缤纷绚烂，目不暇接。\n"+
		 HIC+"$N右手"+weapon2->query("name")+HIC"忽而当判官笔点、戳、捺、挑，更有时左手匕首，右手水刺。\n"NOR,me, target);        
         target->add_busy(1+random(2));
		 target->receive_damage("qi",i*2,me);
         target->receive_wound("qi", i/4,me);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		}
     if ( me->is_fighting(target) && me->query_skill("xiaoyao-jian", 1) > 400  ){
	   message_vision(HIB"$N仰天长啸一声，陡然间连变了二十二般兵刃招式，每般兵刃均是两套招式，一共四十四套招式陆续施展。\n"NOR,me,target);
	   message_vision(HIY"手中招式华彩缤纷，极其驳杂，但$N施展出来后又是如此的美妙，令人赏心悦目！\n"NOR,me,target);

	     me->add_temp("apply/attack",i/5);
         me->add_temp("apply/damage",i/6);
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
         me->add_temp("apply/attack",-i/5);
         me->add_temp("apply/damage",-i/6);
	  }
		me->add("neili", -(200+random(100)));
		 me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/5);
		me->add_temp("apply/sword",-skill/5);
        me->start_perform(5, "「逍遥剑诀」");   
		
        return 1;

}

string perform_name(){ return HIC"逍遥剑诀"NOR; }
int help(object me)
{
        write(HIG"\n逍遥剑法之"+HIC"「逍遥剑诀」"NOR"\n");
        write(@HELP
	杨逍乃是明教光明左使，与范遥合称”逍遥二仙“。一身武功极其驳杂，
	最具代表性的即为这逍遥剑法，当年少林寺一战，杨逍以资深武功和
	少林三老一番大战，其武功之庞杂与怪异表现的淋漓尽致，连平素一
	项都不服气的范遥都深为叹服。
	逍遥剑诀乃是逍遥二仙杨逍的绝技，一身功夫全靠博杂。可以手持剑
	匕首来施展此招。
	
	指令;perform sword.xiaoyao

要求：  
	当前内力要求 1000 以上；
	最大内力要求 3500 以上；
	当前精力要求 600 以上；
	逍遥剑法等级 350 以上；
	圣火神功等级 350 以上；
	基本剑法等级 350 以上；
	激发剑法为逍遥剑法；
	激发招架为逍遥剑法或乾坤大挪移；
	激发内功不限。
HELP
        );
        return 1;
}
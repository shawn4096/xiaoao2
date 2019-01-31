// Modified by snowman@SJ 05/12/2000
// Update By lsxk@hsbbs 2007/6/14

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

string perform_name() {return HIR"一指点三脉"NOR;}

int perform(object me, object target)
{
        int lev,lvl;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("「一指点三脉」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「一指点三脉」！\n");   

        if( (int)me->query_skill("yiyang-zhi", 1) < 500 )
                return notify_fail("你的一阳指还不够娴熟，使不出「一指点三脉」绝技。\n");

        if((int)me->query_skill("force",1) < 500 ) 
                return notify_fail("你的内功修为还不够，使不出「一指点三脉」绝技。\n");

        
        if(me->query_skill("kurong-changong", 1)<500)
          if(me->query_skill("qiantian-yiyang", 1) < 500)
                return notify_fail("以你现在激发的内功修为还使不出「一指点三脉」。\n");        

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("你现在无法使用「一指点三脉」！\n"); 

        if (me->query_skill_mapped("force") != "kurong-changong" )
          if(me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("你所使用的内功不对。\n");                

        if( (int)me->query("max_neili") < ((int)me->query_skill("force",1)+1000) )
                return notify_fail("你现在内力太弱，使不出「一指点三脉」。\n");      

        if( (int)me->query("neili") < ((int)me->query_skill("force",1)+1100) )
                return notify_fail("你现在真气太弱，使不出「一指点三脉」。\n");

        if( (int)me->query("jingli") < ((int)me->query_skill("force",1)+ 800) )
                return notify_fail("你现在精力太少，使不出「一指点三脉」。\n");
        if (me->query_temp("yyz/yizhisanmai"))
                return notify_fail("你现在正在使用「一指点三脉」。\n");
        
		lev = (int)me->query_skill("yiyang-zhi", 1)/4;
        
        if(!userp(me)) lev = lev*2/3 ;
        else lev = lev *3/2  ; //3/8的威力
		lvl=lev;

	    
		message_vision(BRED+HIY"\n$N运转内力不绝，出指舒缓自如，收臂潇洒飘逸，手臂颤动，犹如蜻蜓点水，一指点出，竟分袭三道大脉，快捷无伦！\n"NOR,me,target);
        me->add_temp("apply/strength", lev /5);
        me->add_temp("apply/attack", lev);
        me->add_temp("apply/damage", lev);
        me->add_temp("apply/finger", lev);
        me->set_temp("yyz/yzsm",lev);
		//设定临时变量

		if (me->query("yideng/ronghe")=="pass")
           me->set_temp("yyz/yz3m",4);
		else me->set_temp("yyz/yz3m",3);
        //第一指
        if (objectp(target)&&me->is_fighting())
        {
		  if (me->query("yideng/ronghe")=="pass")
		  {
            me->set_temp("yyz/yz3m",4);
		    lev=lev+me->query_skill("xiantian-gong",1);
		    message_vision(HIR"$N右手食指晃动，内力凝聚双手不散，着指之处分毫不差，一中即离，一攻而退！正中$n的胸口大穴！\n"NOR,me,target);
		    target->receive_damage("qi",lev*4,me);
		    target->receive_damage("jing",lev,me);
			if(userp(me) && me->query("env/damage")&&objectp(target))
        		tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ lev+ WHT"点攻击伤害。\n"NOR);

		  }
			COMBAT_D->do_attack(me, target, 0, 3);

        }
         //me->add_temp("yyz/yz3m",-1);
		//第二指
        if( me->is_fighting(target)) {
            COMBAT_D->do_attack(me, target, 0, 3);
           // me->add_temp("yyz/yz3m",-1);
        }
		//第三指
        if( me->is_fighting(target) && (int)me->query_skill("yiyang-zhi",1) > 199 ) {
      	 COMBAT_D->do_attack(me, target, 0, 3);
	     //me->add_temp("yyz/yz3m",-1);
        }
        //追加一招特殊攻击
		
		if(objectp(target)&& me->is_fighting() &&me->query("yideng/ronghe")=="pass") {
		 message_vision(HIM"$N一阳指功力已然大乘，运转如意，伸手抬指间劲气汹涌，融合了先天功的一阳指威力陡增。\n"NOR,me);
         switch(random(3)){
           case 0:
            if(objectp(target)&& me->is_fighting(target)) {      
		         message_vision(BLU"$N将领悟的先天功的精要施展出来，威力更甚！顿时指尖闪动，劲风“嗤嗤”作响！\n"NOR,me);
                // me->add_temp("apply/attack",lvl/2); 
				 target->add_busy(2+random(2));
                 COMBAT_D->do_attack(me, target, 0, 3);
				 //me->add_temp("apply/attack",-lvl/2);				 
				 //me->add_temp("yyz/yz3m",-1);
				 me->add("neili",-lvl/4);
				 }
		   break;
		   case 1:
            if( objectp(target)&&me->is_fighting(target)) {          
		         message_vision(HIC"$N直点阳维脉三十二穴，这一次是遥点，他身子远离$n一丈开外，倏忽之间，欺近身去点了她颈中的风池穴，一中即离，快捷无伦！\n"NOR,me,target);
                 if (objectp(target))
				    target->set_temp("must_be_hit",1);
				 target->apply_condition("no_exert",1+random(1));
                 COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
				 COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
				 COMBAT_D->do_attack(me, target, 0,  3);
				 if (objectp(target))
				    target->delete_temp("must_be_hit");
                 target->receive_wound("qi",-(int)lvl/2,me);
                 me->add("neili",-lvl/4);
                 //me->add_temp("yyz/yz3m",-1);
		   }
		   break;
		   case 2:
			  if(objectp(target)&& me->is_fighting(target)) {  
		         message_vision(HBMAG"$N背向$n，倒退而行，反手出指，缓缓点她章门穴。这带脉共有八穴，出手极慢，口中呼呼喘气,大有支持不住之态。\n"NOR,me,target);
                 target->apply_condition("no_perform",1+random(2));
				 target->add("jingli",-lvl/2);
				 me->add_temp("apply/damage",lvl/6);                 
				 COMBAT_D->do_attack(me, target, 0, 3);
				 me->add_temp("apply/damage",-lvl/6);
                 //me->add_temp("yyz/yz3m",-1);				 
				 me->add("neili",-lvl/4);
		        }
		   break;		   
		   }
		}
        //me->start_busy(1);
        me->delete_temp("yyz/yz3m");

        me->add_temp("apply/strength", -lev /5);
        me->add_temp("apply/attack", -lev);
        me->add_temp("apply/damage", -lev);
        me->add_temp("apply/finger", -lev);

        me->add("neili", -300);
        me->add("jingli", -100);
        me->start_perform(4,"「一指点三脉」");
        return 1;
}


int yzsm_attack(object me, int flag)
{
        object target;
        int lev;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("「一指点三脉」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「一指点三脉」！\n");   

        if( (int)me->query_skill("yiyang-zhi", 1) < 500 )
                return notify_fail("你的一阳指还不够娴熟，使不出「一指点三脉」绝技。\n");

        if((int)me->query_skill("force",1) < 500 ) 
                return notify_fail("你的内功修为还不够，使不出「一指点三脉」绝技。\n");

        if( me->query_temp("pf_rong"))
                return notify_fail("你正在运用「荣」字大法！\n"); 

        if(me->query_skill("kurong-changong", 1)<500)
          if(me->query_skill("qiantian-yiyang", 1) < 500)
                return notify_fail("以你现在的内功修为还使不出「一指点三脉」。\n");        

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("你现在无法使用「一指点三脉」！\n"); 

        if (me->query_skill_mapped("force") != "kurong-changong" )
          if(me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("你所使用的内功不对。\n");                

        if( (int)me->query("max_neili") < ((int)me->query_skill("force",1)+1000) )
                return notify_fail("你现在内力太弱，使不出「一指点三脉」。\n");      

        if( (int)me->query("neili") < ((int)me->query_skill("force",1)+1100) )
                return notify_fail("你现在真气太弱，使不出「一指点三脉」。\n");

        if( (int)me->query("jingli") < ((int)me->query_skill("force",1)+ 800) )
                return notify_fail("你现在精力太少，使不出「一指点三脉」。\n");

        lev = (int)me->query_skill("yiyang-zhi", 1)/4;
        
        if(userp(me))  lev = lev * flag;


        message_vision(HIR"\n$N出指舒缓自如，收臂潇洒飘逸，手臂颤动，犹如蜻蜓点水，一指点出，竟分袭三道大脉，快捷无伦！\n"NOR,me,target);

        me->add_temp("apply/strength", lev /10);
        me->add_temp("apply/attack", lev/ 2);
        me->add_temp("apply/damage", lev);
        me->add_temp("apply/finger", lev);


        me->set_temp("yyz/yz3m",3);
        
         COMBAT_D->do_attack(me, target, 0, 3);
        me->add_temp("yyz/yz3m",-1);
 
        if( me->is_fighting(target)) {
          COMBAT_D->do_attack(me, target, 0, 3);
          me->add_temp("yyz/yz3m",-1);
        }

        if( me->is_fighting(target) && (int)me->query_skill("yiyang-zhi",1) > 450 ) {
      	 COMBAT_D->do_attack(me, target, 0, 3);
	     me->add_temp("yyz/yz3m",-1);
        }
        me->start_busy(1);
        me->delete_temp("yyz/yz3m");

        me->add_temp("apply/strength", -lev /10);
        me->add_temp("apply/attack", -lev/ 2);
        me->add_temp("apply/damage", -lev);
        me->add_temp("apply/finger", -lev);

        me->add("neili", -300);
        me->add("jingli", -100);
        me->start_perform(5,"「一指点三脉」");
        return 1;
}


int help(object me)
{
   write(HIY"\n一阳指之「"HIR"一指点三脉"WHT"」："NOR"\n\n");
   write(@HELP
	大理段氏以一阳指名扬天下，这一阳指既是运功后以右手食指点穴，
	出指可缓可快，缓时潇洒飘逸，快则疾如闪电，但着指之处，分毫
	不差。当与敌挣搏凶险之际，用此指法既可贴近径点敌人穴道，也
	可从远处欺近身去，一中即离，一攻而退，实为克敌保身的无上妙
	术。
	一指点三脉，乃是大理国无上绝技，一指笼罩之下，连续点三条大脉
	端的是厉害无比，若能解开一灯大师的先天功融合秘籍，一指三脉
	威力将彻底释放。

要求: 
	最大内力大于基本内功1000点以上；
	当前内力大于基本内功1100点以上；
	当前精力大于基本内功800点以上；
	一阳指等级 500 以上；
	基本内功等级 500 以上；
	特殊内功等级 500 以上；
	激发指法为一阳指；
	空手，备一阳指。
	如设置 set 一阳指点穴 则威力更甚。

HELP
   );
   return 1;
}

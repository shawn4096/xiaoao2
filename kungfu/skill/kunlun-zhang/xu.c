//昆仑叠掌之蓄劲
// By truekk

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBWHT+HIY"蓄劲"NOR; }

void checking(int i,int j,object me);

int perform(object me, object target)
{
        int i,j;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("【蓄劲】只能在战斗中使用。\n");       
        if( (int)me->query_skill("strike", 1) < 500 )
                return notify_fail("你的基本拳法不够娴熟，无法使用昆仑叠掌之蓄劲。\n");  
        //意味着550后可以武器蓄力？？
		
		if( objectp(me->query_temp("weapon")) 
			&& (int)me->query_skill("xuantian-wuji", 1) < 550
			&& !me->query("quest/kl/klz/xu/pass"))
                return notify_fail("你的玄天无极功修为不足，尚未融会贯通，无法在使用兵器的时候蓄力。\n");  
        
		if((int)me->query_skill("kunlun-zhang", 1) < 500 )
                return notify_fail("你的昆仑叠掌还不够娴熟，不能使出昆仑叠掌之蓄劲。\n");
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("你不使用昆仑叠掌，又岂能使得蓄劲？\n");   
        
		if( (int)me->query("max_neili", 1) < 15000 )
                return notify_fail("你内力修为太浅，无法蓄劲！\n");                
        if( (int)me->query("neili", 1) < 10000 )
                return notify_fail("你现在真气不够，无法蓄劲。\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 500 )
                return notify_fail("你的玄天无极功修为不足以将内力外放。\n");
        if( me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("你的内功心法不对，发挥不出蓄劲之威。\n");   
        
		if( me->query_temp("kunlun_xu") )
                return notify_fail("你上次蓄力还没结束，想爆体而亡吗！？\n");

	
        if( me->query_str(1) < 80 )
                return notify_fail("你的后天臂力不足80，无法使用昆仑叠掌之蓄劲掌力。\n");  
		
		i=me->query_skill("kunlun-zhang",1)/40;
        j=me->query("env/昆仑叠掌蓄劲");
        
		if( j<1) j=1;
		j=(int)me->query_skill("kunlun-zhang",1)/6;
		
        if( j>10) j=10;

        if( !userp(me))  i = i / 5;    //npc 弱化
		
        if( objectp(me->query_temp("weapon")) ) i=i / 2;//武器减半
		
		if (me->query("gender")!="男性")
		{
			j=j/3;
		}

        message_vision(WHT"\n$N运起玄天无极功，面色如铁，真气缓缓溶入双手，无声无息，手上劲道越来越强，蓄势待发！\n" NOR, me);
        me->delete_temp("kl_xu");
       //设定启动量
		me->set_temp("kl_xu",1);
        
		me->set_temp("kunlun_xu",1);
        me->add("neili", -100); 
        call_out("checking",1,i,j,me);
        return 1;
}
/*
void checking(int i,int j,object me)
{
        object weapon,target;
      //  int i;
        if( !me )  return;	
		
	//	i=me->query_skill("kunlun-zhang",1)/15;

        if( !target ) target = offensive_target(me);
        if( !target || !(target->is_character()) || !(me->is_fighting(target)) ) 
		{
			call_out("xu_end", 1,i,j, me);
			return; 
		}


        if ( (int)me->query("neili") < 900  ) {
             message_vision(HIR"$N的内劲後继无力，不得不停止蓄力！\n" NOR, me,target);
             call_out("xu_end", 1,i,j, me);
			 return;
        }
        else if ( me->query_skill_mapped("strike") != "kunlun-zhang"
				||me->query_skill_prepared("strike") != "kunlun-zhang" ) {
             tell_object(me, HIR "\n你未施展昆仑叠掌，无法再进行「蓄劲」！\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else if ( me->is_busy() ) {
             tell_object(me, HIR "\n你现在动作不够灵活，无法继续维持蓄力！\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else if (!me->is_fighting()) {
             tell_object(me,  "\n你现在没有和人过招，当下收回了「蓄劲」!。\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else if( environment(target) != environment(me) ) {
             tell_object(me, "你见对方已经不在这里，当下停止了蓄力。\n");
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else {
			
			if ( me->query_temp("kl_xu") ==10 )
			{        
				 message_vision(HBRED+HIW"\n$N的第十层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -900);
			}
			else if ( me->query_temp("kl_xu") ==9 ) {        
				 message_vision(HBYEL+"\n$N的第九层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -800);
			}
			else if ( me->query_temp("kl_xu") ==8 ) {        
				 message_vision(HIR"\n$N的第八层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -700);
			}
			else if ( me->query_temp("kl_xu") ==7 ) {        
				 message_vision(WHT"\n$N的第七层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -600);
			}
			else if ( me->query_temp("kl_xu") ==6 ) {        
				 message_vision(RED"\n$N的第六层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -500);
			}
			else if ( me->query_temp("kl_xu") ==5 ) {        
				 message_vision(BLU"\n$N的第五层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -400);
			}
			else if ( me->query_temp("kl_xu") ==4 ) {        
				 message_vision(HIG"\n$N的第四层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -300);
			}
			else if ( me->query_temp("kl_xu") ==3 ) {        
				 message_vision(MAG"\n$N的第三层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -200);
			}
			else if ( me->query_temp("kl_xu") ==2 ) {        
				 message_vision(YEL"\n$N的第二层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				// me->add_temp("apply/attack", i*2);
				 me->add("neili", -100);
			}
			else if ( me->query_temp("kl_xu") ==1 ) {        
				 message_vision(CYN"\n$N的第一层玄天无极真气溶入双手，蓄势待发！\n" NOR, me);
				 me->add_temp("apply/damage", i);
				// me->add_temp("apply/attack", i*2);
				 me->add("neili", -100);
			}
			else if ( me->query_temp("kl_xu") == j ) {
				 message_vision(HIW "\n$N蓄力完成，长啸一声，双手闪耀乳白色的光辉，显然已经被玄天无极功的内力布满！\n" NOR, me, target);      	
				 call_out("xu_end", (int)me->query_skill("kunlun-zhang",1)/60,i,j, me);        		
			}
			else {
				 me->set_temp("kl_xu", me->query_temp("kl_xu")+1);
				 call_out("checking", 1,i,j, me);
			}  
        }
}  */

void checking(int i,int j,object me)
{
		object weapon,target;
		int klz;
		if( !me )  return;	
		
		klz= me->query_temp("kl_xu");
		
		     
		message_vision(HIW"\n$N玄天无极功运转一圈，将第"HIY+chinese_number(klz)+HIW"层玄天无极真气溶入双手！\n" NOR, me);
		me->add_temp("apply/damage", i);
		//满了坚持10秒
		if (me->query_temp("kl_xu") == j )
		{
			message_vision(HIR "\n$N长啸一声，功力已经达到瓶颈，双手闪耀乳白色的光辉，显然已经被玄天无极功的内力布满！\n" NOR, me, target); 
			call_out("xu_end", (int)me->query_skill("kunlun-zhang",1)/60,i,j, me);
			return;
		}


        if ( (int)me->query("neili") < 900  )
		{
             message_vision(HIR"$N的内劲後继无力，不得不停止蓄力！\n" NOR, me,target);
             call_out("xu_end", 1,i,j, me);
			 return;
        }
        if ( me->query_skill_mapped("strike") != "kunlun-zhang"
				||me->query_skill_prepared("strike") != "kunlun-zhang" ) 
		{
             tell_object(me, HIR "\n你未施展昆仑叠掌，无法再进行「蓄劲」！\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        if ( me->is_busy() ) {
             tell_object(me, HIR "\n你现在动作不够灵活，无法继续维持蓄力！\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        if (!me->is_fighting()) {
             tell_object(me,  "\n你现在没有和人过招，当下收回了「蓄劲」!。\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        if( environment(target) != environment(me) ) {
             tell_object(me, "你见对方已经不在这里，当下停止了蓄力。\n");
             call_out("xu_end", 1,i,j, me);
             return;
        }
		me->set_temp(me->query_temp("kl_xu")+1);
		me->add("neili", -900-random(100));

	    call_out("checking", 1,i,j, me);
}

void xu_end(int i,int j,object me)
{
	if (!me) return;
	
  
  
  //  me->add_temp("apply/attack", -i*2);   
    me->add_temp("apply/damage", -i*j);   
    me->delete_temp("kl_xu");
    me->delete_temp("kunlun_xu");
    me->start_busy(2+random(2));
    tell_object(me, HIW "\n你暗自调息，渐渐释放蓄积在双手附着的玄天无极真气。\n\n" NOR);

   return;
}

int help(object me)
{
	write(WHT"\n昆仑叠掌之「"HBWHT+HIY"蓄劲"WHT"」："NOR"\n");
	write(@HELP
	昆仑叠掌是昆仑派开派祖师何足道的高级空手功夫
	何足道大战卫天望时见他以少林硬功来战，于是也
	以昆仑掌法来和他对抗，昆仑掌法刚柔相济，厉害
	无比虽然不及降龙十八掌刚猛，但也有其独到之处。
	昆仑叠掌蓄力是将自己平生辛苦修炼的内劲运使双
	掌之中，蓄而不发，蓄力越久威力越大。
	昆仑叠掌修炼到550级且受苦柏长老指点后,内劲运
	使圆转如意，此招不受手中是否有兵器的限制。但
	威力不足空手状态的一半。
	此招极为耗损真气，功力不高者慎用，功力不纯者
	慎用。
	注意：set 昆仑叠掌蓄劲 xx（1-10）数字代表蓄积
	的劲道数量。默认值为一道内劲。
	
	指令：perform strike.xu

要求：     
	当前内力 2000 以上，
	最大内力 15000 以上。
	基本掌法 500  以上；
	昆仑叠掌 500  以上；
	玄天无极 500  以上；
	后天臂力 80   以上；
	激发内功为玄天无极功；
	激发掌法且备为昆仑叠掌
	解密何足道方可使用
HELP
	);
	return 1;
}

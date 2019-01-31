// huagu_poison.c

#include <ansi.h>


//inherit F_CLEAN_UP;
/*
int update_condition(object me, int duration)
{    
      tell_object(me, HIR "你感到一阵剧痛，全身的骨头格格作响！\n" NOR );
      message_vision(HIR"$你突然两腿发软，感觉全身乏力，好象虚脱一般，劲气大量外泄。\n"NOR, me);

      me->receive_damage("qi", 100+random(50));
      me->receive_wound("qi", 50+random(70));
      me->receive_damage("jing", 100+random(50));
      me->receive_wound("jing", 50+random(50));
      me->set_temp("last_damage_from", "化骨绵掌毒性发作");
      me->apply_condition("huagu_poison", duration - 1);
     if( duration < 1 ) return 0;
     return CND_CONTINUE;
}*/




int update_condition(object me, int duration)
{
        int qi,cs,nl;
        string msg;
        if(duration<0)
        {
                me->delete_temp("nlcs");
                return 0;
        }
        if(me->is_ghost())
        {
                me->set("huagu",0);
                me->delete_temp("nlcs");
                return 0;
        }
        if( duration < 1 ) 
        {
          	qi=me->query("huagu");
           	me->delete_temp("nlcs");
           	me->delete("huagu");
           	me->delete("sld/huagu_mark");
          	if(qi)
          	{
            		me->set_temp("last_damage_from", "化骨绵掌毒发作");
            		me->receive_damage("qi", qi);
            		me->receive_wound("qi", qi);
           		if (living(me))
                    		msg = "$N感到一阵剧痛，全身的骨头格格作响！\n";
             		else
                    		msg = "$N一声惨叫，全身的骨头一块块地化做了粉末！\n";
                    	message_vision(BLU+msg+NOR,me);                    	
           		if(qi>me->query("max_qi"))
                		me->die();
          	}
           return 0;
        }

	    if(!random(me->query("sld/huagu_mark")))
        {
        	me->receive_damage("qi", 10);
        	me->set_temp("last_damage_from", "化骨绵掌毒发作");
        	
			if(me->query("neili")>60)
        	{
                	cs=me->query("neili")/60;
                	//nl=60*cs;
					nl=cs;
                	me->add("neili",-nl);
                	if(!me->query_temp("nlcs",1))
	                        me->set_temp("nlcs",cs-1);
        	        else
                	        me->add_temp("nlcs",cs-1);
                	if(userp(me))                	
			      	{
						me->add("huagu",-2*cs);
                        duration--;}
                	else
                		duration--;
                	
                	if (living(me))
                        	msg = "$N感到身上一阵剧痛，忙运功抵御！\n";
                	else
                        	msg = "$N痛苦地呻咛了一声，感到身上的内力在一点点地消失！\n";
        	}
        	else if(me->query_temp("nlcs",1)>=10)
        		{
                		me->add_temp("nlcs",-10);
                		if (living(me))
                        		msg = "$N感到身上一阵剧痛，忙运功抵御！\n";
                		else
                        		msg = "$N痛苦地呻咛了一声，感到身上的内力在一点点地消失！\n";
        		}
        		else
        		{
         			me->add("huagu",400);
        			if(me->query("huagu")>me->query("max_qi"))
                			duration=0;
        			else
                			duration--;
        			if (living(me))
                        		msg = "$N感到一阵疼痛掠体而过！\n";
                		else	
                        		msg = "$N痛苦地呻咛了一声，感到一阵疼痛掠体而过！\n";
        		}
        	
			    if(wizardp(me))
        	     {
        		   if(me->query("huagu")>0)
                		tell_object(me,sprintf("你中的化骨绵掌毒尚要发作%d次，你现在所中的化骨绵掌毒力已达到了%d。\n",duration,me->query("huagu")));
        		   else if(me->query("huagu")<0)
                		    tell_object(me,sprintf("你中的化骨绵掌毒尚要发作%d次，你现在对化骨绵掌毒的抵御力为%d。\n",duration,-me->query("huagu")));
        	     	else
                		  tell_object(me,sprintf("你中的化骨绵掌毒尚要发作%d次。\n",duration));
                }
                me->apply_condition("huagu_poison", duration-1);
                message_vision(BLU+msg+NOR,me);
                me->add_busy(1);
            }
        return 1;
}

string query_type(object me)
{
        return "poison";
}

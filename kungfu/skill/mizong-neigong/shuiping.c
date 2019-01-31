
// shenghuo.c  圣火重构，定位成阴寒属性，定位为9，侧重配合圣火令法，乾坤大挪移，吸血等奇诡之武功，大成，即便不开九阳也无所谓。 

#include <ansi.h>
inherit F_SSERVER;
//inherit F_CLEAN_UP;
int help(object me);

void remove_effect(object me, int amount);

string exert_name(){ return WHT"圣火焚躯"NOR; }

int exert(object me)
{
	int skill, i;
	int j;
	if(!me->is_fighting() && me->query_skill("shenghuo-shengong", 1) < 100 ) 
	     return notify_fail("你只能在战斗中用圣火神功来提升自己的战斗力。\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("你的内力不够。\n");
		
	if( (int)me->query_temp("mj/shenghuo") ) 
		return notify_fail("你已经在运功中了。\n");

   // skill = (int)me->query_skill("force",1) + (int)me->query_skill("shenghuo-shengong",1);
    skill = (int)me->query_skill("shenghuo-shengong",1);
    i = skill/10 + random(skill/10); 

	me->add("neili", -100+random(100));
	if (me->query_skill("qiankun-danuoyi",1)<100) j=1;
	else if (100<me->query_skill("qiankun-danuoyi",1)<200) j=2;
	else if (200<=me->query_skill("qiankun-danuoyi",1)<300) j=3;
	else if (300<=me->query_skill("qiankun-danuoyi",1)<350) j=4;
	else if (350<=me->query_skill("qiankun-danuoyi",1)<400) j=5;
	else if (400<=me->query_skill("qiankun-danuoyi",1)<450) j=6;
	else if (450<=me->query_skill("qiankun-danuoyi",1)) j=7;
	else j=1;
	
    if (me->query_skill("shenghuo-shengong",1)>449 && me->query_skill("mj/qkdny/ronghe"))
    {
	  message_vision(WHT "\n$N微一凝神，运起圣火焚躯，只见$N的脸色变得由青变白，再由白变青转换"+chinese_number(j)+WHT"次。\n" NOR, me);
      message_vision(HIW "\n随着$N的轻吟“熊熊烈火，焚我残躯”，$N的周身腾起一股若隐若现的青蒙之气，出手似乎更重了。\n" NOR, me);
      me->add_temp("apply/attack", i*7);
      me->add_temp("apply/damage", i*5);
      me->add_temp("apply/dagger", i*5);
	  me->add_temp("apply/armor", i*2);
	  call_out("remove_effect", 1, me, i);	  
     }
	 else
	  {
	  message_vision(WHT "$N微一凝神，运起圣火神功，只见$N的脸色变得由青变白，再由白变青转换"+chinese_number(j)+"次。\n" NOR, me);
	  me->add_temp("apply/attack", i);
	  me->add_temp("apply/armor", i);
      me->add_temp("apply/dagger", i);
	  call_out("remove_effect", 1, me, i);
	  }
    me->set_temp("mj/shenghuo", i);
	if( me->is_fighting() && me->query_skill("shenghuo-shengong",1) < 349 ) me->start_busy(random(2));
	   me->start_exert(1,"圣火神功");
	return 1;
}

void remove_effect(object me, int count)
{    
     int amount;
     if( objectp(me) && me->query_temp("mj/shenghuo") ) 
        {
              if( count-- > 0 ) {
                     call_out("remove_effect", 1, me, count);
                    return;
                 }
	
	if (me->query_skill("shenghuo-shengong",1)>449 && me->query_skill("mj/qkdny/ronghe"))
     {
	  me->add_temp("apply/attack", -count*7);
      me->add_temp("apply/damage", -count*5);
      me->add_temp("apply/dagger", -count*5);
	  me->add_temp("apply/armor", -count*2);
	  me->delete_temp("mj/shenghuo");
     }
	else
	  {
	  me->add_temp("apply/attack", - count);
	  me->add_temp("apply/armor", - count);
      me->add_temp("apply/dagger", - count);
	  me->delete_temp("mj/shenghuo");
      }
	 
     tell_object(me, HIW"\n你的"WHT"圣火焚躯"HIW"运行完毕，将内力收回丹田。\n"NOR);
	  }       
}

int help(object me)
{
        write(HIC"\n圣火神功「圣火焚躯」："NOR"\n");
        write(@HELP
		说明：明教弟子一生忠于明尊，以火为神圣之物，对于门派最大的忠诚表现在以火焚身的精神，
			这是明尊弟子最大的追求和向往。
        要求：  当前内力 800 以上；
                当前精力 300 以上；
                圣火神功等级 100 以上；
                激发内功为圣火神功。

        另外：
        350级小飞，取消busy        
		450后解开乾坤大挪移【融合】谜题，彻底和乾坤大挪移融合，阴性威力放开。

HELP
        );
        return 1;
}
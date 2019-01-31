
// yuxue 浴血重生.c  血刀门核心武技，身上血越多，攻击和杀伤力越强。
// xuedao/dafa/pass 为谜题标记
#include <ansi.h>
inherit F_SSERVER;
//inherit F_CLEAN_UP;
int help(object me);

void remove_effect(object me, int amount);

string exert_name(){ return HIR"浴血重生"NOR; }

int exert(object me)
{
	int skill, i;
	int j;
	string msg;
	if(!me->is_fighting() && me->query_skill("xuedao-dafa", 1) < 100 ) 
	     return notify_fail("你只能在战斗中用血刀大法来提升自己的战斗力。\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("你的内力不够。\n");
		
	if( (int)me->query_temp("xuedao/yuxue") ) 
		return notify_fail("你已经在运功中了。\n");

   // skill = (int)me->query_skill("force",1) + (int)me->query_skill("xuedao-dafa",1);
    skill = (int)me->query_skill("xuedao-dafa",1);
    i = skill/10 + random(skill/10); 

	me->add("neili", -100+random(100));
	if (me->query_skill("xuedao-dafa",1)<100) j=1;
	else if (100<=me->query_skill("xuedao-dafa",1)<200) j=2;
	else if (200<=me->query_skill("xuedao-dafa",1)<300) j=3;
	else if (300<=me->query_skill("xuedao-dafa",1)<350) j=4;
	else if (350<=me->query_skill("xuedao-dafa",1)<400) j=5;
	else if (400<=me->query_skill("xuedao-dafa",1)<450) j=6;
	else if (450<=me->query_skill("xuedao-dafa",1)) j=7;
	else j=1;
	
    if (me->query_skill("xuedao-dafa",1)>449 && me->query_skill("xuedao/dafa/pass"))
    {
	  message_vision(HBRED "\n$N微一凝神，运起血刀大法之浴血重生终极秘籍，只见$N的脸色变得由青变红，再由红变白转换"+chinese_number(j)+HBRED"次。\n" NOR, me);
      message_vision(HBRED "\n随着$N的嘴里轻吟起密宗神秘的经文，$N的周身腾起一股若隐若现的血红气罩，出手似乎更重了。\n" NOR, me);
      me->add_temp("apply/attack", i*7);
      me->add_temp("apply/damage", i*5);
      me->add_temp("apply/blade", i*5);
	  me->add_temp("apply/armor", i*2);
	  //me->set_temp("xuedao/yuxue",i);
	  call_out("remove_effect", 1, me, i);	
	  
     }
	 else
	  {
	  message_vision(HBRED "$N微一凝神，运起血刀大法之浴血秘技，只见$N的脸色变得由青变红，再由红变白转换"+chinese_number(j)+"次。\n" NOR, me);
	  me->add_temp("apply/attack", 2*i);
	  me->add_temp("apply/armor", i);
      me->add_temp("apply/blade", i);
	  //me->set_temp("xuedao/yuxue",i);
	  call_out("remove_effect", 1, me, i);
	  }
     me->set_temp("xuedao/yuxue", i);
	 if( me->is_fighting() && me->query_skill("xuedao-dafa",1) < 349 ) me->start_busy(random(2));
	 if (me->query_skill("xuedao-dafa",1) > 449)
	   {
		msg = HIR "$N深深吸入一口气，脸色由红转白，复又由白返红，伤势恢复了不少。\n" NOR;
	    message_vision(msg,me);
		me->receive_curing("qi", i);
        me->receive_healing("qi", i * 3 / 2);
        me->add("neili", -200);
	    if (random(10) < 3)
        {
                tell_object(me, HIC "由于你过度的催动真元，导致你的内力有所损耗。\n" NOR);
                me->add("max_neili", -1);
        }/**/
	   }
		 
	   me->start_exert(1,"浴血重生");
	   return 1;
}

void remove_effect(object me, int count)
{    
     int amount;

     if( objectp(me) && me->query_temp("xuedao/yuxue") ) 
        {
              if( count-- > 0 ) {
                     call_out("remove_effect", 1, me, count);
					
                    return;
                 }
		  }
		  amount=me->query_temp("xuedao/yuxue");
	      if (me->query_skill("xuedao-dafa",1)>449 && me->query_skill("xuedao/dafa/pass"))
                  {
	               me->add_temp("apply/attack", -amount*7);
                   me->add_temp("apply/damage", -amount*5);
                   me->add_temp("apply/blade", -amount*5);
	               me->add_temp("apply/armor", -amount*2);
	               me->delete_temp("xuedao/yuxue");
				   //write("449");
				   tell_object(me, HIR"\n你的血刀大法秘技运行完毕，将内力收回丹田0。\n"NOR);
				   return;
                }
	          else
	            {
	               me->add_temp("apply/attack", -2*amount);
	               me->add_temp("apply/armor", -amount);
                   me->add_temp("apply/blade", -amount);
	               me->delete_temp("xuedao/yuxue");
				  // write("<449"+amount);
				   tell_object(me, HIR"\n你的血刀大法秘技运行完毕，将内力收回丹田1。\n"NOR);
				   return;
                }
				//write("bottom");
}

int help(object me)
{
        write(HIR"\n血刀大法之「浴血重生」："NOR"\n");
        write(@HELP
		说明：血刀大法乃是青海黑教血刀门第一代掌门人血刀老祖所创，他号称武林第一邪派高手。主要原因就是
			因为这门奇特的内功和刀法相配，会产生意想不到的效果。血刀大法，言外之意就是和血光有关，身上的
			血越多，攻击力越强，身法和气劲越是诡异。

        要求：  当前内力 800 以上；
                当前精力 300 以上；
                血刀大法等级 100 以上；
                激发内功为血刀大法。

        另外：
        350级小飞，取消busy。
		450后可以自动疗伤，若解开血刀老祖谜题，血刀大法诡异之效果威力将全部释放。

HELP
        );
        return 1;
}
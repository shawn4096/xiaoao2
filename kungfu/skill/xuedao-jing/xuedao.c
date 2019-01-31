
// 血刀大法，血刀门的奇异武学，会增加刀法的诡异
// xuedao.c 

#include <ansi.h>
inherit F_SSERVER;
//inherit F_CLEAN_UP;
int help(object me);

void remove_effect(object me, int amount);

string exert_name(){ return HBRED+HIY"血刀大法"NOR; }

int exert(object me)
{
	int skill, i;
	
	if(!me->is_fighting()) 
	     return notify_fail("你只能在战斗中用血刀经来提升自己的刀法威力。\n");

	if( (int)me->query("neili") < 5000  ) 
		return notify_fail("你的内力不够。\n");
	if( (int)me->query("jingli") < 3000  ) 
		return notify_fail("你的精力不够。\n");

	if( me->query_skill("force", 1) < 500 )
        return notify_fail("你的基本内功修为火候未到，施展只会伤及自身！\n");
	if( me->query_skill("xuedao-jing", 1) < 500 )
        return notify_fail("你的血刀经功夫修为火候未到，施展只会伤及自身！\n");
	if (!me->query("quest/xd/xdj/xuedao/pass"))
	{
		return notify_fail("你尚未领悟到血刀秘笈中的大法绝世精髓，无法施展！\n");

	}
	if( (int)me->query_temp("xdj/xuedao") ) 
		return notify_fail("你已经在施展血刀大法中了。\n");

   // skill = (int)me->query_skill("force",1) + (int)me->query_skill("xuedao-dafa",1);
    skill = (int)me->query_skill("xuedao-jing",1);
  
	message_vision(MAG "\n$N忽然间左足金鸡独立，右足横着平伸而出，双手反在身后，左手握着右耳，右手握着左耳,姿式越来越怪。\n" 
					        +"花样变幻无穷，有时双手撑地，有时飞跃半空，更有时以头顶地倒立，下半身却凭空生出六条腿来!\n"
					        +"$N的舌尖从左边嘴角中微微伸出，同时右眼张大而左眼略眯，脸上神情十分古怪，但手中的刀却下意识的晃了晃。\n"
							+"刀身似乎变得更为柔韧！\n"NOR, me);
      me->add_temp("apply/attack", skill/6);
      me->add_temp("apply/blade", skill/4);
	  me->add_temp("apply/damage", skill/5);

      me->set_temp("xdj/xuedao", skill);
	  
	  call_out("remove_effect", 1, me,(int)skill/30);	

	  return 1;
}

void remove_effect(object me, int count)
{    
     int skill;
	 if (!me||!me->query_temp("xdj/xuedao")) return;
	 skill=me->query_temp("xdj/xuedao");
	 if( !me->is_fighting()
		||count-- < 0 )
	 {
		  me->add_temp("apply/attack", -skill/6);
		  me->add_temp("apply/blade", -skill/4);
		  me->add_temp("apply/damage", -skill/5);
		  me->delete_temp("xdj/xuedao");
		  tell_object(me, MAG"\n你的血刀大法秘技运行完毕，刀势也逐渐恢复原样。\n"NOR);
		  return;
       } 
	  call_out("remove_effect",1,me,count--);
	
}

int help(object me)
{
        write(HIR"\n血刀经之「血刀大法」："NOR"\n");
        write(@HELP
	血刀经乃是青海黑教血刀门第一代掌门人血刀老祖所创，
	他号称武林第一邪派高手。主要原因就是因为这门奇特的
	内功和刀法相配，会产生意想不到的效果。血刀大法是血
	刀门的震门之宝，血刀秘籍的绝世武技，非核心弟子不传。
	注意：做雪谷激战任务中会随机触发解密条件，然后可以
	向老祖每天请教即可。

	说明：血刀大法是针对血刀门对于刀法的运用已臻极致，
	很多功法都将内劲和刀法使用技巧结合，使得血刀门对于
	刀法的运用具有独到之处。
	
	指令：exert xuedao

要求：
	当前内力需求 5000 以上；
	当前精力需求 3000 以上；
	血刀经的等级 500 以上；
	基本内功等级 500 以上；
	激发内功为血刀经。

HELP
        );
        return 1;
}
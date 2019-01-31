
// yuxue 浴血重生.c  血刀门核心武技，身上血越多，攻击和杀伤力越强。
// xuedao/dafa/pass 为谜题标记
#include <ansi.h>
inherit F_SSERVER;
//inherit F_CLEAN_UP;
int help(object me);

void remove_effect(object me, int amount);

string exert_name(){ return HBRED+HIW"浴血重生"NOR; }

int exert(object me)
{
	int skill, i;
	int j;
	string msg;
	if(!me->is_fighting() && me->query_skill("xuedao-jing", 1) < 500 ) 
	     return notify_fail("你只能在战斗中用血刀经来提升自己的战斗力。\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("你的内力不够。\n");
	
	if( (int)me->query("max_neili") < 1400  ) 
		return notify_fail("你的最大内力不够。\n");
	
	if( (int)me->query("max_jingli") < 1400  ) 
		return notify_fail("你的最大精力不够。\n");

	if( (int)me->query_skill("xuedao-jing",1) < 100  ) 
		return notify_fail("你的血刀经功力不够100。\n");
	
	if( (int)me->query_skill("force",1) < 100  ) 
		return notify_fail("你的基本内功功力不够100。\n");

	if( (int)me->query_temp("xdj/yuxue") ) 
		return notify_fail("你已经在运功中了。\n");

   // skill = (int)me->query_skill("force",1) + (int)me->query_skill("xuedao-jing",1);
    skill = (int)me->query_skill("xuedao-jing",1);
    
	i = skill/10 + random(skill/10); 

	me->add("neili", -100+random(100));
	if (me->query_skill("xuedao-jing",1)<100) j=1;
	else if (100<=me->query_skill("xuedao-jing",1)<200) j=2;
	else if (200<=me->query_skill("xuedao-jing",1)<300) j=3;
	else if (300<=me->query_skill("xuedao-jing",1)<350) j=4;
	else if (350<=me->query_skill("xuedao-jing",1)<400) j=5;
	else if (400<=me->query_skill("xuedao-jing",1)<450) j=6;
	else if (450<=me->query_skill("xuedao-jing",1)) j=7;
	else j=1;
	
    if (me->query_skill("xuedao-jing",1)>449 
		&& me->query_skill("quest/xd/xdj/xuedao/pass"))
    {
		  message_vision(HBRED "\n$N微一凝神，运起血刀经之浴血重生终极秘籍，辛苦修炼的气血精气瞬间内敛。\n" NOR, me);
		  message_vision(HBRED "\n随着$N的嘴里轻吟起密宗神秘的经文，$N的周身腾起一股若隐若现的血红气圈。\n" NOR, me);
		  me->add_temp("apply/attack", skill/4);
		  me->add_temp("apply/damage", skill/5);
		  me->add_temp("apply/blade", skill/3);
		  me->add_temp("apply/armor", skill/5);
		  me->add_temp("apply/parry", skill/5);

		  //me->set_temp("xuedao/yuxue",i);
		  call_out("remove_effect", 1, me, skill/20);	
	  
     }
	 else
	  {
		  message_vision(RED "$N微一凝神，运起血刀经之浴血秘技，只见$N气血上涌立时变红，劲气带动周身僧袍微微腾起。\n" NOR, me);
		  me->add_temp("apply/attack", skill/6);
		  me->add_temp("apply/armor", skill/6);
		  me->add_temp("apply/blade", skill/5);
		  //me->set_temp("xuedao/yuxue",i);
		  call_out("remove_effect", 1, me, skill/30);
	  }
	//神照经2融合威力增加
	if (me->query("quest/xd/szj/ronghe/pass"))
	{
		skill=skill+me->query_skill("shenzhao-jing",1)/5;
		message_vision(HBMAG+HIW "\n$N将神照经的功夫融合到血刀经中，邪中带正，刚中带柔，血刀经的威力大增。\n"NOR, me);
		me->add_temp("apply/parry",skill/6);
		me->add_temp("apply/armor",skill/6);
		me->add_temp("apply/damage",skill/6);

		me->set_temp("xdj/shenzhaoronghe",skill);
	}



		me->set_temp("xdj/yuxue", skill);
		
		if( me->is_fighting() && me->query_skill("xuedao-jing",1) < 349 ) me->start_busy(random(2));
		
	   if (me->query_skill("xuedao-jing",1) > 450 
		   && me->query("env/血刀经")=="浴血疗伤"
		   && me->query("eff_qi")< me->query("max_qi"))
	   {
			msg = HIR "$N深深吸入一口气，脸色由红转白，复又由白返红,血刀经功力发动，伤势竟然在缓缓恢复。\n" NOR;
			message_vision(msg,me);
			me->receive_curing("qi", skill/10);
			me->receive_healing("qi", skill * 3 / 20);
			me->add("neili", -200);
			if (random(10) < 2 && !me->query("quest/xd/xdj/xuedao/pass"))
			{
					tell_object(me, HIC "由于你过度的催动真元，导致你的最大内力有所损耗。\n" NOR);
					me->add("max_neili", -1);
			}
	   }
	   if(me->query_skill("xuedao-jing",1) < 350 ) 
		  me->start_exert(1,"浴血重生");
	   return 1;
}

void remove_effect(object me, int count)
{    
     int skill;
	 if (!me||!me->query_temp("xdj/yuxue")) return;
	 skill=me->query_temp("xdj/yuxue");
	
     if( !me->is_fighting()
		 ||count-- < 0 )
	{

	   if (me->query_skill("xuedao-jing",1)>449 
		   && me->query_skill("quest/xd/xdj/xuedao/pass"))
       {
		  me->add_temp("apply/attack", -skill/4);
		  me->add_temp("apply/damage", -skill/5);
		  me->add_temp("apply/blade", -skill/3);
		  me->add_temp("apply/armor", -skill/5);
		  me->add_temp("apply/parry",- skill/5);
		  me->delete_temp("xdj/yuxue");
		  tell_object(me, HIR"\n你的血刀经浴血秘技运行完毕，将内力收回丹田。\n"NOR);
		  return;
       } else
	   {
		  me->add_temp("apply/attack", -skill/6);
		  me->add_temp("apply/armor", -skill/6);
		  me->add_temp("apply/blade", -skill/5);		
		  me->delete_temp("xdj/yuxue");

		  tell_object(me, HIR"\n你的血刀经秘浴血技运行完毕，将内力收回丹田。\n"NOR);
		  return;
       } 
	   if (me->query_temp("xdj/shenzhaoronghe"))
	   {
			  me->add_temp("apply/parry",-skill/6);
			  me->add_temp("apply/armor",-skill/6);
			  me->add_temp("apply/damage",-skill/6);
			  me->delete_temp("xdj/shenzhaoronghe");
		}

					 
					
	 }
					 
	 call_out("remove_effect", 1, me, count);
				
}

int help(object me)
{
        write(HIR"\n血刀经之「浴血重生」："NOR"\n");
        write(@HELP
	血刀经乃是青海黑教血刀门第一代掌门人血刀老祖所创，
	他号称武林第一邪派高手。主要原因就是因为这门奇特的
	内功和刀法相配，会产生意想不到的效果。血刀经，言外
	之意就是和血光有关，身上的血越多，攻击力越强，身法
	和气劲越是诡异。
	若解开神照经第二段并请教狄云后，浴血重生将发生一定
	的异变，邪中带正，威力再上一层楼。

	说明：血刀经内功源自《血刀经》秘籍，初始可以通过读
	书来修习内功，到一定程度后，可以跟血刀老祖请教血刀
	秘笈的绝世心法后方可登堂入室，修为大成。350级后小飞。

	注意：set 血刀经 浴血疗伤 

	使用条件，450级方可使用，如果没解开血刀大法会随机
	损失一点最大内力为代价，玩家慎用。

	指令：exert yuxue

要求：
	当前内力 800 以上；
	最大内力 1400 以上；
	最大精力 1400 以上；
	当前精力 300 以上；
	血刀经等级 100 以上；
	激发内功为血刀经。

另外：
	350级小飞，取消busy。
	450 后可以自动疗伤，随机掉最大内力
	若解开血刀老祖谜题，不会掉最大内力
	血刀经诡异之效果威力将全部释放。
	
HELP
        );
        return 1;
}
// sohu@xojh
//xinchan.c
//心禅

#include <ansi.h>
void remove_effect(object me,int count);
string pic;
string *pictures=({
  HIY"观自在菩萨，行深般若波罗蜜多时，照见五蕴皆空，度一切苦厄"NOR,
  HIC"舍利子，色不异空，空不异色，色即是空，空即是色，受想行识亦复如是"NOR,
  HIR"舍利子，是诸法空相，不生不灭，不垢不净，不增不减"NOR,
  HIB"故说般若波罗蜜多咒，即说咒曰：揭谛揭谛　波罗揭谛　波罗僧揭谛　菩提萨婆诃"NOR,
  MAG"是故空中无色，无受想行识，无眼耳鼻舌身意，无色声香味触法，无眼界乃至无意识界\n无无明亦无无明尽，乃至无老死，亦无老死尽，无苦集灭道，无智亦无得。"NOR,
  HIW"以无所得故，菩提萨埵。依般若波罗蜜多故，心无挂碍；无挂碍故，无有恐怖，远离颠倒梦想，究竟涅槃"NOR,
  HIG"故知般若波罗蜜多，是大神咒，是大明咒，是无上咒，是无等等咒，能除一切苦，真实不虚"NOR
});

int exert(object me)
{    
      int skill;
	  skill=me->query_skill("hunyuan-yiqi",1);
	  if ( !me->is_fighting())
                return notify_fail("你只能在战斗中使用「心禅境」！\n");
	
      if( (int)me->query_skill("hunyuan-yiqi", 1) < 250 )
                return notify_fail("你的易筋经内功修为不够，无法使用「心禅境」！\n");
      if( (int)me->query_skill("force", 1) < 250 )
                return notify_fail("你的基本内功修为不够，无法使用「心禅境」！\n");
 

      if (me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("其它内功有「心禅境」吗？\n");

      if( (int)me->query_con() < 40 )
                return notify_fail("你的后天根骨太低，根本无法使用「心禅境」！\n");
 
      if( (int)me->query("neili") < 600 )
                return notify_fail("你目前的内力太少了，无法使用「心禅境」！\n");   
    
      if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力不够，还想使用「心禅境」？\n");   
      if( me->query_temp("hyyq/xinchan"))
                return notify_fail("你正在运用「心禅境」！\n");
                                                                                 
      message_vision(HIR"\n$N低诵佛号，阿弥陀佛！善哉善哉，面上无喜无忧，一股劲气遍布周身，很快进入"HIG"心禅"HIR"境界！\n" NOR, me);
	  pic=pictures[random(sizeof(pictures))];
	  message_vision(pic+"\n",me);

    
      me->set_temp("hyyq/xinchan",skill);
	  
	  me->add_temp("apply/attack", skill/4);		
      me->add_temp("apply/damage", skill/6);
	  if (me->query("quest/sl/hyyq/xinchan/pass"))
	  {
		message_vision(HIC"朗声吟诵道，“不立文字，教外别传，直指人心，见性成佛！”善哉，善哉！随着$N的吟诵，由定生静，由静生慧！\n"NOR,me);
		me->add_temp("apply/intelligence", (int)me->query_skill("buddhism",1)/10);
	  }
      me->add("neili", -300);  
	  me->add("jingli", -200);  

      call_out("remove_effect", 1, me, (int)me->query_skill("hunyuan-yiqi", 1)/40);

      return 1;
}

void remove_effect(object me,int count)
{
        int skill;
		if( !me||!me->query_temp("hyyq/xinchan")) return;
		skill=me->query_temp("hyyq/xinchan");
        if( count < 1
			||!me->is_fighting())
	   {
		  me->add_temp("apply/attack", -skill/4);		
		  me->add_temp("apply/damage", -skill/6);
		  if (me->query("quest/sl/hyyq/xinchan/pass"))
		  {
			me->add_temp("apply/intelligence", -(int)me->query_skill("buddhism",1)/10);
		  }

		  me->delete_temp("hyyq/xinchan");
		  message_vision(HIR"\n$N默念佛号，缓缓释放蓄积的混元一气功,心禅状态解除。\n"NOR, me);    
		  return;
		}     
        call_out("remove_effect", 1, me,count -1);
		return;
}
string exert_name(){ return HBGRN+HIW"心禅"NOR; }

int help(object me)
{
        write(HIY"\n混元一气功之「心禅」："NOR"\n");
        write(@HELP
	少林混元一气功是少林寺基础心法，凝聚混元一气劲
	既可以修炼心禅境，也可以增加手头上功夫，练到高
	深处，虽然不如本门第一神功易筋经的威力，但因其
	脱胎于易筋经心法，也是不俗的内功心法。
	少林乃禅宗祖庭，以顿悟立世，心禅是将佛法融入到
	武技中，不立文字，教外别传，直指人心，见性成佛
	短期内提升命中和伤害的内功心法。解密后会增加少
	许的悟性，和佛法修为有关。

	指令：exert xinchan

要求：  
	混元一气功等级 250  以上；
	基本内功的等级 250  以上；
	后天根骨的需求 40   以上；
	当前的内力需求 600 以上；
	当前的精力需求 500  以上。

HELP
        );
        return 1;
}

// tanqin.c 仙姬弹琴
// Created by snowman@SJ 08/03/2001

#include <ansi.h>

inherit F_SSERVER;

int is_pfm() { return 1;}
void check_fight(object me, int i);

#define PFM_NAME 	"仙姬弹琴"

string perform_name(){ return HIG+PFM_NAME+NOR; }

void check_fight(object me, int i);

int perform(object me, object target)
{
	object weapon;
	int i;
	
      	if( !me->is_fighting() )
      		return notify_fail("「"PFM_NAME + "」只能在战斗中对对手使用。\n");      
     		
     	i = (int)me->query_skill("fuqin-shi", 1);
      	if( i < 300 )
      		return notify_fail("你的抚琴式不够娴熟，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query_skill("whip",1) < 300 )
      		return notify_fail("你的基本鞭法等级不够，不能使用「" + PFM_NAME + "」！\n");  
      
      	if( (int)me->query_skill("sancheng-gong", 1) < 300 )
      		return notify_fail("你的三乘功法等级不够，不能使用「" + PFM_NAME + "」！\n");

      	if( (int)me->query("max_neili") < 6500 )
      		return notify_fail("你的内力太弱，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query("neili") < 3000 )
      		return notify_fail("你的内力太少了，无法使用出「" + PFM_NAME + "」！\n");   
        
	    if( me->query("jiali") > me->query_dex() )
      		return notify_fail("你现在用力过猛，无法支持使用「" + PFM_NAME + "」。\n");
      								      
      	if( me->query_skill_mapped("force") != "sancheng-gong")
      		return notify_fail("你现在的内功无法支持使用「" + PFM_NAME + "」。\n");
      	
      	if( (int)me->query_int() < 45 )
      		return notify_fail("你对琴韵的理解还不够透彻，无法发挥「" + PFM_NAME + "」的威力！\n");
      		
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "whip"
       	|| me->query_skill_mapped("whip") != "fuqin-shi")
      		return notify_fail("你手里没有鞭，无法使用「" + PFM_NAME + "」！\n");   
      		
      	if( me->query_temp("pfm/tanqin") )
      		return notify_fail("你正在使用「" + PFM_NAME + "」中！\n");   
      		
      	message_vision(HIG"\n$N将$n"HIG"卷曲，默默运起真气，向左右各走了一步，接着将$n"HIG"一甩，在头顶绕了数个园圈。$n"HIG"在$P手中不断颤动，发出了一阵阵清脆的声音，加上$P微声轻啸，相辅相济，宛如悦耳的琴声一般！\n"NOR, me,weapon);
      	me->set_temp("pfm/tanqin", i);
      	me->add_temp("apply/attack", i/5);
	me->add("neili", -400);
	check_fight(me, i/2);
      	me->start_perform(6 , PFM_NAME);
      	return 1;
}


void remove_setting(object me)
{
	int j;
	
	if( !me ) return; 
        if( !intp(j = me->query_temp("pfm/tanqin")) ) return;
        
	me->add_temp("apply/attack", -j/5);
        me->delete_temp("pfm/tanqin");
        me->start_perform(2, PFM_NAME);	
}


string *pfm_chat = ({
HIG"\n$N用$n"HIG"为辅使出的「" + PFM_NAME + "」声音悦耳，略似广俊，令所有人都情不自禁！\n"NOR,
HIG"\n$n"HIG"点地出声，如同小蛙滨水而鸣，恰如琴韵，而又配上$N"HIG"的轻歌慢吟，将八方四路都包含在「" + PFM_NAME + "」之下！\n"NOR,
HIG"\n$N抚鞭出招，吟出「" + PFM_NAME + "」，宛如处子端坐抚琴般，其指法韵律，略似广俊，所有人都不禁赞美出声！\n"NOR,
HIG"\n流水般悦耳的声音出自$N"HIG"口中，再加上$n"HIG"激起的沙沙风声，织成一篇美丽的乐章，弥漫四周！\n"NOR,
HIG"\n$n"HIG"激起的风声加上$N"HIG"的轻啸，持续发出悦耳的乐声，人人都为之一愣，这便是娥嵋绝招「" + PFM_NAME + "」！\n"NOR,
HIG"\n一阵阵优美的乐声发自$N口中和挥动中的"HIG"$n，方圆四周都被笼罩在了这「" + PFM_NAME + "」绝技当中！\n"NOR,
});

int family_check(object obj)
{
	if( !obj->is_character() ) return 0;
  	if( obj->query("family/family_name") == "峨嵋派" )
    		return 0;
  	return 1;
}
void check_fight(object me, int i)
{       
        object weapon, *ob;
        int j;
        
        if( !me ) return; 
 
 	weapon = me->query_temp("weapon");
        i--;
        if( !me->is_fighting() 
	|| !living(me)
        ||  i < 1
        ||  !weapon
        ||  weapon->query("skill_type") != "whip"
       	||  me->query_skill_mapped("whip") != "fuqin-shi"
        ||  me->query("neili") < 500
        ||  me->query_skill_mapped("force") != "sancheng-gong"
        ||  me->query_skill_mapped("whip") != "fuqin-shi"
        ||  me->query_skill_mapped("parry") != "fuqin-shi") {
        	me->add_temp("apply/attack", -j/5);
        	me->delete_temp("pfm/tanqin");
        	me->add("neili", -j );
        	me->start_perform(2, PFM_NAME);
        	if( living(me) )
			message_vision(YEL "\n$N后退两步，停止了「" + PFM_NAME + "」。\n" NOR, me);   
        	return;
        }
        me->add("neili", -10 );
        ob = filter_array(all_inventory(environment(me)), (:  family_check :));
	   ob->start_perform(2, PFM_NAME);

	if( i % 10 == 0 )
		message_vision(pfm_chat[random(sizeof(pfm_chat))], me,weapon);

        call_out("check_fight", 1, me, i);
}

int help(object me)
{
	write(HIG"\n抚琴式「" + PFM_NAME + "」："NOR"\n");
	write(@HELP
	传说大诗人李白在万年寺听广俊和尚弹琴时，常有绿衣姑娘前去听。后来
	李白离去，广俊园寂。但是每到晨昏，白水池边就会琴声悠扬。有人隔窗
	窥视见一绿衣姑娘端坐抚琴，指法韵律，略似广俊，不禁赞美出声，姑娘
	惊起急避，跃入池中。前往探视，却见一小青蛙滨水而鸣，其声恰如琴韵。
	传为“仙姬弹琴”。此曲能定人神气，曲终前所有人都不能使用绝招！
	
	要求：	
		抚琴式等级 300 以上；
		基本鞭法等级 300 以上；
		三乘功法等级 300 以上；
		最大内力 6500 以上； 
		内力 3000 以上；      
		悟性 45 以上。
HELP
	);
	return 1;
}


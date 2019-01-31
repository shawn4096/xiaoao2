// 内八路，外九路，总计17剑，名曰纵横17剑
// Created by sohu@xojh,2014
// zhengheng.c 
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int is_pfm() { return 1;}
void check_first(object me,object target, int i);
#define PFM_NAME 	"纵横捭阖"
string perform_name(){ return HBYEL+HIR+PFM_NAME+NOR; }

int perform(object me, object target)
{     
      	if( (int)me->query_skill("songshan-jian",1) < 500 )
           	return notify_fail("你的嵩山剑法不够娴熟，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query_skill("sword",1) < 500 )
           	return notify_fail("你的基本剑法等级不够，不能使用" + PFM_NAME + "！\n");  
      
      	if( (int)me->query_skill("hanbing-zhenqi", 1) < 500 )
           	return notify_fail("你的寒冰真气等级不够，不能使用" + PFM_NAME + "！\n");

      	if (me->query_skill_mapped("sword") != "songshan-jian"
			||me->query_skill_mapped("parry") != "songshan-jian")
            return notify_fail("你所使用的剑法激发不是嵩山剑法。\n");
		   
	  //允许此招使用解密武功？？
		if (!me->query("quest/ss/ssjf/jueji/pass"))
		    return notify_fail("你没有解开华山石壁的绝技，无法施展此招。\n");

      	if( (int)me->query("max_neili") < 15000 )
           	return notify_fail("你的最大内力太弱，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query("neili") < 2000 )
           	return notify_fail("你的当前内力太少了，无法使用出" + PFM_NAME + "！\n"); 
        
        if( !target ) target = offensive_target(me);
        
       	if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 500 || me->query("jingli") < 100 
        || environment(target) != environment(me) )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
                
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	   object weapon;
		int i;
		
      	if( !me->is_fighting() 
        || me->query("neili") < 500 || me->query("jingli") < 100 )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
                	
	        weapon = me->query_temp("weapon");
      	if (!weapon
       	|| weapon->query("skill_type") != "sword"
       	|| me->query_skill_mapped("sword") != "songshan-jian" )
       		return notify_fail("你现在无法使用" + PFM_NAME + "！\n");      
       	//没有pfm也攻击？？	
       
       	message_vision(HBGRN+HIY"\n$N将嵩山剑法一十七路精华施展出来，气势森严，如长枪大戟，快慢变化，纵横千里。\n"
		                      +"正是嵩山剑法绝技"+ perform_name() +HBGRN+HIY"，内八路外九路,连出数剑，变幻莫测，直袭$n！\n"NOR, me, target);
       	if (me->query_temp("ss/hb"))
			i=me->query_skill("songshan-jian",1)+me->query_skill("hanbing-zhenqi",1);//寒冰有加成
		else i=me->query_skill("songshan-jian",1);
		if (me->query_temp("ss/focus"))
				i=i+(int)me->query_temp("ss/focus");//寒冰有加成
		
		me->set_temp("ssj/zhbh",i);
		me->add_temp("apply/attack", i/2);
      	me->add_temp("apply/damage", i/3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      	if( me->is_fighting(target) )
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
      	if( me->is_fighting(target) )
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
        me->add_temp("apply/damage", -i/3);
      	me->add_temp("apply/attack", -i/2);
      	
        //内八路招式
        if( me->query_temp("ssj/zhbh")&& objectp(target)&&me->is_fighting() )
       				call_out("second_attack",0,me,target);
        else call_out("check_fight",1,me,3);
		//外九路招式

      	me->start_perform(4, PFM_NAME);	
       	return 1;       	
}
//内八路增加攻击力

void check_first(object me,object target, int i)
{       
      if( !me ) return; 
        //if( !me->query_temp("ssj/zhbh1") ) return;
        
        i--;       

        if( !me->is_fighting() 
        ||  i < 1
        ||  !me->query_temp("weapon")
        ||  me->query_skill_mapped("sword") != "songshan-jian"
        ||  me->query_skill_mapped("parry") != "songshan-jian") 
		{
        	me->delete_temp("ssj/zhbh");
			me->delete_temp("ssj/zhbh1");
			me->delete_temp("ssj/zhbh2");
			message_vision(HIY"$N将一套嵩山剑绝技使完，浑身劲力一散，缓缓收功,神情肃然。\n"NOR,me);
        	return;
        }
        me->add_temp("apply/attack", me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", me->query_skill("songshan-jian", 1)/4);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
      	me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", -me->query_skill("songshan-jian", 1)/4);
          
        call_out("check_first", 1, me, target,i);
}
//检查
void check_fight(object me, int i)
{       
        if( !me ) return; 
        if( !me->query_temp("ssj/zhbh") ) return;
        
        i--;       

        if( !me->is_fighting() 
        ||  i < 1
        ||  !me->query_temp("weapon")
        ||  me->query_skill_mapped("sword") != "songshan-jian"
        ||  me->query_skill_mapped("parry") != "songshan-jian") {
        	me->delete_temp("ssj/zhbh");
			me->delete_temp("ssj/zhbh1");
			me->delete_temp("ssj/zhbh2");
			message_vision(HIY"$N将一套嵩山剑绝技使完，浑身劲力一散，缓缓收功,神情肃然。\n"NOR,me);
        	return;
        }
      
        call_out("check_fight", 1, me, i);
}
/*
void attacking(object me)
{
	object target = offensive_target(me);
	
       	if( !target 
       	|| !target->is_character() 
       	|| !me->is_fighting(target) 
       	|| !living(target) 
        || environment(target) != environment(me) )
        	return;
        me->add_temp("apply/attack", me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", me->query_skill("songshan-jian", 1)/6);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
      	me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", -me->query_skill("songshan-jian", 1)/6);
        	
}*/
//快攻，外攻 外九路
int second_attack(object me, object target)
{
	int i = me->query_skill("songshan-jian", 1)/50;
	if( i > 9 ) i = 9;
	i=random(i);
	me->set_temp("ssj/zhbh2",i);
	me->add_temp("apply/attack", me->query_skill("songshan-jian", 1)/2);
    me->add_temp("apply/damage", me->query_skill("songshan-jian", 1)/6);
	
       	message_vision(HIB"\n$N见$n仍在负隅顽抗，一声清啸，身形幻动，和$n一来一往相互交错，无数的剑光从中闪出，\n"
		+"招式奇幻，变化莫测，迅捷如闪电，数剑连出，正是嵩山剑法外九路的快攻招式！\n"NOR, me, target);
    while( i-- ){
     	if( me->is_fighting() )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

        		
    }
	me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
    me->add_temp("apply/damage", -me->query_skill("songshan-jian", 1)/6);
	
	me->delete_temp("ssj/zhbh2");
    
	me->start_perform(5, PFM_NAME);	
	//调用内八路剑法	
	if (me->is_fighting()&&objectp(target) && me->query_temp("weapon"))
	    	call_out("first_attack",1,me,target);
	else 
	    {
			remove_call_out("check_fight");
			call_out("check_fight",1,me,5);
	     }
       	return 1;
}
//缓慢进攻
int first_attack(object me, object target)
{
	    object weapon;
		int i = me->query_skill("songshan-jian", 1)/50;
    	if( i > 8 ) i = 8;	
	    //me->delete_temp("ssj/zhbh2");
		weapon=me->query_temp("weapon");
		me->set_temp("ssj/zhbh1",i);
       	message_vision(HIC"\n$N将手中"+weapon->query("name")+HIC"上下连晃，剑势变作迟缓，但威力却大增，正是内八路中的招式。\n"NOR, me);
       	
		me->add_temp("apply/attack",me->query_skill("songshan-jian", 1)/2 );
      	me->add_temp("apply/damage",me->query_skill("songshan-jian", 1)/5 );
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      	me->add_temp("apply/damage",-me->query_skill("songshan-jian", 1)/5 );
		me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
       	//me->start_perform(1, PFM_NAME);	
		if (me->is_fighting()&& objectp(target))
		{
			remove_call_out("check_first");
			call_out("check_first",1,me,target,i);
		} 
       	return 1;
}


int help(object me)
{
	write(HBYEL+RED"\n嵩山剑法「"NOR + perform_name() + HBYEL+RED"」："NOR"\n");
	write(@HELP
	嵩山剑法有“内八路，外九路”之称，17路长短快慢的剑法应有尽有。
	当年五岳剑派与魔教十长老两度会战华山，五岳剑派的好手死伤殆尽，
	五派剑法的许多惊世绝招随五派高手而消逝。嵩山派掌门左冷禅会集
	本派残存的耆老，将各人所记得的剑招不论粗精，尽数录了下来，汇
	成一部剑谱。这十年来，他去芜存菁，将本派剑法中种种不够狠辣的
	招数，不够堂皇的姿势，一一修改，使得本派的十七路剑招完美无缺。
	他虽未创设新的剑路，却算得是整理嵩山剑法的大功臣。
	所以嵩山弟子若能参悟透华山石壁的嵩山武技，那么嵩山剑法的大威
	力将彻底释放。
	
	指令：perform sword.zongheng

要求：	
	嵩山剑法等级 500 以上；
	基本剑法等级 500 以上；
	寒冰真气等级 500 以上；
	最大内力需求 15000 以上； 
	当前内力需求 2000 以上。
	激发剑法为嵩山剑法
	激发招架为嵩山剑法
	无需激发特殊内功
	手持剑类武器
HELP
	);
	return 1;
}


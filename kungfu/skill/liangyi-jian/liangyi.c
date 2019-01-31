//liangyi.c 昆仑正两仪剑的至高武学
//cre by sohu@xojh 2014
// 源自倚天和正两仪剑与反两仪刀融合。
// 两仪剑诀 

#include <ansi.h>
inherit F_SSERVER;
void finish();
void check_fight(object me, int count);

int perform(object me, object target)
{
        object weapon;
        int i=me->query_skill("liangyi-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用"HIG"两仪剑诀"NOR"。\n");
        weapon = me->query_temp("weapon");
        if( !me->query("quest/kl/lyj/liangyi/pass"))
                return notify_fail("你只是听过有这门绝技，无法施展出"HIG"两仪剑诀"NOR"。\n");
		if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("parry") != "liangyi-jian"
            || me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("你手里没有剑，无法使用"HIG"两仪剑诀"NOR"！\n");
        if( (int)me->query_skill("liangyi-jian", 1) < 500 )
                return notify_fail("你的正两仪剑法不够娴熟，无法施展出"HIG"两仪剑诀"NOR"。\n");
        if( (int)me->query_skill("sword", 1) < 500 )
                return notify_fail("你的基本剑法不够娴熟，无法施展出"HIG"两仪剑诀"NOR"。\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 500 )
                return notify_fail("你的玄天无极功不够娴熟，无法施展出"HIG"两仪剑诀"NOR"。\n");
		if( me->query_temp("xtwj/qinjian") )
			return notify_fail("你正在使用琴剑双绝，不能同时使用「两仪决」！\n");
		if( me->query_skill_mapped("force")!="xuantian-wuji")
                return notify_fail("你激发的内功非玄天无极功，无法施展出"HIG"两仪剑诀"NOR"。\n");
         
		if ( (int)me->query("max_neili") <15000)
                return notify_fail("你的最大内力不够，无法施展出"HIG"两仪剑诀"NOR"。\n");
        if ( (int)me->query("neili") < 1500)
                return notify_fail("你的真气不够，无法施展出"HIG"两仪剑诀"NOR"。\n");
        if ((int)me->query("jingli") < 1000)
                return notify_fail("你的精力不够，无法施展出"HIG"两仪剑诀"NOR"。\n");
		if ( me->query_temp("lyj/liangyi"))
                return notify_fail("你正在施展"HIG"两仪剑诀"NOR"。\n");
    
        me->add("neili", -random(1500));
        me->add("jingli", -200);
        
		message_vision(HIC"$N手中的"+weapon->query("name")+HIC"剑势一变，忽然施展出正两仪和反两仪的要诀，顿时剑势和先前迥然不同！\n"NOR,me, target);
 		message_vision(BLU"这两门武技派别不同，武功大异，但招式一出，却配合的天衣无缝，宛如一生寂寞之人忽遇知己般的喜欢！\n"NOR,me, target);

		me->add_temp("apply/attack",i/4);
		me->add_temp("apply/damage",i/4);
		me->add_temp("apply/sword",i/4);
		me->add_temp("apply/parry",i/4);
		me->add_temp("apply/defense",i/4);

        me->set_temp("lyj/liangyi",i);
		call_out("check_fight",1,me,i/20);
		
		return 1; 
}

void check_fight(object me,int count)
{
    object weapon, target;

    if (!me ) return;
    
    target = offensive_target(me);
    
	if (!target) 
	{		
	  call_out("finish",1);
	  return;
	}
	
    if( !me->is_fighting(target) 
		|| count < 0
        || environment(target)!=environment(me)
        || !me->query_temp("lyj/liangyi")) {
              call_out("finish",1);
			  return;
	}
    else if(me->query_skill_mapped("sword") != "liangyi-jian"||me->query_skill_mapped("parry") != "liangyi-jian"){
                tell_object(me, HIR"你临时改换剑法，决定不再使用「两仪剑诀」绝技。\n");
                call_out("finish",1);
				return;
    }
    else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
                tell_object(me, HIR"你临时改换武器，决定不再使用「两仪剑诀」绝技。\n");
                call_out("finish",1);
				return;
    }
    else if ((int)me->query("neili") < 1500 ){
                tell_object(me, HIR"你内力不济，只得缓缓收回「两仪剑诀」。\n");
                call_out("finish",1);
				return;
    }				
    else if ((int)me->query("jingli") < 1000 ){
                tell_object(me, HIR"你体力不支，只得缓缓收回「两仪剑诀」。\n");
                call_out("finish",1);
				return;
    }
    count=count-1;
	call_out("check_fight",1, me, count);
	return; 
    
}

void finish()
{
       int i;
	   object me = this_player();
       if (!me||!me->query_temp("lyj/liangyi")) return;
     
	   i=me->query_skill("liangyi-jian",1);
	   
	   
	   me->add_temp("apply/attack",-i/4);
	   me->add_temp("apply/damage",-i/4);
	   me->add_temp("apply/sword",-i/4);  
	   me->add_temp("apply/parry",-i/4);
	   me->add_temp("apply/defense",-i/4);
       me->delete_temp("lyj/liangyi"); 
       message_vision(HIC"$N方才一阵疾攻，不免颇耗内力，长吁一口气，剑势回归自然。\n"NOR, me);
	   return;

}

string perform_name(){ return HIY"两仪"HIC"剑决"NOR; }
int help(object me)
{
write(HIW"\n两仪剑法之"HIC"「两仪剑诀」："NOR"\n\n");
write(@HELP
	两仪剑诀是将正两仪剑和反两仪刀的招式进行融合后。
	大幅提升本身的攻击力，这种融合是两仪剑的绝顶招式
	正反两仪是易经的智慧体现。
	注意：解密后方可修习。因为两仪是具有和反两仪刀相
	符合的性质，所以不能和琴剑双绝互用。
	
	指令：perform sword.liangyi

要求：
	最大内力要求 15000 点以上；
	当前内力要求 1500 点以上；
	当前精力要求 1000 点以上；
	两仪剑法等级 500 以上；
	玄天无极等级 500 以上；
	基本剑法等级 500 以上；
	激发剑法为两仪剑法；
	激发招架为两仪剑法；
	激发内功为玄天无极功；
	手拿剑类兵器。
HELP
	);
	return 1;
}






















/*
#include <ansi.h>
inherit F_SSERVER;
//int remove_effect(object me);
int perform(object me, string arg)
{
    object weapon, weapon1, target;
    int skill, skill1;
    string msg;
	skill = me->query_skill("liangyi-jian", 1);
    skill1 = target->query_skill("liangyi-jian", 1);

    if(!arg) return notify_fail("你想和谁一起合璧？\n");
    if(!objectp(target = present(arg, environment(me))))
             return notify_fail("这里没有这个人。\n");

	if( !target->is_fighting() || !target->is_character() || !me->is_fighting())
                return notify_fail("合璧只能在战斗中使用。\n");
    if(!living(target))
                return notify_fail(target->name()+"已经无法战斗了。\n"); 
    if(target==me) return notify_fail("和自己合璧？\n"); 
    if(me->is_fighting(target))
                return notify_fail("你正在和"+target->name()+"打架呢。\n");            

    weapon = me->query_temp("weapon");  
    weapon1 = target->query_temp("weapon");  

    if(!weapon || weapon->query("skill_type") != "sword"
      || me->query_skill_mapped("sword") != "liangyi-jian"
      || me->query_skill_mapped("parry") != "liangyi-jian")
        return notify_fail("你现在无法使用「双剑合璧」。\n");

    if(!weapon1 || weapon1->query("skill_type") != "sword"
      || target->query_skill_mapped("sword") != "liangyi-jian"
      || target->query_skill_mapped("parry") != "liangyi-jian")
        return notify_fail(target->name()+"现在无法使用「双剑合璧」。\n");

   
    if(skill < 100 )
        return notify_fail("你的两仪剑法等级不够，不能使用「双剑合璧」。\n");
    
    if((int)me->query_skill("xuantian-wuji", 1) < 100 )
        return notify_fail("你的玄天无级功等级不够，不能使用「双剑合璧」。\n");       
    
    if((int)me->query("neili") < 500 )
        return notify_fail("你现在真气太弱，不能使用「双剑合璧」。\n");
    if((int)me->query("max_neili") < 1000 )
        return notify_fail("你现在内力太弱，不能使用「双剑合璧」。\n");

    if(me->query_temp("ly_hebi")) 
        return notify_fail("你已经在使用「双剑合璧」了。\n");

   if(target->query_temp("ly_hebi")) 
        return notify_fail(target->name()+"已经在和他人使用「双剑合璧」了。\n");

          
    if(me->query_temp("lyhebi_target")){
          if(me->query_temp("lyhebi_target")==target)
                return notify_fail("你已经做好和"+target->name()+"双剑合璧的准备了。\n");
          else{
               tell_object(me->query_temp("hebi_target"), YEL+me->name()+"不打算和你进行双剑合璧了。\n"NOR); 
                me->delete_temp("lyprepare_hebi");
                me->delete_temp("lyhebi_target");
               }
          }
     if(target->query_temp("lyprepare_hebi") && target->query_temp("lyhebi_target") ==me){
        message_vision(MAG"\n $N对$n使个眼色,手中"+weapon->name()+MAG+"和$n的"+weapon1->name()+MAG+"交错相击，双剑齐上，顿时只见剑光凌厉，威力大增！\n"NOR, me, target);
       me->delete_temp("lyprepare_hebi");
       me->delete_temp("lyhebi_target");
       target->delete_temp("lyprepare_hebi");
        target->delete_temp("lyhebi_target");
        me->set_temp("ly_hebi", 1); 
        target->set_temp("ly_hebi", 1); 
        me->add("neili", -300);
        target->add("neili", -300);
        me->add("jingli", -50);
        target->add("jingli", -50);
        remove_call_out("check_reply");
        me->start_call_out( (: call_other, __FILE__, "check_fight", me, target :), 1);
        target->start_call_out( (: call_other, __FILE__, "check_fight", target, me :), 1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), (skill+skill1)/2);
        target->start_call_out( (: call_other, __FILE__, "remove_effect", target :), (skill+skill1)/2);
        return 1;
        }
    message_vision(HIC"\n $N将手中"+weapon->name()+HIC"一横，暗示$n和$P一起运用双剑合璧。\n"NOR, me, target);
    tell_object(target, YEL"你如果愿意和"+me->name()+"进行双剑和壁，请也对"+me->name()+"下一次 ( perform hebi <player's id> ) 的命令。\n"NOR); 
    me->set_temp("lyprepare_hebi", 1);     
    me->set_temp("lyhebi_target", target);
      call_out("check_reply", 15, me); 
    return 1;
}

void check_fight(object me, object target)
{
    object weapon,weapon1;  
    
 	weapon = me->query_temp("weapon");  
      weapon1 = target->query_temp("weapon");  

    if(!weapon || weapon->query("skill_type") != "sword"
      || me->query_skill_mapped("sword") != "liangyi-jian"
      || me->query_skill_mapped("parry") != "liangyi-jian")
         call_out("remove_effect", 0, me);

    if(!weapon1 || weapon1->query("skill_type") != "sword"
      || target->query_skill_mapped("sword") != "liangyi-jian"
      || target->query_skill_mapped("parry") != "liangyi-jian")
		  call_out("remove_effect", 0, me);

     else if((!present(target->query("id"), environment(me))) ||
            !me->is_fighting() || !living(target) || !target->is_fighting()
            || target->is_ghost() || me->is_ghost() || !living(me)
            || !target->query_temp("ly_hebi"))
         call_out("remove_effect", 0, me);

    else call_out("check_fight", 1, me, target);
}
void check_reply(object me)
{
if (me->query_temp("lyprepare_hebi", 1)) {     
        me->delete_temp("lyprepare_hebi");     
        me->delete_temp("lyhebi_target");
            return notify_fail("似乎对方对你的暗示没有反应，你在只好取消了双剑合壁的请求。\n");
}   
}
void remove_effect(object me)
{
  if(me->query_temp("ly_hebi")){
    me->delete_temp("ly_hebi");
	return notify_fail(HIR"你双剑合璧完结，攻守也恢复正常了。\n"NOR);
       }
}

*/
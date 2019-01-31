//sanjue.c 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
  	string msg;
    int i,ap,dp,damage;
    object weapon;
	if( !target ) target = offensive_target(me);
	if( !target || !me->is_fighting(target) )
		return notify_fail("「修罗索命」只能在战斗中对对手使用。\n");
    weapon = me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="blade")
        return notify_fail("你必须使用刀时才能使出「修罗索命」！\n");
    if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功不够娴熟，不会使用「修罗索命」。\n");
	if( (int)me->query_skill("dodge", 1) < 100 )
		return notify_fail("你的基本轻功不够娴熟，不会使用「修罗索命」。\n");
	if( (int)me->query_skill("xiuluo-dao", 1) < 100 )
		return notify_fail("你的修罗刀法不够娴熟，不会使用「修罗索命」。\n");
    if(me->query_skill_mapped("blade")!="xiuluo-dao"||me->query_skill_mapped("parry")!="xiuluo-dao")
        return notify_fail("你没有激发修罗刀，不能使用「修罗索命」。\n");
	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功修为不够，不能使用「修罗索命」。\n");
    if( me->query_temp("sl/xiuluo"))
		return notify_fail("你正在使用「修罗索命」刀。\n");
	if( (int)me->query("max_neili", 1) < 1400 )
		return notify_fail("你现在内力太弱，不能使用「修罗索命」。\n");
	if( (int)me->query("neili", 1) < 400 )
		return notify_fail("你现在内力太弱，不能使用「修罗索命」。\n");
    if((int)me->query("jingli",1)< 200)
        return notify_fail("你现在精力太少，不能使用「修罗索命」。\n");
        i = me->query_skill("xiuluo-dao", 1);
        
       
		//增加伤害,350前有优势
        if (userp(me) && me->query_skill("xiuluo-dao",1)<350)
        {
          me->add_temp("apply/damage", i/4);
        }
		//玩家为出家人有优势
		if (userp(me)&&me->query("class")=="bonze")
		{
          me->add_temp("apply/damage", i/6);
          me->add_temp("apply/attack", i/3);
		  message_vision(YEL"$N高诵佛号，喝道，“阿弥陀佛！罪过！罪过！，同时手上的力道明显加强不少。\n"NOR,me,target);
		}		
        //me->add_temp("apply/attack", i); 	    
        msg = HIY "$N" HIY "脸上杀气大盛，一振手中的" + weapon->query("name")+HIY "，唰唰数刀试图将$n" + HIY "团团裹住！\n" NOR;
        ap = me->query_skill("blade",1);
		if (me->query("class")=="bonze")
		   ap=ap+me->query_skill("huddhism",1);
        dp = target->query_skill("parry",1);
        damage = ap*4+ random(ap);
		damage=damage*2;
	  if (damage>4000) damage=4000+(damage-4000)/100;
	
      if (ap / 2 + random(ap) > dp || random(me->query_str())>target->query_con()/2)
        {
               
				msg+=HIC"$n一不小心为$N的刀光所困，顿时手忙脚乱起来。\n"NOR;				
                target->start_busy(2+random(2));
				if (me->query_skill("buddhism")>=200&&me->query("class")=="bone"&&me->query_skill("xiuluo-dao")>150)
				{
					 msg+= HIR "$N有心除魔，刀光闪烁，就听见$n" HIR "惨叫连连，一阵阵血雨自" HIR"亮白的刀光中溅出！\n" NOR;
					 target->receive_damage("qi",damage,me);
					 message_vision(msg,me,target);
					 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				}
        } else
        {               
                me->start_busy(1);
                msg += CYN "可是$p" CYN "眼明手快，只听叮叮当当响起了一串"
                       CYN "刀鸣，$p" CYN "将$P" CYN "的招式全部挡开！\n" NOR;
        }
	    message_vision(msg, me, target);
        me->add("neili", -100);
        me->add("jingli",-50);
		me->set_temp("sl/xiuluo",1);
        
		if (me->is_fighting()&&objectp(target)&&me->query("class")=="bonze")
        {
            message_vision(YEL"$N又再次高诵佛号，喝道，“既然你如此顽冥不化，今天我就替世人除魔卫道。\n"+HIC"$N反手一刀挥出，直逼$n的胸口劈去！\n"NOR,me,target);
			target->receive_damage("qi",damage,me);
            target->receive_wound("qi",damage/3,me);
	        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        }
		me->start_busy(1);
            
       // me->add_temp("apply/attack", -i); 
		if (userp(me)&&me->query_skill("xiuluo-dao",1)<350)
        {
          me->add_temp("apply/damage", -i/4);
        }
		if (userp(me)&&me->query("class")=="bonze")
		{
          me->add_temp("apply/damage", -i/6);
          me->add_temp("apply/attack", -i/3);
		}
		me->delete_temp("sl/xiuluo");
        me->start_perform(3,"修罗索命");
        
      return 1;
}
string perform_name(){ return HIB"修罗索命"NOR; }
int help(object me)
{
         write(HIB"\n修罗刀法之「修罗索命」："NOR"\n");
        write(@HELP
	修罗索命乃是修罗老祖为了除魔卫道所遗留下来的少林入门武技。
	修罗索命对于出家人来说，因心中有所局限，所以多以牵制为主
	刀光凛冽，霍霍冷艳，刀法施展后先困敌，待对方觉醒，为其留
	一条活路，若实在顽冥不化，则最后一刀毙命。出家人有优势且
	与所修的佛法关联。
	
	perform blade.xiuluo

要求：
	基本内功：100
	基本轻功：100
	修罗刀法：100
	基本内功：100
	最大内力：1400
	当前内力：500
	当前精力：200
	需激发修罗刀。       
HELP
        );
        return 1;
}


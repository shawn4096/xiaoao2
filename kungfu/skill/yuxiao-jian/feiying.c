// feiying.c
// YUJ@SJ 2002-07-12

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int lvl, qi2,i;

        lvl = me->query_skill("yuxiao-jian", 1);
        lvl += me->query_skill("tanzhi-shentong", 1);
        lvl += me->query_skill("luoying-zhang", 1);
        lvl += me->query_skill("lanhua-shou", 1);
        lvl += me->query_skill("xuanfeng-tui", 1);
        lvl += me->query_skill("suibo-zhuliu", 1);
        lvl /= 6;
        if (!target) target = offensive_target(me);

        if (!objectp(target)
        || !me->is_fighting(target)
		||!living(target))
                return notify_fail("你只能对战斗中的对手使用飞影。\n");

        weapon = me->query_temp("weapon");

        if (!weapon || !(weapon->id("xiao")))
                return notify_fail("你手里没有拿箫，无法施展出飞影。\n");

        if (me->query_skill("yuxiao-jian", 1) < 500)
                return notify_fail("你的玉箫剑法不够娴熟，无法施展出飞影。\n");

        if (me->query_skill("qimen-bagua", 1) < 200)
                return notify_fail("你的奇门八卦不够娴熟，无法施展出飞影。\n");

        if (me->query_skill("tanzhi-shentong", 1) < 500)
                return notify_fail("你的弹指神通不够娴熟，无法施展出飞影。\n");

        if (me->query_skill("lanhua-shou", 1) < 500)
                return notify_fail("你的兰花拂穴手不够娴熟，无法施展出飞影。\n");

        if (me->query_skill("luoying-zhang", 1) < 500)
                return notify_fail("你的落英神剑掌不够娴熟，无法施展出飞影。\n");

        if (me->query_skill("xuanfeng-tui", 1) < 500)
                return notify_fail("你的旋风扫叶腿不够娴熟，无法施展出飞影。\n");

        if (me->query_skill("bihai-chaosheng", 1) < 500)
                return notify_fail("你的碧海潮生功火候不够，无法施展出飞影。\n");

        if (me->query_skill("suibo-zhuliu", 1) < 500)
                return notify_fail("你的随波逐流火候不够，无法施展出飞影。\n");

        if ( me->query_skill_mapped("sword") != "yuxiao-jian"
        || (me->query_skill_mapped("parry") != "yuxiao-jian"&& me->query_skill_mapped("parry") != "tanzhi-shentong")
        || me->query_temp("thd/feiying"))
                return notify_fail("你暂时无法使用飞影绝技。\n");

        if (me->query("max_neili") < 7500)
                return notify_fail("你的内力不够，无法施展出飞影。\n");

        if (me->query("neili") < 4000)
                return notify_fail("你的真气不够，无法施展出飞影。\n");

        if (me->query("jingli") < 2500)
                return notify_fail("你的精气不够，无法施展出飞影。\n");

        me->set_temp("thd/feiying", 1);
      //  message_vision(HIW"\n$N深吸一口气，使出桃花绝技「飞影」攻向$n！\n\n"NOR,me, target);
        
        if (me->query("thdjj/ronghe")=="pass")
			message_vision(HBRED+HIW"\n$N深吸一口气，使出桃花岛玉箫剑法「飞影」绝技攻向$n！\n\n"
		                              +"$N已得桃花岛绝技精髓，飞影的威力更上一层楼。\n"NOR,me, target);
		else message_vision(HIW"\n$N深吸一口气，使出桃花绝技「飞影」攻向$n！\n\n"NOR,me, target);

		lvl = to_int( lvl/3.0 * lvl/275.0);//4 -> 3,350->250 
		if (me->query("thdjj/ronghe")=="pass") 
	    {
			//lvl=1.5*lvl;
			lvl=2*lvl;
			i=3;

		}else i=1;
        

        me->add_temp("apply/attack", lvl);

		me->add_temp("apply/damage", lvl/2);

        message_vision(HIG"$N手中的"+weapon->query("name")+HIG"如行云流水一般，向$n潇洒地攻去！"NOR,me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); //增加一招，凸显玉箫剑法的迅捷
        message_vision(HIG"$n只觉得四面八方都是箫影，顿时不知所措！\n"NOR,me, target);
        weapon->unequip();
        me->prepare_skill("hand");
        me->prepare_skill("strike");
       // me->prepare_skill("cuff");
        me->prepare_skill("finger");
        me->prepare_skill("leg");
        me->prepare_skill("claw");
        if (me->is_fighting(target)) {
                me->prepare_skill("hand", "lanhua-shou");
                qi2 = target->query("qi");
                me->add_temp("apply/hand", lvl*2);
				message_vision(HIC"\n$N把"+weapon->query("name")+HIC"插回腰间，双手如清风拂晓般向$n拂去！"NOR,me, target);
                COMBAT_D->do_attack(me, target, 0, i);
				me->add_temp("apply/hand", -lvl*2);
                if (target->query("qi") < qi2)
                        message_vision(HIC"$N正好拂到了$n的小腹关元穴！$n觉得真气无法重新凝聚！\n"NOR,me, target);
        }
        if ( me->is_fighting(target)) {
                me->prepare_skill("hand");
                me->prepare_skill("strike","luoying-zhang");
                qi2 = target->query("qi");
                me->add_temp("apply/strike", lvl*2);
                message_vision(HIM"\n$N倏地转手为掌，$n觉得到处是掌影，虚虚实实无法捉摸。"NOR,me, target);
				COMBAT_D->do_attack(me, target, 0, i);

				me->add_temp("apply/strike", -lvl*2);
                if (target->query("qi") < qi2)
                message_vision(HIM"$N突然打在$n后心至阳穴上，$n不由得吐了口鲜血。\n"NOR,me, target);
        }
        if ( me->is_fighting(target)) {
                me->prepare_skill("strike");
                me->prepare_skill("leg","xuanfeng-tui");
                qi2 = target->query("qi");
                me->add_temp("apply/leg", lvl*2);
                message_vision(HIR"\n$N尚未收掌，旋风扫叶腿已经攻到$n面前！"NOR, me, target);
				COMBAT_D->do_attack(me, target, 0, i);

				me->add_temp("apply/leg", -lvl*2);
                if (target->query("qi") < qi2)
                message_vision(HIR"$N连出好几腿，$n连连后退，无暇出力！\n"NOR,me, target);
        }
        if (me->is_fighting(target)) {
                me->prepare_skill("leg");
                me->add_temp("apply/finger", lvl*2);
                me->prepare_skill("finger","tanzhi-shentong");
			    message_vision(HIY"\n$N收腿之际，突然使出弹指神通的功夫，一指向$n太阳穴戳去！收掌出指，连点$n身前大穴！"NOR,me, target);
				COMBAT_D->do_attack(me, target, 0, 3);
                me->add_temp("apply/finger", -lvl*2);
                qi2 = target->query("qi");
                if (target->query("qi") < qi2)					
                message_vision(HIY"$N$n摇摇晃晃，举步维艰。\n"NOR,me, target);
        }  
	
		if (objectp(target)
			&&me->is_fighting(target)
			&&me->query("thdjj/ronghe")=="pass" 
			&&me->query("quest/jiuyin2/pass"))
		{
          switch(random(3)){
              case 0:
                if (me->query_skill("cuixin-zhang",1)>449 && me->is_fighting(target)) {
                    me->prepare_skill("finger");
				    me->prepare_skill("strike","cuixin-zhang");                                      
			    	//me->prepare_skill("strike");
				    me->add_temp("apply/strike", lvl*2);
			    	message_vision(RED"\n$N突然使出九阴真经中「摧心掌」的功夫,收指出掌拍向$n的胸口膻中大穴！"NOR,me, target);
			    	message_vision(HBRED"\n$n躲闪不及，顿时为$N拍中，一阵撕心裂肺的剧痛传来！"NOR,me, target);
					target->add_condition("no_exert",1+random(1));
					target->receive_damage("qi",lvl*2,me);
					target->receive_wound("qi",lvl,me);
					me->add_temp("apply/damage",(int)lvl/4);
					COMBAT_D->do_attack(me, target, 0, 3);
                    me->add_temp("apply/damage",-(int)lvl/4);
                   
					me->add_temp("apply/strike", -lvl*2);
                    qi2 = target->query("qi");              
                    if (target->query("qi") < qi2)					
                    message_vision(HIY"$N一掌拍向$n的心窝！$n哇地吐出一口鲜血。\n"NOR,me, target);
					break;
			     }
				 break;
			  case 1:
			  case 2:
                 if (me->query_skill("jiuyin-baiguzhua",1)>449) {
                    me->prepare_skill("finger");
                    me->prepare_skill("claw","jiuyin-baiguzhua");
					me->add_temp("apply/claw", lvl*2);
			    	message_vision(HBBLU"\n$N指法一变成爪，突然使出九阴真经上的功夫"+HIW"「九阴白骨爪」!\n"NOR,me, target);
					if (random(me->query_dex(1))>target->query_dex(1)/3)
					{
			    	  message_vision(MAG"\n$n只觉$N的指风犀利，似乎带有剧毒，心神恍惚间'咔嚓'一声被抓破头盖骨！，\n"NOR,me, target);
					  target->apply_wound("qi",lvl*3,me);
                      target->apply_condition("no_perform",2+random(1));
					}
			    	me->add_temp("apply/damage",lvl/4);
					COMBAT_D->do_attack(me, target, 0, 3);
                    me->add_temp("apply/damage",-lvl/4);
					me->add_temp("apply/claw", -lvl*2);
                   // qi2 = target->query("qi");          
                    if (objectp(target)&&!random(5)){
						target->receive_damage("qi",random(3000),me);
						target->receive_wound("qi",random(1000),me);
                        message_vision(HIY"$N爪影闪烁，招招不离$n的头顶，$n一不小心，被撕去一块头皮。\n"NOR,me, target);                    
					}				
				   
                }
				break;
				
				  //case 2:  预留接口，九阴的狠毒招式。
		   }
	   }

	
	
	    message_vision(HIW"\n$N飞影使完，手一晃将"+weapon->query("name")+HIW"拿回手中。\n"NOR,me);
        weapon->wield();
		me->start_busy(2+random(2));
        me->add_temp("apply/attack", -lvl);
	    target->set_temp("faint_by",me);//增加一个标记，避免莫名其妙死亡 by renlai

		me->add_temp("apply/damage", -lvl/2);
        me->add("neili", -450);
        me->add("jingli", -180);
        me->start_perform(5, "「飞影」");
        me->delete_temp("thd/feiying");
        return 1;
}

string perform_name(){ return HIW"飞影绝技"NOR; }

int help(object me)
{
        write(HIW"\n玉箫剑法之「飞影绝技」："NOR"\n\n");
        write(@HELP
	玉箫剑法乃是五绝之东邪黄药师的独门绝技，
	招式玄幻，缤纷灿烂，乃是集桃花岛所有武技
	的大乘，倘若解开桃花岛一系列小谜题后，飞
	影的攻击将发生不断的飞越，当然若解开桃花
	岛绝世谜题，则会发生本质的不同。
	
	指令：perform sword.feiying

要求：
	当前内力需求 4000 以上；
	最大内力需求 7500 以上；
	当前精力需求 2500 以上；
	玉箫剑法等级 500 以上；
	奇门八卦等级 200 以上；
	弹指神通等级 500 以上；
	兰花拂穴手等级 500 以上；
	落英神剑掌等级 500 以上；
	旋风扫叶腿等级 500 以上；
	碧海潮生功等级 500 以上；
	随波逐流等级 500 以上；
	手持箫类武器。

HELP
        );
        return 1;
}



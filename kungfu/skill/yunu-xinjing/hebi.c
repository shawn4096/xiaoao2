// hebi.c 合壁
// by Yu Jue 98/7
// Modify by River 98/10
// server 开放单人Hebi
//合璧为合击之术，互博植入剑法中
// 
#include <ansi.h>
string exert_name(){ return HIC"双剑合壁"NOR; }
int exert(object me, object target)
{
        object *enemy;
        int i,j;
        mapping fam,fam1;
        object weapon1,weapon = me->query_temp("weapon");

        if (!target || (target == me && !me->query("double_attack"))) return notify_fail("你要和谁合壁？\n");
    
        if (!target || (target == me && me->query("gender")=="男性")) return notify_fail("你要和谁合壁？\n");

		if (!present(target,environment(me))) return notify_fail("这里有这个人吗？\n");
        
		if (me->query_temp("hebi")) return notify_fail("你已经在合壁了。\n");
        if (target->query_temp("hebi")) return notify_fail("你已经在合壁了。\n");
        
		if (me->query("jingli") < 200) return notify_fail("你的精力不够了。\n");
        if (target->query("jingli") < 200) return notify_fail("对方的精力不够了。\n");
        if (!me->is_fighting()) return notify_fail("合壁只能在战斗中使用。\n");
        if (me->is_fighting(target)) return notify_fail("你正在和对方打架，合壁干什么？\n");
        //if ((int)me->query_temp("gumu_suxin")) return notify_fail("你现在正在使用「玉女素心」绝技。\n");
        //if((int)target->query_temp("gumu_suxin")) return notify_fail("对方现在正在使用「玉女素心」绝技。\n"); 

        fam= me->query("family");
        fam1= target->query("family");
        
		if (!fam || fam["family_name"] != "古墓派")
                return notify_fail("你不是古墓弟子怎么能合壁？\n");
        if (!fam1 || fam1["family_name"] != "古墓派")
                return notify_fail("对方不是古墓弟子，不能和你合壁！\n");
        if(me->query_skill("yunu-xinjing", 1) < 550 )
                return notify_fail("你的玉女心经不够娴熟,不足550级，不能使用合壁。\n");
        if(me->query("jingli") < 1500 )
                return notify_fail("你的当前精力不够1500，不能使用合壁。\n");
        if(me->query("neili") < 1500 )
                return notify_fail("你的当前内力不够1500，不能使用合壁。\n");

        if((string)me->query("gender") =="女性" 
			 && (int)me->query_skill("yunu-jianfa", 1) < 550 )
                return notify_fail("你的玉女剑法不够娴熟,不足550级，不会使用合壁。\n");
        if((string)me->query("gender") =="男性" 
			 && (int)me->query_skill("quanzhen-jianfa", 1) < 550 )
                return notify_fail("你的全真剑法不够娴熟，不足550级,不会使用合壁。\n");
//女性激发玉女，男性激发全真剑法
        if ((string)me->query("gender")=="女性" 
			&& (!weapon || weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("sword") != "yunu-jianfa"
			|| me->query_skill_mapped("parry") != "yunu-jianfa"))
                return notify_fail("你现在无法合壁。\n");
        
		if ((string)me->query("gender")=="男性" 
			&& (!weapon || weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("sword") != "quanzhen-jianfa"
			|| me->query_skill_mapped("parry") != "quanzhen-jianfa"))
                return notify_fail("你现在无法合壁。\n");
//非夫妻不能合璧
        if( me->query("id") != target->query("marry/id") && !me->query("double_attack"))
                return notify_fail("对方不是你的配偶，所以你两无法达到双剑合壁所需要的意境。\n");

        enemy = me->query_enemy();
        i = sizeof(enemy);
        
		while (i--) if (target->is_fighting(enemy[i])) break;
			if (i<0) return notify_fail(target->name()+"并没有和你的对手在交战。\n");
		
        if((string)me->query("gender")=="男性" 
         && (int)target->query_skill("yunu-jianfa", 1) < 550)
                return notify_fail("对方的玉女剑法不够娴熟，不足550级，不会使用合壁。\n");
        if((string)me->query("gender")=="女性"
         && (int)target->query_skill("quanzhen-jianfa", 1) < 550)
                return notify_fail("对方的全真剑法不够娴熟，不足550级，不会使用合壁。\n");

        weapon = target->query_temp("weapon");
        
		if ((string)target->query("gender")=="女性"
			&& (target->is_busy() || !weapon || weapon->query("skill_type") != "sword"
			|| target->query_skill_mapped("sword") != "yunu-jianfa"
			|| target->query_skill_mapped("parry") != "yunu-jianfa"))
                return notify_fail("对方没有激发玉女剑法，现在无法与你合壁。\n");
        if ((string)target->query("gender")=="男性" 
			&& (target->is_busy() || !weapon || weapon->query("skill_type") != "sword"
			|| target->query_skill_mapped("sword") != "quanzhen-jianfa"
			|| target->query_skill_mapped("parry") != "quanzhen-jianfa"))
                return notify_fail("对方现在无法合壁。\n");

        if (target == me && me->query("quest/gm/ynjf/hubo/pass"))
			message_vision(HBYEL+HIW "\n$N神态清冷，将玉女剑法的招式和全真剑法的招式以左右互搏之术同时使出，攻守兼备，剑气弥漫。\n"
			+"威力大增，远比先前双剑合璧威力更大，玉女心经最后一章的武功奥秘至此方显。\n\n" NOR, me);
        else
			message_vision(HIY "\n$N心中满溢柔情密意，回首凝视$n，二人皆不守而皆守，双剑之势骤然而长。\n\n" NOR, me, target);
        me->set_temp("hebi", 1);
        target->set_temp("hebi", 1);
        me->receive_damage("jingli", 500);
        target->receive_damage("jingli", 500);
		me->add("neili",-800);
		target->add("neili",-800);
 //       me->start_busy(1);
 //      target->start_busy(1);
 //统一调整到3-》5适当
        if ((string)me->query("gender")=="女性")
			i = me->query_skill("yunu-jianfa", 1) / 5;
        if ((string)me->query("gender") =="男性")
			i = me->query_skill("quanzhen-jianfa", 1) / 5;
        if ((string)target->query("gender") =="男性")
			j = target->query_skill("quanzhen-jianfa", 1) / 5;
        if ((string)target->query("gender") =="女性")
			j = target->query_skill("yunu-jianfa", 1) / 5;

        me->add_temp("apply/parry", i);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/sword", i);
        me->add_temp("apply/damage", i);
        me->add_temp("apply/dodge", i);

        target->add_temp("apply/parry", j);
        target->add_temp("apply/attack", j); 
        target->add_temp("apply/sword", j);
        target->add_temp("apply/damage", j);
        target->add_temp("apply/dodge", j);

        weapon = me->query_temp("weapon");
        weapon1 = target->query_temp("weapon");
        if( me->query("gender") == "男性" 
         && weapon->query("id") == "junzi jian" 
         && target->query("gender") == "女性" 
         && weapon1->query("id") =="shunu jian")
		{
          me->set_temp("double_attack", 1);
          target->set_temp("double_attack", 1);
        }
        if( me->query("gender") == "女性" 
         && weapon->query("id") == "shunu jian" 
         && target->query("gender") == "男性" 
         && weapon1->query("id") =="junzi jian")
		{
          me->set_temp("double_attack", 1);
          target->set_temp("double_attack", 1);
        }
        call_out("hebi", 1, me, target, environment(me), i, j, (i+j)/5);
        return 1;
}

void hebi(object me, object target, object env, int i, int j, int count)
{
        object weapon;

        if (!me && !target) return;
        
		if (!me && target) 
		{
            tell_room(env, HIY "\n合壁自动瓦解。\n" NOR);

			target->add_temp("apply/parry",- j);
			target->add_temp("apply/attack", -j); 
			target->add_temp("apply/sword",- j);
			target->add_temp("apply/damage",- j);
			target->add_temp("apply/dodge",- j);


			target->delete_temp("double_attack");
			target->delete_temp("hebi");
			return;
        }
        if (me && !target) 
		{
                tell_room(env, HIY "\n合壁自动瓦解。\n" NOR);

        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);

                me->delete_temp("double_attack");
                me->delete_temp("hebi");
                return;
        }
        weapon = me->query_temp("weapon");
        if ((string)me->query("gender") =="男性" 
        && (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "quanzhen-jianfa"
        || me->query_skill_mapped("parry") != "quanzhen-jianfa")) {
                tell_room(env, HIY "合壁自动瓦解。\n" NOR);

        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);

                me->delete_temp("hebi");
                me->delete_temp("double_attack");

        target->add_temp("apply/parry",- j);
        target->add_temp("apply/attack", -j); 
        target->add_temp("apply/sword",- j);
        target->add_temp("apply/damage",- j);
        target->add_temp("apply/dodge",- j);

                target->delete_temp("hebi");
                target->delete_temp("double_attack");
                return;
        }
        if ((string)me->query("gender") =="女性" 
        && (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yunu-jianfa"
        || me->query_skill_mapped("parry") != "yunu-jianfa")) {
                tell_room(env, HIY "合壁自动瓦解。\n" NOR);
  


        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);

                me->delete_temp("hebi");
                me->delete_temp("double_attack");

        target->add_temp("apply/parry",- j);
        target->add_temp("apply/attack", -j); 
        target->add_temp("apply/sword",- j);
        target->add_temp("apply/damage",- j);
        target->add_temp("apply/dodge",- j);

                target->delete_temp("hebi");
                target->delete_temp("double_attack");
                return;
        }
        weapon = target->query_temp("weapon");
        if ((string)target->query("gender") =="男性"
        && (!weapon || weapon->query("skill_type") != "sword"
        || target->query_skill_mapped("sword") != "quanzhen-jianfa"
        || target->query_skill_mapped("parry") != "quanzhen-jianfa")) {
                tell_room(env, HIY "合壁自动瓦解。\n" NOR);

        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);


                me->delete_temp("hebi");
                me->delete_temp("double_attack");

                target->delete_temp("double_attack");

        target->add_temp("apply/parry",- j);
        target->add_temp("apply/attack", -j); 
        target->add_temp("apply/sword",- j);
        target->add_temp("apply/damage",- j);
        target->add_temp("apply/dodge",- j);

                target->delete_temp("hebi");
                return;
        }
        if ((string)target->query("gender") =="女性" 
        && (!weapon || weapon->query("skill_type") != "sword"
        || target->query_skill_mapped("sword") != "yunu-jianfa"
        || target->query_skill_mapped("parry") != "yunu-jianfa")) {
                tell_room(env, HIY "合壁自动瓦解。\n" NOR);
        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);
                me->delete_temp("hebi");
                me->delete_temp("double_attack");
                target->delete_temp("double_attack");
        target->add_temp("apply/parry",- j);
        target->add_temp("apply/attack", -j); 
        target->add_temp("apply/sword",- j);
        target->add_temp("apply/damage",- j);
        target->add_temp("apply/dodge",- j);
                target->delete_temp("hebi");
                return;
        }
        if (environment(me) != env || environment(target) != env) {
                tell_room(env, HIY "合壁自动瓦解。\n" NOR);
        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);
                me->delete_temp("hebi");
                me->delete_temp("double_attack");
                target->delete_temp("double_attack");
        target->add_temp("apply/parry",- j);
        target->add_temp("apply/attack", -j); 
        target->add_temp("apply/sword",- j);
        target->add_temp("apply/damage",- j);
        target->add_temp("apply/dodge",- j);
                target->delete_temp("hebi");
                return;
        }
        if (!me->is_fighting() || !target->is_fighting() || count < 1)
        {
        if (target == me)
                {
                message_vision(HIY "\n$N合壁完毕，从容收招。\n" NOR, me);
        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);
                  me->delete_temp("hebi");
                  me->delete_temp("double_attack");
                  target->delete_temp("double_attack");
        target->add_temp("apply/parry",- j);
        target->add_temp("apply/attack", -j); 
        target->add_temp("apply/sword",- j);
        target->add_temp("apply/damage",- j);
        target->add_temp("apply/dodge",- j);
                  target->delete_temp("hebi");
                }
                else
                {
                message_vision(HIY "\n$N和$n相视一笑，各自收招。\n" NOR, me, target);
        me->add_temp("apply/parry",- i);
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/sword",- i);
        me->add_temp("apply/damage",- i);
        me->add_temp("apply/dodge",- i);
                  me->delete_temp("hebi");
                  me->delete_temp("double_attack");
                  target->delete_temp("double_attack");
        target->add_temp("apply/parry",- j);
        target->add_temp("apply/attack", -j); 
        target->add_temp("apply/sword",- j);
        target->add_temp("apply/damage",- j);
        target->add_temp("apply/dodge",- j);
                  target->delete_temp("hebi");

                }
                return;
        }
        call_out("hebi", 1, me, target, env, i, j, count - 1);
}
int help(object me)
{
write(HIW"\n玉女心经「双剑合壁」："NOR"\n");
write(@HELP
	此式要求夫妻二人同时施展方能使用，男使全真剑法
	女使玉女素心剑法，利用全真剑法和玉女素心剑法相
	辅相成的巧合施展完美无瑕的招数，以弱胜强。如果
	身负左右互搏之术，且在小龙女处解开双剑合璧互博
	的秘密，则个人能将玉女心经最后一章的武功心法融
	入到剑法之中，威力更胜双人合击的威力，此时古墓
	武功威力彻底释放！

	指令: yun hebi

 要求：
	当前内力要求 1500 以上；
	当前精力要求 1500 以上；
	玉女剑法 (女) 550 以上；
	全真剑法 (男) 550 以上；
	玉女心经要求  550 以上：
	手持剑类武器：

HELP
);
return 1;
}

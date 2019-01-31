// huagong.c 化功
// by snowman@SJ
// modify by snowman@SJ 25/02/2000
// Modified by darken@SJ

#include <ansi.h>

inherit F_SSERVER;

string exert_name(){ return HIG"化精"NOR; }
void huagong(object me, object target);

int exert(object me, object target)
{        
        object room,ob;
        
        if( !target) target = offensive_target(me);
        if( !target || !objectp(target) || !me->is_fighting(target) || !living(target))
                return notify_fail("化精只能在战斗中对对手使用。\n");
                   
        if( !objectp(target) || target->query("id") == "mu ren" )
                return notify_fail("用火把来烧比较快。\n");
        
       // if( !userp(target))
               // return notify_fail("你不能对他使用化精！\n");

        if(!( room = find_object("/d/taishan/fengchan")) )
                room = load_object("/d/taishan/fengchan");
        if( objectp(ob = present("zhong shentong", room)) ) {
                if(target->query("id") == ob->query("winner"))
                        return notify_fail("大胆！竟敢对中神通运用化功大法！\n");
        }

        if( !living(target) || ! target->query("can_speak"))
                return notify_fail("它不是活物。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你必须使用空手和化功大法，方能抓住对手。\n");

        if( me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("你必须使用抽髓掌，方能抓住对手。\n");

        if( (int)me->query_skill("huagong-dafa",1) < 350 )
                return notify_fail("你的功力不够，不能施展化精！\n");
        if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("你的内功不够，不能施展化精！\n");
        if( (int)me->query_skill("poison",1) < 200 )
                return notify_fail("你体内的毒素不够，不能施展化精！\n");

        if((int)target->query("max_jingli") <= 0 || target->query("combat_exp") < me->query("combat_exp")/2)
                return notify_fail( target->name() +"没有任何精力可化！\n");

        message_vision(BLU"突然$N双手挥舞，状若疯魔，仰天阴阴一声长笑，骨节一阵爆响，两股若隐若现的浅蓝色气流裹向$n的头部！\n" NOR, me, target );

        if( random(me->query_int()) > target->query_int()/2) {
            message_vision(HBRED"$n不知$N是什么意图，竟然伸出双掌拍来挡格，双方对接间，$n似乎想起了什么，暗叫一声不好！\n" NOR, me, target );
            me->start_busy(2);
            target->start_busy(2);
            call_out("huagong", 2, me, target, 1);
        }

        if( !target->is_killing(me->query("id")) ){ 
                me->kill_ob(target);
                target->kill_ob(me);              
        }

        me->start_exert(3);

        return 1;
}

void huagong(object me, object target)
{
        object victim, *people;
        int i,j;

        if (!me || !target) return;
        if (!me->query("quest/hgdf/powerup"))
         { 
			me->start_busy(2);
            i = 50 + random(50);
		 }
		 else i=100+random(100);
        target->start_busy(2);
        if (target->query("max_jingli") < 1 || target->query_temp("huagong/count") > 10) {
            message_vision(RED"$n被$N化尽了丹元，软软的摊在地上。\n"NOR, me, target);
            message_vision(RED"$N哈哈一笑，松开了手。\n"NOR, me, target);
            
            target->add("max_jingli", -i);
            target->add("eff_jingli", -i);
            target->add("jingli", -i);
            if (target->query("max_jingli") < 0) target->set("max_jingli",0);
			target->delete_temp("huagong/count");
			target->remove_all_enemy();
            target->unconcious();            
            me->remove_all_enemy();
            
            return;
        }
        if (target->query_skill("douzhuan-xingyi",1) > 450 || 
            target->query_skill("qiankun-danuoyi",1) > 450){
             people = all_inventory(environment(me));
             i = random(sizeof(people));
             for (j=0;j<=i ;j++ )
             {
				victim = people[i];
             //   if (victim != me && victim != target && victim->is_character() && living(victim) && !wizardp(victim)) 
				if (victim != me && victim != target && !victim->is_character() && living(victim) && !wizardp(victim)) 
				{
					message_vision(HBRED"$N灵机一动，一牵一引，把$n拉转到身前，接过了对手的魔掌！\n"NOR, target, victim);
					target->remove_all_enemy();
					me->remove_all_enemy();
					huagong(me, victim);
					return;
                }
             }
			
        }
        if (random(target->query("neili")) > me->query("neili")/2) {
            message_vision(RED"$n拼著大耗真元，将全身内力用力向$N一送，挣开了$N的掌握。\n"NOR, me, target);
            target->add("max_neili",-5-random(5));
            return;
        }
        message_vision(RED"$n使劲挣扎，就是无法脱出$N掌握，只觉得精力不断流失。\n"NOR, me, target);
        //me->add("potential", (me->query_skill("force") + random(me->query_skill("poison")))/20);
        i = 20 + random(11);
        target->add("max_jingli", -i);
        target->add("eff_jingli", -i);
        target->add("jingli", -i);
        target->add_temp("huagong/count", 1);
        call_out("huagong", 2, me, target);
}


int help(object me)
{
          write(BLU"\n化功大法之「化精」绝技："NOR"\n");
          write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	化功大法吸人内力，阴毒异常，江湖上人提起，无不谈虎色变。
	这化功大法之化功绝技乃是以毒化去对方内力的效果，通过毒气
	运用，附加以高深的内功在于对方接触过程中不断侵蚀对方经脉，
	伤害其功力和最大功力，端的是阴险无比。解密化功大法的奥秘
	后，会出现飞跃。斗转星移和乾坤大挪移对此招有一定克制功效，		 
	最终判断双方功力。玩家当慎用。
	
	指令：yun huajing

要求:
	化功大法 350 级；
	毒技等级 200 级；
	当前内力 1500 点；
	最大内力 5000 点。
	需激发掌法为抽髓掌,
	命中悟性有关。

HELP
);
return 1;
}

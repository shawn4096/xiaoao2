// guiyuan-tunafa.c 铁掌帮 归元吐纳法
//增加内功效果 By Spiderii@ty 参考tz player tekken建议
//哪知他刚一用劲，掌心立感烫热无比，犹似握到了一块红炭，急忙撤手，
//手掌却已被对方牢牢抓住，这股烫热宛如一直烧到了心里，忍不住大叫。
//鲁有脚用力挣扎，裘千仞那肚皮却有极大吸力，牢牢将他脑袋吸住，
//惊惶之中只觉脑门渐渐发烫，同时双手也似落入了一只熔炉之中，既痛且热。
//（第一段是杨康不知天高地厚，要和裘千仞比掌力，第二段是裘千仞和鲁有脚的过招片段。

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        int nf;
        nf = (int)me->query_skill("force", 1);

        if ( nf < 10)
                return notify_fail("你的基本内功火候还不够，无法领会归元吐呐法。\n");

        if ((int)me->query_skill("guiyuan-tunafa", 1) > me->query_skill("force", 1) + 10
         && me->query_skill("guiyuan-tunafa", 1) >= 200 )
                return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
        if((int)me->query_skill("guiyuan-tunafa", 1) >= 200 ) {
                if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
                        me->improve_skill("guiyuan-tunafa", (int)me->query_int());
                        me->add("neili", -100); 
                        me->add("potential", -1*(1+random(3)));
                        return 1;
                }
                else return notify_fail("你现在的修为不足以提高归元吐呐法了。\n");
        }
        else return notify_fail("你现在的归元吐呐法修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"guiyuan-tunafa/" + func;
}

mapping exercise_msg(object me)
{
        return ([
                "status_msg" : YEL + me->name()+"盘膝坐下，采取天地之精华，身周气流暗涌，腾现茫茫白雾"NOR,
                "start_my_msg" : "你盘膝坐下，暗运内力，试图采取天地之精华，只觉得四周暗潮渐生，天地顿合，四周白茫茫一片。\n",
                "start_other_msg" :HIY + me->name()+"盘膝坐下，暗运内力，试图采取天地之精华，只觉得四周暗潮渐生，天地顿合，四周白茫茫一片。\n"NOR,
                "halt_msg" : HIY"$N内息一转，迅速收气，缓缓收功站了起来。\n"NOR,
                "end_my_msg" : "你双眼微闭，缓缓将天地精华之气吸入体内,见天地恢复清明，收功站了起来。\n",
                "end_other_msg" : HIY +me->name()+"双眼微闭，缓缓将天地精华之气吸入体内,气流渐渐消退，白雾散去，收功站了起来。\n"NOR,
                "heal_msg" : YEL"$N神情肃然，双目虚闭，开始吸呐身周草木精华为已所用，恢复受损元气。\n"NOR,
                "heal_finish_msg" : YEL"$N将草木精华与内息融纳一体，感觉伤势已然痊愈，神情也变得清朗起来。\n"NOR,
                "heal_unfinish_msg" : HIR"$N内息难以为继，脸色愈发铁青，只好暂停疗伤，站了起来。\n"NOR,
                "heal_halt_msg" : YEL"$N突感草木精华再难与内息融合,继续疗伤反而有损真元，急忙强压内息，缓缓站起。\n"NOR,
        ]);
}

mixed hit_ob(object me, object ob, int damage)
{

        if(me->query_temp("tz/focus")
        && me->query_skill_mapped("parry") == "tiezhang-zhangfa"
        && !ob->query_condition("hot_poison")
        && random(4)==1
        ) 
         {   message_vision(HIR"$N更是将内劲布满双掌，掌心炽热，$n中掌之处疼痛难忍，犹如被火烫一般！\n"NOR,me,ob);
             ob->apply_condition("hot_poison",(int)me->query_skill("tiezhang-xinfa",1)/10);
                 }
         else
               if(me->query_temp("tz/focus")
               && me->query_skill_mapped("parry") == "tiezhang-zhangfa"
               && !ob->busy()
               && me->query("neili")>2000
               && random(4)==1
         ){
                 message_vision(HIR"$n只觉周身掌风凛冽,犹如身在洪涛巨浪之中，招式也越见涩滞！\n"NOR,me,ob);
                ob->add_busy(1+random(2));
         }
         return 1;
}


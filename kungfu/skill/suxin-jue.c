// /kungfu/skill/lamaism
// by dubei
// mizong-xinfa.c 密宗心法

 
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
        int lvl;
        
        lvl = (int)me->query_skill("suxin-jue", 1);
        
        if(me->query("gender") == "无性" && lvl > 10)
                return notify_fail("你刚听一会儿，觉得无法领悟玉女素心诀。\n");
        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("玉女素心诀只能靠读书来提高。\n");
}
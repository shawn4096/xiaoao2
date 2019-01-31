//听风辨器
// by sohu
// 暗器心法

 
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
        int lvl;
        
        lvl = (int)me->query_skill("tingfeng-bianqi", 1);
        
        if(me->query("gender") == "无性" && lvl > 10)
                return notify_fail("你刚听一会儿，觉得无法领悟暗器心法听风辨器绝技。\n");
        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("听风辨器只能靠读书来提高。\n");
}
// huanxi-chan.c 欢喜禅

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
    if( me->query("class") != "mizong")
        return notify_fail("你非大轮寺弟子，学习密宗佛法有何用？\n");
    if( (int)me->query_skill("mizong-fofa", 1) < 200 )
        return notify_fail("密宗佛法必须通过冥想修持才可以得到。\n");
	if( (int)me->query_skill("mizong-fofa", 1) >= 200 )
        return notify_fail("你不能再学习密宗佛法精要了。\n");
    return 1;
}

int practice_skill(object me)
{       
        
		return notify_fail("密宗佛法只能靠学习来提高。\n");
}

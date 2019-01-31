
//xueying-dunxing.c 血刀轻功
//血刀经
// by sohu

inherit SKILL;

string *dodge_msg = ({
"突然$n纵到$N身后，朝$N脖子处轻轻吹了口气，$N只觉得后脖凉飕飕的，忙向后纵出丈许避开。\n",
"$N只觉眼前红光一闪，$n的闪出一道血红身影遁开，$N的招式全部打在空处。\n",
"$n借用飞溅起的血光，$N的眼前顿时出现了数个$n的身形，当真不知哪个是真哪个是假。\n",
"$n喋喋怪笑，左右晃动，瞬间向后闪出尺余，在电光火石之间躲开了$N的攻击。\n",
"$N只觉眼前一花，$n的身形幻起一道艳红的细线，但随即又见$n回到原地，却似从未离开。\n",
"$N眼睛一花，便没了$n的踪影。回头一看，$n已经站在$N的的右侧方，站在那儿发出怪异的笑声。\n",
"$n嘿然一纵身，身子飞跃$N头顶，身形超过之际，瞬间侧头向$N瞪视，发出一阵阵淫笑。\n",
});

int valid_enable(string usage) 
{ 
    return usage == "dodge"; 
}

int valid_learn(object me)
{
        if (me->query_skill("xuedao-jing", 1) < 20)
			return notify_fail("血影遁形需要血刀经来支持方可学习。\n"); 
		return 1;

}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("jingli") < 40 )
                return notify_fail("你的体力太差了，不能练习血影遁形。\n");
        me->receive_damage("jingli", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xueying-dunxing/" + action;
}
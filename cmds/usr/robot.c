// Cmd:  zhua.c
// Created by Numa 1999-12-10
// Add Log

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        if (!me->is_robot())
	return notify_fail("你当前没有被系统判断为机器人，不需要召唤银翼杀手。\n");
        if (me->query_temp("robot_test"))
	return notify_fail("你还是先好好回答当前的问题吧。\n");    
   
        ob = new("/clone/npc/antirobotnew");
        ob->test_robot(me);
        tell_object(me,HIY"你召来了一个银翼杀手。\n");   
        return 1;
}
int help(object me)
{
write(@HELP
指令格式 : robot

此指令可让你在机器人状态下召来一个银翼杀手，
解除你的机器人状态。

HELP
    );
    return 1;
}


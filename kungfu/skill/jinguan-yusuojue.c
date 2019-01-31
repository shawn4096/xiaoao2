// jinguan-yusuojue.c 全真教核心心法
// by sohu
//


inherit SKILL;
#include <ansi.h>
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	int i;
	if(me->query_int() < 30)
		return notify_fail("全真教乃五绝之首，你似乎悟性太过于俗气了些。\n");
    i=me->query("yusuo/degree");
	if((int)me->query("shen") < 0 )
		return notify_fail("全真教乃是天下第一大教，名门正派，你如此邪恶焉能体会悲天悯人的天道？\n");
//	if((int)me->query_skill("jinguan-yusuojue", 1) >= 200 && !me->query("quest/qz/biguan/pass"))
		//return notify_fail("你不能再学习金关玉锁诀的奥义了。\n");
	if((int)me->query_skill("jinguan-yusuojue", 1) > me->query("max_pot")-100 )
		return notify_fail("你受经验所限，无法再进步了。\n");
	if((int)me->query_skill("jinguan-yusuojue", 1) > me->query_skill("xiantian-gong",1) )
		return notify_fail("你受先天功所限，金关玉锁诀无法再进步了。\n");
	if ((int)me->query_skill("jinguan-yusuojue",1)>100 && !me->query("yusuo/degree"))
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第一重关口方可继续修炼。\n");
	if (me->query_skill("jinguan-yusuojue",1)>200 && i<2){

		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第二重关口方可继续修炼。\n");
		}
	if (me->query_skill("jinguan-yusuojue",1)>300 && (int)me->query("yusuo/degree")<3)
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第三重关口方可继续修炼。\n");
	if (me->query_skill("jinguan-yusuojue",1)>400 && (int)me->query("yusuo/degree")<4)
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第四重关口方可继续修炼。\n");
	if (me->query_skill("jinguan-yusuojue",1)>500 && me->query("yusuo/degree")<5)
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第五重关口方可继续修炼。\n");
	if (me->query_skill("jinguan-yusuojue",1)>600 && me->query("yusuo/degree")<6)
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第六重关口方可继续修炼。\n");
	if (me->query_skill("jinguan-yusuojue",1)>700 && me->query("yusuo/degree")<7)
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第七重关口方可继续修炼。\n");
	if (me->query_skill("jinguan-yusuojue",1)>800 && me->query("yusuo/degree")<8)
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第八重关口方可继续修炼。\n");
	if (me->query_skill("jinguan-yusuojue",1)>900 && me->query("yusuo/degree")<9)
		return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第九重关口方可继续修炼。\n");
	return 1;
}


int practice_skill(object me)
{

	return notify_fail("金关玉锁诀只能靠读书或领悟来提高。\n");
}

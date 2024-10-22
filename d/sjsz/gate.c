//试剑山庄  gate.c

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	set("short",HIY"庄院"NOR);
	set("long", @LONG
眼面的庄院就是名满天下的试剑山庄了，你不觉松了一口气，前往山庄的地
上打扫的一尘不染，汉白玉砌成的台阶豪华典雅，古红木定制的大门紧闭着，使
人无法洞悉门内的一切，三丈多高的琉璃墙在透过树叶的阳光照耀下闪闪发亮，
寂静的四周只闻的远方鸟儿的鸣嘀声。
LONG
	);
        set("exits", ([
		"north" : __DIR__"qianting",
		"out": __DIR__"zongtai",
	]));

	set("no_dig", 1);
	set("outdoors", "试剑山庄");
	setup();
}

void init()
{
    object me = this_player();

    if(me->query("no_pk")){
        tell_object(me,BLINK + HIW"请注意，您已经进入了"HIG"【试剑山庄】"HIR"绝对PK环境"HIW"，系统自动临时删除了您身上的洗手状态!\n"NOR);
        tell_object(me,BLINK + HIC"当您离开试剑山庄后，系统将会自动为您恢复洗手状态！\n"NOR);
        me->set("no_pk_recover",me->query("no_pk"));
        //给予5分钟探索时间
        //me->apply_condition("sjsz_time",10);
        me->delete("no_pk");
    }

    //删除进入机会标记。
    me->add_temp("get_in_sjsz",-1);

    return;
}
int valid_leave(object me, string dir)
{
	object *ob = deep_inventory(me);
	int i = sizeof(ob);
	if( dir == "out") {
		while (i--)
		if( ob[i]->query("secret_obj"))
			return notify_fail("你带着这么贵重的东西，想离开试剑山庄是不可能的。\n");
	}

    if(dir == "out"){
      if(me->query("no_pk_recover")){
        tell_object(me,BLINK + HIG"您离开了试剑山庄，系统自动恢复了您的洗手状态！\n"NOR);
        me->set("no_pk",me->query("no_pk_recover"));
        me->delete("no_pk_recover");
      }
        me->clear_condition("sjsz_time");
		tell_object(me,BLINK + HIG"您离开了试剑山庄！\n"NOR);
    }	

	return ::valid_leave(me, dir);
}

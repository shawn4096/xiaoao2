inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "花径小路");
        set("long", @LONG
这里是后山上的小路。这条小路好象不是人工刻意修出来
的，也许只是以前的采药人踩多了，现出这样一条小路来。两旁
开满了各种野花，花香阵阵，风送花香，极为幽静，两旁山坡上
的花朵极为壮观，又大又美，漫山遍野，似乎望不到边际。
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
               // "north" : __DIR__"baihuagu",
				"northwest" : __DIR__"huajing2",               
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

void init()
{
        object me=this_player();
		message_vision(MAG"\n花香弥漫，仿佛沉浸在一片花海之中，沁人心脾，神魂舒畅。\n"NOR,me);
		//me->add_busy(1);
		
		call_out("happen1",1,me);
		return;
}

int do_find(string arg)
{
        object me = this_player();
		object bee;
		
        if(!arg ||arg != "蜜蜂") 
        	return notify_fail("你到处乱瞅，想做什么？\n");        

	    if (me->is_busy())
                return notify_fail("你正忙着呢。\n");
		me->add_busy(2);
		if(random(10)>4)
		{
			message_vision(HIY"\n\n\n$N忽然看见身旁的一朵大花上飞来一只蜜蜂，正在采蜜。\n"NOR,me);
			if (!random(3))
			{				
				if (!objectp(present("yu feng",environment(me))))
				{
					bee=new("d/gumu/npc/bee");
					bee->move(this_object());
				}
				message_vision(HIG"\n\n\n$N见到这个"HIW"玉蜂"HIG"甚是奇怪，凑近一看，见这只小玉蜂上似乎身上有字！\n"NOR,me);
				me->set_temp("baihuagu/find1",1);
				add_action("do_gensui","gensui");
				return 1;
			}else {
				message_vision(HIC"\n\n\n$N见到这个小蜜蜂真自由自在的采蜜，甚是忙碌。\n"NOR,me);
				if (!objectp(bee=present("mi feng",environment(me))))
				{
					bee=new("d/gumu/npc/bee4");
					bee->move(environment(me));
				}
			}
			return 1;

		}else message_vision(HIY"\n\n\n小蜜蜂振振翅膀，嗡嗡地飞走了。\n"NOR,me);
		me->add_busy(1);
		return 1;
}

int happen1(object me)
{
	if (!me) return 0;

	message_vision(HIC"周围极为寂静，$N沉浸在花香的海洋中，动都不想动。\n$N待了会，忽然听见空气中传来嗡嗡的声音，急忙定睛仔细观瞧。\n",me);
	message_vision(HIR"原来是在花上停了几只"HIY"蜜蜂。\n"NOR,me);
	add_action("do_find", "find");
	return 1;
}

int do_gensui(string arg)
{
	object me=this_player();
	if (!arg||arg!="玉蜂")
	{
		return notify_fail("你要跟随什么走？\n");
	}
	if (!me->query_temp("baihuagu/find1"))
	{
		return notify_fail("你跟随这只小蜜蜂走了很久，走来走去发现又回到了原点。\n");
	}
	message_vision(HIC"你心中甚是好奇，这小小的玉蜂身上居然有字，这是天生的还是人为的？\n"NOR,me);
	message_vision(HIC"\n忍住心中的好奇，跟随这只小玉蜂去看看到底是怎么回事！\n"NOR,me);
	message_vision(HIG"\n几个转完后，眼前豁然开朗！\n"NOR,me);
	me->delete_temp("baihuagu");
	me->move("d/quanzhen/baihuagu");
	
	return 1;
}

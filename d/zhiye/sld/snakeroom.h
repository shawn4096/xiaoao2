// /d/sld/snakeroom.h
// by sohu 
//增加神龙岛危险性
#include <ansi.h>

void init()
{
	object me = this_player();

	if( interactive(me) &&
		!objectp(present("xiong huang", me)) &&
		!objectp(present("snake", this_object())) &&
		random((int)me->query("combat_exp")) < 25000 )
	{
		remove_call_out("showup"); 
		call_out("showup", 1 + random(3));
	}
}

void showup()
{
	string snakefile, *snakegroup;
	object snake;
	//检查此地蛇种类
	snakegroup = query("snaketype");
	//随机
	snakefile = snakegroup[random(sizeof(snakegroup))];
	
	snakefile = "/d/sld/snake/" + snakefile;
	
	snake = new(snakefile);

	message("vision", HIR"突然一条" + snake->query("name") + "从不知什么地方游了出来！！！\n" NOR, this_object());
	snake->move(this_object());

	remove_call_out("disappear");
	call_out("disappear", 10 + random(10), snake);
}

void disappear(object snake)
{
	if( !objectp(snake) ) 
		return;

	if( !living(snake) || snake->is_fighting() || snake->is_busy() )
	{
		call_out("disappear", 10 + random(10), snake);
		return;
	}

	message_vision("只见$N飞快地游走了。\n", snake);
	destruct(snake);
}


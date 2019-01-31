// zl1.c
// 竹林1
inherit ROOM;
void create()
{
	set("short","竹林");
	set("long",@long
这里到处都是高可及天的竹子，把太阳都遮住了，又位居峰顶，随时
可以吹到海风，所以在炎夏季节是一处纳凉的好地方。偶而，海风不知从
哪里带来一股药香,竹林北面似乎是一片药圃。
long);
	set("exits",([
	    "enter" : __DIR__"tz",
           "west"  : __DIR__"zl2",
		 "north"  : __DIR__"yaopu",
	]));
	set("outdoors", "神龙岛");
    set("coor/x",490);
	set("coor/y",430);
    set("coor/z",80);
    setup();
}


/*
int do_to()
{
	object me;
	//string* pos=({"northwest","north","northeast","east","southeast","south","southwest","west"}); 
	me=this_player();

	if (me->query_temp("sld/zhongyao/start"))
	{
		tell_object(me,YEL"这时，一阵风吹过，似乎是"NOR)
	}

}


//调用去药铺的区域
int do_to(string arg)
{//每225一换 
	int times,ypstep;//times=0 西北 1 北 2 东北 3 东 4 东南 5 南 6 西南 7 西
	
	object me=this_player();
	string* pos=({"northwest","north","northeast","east","southeast","south","southwest","west"}); 
	
	int * zeropos=({0,6,3,4,1,5,2,7});

	if(!arg || arg!="east" && arg!="west" && arg!="north" && arg!="south" && arg!="northeast"
	   && arg!="northwest" && arg!="southeast" && arg!="southwest" )
		return notify_fail("你要往哪里去？\n");
	//设定进入药圃时间，计时开始
	if(!me->query_temp("yaopu/time"))
	{
		times=uptime() % 1800;
		times/=225;
		me->set_temp("yaopu/time",times);
	}
	else
		times=me->query_temp("yaopu/time",1);
	//药圃第一步
	ypstep=me->query_temp("yaopu/step",1);
	//路径走正确增加一步，走错了清零
	if(pos[(zeropos[ypstep]+times)%8]==arg)
		me->set_temp("yaopu/step",ypstep+1);
	else
		me->delete_temp("yaopu");
	
	ypstep=me->query_temp("yaopu/step",1);
	
	if(ypstep==8)
	{
		me->move(__DIR__"yaopu1");
		me->delete_temp("yaopu");
	}
	else
		tell_object(me,"你往竹林中走去。\n");
	return 1;
}*/

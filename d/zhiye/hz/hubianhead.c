

int do_mai(string arg)
{
	object me,ob;
	me=this_player();
	if (!arg||arg!="郭啸天首级")
	{
		return notify_fail("你要埋什么？\n");
	}
	if (!objectp(ob=present("guoxiaotian shouji",me)))
	{
		return notify_fail("你身上没有这样东西？\n");
	}
	if (!objectp(present("tie chu",me))&&!objectp(present("tie qiao",me)))
	{
		return notify_fail("你身上没有锄类或铁锹类工具如何挖土？\n");
	}
	if (!me->query_temp("quest/射雕英雄传/江南七怪/getshouji"))
	{
		return notify_fail("你拿个铲子在挖地要做什么?\n");
	}
	if (me->query_temp("quest/射雕英雄传/江南七怪/mailhead"))
	{
		return notify_fail("你已经埋过了！?\n");
	}
	me->set_temp("quest/射雕英雄传/江南七怪/maihead",1);
	message_vision("$N在西湖边挖了个坑将郭啸天的首级埋了下去，然后磕头拜别！\n",me);
	message_vision("$N长啸一声，抒发了心中的郁闷之情，暗自发誓，必杀段天德！\n",me);
	message_vision("$N大喊道，“段天德！我与你势不两立”\n",me);
	destruct(ob);

	return 1;
}


int do_mai(string arg)
{
	object me,ob;
	me=this_player();
	if (!arg||arg!="��Х���׼�")
	{
		return notify_fail("��Ҫ��ʲô��\n");
	}
	if (!objectp(ob=present("guoxiaotian shouji",me)))
	{
		return notify_fail("������û������������\n");
	}
	if (!objectp(present("tie chu",me))&&!objectp(present("tie qiao",me)))
	{
		return notify_fail("������û�г���������๤�����������\n");
	}
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/getshouji"))
	{
		return notify_fail("���ø��������ڵ�Ҫ��ʲô?\n");
	}
	if (me->query_temp("quest/���Ӣ�۴�/�����߹�/mailhead"))
	{
		return notify_fail("���Ѿ�����ˣ�?\n");
	}
	me->set_temp("quest/���Ӣ�۴�/�����߹�/maihead",1);
	message_vision("$N�����������˸��ӽ���Х����׼�������ȥ��Ȼ���ͷ�ݱ�\n",me);
	message_vision("$N��Хһ�����㷢�����е�����֮�飬���Է��ģ���ɱ����£�\n",me);
	message_vision("$N�󺰵���������£��������Ʋ�������\n",me);
	destruct(ob);

	return 1;
}
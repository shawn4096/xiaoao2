//linhai.h 
//cre bu sohu@xojh

void init()
{
	object me=this_player();
	object fox;
	if (me->query_temp("quest/shendiao/��ѩ�����/askheal")
		&& !me->query_temp("anran/findfox")
		&& random(10)>5
		&& me->query_temp("quest/shendiao/��ѩ�����/yingok"))
	{
		message_vision(HIY"$N�ڴ����б��߱߰�����������֮�����ɹ�����ֻ��β�������������\n"NOR,me);
		fox=new("clone/npc/fox");
		fox->move(environment(me));
		me->set_temp("anran/findfox",1);
	}
	return;
}


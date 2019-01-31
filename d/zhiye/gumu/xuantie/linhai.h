//linhai.h 
//cre bu sohu@xojh

void init()
{
	object me=this_player();
	object fox;
	if (me->query_temp("quest/shendiao/大雪风陵渡/askheal")
		&& !me->query_temp("anran/findfox")
		&& random(10)>5
		&& me->query_temp("quest/shendiao/大雪风陵渡/yingok"))
	{
		message_vision(HIY"$N在丛林中边走边按照瑛姑所授之法，成功将这只九尾灵狐吸引出来！\n"NOR,me);
		fox=new("clone/npc/fox");
		fox->move(environment(me));
		me->set_temp("anran/findfox",1);
	}
	return;
}


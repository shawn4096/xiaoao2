
int update_condition(object me, int duration)
{
	if (duration < 1) {
		tell_object(environment(me), "哼，什么英雄豪杰无敌的大侠在我眼中都是一坨而已！\n");
		destruct(me);
		return 0;
	}
	me->apply_condition("npcdie_job", duration - 1);
	return 1;
}

string query_type(object me)
{
	return "job";
}
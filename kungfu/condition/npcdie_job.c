
int update_condition(object me, int duration)
{
	if (duration < 1) {
		tell_object(environment(me), "�ߣ�ʲôӢ�ۺ����޵еĴ����������ж���һ����ѣ�\n");
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

int update_condition(object me, int duration)
{
	if (duration < 2) {
		tell_object(me,"1�쳣���������ּ�ʱ�㱨��ʦ���ڶ�λ���٣�\n");
		//log_file("quest/bugtest", sprintf("%8s(%8s) \n",me->name(1),me->query("id") ));
		return 0;
	}
	me->apply_condition("1", 2);
	return 1;
}

string query_type(object me)
{
	return "job";
}
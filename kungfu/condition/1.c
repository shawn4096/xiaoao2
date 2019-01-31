
int update_condition(object me, int duration)
{
	if (duration < 2) {
		tell_object(me,"1异常结束，发现及时汇报巫师，在定位跟踪！\n");
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
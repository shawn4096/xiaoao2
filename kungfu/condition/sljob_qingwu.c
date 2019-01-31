
int update_condition(object me, int duration)
{
	if (duration < 1){
		// if(me->query_temp("quest/id"))	
		// me->apply_condition("job_busy", 40);
		 return 0;
		 }
	me->apply_condition("sljob_qingwu", duration - 1);
	return 1;
}

string query_type(object me)
{
	return "job";
}

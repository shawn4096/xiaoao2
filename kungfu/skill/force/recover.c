// recover.c

//inherit SSERVER;

int exert(object me, object target)
{
	int n, q;

	if (me->query("neili") < 20 || !me->query_skill("force"))
		return notify_fail("�������������\n");
	q = me->query("eff_qi") + me->query_temp("apply/qi") - me->query("qi");
	if (q < 10)
		return notify_fail("�������������档\n");
	n = 100 * q / me->query_skill("force");
	if (n < 20)
		n = 20;
	if (me->query("neili") < n) {
		n = me->query("neili");
		q = me->query("neili") * me->query_skill("force") / 100;
	}

	me->add("neili", -(int)n);
	me->receive_heal("qi", (int)q);
	
	message_vision("$N�������˼���������ɫ�������ö��ˡ�\n", me);

	q *= sqrt(q);
	q /= 2000;
	me->improve_skill("force", q, 1);
        if (me->is_fighting())
		me->start_busy(1);

	return 1;
}